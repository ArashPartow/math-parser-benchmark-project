typedef struct
{
	xyi_t dim;
	int be, chan, bpc;	// big endian, channel count, bits per channel
	int compression;	// 1 for uncompressed
	int photometric;	// 2 for RGB(A)
	int sample_format;	// 1 for uint, 2 for int, 3 for float
	int lzw_diff;		// 1 for no difference, 2 for horizontal difference
	uint32_t *data_offset;	// points to the strip offsets
	int offset_count;	// number of strip offsets
	int rowsperstrip, planarconfig;
	int bytesperstrip;	// number of decoded bytes per strip
} tiff_info_t;

extern int is_file_tiff_mem(uint8_t *data);
extern raster_t load_tiff_mem_raster(uint8_t *data);
extern float *load_tiff_file(const char *path, xyi_t *dim, int *out_chan);
extern void *load_tiff_file_raw(const char *path, tiff_info_t *info);
extern raster_t load_tiff_file_raster(const char *path);
extern int save_image_tiff(const char *path, float *im, xyi_t dim, int in_chan, int out_chan, int bpc);
