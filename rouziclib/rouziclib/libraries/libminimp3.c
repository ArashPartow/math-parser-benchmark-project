#define MINIMP3_FLOAT_OUTPUT
#define MINIMP3_ONLY_MP3
#define MINIMP3_IMPLEMENTATION
#define get_bits get_bits_minimp3
#include "orig/minimp3.h"
#undef get_bits

void *load_full_mp3_fullarg(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int (*bytes_per_sample_func)(int), int (*conv_func)(void*,void*,size_t,int))
{
	uint8_t *raw_data;
	size_t data_size, raw_index=0;
	int frame_sample_count, conv_channel_count=0;
	uint8_t *out=NULL, *p;
	size_t out_count=0, out_as=0, out_start=0;
	int out_size_elem=-1;

	mp3dec_t mp3d;
	mp3dec_frame_info_t info;
	float pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];

	*sample_count = 0;
	raw_data = load_raw_file(in_path, &data_size);
	if (raw_data==NULL)
		return NULL;

	mp3dec_init(&mp3d);

	do
	{
		frame_sample_count = mp3dec_decode_frame(&mp3d, &raw_data[raw_index], data_size - raw_index, pcm, &info);
		raw_index += info.frame_bytes;

		if (raw_index == info.frame_bytes)	// if it's the first decoded frame
		{
			if (raw_index==0)				// if the first frame is empty
				return NULL;

			*channel_count = info.channels;
			*samplerate = info.hz;
			out_size_elem = bytes_per_sample_func(*channel_count);
		}

		if (frame_sample_count)
		{
			alloc_enough(&out, out_count+=frame_sample_count, &out_as, out_size_elem, 1.5);
			conv_channel_count = conv_func(pcm, &out[out_size_elem*out_start], frame_sample_count, *channel_count);
			out_start = out_count;
		}
	}
	while (info.frame_bytes);

	free(raw_data);
	*channel_count = conv_channel_count;

	*sample_count = out_count;
	p = realloc(out, out_count * out_size_elem);	// trim the allocation of out
	return p ? p : out;
}

float *load_full_mp3_float_select_chan(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int sel_chan)
{
	switch (sel_chan)
	{
		case 0:  return load_full_mp3_fullarg(in_path, sample_count, channel_count, samplerate, calc_bytes_per_sample_f32_mono, convert_samples_f32_to_f32_mono);	// averaged mono
		case 1:  return load_full_mp3_fullarg(in_path, sample_count, channel_count, samplerate, calc_bytes_per_sample_f32_mono, convert_samples_f32_left_to_f32);	// left channel
		case 2:  return load_full_mp3_fullarg(in_path, sample_count, channel_count, samplerate, calc_bytes_per_sample_f32_mono, convert_samples_f32_right_to_f32);	// right channel
		case 3:  return load_full_mp3_fullarg(in_path, sample_count, channel_count, samplerate, calc_bytes_per_sample_f32_stereo, convert_samples_f32_to_f32_stereo);	// forced stereo
		default: return load_full_mp3_fullarg(in_path, sample_count, channel_count, samplerate, calc_bytes_per_sample_f32, convert_samples_f32_to_f32);			// all channels
	}
}
