void draw_line_thin_lrgb(xy_t p1, xy_t p2, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{
	int32_t i, iy, ix, fbi;
	xy_t p3, p4, p1l, p2l, p3l, p4l;
	double d12, d12s, dx12, dy12, vx12, vy12, grad;
	int32_t p, ratio;		// 0.15
	double iradius, bradius, bvx, bvy;
	int32_t bstartx, bstarty, bendx, bendy, incx, incy, incc;
	int bx0, by0, bx1, by1, dx, dy, sx, sy, err, e2;	// Bresenham routine variables

	int32_t x1f, y1f, x2f, y2f;
	int32_t xr1, yr1, xr2, xrp, yrp;
	int32_t th, costh, sinth;
	const int32_t fp=16, fpi=30-fp;
	const double fpratio = (double) (1<<fp);

	grad = GAUSSRAD(intensity, radius);	// solves e^-x² = GAUSSLIMIT for x, giving 2.92 (the necessary Gaussian radius) for GAUSSLIMIT of 0.0002
	bradius = grad * sqrt(2.);		// bounding radius, the maximum radius necessary at each end of the line

	border_clip(fb.w-1, fb.h-1, &p1, &p2, grad);	// cut the part of the segment outside the screen

	ratio = 32768. * intensity + 0.5;

	dx12 = p2.x-p1.x;
	dy12 = p2.y-p1.y;
	d12 = hypot(dx12, dy12); if (d12==0.) return;
	vx12 = dx12/d12;
	vy12 = dy12/d12;

	p3.x = p1.x - bradius * vx12;
	p3.y = p1.y - bradius * vy12;
	p4.x = p2.x + bradius * vx12;
	p4.y = p2.y + bradius * vy12;
	bvx = -vy12;
	bvy = vx12;
	p1l.x = p1.x - bvx * grad;
	p1l.y = p1.y - bvy * grad;
	p2l.x = p2.x - bvx * grad;
	p2l.y = p2.y - bvy * grad;

	iradius = 1./radius;

	x1f = roundaway(p1.x * fpratio);
	y1f = roundaway(p1.y * fpratio);
	x2f = roundaway(p2.x * fpratio);
	y2f = roundaway(p2.y * fpratio);

	th = fpatan2_d2(y2f-y1f, x2f-x1f);
	costh = iradius * fpcos_d2(-th);			// iradius is double, can be above 1.0, not sure how that doesn't overflow
	sinth = iradius * fpsin_d2(-th);
	xr1 = ((int64_t) x1f * costh >> 30) - ((int64_t) y1f * sinth >> 30);
	yr1 = ((int64_t) x1f * sinth >> 30) + ((int64_t) y1f * costh >> 30);
	xr2 = ((int64_t) x2f * costh >> 30) - ((int64_t) y2f * sinth >> 30);

	incx = 949;
	if (dx12 >= fabs(dy12))	// start line left side of p1.x
	{
		p3l.x = p3.x;
		p3l.y = p3.y - 1.;
		incx = 0;
		incy = 1;
	}
	if (dy12 >= fabs(dx12))	// start line up side of p1.x
	{
		p3l.x = p3.x + 1.;
		p3l.y = p3.y;
		incx = -1;
		incy = 0;
	}
	if (-dx12 >= fabs(dy12))	// start line right side of p1.x
	{
		p3l.x = p3.x;
		p3l.y = p3.y + 1.;
		incx = 0;
		incy = -1;
	}
	if (-dy12 >= fabs(dx12))	// start line down side of p1.x
	{
		p3l.x = p3.x - 1.;
		p3l.y = p3.y;
		incx = 1;
		incy = 0;
	}
	if (incx==949)		// if the coordinates are invalid (like a NaN)
		return ;	// return

	p3l = line_line_intersection(p1l, p2l, p3, p3l);

	p4l.x = p4.x - p3.x + p3l.x;
	p4l.y = p4.y - p3.y + p3l.y;

	if (incx+incy == 1)
	{
		bstartx = (int32_t) floor (p3l.x);
		bstarty = (int32_t) floor (p3l.y);
		bendx = (int32_t) floor (p4l.x);
		bendy = (int32_t) floor (p4l.y);

		if (incx==1)
			incc = (int32_t) ceil (p3.x*2-p3l.x) - bstartx;
		else
			incc = (int32_t) ceil (p3.y*2-p3l.y) - bstarty;
	}
	else
	{
		bstartx = (int32_t) ceil (p3l.x);
		bstarty = (int32_t) ceil (p3l.y);
		bendx = (int32_t) ceil (p4l.x);
		bendy = (int32_t) ceil (p4l.y);

		if (incx==-1)
			incc = bstartx - (int32_t) floor (p3.x*2-p3l.x);
		else
			incc = bstarty - (int32_t) floor (p3.y*2-p3l.y);
	}

	incc = fastabs(incc) + 1;

	// check for >45 degree angles
	if (dx12 >= fabs(dy12))	// start line left side of p1.x
		if (bendx-bstartx < fastabs(bendy-bstarty))
			bendy = fastabs(bendx-bstartx) * sign(bendy-bstarty) + bstarty;
	if (dy12 >= fabs(dx12))	// start line up side of p1.x
		if (bendy-bstarty < fastabs(bendx-bstartx))
			bendx = fastabs(bendy-bstarty) * sign(bendx-bstartx) + bstartx;
	if (-dx12 >= fabs(dy12))	// start line right side of p1.x
		if (-bendx+bstartx < fastabs(bendy-bstarty))
			bendy = fastabs(bendx-bstartx) * sign(bendy-bstarty) + bstarty;
	if (-dy12 >= fabs(dx12))	// start line down side of p1.x
		if (-bendy+bstarty < fastabs(bendx-bstartx))
			bendx = fastabs(bendy-bstarty) * sign(bendx-bstartx) + bstartx;

	for (i=0; i<incc; i++)
	{
		//********Bresenham routine********
		bx0 = bstartx;
		by0 = bstarty;
		bx1 = bendx;
		by1 = bendy;

		dx = fastabs(bx1-bx0);
		dy = fastabs(by1-by0);
		sx = -1; if (bx0 < bx1) sx = 1;
		sy = -1; if (by0 < by1) sy = 1;
		err = dx-dy; ix = bx0; iy = by0;

		while (1)
		{
			if (ix>=0 && ix<fb.w && iy>=0 && iy<fb.h)
			{
				fbi = iy*fb.w+ix;
				xrp = ((int64_t) ix * costh >> fpi) - ((int64_t) iy * sinth >> fpi);
				yrp = ((int64_t) ix * sinth >> fpi) + ((int64_t) iy * costh >> fpi);

				p = fperfr_d0(xrp-xr1) >> 15;
				p -= fperfr_d0(xrp-xr2) >> 15;
				p *= fpgauss_d0(yrp-yr1) >> 15;
				p >>= 15;
				p = p * ratio >> 15;

				bf(&fb.r.l[fbi], colour, p);
			}

			if (ix==bx1 && iy==by1) break;
			e2 = err*2;
			if (e2 > -dy) { err -= dy; ix += sx; }
			if (e2 < dx) { err += dx; iy += sy; }
		}
		//--------Bresenham routine--------

		bstartx += incx;
		bendx += incx;
		bstarty += incy;
		bendy += incy;
	}
}

void draw_line_thin_frgb(xy_t p1, xy_t p2, double radius, frgb_t colour, const blend_func_fl_t bf, double intensity)
{
	int32_t i, iy, ix, fbi;
	xy_t p3, p4, p1l, p2l, p3l, p4l;
	double d12, d12s, dx12, dy12, vx12, vy12, grad;
	float ixf, iyf, p, ratio=intensity;
	double iradius, bradius, bvx, bvy;
	int32_t bstartx, bstarty, bendx, bendy, incx, incy, incc;
	int bx0, by0, bx1, by1, dx, dy, sx, sy, err, e2;	// Bresenham routine variables
	float xr1, yr1, xr2, xrp, yrp;
	float th, costh, sinth;

	//grad = GAUSSRAD(intensity, radius);	// solves e^-x² = GAUSSLIMIT for x, giving 2.92 (the necessary Gaussian radius) for GAUSSLIMIT of 0.0002
	grad = GAUSSRAD_HQ * radius;			// erfr and gaussian can go up to x = ±4
	bradius = grad * sqrt(2.);		// bounding radius, the maximum radius necessary at each end of the line

	border_clip(fb.w-1, fb.h-1, &p1, &p2, grad);	// cut the part of the segment outside the screen

	dx12 = p2.x-p1.x;
	dy12 = p2.y-p1.y;
	d12 = hypot(dx12, dy12); if (d12==0.) return;
	vx12 = dx12/d12;
	vy12 = dy12/d12;

	p3.x = p1.x - bradius * vx12;
	p3.y = p1.y - bradius * vy12;
	p4.x = p2.x + bradius * vx12;
	p4.y = p2.y + bradius * vy12;
	bvx = -vy12;
	bvy = vx12;
	p1l.x = p1.x - bvx * grad;
	p1l.y = p1.y - bvy * grad;
	p2l.x = p2.x - bvx * grad;
	p2l.y = p2.y - bvy * grad;

	iradius = 1./radius;

	th = atan2(p2.y-p1.y, p2.x-p1.x);
	costh = iradius * cos(-th);
	sinth = iradius * sin(-th);
	xr1 = p1.x * costh - p1.y * sinth;
	yr1 = p1.x * sinth + p1.y * costh;
	xr2 = p2.x * costh - p2.y * sinth;

	incx = 949;
	if (dx12 >= fabs(dy12))	// start line left side of p1.x
	{
		p3l.x = p3.x;
		p3l.y = p3.y - 1.;
		incx = 0;
		incy = 1;
	}
	if (dy12 >= fabs(dx12))	// start line up side of p1.x
	{
		p3l.x = p3.x + 1.;
		p3l.y = p3.y;
		incx = -1;
		incy = 0;
	}
	if (-dx12 >= fabs(dy12))	// start line right side of p1.x
	{
		p3l.x = p3.x;
		p3l.y = p3.y + 1.;
		incx = 0;
		incy = -1;
	}
	if (-dy12 >= fabs(dx12))	// start line down side of p1.x
	{
		p3l.x = p3.x - 1.;
		p3l.y = p3.y;
		incx = 1;
		incy = 0;
	}
	if (incx==949)		// if the coordinates are invalid (like a NaN)
		return ;	// return

	p3l = line_line_intersection(p1l, p2l, p3, p3l);

	p4l.x = p4.x - p3.x + p3l.x;
	p4l.y = p4.y - p3.y + p3l.y;

	if (incx+incy == 1)
	{
		bstartx = (int32_t) floor (p3l.x);
		bstarty = (int32_t) floor (p3l.y);
		bendx = (int32_t) floor (p4l.x);
		bendy = (int32_t) floor (p4l.y);

		if (incx==1)
			incc = (int32_t) ceil (p3.x*2-p3l.x) - bstartx;
		else
			incc = (int32_t) ceil (p3.y*2-p3l.y) - bstarty;
	}
	else
	{
		bstartx = (int32_t) ceil (p3l.x);
		bstarty = (int32_t) ceil (p3l.y);
		bendx = (int32_t) ceil (p4l.x);
		bendy = (int32_t) ceil (p4l.y);

		if (incx==-1)
			incc = bstartx - (int32_t) floor (p3.x*2-p3l.x);
		else
			incc = bstarty - (int32_t) floor (p3.y*2-p3l.y);
	}

	incc = fastabs(incc) + 1;

	// check for >45 degree angles
	if (dx12 >= fabs(dy12))	// start line left side of p1.x
		if (bendx-bstartx < fastabs(bendy-bstarty))
			bendy = fastabs(bendx-bstartx) * sign(bendy-bstarty) + bstarty;
	if (dy12 >= fabs(dx12))	// start line up side of p1.x
		if (bendy-bstarty < fastabs(bendx-bstartx))
			bendx = fastabs(bendy-bstarty) * sign(bendx-bstartx) + bstartx;
	if (-dx12 >= fabs(dy12))	// start line right side of p1.x
		if (-bendx+bstartx < fastabs(bendy-bstarty))
			bendy = fastabs(bendx-bstartx) * sign(bendy-bstarty) + bstarty;
	if (-dy12 >= fabs(dx12))	// start line down side of p1.x
		if (-bendy+bstarty < fastabs(bendx-bstartx))
			bendx = fastabs(bendy-bstarty) * sign(bendx-bstartx) + bstartx;

	for (i=0; i<incc; i++)
	{
		//********Bresenham routine********
		bx0 = bstartx;
		by0 = bstarty;
		bx1 = bendx;
		by1 = bendy;

		dx = fastabs(bx1-bx0);
		dy = fastabs(by1-by0);
		sx = -1; if (bx0 < bx1) sx = 1;
		sy = -1; if (by0 < by1) sy = 1;
		err = dx-dy; ixf = ix = bx0; iyf = iy = by0;

		while (1)
		{
			if (ix>=0 && ix<fb.w && iy>=0 && iy<fb.h)
			{
				fbi = iy*fb.w+ix;

				xrp = ixf * costh - iyf * sinth;
				yrp = ixf * sinth + iyf * costh;

				p = fasterfrf_d1(xrp-xr1);
				p -= fasterfrf_d1(xrp-xr2);
				p *= fastgaussianf_d1(yrp-yr1);
				p *= ratio;

				bf(&fb.r.f[fbi], colour, p);
			}

			if (ix==bx1 && iy==by1) break;
			e2 = err*2;
			if (e2 > -dy) { err -= dy; ix += sx; ixf = ix; }
			if (e2 < dx) { err += dx; iy += sy; iyf = iy; }
		}
		//--------Bresenham routine--------

		bstartx += incx;
		bendx += incx;
		bstarty += incy;
		bendy += incy;
	}
}

void draw_line_thin_dq(xy_t p1, xy_t p2, double radius, frgb_t colour, const int bf, double intensity, int quality)
{
	double grad;
	int32_t ix, iy;
	float *df;
	recti_t bb;
	rect_t box;
	xy_t l1, l2, b1, b2;
	xyi_t bb_dim;

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4
	//if (fb.use_drawq==2)
		grad = GAUSSRAD(intensity, radius);	// solves e^-x² = GAUSSLIMIT for x, giving 2.92 (the necessary Gaussian radius) for GAUSSLIMIT of 0.0002

	if (fastabs(p2.x-p1.x)+fastabs(p2.y-p1.y) > 1e6)	// cut out lines that are in the millions of pixels
		border_clip(fb.w-1, fb.h-1, &p1, &p2, grad);	// cut the part of the segment outside the screen
	if (p1.x==p2.x && p1.y==p2.y)			// if there's no line to display
		return ;

	// calculate the bounding box for a first rectangular estimate of the sectors needed
	box = sort_rect(rect(p1, p2));

	bb.p0.x = ceil (box.p0.x - grad);	bb.p0.x = MAXN(bb.p0.x, 0);
	bb.p0.y = ceil (box.p0.y - grad);	bb.p0.y = MAXN(bb.p0.y, 0);
	bb.p1.x = floor(box.p1.x + grad);	bb.p1.x = MINN(bb.p1.x, fb.w-1);
	bb.p1.y = floor(box.p1.y + grad);	bb.p1.y = MINN(bb.p1.y, fb.h-1);

	bb = rshift_recti(bb, fb.sector_size);

	// store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(DQT_LINE_THIN_ADD);
	if (df==NULL)
		return;
	if (0)//fb.use_drawq==1)
	{
		df[0] = p1.x;
		df[1] = p1.y;
		df[2] = p2.x;
		df[3] = p2.y;
		df[4] = 1./radius;
	}
	else
	{
		float iradius = 1./radius;
		float th = atan2f(p2.y-p1.y, p2.x-p1.x);	// TODO optimise atan2
		float costh = fastcosf_d2(-th) * iradius;
		float sinth = fastsinf_d2(-th) * iradius;
		df[0] = p1.x * costh - p1.y * sinth;		// r1x
		df[1] = p1.x * sinth + p1.y * costh;		// r1y
		df[2] = p2.x * costh - p2.y * sinth;		// r2x
		df[3] = costh;
		df[4] = sinth;
	}
	df[5] = colour.r * intensity;
	df[6] = colour.g * intensity;
	df[7] = colour.b * intensity;
	df[8] = colour.a * intensity;

	bb_dim = get_recti_dim(bb);
	if (bb_dim.x <= 0 || bb_dim.y <= 0)
		return ;

	if (p1.x==p2.x || p1.y==p2.y || bb_dim.x==1 || bb_dim.y==1 || mul_x_by_y_xyi(bb_dim) <= 4)	// if the line is purely vertical or horizontal or is only 1 sector across or if there's 4 possible sectors or less then just do them all anyway
		drawq_add_sectors_for_area(bb);		// add all sector references
	else
	{
		double c0, c1, c1_inv;

		c1 = (p2.y - p1.y) / (p2.x - p1.x);		// turn the line p1-p2 into c1*x + c0

		if (fabs(c1) < 1e-6)				// if the line is pretty much horizontal
			drawq_add_sectors_for_area(bb);		// add all sector references
		else if (fabs(c1_inv = 1. / c1) < 1e-6)		// if the line is pretty much vertical
			drawq_add_sectors_for_area(bb);		// add all sector references
		else
		{
			double sec_size = 1<<fb.sector_size, inv_sec_size = 1. / sec_size;

			c0 = p1.y - c1 * p1.x;

			for (iy=bb.p0.y; iy<=bb.p1.y; iy++)
			{
				double y0, y1, x0, x1;
				int sec0, sec1;

				// Calculate where in x the line intersects with the padded top and bottom y levels
				y0 = (iy * sec_size) - grad;
				y1 = (iy * sec_size) + grad + sec_size - 1.;
				x0 = (y0 - c0) * c1_inv;
				x1 = (y1 - c0) * c1_inv;

				// Find the first and last sector for this iy sector line
				minmax_double(&x0, &x1);
				sec0 = floor((x0 - grad) * inv_sec_size);
				sec1 = ceil((x1 + grad) * inv_sec_size);
				sec0 = MAXN(bb.p0.x, sec0);
				sec1 = MINN(bb.p1.x, sec1);

				for (ix=sec0; ix <= sec1; ix++)
					drawq_add_sector_id(iy*fb.sector_w + ix);	// add sector reference
			}
		}
	}
}

void draw_line_thin(xy_t p1, xy_t p2, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	if (fb.discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, &intensity, 0);	// adjusts the focus

	if (fb.use_drawq)
		draw_line_thin_dq(p1, p2, radius, col_to_frgb(colour), 0, intensity, 0);
	else if (fb.r.use_frgb)
		draw_line_thin_frgb(p1, p2, radius, col_to_frgb(colour), get_blend_fl_equivalent(bf), intensity);
	else
		draw_line_thin_lrgb(p1, p2, radius, col_to_lrgb(colour), bf, intensity);
}

void draw_line_thin_rectclip(xy_t p1, xy_t p2, xy_t b1, xy_t b2, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	line_rect_clip(&p1, &p2, rect(b1, b2));
	draw_line_thin(p1, p2, radius, colour, bf, intensity);
}

void draw_line_thin_short(xy_t p1, xy_t p2, double u1, double u2, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	xy_t p3, p4;

	if (u2<=u1)
		return;

	if (u1!=0.)
	{
		p3.x = p1.x + u1 * (p2.x-p1.x);
		p3.y = p1.y + u1 * (p2.y-p1.y);
	}
	else
		p3 = p1;

	if (u2!=1.)
	{
		p4.x = p1.x + u2 * (p2.x-p1.x);
		p4.y = p1.y + u2 * (p2.y-p1.y);
	}
	else
		p4 = p2;

	draw_line_thin(p3, p4, radius, colour, bf, intensity);
}

void bres_func_lrgb(xyi_t ip, raster_t *r, lrgb_t *col, void *arg3, void *arg4)		// lrgb opaque pixel drawing function for bresenham_line_core
{
	if (check_pixel_within_image(ip, r->dim))
		r->l[ip.y * r->dim.x + ip.x] = *col;
}

void bresenham_line_core(xyi_t b0, xyi_t b1, void (*func)(xyi_t,void*,void*,void*,void*), void *arg1, void *arg2, void *arg3, void *arg4)
{
	xyi_t d, s, i;
	int err, e2;

	d = abs_xyi(sub_xyi(b1, b0));
	s.x = b0.x < b1.x ? 1 : -1;
	s.y = b0.y < b1.y ? 1 : -1;
	err = d.x - d.y;
	i = b0;

	while (1)
	{
		func(i, arg1, arg2, arg3, arg4);

		if (equal_xyi(i, b1))
			break;

		e2 = err << 1;
		if (e2 > -d.y) { err -= d.y; i.x += s.x; }
		if (e2 < d.x)  { err += d.x; i.y += s.y; }
	}
}
