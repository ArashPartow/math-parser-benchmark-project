#define STB_VORBIS_NO_STDIO
#define STB_VORBIS_NO_INTEGER_CONVERSION
#define get_bits get_bits_vorbis
#include "orig/stb_vorbis.c"
#undef get_bits

static void convert_channels_float_interleaved(int buf_c, float *buffer, int data_c, float **data, int d_offset, int len)
{
	int i, j;
	int limit = buf_c < data_c ? buf_c : data_c;

	for (j=0; j < len; ++j)
	{
		for (i=0; i < limit; ++i)
			*buffer++ = data[i][d_offset+j];

		for (   ; i < buf_c; ++i)
			*buffer++ = 0.f;
	}
}

int stb_vorbis_get_frame_float_interleaved(stb_vorbis *f, int num_c, float *buffer, int num_floats)
{
	float **output;
	int len;

	len = stb_vorbis_get_frame_float(f, NULL, &output);
	if (len)
	{
		if (len*num_c > num_floats)
			len = num_floats / num_c;

		convert_channels_float_interleaved(num_c, buffer, f->channels, output, 0, len);
	}

	return len;
}

int stb_vorbis_decode_memory_fl32(const uint8 *mem, int len, int *channels, int *sample_rate, float **output)
{
	int data_len, offset, total, limit, error;
	float *data;

	stb_vorbis *v = stb_vorbis_open_memory(mem, len, &error, NULL);
	if (v == NULL)
		return -1;

	limit = v->channels * 4096;
	*channels = v->channels;
	if (sample_rate)
		*sample_rate = v->sample_rate;

	offset = data_len = 0;
	total = limit;

	data = (float *) malloc(total * sizeof(*data));
	if (data == NULL)
	{
		stb_vorbis_close(v);
		return -2;
	}

	for (;;)
	{
		int n = stb_vorbis_get_frame_float_interleaved(v, v->channels, data+offset, total-offset);
		if (n == 0)
			break;

		data_len += n;
		offset += n * v->channels;

		if (offset + limit > total)
		{
			float *data2;
			total *= 2;
			data2 = (float *) realloc(data, total * sizeof(*data));
			if (data2 == NULL)
			{
				free(data);
				stb_vorbis_close(v);
				return -2;
			}

			data = data2;
		}
	}

	*output = data;
	stb_vorbis_close(v);

	return data_len;
}

float *load_sound_vorbis_file(const char *path, size_t *sample_count, int *channels, int *samplerate)
{
	uint8_t *data;
	size_t data_len;
	float *output=NULL;

	*sample_count = 0;
	data = load_raw_file(path, &data_len);
	if (data==NULL)
		return NULL;

	*sample_count = stb_vorbis_decode_memory_fl32(data, data_len, channels, samplerate, &output);
	free(data);

	return output;
}
