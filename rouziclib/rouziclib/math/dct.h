extern double dct_type_II_8x8_coef(xyi_t spatialfreq, xyi_t pos);
extern double dct_type_II_8x8_coef_lut(xyi_t spatialfreq, xyi_t pos);
extern double dct_type_III_8x8_coef(xyi_t spatialfreq, xyi_t pos);
extern double dct_type_II_cell(double *b0, xyi_t ip);
extern double dct_type_III_cell(double *freq_block, xyi_t ip);
extern void dct_type_II_8x8(double *b0, double *b1);
extern void dct_type_III_8x8(double *freq_block, double *space_block);
