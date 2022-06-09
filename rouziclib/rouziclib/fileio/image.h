#define IMAGE_USE_SRGB	1
#define IMAGE_USE_LRGB	2
#define IMAGE_USE_FRGB	4
#define IMAGE_USE_SQRGB	8
#define IMAGE_USE_BUF	16

typedef raster_t (*image_load_mem_func_t)(uint8_t *, size_t, const int);

extern void convert_image_srgb8_fullarg(raster_t *im, const uint8_t *data, const int mode, int free_srgb);
extern void convert_image_srgb16(raster_t *im, const uint16_t *data, const int mode);
extern void convert_image_frgb(raster_t *im, const float *data, const int mode);
extern void convert_image_to_srgb(raster_t im, srgb_t *data);
extern void convert_image_to_frgb(raster_t im, frgb_t *data);
extern void convert_image_to_srgb16(raster_t *im, uint16_t *data, const int mode, const int chan);
extern raster_t load_image_mem_lib(image_load_mem_func_t load_func, uint8_t *raw_data, size_t size, const int mode);
extern raster_t load_image_lib(image_load_mem_func_t load_func, const char *path, const int mode);
extern raster_t load_image_from_http_lib(image_load_mem_func_t load_func, char *url, const int mode);
extern mipmap_t load_mipmap_from_http_lib(image_load_mem_func_t load_func, char *url, const int mode);
extern mipmap_t load_mipmap_lib(image_load_mem_func_t load_func, const char *path, const int mode);
extern raster_t load_image_mem_builtin(uint8_t *raw_data, size_t size, const int mode);
extern raster_t load_file_tiles_to_raster(const char *dir_path, const char *filename_fmt, int x_first, const int mode);
extern int save_image(char *path, raster_t r, int jpg_quality);

#define convert_image_srgb8(im, data, mode)	convert_image_srgb8_fullarg(im, data, mode, 1)

#define load_image(path, mode)			load_image_lib(NULL, path, mode)
#define load_image_from_http(url, mode)		load_image_from_http_lib(NULL, url, mode);
#define load_mipmap_from_http(url, mode)	load_mipmap_from_http_lib(NULL, url, mode);
#define load_mipmap(path, mode)			load_mipmap_lib(NULL, path, mode)

#ifndef load_image_mem
#define load_image_mem	load_image_mem_builtin
#endif
