/*
	Summary of the main trigonometry functions:

			approx	builtin		LUT	builtin
			speed	speed	error	size	equivalent
			----------------------------------------------------------------------------------------------------------
	fastlog2(x)	~13	~49	7.1e-9	3 kB	log2(x), except fastlog2(x) never returns a NaN or inf
	fastexp2(x)	~31	~205	6.7e-9	1.5 kB	exp2(x), only valid if x = [-1022.0 , 1024.0[
	fastpow(x,y)	~63	~450	2.6e-8		pow(x,y), returns bogus results instead of NaNs or inf
	fastsqrt(x)	~21.5	~12.5	9e-10	3 kB	sqrt(x), disregards the sign of x
 */

float polynomial_from_lutf(const float *lut, const int lutind, const int order, const float x)
{
	const float *c;

	switch (order)
	{
		case 0:
			return lut[lutind];

		case 1:
			c = &lut[lutind<<1];
			return c[1]*x + c[0];

		case 2:
			c = &lut[lutind*3];
			return (c[2]*x + c[1])*x + c[0];

		case 3:
			c = &lut[lutind<<2];
			return (((c[3])*x + c[2])*x + c[1])*x + c[0];

		case 4:
			c = &lut[lutind*5];
			return (((c[4]*x + c[3])*x + c[2])*x + c[1])*x + c[0];

		case 5:
			c = &lut[lutind*6];
			return ((((c[5]*x + c[4])*x + c[3])*x + c[2])*x + c[1])*x + c[0];

		case 6:
			c = &lut[lutind*7];
			return (((((c[6]*x + c[5])*x + c[4])*x + c[3])*x + c[2])*x + c[1])*x + c[0];
	}

	return NAN;
}

double polynomial_from_lut(const double *lut, const int lutind, const int order, const double x)
{
	const double *c;

	switch (order)
	{
		case 0:
			return lut[lutind];

		case 1:
			c = &lut[lutind<<1];
			return c[1]*x + c[0];

		case 2:
			c = &lut[lutind*3];
			return (c[2]*x + c[1])*x + c[0];

		case 3:
			c = &lut[lutind<<2];
			return (((c[3])*x + c[2])*x + c[1])*x + c[0];

		case 4:
			c = &lut[lutind*5];
			return (((c[4]*x + c[3])*x + c[2])*x + c[1])*x + c[0];

		case 5:
			c = &lut[lutind*6];
			return ((((c[5]*x + c[4])*x + c[3])*x + c[2])*x + c[1])*x + c[0];

		case 6:
			c = &lut[lutind*7];
			return (((((c[6]*x + c[5])*x + c[4])*x + c[3])*x + c[2])*x + c[1])*x + c[0];
	}

	return NAN;
}

#ifndef RL_EXCL_APPROX

// log2 approximation, returns slightly bogus values for 0, subnormals, inf and NaNs, returns the real value only for negative x
// max error of 7.098e-09 for lutsp of 7, lut takes 3 kB
double fastlog2(double x)
{
	static const double lut[] = 
	#include "tables/fastlog2.h"
	uint64_t xint, m, m1int;
	double m1, mlog;
	int32_t exp, lutind;
	const int64_t ish = 52-lutsp;		// index shift
	const double *c;
	double c0, c1, c2;

	xint = *((uint64_t *) &x);
	exp = (xint & 0x7FF0000000000000) >> 52;	// exponent mask and shift

	exp -= 1023;			// exponent offset compensation

	m = xint & 0x000FFFFFFFFFFFFF;	// 52-bit mantissa
	m1int = 0x3FF0000000000000 | m;	// 1.0 + mantissa
	m1 = *((double *) &m1int);	// m1 = [1.0 , 2.0[

	lutind = m >> ish;

	c = &lut[lutind*3];    c0 = c[0];    c1 = c[1];    c2 = c[2];
	mlog = (c2*m1 + c1)*m1 + c0;	// logarithm of the mantissa

	return (double) exp + mlog;
}

// exp2 approximation, returns bogus results if x is outside [-1022.0 , 1024.0[
// max error of 6.65255e-09 for lutsp of 6, lut takes 1.5 kB
#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
double fastexp2(double x)
{
	static const double lut[] = 
	#include "tables/fastexp2.h"
	double xr, xf, xf1, y, xfe;
	int32_t exp, lutind;
	const int64_t ish = 52-lutsp;		// index shift
	uint64_t yint, m;
	const double *c;

	#ifdef RL_INTEL_INTR				// for MSVC only needed if compiling without /arch:AVX
	__m128d mx = _mm_set_sd(x);
	xr = _mm_cvtsd_f64(_mm_floor_sd(mx, mx));	// SSE4.1, not checking for speed
	#else
	xr = floor(x);		// integer part of x
	#endif
	xf = x - xr;		// fractional part of x. xf = [0.0 , 1.0[
	xf1 = xf + 1.;

	exp = xr;
	exp += 1023;	// IEEE-754 exponent. Will be bogus if x < -1022 or x >= 1024

	yint = (uint64_t) exp << 52;			// put the exponent in the final result
	y = *((double *) &yint);			// now y = 2^xr

	m = *((uint64_t *) &xf1) & 0x000FFFFFFFFFFFFF;	// 52-bit mantissa of the fractional part
	lutind = m >> ish;

	c = &lut[lutind*3];
	xfe = (c[2]*xf + c[1])*xf + c[0];		// 2^xf

	return y * xfe;					// y = 2^xr * 2^xf
}

// max error is 2.627e-08
double fastpow(double x, double y)
{
	return fastexp2(fastlog2(x) * y);
}

// Oops, it's actually slower than sqrt(x)
double fastsqrt(double x)
{
	static const double lut[] = 
	#include "tables/fastsqrt.h"
	uint64_t xint, m, m1int, explsbint;
	double m1, ms, expmul, es;
	int32_t lutind;
	int64_t exp;
	const double ec = sqrt(0.5) - 0.5;
	const int64_t ish = 52-lutsp;		// index shift
	const double *c;
	double c0, c1, c2;

	xint = *((uint64_t *) &x);
	exp = (xint & 0x7FF0000000000000) >> 52;	// exponent mask and shift
	exp -= 1023;					// exponent offset compensation

	explsbint = (exp & 0x1) << 62;		// least significant bit of the exponent promoted to most significant bit
	expmul = *((double *) &explsbint);	// expmul is now either 0.0 or 2.0
	expmul = 1. + expmul * ec;		// expmul is now either 1.0 or 1.4142...

	exp >>= 1;			// exponent of the sqrt of x is half the exponent of x
	exp += 1023;			// exponent offset compensation
	exp <<= 52;			// put the exponent back in its IEEE double place
	es = *((double *) &exp);	// sqrt of the exponent

	m = xint & 0x000FFFFFFFFFFFFF;	// 52-bit mantissa
	m1int = 0x3FF0000000000000 | m;	// 1.0 + mantissa
	m1 = *((double *) &m1int);	// m1 = [1.0 , 2.0[

	lutind = m >> ish;

	c = &lut[lutind*3];    c0 = c[0];    c1 = c[1];    c2 = c[2];
	ms = (c2*m1 + c1)*m1 + c0;	// sqrt of the mantissa

	return es * expmul * ms;
}

float fast_lsrgbf(float x)
{
	static const float lut[] = 
	#include "tables/fastlsrgb.h"		// 396 bytes, contains order, ish
	const float offset = 0.0031308f;
	uint32_t lutind;

	x = rangelimitf(x, 0.f, 1.f);

	lutind = float_as_u32(x + offset) - float_as_u32(offset) >> ish;

	return polynomial_from_lutf(lut, lutind, order, x);
}

float fastgaussianf_d0(float x)
{
	#include "tables/fastgauss_d0.h"	// contains the LUT, offset and limit
	uint32_t index, *xint = (uint32_t *) &x;

	*xint &= 0x7FFFFFFF;		// x = |x|

	if (x > limit)			// if x isn't represented in the LUT
		return 0.f;

	x += offset;			// turns the mantissa into an integer suitable as a LUT index
	index = *xint & 0x007FFFFF;	// keeps mantissa
	return fastgauss_lut[index];
}

float fastgaussianf_d1(float x)
{
	#include "tables/fastgauss_d1.h"	// contains the LUT, offset and limit
	uint32_t index, *xint = (uint32_t *) &x;
	float xa;
	const float *c;

	*xint &= 0x7FFFFFFF;		// x = |x|
	xa = x;

	if (x > limit)			// if x isn't represented in the LUT
		return 0.f;

	x += offset;			// turns the mantissa into an integer suitable as a LUT index
	index = *xint & 0x007FFFFE;	// keeps mantissa
	c = &fastgauss_lut[index];
	return c[1]*xa + c[0];
}

float fasterfrf_d0(float x)
{
	#include "tables/fasterfr_d0.h"	// contains the LUT, offset and limit
	uint32_t index, *xint = (uint32_t *) &x;

	if (x > limit)			// if x isn't represented in the LUT
		return 1.f;
	if (x < -limit)			// if x isn't represented in the LUT
		return 0.f;

	x += offset;			// turns the mantissa into an integer suitable as a LUT index
	index = *xint & 0x007FFFFF;	// keeps mantissa
	return fasterfr_lut[index];
}

float fasterfrf_d1(float x)
{
	#include "tables/fasterfr_d1.h"	// contains the LUT, offset and limit
	uint32_t index, *xint = (uint32_t *) &x;
	float xa;
	const float *c;

	if (x > limit)			// if x isn't represented in the LUT
		return 1.f;
	if (x < -limit)			// if x isn't represented in the LUT
		return 0.f;

	xa = x;

	x += offset;			// turns the mantissa into an integer suitable as a LUT index
	index = *xint & 0x007FFFFE;	// keeps mantissa
	c = &fasterfr_lut[index];
	return c[1]*xa + c[0];
}

// The following functions just wrap to the matching fixed-point function
double fastatan2(double y, double x)	// as it is the caller must provide numbers large enough to be treated as integers
{
	double th;
	int32_t xi, yi;
	const double convratio = 2.*3.1415926535897932 / 4294967296.;

	xi = roundaway(x);
	yi = roundaway(y);

	th = fpatan2_d2(yi, xi);
	th *= convratio;

	return th;
}

double fastexp_limited(double x)	// max error of 1/11039 for x <= 0
{
	static const double lut[] = 
	#include "tables/fastexp_limited.h"		// 552 bytes, contains order, ish, offset, end
	uint32_t lutind;

	if (x > 0.)
	{
		static int init=1;
		if (init)
		{
			init = 0;
			fprintf_rl(stderr, "fastexp_limited() doesn't take positive values\n");
		}
		return NAN;
	}

	x = -x;		// the lut approximation is actually for exp(-x)

	if (x > end)
		return 0.;

	lutind = (double_as_u64(x + offset) - double_as_u64(offset)) >> ish;

	return polynomial_from_lut(lut, lutind, order, x);
}

#endif

_Thread_local double short_erf_fit_w;

double short_erf_fit_func(double x)
{
	return short_erf(x, short_erf_fit_w);
}

double fastshort_erf(double x, double w)	// max error < 1.9e-9 for w >= 2
{
	double xa;
	static int degree=0;
	static _Thread_local double *lut=NULL, cached_w = -1., index_mul=0.;

	xa = fabs(x);

	if (xa >= w)
		return copysign(1., x);

	// Update cached LUT
	if (w != cached_w)
	{
		short_erf_fit_w = cached_w = w;

		int is, segcount=0;
		double err, max_err=0., segstart, segend, segstep = 1./32.;
		degree = 3;

		// Calc LUT size and adjust parameters
calc_segcount:
		segcount = ceil(w / segstep);

		// Make sure the LUT takes up no more than 3.5 kB
		if (segcount * (degree+1) * sizeof(double) > 3500)
		{
			degree++;
			segstep *= 2.;
			goto calc_segcount;
		}

		// Make sure it's not too small either
		if (segcount < 48 && w > 0.001 && w < 1.5)
		{
			segstep *= 0.5;
			goto calc_segcount;
		}

		index_mul = 1. / segstep;

		// Alloc LUT
		free(lut);
		lut = calloc(segcount * (degree+1), sizeof(double));

		// Generate LUT
		for (is=0; is < segcount; is++)
		{
			segstart = (double) is * segstep;
			segend = MINN(w, segstart + segstep);

			polynomial_fit_on_function_by_dct_count(short_erf_fit_func, segstart, segend, &lut[is*(degree+1)], degree, (degree+1)+3, fastcos_tr_d5);
			//err = get_polynomial_error(short_erf_fit_func, segstart, segend, &lut[is*(degree+1)], degree, NEGMODE);
			//max_err = MAXN(max_err, err);
		}

		//fprintf_rl(stdout, "short_erf(x, %g) LUT max error %g\n", w, max_err);
	}

	// Evaluation
	int lutind = xa * index_mul;

	return copysign(polynomial_from_lut(lut, lutind, degree, xa), x);
}
