#ifdef RL_MPFR

#ifdef _MSC_VER
#pragma comment (lib, "mpfr.lib")	// check if correct
#endif

#include <gmp.h>
#include <mpfr.h>

#define real_t	mpfr_t

#define r_init(x)	mpfr_init_set_d(x, 0., MPFR_RNDN)
#define r_free(x)	mpfr_clear(x)
#define r_set(x,y)	mpfr_set(x, y, MPFR_RNDN)
#define r_setd(x,y)	mpfr_set_d(x, y, MPFR_RNDN)
#define r_abs(x)	mpfr_abs(x, x, MPFR_RNDN)
#define r_add(x,y)	mpfr_add(x, x, y, MPFR_RNDN)
#define r_addd(x,y)	mpfr_add_d(x, x, y, MPFR_RNDN)
#define r_radd(r,x,y)	mpfr_add(r, x, y, MPFR_RNDN)
#define r_sub(x,y)	mpfr_sub(x, x, y, MPFR_RNDN)
#define r_rsub(r,x,y)	mpfr_sub(r, x, y, MPFR_RNDN)
#define r_subd(x,y)	mpfr_sub_d(x, x, y, MPFR_RNDN)
#define r_neg(x)	mpfr_neg(x, x, MPFR_RNDN)
#define r_rneg(r,x)	mpfr_neg(r, x, MPFR_RNDN)
#define r_mul(x,y)	mpfr_mul(x, x, y, MPFR_RNDN)
#define r_rmul(r,x,y)	mpfr_mul(r, x, y, MPFR_RNDN)
#define r_muld(x,y)	mpfr_mul_d(x, x, y, MPFR_RNDN)
#define r_rmuld(r,x,y)	mpfr_mul_d(r, x, y, MPFR_RNDN)
#define r_muli(x,y)	mpfr_mul_si(x, x, y, MPFR_RNDN)
#define r_div(x,y)	mpfr_div(x, x, y, MPFR_RNDN)
#define r_rdiv(r,x,y)	mpfr_div(r, x, y, MPFR_RNDN)
#define r_divd(x,y)	mpfr_div_d(x, x, y, MPFR_RNDN)
#define r_rddiv(r,x,y)	mpfr_d_div(r, x, y, MPFR_RNDN)
#define r_fma(r,x,y,z)	mpfr_fma(r, x, y, z, MPFR_RNDN)
#define r_pow(x,y)	mpfr_pow(x, x, y, MPFR_RNDN)
#define r_rpow(r,x,y)	mpfr_pow(r, x, y, MPFR_RNDN)
#define r_powi(x,y)	mpfr_pow_si(x, x, y, MPFR_RNDN)
#define r_rpowi(r,x,y)	mpfr_pow_si(r, x, y, MPFR_RNDN)
#define r_todouble(x)	mpfr_get_d(x, MPFR_RNDN)
#define r_pi(x)		mpfr_const_pi(x, MPFR_RNDN)
#define r_cos(r,x)	mpfr_cos(r, x, MPFR_RNDN)
#define r_sin(r,x)	mpfr_sin(r, x, MPFR_RNDN)
#define r_sq(r,x)	mpfr_sqr(r, x, MPFR_RNDN)
#define r_sqrt(r,x)	mpfr_sqrt(r, x, MPFR_RNDN)
#define r_exp(r,x)	mpfr_exp(r, x, MPFR_RNDN)
#define r_log(r,x)	mpfr_log(r, x, MPFR_RNDN)
#define r_log2(r,x)	mpfr_log2(r, x, MPFR_RNDN)
#define r_log10(r,x)	mpfr_log10(r, x, MPFR_RNDN)
#define r_exp10(r,x)	mpfr_exp10(r, x, MPFR_RNDN)
#define r_erf(r,x)	mpfr_erf(r, x, MPFR_RNDN)

extern real_t *r_init_array(int count);
extern void r_zero_array(real_t *a, int count);
extern void r_free_array(real_t **a, int count);
extern void r_flipsign(real_t y, real_t x);
extern void r_gaussian(real_t y, real_t x);
extern void r_mix(real_t x, double t, real_t start, real_t end);
extern ddouble_t mpfr_to_ddouble(real_t v);
extern void ddouble_to_mpfr(real_t r, ddouble_t v);
extern double diff_mpfr_ddouble(real_t m, ddouble_t q);

#else

#define real_t double

#endif
