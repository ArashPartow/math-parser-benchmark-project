// Avoids optimising away certain crucial operations when /fp:fast or -ffast-math are specified
// Works on MSVC and Clang, not on GCC
#ifndef _gcc_
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

ddouble_t ddouble(const double v)
{
	ddouble_t r = {v, 0.};
	return r;
}

// Double to quad basic operations
#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t add_dd_q_quick(double a, double b)
{
	ddouble_t r;
	r.hi = a + b;
	r.lo = b - (r.hi - a);
	return r;
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t add_dd_q(double a, double b)
{
	ddouble_t r;
	r.hi = a + b;
	double v = r.hi - a;
	r.lo = (a - (r.hi - v)) + (b - v);
	return r;
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t sub_dd_q(double a, double b)
{
	ddouble_t r;
	r.hi = a - b;
	double v = r.hi - a;
	r.lo = (a - (r.hi - v)) - (b + v);
	return r;
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t mul_dd_q(double a, double b)
{
	ddouble_t r;
	r.hi = a * b;
	r.lo = fma(a, b, -r.hi);
	return r;
}

// Mixed quad/double operations
ddouble_t add_qd(ddouble_t a, double b)
{
	ddouble_t s = add_dd_q(a.hi, b);
	return add_dd_q_quick(s.hi, a.lo + s.lo);
}

ddouble_t sub_qd(ddouble_t a, double b)
{
	ddouble_t s = sub_dd_q(a.hi, b);
	return add_dd_q_quick(s.hi, a.lo + s.lo);
}

ddouble_t sub_dq(double a, ddouble_t b)
{
	// FIXME probably not optimal
	return add_qd(neg_q(b), a);
}

ddouble_t mul_qd(ddouble_t a, double b)
{
	ddouble_t c = mul_dd_q(a.hi, b);
	return add_dd_q_quick(c.hi, fma(a.lo, b, c.lo));
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t div_qd(ddouble_t a, double b)
{
	double t_hi = a.hi / b;
	ddouble_t p = mul_dd_q(t_hi, b);
	double d_hi = a.hi - p.hi;
	double d_lo = a.lo - p.lo;
	double t_lo = (d_hi + d_lo) / b;
	return add_dd_q_quick(t_hi, t_lo);
}

ddouble_t div_dq(double a, ddouble_t b)
{
	// FIXME probably not ideal
	return mul_qd(recip_q(b), a);
}

// Quad operations
ddouble_t add_qq(ddouble_t a, ddouble_t b)
{
	ddouble_t s = add_dd_q(a.hi, b.hi);
	ddouble_t t = add_dd_q(a.lo, b.lo);
	ddouble_t v = add_dd_q_quick(s.hi, s.lo + t.hi);
	ddouble_t z = add_dd_q_quick(v.hi, t.lo + v.lo);
	return z;
}

ddouble_t sub_qq(ddouble_t a, ddouble_t b)
{
	ddouble_t s = sub_dd_q(a.hi, b.hi);
	ddouble_t t = sub_dd_q(a.lo, b.lo);
	ddouble_t v = add_dd_q_quick(s.hi, s.lo + t.hi);
	ddouble_t z = add_dd_q_quick(v.hi, t.lo + v.lo);
	return z;
}

// Based on https://stackoverflow.com/a/31647953/1675589
#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t mul_qq(ddouble_t a, ddouble_t b)
{
	ddouble_t r, m;
	const double c = 134217729.;
	double up, u1, u2, vp, v1, v2;

	up = a.hi*c;        vp = b.hi*c;
	u1 = (a.hi-up)+up;  v1 = (b.hi-vp)+vp;
	u2 = a.hi-u1;       v2 = b.hi-v1;

	m.hi = a.hi*b.hi;
	m.lo = (((u1*v1-m.hi)+(u1*v2))+(u2*v1))+(u2*v2);

	m.lo += a.hi*b.lo + a.lo*b.hi;
	r.hi = m.hi + m.lo;
	r.lo = m.hi - r.hi + m.lo;

	return r;
}

ddouble_t mad_qqq(ddouble_t a, ddouble_t b, ddouble_t c)
{
	return add_qq(mul_qq(a, b), c);
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t div_qq(ddouble_t a, ddouble_t b)
{
	double t_hi = a.hi / b.hi;
	ddouble_t r = mul_qd(b, t_hi);
	double pi_hi = a.hi - r.hi;
	double d = pi_hi + (a.lo - r.lo);
	double t_lo = d / b.hi;
	return add_dd_q_quick(t_hi, t_lo);
}

ddouble_t neg_q(ddouble_t a)
{
	ddouble_t r;
	r.hi = -a.hi;
	r.lo = -a.lo;
	return r;
}

ddouble_t abs_q(ddouble_t a)
{
	if (a.hi < 0.)
		a = neg_q(a);
	return a;
}

ddouble_t copysign_q(ddouble_t a, ddouble_t b)
{
	if ((a.hi > 0. && b.hi < 0.) || (a.hi < 0. && b.hi > 0.))
		a = neg_q(a);

	return a;
}

ddouble_t sq_q(ddouble_t a)
{
	return mul_qq(a, a);
}

#ifdef _gcc_
__attribute__((optimize("-fno-fast-math")))
#endif
ddouble_t recip_q(ddouble_t b)
{
	double t_hi = 1.0 / b.hi;
	ddouble_t r = mul_qd(b, t_hi);
	double pi_hi = 1.0 - r.hi;
	double d = pi_hi - r.lo;
	double t_lo = d / b.hi;
	return add_dd_q_quick(t_hi, t_lo);
}

ddouble_t mul_qd_simple(ddouble_t a, double m)	// multiplier must only change the exponent, not the mantissa
{						// like 0.125, -0.5, 1., -2., 64., ...
	a.hi *= m;
	a.lo *= m;
	return a;
}

#ifndef _gcc_
#pragma float_control(pop)
#endif

int cmp_qq(const ddouble_t *a, const ddouble_t *b)
{
	if (a->hi > b->hi) return 1;
	if (a->hi < b->hi) return -1;
	if (a->lo == b->lo) return 0;
	if (a->lo > b->lo) return 1;
	return -1;
}

int cmp_qd(const ddouble_t a, const double b)
{
	if (a.hi > b) return 1;
	if (a.hi < b) return -1;
	if (a.lo == 0.) return 0;
	if (a.lo > 0.) return 1;
	return -1;
}

ddouble_t min_qq(ddouble_t a, ddouble_t b)
{
	if (cmp_qq(&a, &b) < 0)
		return a;
	return b;
}

ddouble_t max_qq(ddouble_t a, ddouble_t b)
{
	if (cmp_qq(&a, &b) > 0)
		return a;
	return b;
}

ddouble_t rangelimit_qqq(ddouble_t x, ddouble_t min, ddouble_t max)
{
	return min_qq(max_qq(x, min), max);
}

ddouble_t floorceiltrunc_q(ddouble_t a, double (*func)(double))
{
	ddouble_t r;

	r.hi = func(a.hi);
	r.lo = 0.;

	// If hi is large enough that it is an integer
	if (r.hi == a.hi)
	{
		// Apply function on lo
		r.lo = func(a.lo);
		return add_dd_q_quick(r.hi, r.lo);
	}

	return r;
}

ddouble_t floor_q(ddouble_t a)
{
	return floorceiltrunc_q(a, floor);
}

ddouble_t ceil_q(ddouble_t a)
{
	return floorceiltrunc_q(a, ceil);
}

ddouble_t trunc_q(ddouble_t a)
{
	return floorceiltrunc_q(a, trunc);
}

ddouble_t nearbyint_q(ddouble_t a)
{
	return floorceiltrunc_q(a, nearbyint);
}

ddouble_t string_to_ddouble(const char *string, char **endptr)
{
	int i, neg=0, digits_end=0, separator_pos, p_len, exponent=0, digit_count, dest_index, carry;
	const int print = 0;	// set to 1 to print buffer contents
	const char *p;
	char *endptr2=NULL, buf_a[635+1], buf_b[635+1];
	double vd, a, digit_mul;
	ddouble_t r={0};

	// Let strtod reveal invalid strings, NANs, INFs and zeros
	vd = strtod(string, &endptr2);
	if (endptr)
		*endptr = endptr2;

	if (vd==0. || isfinite(vd)==0)
		return ddouble(vd);

	p = skip_whitespace(string);

	// Detect and remove sign
	if (p[0] == '+' || p[0] == '-')
	{
		if (p[0] == '-')
			neg = 1;
		p = &p[1];
	}

	// Find things
	p_len = endptr2 - p;
	separator_pos = p_len;			// if there's no separator this position will be used
	for (i=0; i < p_len; i++)
	{
		// Look for last digit
		if (isdigit(p[i]))
			digits_end = i;

		// Look for separator
		if (p[i] == '.')
			separator_pos = i;

		// Look for exponent
		if (p[i] == 'e' || p[i] == 'E')
		{
			separator_pos = MINN(separator_pos, i);		// if there's no separator 'e' will be used
			exponent = atoi(&p[i+1]);
			break;
		}
	}

	vd = fabs(vd);
	r.hi = vd;

	// Any finite double can have the exact value it represents represented exactly by 1 (sign) + 309 (integers) + 1 (.) + 1074 (fractionals) = 1385 chars
	// However the last 750 chars have no influence so using only 324 fractional chars instead of 1074 is just as good

	// Turn the original string into a +309.324 representation
	sprintf(buf_a, "%+0635.324f", 0.);

	// Place digits from before the separator
	for (i=0; i < separator_pos; i++)
	{
		dest_index = 310-1-i - exponent;
		if (dest_index >= 310)		// digit goes after destination separator
			dest_index++;

		if (dest_index > 0 && dest_index < 635)
			buf_a[dest_index] = p[separator_pos-1-i];
	}

	// Place digits from after the separator
	for (i=0; i < digits_end-separator_pos; i++)
	{
		dest_index = 310+i - exponent;
		if (dest_index >= 310)		// digit goes after destination separator
			dest_index++;

		if (dest_index > 0 && dest_index < 635)
			buf_a[dest_index] = p[separator_pos+1+i];
	}

	// Turn vd into a +309.324 representation
	sprintf(buf_b, "%+0635.324f", vd);
	if (print) fprintf_rl(stdout, "%s\n%s\n", buf_a, buf_b);

	// Subtract digits
	carry = 0;
	for (i=635-1; i > 0; i--)
	{
		if (i != 310)
		{
			buf_a[i] = buf_a[i] - buf_b[i] + carry + '0';

			carry = 0;
			if (buf_a[i] < '0')
			{
				carry = -1;
				buf_a[i] += 10;
			}
		}
	}

	// Handle propagated carry that flips the sign
	if (carry == -1)
	{
		// Flip sign
		buf_a[0] = buf_a[0]=='+' ? '-' : '+';

		// Flip digits
		for (i=1; i < 635; i++)
			if (i != 310)
				buf_a[i] = '9' - buf_a[i] + '0';

		// Propagate carry from the lowest digit
		for (i=635-1; i > 0; i--)
		{
			if (i != 310)
			{
				buf_a[i] += 1;

				if (buf_a[i] > '9')
					buf_a[i] -= 10;
				else
					break;		// stop spreading the carry when there's no more overflow
			}
		}
	}
	if (print) fprintf_rl(stdout, "%s\n", buf_a);

	// Turn buf_a into a double
	r.lo = strtod(buf_a, NULL);
	if (print) fprintf_rl(stdout, "Result: {%.17g, %.17g}\n\n", r.hi, r.lo);

	// Apply sign
	if (neg)
		r = neg_q(r);

	return r;
}
