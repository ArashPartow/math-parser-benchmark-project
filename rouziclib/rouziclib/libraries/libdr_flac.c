#define DR_FLAC_IMPLEMENTATION
#define DR_FLAC_NO_STDIO
#include "orig/dr_flac.h"

float *load_sound_flac_file(const char *path, size_t *sample_count, int *channels, int *samplerate)
{
	uint64_t total_sample_count=0;

	buffer_t data = buf_load_raw_file(path);
	float *snd = drflac_open_memory_and_read_pcm_frames_f32(data.buf, data.len, channels, samplerate, &total_sample_count, NULL);
	free_buf(&data);

	*sample_count = total_sample_count / *channels;

	return snd;
}
