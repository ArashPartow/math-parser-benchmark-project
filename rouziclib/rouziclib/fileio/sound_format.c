int calc_bytes_per_sample_f32(int channel_count)
{
	return channel_count * sizeof(float);
}

int calc_bytes_per_sample_f32_mono(int channel_count)
{
	return sizeof(float);
}

int calc_bytes_per_sample_f32_stereo(int channel_count)
{
	return 2 * sizeof(float);
}

int convert_samples_i16_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count)
{
	int i;
	const float ratio = 1.f/32768.f;

	for (i=0; i < sample_count * channel_count; i++)
		out[i] += in[i] * ratio;

	return channel_count;
}

int convert_samples_f32_to_f32(float *in, float *out, size_t sample_count, int channel_count)
{
	memcpy(out, in, sample_count * channel_count * sizeof(float));

	return channel_count;
}

int convert_samples_i16_to_f32_mono(int16_t *in, float *out, size_t sample_count, int channel_count)
{
	int i, ic;
	float sample;
	float ratio = 1.f/(32768.f * (float) channel_count);

	for (i=0; i < sample_count; i++)
	{
		sample = 0.f;
		for (ic=0; ic < channel_count; ic++)
			sample += in[i*channel_count + ic];

		out[i] = sample * ratio;
	}

	return 1;
}

int convert_samples_f32_to_f32_mono(float *in, float *out, size_t sample_count, int channel_count)
{
	int i, ic;
	float sample;
	float ratio = 1.f/(float) channel_count;

	for (i=0; i < sample_count; i++)
	{
		sample = 0.f;
		for (ic=0; ic < channel_count; ic++)
			sample += in[i*channel_count + ic];

		out[i] = sample * ratio;
	}

	return 1;
}

int convert_samples_i16_sel_chan_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count, int ic)
{
	int i;
	const float ratio = 1.f/32768.f;

	ic = MINN(ic, channel_count-1);

	for (i=0; i < sample_count; i++)
		out[i] = in[i*channel_count + ic] * ratio;

	return 1;
}

int convert_samples_f32_sel_chan_to_f32(float *in, float *out, size_t sample_count, int channel_count, int ic)
{
	int i;

	ic = MINN(ic, channel_count-1);

	for (i=0; i < sample_count; i++)
		out[i] = in[i*channel_count + ic];

	return 1;
}

int convert_samples_i16_left_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count)
{
	return convert_samples_i16_sel_chan_to_f32(in, out, sample_count, channel_count, 0);
}

int convert_samples_i16_right_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count)
{
	return convert_samples_i16_sel_chan_to_f32(in, out, sample_count, channel_count, 1);
}

int convert_samples_f32_left_to_f32(float *in, float *out, size_t sample_count, int channel_count)
{
	return convert_samples_f32_sel_chan_to_f32(in, out, sample_count, channel_count, 0);
}

int convert_samples_f32_right_to_f32(float *in, float *out, size_t sample_count, int channel_count)
{
	return convert_samples_f32_sel_chan_to_f32(in, out, sample_count, channel_count, 1);
}

int convert_samples_i16_to_f32_stereo(int16_t *in, float *out, size_t sample_count, int channel_count)
{
	int i, icr = MINN(1, channel_count-1);
	const float ratio = 1.f/32768.f;

	for (i=0; i < sample_count; i++)
	{
		out[i*2] += in[i*channel_count] * ratio;
		out[i*2+1] += in[i*channel_count + icr] * ratio;
	}

	return 2;
}

int convert_samples_f32_to_f32_stereo(float *in, float *out, size_t sample_count, int channel_count)
{
	int i, icr = MINN(1, channel_count-1);

	for (i=0; i < sample_count; i++)
	{
		out[i*2] += in[i*channel_count];
		out[i*2+1] += in[i*channel_count + icr];
	}

	return 2;
}

float *load_sound_fl32_select_chan(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int sel_chan)
{
	char ext[32];
	float *s0=NULL, *s1;
	int (*bytes_per_sample_func)(int);
	int (*conv_func)(void*,void*,size_t,int);

	*sample_count = 0;
	extract_file_extension(in_path, ext);

	// Load sound file depending on the extension
	if (strcmp(ext, "mp3")==0)
		return load_full_mp3_float_select_chan(in_path, sample_count, channel_count, samplerate, sel_chan);

	if (strcmp(ext, "aif")==0 || strcmp(ext, "aiff")==0 || strcmp(ext, "aifc")==0)
		s0 = load_sound_aiff_file(in_path, sample_count, channel_count, samplerate);

	if (strcmp(ext, "wav")==0 || strcmp(ext, "wave")==0)
		s0 = load_sound_wav_file(in_path, sample_count, channel_count, samplerate);

	if (strcmp(ext, "flac")==0 || strcmp(ext, "fla")==0)
		s0 = load_sound_flac_file(in_path, sample_count, channel_count, samplerate);

	if (strcmp(ext, "ogg")==0 || strcmp(ext, "oga")==0)
		s0 = load_sound_vorbis_file(in_path, sample_count, channel_count, samplerate);

	if (s0==NULL)
		return s0;

	// Convert to the right channel layout
	switch (sel_chan)
	{
		case 0:  bytes_per_sample_func = calc_bytes_per_sample_f32_mono;	conv_func = convert_samples_f32_to_f32_mono;	break;	// averaged mono
		case 1:  bytes_per_sample_func = calc_bytes_per_sample_f32_mono;	conv_func = convert_samples_f32_left_to_f32;	break;	// left channel
		case 2:  bytes_per_sample_func = calc_bytes_per_sample_f32_mono;	conv_func = convert_samples_f32_right_to_f32;	break;	// right channel
		case 3:  bytes_per_sample_func = calc_bytes_per_sample_f32_stereo;	conv_func = convert_samples_f32_to_f32_stereo;	break;	// forced stereo
		default: bytes_per_sample_func = calc_bytes_per_sample_f32;		conv_func = convert_samples_f32_to_f32;		break;	// all channels
	}

	s1 = calloc(*sample_count, bytes_per_sample_func(*channel_count));
	conv_func(s0, s1, *sample_count, *channel_count);
	free(s0);
	*channel_count = bytes_per_sample_func(*channel_count) / sizeof(float);		// new channel count

	return s1;
}

sound_sample_t load_sound_sample(char *in_path, int sel_chan)
{
	sound_sample_t s={0};
	s.snd = load_sound_fl32_select_chan(in_path, &s.sample_count, &s.channels, &s.samplerate, sel_chan);
	s.as = s.sample_count;
	return s;
}

void save_sound_fl32_file(const char *path, float *snd, size_t sample_count, int channels, int samplerate, void *codec_param)
{
	char ext[32];

	extract_file_extension(path, ext);

	if (strcmp(ext, "aif")==0 || strcmp(ext, "aiff")==0 || strcmp(ext, "aifc")==0)
		save_sound_aiff_fl32_file(path, snd, sample_count, channels, samplerate);

	if (strcmp(ext, "wav")==0 || strcmp(ext, "wave")==0)
		save_sound_wav_fl32_file(path, snd, sample_count, channels, samplerate);
}

float *sound_join_channels(float *ch0, float *ch1, size_t len)
{
	size_t i;
	float *s=NULL;

	if (ch0==NULL || ch1==NULL || len==0)
		return s;

	s = calloc(len, 2*sizeof(float));

	for (i=0; i < len; i++)
	{
		s[2*i] = ch0[i];
		s[2*i+1] = ch1[i];
	}

	return s;
}
