#ifdef RL_MPFR

void eval_polynomial_mpfr(real_t y, real_t x, real_t *c, int degree)
{
	int i;

	r_setd(y, 0.);

	for (i=degree; i > 0; i--)
	{
		r_add(y, c[i]);
		r_mul(y, x);
	}
	r_add(y, c[0]);
}

void eval_chebyshev_polynomial_mpfr(real_t y, real_t x, real_t *cm, int degree)
{
	int id;
	real_t b1, b2, x2;

	r_init(b1);
	r_init(b2);
	r_init(x2);

	if (degree == 0)
	{
		r_set(y, cm[0]);
		goto end;
	}

	r_rmuld(x2, x, 2.);

	// Clenshaw evaluation
	r_set(y, cm[degree]);
	for (id = degree-1; id >= 1; id--)
	{
		r_set(b2, b1);
		r_set(b1, y);

		// y = cm[id] + x2*b1 - b2;
		r_fma(y, x2, b1, cm[id]);
		r_sub(y, b2);
		
	}

	// y = cm[0] + x*y - b1;
	r_fma(y, x, y, cm[0]);
	r_sub(y, b1);

end:
	r_free(b1);
	r_free(b2);
	r_free(x2);
}

double get_polynomial_error_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree, int errmode)
{
	int i, ic;
	real_t a, b, x, err;
	double errd;

	r_init(a);
	r_init(b);
	r_init(x);
	r_init(err);

	r_setd(err, 0.);
	for (i=0; i <= 1000; i++)
	{
		r_mix(x, (double) i / 1000., start, end);
		eval_polynomial_mpfr(a, x, c, degree);
		f(b, x);

		if (errmode==DIVMODE)
		{
			if (mpfr_cmp(a, b) < 0)		// if (a < b)
			{
				r_rdiv(a, b, a);	// a = b / a - 1.;
				r_subd(a, 1.);
			}
			else
			{
				r_div(a, b);		// a = a / b - 1.;
				r_subd(a, 1.);
			}
		}
		else
			r_rsub(a, b, a);		// a = b - a;

		r_abs(a);

		if (mpfr_cmp(err, a) < 0)
			r_set(err, a);
	}

	errd = r_todouble(err);

	r_free(a);
	r_free(b);
	r_free(x);
	r_free(err);

	return errd;
}

void polynomial_addition_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c)
{
	int i, mindeg = MINN(adeg, bdeg), maxdeg = MAXN(adeg, bdeg);

	for (i=0; i <= maxdeg; i++)
	{
		if (i <= mindeg)
			r_radd(c[i], a[i], b[i]);
		else
			r_set(c[i], (adeg > bdeg) ? a[i] : b[i]);
	}
}

void polynomial_subtraction_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c)
{
	int i, mindeg = MINN(adeg, bdeg), maxdeg = MAXN(adeg, bdeg);

	for (i=0; i <= maxdeg; i++)
	{
		if (i <= mindeg)
			r_rsub(c[i], a[i], b[i]);
		else if (adeg > bdeg)
			r_set(c[i], a[i]);
		else
			r_rneg(c[i], b[i]);
	}
}

void polynomial_scalar_mul_mpfr(real_t *a, int adeg, real_t m, real_t *c)
{
	int i;

	for (i=0; i <= adeg; i++)
		r_rmul(c[i], a[i], m);
}

int polynomial_multiplication_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c, int cdeg)
{
	int ia, ib, deg, maxdeg=0;

	for (ia=0; ia <= adeg; ia++)
	{
		for (ib=0; ib <= bdeg; ib++)
		{
			deg = ia + ib;

			if (cdeg >= deg)
			{
				r_fma(c[deg], a[ia], b[ib], c[deg]);

				if (mpfr_zero_p(c[deg])==0)
					maxdeg = MAXN(maxdeg, deg);
			}
		}
	}

	if (cdeg < maxdeg)
		fprintf_rl(stderr, "cdeg of %d < maxdeg of %d in polynomial_multiplication_mpfr()\n", cdeg, maxdeg);

	return maxdeg;
}

real_t *polynomial_power_mpfr(real_t *a, int adeg, int n, int *maxdegp)
{
	int i, j, maxdeg=0;
	real_t *c0, *c1, *p;

	if (n==0)
	{
		c0 = r_init_array(1);
		r_setd(c0[0], 1.);

		if (maxdegp)
			*maxdegp = 0;
		return c0;
	}

	c0 = r_init_array(adeg*n+1);
	c1 = r_init_array(adeg*n+1);
	r_setd(c0[0], 1.);

	for (i=1; i <= n; i++)
	{
		for (j=0; j < adeg*n+1; j++)
			r_setd(c1[j], 0.);

		maxdeg = polynomial_multiplication_mpfr(a, adeg, c0, maxdeg, c1, adeg*n);

		p = c0;
		c0 = c1;
		c1 = p;
	}

	r_free_array(&c1, adeg*n+1);

	if (maxdegp)
		*maxdegp = maxdeg;

	for (i=*maxdegp+1; i < adeg*n+1; i++)
		r_free(c0[i]);		// c0 will only have reals up to maxdeg

	return c0;
}

void polynomial_x_substitution_mpfr(real_t *a, int adeg, real_t *xs, int xsdeg, real_t *c)
{
	int i, id, maxdeg;
	real_t *exs;

	for (id=0; id <= adeg; id++)
	{
		exs = polynomial_power_mpfr(xs, xsdeg, id, &maxdeg);	// expand xs^id
		for (i=0; i <= maxdeg; i++)
			r_fma(c[i], a[id], exs[i], c[i]);		// multiply by the coefficient and add to c
		r_free_array(&exs, maxdeg+1);
	}
}

real_t *chebyshev_coefs_mpfr(int degree)
{
	int i;
	real_t *t0, *t1, *t2, *p, *m;

	t0 = r_init_array(degree+1);
	r_setd(t0[0], 1.);
	if (degree==0)
		return t0;

	t1 = r_init_array(degree+1);
	r_setd(t1[1], 1.);
	if (degree==1)
	{
		r_free_array(&t0, degree+1);
		return t1;
	}

	t2 = r_init_array(degree+1);
	m = r_init_array(2);
	r_setd(m[1], 2.);	// 2*x + 0

	for (i=2; i <= degree; i++)
	{
		// t2 = 2*x * t1 - t0
		r_zero_array(t2, degree+1);
		polynomial_multiplication_mpfr(m, 1, t1, i-1, t2, degree);
		polynomial_subtraction_mpfr(t2, degree, t0, i-2, t2);

		p = t0;
		t0 = t1;
		t1 = t2;
		t2 = p;
	}

	r_free_array(&m, 2);
	r_free_array(&t0, degree+1);
	r_free_array(&t2, degree+1);

	return t1;
}

void chebyshev_node_mpfr(real_t v, double degree, double node)
{
	if (degree < 1. || node+0.5 < 0. || node+0.5 > degree)
	{
		r_setd(v, 0.);
		return;
	}

	// cos(pi * (node + 0.5) / degree);
	r_pi(v);
	r_muld(v, node + 0.5);
	r_divd(v, degree);
	r_cos(v, v);
}

void polynomial_fit_on_points_mpfr(real_t *x, real_t *y, real_t *c, int degree)
{
	int i, ii, id, j, deg;
	real_t *lj, mj, ci;

	for (i=0; i<degree+1; i++)
		r_setd(c[i], 0.);

	lj = r_init_array(degree*2);

	r_init(mj);
	r_init(ci);

	for (j=0; j < degree+1; j++)
	{
		// Prepare the (a*x + b) form Lagrange polynomial coeficients
		for (i=0; i < degree+1; i++)
		{
			if (i != j)
			{
				ii = i - (i > j);		// one place less if i is over the skipped i==j

				// mj = 1. / (x[j] - x[i]);
				r_rsub(mj, x[j], x[i]);
				r_rddiv(mj, 1., mj);

				r_set(lj[ii*2+1], mj);		// the a of (a*x + b)
				r_rneg(lj[ii*2], x[i]);		// the b of (a*x + b)
				r_mul(lj[ii*2], mj);
			}
		}

		// Expand the Lagrange polynomial
		for (i=0; i < (1 << degree); i++)
		{
			deg = 0;
			r_setd(ci, 1.);

			for (id=0; id < degree; id++)			// go through each element of the multiplication being expanded
			{
				deg += get_bit(i, id);			// deg is the degree of the multiplication
				r_mul(ci, lj[id*2 + get_bit(i, id)]);	// multiply all the elements together into a coefficient
			}

			r_fma(c[deg], ci, y[j], c[deg]);		// add the yj-multiplied coefficient to the correct degree
		}
	}

	r_free(ci);
	r_free(mj);
	r_free_array(&lj, degree*2);
}

void polynomial_fit_on_function_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree)
{
	int i;
	real_t *x, *y, range;

	// Init
	r_init(range);
	r_rsub(range, end, start);

	x = r_init_array(degree+1);
	y = r_init_array(degree+1);

	// Compute the points
	for (i=0; i < degree+1; i++)
	{
		chebyshev_node_mpfr(x[i], degree+1, i);
		r_muld(x[i], 0.5);
		r_addd(x[i], 0.5);
		r_fma(x[i], range, x[i], start);

		f(y[i], x[i]);
	}

	// Fit
	polynomial_fit_on_points_mpfr(x, y, c, degree);

	// Freeing
	r_free_array(&x, degree+1);
	r_free_array(&y, degree+1);
	r_free(range);
}

void chebyshev_multiplier_by_dct_mpfr(real_t v, real_t *y, int p_count, int id)	// look for the Chebyshev multiplier of degree id
{
	int i;
	real_t x, sum, freq;

	r_init(x);
	r_init(sum);
	r_init(freq);

	r_pi(freq);
	r_muld(freq, (double) id);
	r_divd(freq, (double) p_count);

	// DCT
	r_setd(x, 0.5);
	for (i=0; i < p_count; i++)
	{
		// sum += y[i] * cos(x * freq);
		r_rmul(v, x, freq);
		r_cos(v, v);
		r_fma(sum, y[i], v, sum);

		r_addd(x, 1.);
	}

	// Sum division
	// sum *= 2. / (double) p_count;
	r_muld(sum, 2.);
	r_divd(sum, (double) p_count);
	if (id==0)
		r_muld(sum, 0.5);	// frequency 0 gets its sum halved
	r_set(v, sum);

	r_free(x);
	r_free(sum);
	r_free(freq);
}

void polynomial_fit_on_points_by_dct_mpfr(real_t *y, int p_count, real_t start, real_t end, real_t *c, int degree)
{
	int i;
	real_t cm, *cc, *xs;

	r_init(cm);

	xs = r_init_array(2);
	r_zero_array(c, degree+1);

	// x substitution for the shifting
	r_rsub(xs[1], end, start);	// xs[0] = -2.*start/(end-start) - 1.;
	r_rmuld(xs[0], start, -2.);
	r_div(xs[0], xs[1]);
	r_subd(xs[0], 1.);

	r_rddiv(xs[1], 2., xs[1]);	// xs[1] = 2. / (end-start);

	// Compute the coefficients
	for (i=0; i <= degree; i++)
	{
		chebyshev_multiplier_by_dct_mpfr(cm, y, p_count, i);	// get the Chebyshev multiplier for degree i
		cc = chebyshev_coefs_mpfr(i);				// get the default polynomial coeficients
		polynomial_scalar_mul_mpfr(cc, i, cm, cc);		// apply the multiplier
		polynomial_x_substitution_mpfr(cc, i, xs, 1, c);	// shift the polynomial and add to c
		r_free_array(&cc, i+1);
	}

	r_free_array(&xs, 2);
	r_free(cm);
}

real_t *polynomial_function_to_points_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, int p_count)
{
	int i;
	real_t *y, v;

	r_init(v);
	y = r_init_array(p_count);

	// Compute the points
	for (i=0; i < p_count; i++)
	{
		// y[i] = f((end-start) * (0.5+0.5*chebyshev_node(p_count, i)) + start);
		chebyshev_node_mpfr(v, p_count, i);
		r_muld(v, 0.5);
		r_addd(v, 0.5);
		r_rsub(y[i], end, start);
		r_fma(v, y[i], v, start);
		f(y[i], v);
	}
	r_free(v);

	return y;
}

void polynomial_fit_on_function_by_dct_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree)
{
	int p_count = 1000;
	real_t *y;

	// Compute the points
	y = polynomial_function_to_points_mpfr(f, start, end, p_count);

	// Fit
	polynomial_fit_on_points_by_dct_mpfr(y, p_count, start, end, c, degree);

	r_free_array(&y, degree+1);
}

void chebyshev_analysis_on_function_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *cm, int degree, int p_count)
{
	int id;
	real_t *y;

	// Compute the points
	y = polynomial_function_to_points_mpfr(f, start, end, p_count);

	// Compute the coefficients
	for (id=0; id <= degree; id++)
		chebyshev_multiplier_by_dct_mpfr(cm[id], y, p_count, id);	// get the Chebyshev multiplier for degree id

	r_free_array(&y, degree+1);
}

double reduce_digits_mpfr(void (*f)(real_t,real_t), real_t segstart, real_t segend, real_t *c, const int degree, int errmode, double added_error_thresh, double digits)
{
	int i;
	double err0, err1, err_orig;
	real_t l, m, r, rp;

	r_init(l);
	r_init(m);
	r_init(r);
	r_init(rp);

	err_orig = get_polynomial_error_mpfr(f, segstart, segend, c, degree, NEGMODE);

	for (i=0; i <= degree; i++)		// go through every coef to round it
	{
		err0 = get_polynomial_error_mpfr(f, segstart, segend, c, degree, NEGMODE);

		if (mpfr_zero_p(c[i]) == 0)	// if the coef is not 0
		{
			mpfr_abs(l, c[i], MPFR_RNDN);	// -0.0007 -> 0.0007
			r_log10(l, l);			// 0.0007 -> -3.15
			mpfr_floor(l, l);		// -3.15 -> -4
			r_subd(l, digits);		// -4 -> -24

			r_exp10(m, l);			// -24 -> 1e-24

			while (1)
			{
				r_set(rp, r);		// copy the previous result

				r_rdiv(r, c[i], m);	// -0.0007 / 1e-24 -> -7e20
				mpfr_round(r, r);	// -7e20
				r_mul(r, m);		// -7e20 * 1e-24 -> -0.0007
				mpfr_swap(c[i], r);	// set the rounded coef into the coef array for evaluation

				err1 = get_polynomial_error_mpfr(f, segstart, segend, c, degree, NEGMODE);

				if (err1 > err0 * added_error_thresh || mpfr_zero_p(c[i]))		// if the added error is over the threshold
				{
					if (err1 > err0 * added_error_thresh)
						r_set(c[i], rp);	// restore the previous rounding so the error is the threshold
					break;
				}
				else
					mpfr_swap(c[i], r);	// restore the unrounded coef

				r_muld(m, 10.);		// 1e-24 -> 1e-23
			}
		}
	}

	return get_polynomial_error_mpfr(f, segstart, segend, c, degree, NEGMODE);
}

#endif
