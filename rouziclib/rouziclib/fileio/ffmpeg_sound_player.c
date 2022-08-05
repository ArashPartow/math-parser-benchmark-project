#ifdef RL_FFMPEG

int audio_player_load_thread(audio_player_data_t *data)
{
	int i, ip=-1, must_seek=0, ip0=-1, ip1;
	double ts_req=0., ts0=NAN, ts0_end=0., ts1=NAN;
	ffframe_info_t info;
	int ret=0, sample_count;
	float *buf=NULL;
	size_t buf_as=0, buf_pos=0;

	while (data->thread_on)
	{
loop_start:
		rl_mutex_lock(&data->mutex);

		// if we're jumping back or forward
		if (data->speed < 0. || data->ts_req < ts_req || (data->ts_req - ts1 > 60. && isnan(ts1)==0))
		{
			ip = -1;
			ts0 = NAN;
			ts0_end = 0.;
			ts1 = NAN;
			must_seek = 1;
			ip0 = -1;
			ip1 = -1;
		}

		ts_req = data->ts_req;

		rl_mutex_unlock(&data->mutex);

		// Pause the loading if the frame to be replaced next is still needed
		if (ts_req >= ts0 && ts_req < ts0_end && must_seek==0 && data->thread_on && circ_index(ip+1, data->frame_as)==ip0)
		{
			sleep_ms(1);
			goto loop_start;
		}

		if (llabs(double_diff_ulp(data->speed, 1.)) < 100)
		{
			// Load the frame, either by seeking or sequentially
			buf_pos = 0;
			ret = ff_load_audio_fl32(data->stream, data->path, must_seek, ts_req, &buf, &buf_as, &buf_pos);
			if (ret >= 0)
				sample_count = data->stream->frame->nb_samples;
		}

		if (ret <= 0)
			sleep_ms(20);		// if the frame was empty just wait
		else
		{
			info = ff_make_frame_info(data->stream);

			rl_mutex_lock(&data->mutex);

			// Add the frame to the tables
			ip = circ_index(ip + 1, data->frame_as);

			// if new frame replaces old frame[ip0]
			if (ip==ip0)
			{
				ip0 = circ_index(ip + 1, data->frame_as);
				ts0 = data->frame[ip0].info.ts;
				ts0_end = data->frame[ip0].info.ts_end;
			}

			if (isnan(ts0))			// init ts0
			{
				ip0 = ip;
				ts0 = MINN(ts_req, info.ts);	// in case info.ts is higher than ts_req
				ts0_end = info.ts_end;
			}
			ts1 = info.ts_end;
			ip1 = ip;

			data->frame[ip].used = 1;
			data->frame[ip].sample_count = sample_count;
			data->frame[ip].channels = data->stream->frame->ch_layout.nb_channels;
			data->frame[ip].samplerate = data->stream->codec_ctx->sample_rate;
			alloc_enough_and_copy(&data->frame[ip].buffer, buf, data->frame[ip].len = ret, &data->frame[ip].as, sizeof(float), 1.);
			data->frame[ip].info = info;

			if (must_seek==0)
				data->frame[ip].info.ts = data->frame[circ_index(ip - 1, data->frame_as)].info.ts_end;
			data->frame[ip].info.ts_end = data->frame[ip].info.ts + (double) sample_count / data->frame[ip].samplerate;

			rl_mutex_unlock(&data->mutex);
		}

		must_seek = 0;
	}

	ffstream_close_free(data->stream);

	return 0;
}

void audio_player_thread_exit(audio_player_data_t *data)
{
	int i;

	rl_mutex_lock(&data->mutex);

	for (i=0; i < data->frame_as; i++)
	{
		free(data->frame[i].buffer);
		memset(&data->frame[i], 0, sizeof(audframe_t));
	}

	rl_mutex_unlock(&data->mutex);
}

void audio_player_main(audio_player_data_t *data, char *path, double ts_req, double speed, double volume)
{
	int start_thread=1, stop_thread=1, jump=0;

	// Close the old stream and open the new one
	if (path && data->path)
	if (strcmp(path, data->path)==0)
	{
		start_thread = 0;
		stop_thread = 0;
	}

	if (path==NULL)
		start_thread = 0;

	// Init the data
	if (data->init==0)
	{
		data->init = 1;
		rl_mutex_init(&data->mutex);
		data->frame = calloc(data->frame_as = 600, sizeof(audframe_t));
		data->stream = calloc(1, sizeof(ffstream_t));
	}

	if (stop_thread)
	{
		data->thread_on = 0;
		audiosys_bus_unregister(data);
		audio_player_thread_exit(data);
		free_null(&data->path);
	}

	if (start_thread)
	{
		// Initialise new data
		data->path = make_string_copy(path);
		data->duration = ff_get_audio_duration(NULL, data->path);
		data->ts_req = 0.;
		data->ifr = -1;
		data->is = -1;
		data->thread_on = 1;
		rl_thread_create(&data->thread_handle, audio_player_load_thread, data);
	}

	// Update values
	rl_mutex_lock(&data->mutex);

	if (fabs(data->ts_cb - ts_req) > 2. * audiosys.sec_per_buf + 0.05)	// FIXME calculate whether to jump or not better
		jump = 1;

	if (jump)
		fprintf_rl(stdout, "jump to ts %.4f\n", ts_req);

	// Set the time offset
	if (jump || start_thread)
		data->ts_cb = ts_req;
		//data->time_offset = get_time_hr() - ts_req;

	data->ts_req = rangelimit(ts_req - 1., 0., data->duration);
	data->speed = speed;
	data->volume = volume;

	rl_mutex_unlock(&data->mutex);

	// Register the callback
	int audio_bus_index = audiosys_bus_register(audio_player_callback, data, 0, 0.);
}

void audio_player_callback(float *stream, audiosys_t *sys, int bus_index, audio_player_data_t *data)
{
	int i, ifr;
	double t, ibl, vol_t;
int debug=1;

	// Deinit
	if (stream==NULL)
	{
		data->thread_on = 0;

		if (bus_index == -1)	// this signals a blocking deinitialisation
			rl_thread_join_and_null(&data->thread_handle);

		data->vol1 = NAN;
		return;
	}

	// Only play if speed == 1 and thread_on
	if (fabs(data->speed - 1.) >= 2e-14 || data->thread_on==0)
	{
		data->vol1 = NAN;
		return;
	}

	rl_mutex_lock(&data->mutex);

	// Prepare volume interpolation
	data->vol0 = data->vol1;
	if (isnan(data->vol0))
		data->vol0 = data->volume;
	data->vol1 = data->volume;
	ibl = 1. / (double) sys->buffer_len;

	// Go through each sample
	for (t=data->ts_cb, i=0; i < sys->buffer_len; i++, t+=sys->sec_per_sample)
	{
		// Search for frame when no frame is selected
		if (data->ifr = -1)
		{
			// Search for frame that contains the requested timestamp
			for (ifr=0; ifr < data->frame_as; ifr++)
				if (t >= data->frame[ifr].info.ts && t < data->frame[ifr].info.ts_end)
				{
					data->ifr = ifr;
					data->is = (t - data->frame[ifr].info.ts) * data->frame[ifr].samplerate;
					if (data->is > data->frame[ifr].sample_count-1)
						data->ifr = -1;
					else
						break;
				}
		}

		// Interpolate volume
		vol_t = mix(data->vol0, data->vol1, (double) i * ibl);
		//if (data->vol0 != data->vol1 && ((i & 0xFF) == 0 || i == sys->buffer_len -1)) fprintf_rl(stdout, "mix(%.6f , %.6f, %.6f) = %.6f (%4d/%4d)\n", data->vol0, data->vol1, (double) i * ibl, vol_t, i, sys->buffer_len);

		// Copy samples from frame
		if (data->ifr != -1)
		{
			if (data->frame[data->ifr].channels==1)
			{
				stream[i*2  ] += data->frame[data->ifr].buffer[data->is] * vol_t;
				stream[i*2+1] += data->frame[data->ifr].buffer[data->is] * vol_t;
			}
			else
			{
				stream[i*2  ] += data->frame[data->ifr].buffer[data->is*data->frame[data->ifr].channels] * vol_t;
				stream[i*2+1] += data->frame[data->ifr].buffer[data->is*data->frame[data->ifr].channels + 1] * vol_t;
			}
		}
else if (debug)
{
	debug = 0;
	double min_ts=1e9, max_ts=-1.;
	for (ifr=0; ifr < data->frame_as; ifr++)
	{
		min_ts = MINN(min_ts, data->frame[ifr].info.ts);
		max_ts = MAXN(max_ts, data->frame[ifr].info.ts_end);
	}
	fprintf_rl(stdout, "No sample for ts %.4f (ts available: %.4f to %.4f\n", t, min_ts, max_ts);
}

		// Iterate to next sample
		data->is++;
		if (data->is == data->frame[data->ifr].sample_count)
		{
			data->ifr = -1;
		}
	}
	data->ts_cb += sys->sec_per_buf;

	rl_mutex_unlock(&data->mutex);
}

#endif
