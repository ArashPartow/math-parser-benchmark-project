ddouble_t sqrt_q(ddouble_t x)	// max error ratio about 5.8e-33
{
	ddouble_t y, y2, v1, v2, v3;

	if (x.hi < 0.)
		return Q_NAN;

	// Start from double precision sqrt
	y = ddouble(sqrt(x.hi));

	// Use Halley's method to refine
	// y -= 2y * (y^2 - x) / (3y^2 + x)
	y2 = mul_qq(y, y);
	v1 = mul_qd_simple(y, 2.);
	v2 = sub_qq(y2, x);
	v3 = add_qq(mul_qd(y2, 3.), x);
	v1 = mul_qq(v1, v2);
	v1 = div_qq(v1, v3);
	y = sub_qq(y, v1);

	return y;
}

#define COS_Q_CHEB
ddouble_t cos_tr_q(ddouble_t x)	// max error about 4.3e-32 (Chebyshev version, the other is slightly worse)
{
	double endsign = 1.;
	ddouble_t y;
	#ifdef COS_Q_CHEB
	ddouble_t cm[] = {
		{0.47200121576823478, -1.5640151617803393e-17}, 	// T_0 (err 1.56e-34)
		{-0.4994032582704071, 1.4758624598140668e-17},  	// T_1 (err 1.5e-35)
		{0.027992079617547617, 7.3010368448985277e-19}, 	// T_2 (err 4.49e-35)
		{-0.00059669519654884649, -1.3902999147480702e-20},     // T_3 (err 7.07e-38)
		{6.7043948699168399e-06, 2.035995049262044e-22},        // T_4 (err -2.51e-39)
		{-4.6532295897319527e-08, -1.769161868176914e-24},      // T_5 (err -1.36e-40)
		{2.1934576589567331e-10, 2.8463881389941215e-27},       // T_6 (err 1e-43)
		{-7.4816487010336462e-13, 4.1338949231363225e-29},      // T_7 (err -5.31e-46)
		{1.9322978458633277e-15, -7.2354286636588526e-32},      // T_8 (err 2.4e-49)
		{-3.9101701216325904e-18, 6.942454170604681e-35},       // T_9 (err 3.62e-52)
		{6.3670401158338003e-21, 1.579630782651198e-37},        // T_10 (err 5.06e-54)
		{-8.522886041732634e-24, 8.5324378256780345e-41},       // T_11 (err 2.82e-57)
		{9.5446630340576279e-27, 1.1519600914539063e-43},       // T_12 (err 6.84e-61)
		{-9.0744812452201831e-30, -4.2984483792836492e-46},     // T_13 (err 1.25e-63)
		{7.415916419082441e-33, 5.1095287340737115e-49},        // T_14 (err -9.6e-66)
		/* Errors for this implementation based on the maximum degree used:
		   T_12 => 9.11347e-30
		   T_13 => 4.76886e-32
		   T_14 => 4.27417e-32
		   T_15 => 4.27417e-32
		   */
	};
	#else
	ddouble_t c[] = {
		{1, -5.2685651532657577e-36},   			// c0
		{-19.739208802178716, -1.2530591017479423e-15}, 	// c1
		{64.939394022668296, -4.2563201318878282e-15},  	// c2
		{-85.456817206693728, 2.0361752253113143e-16},  	// c3
		{60.244641371876661, -3.2212648404075122e-16},  	// c4
		{-26.426256783374399, 1.1982764379130646e-15},  	// c5
		{7.9035363713184692, -3.9613952660077854e-16},  	// c6
		{-1.714390711088672, -3.4612037008301457e-17},  	// c7
		{0.28200596845579096, 2.1376133124519225e-17},  	// c8
		{-0.036382841142537675, 1.7328614067836044e-18},        // c9
		{0.0037798342004859886, -1.8105199741884246e-20},       // c10
		{-0.0003229910638446016, -1.3130761734743837e-20},      // c11
		{2.3099916358372477e-05, -3.4908602905870041e-22},      // c12
		{-1.4026753595423889e-06, 9.914502332376071e-23},       // c13
		{7.1722342681062607e-08, 4.9416329701476483e-24},       // c14
		/* Errors for this implementation based on the polynomial degree:
		   degree 12 => 9.10454e-30
		   degree 13 => 5.68422e-32
		   degree 14 => 5.17274e-32
		   degree 15 => 5.17274e-32
		   */
	};		
	#endif

	// x = ]-inf , +inf[ --> x = [0 , 1[
	x = sub_qq(x, floor_q(x));

	// Quadrant symmetry
	// x = [0 , 1[ --> x = [0 , 0.5]
	if (cmp_qd(x, 0.5) > 0)
		x = sub_dq(1., x);

	// x = [0 , 0.5] --> x = [0 , 0.25]
	if (cmp_qd(x, 0.25) > 0)
	{
		endsign = -1.;
		x = sub_dq(0.5, x);
	}

	// Square mapping, x = [0 , 0.25] --> x = [0 , 0.0625]
	x = mul_qq(x, x);

	#ifdef COS_Q_CHEB
	// x = [0 , 0.0625] --> x = [-1 , 1] to fit the Chebyshev unit span
	x = sub_qd(mul_qd_simple(x, 32.), 1.);

	// Chebyshev evaluation
	y = eval_chebyshev_polynomial_q(x, cm, 14);

	#else

	// Polynomial evaluation
	y = eval_polynomial_q(x, c, 14);
	#endif

	return mul_qd_simple(y, endsign);
}

ddouble_t cos_q(ddouble_t x)
{
	return cos_tr_q(mul_qq(x, Q_1_2PI));
}

ddouble_t sin_tr_q(ddouble_t x)
{
	return cos_tr_q(add_qd(x, -0.25));
}

ddouble_t sin_q(ddouble_t x)
{
	return sin_tr_q(mul_qq(x, Q_1_2PI));
}

ddouble_t asin_q(ddouble_t x)	// max error < 1e-30 for |x| < 0.9996, < 1e-28 for |x| < 0.99999999, worsens as it approaches 1
{
	int i;
	ddouble_t y, a, a2, b, c, d, ax;
	double xa, xm;

	xa = fabs(x.hi);
	if (xa > 1.)
		return Q_NAN;

	// Map x
	xm = 1. - sqrt(1. - xa);

	// Polynomial
	y = ddouble(((((((((((0.1136485*xm - 0.73547003)*xm + 2.14575625)*xm - 3.76647442)*xm +
		4.514331632)*xm - 4.03300466)*xm + 2.93612186)*xm - 1.93150055)*xm +
		1.32709065)*xm - 0.99969704)*xm + 1.99999412)*xm + 1.918e-08);

	// Copy sign
	if (x.hi < 0.)
		y = neg_q(y);

	// Newton-Raphson steps (the first iteration brings the error in the e-17 range)
	// y -= (a - x) / sqrt(1 - a^2)
	/*for (i=0; i < 3; i++)
	{
		a = sin_q(y);
		b = sqrt_q(sub_dq(1., mul_qq(a, a)));	// replaces b = cos_q(y)
		a = div_qq(sub_qq(a, x), b);
		y = sub_qq(y, a);
	}*/

	// Halley's method (the first iteration brings the error in the e-24 range)
	// y -= (2 sqrt(1 - a^2) (x-a))/(a (x+a) - 2)
	for (i=0; i < 2; i++)
	{
		a = sin_q(y);
		a2 = mul_qq(a, a);
		c = sub_dq(1., a2);		// c = 1 - a^2
		b = mul_qq(mul_qd_simple(sqrt_q(c), 2.), sub_qq(x, a));
		d = sub_qd(mul_qq(a, add_qq(x, a)), 2.);
		y = sub_qq(y, div_qq(b, d));
	}

	return y;
}

ddouble_t exp2_q(ddouble_t x)	// max error < 7.3e-32 when x < 1
{
	ddouble_t xr, xf, xfe;
	double em;
	uint64_t em_int;

	ddouble_t cm[] = {
		{1.4569998750129629, 5.0865586328592469e-17},   	// T_0 (err -6.92e-34)
		{0.49752486781044186, 2.3150358977957938e-17},  	// T_1 (err 1.41e-33)
		{0.042893111989679641, -1.7882037061404992e-18},        // T_2 (err -2.23e-35)
		{0.0024714281639958507, 1.1268571377686657e-20},        // T_3 (err -6.22e-37)
		{0.00010690611635808512, -4.8207576519531194e-21},      // T_4 (err 4.17e-38)
		{3.7013814277244363e-06, -1.8289982818732787e-22},      // T_5 (err 2.87e-39)
		{1.0682375375401699e-07, 2.4488927360643164e-24},       // T_6 (err 8.22e-41)
		{2.6430327628977725e-09, -1.7441478191487318e-25},      // T_7 (err 9.74e-42)
		{5.7226475706182939e-11, -1.3700094783348603e-27},      // T_8 (err 6.11e-44)
		{1.1014762141606643e-12, -3.7265104963113956e-29},      // T_9 (err -7.2e-46)
		{1.9081920420290866e-14, 4.3622504995887996e-31},       // T_10 (err -3.14e-48)
		{3.0053572100519623e-16, -1.4361602666938867e-32},      // T_11 (err 1.08e-48)
		{4.3390709066981233e-18, 3.8426473152644908e-35},       // T_12 (err 3.87e-52)
		{5.7829205566101519e-20, -5.0398703797465889e-36},      // T_13 (err -2.74e-52)
		{7.156860824424656e-22, -1.0673183625670153e-38},       // T_14 (err 3.84e-55)
		{8.2668956137979358e-24, -3.8501670767186593e-40},      // T_15 (err -2.92e-56)
		{8.9524108085309483e-26, 4.0272836385292071e-42},       // T_16 (err 7.97e-59)
		{9.1246021818829229e-28, -3.1270978525262432e-44},      // T_17 (err 1.81e-60)
		{8.7835236771544351e-30, -4.8566286446849949e-46},      // T_18 (err 4.67e-63)
		{8.010254786459366e-32, -4.5981913695050257e-49},       // T_19 (err -2.9e-65)
		// T_18 => 1.50329e-31
		// T_19 => 7.28674e-32
		// T_20 => 8.28381e-32
	};

	if (x.hi < -1022. || x.hi >= 1024.)
		return Q_NAN;

	// Separate integer from fractional parts
	xr = floor_q(x);	// integer part of x
	xf = sub_qq(x, xr);		// fractional part of x. xf = [0.0 , 1.0[

	// Make 2^xr multiplier
	em_int = ((uint64_t) xr.hi + 1023) << 52;	// turn xr into an IEEE-754 exponent
	em = *((double *) &em_int);			// now em = 2^xr

	// Chebyshev evaluation
	xf = sub_qd(mul_qd_simple(xf, 2.), 1.);
	xfe = eval_chebyshev_polynomial_q(xf, cm, 19);

	// y = 2^xf * 2^xr
	return mul_qd_simple(xfe, em);
}

ddouble_t exp_q(ddouble_t x)
{
	return exp2_q(mul_qq(x, Q_1_LOG2));
}

ddouble_t gaussian_q(ddouble_t x)
{
	return exp_q(neg_q(mul_qq(x, x)));
}

ddouble_t erf_q(ddouble_t x)	// max err < 2.1e-32
{
	#include "tables/erf_q.h"	// contains tables cm0 to cm6, 2.6 kB
	ddouble_t xa, xm, y;

	xa = abs_q(x);

	// Chebyshev evaluation by segment
	if (xa.hi <= 0.5)
	{
		xm = sub_qd(mul_qd_simple(xa, 4.), 1.);			// [0 , 0.5] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm0, 25);
	}
	else if (xa.hi <= 1.)
	{
		xm = sub_qd(mul_qd_simple(xa, 4.), 3.);			// [0.5 , 1] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm1, 25);
	}
	else if (xa.hi <= 2.)
	{
		xm = sub_qd(mul_qd_simple(xa, 2.), 3.);			// [1 , 2] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm2, 27);
	}
	else if (xa.hi <= 3.5)
	{
		xm = div_qd(mul_qd_simple(sub_qd(xa, 2.75), 4.), 3.);	// [2 , 3.5] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm3, 27);
	}
	else if (xa.hi <= 6.)
	{
		xm = div_qd(mul_qd_simple(sub_qd(xa, 4.75), 4.), 5.);	// [3.5 , 6] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm4, 25);
	}
	else if (xa.hi <= 10.)
	{
		xm = mul_qd_simple(sub_qd(xa, 8.), 0.5);		// [6 , 10] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm5, 17);
	}
	else //if (xa.hi <= 20.)
	{
		xa = min_qq(xa, ddouble(40.));
		xm = div_qd(sub_qd(xa, 15.), 5.);			// [10 , 20] => [-1 , 1]
		y = eval_chebyshev_polynomial_q(xm, cm6, 20);
	}

	// Apply other operations
	if (xa.hi > 1.)
		y = sub_dq(1., exp_q(y));

	// Apply sign
	if (x.hi < 0.)
		y = neg_q(y);

	return y;
}
