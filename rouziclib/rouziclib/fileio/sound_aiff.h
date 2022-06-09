extern float *load_sound_aiff_mem(const uint8_t *data, size_t data_len, size_t *sample_count, int *channels, int *samplerate);
extern float *load_sound_aiff_file(const char *path, size_t *sample_count, int *channels, int *samplerate);
extern void save_sound_aiff_fl32_file(const char *path, float *snd, size_t sample_count, int channels, int samplerate);
