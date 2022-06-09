#ifdef RL_MINIAUDIO

#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_GENERATION
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#define MA_ENABLE_WASAPI
#include "orig/miniaudio.h"

extern int miniaudio_init_wasapi_loopback(void *data_callback, void *user_data);

#endif
