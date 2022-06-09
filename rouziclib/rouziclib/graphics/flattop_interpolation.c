double blit_scale_func_linear(double x, double unit_inv, interp_param_t p)
{
	uint64_t *xp = (uint64_t *) &x;

	*xp &= 0x7FFFFFFFFFFFFFFF;	// fabs() equivalent
	x *= unit_inv;

	return (1. - x) * unit_inv;
	//return (0.5+0.5*cos(pi*x)) * unit_inv;
}

double blit_scale_func_modlin(double x, double unit_inv, interp_param_t p)
{
	uint64_t *xp = (uint64_t *) &x;

	*xp &= 0x7FFFFFFFFFFFFFFF;	// fabs() equivalent

	if (x < p.knee)
		return p.top;
	else
		return p.c1*x + p.c0;
}

interp_param_t calc_interp_param_modlin(double n)
{
	interp_param_t p;
	double m, trough, ni = 1./n;	// n = ]0 , 1], ni >= 1

	if (ni == floor(ni))				// if ni is an integer like 1.0, 2.0, 3.0...
		p.func = blit_scale_func_linear;	// this means regular linear filtering should be used
	else
		p.func = blit_scale_func_modlin;	// this means my modified filtering should be used

	p.knee = 0.5 - fabs(fmod(ni, 1.) - 0.5);	// Knee position = [0 , 0.5]

	m = floor(ni+0.5);				// mid-point of the current trough segment
	trough = 2.*m - n*m*m;				// uncorrected trough height
	trough = (1. - p.knee*n) / trough;		// corrected

	p.top = trough;
	p.c1 = -trough / (ni-p.knee);
	p.c0 = -p.c1 * ni;				// this gives a 0 intercept at ni

	return p;
}

double calc_flattop_slope(double n)
{
	double knee, midpoint, trough, top, slope;

	knee = 0.5 - fabs(fmod(n, 1.) - 0.5);		// the knee position ping pongs within [0 , 0.5] depending on n
	midpoint = floor(n+0.5);			// the mid-point of the current trough segment
	trough = 2.*midpoint - midpoint*midpoint/n;	// the height of the trough
	top = (1. - knee/n) / trough;			// the height of the flat top
	slope = -top / (n-knee);			// and the most important, the slope

	return slope;
}

flattop_param_t flattop_init_param(xyi_t dst_dim, xyi_t src_dim, xy_t pscale, xy_t pos)
{
	flattop_param_t param={0}, *p = &param;
	xy_t p0, p1;

	p->src_dim = src_dim;
	p->ipscale = inv_xy(pscale);

	p->kr1 = set_xy(1.0);
	p->kr0 = p->kr1;				// kernel radiuses at the unscaled level
	if (pscale.x < 1.)
		p->kr0.x *= p->ipscale.x;

	if (pscale.y < 1.)
		p->kr0.y *= p->ipscale.y;

	p->ikr0 = inv_xy(p->kr0);			// ikr0 = ]0 , 1]

	// Flattop or bilinear parameters
	p->param_x = calc_interp_param_modlin(p->ikr0.x);
	p->param_y = calc_interp_param_modlin(p->ikr0.y);

	// Find start and stop indices
	p0 = mad_xy(pscale, neg_xy(p->kr1), pos);
	p1 = mad_xy(pscale, add_xy(p->kr1, xy(src_dim.x-1, src_dim.y-1)), pos);

	p->start = max_xyi(XYI0, xy_to_xyi(floor_xy(min_xy(p0, p1))));
	p->stop = min_xyi(dst_dim, add_xyi(XYI1, xy_to_xyi(ceil_xy(max_xy(p0, p1)))));

	return param;
}

void flattop_calc_j_bounds(flattop_param_t *p, xy_t pos)
{
	// Position in the source image
	p->pin = mul_xy(sub_xy(xyi_to_xy(p->ip), pos), p->ipscale);

	// Start and end for sampling in the source image
	p->jstart = max_xyi(XYI0, add_xyi(xy_to_xyi(floor_xy(sub_xy(p->pin, p->kr0))), XYI1));
	p->jstop = min_xyi(p->src_dim, xy_to_xyi(ceil_xy(add_xy(p->pin, p->kr0))));
}

void flattop_calc_weight_y(flattop_param_t *p)
{
	p->iw.y = p->param_y.func((double) p->jp.y - p->pin.y, p->ikr0.y, p->param_y);
}

double flattop_calc_weight(flattop_param_t *p)
{
	return p->iw.y * p->param_x.func((double) p->jp.x - p->pin.x, p->ikr0.x, p->param_x);
}
