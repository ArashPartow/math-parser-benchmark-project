#ifdef RL_FFMPEG

static char *const ffmpeg_get_error_text(const int error)
{
	static char error_buffer[255];
	av_strerror(error, error_buffer, sizeof(error_buffer));
	return error_buffer;
}

int ffmpeg_retval(const int ret)
{
	if (ret < 0 && ret != AVERROR(EAGAIN))
		fprintf_rl(stdout, "LibAV error: %s\n", ffmpeg_get_error_text(ret));

	return ret < 0;
}

// TODO try hwaccel stuff from https://www.ffmpeg.org/doxygen/4.0/hw_decode_8c-example.html

int ff_init_stream(ffstream_t *s, const int stream_type)	// returns 1 on success
{
	int i, ret;

	// Find stream
	s->stream_id = -1;

	for (i=0; i < s->fmt_ctx->nb_streams; i++)
		if (s->fmt_ctx->streams[i]->codec->codec_type == stream_type)	// find the video stream
		{
			s->stream_id = i;
			break;
		}

	if (s->stream_id == -1)
		return 0;

	// Load codec
	s->codec_ctx = s->fmt_ctx->streams[s->stream_id]->codec;
	s->codec = avcodec_find_decoder(s->codec_ctx->codec_id);

	ret = avcodec_open2(s->codec_ctx, s->codec, NULL);
	ffmpeg_retval(ret);
	if (ret < 0)
		return 0;

	// Frame
	s->frame = av_frame_alloc();

	return 1;
}

ffstream_t ff_load_stream_init(char const *path, const int stream_type)
{
	int i, ret;
	ffstream_t s={0};

	s.stream_id = -1;

	if (path == NULL)
		return s;

	// Open file
	if (ret = avformat_open_input(&s.fmt_ctx, path, NULL, NULL))
	{
		ffmpeg_retval(ret);
		fprintf_rl(stderr, "Couldn't avformat_open_input() file '%s'\n", path);
		return s;
	}

	ret = avformat_find_stream_info(s.fmt_ctx, NULL);
	ffmpeg_retval(ret);

	// Init
	ff_init_stream(&s, stream_type);

	return s;
}

int ff_load_stream_packet(ffstream_t *s)
{
	int i, ret, result=0;
	AVPacket packet={0};

	av_init_packet(&packet);

	while (av_read_frame(s->fmt_ctx, &packet)==0)				// get the next frame from the file
	{
		if (packet.stream_index == s->stream_id)			// check that it's the right stream
		{
			s->byte_pos = packet.pos;
			ret = avcodec_send_packet(s->codec_ctx, &packet);	// supply raw packet data as input to a decoder
			if (ret != AVERROR_EOF)
				ffmpeg_retval(ret);

			ret = avcodec_receive_frame(s->codec_ctx, s->frame);	// return decoded output data (in frame) from a decoder
			if (ret != AVERROR_EOF)
				ffmpeg_retval(ret);

			if (ret >= 0)
				result = 1;
		}

		av_packet_unref(&packet);

		if (result)
			break;
	}

	// Flush the decoder
	if (result==0)
	{
		ret = avcodec_send_packet(s->codec_ctx, NULL);
		if (ret != AVERROR_EOF)
			ffmpeg_retval(ret);

		ret = avcodec_receive_frame(s->codec_ctx, s->frame);
		if (ret != AVERROR_EOF)
			ffmpeg_retval(ret);

		if (ret >= 0)
			result = 1;
	}

	return result;
}

void ffstream_close_free(ffstream_t *s)
{
	free_null(&s->frame_info);
	av_frame_free(&s->frame);
	avcodec_close(s->codec_ctx);
	avformat_close_input(&s->fmt_ctx);
	memset(s, 0, sizeof(ffstream_t));
}

double ff_get_timestamp(ffstream_t *s, int64_t timestamp)
{
	AVRational time_base = s->fmt_ctx->streams[s->stream_id]->time_base;
	int64_t start_time = s->fmt_ctx->streams[s->stream_id]->start_time;

	return (timestamp - 0*start_time) * av_q2d(time_base);
}

double ff_get_frame_timestamp(ffstream_t *s)
{
	return ff_get_timestamp(s, s->frame->best_effort_timestamp);
}

int64_t ff_make_timestamp(ffstream_t *s, double t)
{
	AVRational time_base = s->fmt_ctx->streams[s->stream_id]->time_base;
	int64_t start_time = s->fmt_ctx->streams[s->stream_id]->start_time;

	return nearbyint(t / av_q2d(time_base) + 0*start_time);
}

/*raster_t ff_frame_to_raster(ffstream_t *s, const int mode)
{
	AVFrame *frame_rgb = av_frame_alloc();
	int alloc_size;
	uint8_t *buffer;
	raster_t im={0};
	struct SwsContext *sws_ctx={0};
	const int rgb_fmt = AV_PIX_FMT_0BGR32;
uint32_t td=0;
get_time_diff(&td);

	sws_ctx = sws_getCachedContext( sws_ctx,
				 s->frame->width,
				 s->frame->height,
				 s->codec_ctx->pix_fmt,
				 s->frame->width,
				 s->frame->height,
				 rgb_fmt,
				 SWS_BILINEAR,
				 NULL,
				 NULL,
				 NULL );

	alloc_size = av_image_get_buffer_size(rgb_fmt, s->codec_ctx->width, s->codec_ctx->height, 1);
	buffer = av_malloc(alloc_size);
//fprintf_rl(stdout, "\n\t sws_getCachedContext() took %d ms\n", get_time_diff(&td));

	av_image_fill_arrays(frame_rgb->data, frame_rgb->linesize, buffer, rgb_fmt, s->codec_ctx->width, s->codec_ctx->height, 1);
//fprintf_rl(stdout, "\t av_image_fill_arrays() took %d ms\n", get_time_diff(&td));

	sws_scale(sws_ctx, s->frame->data, s->frame->linesize, 0, s->frame->height, frame_rgb->data, frame_rgb->linesize);
//fprintf_rl(stdout, "\t sws_scale() took %d ms\n", get_time_diff(&td));

	im.dim = xyi(s->codec_ctx->width, s->codec_ctx->height);
	convert_image_srgb8(&im, frame_rgb->data[0], mode);
//fprintf_rl(stdout, "\t convert_image_srgb8() took %d ms\n", get_time_diff(&td));

	av_free(buffer);
	av_frame_free(&frame_rgb);
	sws_freeContext(sws_ctx);

	return im;
}*/

int ff_pix_fmt_byte_count(int pix_fmt)
{
	if (	(pix_fmt >= AV_PIX_FMT_YUV420P9BE  && pix_fmt <= AV_PIX_FMT_YUV422P9LE ) ||
		(pix_fmt >= AV_PIX_FMT_YUV420P16LE && pix_fmt <= AV_PIX_FMT_YUV444P16BE) ||
	  	(pix_fmt >= AV_PIX_FMT_YUV420P12BE && pix_fmt <= AV_PIX_FMT_YUV444P14LE) )
		return 2;

	return 1;
}

int ff_pix_fmt_bit_depth(int pix_fmt)
{
	switch (pix_fmt)
	{
		case AV_PIX_FMT_YUV420P9LE:
		case AV_PIX_FMT_YUV420P9BE:
			return 9;

		case AV_PIX_FMT_YUV420P10LE:
		case AV_PIX_FMT_YUV420P10BE:
			return 10;

		case AV_PIX_FMT_YUV420P12LE:
		case AV_PIX_FMT_YUV420P12BE:
			return 12;

		case AV_PIX_FMT_YUV420P14LE:
		case AV_PIX_FMT_YUV420P14BE:
			return 14;

		case AV_PIX_FMT_YUV420P16LE:
		case AV_PIX_FMT_YUV420P16BE:
			return 16;

		default:
			return 8;
	}
}

int ff_pix_fmt_to_buf_fmt(int pix_fmt)
{
	switch (pix_fmt)
	{
		case AV_PIX_FMT_YUV420P:
			return 10;

		case AV_PIX_FMT_YUV420P10LE:
			return 11;

		case AV_PIX_FMT_YUV420P12LE:
			return 12;
	}

	return -1;
}

int ff_buf_fmt_to_pix_fmt(int buf_fmt)
{
	switch (buf_fmt)
	{
		case 10:
			return AV_PIX_FMT_YUV420P;

		case 11:
			return AV_PIX_FMT_YUV420P10LE;

		case 12:
			return AV_PIX_FMT_YUV420P12LE;
	}

	return -1;
}

raster_t ff_frame_to_buffer(ffstream_t *s)
{
	int i, ip, bpc = 1;
	raster_t im={0};
	uint8_t *plane[3];

	bpc = ff_pix_fmt_byte_count(s->codec_ctx->pix_fmt);
	im.buf_fmt = ff_pix_fmt_to_buf_fmt(s->codec_ctx->pix_fmt);

	im.dim = xyi(s->codec_ctx->width, s->codec_ctx->height);
	im.buf_size = av_image_get_buffer_size(s->codec_ctx->pix_fmt, s->codec_ctx->width, s->codec_ctx->height, 1);
	im.buf = malloc(im.buf_size);
	if (im.buf==NULL)
	{
		fprintf_rl(stderr, "malloc(%zu) failed in ff_frame_to_buffer()\n", im.buf_size);
		return im;
	}
	plane[0] = im.buf;
	plane[1] = &plane[0][bpc * mul_x_by_y_xyi(im.dim)];
	plane[2] = &plane[1][bpc * mul_x_by_y_xyi(im.dim)/4];

	ip = 0;
	for (i=0; i < im.dim.y; i++)
		memcpy(&plane[ip][i*im.dim.x * bpc], &s->frame->data[ip][i*s->frame->linesize[ip]], bpc * im.dim.x);

	for (ip=1; ip < 3; ip++)
		for (i=0; i < im.dim.y>>1; i++)
			memcpy(&plane[ip][i*(im.dim.x>>1) * bpc], &s->frame->data[ip][i*s->frame->linesize[ip]], bpc * im.dim.x>>1);

	return im;
}

raster_t ff_frame_to_raster(ffstream_t *s, const int mode)
{
	int bpc, bit_depth, lsy, lsuv;
	raster_t im={0};
	xyi_t ip, iph;
	xyz_t yuv, depth_mul;
	uint8_t **d8=NULL;
	uint16_t **d16=NULL;

	im = make_raster(NULL, xyi(s->codec_ctx->width, s->codec_ctx->height), XYI0, mode);

	// Prepare parameters and pointers
	bpc = ff_pix_fmt_byte_count(s->codec_ctx->pix_fmt);
	bit_depth = ff_pix_fmt_bit_depth(s->codec_ctx->pix_fmt);
	lsy = s->frame->linesize[0] / bpc;
	lsuv = s->frame->linesize[1] / bpc;

	if (bpc==1)
	{
		d8 = s->frame->data;

		if (mode == IMAGE_USE_FRGB)
			for (ip.y=0; ip.y < im.dim.y; ip.y++)
				for (ip.x=0; ip.x < im.dim.x; ip.x++)
				{
					iph = rshift_xyi(ip, 1);
					yuv = xyz(d8[0][ip.y*lsy + ip.x], d8[1][iph.y*lsuv + iph.x], d8[2][iph.y*lsuv + iph.x]);
					im.f[ip.y*im.dim.x + ip.x] = yuv_to_frgb(yuv);
				}
		else if (mode == IMAGE_USE_SQRGB)
			for (ip.y=0; ip.y < im.dim.y; ip.y++)
				for (ip.x=0; ip.x < im.dim.x; ip.x++)
				{
					iph = rshift_xyi(ip, 1);
					yuv = xyz(d8[0][ip.y*lsy + ip.x], d8[1][iph.y*lsuv + iph.x], d8[2][iph.y*lsuv + iph.x]);
					im.sq[ip.y*im.dim.x + ip.x] = frgb_to_sqrgb(yuv_to_frgb(yuv));
				}
	}
	else
	{
		d16 = (uint16_t **) s->frame->data;
		depth_mul = set_xyz(1. / (double) (1 << bit_depth-8));

		if (mode == IMAGE_USE_FRGB)
			for (ip.y=0; ip.y < im.dim.y; ip.y++)
				for (ip.x=0; ip.x < im.dim.x; ip.x++)
				{
					iph = rshift_xyi(ip, 1);
					yuv = xyz(d16[0][ip.y*lsy + ip.x], d16[1][iph.y*lsuv + iph.x], d16[2][iph.y*lsuv + iph.x]);
					im.f[ip.y*im.dim.x + ip.x] = yuv_to_frgb(mul_xyz(yuv, depth_mul));
				}
		else if (mode == IMAGE_USE_SQRGB)
			for (ip.y=0; ip.y < im.dim.y; ip.y++)
				for (ip.x=0; ip.x < im.dim.x; ip.x++)
				{
					iph = rshift_xyi(ip, 1);
					yuv = xyz(d16[0][ip.y*lsy + ip.x], d16[1][iph.y*lsuv + iph.x], d16[2][iph.y*lsuv + iph.x]);
					im.sq[ip.y*im.dim.x + ip.x] = frgb_to_sqrgb(yuv_to_frgb(mul_xyz(yuv, depth_mul)));
				}
	}

	return im;
}

void ff_seek_timestamp(ffstream_t *s, double ts, int64_t pts, int flush)
{
	int ret;

	if (isnan(ts)==0)
		pts = ff_make_timestamp(s, ts);

	ret = av_seek_frame(s->fmt_ctx, s->stream_id, pts, AVSEEK_FLAG_ANY);
	ffmpeg_retval(ret);

	if (flush && s->codec_ctx)
		avcodec_flush_buffers(s->codec_ctx);
}

void ff_seek_byte(ffstream_t *s, int64_t pos, int flush)
{
	int ret;

	//seek_frame_byte(s->fmt_ctx, s->stream_id, pos, 0);

	//ret = av_seek_frame(s->fmt_ctx, s->stream_id, pos, AVSEEK_FLAG_BYTE);
	ret = avio_seek(s->fmt_ctx->pb, pos, SEEK_SET);
	//ffmpeg_retval(ret);

	if (flush)
	{
		avio_flush(s->fmt_ctx->pb);
		avformat_flush(s->fmt_ctx);
		if (s->codec_ctx)
			avcodec_flush_buffers(s->codec_ctx);
	}
}

int ff_find_table_frame_id(ffstream_t *s, double t, const int keyframe)
{
	int i, ret, frame_id;

	if (s->frame_info==NULL)
		return -1;

	// check if t isn't after the expected end
	if (t > s->frame_info[s->frame_count-1].ts_end)
		return -1;

	frame_id = -1;
	for (i=0; i < s->frame_count; i++)
		if (t >= s->frame_info[i].ts)
		{
			if (s->frame_info[i].key_frame || keyframe==0)
				frame_id = i;
		}
		else
			break ;

	if (frame_id > -1)
	{
		ff_seek_timestamp(s, NAN, s->frame_info[frame_id].pts, keyframe);
		//ff_seek_byte(s, s->frame_info[frame_id].pkt_pos, keyframe);

		ff_load_stream_packet(s);		// get the sought frame

		if (s->frame_info[frame_id].ts != ff_get_frame_timestamp(s))
			fprintf_rl(stdout, "\tSought PTS %.3f s - Found PTS %.3f sec\n", s->frame_info[frame_id].ts, ff_get_frame_timestamp(s));
	}

	return frame_id;
}

int ff_decode_frame_from_table(ffstream_t *s, double t)
{
	int frame_id;

	if (s->frame_info)
		if (frame_id = ff_find_table_frame_id(s, t, 1) > -1)
		{
			if (s->frame_info[frame_id].ts == t)
				return 1;

			if (ff_find_table_frame_id(s, t, 0) > -1)
				return 1;
		}

	return 0;
}

int ff_find_keyframe_for_time(ffstream_t *s, const double t)
{
	int i, ret;
	AVFrame *f;
	int64_t timestamp, timestamp_o=-1;
	double seek_offset=0.;
	int frame_id;

	if (s->frame_info)
		if (ret = ff_find_table_frame_id(s, t, 1) > -1)
			return ret;

	if (t < 2.)
	{
		//ff_seek_byte(s, 0, 1);
		ff_seek_timestamp(s, 0., 0, 1);

		if (ff_load_stream_packet(s))		// get the sought frame
			return 1;
		else
			return 0;
	}

	// initial seek
seek_start:
	timestamp = ff_make_timestamp(s, t+seek_offset);	// FIXME timestamp can't be before the start
	if (timestamp_o==-1)
		timestamp_o = timestamp;
	ret = av_seek_frame(s->fmt_ctx, s->stream_id, timestamp, AVSEEK_FLAG_BACKWARD);
	ffmpeg_retval(ret);
	if (s->codec_ctx)
		avcodec_flush_buffers(s->codec_ctx);

	if (ff_load_stream_packet(s))		// get the sought frame
	{
		f = s->frame;
		if (f->best_effort_timestamp > timestamp_o)
		{
			seek_offset -= 1.;	// seek one second further back
			if (t+seek_offset <= -2.)
				return 0;

			//fprintf_rl(stdout, "The found keyframe is %g seconds late, seeking %g seconds back\n", ff_get_timestamp(s, s->frame->best_effort_timestamp) - ff_get_timestamp(s, timestamp_o), seek_offset);
			goto seek_start;	// go back to the start of the seeking
		}

		//fprintf_rl(stdout, "%d x %d, format %d, type %d\ttimestamp %5.3f s, number %d%s\n", f->width, f->height, f->format, f->pict_type, ff_get_frame_timestamp(s), f->coded_picture_number, f->key_frame ? ", KEYFRAME" : "");
	}
	else
		return 0;

	return 1;
}

int ff_find_frame_at_time(ffstream_t *s, const double t)	// finds and decode properly the right frame at a given time (can sometimes be one frame late)
{
	AVFrame *f;

	if (ff_find_keyframe_for_time(s, t))		// find the preceding keyframe
	{
		do
		{
			f = s->frame;
			if (ff_get_timestamp(s, f->best_effort_timestamp + f->pkt_duration) > t)	// if the next frame would be after t
				return 1;								// caveat: pkt_duration can fail to accurately predict the next timestamp
		}
		while (ff_load_stream_packet(s));
	}

	return 0;
}

ffframe_info_t ff_make_frame_info(ffstream_t *s)
{
	ffframe_info_t fi={0};

	if (s->frame==NULL)
		return fi;

	fi.key_frame = s->frame->key_frame;
	fi.pkt_pos = s->frame->pkt_pos;
	fi.pts = s->frame->pkt_dts;
	if (s->frame->pkt_dts == 0x8000000000000000)
		fi.pts = s->frame->pkt_pts;
	fi.ts = ff_get_timestamp(s, fi.pts);
	fi.ts_end = ff_get_timestamp(s, fi.pts + s->frame->pkt_duration);

	return fi;
}

void ff_make_frame_table(ffstream_t *s)
{
	int ret;
	AVPacket packet={0};

	av_init_packet(&packet);

	while (av_read_frame(s->fmt_ctx, &packet)==0)				// get the next frame from the file
	{
		if (packet.stream_index == s->stream_id)			// check that it's the right stream
		{
			ret = avcodec_send_packet(s->codec_ctx, &packet);	// supply raw packet data as input to a decoder
			ffmpeg_retval(ret);

			ret = avcodec_receive_frame(s->codec_ctx, s->frame);	// return decoded output data (in frame) from a decoder
			ffmpeg_retval(ret);

			alloc_enough(&s->frame_info, s->frame_count+=1, &s->frame_as, sizeof(ffframe_info_t), 1.5);
			s->frame_info[s->frame_count-1] = ff_make_frame_info(s);
		}

		av_packet_unref(&packet);
	}
}

double ff_get_stream_duration(ffstream_t *s, const char *path, int stream_type)
{
	int i, ret;
	uint32_t td=0;
	double duration;

	if (s==NULL)		// allows finding the duration even if s is NULL
	{
		ffstream_t stream={0};
		duration = ff_get_video_duration(&stream, path);
		ffstream_close_free(&stream);
		return duration;
	}

	if (s->fmt_ctx==NULL)
	{
		*s = ff_load_stream_init(path, stream_type);
		if (s->stream_id == -1)
			return NAN;
	}

	if (s->fmt_ctx->duration == AV_NOPTS_VALUE)
		return NAN;

	return (double) s->fmt_ctx->duration / (double) AV_TIME_BASE;
}

double ff_get_video_duration(ffstream_t *s, const char *path)
{
	return ff_get_stream_duration(s, path, AVMEDIA_TYPE_VIDEO);
}

double ff_get_audio_duration(ffstream_t *s, const char *path)
{
	return ff_get_stream_duration(s, path, AVMEDIA_TYPE_AUDIO);
}

raster_t ff_load_video_raster(ffstream_t *s, const char *path, const int seek_mode, const double t, const int raster_mode)
{
	int i, ret=0;
	raster_t im={0};

	// Init
	if (s->fmt_ctx==NULL)
	{
		*s = ff_load_stream_init(path, AVMEDIA_TYPE_VIDEO);
		if (s->stream_id == -1)
			return im;
	}

	if (s->stream_id == -1)
		return im;

	// Load AVFrame
	switch (seek_mode)
	{
		case 0:		// next frame
			ret = ff_load_stream_packet(s);
			break;

		case 1:		// frame at time
			ret = ff_find_frame_at_time(s, t);
			break;

		case 2:		// keyframe before time
			ret = ff_find_keyframe_for_time(s, t);
			break;
	}

	// Convert frame data
	if (ret)
		if (raster_mode & IMAGE_USE_BUF)
			im = ff_frame_to_buffer(s);
		else
			im = ff_frame_to_raster(s, raster_mode);

	return im;
}

// Audio

int ff_load_audio_fl32(ffstream_t *s, const char *path, const int seek_mode, const double t, float **bufp, size_t *buf_as, size_t *buf_pos)
{
	int i, ic, ret=0;
	size_t buf_size;

	// Init
	if (s->fmt_ctx==NULL)
	{
		*s = ff_load_stream_init(path, AVMEDIA_TYPE_AUDIO);
		if (s->stream_id == -1)
			return -1;

		AVDictionaryEntry *t = NULL;
		while (t = av_dict_get(s->fmt_ctx->metadata, "", t, AV_DICT_IGNORE_SUFFIX))
			fprintf_rl(stdout, "%s: %s\n", t->key, t->value);
	}

	if (s->stream_id == -1)
		return -1;

	// Load AVFrame
	switch (seek_mode)
	{
		case 0:		// next frame
			ret = ff_load_stream_packet(s);
			break;

		case 1:		// frame at time
			ret = ff_find_frame_at_time(s, t);
			break;
	}

	// Convert frame data
	if (ret)
	{
		// Enlarge the output buffer
		buf_size = *buf_pos + s->frame->nb_samples * s->frame->channels;
		alloc_enough(bufp, buf_size, buf_as, sizeof(float), 1.5);

		// Convert/copy samples
		switch (s->codec_ctx->sample_fmt)
		{
			case AV_SAMPLE_FMT_U8:
				for (i=0; i < s->frame->nb_samples * s->frame->channels; i++)
					(*bufp)[*buf_pos + i] = ((int) ((uint8_t *)s->frame->data[0])[i] - 128) * 1.f/128.f;
				break;

			case AV_SAMPLE_FMT_U8P:
				for (i=0; i < s->frame->nb_samples; i++)
					for (ic=0; ic < s->frame->channels; ic++)
						(*bufp)[*buf_pos + i*s->frame->channels + ic] = ((int) ((uint8_t *)s->frame->data[ic])[i] - 128) * 1.f/128.f;
				break;

			case AV_SAMPLE_FMT_S16:
				for (i=0; i < s->frame->nb_samples * s->frame->channels; i++)
					(*bufp)[*buf_pos + i] = ((int16_t *)s->frame->data[0])[i] * 1.f/32768.f;
				break;

			case AV_SAMPLE_FMT_S16P:
				for (i=0; i < s->frame->nb_samples; i++)
					for (ic=0; ic < s->frame->channels; ic++)
						(*bufp)[*buf_pos + i*s->frame->channels + ic] = ((int16_t *)s->frame->data[ic])[i] * 1.f/32768.f;
				break;

			case AV_SAMPLE_FMT_S32:
				for (i=0; i < s->frame->nb_samples * s->frame->channels; i++)
					(*bufp)[*buf_pos + i] = ((int32_t *)s->frame->data[0])[i] * 1.f/2147483648.f;
				break;

			case AV_SAMPLE_FMT_S32P:
				for (i=0; i < s->frame->nb_samples; i++)
					for (ic=0; ic < s->frame->channels; ic++)
						(*bufp)[*buf_pos + i*s->frame->channels + ic] = ((int32_t *)s->frame->data[ic])[i] * 1.f/2147483648.f;
				break;

			case AV_SAMPLE_FMT_FLT:
				memcpy(&(*bufp)[*buf_pos], s->frame->data[0], s->frame->nb_samples * s->frame->channels * sizeof(float));
				break;

			case AV_SAMPLE_FMT_FLTP:
				for (i=0; i < s->frame->nb_samples; i++)
					for (ic=0; ic < s->frame->channels; ic++)
						(*bufp)[*buf_pos + i*s->frame->channels + ic] = ((float *)s->frame->data[ic])[i];
				break;

			case AV_SAMPLE_FMT_DBL:
				for (i=0; i < s->frame->nb_samples * s->frame->channels; i++)
					(*bufp)[*buf_pos + i] = ((double *)s->frame->data[0])[i];
				break;

			case AV_SAMPLE_FMT_DBLP:
				for (i=0; i < s->frame->nb_samples; i++)
					for (ic=0; ic < s->frame->channels; ic++)
						(*bufp)[*buf_pos + i*s->frame->channels + ic] = ((double *)s->frame->data[ic])[i];
				break;
		}

		*buf_pos = buf_size;
		return s->frame->nb_samples * s->frame->channels;
	}

	return -1;
}

float *ff_load_audio_fl32_full(const char *path, size_t *sample_count, int *channels, int *samplerate)
{
	int ret=0;
	ffstream_t s={0};
	float *buf=NULL;
	size_t buf_as=0, buf_pos=0;

	while (ret > -1)
	{
		ret = ff_load_audio_fl32(&s, path, 0, NAN, &buf, &buf_as, &buf_pos);

		if (ret > -1)
		{
			*channels = s.frame->channels;
			*samplerate = s.codec_ctx->sample_rate;
		}
	}

	*sample_count = buf_pos / *channels;

	ffstream_close_free(&s);

	return buf;
}

#endif
