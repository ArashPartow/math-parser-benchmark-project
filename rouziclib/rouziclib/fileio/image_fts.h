extern int is_file_fts_mem(uint8_t *data);
extern double fts_read_double(uint8_t *data, const char *field_name);
extern int fts_read_int(uint8_t *data, const char *field_name);
extern float *load_fts_mem(uint8_t *data, const size_t data_size, xyi_t *dim, int *out_chan);
extern raster_t load_fts_mem_raster(uint8_t *data, const size_t data_size);
