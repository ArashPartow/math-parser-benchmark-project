#ifdef RL_FFMPEG

typedef struct
{
	int used;
	float *buffer;
	int len, as;
	ffframe_info_t info;
	int channels, sample_count;
	double samplerate;
} audframe_t;

typedef struct
{
	volatile int thread_on;
	int init;
	char *path;
	ffstream_t *stream;
	rl_mutex_t mutex;
	rl_thread_t thread_handle;
	audframe_t *frame;
	int frame_as;
	volatile double ts_req, speed, volume, vol0, vol1, ts_cb;
	double duration;
	double time_offset;	// offset to convert between callback sample time and timestamp
	int ifr, is;	// frame index and sample index in that frame
} audio_player_data_t;

extern void audio_player_main(audio_player_data_t *data, char *path, double ts_req, double speed, double volume);
extern void audio_player_callback(float *stream, audiosys_t *sys, int bus_index, audio_player_data_t *data);

#endif
