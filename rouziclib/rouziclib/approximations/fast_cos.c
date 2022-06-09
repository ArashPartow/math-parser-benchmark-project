#ifndef RL_EXCL_APPROX

uint32_t fastcos_get_param(double *xp, double *endsign, const int quads)
{
	double x=*xp, xoff;
	uint64_t *xint = (uint64_t *) &x;
	uint32_t lutind;

	// x = ]-inf , +inf[ --> x = [0 , 1[
	x = get_fractional_part_positive(x);

	// Quadrant symmetry
	if (quads <= 2)
	{
		// x = [0 , 1[ --> x = [0 , 0.5]
		if (*xint > 0x3FE0000000000000)		// if x > 0.5 when 1 or 2 quadrants
			x = 1. - x;

		// x = [0 , 0.5] --> x = [0 , 0.25]
		if (quads == 1 && *xint > 0x3FD0000000000000)		// if x > 0.25 when 1 quadrant
		{
			*endsign = -1.;
			x = 0.5 - x;
		}
	}

	*xp = x;
	xoff = x + 2.;		// the mantissa for xoff is [1.0 , either 1.125, 1.25 or 1.5]

	lutind = (((uint32_t *) &xoff)[1] & 0x000FFFFF);		// top bits of the mantissa form the LUT index
	return lutind;
}

uint32_t fastcosf_get_param(float *xp)
{
	float x=*xp, xoff;
	uint32_t *xint = (uint32_t *) &x;
	uint32_t lutind;

	// x = ]-inf , +inf[ --> x = [0 , 1]
	x = get_fractional_part_positivef(x);

	*xp = x;
	xoff = x + 2.f;	// the mantissa for xoff is [1.0 , 1.5]

	lutind = (*((uint32_t *) &xoff) & 0x007FFFFF);	// top bits of the mantissa form the LUT index
	return lutind;
}

float fastcosf_tr_d2(float x)	// max error: 2.82e-006 (compare with 1.52017e-007 for cosf())
{
	static const float lut[] = 
	#include "tables/fastcos_d2.h"		// 1 kB
	const uint32_t ish=20-lutsp;
	const float *c;
	uint32_t lutind;

	lutind = fastcosf_get_param(&x) >> ish;
	c = &lut[lutind*3];
	//return fmaf(fmaf(c[2], x, c[1]), x, c[0]);		// too slow
	return (c[2]*x + c[1])*x + c[0];			// less precise
}

double fastcos_tr_d2(double x)	// max error: 6.159e-007
{
	static const double lut[] = 
	#include "tables/fastcos_d2.h"		// 2 kB
	const uint32_t ish=17-lutsp;
	const double *c;
	uint32_t lutind;

	lutind = fastcos_get_param(&x, NULL, quads) >> ish;
	c = &lut[lutind*3];
	//return fma(fma(c[2], x, c[1]), x, c[0]);
	return (c[2]*x + c[1])*x + c[0];
}

double fastcos_tr_d3(double x)	// max error: 1.88958e-009
{
	static const double lut[] = 
	#include "tables/fastcos_d3.h"		// 3 kB
	const uint32_t ish=17-lutsp;
	const double *c;
	uint32_t lutind;

	lutind = fastcos_get_param(&x, NULL, quads) >> ish;
	c = &lut[lutind<<2];
	//return fma(fma(fma(c[3], x, c[2]), x, c[1]), x, c[0]);
	return ((c[3]*x + c[2])*x + c[1])*x + c[0];
}

double fastcos_tr_d4(double x)	// max error: 4.63742e-012
{
	static const double lut[] = 
	#include "tables/fastcos_d4.h"		// 2 kB
	const uint32_t ish=17-lutsp;
	const double *c;
	uint32_t lutind;

	lutind = fastcos_get_param(&x, NULL, quads) >> ish;
	c = &lut[lutind*5];
	//return fma(fma(fma(fma(c[4], x, c[3]), x, c[2]), x, c[1]), x, c[0]);
	return (((c[4]*x + c[3])*x + c[2])*x + c[1])*x + c[0];
}

double fastcos_tr_d5(double x)	// max error: ~9e-016 (compare with 3.41596e-016 for cos())
{
	static const double lut[] = 
	#include "tables/fastcos_d5.h"		// 2.5 kB
	const uint32_t ish=17-lutsp;
	const double *c;
	double endsign = 1.;
	uint32_t lutind;

	lutind = fastcos_get_param(&x, &endsign, quads) >> ish;
	c = &lut[lutind*6];
	return copysign(fma(fma(fma(fma(fma(c[5], x, c[4]), x, c[3]), x, c[2]), x, c[1]), x, c[0]), endsign);
	//return endsign * (((((c[5]*x + c[4])*x + c[3])*x + c[2])*x + c[1])*x + c[0]);
}

xy_t fastcos_tr_d3_xy(xy_t v)
{
	#ifdef RL_INTEL_INTR

	__m128d md = _mm_load_pd((double *) &v);
	md = _mm_fastcos_tr_d3(md);
	_mm_storeu_pd((double *) &v, md);
	return v;

	#endif

	return func1_xy(v, fastcos_tr_d3);
}

#endif
