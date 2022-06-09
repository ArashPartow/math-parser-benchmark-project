extern void *load_full_mp3_fullarg(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int (*bytes_per_sample_func)(int), int (*conv_func)(void*,void*,size_t,int));
extern float *load_full_mp3_float_select_chan(char *in_path, size_t *sample_count, int *channel_count, int *samplerate, int sel_chan);
