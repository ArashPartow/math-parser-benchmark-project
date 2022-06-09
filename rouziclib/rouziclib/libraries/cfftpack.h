#ifndef RL_EXCL_CFFTPACK

typedef struct
{
	float *savef, *workf;
	double *saved, *workd;
	int lensav, lenwork, scale;
	size_t elemsize;
	xyi_t dim;
} cfft_plan_t;

extern void cfft_plan_free(cfft_plan_t *plan);
extern cfft_plan_t cfft_1D_create_plan(int n, const size_t elemsize);
extern cfft_plan_t cfft_2D_create_plan(xyi_t dim, const size_t elemsize);
extern int cfft_1D(cfft_plan_t *plan, void *data, const int way);
extern int cfft_2D(cfft_plan_t *plan, void *data, const int way);

extern void cfft_complex_mul_2D_f(void *va, void *vb, void *vr, xyi_t dim);
extern void cfft_complex_mul_2D_d(void *va, void *vb, void *vr, xyi_t dim);
extern void cfft_copy_r2c_pad(void *in, const size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, xyi_t in_dim, xyi_t out_dim);
extern void cfft_copy_c2r(void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, xyi_t dim);
extern void cfft_1D_c2c_fft(cfft_plan_t *plan, void *array, const size_t elemsize, int n);
extern void cfft_1D_r2c_padded_fft(cfft_plan_t *plan, void *in, size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, int in_n, int out_n);
extern void cfft_2D_r2c_padded_fft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, xyi_t in_dim, xyi_t out_dim);
extern void cfft_1D_c2r_full_ifft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, int n);
extern void cfft_2D_c2r_full_ifft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, xyi_t dim);

#endif
