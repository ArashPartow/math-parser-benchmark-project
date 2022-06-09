double gaussrad(double intensity, double radius)
{
	static double last_intensity=0., last_radius=0., last_result=0.;

	if (last_intensity==intensity && last_radius==radius)
		return last_result;
	else
	{
		last_intensity = intensity;
		last_radius = radius;
		if (intensity > GAUSSLIMIT)
			last_result = (sqrt(log(intensity / GAUSSLIMIT))*radius);
		else
			last_result = 0.;
		return last_result;
	}
}

size_t get_raster_mode_elem_size(const int mode)
{
	switch (mode)
	{
		case IMAGE_USE_SRGB:	return sizeof(srgb_t);
		case IMAGE_USE_LRGB:	return sizeof(lrgb_t);
		case IMAGE_USE_FRGB:	return sizeof(frgb_t);
		case IMAGE_USE_SQRGB:	return sizeof(sqrgb_t);
		case IMAGE_USE_BUF:	return 1;
		default:		return 0;
	}
}

raster_t make_raster(void *data, const xyi_t dim, xyi_t maxdim, const int mode)	// maxdim can be XYI0
{
	raster_t r={0};
	void **ptr;

	if (is0_xyi(maxdim))
		maxdim = dim;

	r.dim = dim;
	r.table_index = -1;
	r.as = mul_x_by_y_xyi(maxdim);
	ptr = get_raster_buffer_for_mode_ptr(&r, mode);

	if (data)
		*ptr = data;
	else if (r.as)
		*ptr = calloc(r.as, get_raster_mode_elem_size(mode));

	return r;
}

raster_t make_raster_empty()
{
	raster_t r={0};
	r.table_index = -1;
	return r;
}

raster_t copy_raster(raster_t r0)
{
	raster_t r1;

	r1 = r0;

	r1.l = copy_alloc(r0.l, r0.dim.x*r0.dim.y*sizeof(lrgb_t));
	r1.f = copy_alloc(r0.f, r0.dim.x*r0.dim.y *sizeof(frgb_t));
	r1.srgb = copy_alloc(r0.srgb, r0.dim.x*r0.dim.y *sizeof(srgb_t));
	r1.sq = copy_alloc(r0.sq, r0.dim.x*r0.dim.y *sizeof(sqrgb_t));
	r1.buf = copy_alloc(r0.buf, r0.buf_size);
	r1.buf_size = r0.buf_size;

	return r1;
}

void blank_raster(raster_t *r, const int set_alpha_to_1)
{
	size_t i, pix_count = mul_x_by_y_xyi(r->dim);

	if (r->l)	memset(r->l, 0, pix_count*sizeof(lrgb_t));
	if (r->f)	memset(r->f, 0, pix_count*sizeof(frgb_t));
	if (r->srgb)	memset(r->srgb, 0, pix_count*sizeof(srgb_t));
	if (r->sq)	memset(r->sq, 0, pix_count*sizeof(sqrgb_t));
	if (r->buf)	memset(r->sq, 0, r->buf_size);

	if (set_alpha_to_1)
	{
		if (r->l)
			for (i=0; i < pix_count; i++)
				r->l[i].a = ONE;

		if (r->f)
			for (i=0; i < pix_count; i++)
				r->f[i].a = 1.f;

		if (r->srgb)
			for (i=0; i < pix_count; i++)
				r->srgb[i].a = 255;
	}
}

void **get_raster_buffer_for_mode_ptr(raster_t *r, const int mode)
{
	switch (mode)
	{
		case IMAGE_USE_SRGB:	return &r->srgb;	break;
		case IMAGE_USE_LRGB:	return &r->l;		break;
		case IMAGE_USE_FRGB:	return &r->f;		break;
		case IMAGE_USE_SQRGB:	return &r->sq;		break;
		case IMAGE_USE_BUF:	return &r->buf;		break;
	}

	return NULL;
}

void *get_raster_buffer_for_mode(raster_t r, const int mode)
{
	if (mode & IMAGE_USE_SRGB)	return r.srgb;
	if (mode & IMAGE_USE_LRGB)	return r.l;
	if (mode & IMAGE_USE_FRGB)	return r.f;
	if (mode & IMAGE_USE_SQRGB)	return r.sq;
	if (mode & IMAGE_USE_BUF)	return r.buf;

	return NULL;
}

void **get_raster_buffer_ptr(raster_t *r)
{
	if (r->srgb)	return &r->srgb;
	if (r->l)	return &r->l;
	if (r->f)	return &r->f;
	if (r->sq)	return &r->sq;
	if (r->buf)	return &r->buf;

	return NULL;
}

void *get_raster_buffer(raster_t *r)
{
	void **ptr;

	ptr = get_raster_buffer_ptr(r);

	return *ptr;
}

int get_raster_mode(raster_t r)
{
	if (r.srgb)	return IMAGE_USE_SRGB;
	if (r.l)	return IMAGE_USE_LRGB;
	if (r.f)	return IMAGE_USE_FRGB;
	if (r.sq)	return IMAGE_USE_SQRGB;
	if (r.buf)	return IMAGE_USE_BUF;

	return -1;
}

srgb_t get_raster_pixel_in_srgb(raster_t r, const size_t index)
{
	srgb_t s={0};
	frgb_t f;
	lrgb_t l;
	static int init=1;
	static lut_t lsrgb_l, lsrgb_fl_l;

	if (r.srgb)
		return r.srgb[index];

	if (init)
	{
		init = 0;
		lsrgb_l = get_lut_lsrgb();
		lsrgb_fl_l = get_lut_lsrgb_fl();
	}

	if (r.f || r.sq)
	{
		if (r.f)
			f = clamp_frgba(r.f[index]);
		else
			f = sqrgb_to_frgb(r.sq[index]);

		s.r = lsrgb_fl(f.r, lsrgb_fl_l.lutint) + 16 >> 5;
		s.g = lsrgb_fl(f.g, lsrgb_fl_l.lutint) + 16 >> 5;
		s.b = lsrgb_fl(f.b, lsrgb_fl_l.lutint) + 16 >> 5;
		s.a = lsrgb_fl(f.a, lsrgb_fl_l.lutint) + 16 >> 5;

		return s;
	}

	if (r.l)
	{
		l = r.l[index];
		s.r = lsrgb_l.lutint[l.r] + 16 >> 5;
		s.g = lsrgb_l.lutint[l.g] + 16 >> 5;
		s.b = lsrgb_l.lutint[l.b] + 16 >> 5;
		s.a = lsrgb_l.lutint[l.a] + 16 >> 5;

		return s;
	}

	return s;
}

frgb_t get_raster_pixel_in_frgb(raster_t r, const size_t index)
{
	if (r.f)
		return r.f[index];

	if (r.l)
		return lrgb_to_frgb(r.l[index]);

	if (r.sq)
		return sqrgb_to_frgb(r.sq[index]);

	if (r.srgb)
		return srgb_to_frgb(r.srgb[index]);

	return make_colour_frgb(NAN, NAN, NAN, NAN);
}

frgb_t get_raster_pixel_in_frgb_xyi(raster_t r, xyi_t p)
{
	frgb_t pv={0};

	if (p.y >= 0 && p.y < r.dim.y && p.x >= 0 && p.x < r.dim.x)
		pv = get_raster_pixel_in_frgb(r, p.y * r.dim.x + p.x);

	return pv;
}

void free_raster(raster_t *r)
{
	void **ptr;

	ptr = get_raster_buffer_ptr(r);

	while (ptr)	// free every possible buffer
	{
		#ifdef RL_OPENCL
		cl_data_table_remove_entry_by_host_ptr(*ptr);	// remove reference from cl data table
		#endif

		free_null(ptr);

		ptr = get_raster_buffer_ptr(r);
	}

	memset(r, 0, sizeof(raster_t));
}

void cl_unref_raster(raster_t *r)
{
	#ifdef RL_OPENCL
	void **ptr;

	ptr = get_raster_buffer_ptr(r);

	if (ptr == NULL)
		return;

	cl_data_table_remove_entry_by_host_ptr(*ptr);	// remove reference from cl data table
	#endif
}

framebuffer_t init_framebuffer(xyi_t dim, xyi_t maxdim, const int mode)
{
	framebuffer_t fb={0};

	if (is0_xyi(maxdim))
		maxdim = dim;

	fb.r = make_raster(NULL, dim, maxdim, mode);
	fb.w = fb.r.dim.x;
	fb.h = fb.r.dim.y;
	fb.maxdim = maxdim;

	return fb;
}

void init_tls_fb(xyi_t dim)	// initalisation of thread-local fb and zc in fRGB mode, used for video generation. Just free_raster(&fb.r); at the end
{
	memset(&fb, 0, sizeof(framebuffer_t));
	fb.w = dim.x;
	fb.h = dim.y;
	fb.r = make_raster(NULL, dim, XYI0, IMAGE_USE_FRGB);
	fb.r.use_frgb = 1;
	fb.use_drawq = 0;

	zc = init_zoom(&mouse, drawing_thickness);
	calc_screen_limits(&zc);
}

void enlarge_framebuffer(xyi_t newdim)
{
	if (fb.use_drawq==0)
		alloc_enough(get_raster_buffer_ptr(&fb.r), mul_x_by_y_xyi(newdim), &fb.r.as, get_raster_mode_elem_size(get_raster_mode(fb.r)), 1.2);

	fb.r.dim = newdim;
	fb.w = fb.r.dim.x;
	fb.h = fb.r.dim.y;
}

double intensity_scaling(double scale, double scale_limit)	// gives an intensity ratio that decreases if the scale of the thing to be drawn is below a scale threshold
{
	double ratio = 1., x;
	const double knee_width = 0.25, y_offset = sqrt(1.+knee_width) - 1.;

	if (scale < scale_limit)
		ratio = scale / scale_limit;

	// linear adjust knee smoothing
	x = scale / scale_limit;
	ratio = sqrt(sq(x-1.)+knee_width) - x - 1. - y_offset;
	ratio *= -0.5;
	ratio = MINN(ratio, 1.);

	return ratio;
}

void thickness_limit(double *thickness, double *brightness, double limit)	// same except also limits thickness
{
	if (*thickness < limit)
	{
		*brightness *= *thickness / limit;
		*thickness = limit;
	}
}

void screen_blank()
{
	if (fb.use_drawq)
		return ;
	else if (fb.r.use_frgb)
		memset(fb.r.f, 0, fb.w*fb.h*sizeof(frgb_t));
	else
		memset(fb.r.l, 0, fb.w*fb.h*sizeof(lrgb_t));
}
