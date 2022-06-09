typedef void (*audiosys_bus_callback_t)(float*,void*,int,void*);

typedef struct
{
	int on;
	audiosys_bus_callback_t callback;
	void *data;
	rl_mutex_t mutex;
	int use_mutex;
	double expiry_dur, last_reg_time, stime;
} audiosys_bus_t;

typedef struct
{
	double samplerate;
	int buffer_len;
	double sec_per_buf, sec_per_sample;
	int device_id;

	audiosys_bus_t *bus;
	int bus_count, bus_as;
	rl_mutex_t mutex;
} audiosys_t;

extern void audiosys_callback(void *userdata, uint8_t *stream, int stream_bytes);
extern int audiosys_bus_register(audiosys_bus_callback_t bus_callback, void *bus_data, int use_mutex, double expiry_dur);
extern void audiosys_bus_unregister(void *bus_data);
extern void sdl_audiosys_init(int def_buflen);
