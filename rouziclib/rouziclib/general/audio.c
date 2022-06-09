void audiosys_callback(void *userdata, uint8_t *stream, int stream_bytes)
{
	int ib;
	audiosys_t *sys = (audiosys_t *) userdata;
	double now = get_time_hr();

	memset(stream, 0, stream_bytes);

	rl_mutex_lock(&sys->mutex);

	for (ib=0; ib < sys->bus_count; ib++)
	{
		// Check expiry
		if (sys->bus[ib].on)
			if (now - sys->bus[ib].last_reg_time > sys->bus[ib].expiry_dur)
			{
				sys->bus[ib].on = 0;
				sys->bus[ib].callback(NULL, sys, ib, sys->bus[ib].data);	// deinitialisation signal to the callback (non-blocking)
			}

		if (sys->bus[ib].on)
		{
			// Lock mutex
			if (sys->bus[ib].use_mutex)
				rl_mutex_lock(&sys->bus[ib].mutex);

			// Resync stime (sample time) if needed
			if (sys->bus[ib].stime==0. || sys->bus[ib].stime + sys->sec_per_buf*2. < sys->bus[ib].last_reg_time)
			{
				if (sys->bus[ib].stime > 0)
					fprintf_rl(stdout, "audiosys_callback() resync: was off by %.5f sec\n", sys->bus[ib].stime - (sys->bus[ib].last_reg_time - sys->sec_per_buf));
				sys->bus[ib].stime = sys->bus[ib].last_reg_time - sys->sec_per_buf;
			}

			// Call the function
			sys->bus[ib].callback((float *) stream, sys, ib, sys->bus[ib].data);

			sys->bus[ib].stime += sys->sec_per_buf;

			// Unlock mutex
			if (sys->bus[ib].use_mutex)
				rl_mutex_unlock(&sys->bus[ib].mutex);
		}
	}

	rl_mutex_unlock(&sys->mutex);
}

int audiosys_bus_register(audiosys_bus_callback_t bus_callback, void *bus_data, int use_mutex, double expiry_dur)
{
	int ib;

	// Check if the bus is already registered
	for (ib=0; ib < audiosys.bus_count; ib++)
	{
		if (audiosys.bus[ib].data == bus_data)
		{
			audiosys.bus[ib].on = 1;
			audiosys.bus[ib].last_reg_time = get_time_hr();
			return ib;
		}
	}

	rl_mutex_lock(&audiosys.mutex);

	// Add new bus
	ib = audiosys.bus_count;
	alloc_enough(&audiosys.bus, audiosys.bus_count+=1, &audiosys.bus_as, sizeof(audiosys_bus_t), 2.);

	audiosys.bus[ib].on = 1;
	audiosys.bus[ib].callback = bus_callback;
	audiosys.bus[ib].data = bus_data;
	audiosys.bus[ib].use_mutex = use_mutex;
	if (use_mutex)
		rl_mutex_init(&audiosys.bus[ib].mutex);
	audiosys.bus[ib].expiry_dur = expiry_dur==0. ? 2. : expiry_dur;
	audiosys.bus[ib].last_reg_time = get_time_hr();

	rl_mutex_unlock(&audiosys.mutex);

	return ib;
}

void audiosys_bus_unregister(void *bus_data)
{
	int ib;

	rl_mutex_lock(&audiosys.mutex);

	// Find the bus and erase it
	for (ib=0; ib < audiosys.bus_count; ib++)
	{
		if (audiosys.bus[ib].data == bus_data)
		{
			// Deinit mutex
			if (audiosys.bus[ib].use_mutex)
				rl_mutex_destroy(&audiosys.bus[ib].mutex);

			// Deinit signal to the callback (blocking)
			audiosys.bus[ib].callback(NULL, &audiosys, -1, audiosys.bus[ib].data);

			// Remove bus from bus array
			memset(&audiosys.bus[ib], 0, sizeof(audiosys_bus_t));
			if (ib == audiosys.bus_count-1)
				audiosys.bus_count--;
			break;
		}
	}

	rl_mutex_unlock(&audiosys.mutex);
}

void sdl_audiosys_init(int def_buflen)
{
#ifdef RL_SDL
	SDL_AudioSpec audio_format={0}, obtained={0};
	int i, driver_index=0, device_index=0;
	const char *driver_name=NULL, *device_name=NULL;

	// Pick the default driver
	for (i=0; i < SDL_GetNumAudioDrivers(); i++)
		if (strcmp("wasapi", SDL_GetAudioDriver(i)))	// if the driver isn't called "wasapi"
		{
			driver_index = i;
			break;
		}

	// Load preferred driver name from pref file
	if (pref_def.path)
		driver_name = pref_get_string(&pref_def, "Audio output:Preferred driver", SDL_GetAudioDriver(driver_index));

	for (i=0; i < SDL_GetNumAudioDrivers(); i++)
		if (strstr_i(SDL_GetAudioDriver(i), driver_name))
		{
			driver_index = i;
			break;
		}

	// Init the driver
	SDL_AudioQuit();					// quit the current audio driver
	SDL_AudioInit(SDL_GetAudioDriver(driver_index));	// initialise it

	// Load preferred output device name from pref file
	if (pref_def.path)
		device_name = pref_get_string(&pref_def, "Audio output:Preferred device", SDL_GetAudioDeviceName(device_index, 0));

	for (i=0; i < SDL_GetNumAudioDevices(0); i++)
		if (strstr_i(SDL_GetAudioDeviceName(i, 0), device_name))
		{
			device_index = i;
			break;
		}

	// Init the output device
	audio_format.freq = pref_get_double(&pref_def, "Audio output:Sample rate", 44100, " Hz");
	audio_format.format = AUDIO_F32;
	audio_format.channels = 2;
	audio_format.samples = pref_get_double(&pref_def, "Audio output:Buffer length", def_buflen ? def_buflen : audio_format.freq/50, " samples");
	audio_format.callback = audiosys_callback;
	audio_format.userdata = &audiosys;
	rl_mutex_init(&audiosys.mutex);

	audiosys.device_id = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(device_index, 0), 0, &audio_format, &obtained, 0);

	if (audio_format.format!=obtained.format)
		fprintf_rl(stderr, "sdl_audio_init(): sdlaudioformat.format > wanted : %6x\tobtained : %6x\n", audio_format.format, obtained.format);
	if (audio_format.channels!=obtained.channels)
		fprintf_rl(stderr, "sdl_audio_init(): sdlaudioformat.channels > wanted : %6d\tobtained : %6d\n", audio_format.channels, obtained.channels);

	audiosys.buffer_len = obtained.samples;
	audiosys.samplerate = obtained.freq;
	if (pref_def.path)
		pref_set_double(&pref_def, "Audio output:Buffer length", audiosys.buffer_len, " samples");

	audiosys.sec_per_buf = (double) audiosys.buffer_len / audiosys.samplerate;
	audiosys.sec_per_sample = 1. / audiosys.samplerate;

	SDL_PauseAudioDevice(audiosys.device_id, 0);
#endif
}
