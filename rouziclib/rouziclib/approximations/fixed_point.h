extern int32_t fastabs(int32_t x);
extern int64_t fastabs64(int64_t x);

#define fpdiv	fpdiv_d2
#define isqrt	isqrt_d1i
#define fplog2	fplog2_d1i
#define fpexp2	fpexp2_d1i
#define fpcos	fpcos_d2
#define fpatan2	fpatan2_d2
#define fpwsinc	fpwsinc_d1i
#define fpgauss	fpgauss_d0
#define fperfr	fperfr_d0

#define fpsin(x) fpcos((x)+0xC0000000)
#define fpsin_d2(x) fpcos_d2((x)+0xC0000000)
#define fpsin_d1i(x) fpcos_d1i((x)+0xC0000000)

#ifndef RL_EXCL_APPROX

extern int32_t log2_ffo32(uint32_t x);
extern int32_t log2_ffo64(uint64_t x);
extern int64_t mulshift (int64_t a, int64_t b, int s);

extern int64_t fpdiv_d2(int32_t y, int32_t x, int32_t outfmt);
extern uint32_t isqrt_d1i(uint64_t x);
extern int32_t fplog2_d1i(uint32_t x);
extern uint32_t fpexp2_d1i(int32_t x);
extern int32_t fppow(uint32_t x, int32_t y, const uint32_t fmt);

extern int32_t fpcos_d2(uint32_t x);
extern int32_t fpcos_d1i(uint32_t x);
extern int64_t fpatan2_d2(int32_t y, int32_t x);
extern int32_t fpwsinc_d1i(int32_t x);
extern int32_t fpgauss_d1i(int32_t x);
extern int32_t fpgauss_d0(int32_t x);
extern int32_t fpgauss_d0_nocheck(int32_t x);
extern int32_t fperfr_d1i(int32_t x);
extern int32_t fperfr_d0(int32_t x);

#else

#define log2_ffo32(x)		noop_i("log2_ffo32(x)")
#define log2_ffo64(x)		noop_i("log2_ffo64(x)")
#define mulshift(a, b, s)	noop_i("mulshift(a, b, s)")
#define fpdiv_d2(y, x, outfmt)	noop_i("fpdiv_d2(y, x, outfmt)")
#define isqrt_d1i(x)		noop_i("isqrt_d1i(x)")
#define fplog2_d1i(x)		noop_i("fplog2_d1i(x)")
#define fpexp2_d1i(x)		noop_i("fpexp2_d1i(x)")
#define fppow(x, y, fmt)	noop_i("fppow(x, y, fmt)")
#define fpcos_d2(x)		noop_i("fpcos_d2(x)")
#define fpcos_d1i(x)		noop_i("fpcos_d1i(x)")
#define fpatan2_d2(y, x)	noop_i("fpatan2_d2(y, x)")
#define fpwsinc_d1i(x)		noop_i("fpwsinc_d1i(x)")
#define fpgauss_d1i(x)		noop_i("fpgauss_d1i(x)")
#define fpgauss_d0(x)		noop_i("fpgauss_d0(x)")
#define fpgauss_d0_nocheck(x)	noop_i("fpgauss_d0_nocheck(x)")
#define fperfr_d1i(x)		noop_i("fperfr_d1i(x)")
#define fperfr_d0(x)		noop_i("fperfr_d0(x)")

#endif
