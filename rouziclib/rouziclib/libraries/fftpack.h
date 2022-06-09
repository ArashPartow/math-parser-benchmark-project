#ifndef RL_EXCL_FFTPACK

typedef struct
{
	double *plan, *plan_backup;	// FFT plan and its backup
	int32_t *ifacg;		// FFT factors
	int plan_init;		// whether or not the FFT plan has been initialised
	int fft_size;
	size_t alloc_size;
} fft_plan_t;

extern void fftp(double *in, double *out, int n, int method, fft_plan_t *plan);
extern fft_plan_t alloc_fft_plan(int fft_size, int alloc_size);
extern void free_fft_plan(fft_plan_t *plan);

#endif
