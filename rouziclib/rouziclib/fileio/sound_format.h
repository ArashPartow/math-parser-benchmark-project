typedef struct
{
	float *snd;
	size_t sample_count, as;
	int channels, samplerate;
} sound_sample_t;

extern int calc_bytes_per_sample_f32(int channel_count);
extern int calc_bytes_per_sample_f32_mono(int channel_count);
extern int calc_bytes_per_sample_f32_stereo(int channel_count);

extern int convert_samples_i16_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_f32_to_f32(float *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_i16_to_f32_mono(int16_t *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_f32_to_f32_mono(float *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_i16_left_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_i16_right_to_f32(int16_t *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_f32_left_to_f32(float *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_f32_right_to_f32(float *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_i16_to_f32_stereo(int16_t *in, float *out, size_t sample_count, int channel_count);
extern int convert_samples_f32_to_f32_stereo(float *in, float *out, size_t sample_count, int channel_count);

extern float *load_sound_fl32_select_chan(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int sel_chan);
extern sound_sample_t load_sound_sample(char *in_path, int sel_chan);
extern void save_sound_fl32_file(const char *path, float *snd, size_t sample_count, int channels, int samplerate, void *codec_param);
extern float *sound_join_channels(float *ch0, float *ch1, size_t len);
