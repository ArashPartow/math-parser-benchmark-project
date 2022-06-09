#ifdef RL_OPENCL
#ifdef RL_CLFFT

#ifdef _MSC_VER
#pragma comment (lib, "delayimp.lib")	// for delay-loading of the DLL
#pragma comment (lib, "clfft.lib")
#endif

#define __inline static
#include <clFFT.h>
#undef __inline

typedef struct
{
	xyi_t fft_dim;
	clfftPlanHandle planid;
	cl_mem gpu_buf, tmp_buf;
} clfft_plan_t;

extern void print_clfft_version();
extern void clfft_setup(const int new_state);
extern void clfft_create_tmpbuf(clctx_t *clctx, clfftPlanHandle planid, cl_mem *tmp_buf);
extern void clfft_make_plan_1d(clctx_t *clctx, clfftPlanHandle *planid, int fft_size, int prec, int layout_in, int layout_out, int location, cl_mem *tmp_buf);
extern void clfft_make_plan_2d(clctx_t *clctx, clfft_plan_t *plan, xyi_t fft_dim, int prec, int layout_in, int layout_out, int location);
extern void clfft_free_plan(clfft_plan_t *plan);
extern void clfft_update_plan_2d(clctx_t *clctx, clfft_plan_t *plan, xyi_t fft_dim);
extern void clfft_2d(clctx_t *clctx, clfft_plan_t *plan, float *cpu_buf, xyi_t dim, int direction);
extern void clfft_1d_selfcontained(clctx_t *clctx, cl_mem in, cl_mem out, const int direction, const int fft_size);
extern void clfft_1d_selfcontained_local(clctx_t *clctx, float *in, float *out, const int direction, const int fft_size);

#endif
#endif
