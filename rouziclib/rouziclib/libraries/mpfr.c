#ifdef RL_MPFR

real_t *r_init_array(int count)
{
	int i;
	real_t *a;

	a = calloc(count, sizeof(real_t));

	for (i=0; i < count; i++)
		r_init(a[i]);

	return a;
}

void r_zero_array(real_t *a, int count)
{
	int i;

	for (i=0; i < count; i++)
		r_setd(a[i], 0.);
}

void r_free_array(real_t **a, int count)
{
	int i;

	for (i=0; i < count; i++)
		r_free((*a)[i]);

	free_null((void **) a);
}

void r_flipsign(real_t y, real_t x)
{
	int new_sign;

	new_sign = (mpfr_signbit(x) == 0);
	mpfr_setsign(y, x, new_sign, MPFR_RNDN);
}

void r_gaussian(real_t y, real_t x)
{
	r_set(y, x);
	r_mul(y, y);
	r_flipsign(y, y);
	r_exp(y, y);
}

void r_mix(real_t x, double t, real_t start, real_t end)	// x = (end-start)*t + start
{
	r_rsub(x, end, start);
	r_muld(x, t);
	r_add(x, start);
}

ddouble_t mpfr_to_ddouble(real_t v)
{
	ddouble_t r;
	real_t d;

	// Make hi part
	r.hi = r_todouble(v);

	// Make lo part by difference between v and r.hi
	r_init(d);
	r_setd(d, r.hi);
	r_rsub(d, v, d);		// difference (remainder)
	r.lo = r_todouble(d);
	r_free(d);

	return r;
}

void ddouble_to_mpfr(real_t r, ddouble_t v)
{
	r_setd(r, v.hi);
	r_addd(r, v.lo);
}

double diff_mpfr_ddouble(real_t m, ddouble_t q)
{
	double r;
	real_t d;

	r_init(d);
	ddouble_to_mpfr(d, q);
	r_sub(d, m);
	r = r_todouble(d);
	r_free(d);
	return r;
}

#endif
