#ifdef RL_LIBJPEG

#ifdef _MSC_VER
#pragma comment (lib, "jpeg.lib")
#endif

#include <jpeglib.h>
#include <setjmp.h>

typedef struct
{
	xyi_t image_dim, block_dim;	// number of end pixels and blocks
	uint16_t quant[64];	// 8x8 quantisation table
	int16_t **dct_block;	// array of DCT blocks, each block an 8x8 DCT coef table
} jpeg_comp_dct_t;

extern jpeg_comp_dct_t *libjpeg_get_dct_data(const char *filepath);
extern void free_jpeg_comp_dct(jpeg_comp_dct_t *data);
extern void copy_convert_8x8_block(float *im, xyi_t dim, xyi_t ib, double *block);
extern void paste_convert_8x8_block(float *im, xyi_t dim, xyi_t ib, double *block);
extern raster_t load_image_mem_libjpeg(uint8_t *raw_data, size_t size, const int mode);

#ifndef load_image_mem
#define load_image_mem	load_image_mem_libjpeg
#endif

#endif

extern int check_data_is_jpeg(uint8_t *raw_data, size_t size);
extern raster_t load_image_mem_libjpeg_if_possible(uint8_t *raw_data, size_t size, const int mode);
