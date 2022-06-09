#ifdef RL_MINIAUDIO

#define MINIAUDIO_IMPLEMENTATION
#include "orig/miniaudio.h"

int miniaudio_init_wasapi_loopback(void *data_callback, void *user_data)
{
	int ret;
	static ma_device_config dev_cfg;
	static ma_device device;
	ma_backend backends[] = { ma_backend_wasapi };

	dev_cfg = ma_device_config_init(ma_device_type_loopback);
	dev_cfg.capture.pDeviceID = NULL; // Use default device for this example. Set this to the ID of a _playback_ device if you want to capture from a specific device
	dev_cfg.capture.format = ma_format_f32;
	dev_cfg.capture.channels = 2;
	dev_cfg.sampleRate = 0;
	dev_cfg.dataCallback = data_callback;	// callback has the prototype void data_callback(ma_device *ma_dev, void *ma_output, const void *ma_input, uint32_t frame_count)
	dev_cfg.pUserData = user_data;

	ret = ma_device_init_ex(backends, sizeof(backends)/sizeof(backends[0]), NULL, &dev_cfg, &device);
	if (ret != MA_SUCCESS)
	{
		fprintf_rl(stderr, "Failed to initialize loopback device in miniaudio_init_wasapi_loopback().\n");
		return -2;
	}

	ret = ma_device_start(&device);
	if (ret != MA_SUCCESS)
	{
		ma_device_uninit(&device);
		fprintf_rl(stderr, "Failed to start the loopback device in miniaudio_init_wasapi_loopback().\n");
		return -3;
	}

	return device.sampleRate;
}

#endif
