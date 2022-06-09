extern raster_t load_image_mem_libstb_image(uint8_t *raw_data, size_t size, const int mode);
extern int save_image_srgb_libstb(const char *path, raster_t r, int jpg_quality);

#ifndef load_image_mem
#define load_image_mem	load_image_mem_libstb_image
#endif

#ifndef save_image_srgb
#define save_image_srgb	save_image_srgb_libstb
#endif
