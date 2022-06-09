extern int noop_i(const char *function_name);
extern float noop_f(const char *function_name);
extern raster_t noop_raster(const char *function_name);

#ifndef load_image
#define load_image_from_memory(raw_data, size, mode)	noop_raster("load_image_from_memory")
#define load_image(in_path, mode)			noop_raster("load_image")
#endif
