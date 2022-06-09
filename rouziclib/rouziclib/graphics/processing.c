void gaussian_blur(float *a, float *b, xyi_t dim, const int channels, double radius)
{
	int i, j, ic, ix, iy, jx, jy, in_place=0;
	double *gk, sum;
	int gks, start, stop;
	float *column;
	int w, h;
	const int edge_norm = 1;	// FIXME

	w = dim.x;
	h = dim.y;

	if (a==NULL || b==NULL)
	{
		fprintf_rl(stderr, "gaussian_blur(0x%p, 0x%p, ... ) can't use NULL buffers.\n", a, b);
		return ;
	}

	if (a==b)
	{
		in_place = 1;
		b = calloc(w*h*channels, sizeof(float));
	}
	else
		memset(b, 0, w*h*channels*sizeof(float));

	gks = floor(GAUSSRAD_HQ * radius) + 1.;
	gk = calloc (gks, sizeof(double));

	for (i=0; i<gks; i++)
	{
		gk[i] = gaussian((double) i / radius);
		//gk[i] = gaussian((double) i / radius) / radius / sqrt(pi);
		//gk[i] = sinc((double) i, 0.3/4.) * blackman((double) i, gks);
		//fprintf_rl(stdout, "gk[%d] = %g\n", i, gk[i]);
	}

	// calculate proper kernel gain
	sum = 0.;
	for (i=-gks+1; i<gks; i++)
		sum += gk[abs(i)];
	sum = 1./sum;

	for (i=0; i<gks; i++)
		gk[i] *= sum;


	for (iy=0; iy<h; iy++)		// horizontal blurring
	{
		for (ix=0; ix<w; ix++)
		{
			start = MAXN (0, ix-(gks-1));
			stop = MINN (w-1, ix+(gks-1));

			for (jx=start; jx<=stop; jx++)
			{
				i = (iy*w + ix) * channels;
				j = (iy*w + jx) * channels;

				for (ic=0; ic < channels; ic++)
					b[i + ic] += gk[abs(jx-ix)] * a[j + ic];
			}
		}
	}

	column = calloc (h*channels, sizeof(float));

	for (ix=0; ix<w; ix++)
	{
		for (iy=0; iy<h; iy++)
		{
			// copy pixel from b into the column buffer
			memcpy(&column[iy*channels], &b[(iy*w + ix)*channels], channels*sizeof(float));
			memset(&b[(iy*w + ix)*channels], 0, channels*sizeof(float));
		}

		for (iy=0; iy<h; iy++)		// vertical blurring
		{
			start = MAXN (0, iy-(gks-1));
			stop = MINN (h-1, iy+(gks-1));
			i = (iy*w + ix) * channels;

			for (jy=start; jy<=stop; jy++)
				for (ic=0; ic < channels; ic++)
					b[i + ic] += gk[abs(jy-iy)] * column[(jy*channels)+ic];
		}
	}

	if (edge_norm)
	{
		for (ix=0; ix<w; ix++)
		{
			start = ix-(gks-1);
			stop = ix+(gks-1);

			if (start < 0 || stop > w-1)			// if we're on the edges
			{
				start = MAXN(0, start);
				stop = MINN(w-1, stop);

				sum = 0.;
				for (jx=start; jx<=stop; jx++)
					sum += gk[abs(jx-ix)];
				sum = 1./sum;

				for (iy=0; iy<h; iy++)
					for (ic=0; ic < channels; ic++)
						b[(iy*w + ix) * channels + ic] *= sum;
			}
		}

		for (iy=0; iy<h; iy++)
		{
			start = iy-(gks-1);
			stop = iy+(gks-1);

			if (start < 0 || stop > h-1)			// if we're on the edges
			{
				start = MAXN(0, start);
				stop = MINN(h-1, stop);

				sum = 0.;
				for (jy=start; jy<=stop; jy++)
					sum += gk[abs(jy-iy)];
				sum = 1./sum;

				for (ix=0; ix<w; ix++)
					for (ic=0; ic < channels; ic++)
						b[(iy*w + ix) * channels + ic] *= sum;
			}
		}
	}

	free (column);
	free (gk);

	if (in_place)
	{
		memcpy(a, b, w*h*channels*sizeof(float));
		free (b);
	}
}

float *get_pixel_address_contig(void *ptr, xyi_t dim, xyi_t ip, int channels)
{
	float *array = ptr;

	return &array[(ip.y * dim.x + ip.x)*channels];
}

float *get_pixel_address_2d(void *ptr, xyi_t dim, xyi_t ip, int channels)
{
	float **array = ptr;

	return &array[ip.y][ip.x*channels];
}

void blit_scale_float(void *dst, xyi_t dst_dim, void *src, xyi_t src_dim, const int channels, xy_t pscale, xy_t pos, float * (*get_pix_f)(void*,xyi_t,xyi_t,int))
{
	int ic;
	float *dst_p, *src_p, sumf[4];
	double interp_weight;
	flattop_param_t param={0}, *p = &param;

	if (dst==NULL || src==NULL || channels > 4)
		return ;

	param = flattop_init_param(dst_dim, src_dim, pscale, pos);

	for (p->ip.y = p->start.y; p->ip.y < p->stop.y; p->ip.y++)
	{
		for (p->ip.x = p->start.x; p->ip.x < p->stop.x; p->ip.x++)
		{
			flattop_calc_j_bounds(p, pos);

			memset(sumf, 0, channels*sizeof(float));		// blank the new sum pixel

			for (p->jp.y = p->jstart.y; p->jp.y < p->jstop.y; p->jp.y++)
			{
				flattop_calc_weight_y(p);

				for (p->jp.x = p->jstart.x; p->jp.x < p->jstop.x; p->jp.x++)
				{
					interp_weight = flattop_calc_weight(p);

					src_p = get_pix_f(src, src_dim, p->jp, channels);	// get the pixel pointer
					for (ic=0; ic < channels; ic++)
						sumf[ic] += src_p[ic] * interp_weight;
				}
			}

			dst_p = get_pix_f(dst, dst_dim, p->ip, channels);	// get the pixel pointer
			for (ic=0; ic < channels; ic++)
				dst_p[ic] += sumf[ic];
		}
	}
}

void blit_scale_float_autoscale(void *dst, xyi_t dst_dim, void *src, xyi_t src_dim, const int channels, float * (*get_pix_f)(void*,xyi_t,xyi_t,int))
{
	xy_t pscale, pos, dst_c, src_c;

	pscale = div_xy(xyi_to_xy(dst_dim), xyi_to_xy(src_dim));
	dst_c = sub_xy(mul_xy(xyi_to_xy(dst_dim), set_xy(0.5)), set_xy(0.5));	// dst*0.5-0.5
	src_c = sub_xy(mul_xy(xyi_to_xy(src_dim), set_xy(0.5)), set_xy(0.5));	// src*0.5-0.5
	pos = sub_xy(dst_c, mul_xy(src_c, pscale));				// dst_c - (src_c * pscale)

	blit_scale_float(dst, dst_dim, src, src_dim, channels, pscale, pos, get_pix_f);
}

void image_downscale_fast_box(raster_t r0, raster_t *r1, const xyi_t ratio, const int mode)
{
	xyi_t dim0, dim1, ip0, ip1;
	recti_t pixbox;
	xyz_t fsum, pix0;
	double fratio;

	if (get_raster_buffer_for_mode(r0, mode)==NULL)
	{
		fprintf_rl(stderr, "image_downscale_fast_box() can't process empty image.\n");
		return ;
	}

	dim0 = xyi(r0.dim.x, r0.dim.y);
	dim1 = div_xyi( add_xyi(dim0, ratio) , ratio );

	// if r1 is inadequate
	if (equal_xyi(dim1, r1->dim)==0 || get_raster_buffer_for_mode(*r1, mode)==NULL)
	{
		free_raster(r1);
		*r1 = make_raster(NULL, dim1, XYI0, mode);
	}

	if (mode & IMAGE_USE_FRGB)
	{
		for (ip1.y=0; ip1.y < dim1.y; ip1.y++)
		{
			for (ip1.x=0; ip1.x < dim1.x; ip1.x++)
			{
				memset(&fsum, 0, sizeof(fsum));
				fratio = 0.;

				pixbox.p0 = mul_xyi(ip1, ratio);
				pixbox.p1 = min_xyi( add_xyi(pixbox.p0, ratio) , dim0 );

				for (ip0.y = pixbox.p0.y; ip0.y < pixbox.p1.y; ip0.y++)
				{
					for (ip0.x = pixbox.p0.x; ip0.x < pixbox.p1.x; ip0.x++)
					{
						pix0 = frgb_to_xyz(r0.f[ip0.y * r0.dim.x + ip0.x]);

						fsum = add_xyz(fsum, pix0);
						fratio += 1.;
					}
				}

				fratio = 1./fratio;
				fsum = mul_xyz(fsum, set_xyz(1. / mul_x_by_y_xyi(ratio)));		// weighting of the sum with a fixed ratio
				r1->f[ip1.y * r1->dim.x + ip1.x] = make_colour_frgb(fsum.x, fsum.y, fsum.z, mul_x_by_y_xyi(ratio) * fratio);
			}
		}
	}

	if (mode & IMAGE_USE_LRGB)	// TODO
	{
	}
}

frgb_t get_raster_pixel_bilinear_frgb(raster_t r, xy_t p)
{
	xy_t t;
	rect_t p_rect;
	recti_t pri;
	frgb_t pv={0};

	// Calc position
	p_rect = rect(floor_xy(p), ceil_xy(p));
	pri = rect_to_recti(p_rect);
	t = sub_xy(p, p_rect.p0);

	// Interpolate
	pv =               mul_scalar_frgba(get_raster_pixel_in_frgb_xyi(r, pri.p0), (1.-t.x) * (1.-t.y));
	pv = add_frgba(pv, mul_scalar_frgba(get_raster_pixel_in_frgb_xyi(r, recti_p01(pri)), (1.-t.x) * t.y));
	pv = add_frgba(pv, mul_scalar_frgba(get_raster_pixel_in_frgb_xyi(r, recti_p10(pri)), t.x * (1.-t.y)));
	pv = add_frgba(pv, mul_scalar_frgba(get_raster_pixel_in_frgb_xyi(r, pri.p1), t.x * t.y));

	return pv;
}

void get_pixel_bilinear_double(double *pix, double *im, xyi_t im_dim, xy_t p, int chan_stride, int chan_count)
{
	int i, ic;
	xy_t t;
	rect_t p_rect;
	recti_t pri;
	xyi_t ind[4];
	double t_mul[4];

	memset(pix, 0, chan_count * sizeof(double));

	// Calc position
	p_rect = rect(floor_xy(p), ceil_xy(p));
	pri = rect_to_recti(p_rect);
	t = sub_xy(p, p_rect.p0);
	ind[0] = pri.p0;
	ind[1] = recti_p01(pri);
	ind[2] = recti_p10(pri);
	ind[3] = pri.p1;

	t_mul[0] = (1.-t.x) * (1.-t.y);
	t_mul[1] = (1.-t.x) * t.y;
	t_mul[2] = t.x * (1.-t.y);
	t_mul[3] = t.x * t.y;

	// Interpolate
	for (i=0; i < 4; i++)
		for (ic=0; ic < chan_count; ic++)
			if (ind[i].y >= 0 && ind[i].y < im_dim.y && ind[i].x >= 0 && ind[i].x < im_dim.x)
				pix[ic] += im[(ind[i].y * im_dim.x + ind[i].x)*chan_stride + ic] * t_mul[i];
}

// Functions that process a whole image using a pointer to a per-pixel processing function
void image_pixel_process_arg0(raster_t r, const int mode, void (*func)(void))
{
	int i;

	if (get_raster_buffer_for_mode(r, mode)==NULL)
	{
		fprintf_rl(stderr, "image_pixel_process_arg0() can't process empty image.\n");
		return ;
	}

	if (mode & IMAGE_USE_FRGB)
		for (i=0; i < r.dim.x*r.dim.y; i++)
			((void (*)(float *, float *))func)((float *) &r.f[i], (float *) &r.f[i]);

	if (mode & IMAGE_USE_LRGB)
		for (i=0; i < r.dim.x*r.dim.y; i++)
			((void (*)(uint16_t *, uint16_t *))func)((uint16_t *) &r.l[i], (uint16_t *) &r.l[i]);
}

void image_pixel_process_arg1f(raster_t r, const int mode, void (*func)(void), float arg1)
{
	int i, arg1_int;

	if (get_raster_buffer_for_mode(r, mode)==NULL)
	{
		fprintf_rl(stderr, "image_pixel_process_arg1d() can't process empty image.\n");
		return ;
	}

	if (mode & IMAGE_USE_FRGB)
		for (i=0; i < r.dim.x*r.dim.y; i++)
			((void (*)(float *, float *, float))func)((float *) &r.f[i], (float *) &r.f[i], arg1);

	arg1_int = nearbyint(arg1 * ONE);
	if (mode & IMAGE_USE_LRGB)
		for (i=0; i < r.dim.x*r.dim.y; i++)
			((void (*)(uint16_t *, uint16_t *, int))func)((uint16_t *) &r.l[i], (uint16_t *) &r.l[i], arg1_int);
}

// Per-pixel processing functions
void pixel_invert_linear(float *p0, float *p1)
{
	int ic;

	for (ic=0; ic<3; ic++)
		p1[ic] = 1. - p0[ic];

	p1[3] = p0[3];
}

void pixel_alpha_to_grey(float *p0, float *p1)
{
	int ic;

	for (ic=0; ic<4; ic++)
		p1[ic] = p0[3];
}

void pixel_mul_by_own_alpha(float *p0, float *p1)
{
	int ic;

	for (ic=0; ic<3; ic++)
		p1[ic] = p0[ic] * p0[3];

	p1[3] = p0[3];
}

void pixel_mul_by_ratio(float *p0, float *p1, float ratio)
{
	int ic;

	for (ic=0; ic<3; ic++)
		p1[ic] = p0[ic] * ratio;

	p1[3] = p0[3];
}
