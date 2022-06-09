double eval_polynomial(double x, double *c, int degree)
{
	int i;
	double y = c[degree];

	for (i=degree-1; i >= 0; i--)
		y = y * x + c[i];

	return y;
}

xy_t eval_polynomial_xy(xy_t p, xy_t *c, int degree)
{
	int i;
	xy_t r = c[degree];

	for (i=degree-1; i >= 0; i--)
		r = mad_xy(r, p, c[i]);

	return r;
}

ddouble_t eval_polynomial_q(ddouble_t x, ddouble_t *c, int degree)
{
	int i;
	ddouble_t r = c[degree];

	for (i=degree-1; i >= 0; i--)
		r = add_qq(mul_qq(r, x), c[i]);

	return r;
}

double eval_polynomial_unrolled(double x, double *c, int degree)
{
	double y = c[degree];

	switch (degree)
	{
		case 19: y = y * x + c[18];
		case 18: y = y * x + c[17];
		case 17: y = y * x + c[16];
		case 16: y = y * x + c[15];
		case 15: y = y * x + c[14];
		case 14: y = y * x + c[13];
		case 13: y = y * x + c[12];
		case 12: y = y * x + c[11];
		case 11: y = y * x + c[10];
		case 10: y = y * x + c[9];
		case 9: y = y * x + c[8];
		case 8: y = y * x + c[7];
		case 7: y = y * x + c[6];
		case 6: y = y * x + c[5];
		case 5: y = y * x + c[4];
		case 4: y = y * x + c[3];
		case 3: y = y * x + c[2];
		case 2: y = y * x + c[1];
		case 1: y = y * x + c[0];
	}

	return y;
}

xy_t eval_polynomial_unrolled_xy(xy_t p, xy_t *c, int degree)
{
	xy_t r = c[degree];

	switch (degree)
	{
		case 19: mad_xy(r, p, c[18]);
		case 18: mad_xy(r, p, c[17]);
		case 17: mad_xy(r, p, c[16]);
		case 16: mad_xy(r, p, c[15]);
		case 15: mad_xy(r, p, c[14]);
		case 14: mad_xy(r, p, c[13]);
		case 13: mad_xy(r, p, c[12]);
		case 12: mad_xy(r, p, c[11]);
		case 11: mad_xy(r, p, c[10]);
		case 10: mad_xy(r, p, c[9]);
		case 9: mad_xy(r, p, c[8]);
		case 8: mad_xy(r, p, c[7]);
		case 7: mad_xy(r, p, c[6]);
		case 6: mad_xy(r, p, c[5]);
		case 5: mad_xy(r, p, c[4]);
		case 4: mad_xy(r, p, c[3]);
		case 3: mad_xy(r, p, c[2]);
		case 2: mad_xy(r, p, c[1]);
		case 1: mad_xy(r, p, c[0]);
	}

	return r;
}

double eval_polynomial_2d(xy_t p, double **c, xyi_t degree)
{
	double sum=0., sum_line=0.;
	xyi_t id;

	for (id.y=degree.y; id.y >= 0; id.y--)
	{
		sum_line = 0.;

		for (id.x=degree.x; id.x > 0; id.x--)
		{
			sum_line = (sum_line + c[id.y][id.x]) * p.x;
		}
		sum_line += c[id.y][0];

		sum = sum * p.y + sum_line;
	}

	return sum;
}

double eval_chebyshev_polynomial(double x, double *cm, int degree)
{
	int id;
	double b1=0., b2, y, x2 = 2.*x;

	if (degree == 0)
		return cm[0];

	// Clenshaw evaluation
	y = cm[degree];
	for (id = degree-1; id >= 1; id--)
	{
		b2 = b1;
		b1 = y;
		y = cm[id] + x2*b1 - b2;
	}

	y = cm[0] + x*y - b1;

	return y;
}

double eval_chebyshev_polynomial_even(double x, double *cm, int degree)		// here degree is /2, cm is multipliers for T_0, T_2, T_4, ...
{
	int id;
	double b1=0., b2, y, x2 = 2.*x;

	if (degree == 0)
		return cm[0];

	// Clenshaw evaluation
	y = cm[degree];
	for (id = degree-1; id >= 1; id--)
	{
		b2 = b1;
		b1 = y;
		y = x2*b1 - b2;
		b2 = b1;
		b1 = y;
		y = cm[id] + x2*b1 - b2;
	}

	b2 = b1;
	b1 = y;
	y = x2*b1 - b2;
	y = cm[0] + x*y - b1;

	return y;
}

ddouble_t eval_chebyshev_polynomial_q(ddouble_t x, ddouble_t *cm, int degree)
{
	int id;
	ddouble_t b1={0}, b2, y, x2 = mul_qd_simple(x, 2.);

	if (degree == 0)
		return cm[0];

	// Clenshaw evaluation
	y = cm[degree];
	for (id = degree-1; id >= 1; id--)
	{
		b2 = b1;
		b1 = y;

		//y = cm[id] + x2*b1 - b2;
		y = mul_qq(x2, b1);
		y = add_qq(cm[id], y);
		y = sub_qq(y, b2);
	}

	//y = cm[0] + x*y - b1;
	y = mul_qq(x, y);
	y = add_qq(cm[0], y);
	y = sub_qq(y, b1);

	return y;
}

ddouble_t eval_chebyshev_polynomial_even_q(ddouble_t x, ddouble_t *cm, int degree)	// here degree is /2, cm is multipliers for T_0, T_2, T_4, ...
{
	int id;
	ddouble_t b1={0}, b2, y, x2 = mul_qd_simple(x, 2.);

	if (degree == 0)
		return cm[0];

	// Clenshaw evaluation
	y = cm[degree];
	for (id = degree-1; id >= 1; id--)
	{
		b2 = b1;
		b1 = y;

		//y = x2*b1 - b2;
		y = mul_qq(x2, b1);
		y = sub_qq(y, b2);

		b2 = b1;
		b1 = y;

		//y = cm[id] + x2*b1 - b2;
		y = mul_qq(x2, b1);
		y = sub_qq(y, b2);
		y = add_qq(cm[id], y);
	}

	b2 = b1;
	b1 = y;

	//y = x2*b1 - b2;
	y = mul_qq(x2, b1);
	y = sub_qq(y, b2);

	//y = cm[0] + x*y - b1;
	y = mul_qq(x, y);
	y = sub_qq(y, b1);
	y = add_qq(cm[0], y);

	return y;
}

xy_t eval_chebyshev_polynomial_xy(xy_t x, xy_t *cm, int degree)
{
	int id;
	xy_t b1=XY0, b2, y, x2 = add_xy(x, x);

	if (degree == 0)
		return cm[0];

	// Clenshaw evaluation
	y = cm[degree];
	for (id = degree-1; id >= 1; id--)
	{
		b2 = b1;
		b1 = y;
		y = mad_xy(x2, b1, cm[id]);
		y = sub_xy(y, b2);
	}

	y = mad_xy(x, y, cm[0]);
	y = sub_xy(y, b1);

	return y;
}

void integrate_chebyshev_coefs(double *cm, int degree, double *cmi, double span)	// cmi is assumed to be allocated to degree+2, cmi[0] unset
{
	int id;
	double scale = span * 0.5;

	// Degree 0
	cmi[1] = scale * cm[0];
	if (degree <= 0)
		return;

	// Degree 1
	cmi[2] = scale * 0.25 * cm[1];
	if (degree <= 1)
		return;

	// Degrees 2 and above
	for (id=2; id <= degree; id++)
	{
		cmi[id-1] -= scale * cm[id] / (2. * (double) (id-1));
		cmi[id+1] = scale * cm[id] / (2. * (double) (id+1));
	}
}

void integrate_chebyshev_coefs_q(ddouble_t *cm, int degree, ddouble_t *cmi, ddouble_t span)	// cmi is assumed to be allocated to degree+2, cmi[0] unset
{
	int id;
	ddouble_t scale = mul_qd_simple(span, 0.5);

	// Degree 0
	cmi[1] = mul_qq(cm[0], scale);
	if (degree <= 0)
		return;

	// Degree 1
	cmi[2] = mul_qq(cm[1], mul_qd_simple(scale, 0.25));
	if (degree <= 1)
		return;

	// Degrees 2 and above
	for (id=2; id <= degree; id++)
	{
		cmi[id-1] = sub_qq(cmi[id-1], div_qd(mul_qq(scale, cm[id]), 2. * (double) (id-1)));
		cmi[id+1] = div_qd(mul_qq(scale, cm[id]), 2. * (double) (id+1));
	}
}

double get_polynomial_error(double (*f)(double), double start, double end, double *c, int degree, int errmode)
{
	int i;
	double x, y, fx, err;

	err = 0.;
	for (i=0; i <= 1000; i++)
	{
		x = mix(start, end, (double) i / 1000.);
		y = eval_polynomial(x, c, degree);
		fx = f(x);

		if (errmode==DIVMODE)
		{
			if (y < fx)
				y = fx / y - 1.;
			else
				y = y / fx - 1.;
		}
		else
			y = fabs(fx - y);
		err = MAXN(err, y);
	}

	return err;
}

double get_polynomial_error_2d(double (*f)(double,double), xy_t start, xy_t end, double **c, xyi_t degree, int errmode)
{
	xyi_t ip;
	xy_t p;
	double z, fp, err;

	err = 0.;
	for (ip.y=0; ip.y <= 200; ip.y++)
	{
		p.y = (double) ip.y / 200.;
		p.y = p.y * (end.y-start.y) + start.y;

		for (ip.x=0; ip.x <= 200; ip.x++)
		{
			p.x = (double) ip.x / 200.;
			p.x = p.x * (end.x-start.x) + start.x;

			z = eval_polynomial_2d(p, c, degree);
			fp = f(p.x, p.y);

			if (errmode==DIVMODE)
			{
				if (z < fp)
					z = fp / z - 1.;
				else
					z = z / fp - 1.;
			}
			else
				z = fabs(fp - z);
			err = MAXN(err, z);
		}
	}

	return err;
}

double get_polynomial_error_from_points(double *x, double *y, int p_count, double *c, int degree, int errmode)
{
	int i;
	double err, yc;

	for (err=0., i=0; i < p_count; i++)
	{
		yc = eval_polynomial(x[i], c, degree);		

		if (errmode==DIVMODE)
		{
			if (yc < y[i])
				yc = y[i] / yc - 1.;
			else
				yc = yc / y[i] - 1.;
		}
		else
			yc = fabs(y[i] - yc);
		err = MAXN(err, yc);
	}

	return err;
}

char *print_polynomial(double *c, int degree, const char *x)
{
	int id, first=1;
	buffer_t buf={0};

	for (id=degree; id >= 0; id--)
	{
		if (fabs(c[id]) >= 1e-12)
		{
			if (first==0)
				bufprintf(&buf, " %c ", c[id] < 0 ? '-' : '+');

			bufprintf(&buf, "%g", first ? c[id] : fabs(c[id]));

			if (id > 0)
				bufprintf(&buf, "*%s", x);

			if (id > 1)
				bufprintf(&buf, "^%d", id);
			first = 0;
		}
	}

	return buf.buf;
}

void polynomial_addition(double *a, int adeg, double *b, int bdeg, double *c)
{
	int i, mindeg = MINN(adeg, bdeg), maxdeg = MAXN(adeg, bdeg);

	for (i=0; i <= maxdeg; i++)
	{
		if (i <= mindeg)
			c[i] = a[i] + b[i];
		else
			c[i] = (adeg > bdeg) ? a[i] : b[i];
	}
}

void polynomial_subtraction(double *a, int adeg, double *b, int bdeg, double *c)
{
	int i, mindeg = MINN(adeg, bdeg), maxdeg = MAXN(adeg, bdeg);

	for (i=0; i <= maxdeg; i++)
	{
		if (i <= mindeg)
			c[i] = a[i] - b[i];
		else
			c[i] = (adeg > bdeg) ? a[i] : -b[i];
	}
}

void polynomial_scalar_mul(const double *a, int adeg, double m, double *c)
{
	int i;

	for (i=0; i <= adeg; i++)
		c[i] = a[i] * m;
}

void polynomial_scalar_mul_2d(const double **a, xyi_t adeg, double m, double **c)
{
	xyi_t id;

	for (id.y=0; id.y <= adeg.y; id.y++)
		for (id.x=0; id.x <= adeg.x; id.x++)
			c[id.y][id.x] = a[id.y][id.x] * m;
}

void polynomial_scalar_muladd_2d(const double **a, xyi_t adeg, double m, double **c)
{
	xyi_t id;

	for (id.y=0; id.y <= adeg.y; id.y++)
		for (id.x=0; id.x <= adeg.x; id.x++)
			c[id.y][id.x] += a[id.y][id.x] * m;
}

int polynomial_multiplication(double *a, int adeg, double *b, int bdeg, double *c, int cdeg)
{
	int ia, ib, deg, maxdeg=0;

	for (ia=0; ia <= adeg; ia++)
	{
		for (ib=0; ib <= bdeg; ib++)
		{
			deg = ia + ib;

			if (cdeg >= deg)
			{
				c[deg] += a[ia] * b[ib];

				if (c[deg] != 0.)
					maxdeg = MAXN(maxdeg, deg);
			}
		}
	}

	if (cdeg < maxdeg)
		fprintf_rl(stderr, "cdeg of %d < maxdeg of %d in polynomial_multiplication()\n", cdeg, maxdeg);

	return maxdeg;
}

xyi_t polynomial_multiplication_2d(double **a, xyi_t adeg, double **b, xyi_t bdeg, double **c, xyi_t cdeg)
{
	xyi_t ia, ib, ic, maxdeg=XYI0;

	for (ia.y=0; ia.y <= adeg.y; ia.y++)
		for (ia.x=0; ia.x <= adeg.x; ia.x++)
		{
			for (ib.y=0; ib.y <= bdeg.y; ib.y++)
				for (ib.x=0; ib.x <= bdeg.x; ib.x++)
				{
					ic = add_xyi(ia, ib);

					if (cdeg.y >= ic.y && cdeg.x >= ic.x)
					{
						c[ic.y][ic.x] += a[ia.y][ia.x] * b[ib.y][ib.x];

						if (c[ic.y][ic.x] != 0.)
							maxdeg = max_xyi(maxdeg, ic);
					}
				}
		}

	if (cdeg.y < maxdeg.y || cdeg.x < maxdeg.x)
		fprintf_rl(stderr, "cdeg of %d , %d < maxdeg of %d , %d in polynomial_multiplication()\n", cdeg.x, cdeg.y, maxdeg.x, maxdeg.y);

	return maxdeg;
}

double *polynomial_power(double *a, int adeg, int n, int *maxdegp)
{
	int i, maxdeg=0;
	double *c0, *c1;

	if (n==0)
	{
		c0 = calloc(1, sizeof(double));
		c0[0] = 1.;

		if (maxdegp)
			*maxdegp = maxdeg;
		return c0;
	}

	c1 = calloc(adeg*n+1, sizeof(double));
	c0 = calloc(adeg*n+1, sizeof(double));
	c0[0] = 1.;

	for (i=1; i <= n; i++)
	{
		memset(c1, 0, (adeg*n+1)*sizeof(double));
		maxdeg = polynomial_multiplication(a, adeg, c0, maxdeg, c1, adeg*n);

		swap_ptr(&c0, &c1);
	}

	free(c1);

	if (maxdegp)
		*maxdegp = maxdeg;
	return c0;
}

double **polynomial_power_2d(double **a, xyi_t adeg, int n, xyi_t *maxdegp)
{
	int i;
	xyi_t maxdeg=XYI0;
	double **c0, **c1;

	if (n==0)
	{
		c0 = (double **) calloc_2d_contig(1, 1, sizeof(double));
		c0[0][0] = 1.;

		if (maxdegp)
			*maxdegp = maxdeg;
		return c0;
	}

	c1 = (double **) calloc_2d_contig(adeg.y*n+1, adeg.x*n+1, sizeof(double));
	c0 = (double **) calloc_2d_contig(adeg.y*n+1, adeg.x*n+1, sizeof(double));
	c0[0][0] = 1.;

	for (i=1; i <= n; i++)
	{
		memset_2d(c1, 0, (adeg.x*n+1)*sizeof(double), adeg.y*n+1);
		maxdeg = polynomial_multiplication_2d(a, adeg, c0, maxdeg, c1, mul_xyi(adeg, set_xyi(n)));

		swap_ptr((void **) &c0, (void **) &c1);
	}

	free_2d(c1, 1);

	if (maxdegp)
		*maxdegp = maxdeg;
	return c0;
}

void polynomial_x_substitution(double *a, int adeg, double *xs, int xsdeg, double *c)
{
	int i, id, maxdeg;
	double *exs;

	if (xs[0]==0. && xs[1]==1.)		// if substitution isn't needed
	{
		for (id=0; id <= adeg; id++)
			c[id] += a[id];		// simply add the coefs as they are
		return;
	}

	for (id=0; id <= adeg; id++)
	{
		exs = polynomial_power(xs, xsdeg, id, &maxdeg);		// expand xs^id
		for (i=0; i <= maxdeg; i++)
			c[i] += a[id] * exs[i];				// multiply by the coefficient and add to c
		free(exs);
	}
}

void polynomial_x_substitution_2d(double **a, xyi_t adeg, double *xs, double *yso, xyi_t sdeg, double **c)
{
	xyi_t i, id, maxdegx, maxdegy, maxdeg;
	double **exs, **eys, **ys, **es;

	ys = (double **) array_1d_to_2d_contig(yso, sdeg.y+1, sizeof(double));

	for (id.y=0; id.y <= adeg.y; id.y++)
		for (id.x=0; id.x <= adeg.x; id.x++)
		{
			exs = polynomial_power_2d(&xs, xyi(sdeg.x, 0), id.x, &maxdegx);		// expand xs^id.x
			eys = polynomial_power_2d(ys, xyi(0, sdeg.y), id.y, &maxdegy);		// expand ys^id.y
			maxdeg = sub_xyi(mul_xyi(add_xyi(maxdegx, set_xyi(1)), add_xyi(maxdegy, set_xyi(1))), set_xyi(1));
			es = (double **) calloc_2d_contig(maxdeg.y+1, maxdeg.x+1, sizeof(double));

			maxdeg = polynomial_multiplication_2d(exs, maxdegx, eys, maxdegy, es, maxdeg);	// es = exs * eys

			polynomial_scalar_muladd_2d(es, maxdeg, a[id.y][id.x], c);			// scalar multiply by the coefficient and add to c

			free_2d(exs, 1);
			free_2d(eys, 1);
			free_2d(es, 1);
		}

	free(ys);
}

double *chebyshev_coefs(int degree)
{
	int i;
	double *t0, *t1, *t2, *p;
	double m[2] = { 0., 2. };	// 2*x + 0

	t0 = calloc(degree+1, sizeof(double));
	t0[0] = 1.;
	if (degree==0)
		return t0;

	t1 = calloc(degree+1, sizeof(double));
	t1[1] = 1.;
	if (degree==1)
	{
		free(t0);
		return t1;
	}

	t2 = calloc(degree+1, sizeof(double));

	for (i=2; i <= degree; i++)
	{
		// t2 = 2*x * t1 - t0
		memset(t2, 0, (degree+1) * sizeof(double));
		polynomial_multiplication(m, 1, t1, i-1, t2, degree);
		polynomial_subtraction(t2, degree, t0, i-2, t2);

		p = t0;
		t0 = t1;
		t1 = t2;
		t2 = p;
	}

	free(t0);
	free(t2);
	return t1;
}

const double *chebyshev_coefs_cached(int degree)
{
	int id;
	double *cc;
	static _Thread_local int cache_degree = -1, *index=NULL;
	static _Thread_local double *cache=NULL;
	static _Thread_local size_t cache_count=0, cache_as=0, index_as=0;

	// Update cache to include requested degree
	if (degree > cache_degree)
	{
		alloc_enough(&index, degree+1, &index_as, sizeof(int), 1.5);

		for (id=cache_degree+1; id <= degree; id++)
		{
			int pos = cache_count;
			cache_count += id+1;
			alloc_enough(&cache, cache_count, &cache_as, sizeof(double), 1.5);

			// Add coefs for degree id into cache
			cc = chebyshev_coefs(id);
			memcpy(&cache[pos], cc, (id+1) * sizeof(double));
			free(cc);

			// Index to beginning of cache
			index[id] = pos;
		}

		cache_degree = degree;
	}

	return &cache[index[degree]];
}


double **chebyshev_coefs_2d(xyi_t degree)
{
	xyi_t id;
	const double *tx, *ty;
	double **t;

	tx = chebyshev_coefs_cached(degree.x);
	ty = chebyshev_coefs_cached(degree.y);

	t = (double **) calloc_2d_contig(degree.y+1, degree.x+1, sizeof(double));

	for (id.y=0; id.y <= degree.y; id.y++)
		for (id.x=0; id.x <= degree.x; id.x++)
			t[id.y][id.x] = ty[id.y] * tx[id.x];

	return t;
}

double chebyshev_node(double degree, double node)		// node = 0,...,degree-1  FIXME degree isn't really degree but degree+1
{
	if (degree < 1. || node+0.5 < 0. || node+0.5 > degree)
		return 0.;

	return cos(pi * (node + 0.5) / degree);
}

ddouble_t chebyshev_node_q(double degree, double node)
{
	if (degree < 1. || node+0.5 < 0. || node+0.5 > degree)
		return Q_ZERO;

	return cos_q(div_qd(mul_qd(Q_PI, node + 0.5), degree));
}

void polynomial_fit_on_points(xy_t *p, double *c, int degree)
{
	int i, ii, id, j, deg;
	double *lj, mj, ci;

	memset(c, 0, (degree+1)*sizeof(double));
	lj = calloc(degree*2, sizeof(double));

	for (j=0; j < degree+1; j++)
	{
		// Prepare the (a*x + b) form Lagrange polynomial coeficients
		for (i=0; i < degree+1; i++)
		{
			if (i != j)
			{
				ii = i - (i > j);		// one place less if i is over the skipped i==j

				mj = 1. / (p[j].x - p[i].x);
				lj[ii*2+1] = mj;		// the a of (a*x + b)
				lj[ii*2] = -p[i].x * mj;	// the b of (a*x + b)
			}
		}

		// Expand the Lagrange polynomial
		for (i=0; i < (1 << degree); i++)
		{
			deg = 0;
			ci = 1.;

			for (id=0; id < degree; id++)			// go through each element of the multiplication being expanded
			{
				deg += get_bit(i, id);			// deg is the degree of the multiplication
				ci *= lj[id*2 + get_bit(i, id)];	// multiply all the elements together into a coefficient
			}

			c[deg] += ci * p[j].y;				// add the yj-multiplied coefficient to the correct degree
		}
	}

	free(lj);
}

void polynomial_fit_on_function(double (*f)(double), double start, double end, double *c, int degree)
{
	int i;
	xy_t *p;

	p = calloc(degree+1, sizeof(xy_t));

	// Compute the points
	for (i=0; i < degree+1; i++)
	{
		p[i].x = (end-start) * (0.5+0.5*chebyshev_node(degree+1, i)) + start;
		p[i].y = f(p[i].x);
	}

	// Fit
	polynomial_fit_on_points(p, c, degree);

	free(p);
}

double chebyshev_multiplier_by_dct(double *y, int p_count, int id, double (*cos_func)(double))	// look for the Chebyshev multiplier of degree id
{
	int i;
	double x, sum=0., freq = (double) id * 0.5 / (double) p_count;

	// DCT
	for (x=0.5, i=0; i < p_count; i++, x+=1.)
		sum += y[i] * cos_func(x * freq);

	// Sum division
	sum *= 1. / (double) p_count;
	if (id > 0)			// non-DC components need doubling
	    sum *= 2.;

	return sum;
}

ddouble_t chebyshev_multiplier_by_dct_q(ddouble_t *y, int p_count, int id)
{
	int i;
	ddouble_t x, sum=Q_ZERO, freq;

	freq = div_qd(ddouble((double) id * 0.5), (double) p_count);

	// DCT
	for (x=ddouble(0.5), i=0; i < p_count; i++, x = add_qd(x, 1.))
		sum = add_qq(sum, mul_qq(y[i], cos_tr_q(mul_qq(x, freq))));

	// Sum division
	sum = div_qd(sum, (double) p_count);
	if (id > 0)				// non-DC components need doubling
	    sum = mul_qd_simple(sum, 2.);

	return sum;
}

double chebyshev_multiplier_by_dct_2d(double **z, xyi_t p_count, xyi_t id)	// look for the Chebyshev multiplier of degree id
{
	xyi_t ip;
	double x, y, sum=0.;
	xy_t freq = mul_xy(xyi_to_xy(id), div_xy(set_xy(pi), xyi_to_xy(p_count)));

	// DCT
	for (y=0.5, ip.y=0; ip.y < p_count.y; ip.y++, y+=1.)
		for (x=0.5, ip.x=0; ip.x < p_count.x; ip.x++, x+=1.)
			sum += z[ip.y][ip.x] * cos(y * freq.y) * cos(x * freq.x);

	// Sum division
	sum *= 4. / (double) mul_x_by_y_xyi(p_count);
	if (id.y==0)
		sum *= 0.5;	// frequency 0 gets its sum halved

	if (id.x==0)
		sum *= 0.5;	// frequency 0 gets its sum halved

	return sum;
}

void polynomial_fit_on_points_by_dct(double *y, int p_count, double start, double end, double *c, int degree, double (*cos_func)(double))
{
	int id;
	double cm, xs[2];
	const double *cc;
	static _Thread_local double *ccm=NULL;
	static _Thread_local size_t ccm_as=0;

	memset(c, 0, (degree+1)*sizeof(double));
	alloc_enough(&ccm, degree+1, &ccm_as, sizeof(double), 1.5);

	// x substitution for the shifting
	xs[0] = -2.*start/(end-start) - 1.;
	xs[1] = 2. / (end-start);

	// Compute the coefficients
	for (id=0; id <= degree; id++)
	{
		cm = chebyshev_multiplier_by_dct(y, p_count, id, cos_func);	// get the Chebyshev multiplier for degree id
		cc = chebyshev_coefs_cached(id);				// get the default polynomial coeficients
		polynomial_scalar_mul(cc, id, cm, ccm);				// apply the multiplier
		polynomial_x_substitution(ccm, id, xs, 1, c);			// shift the polynomial and add to c
	}
}

double *polynomial_function_to_points(double (*f)(double), double start, double end, int p_count)
{
	int i;
	double *y = calloc(p_count, sizeof(double));

	// Compute the points
	for (i=0; i < p_count; i++)
		y[i] = f((end-start) * (0.5+0.5*chebyshev_node(p_count, i)) + start);

	return y;
}

ddouble_t *polynomial_function_to_points_dq(double (*f)(double), double start, double end, int p_count)
{
	int i;
	ddouble_t *y = calloc(p_count, sizeof(ddouble_t));

	// Compute the points
	for (i=0; i < p_count; i++)
		y[i] = ddouble(f((end-start) * (0.5+0.5*chebyshev_node(p_count, i)) + start));

	return y;
}

void polynomial_fit_on_function_by_dct_count(double (*f)(double), double start, double end, double *c, int degree, int p_count, double (*cos_func)(double))
{
	int i;
	double *y;

	// Compute the points
	y = polynomial_function_to_points(f, start, end, p_count);

	// Fit
	polynomial_fit_on_points_by_dct(y, p_count, start, end, c, degree, cos_func);
	free(y);
}

void polynomial_fit_on_function_by_dct(double (*f)(double), double start, double end, double *c, int degree, double (*cos_func)(double))
{
	polynomial_fit_on_function_by_dct_count(f, start, end, c, degree, 1000, cos_func);
}

void chebyshev_analysis_on_function(double (*f)(double), double start, double end, double *cm, int degree, int p_count, double (*cos_func)(double))
{
	int id;
	double *y;

	// Compute the points
	y = polynomial_function_to_points(f, start, end, p_count);

	// Compute the coefficients
	for (id=0; id <= degree; id++)
		cm[id] = chebyshev_multiplier_by_dct(y, p_count, id, cos_func);	// get the Chebyshev multiplier for degree id

	free(y);
}

void chebyshev_analysis_on_function_dq(double (*f)(double), double start, double end, ddouble_t *cm, int degree, int p_count)
{
	int id;
	ddouble_t *y;

	// Compute the points
	y = polynomial_function_to_points_dq(f, start, end, p_count);

	// Compute the coefficients
	for (id=0; id <= degree; id++)
		cm[id] = chebyshev_multiplier_by_dct_q(y, p_count, id);	// get the Chebyshev multiplier for degree id

	free(y);
}

void chebyshev_coefs_to_polynomial_2d(double **cm, xyi_t degree, xy_t start, xy_t end, double **c)
{
	xyi_t id;
	double **cc, xs[2], ys[2];

	memset_2d(c, 0, (degree.x+1)*sizeof(double), degree.y+1);

	// x and y substitution for the shifting
	xs[0] = -2.*start.x/(end.x-start.x) - 1.;
	ys[0] = -2.*start.y/(end.y-start.y) - 1.;
	xs[1] = 2. / (end.x-start.x);
	ys[1] = 2. / (end.y-start.y);

	// Transform each Chebyshev coef into a polynomial
	for (id.y=0; id.y <= degree.y; id.y++)
		for (id.x=0; id.x <= degree.x; id.x++)
		{
			cc = chebyshev_coefs_2d(id);					// get the default polynomial coeficients
			polynomial_scalar_mul_2d(cc, id, cm[id.y][id.x], cc);		// apply the multiplier
			polynomial_x_substitution_2d(cc, id, xs, ys, xyi(1, 1), c);	// shift the polynomial and add to c
			free_2d(cc, 1);
		}
}

double **chebyshev_fit_on_points_by_dct_2d(double **z, xyi_t p_count, xyi_t degree)
{
	xyi_t id;
	double **cm = (double **) calloc_2d_contig(degree.y+1, degree.x+1, sizeof(double));

	// Compute the coefficients
	for (id.y=0; id.y <= degree.y; id.y++)
		for (id.x=0; id.x <= degree.x; id.x++)
			cm[id.y][id.x] = chebyshev_multiplier_by_dct_2d(z, p_count, id);		// get the Chebyshev multiplier for degree id

	return cm;
}

double **polynomial_fit_on_points_by_dct_2d(double **z, xyi_t p_count, xy_t start, xy_t end, double **c, xyi_t degree)
{
	xyi_t id;
	double **cm;

	if (c==NULL)
		c = (double **) calloc_2d_contig(degree.y+1, degree.x+1, sizeof(double));

	// Compute the coefficients
	cm = chebyshev_fit_on_points_by_dct_2d(z, p_count, degree);

	// Convert Chebyshef coefficients to polynomial coefficients
	chebyshev_coefs_to_polynomial_2d(cm, degree, start, end, c);

	free_2d(cm, 1);

	return c;
}

double **polynomial_function_to_point_2d(double (*f)(double, double), xyi_t p_count, xy_t start, xy_t end)
{
	xyi_t ip;
	double **z = (double **) calloc_2d_contig(p_count.y, p_count.x, sizeof(double));

	// Compute the points
	for (ip.y=0; ip.y < p_count.y; ip.y++)
		for (ip.x=0; ip.x < p_count.x; ip.x++)
			z[ip.y][ip.x] = f((end.x-start.x) * (0.5+0.5*chebyshev_node(p_count.x, ip.x)) + start.x, (end.y-start.y) * (0.5+0.5*chebyshev_node(p_count.y, ip.y)) + start.y);

	return z;
}

double **polynomial_fit_on_function_by_dct_2d(double (*f)(double, double), xy_t start, xy_t end, double **c, xyi_t degree)
{
	xyi_t p_count = set_xyi(1000);
	xyi_t ip;
	double **z;

	if (c==NULL)
		c = (double **) calloc_2d_contig(degree.y+1, degree.x+1, sizeof(double));

	// Compute the points
	z = polynomial_function_to_point_2d(f, p_count, start, end);

	// Fit
	polynomial_fit_on_points_by_dct_2d(z, p_count, start, end, c, degree);
	free_2d(z, 1);

	return c;
}

/*
v0 = 10*x
plot v1 = erf(v0)
plot v2 = -1.8812e-10*v0^7 + 5.95468e-07*v0^5 - 0.000591814*v0^3 + 0.211477*v0
plot v3 = 4.60844e-11*v0^7 - 1.46041e-07*v0^5 + 0.000141684*v0^3 - 0.0401948*v0
plot v4 = (v1 - (v2 + c0*v3))*10


plot v0 = exp(-x*x*100)
v1 = 12.3198*x^8 - 27.945*x^6 + 21.227*x^4 - 6.03238*x^2 + 0.476735
plot v2 = cos(acos(x)*  0)*0.120757+
cos(acos(x)*  2)*-0.123411+cos(acos(x)*  4)*0.0832623+
cos(acos(x)*  6)*-0.0591896+cos(acos(x)*  8)*0.0425347+
cos(acos(x)* 10)*-0.0304192+cos(acos(x)* 12)*0.0214769+
cos(acos(x)* 14)*-0.0148945+cos(acos(x)* 16)*0.0101084+
cos(acos(x)* 18)*-0.0066917+cos(acos(x)* 20)*0.00430733+
cos(acos(x)* 22)*-0.00268643+cos(acos(x)* 24)*0.0016166+
cos(acos(x)* 26)*-0.000933467+cos(acos(x)* 28)*0.000513242+
cos(acos(x)* 30)*-0.000265594+cos(acos(x)* 32)*0.000126873
plot v3 = abs(v0-v1)/v2*0.3066*1
v4 = 6.933738469e-1 +x*-1.537650315e-3 +x^2*-1.384847511e+1
+x^3*8.228637481e-2 +x^4*6.131494002e+1 +x^5*-5.585291021e-1
+x^6*-9.252052240e+1 +x^7*7.844065307e-1 +x^8*4.436068364e+1
plot v5 = abs(v0-v4)*1
plot v6 = 1e-9/(x-c0)

plot v0 = gaussian((0.5+0.5*x)*10)
plot v1 = (3.24426*x^7 - 0.635562*x^6 - 6.03683*x^5 + 1.69759*x^4
 + 2.55079*x^3 - 0.548307*x^2 - 0.260136*x + 0.0219204 - v0)*10
plot v3 = (cos(acos(x)*  0)*0.0338554+
cos(acos(x)*  1)*-0.0188564+cos(acos(x)*  2)*0.00204312+
cos(acos(x)*  3)*0.00394375+cos(acos(x)*  4)*-0.00429958+
cos(acos(x)*  5)*0.00256535+cos(acos(x)*  6)*-0.000839876+
cos(acos(x)*  7)*-0.000108108+cos(acos(x)*  8)*0.000347918+
cos(acos(x)*  9)*-0.000237706)
plot v4 = (1.639233702893998064336560647631011889651e-2
+x*-2.928766252335909864193805457528753979412e-1
+x^2*-4.474539206131717132308014291922265223296e-1
+x^3*2.787075293253191929012413648529849594347
+x^4*1.426790345951435341016863501393847789548
+x^5*-6.479284939695181168932746533466860369859
+x^6*-4.536696035358643058644213203913443690196e-1
+x^7*3.485086271675580226339713430689886173452 - v0) * 10
*/

/*double minmax_find_k(int p_count, double *y, double *a, double *b)	// find k that minimises the difference between y and a+k*b
{
	int i, it;
	double k0=0., k1=0., k2=1.;
	double err0, err1, err2;
	double step=4., decrement=1./2.;

	// Initial error
	for (err0=0., i=0; i < p_count; i++)
		err0 = MAXN(err0, fabs(y[i] - a[i]));
	err2 = err1 = err0;

	for (it=0; it < 200; it++)
	{
		// Eval error
		for (err2=0., i=0; i < p_count; i++)
			err2 = MAXN(err2, fabs(y[i] - (a[i] + k2*b[i])));

		// Check if the precision is high enough
		if (err0 / err1 - 1. < 1e-8 && err1 / err2 - 1. < 1e-8 && err0 != err1)
			return k1;

		if (err2 <= err1)			// if the error is still going down
		{
			err0 = err1;
			err1 = err2;
			k0 = k1;
			k1 = k2;
			k2 *= step;			// continue forward
		}
		else					// if the error is now going back up
		{
			k1 = k0;
			if (k0==0.)
				k2 *= 1./8.;
			else
				k2 = k0;		// go back to k0
			err2 = err1 = err0;
			step = pow(step, decrement);	// lower the step
			k2 *= step;
		}
	}

	return k2;
}*/

double minmax_find_k(int p_count, double *y, double *a, double *b, double *an, double *ye, int degree)
{
	int i, it;
	double k0=0., k1=0., k2=1.;
	double err0, err1, err2;
	double step=4., decrement=1./2.;

	// Initial error
	for (err0=0., i=0; i < p_count; i++)
		err0 = MAXN(err0, fabs(y[i] - a[i]));
	err2 = err1 = err0;

	for (it=0; it < 200; it++)
	{
		// Generate an = a + k*b
		for (i=0; i < p_count; i++)
			an[i] = a[i] + k2 * b[i];

		// Fit an to generate ye
		memset(ye, 0, p_count * sizeof(double));
		for (int id=0; id < degree+1; id++)
		{
			double xi, freq = pi * (double) id / (double) p_count;
			double cm = chebyshev_multiplier_by_dct(an, p_count, id, cos_tr);

			for (xi=0.5, i=0; i < p_count; i++, xi+=1.)
				ye[i] += cos(xi * freq) * cm;
		}

		// Eval error
		for (err2=0., i=0; i < p_count; i++)
			err2 = MAXN(err2, fabs(y[i] - ye[i]));

		// Check if the precision is high enough
		if (err0 / err1 - 1. < 1e-8 && err1 / err2 - 1. < 1e-8 && err0 != err1)
			return k1;

		if (err2 <= err1)			// if the error is still going down
		{
			err0 = err1;
			err1 = err2;
			k0 = k1;
			k1 = k2;
			k2 *= step;			// continue forward
		}
		else					// if the error is now going back up
		{
			k1 = k0;
			if (k0==0.)
				k2 *= 1./8.;
			else
				k2 = k0;		// go back to k0
			err2 = err1 = err0;
			step = pow(step, decrement);	// lower the step
			k2 *= step;
		}
	}

	return k2;
}

/*
plot v1 = graph(3+floor(c0)*5, x)
c0 = 0 0 59
*/

void error_curve_transform(double (*f)(double), int p_count, double start, double end, double *c, int degree, double *ye, double *env, double *env2, double *b, double *x, int it)
{
	int i;
	double mx, v, env_sum, env_mul, off;
	char name[64];

	// Generate the imaginary part of ye for the error envelope
	memset(env, 0, p_count * sizeof(double));
	fprintf_rl(stdout, "ye coefs:\n");
	for (int id=0; id < MINN(p_count, (degree+1)*8); id++)
	{
		double xi, freq = pi * (double) id / (double) p_count;
		double cm = chebyshev_multiplier_by_dct(ye, p_count, id, cos_tr);

		if (fabs(cm) > 1e-4)
			fprintf_rl(stdout, "cos(acos(x)*%3d)*%g+\n", id, cm);
		for (xi=0.5, i=0; i < p_count; i++, xi+=1.)
			env[i] += sin(xi * freq) * cm;
	}

	off = sqrt(sq(ye[0]) + sq(env[0]));

	// Generate reciprocal of the error envelope
	for (i=0; i < p_count; i++)
		env[i] = sqrt(sq(ye[i]) + sq(env[i]));
	math_graph_add(x, env, p_count, sprintf_ret(name, "Envelope #%d", it));

	// Offset the envelope
	for (i=0; i < p_count; i++)
		if (it > 20)
			env2[i] = env[i];
		else
			env2[i] = env[i]*0.1 + off;

	// Cumulate and normalise the envelope to produce a position map
	for (env_sum=0., i=0; i < p_count; i++)
		env_sum += env2[i];
	env_mul = 1. / env_sum;

	for (env_sum=0., i=0; i < p_count; i++)
	{
		v = env2[i];
		env_sum += v;
		mx = (env_sum - 0.5*v) * env_mul;			// mapped x within [0 , 1]
		mx = (end-start) * (0.5+0.5*cos(pi * mx)) + start;	// mapped x within [start , end]

		// Generate the b curve
		b[i] = -(f(mx) - eval_polynomial(mx, c, degree)) / env[i];
	}

	math_graph_add(x, b, p_count, sprintf_ret(name, "B curve #%d", it));
}

void polynomial_fit_on_function_by_dct_minmax(double (*f)(double), double start, double end, double *c, int degree)
{
	int i, it, p_count = 10000;
	char *str;
	const char x_str[] = "x";
	char name[64];
	double v, k, err;
	double *x = calloc(p_count, sizeof(double));
	double *y = calloc(p_count, sizeof(double));
	double *a = calloc(p_count, sizeof(double));
	double *an = calloc(p_count, sizeof(double));
	double *ye = calloc(p_count, sizeof(double));
	double *env = calloc(p_count, sizeof(double));
	double *env2 = calloc(p_count, sizeof(double));
	double *b = calloc(p_count, sizeof(double));
	double *ce = calloc(degree+1, sizeof(double));

	free_math_graph_array();

	// Compute the points
	for (i=0; i < p_count; i++)
	{
		x[i] = (end-start) * (0.5+0.5*chebyshev_node(p_count, i)) + start;
		y[i] = f(x[i]);
	}
	math_graph_add(x, y, p_count, "Original curve to fit");
//	math_graph_add(x, y, p_count, sprintf_ret(name, ""));

	// Fit
	polynomial_fit_on_points_by_dct(y, p_count, start, end, c, degree, cos_tr);
	fprintf_rl(stdout, "c = %s\n", str=print_polynomial(c, degree, x_str));
	free(str);
	math_graph_add_y(c, degree+1, sprintf_ret(name, "Original polynomial coefs"));

	// Eval error
	err = get_polynomial_error_from_points(x, y, p_count, c, degree, NEGMODE);
	fprintf_rl(stdout, "Preoptimisation error %g\n", err);

	for (it=0; it < 60; it++)
	{
		err = get_polynomial_error_from_points(x, y, p_count, c, degree, NEGMODE);
		fprintf_rl(stdout, "%d	error %g\n", it, err);

		// Generate the error curve
		for (i=0; i < p_count; i++)
		{
			a[i] = eval_polynomial(x[i], c, degree);
			ye[i] = y[i] - a[i];
		}

		math_graph_add(x, a, p_count, sprintf_ret(name, "Polynomial curve #%d", it));
		math_graph_add(x, ye, p_count, sprintf_ret(name, "Error curve #%d", it));

		// Transform the error curve
		error_curve_transform(f, p_count, start, end, c, degree, ye, env, env2, b, x, it);

		// Find the optimal k for a+k*b
		k = minmax_find_k(p_count, y, a, b, an, ye, degree);
		fprintf_rl(stdout, "	k = %g\n", k);
		// dampen k
		k = k * 0.1;

		// a' = a + k*b
		for (i=0; i < p_count; i++)
			a[i] += k * b[i];
		math_graph_add(x, a, p_count, sprintf_ret(name, "a' = a + %.4g*b curve #%d", k, it));

		// Fit the curve
		polynomial_fit_on_points_by_dct(a, p_count, start, end, c, degree, cos_tr);
		fprintf_rl(stdout, "	c = %s\n", str=print_polynomial(c, degree, x_str));
		free(str);
	}

	free(x);
	free(y);
	free(a);
	free(an);
	free(ye);
	free(env);
	free(env2);
	free(b);
	free(ce);
}

double reduce_digits(double (*f)(double), double segstart, double segend, double *c, const int degree, int errmode, double added_error_thresh, double digits)
{
	int i;
	double err0, err1, err_orig;
	double l, m, r=0., rp;

	err_orig = get_polynomial_error(f, segstart, segend, c, degree, NEGMODE);

	for (i=0; i <= degree; i++)		// go through every coef to round it
	{
		err0 = get_polynomial_error(f, segstart, segend, c, degree, NEGMODE);

		if (c[i] != 0.)			// if the coef is not 0
		{
			l = fabs(c[i]);			// -0.0007 -> 0.0007
			l = log10(l);			// 0.0007 -> -3.15
			l = floor(l);			// -3.15 -> -4
			l -= digits;			// -4 -> -24

			m = pow(10., l);		// -24 -> 1e-24

			while (1)
			{
				rp = r;			// copy the previous result

				r = c[i] / m;		// -0.0007 / 1e-24 -> -7e20
				r = nearbyint(r);	// -7e20
				r *= m;			// -7e20 * 1e-24 -> -0.0007
				swap_double(&c[i], &r);	// set the rounded coef into the coef array for evaluation

				err1 = get_polynomial_error(f, segstart, segend, c, degree, NEGMODE);

				if (err1 > err0 * added_error_thresh || c[i]==0.)	// if the added error is over the threshold
				{
					if (err1 > err0 * added_error_thresh)
						c[i] = rp;	// restore the previous rounding so the error is less than the threshold
					break;
				}
				else
					swap_double(&c[i], &r);		// restore the unrounded coef

				m *= 10.;		// 1e-24 -> 1e-23
			}
		}
	}

	return get_polynomial_error(f, segstart, segend, c, degree, NEGMODE);
}

double reduce_digits_2d(double (*f)(double,double), xy_t segstart, xy_t segend, double **c, const xyi_t degree, int errmode, double added_error_thresh, double digits)
{
	xyi_t ip;
	double err0, err1, err_orig;
	double l, m, r=0., rp;

	err_orig = get_polynomial_error_2d(f, segstart, segend, c, degree, NEGMODE);

	for (ip.y=0; ip.y <= degree.y; ip.y++)		// go through every coef to round it
		for (ip.x=0; ip.x <= degree.x; ip.x++)
		{
			err0 = get_polynomial_error_2d(f, segstart, segend, c, degree, NEGMODE);

			if (c[ip.y][ip.x] != 0.)			// if the coef is not 0
			{
				l = fabs(c[ip.y][ip.x]);			// -0.0007 -> 0.0007
				l = log10(l);			// 0.0007 -> -3.15
				l = floor(l);			// -3.15 -> -4
				l -= digits;			// -4 -> -24

				m = pow(10., l);		// -24 -> 1e-24

				while (1)
				{
					rp = r;			// copy the previous result

					r = c[ip.y][ip.x] / m;		// -0.0007 / 1e-24 -> -7e20
					r = nearbyint(r);	// -7e20
					r *= m;			// -7e20 * 1e-24 -> -0.0007
					swap_double(&c[ip.y][ip.x], &r);	// set the rounded coef into the coef array for evaluation

					err1 = get_polynomial_error_2d(f, segstart, segend, c, degree, NEGMODE);

					if (err1 > err0 * added_error_thresh || c[ip.y][ip.x]==0.)	// if the added error is over the threshold
					{
						if (err1 > err0 * added_error_thresh)
							c[ip.y][ip.x] = rp;	// restore the previous rounding so the error is less than the threshold
						break;
					}
					else
						swap_double(&c[ip.y][ip.x], &r);		// restore the unrounded coef

					m *= 10.;		// 1e-24 -> 1e-23
				}
			}
		}

	return get_polynomial_error_2d(f, segstart, segend, c, degree, NEGMODE);
}
