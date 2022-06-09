#ifndef RL_EXCL_CFFTPACK

#include "orig/fftpack_float.c"
#include "orig/fftpack_double.c"

void cfft_plan_free(cfft_plan_t *plan)
{
	if (plan==NULL)
		return ;

	free(plan->workf);
	free(plan->workd);
	free(plan->savef);
	free(plan->saved);
	memset(plan, 0, sizeof(cfft_plan_t));
}

cfft_plan_t cfft_1D_create_plan(int n, const size_t elemsize)
{
	cfft_plan_t plan={0};
	int ret = 0;

	if (n == 0)
		return plan;

	plan.lensav = n*2 + (int) log2((double) n) + 8;
	plan.lenwork = 2 * n;
	plan.dim = xyi(n, 1);
	plan.elemsize = elemsize;

	if (elemsize == sizeof(float))
	{
		plan.savef = calloc(plan.lensav, sizeof(float));
		plan.workf = calloc(plan.lenwork, sizeof(float));

		cfft1i_f(&n, plan.savef, &plan.lensav, &ret);
	}
	else
	{
		plan.saved = calloc(plan.lensav, sizeof(double));
		plan.workd = calloc(plan.lenwork, sizeof(double));

		cfft1i_d(&n, plan.saved, &plan.lensav, &ret);
	}

	if (ret)
	{
		fprintf_rl(stderr, "cfft1i_() returned %d in cfft_1D_create_plan()\n", ret);
		cfft_plan_free(&plan);
	}

	return plan;
}

cfft_plan_t cfft_2D_create_plan(xyi_t dim, const size_t elemsize)
{
	cfft_plan_t plan={0};
	int ret = 0;

	if (is0_xyi(dim))
		return plan;

	plan.lensav = dim.x*2 + (int) log2((double) dim.x) + dim.y*2 + (int) log2((double) dim.y) + 8;
	plan.lenwork = 2 * dim.x * dim.y;
	plan.dim = dim;
	plan.elemsize = elemsize;

	if (elemsize == sizeof(float))
	{
		plan.savef = calloc(plan.lensav, sizeof(float));
		plan.workf = calloc(plan.lenwork, sizeof(float));

		cfft2i_f(&dim.x, &dim.y, plan.savef, &plan.lensav, &ret);
	}
	else
	{
		plan.saved = calloc(plan.lensav, sizeof(double));
		plan.workd = calloc(plan.lenwork, sizeof(double));

		cfft2i_d(&dim.x, &dim.y, plan.saved, &plan.lensav, &ret);
	}

	if (ret)
	{
		fprintf_rl(stderr, "cfft2i_() returned %d in cfft_2D_create_plan()\n", ret);
		cfft_plan_free(&plan);
	}

	return plan;
}

int cfft_1D(cfft_plan_t *plan, void *data, const int way)
{
	int ret = 0, inc=1;

	if (plan==NULL || data==NULL)
		return -1;

	if (plan->elemsize == sizeof(float))
	{
		if (way==0)
			cfft1f_f(&plan->dim.x, &inc, (fft_complexf_t *) data, &plan->dim.x, plan->savef, &plan->lensav, plan->workf, &plan->lenwork, &ret);
		else
			cfft1b_f(&plan->dim.x, &inc, (fft_complexf_t *) data, &plan->dim.x, plan->savef, &plan->lensav, plan->workf, &plan->lenwork, &ret);
	}
	else
	{
		if (way==0)
			cfft1f_d(&plan->dim.x, &inc, (fft_complexd_t *) data, &plan->dim.x, plan->saved, &plan->lensav, plan->workd, &plan->lenwork, &ret);
		else
			cfft1b_d(&plan->dim.x, &inc, (fft_complexd_t *) data, &plan->dim.x, plan->saved, &plan->lensav, plan->workd, &plan->lenwork, &ret);
	}

	return ret;
}

int cfft_2D(cfft_plan_t *plan, void *data, const int way)
{
	int ret = 0;

	if (plan==NULL || data==NULL)
		return -1;

	if (plan->elemsize == sizeof(float))
	{
		if (way==0)
			cfft2f_f(&plan->dim.x, &plan->dim.x, &plan->dim.y, (fft_complexf_t *) data, plan->savef, &plan->lensav, plan->workf, &plan->lenwork, &ret);
		else
			cfft2b_f(&plan->dim.x, &plan->dim.x, &plan->dim.y, (fft_complexf_t *) data, plan->savef, &plan->lensav, plan->workf, &plan->lenwork, &ret);
	}
	else
	{
		if (way==0)
			cfft2f_d(&plan->dim.x, &plan->dim.x, &plan->dim.y, (fft_complexd_t *) data, plan->saved, &plan->lensav, plan->workd, &plan->lenwork, &ret);
		else
			cfft2b_d(&plan->dim.x, &plan->dim.x, &plan->dim.y, (fft_complexd_t *) data, plan->saved, &plan->lensav, plan->workd, &plan->lenwork, &ret);
	}

	return ret;
}

// Processing

fft_complexf_t cfft_complex_mul_f(fft_complexf_t a, fft_complexf_t b)
{
	fft_complexf_t r={0};

	r.r = a.r*b.r - a.i*b.i;
	r.i = a.r*b.i + a.i*b.r;

	return r;
}

fft_complexd_t cfft_complex_mul_d(fft_complexd_t a, fft_complexd_t b)
{
	fft_complexd_t r={0};

	r.r = a.r*b.r - a.i*b.i;
	r.i = a.r*b.i + a.i*b.r;

	return r;
}

void cfft_complex_mul_2D_f(void *va, void *vb, void *vr, xyi_t dim)
{
	int i, count;
	fft_complexf_t *a = va, *b = vb, *r = vr;

	count = mul_x_by_y_xyi(dim);

	for (i=0; i < count; i++)
		r[i] = cfft_complex_mul_f(a[i], b[i]);
}

void cfft_complex_mul_2D_d(void *va, void *vb, void *vr, xyi_t dim)
{
	int i, count;
	fft_complexd_t *a = va, *b = vb, *r = vr;

	count = mul_x_by_y_xyi(dim);

	for (i=0; i < count; i++)
		r[i] = cfft_complex_mul_d(a[i], b[i]);
}

void cfft_copy_r2c_pad(void *in, const size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, xyi_t in_dim, xyi_t out_dim)	// makes a 0-padded complex copy
{
	xyi_t ip;
	float *inf;
	double *ind;
	fft_complexf_t *outf;
	fft_complexd_t *outd;

	alloc_enough(pout, mul_x_by_y_xyi(out_dim), out_as, out_elemsize*2, 1.);
	memset(*pout, 0, mul_x_by_y_xyi(out_dim) * out_elemsize*2);
	outf = *pout;
	outd = *pout;
	inf = in;
	ind = in;

	if (out_elemsize == sizeof(float))
	{
		if (in_elemsize == sizeof(float))
			for (ip.y=0; ip.y < in_dim.y; ip.y++)
				for (ip.x=0; ip.x < in_dim.x; ip.x++)
					outf[ip.y*out_dim.x + ip.x].r = inf[ip.y*in_dim.x + ip.x];
		else
			for (ip.y=0; ip.y < in_dim.y; ip.y++)
				for (ip.x=0; ip.x < in_dim.x; ip.x++)
					outf[ip.y*out_dim.x + ip.x].r = ind[ip.y*in_dim.x + ip.x];
	}
	else
	{
		if (in_elemsize == sizeof(float))
			for (ip.y=0; ip.y < in_dim.y; ip.y++)
				for (ip.x=0; ip.x < in_dim.x; ip.x++)
					outd[ip.y*out_dim.x + ip.x].r = inf[ip.y*in_dim.x + ip.x];
		else
			for (ip.y=0; ip.y < in_dim.y; ip.y++)
				for (ip.x=0; ip.x < in_dim.x; ip.x++)
					outd[ip.y*out_dim.x + ip.x].r = ind[ip.y*in_dim.x + ip.x];
	}
}

void cfft_copy_c2r(void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, xyi_t dim)
{
	int i, count = mul_x_by_y_xyi(dim);
	fft_complexf_t *inf = in;
	fft_complexd_t *ind = in;
	float *outf = out;
	double *outd = out;

	if (out_elemsize == sizeof(float))
	{
		if (in_elemsize == sizeof(float))
			for (i=0; i < count; i++)
				outf[i] = inf[i].r;
		else
			for (i=0; i < count; i++)
				outf[i] = ind[i].r;
	}
	else
	{
		if (in_elemsize == sizeof(float))
			for (i=0; i < count; i++)
				outd[i] = inf[i].r;
		else
			for (i=0; i < count; i++)
				outd[i] = ind[i].r;
	}
}

void cfft_1D_c2c_fft(cfft_plan_t *plan, void *array, const size_t elemsize, int n)	// when the input is already alloced, padded and complex
{
	if (equal_xyi(plan->dim, xyi(n, 1))==0)		// if we must recreate the plan
	{
		cfft_plan_free(plan);
		*plan = cfft_1D_create_plan(n, elemsize);
	}

	cfft_1D(plan, array, 0);
}

void cfft_1D_r2c_padded_fft(cfft_plan_t *plan, void *in, size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, int in_n, int out_n)	// every arg besides in and *_n can be uninitialised
{
	cfft_copy_r2c_pad(in, in_elemsize, pout, out_elemsize, out_as, xyi(in_n, 1), xyi(out_n, 1));	// 2D real -> 2D complex and padded

	cfft_1D_c2c_fft(plan, *pout, out_elemsize, out_n);
}

void cfft_2D_r2c_padded_fft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void **pout, const size_t out_elemsize, size_t *out_as, xyi_t in_dim, xyi_t out_dim)	// every arg besides in and *_dim can be uninitialised
{
	cfft_copy_r2c_pad(in, in_elemsize, pout, out_elemsize, out_as, in_dim, out_dim);	// 2D real -> 2D complex and padded

	if (equal_xyi(plan->dim, out_dim)==0)			// if we must recreate the plan
	{
		cfft_plan_free(plan);
		*plan = cfft_2D_create_plan(out_dim, out_elemsize);
	}

	cfft_2D(plan, *pout, 0);
}

void cfft_1D_c2r_full_ifft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, int n)	// the IFFT is still in-place for in
{
	xyi_t dim = xyi(n, 1);

	if (equal_xyi(plan->dim, dim)==0)			// if we must recreate the plan
	{
		cfft_plan_free(plan);
		*plan = cfft_1D_create_plan(n, out_elemsize);
	}

	cfft_1D(plan, in, 1);

	cfft_copy_c2r(in, in_elemsize, out, out_elemsize, dim);
}

void cfft_2D_c2r_full_ifft(cfft_plan_t *plan, void *in, const size_t in_elemsize, void *out, const size_t out_elemsize, xyi_t dim)	// the IFFT is still in-place for in
{
	if (equal_xyi(plan->dim, dim)==0)			// if we must recreate the plan
	{
		cfft_plan_free(plan);
		*plan = cfft_2D_create_plan(dim, out_elemsize);
	}

	cfft_2D(plan, in, 1);

	cfft_copy_c2r(in, in_elemsize, out, out_elemsize, dim);
}

#endif
