void draw_circle_lrgb(const int circlemode, xy_t pos, double circrad, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{
	double grad = GAUSSRAD(intensity, radius);
	int32_t ix, iy, fbi, lboundx, lboundy, rboundx, rboundy;
	int32_t p, ratio;	// 0.15
	int64_t lowbound2, highbound2, dx, dy, d, circradf;

	int32_t xf, yf, iradf;
	const int32_t fp=16;
	const double fpratio = (double) (1<<fp);

	ratio = 32768. * intensity + 0.5;
	if (ratio == 0)
		return ;

	iradf = roundaway(1./radius * fpratio);
	circradf = roundaway(circrad * fpratio);

	lboundx = (int32_t) ceil (pos.x - circrad - grad);	if (lboundx<0) lboundx = 0; if (lboundx>=fb->w) lboundx = fb->w-1;
	lboundy = (int32_t) ceil (pos.y - circrad - grad);	if (lboundy<0) lboundy = 0; if (lboundy>=fb->h) lboundy = fb->h-1;
	rboundx = (int32_t) floor (pos.x + circrad + grad);	if (rboundx<0) rboundx = 0; if (rboundx>=fb->w) rboundx = fb->w-1;
	rboundy = (int32_t) floor (pos.y + circrad + grad);	if (rboundy<0) rboundy = 0; if (rboundy>=fb->h) rboundy = fb->h-1;

	if (circlemode==HOLLOWCIRCLE)
	{
		lowbound2 = roundaway(MAXN(circrad - grad, 0.) * fpratio);
		lowbound2 *= lowbound2;
	}
	else
	{
		lowbound2 = -1;
	}

	highbound2 = roundaway((circrad + grad) * fpratio);
	highbound2 *= highbound2;

	xf = roundaway(pos.x * fpratio);
	yf = roundaway(pos.y * fpratio);

	for (iy=lboundy; iy<=rboundy; iy++)
	{
		dy = yf - (iy << fp);
		dy *= dy;

		for (ix=lboundx; ix<=rboundx; ix++)
		{
			fbi = iy*fb->w+ix;

			dx = xf - (ix << fp);
			dx *= dx;
			d = dx + dy;

			if (d>lowbound2 && d<highbound2)
			{
				d = (circradf - isqrt_d1i(d)) * iradf >> fp;

				if (circlemode==FULLCIRCLE)
					p = fperfr_d0(d) >> 15;
				else	// HOLLOWCIRCLE
					p = fpgauss_d0(d) >> 15;

				p = p * ratio >> 15;

				bf(&fb->r.l[fbi], colour, p);
			}
		}
	}
}

void draw_circle_dq(const int circlemode, xy_t pos, double circrad, double radius, frgb_t colour, double intensity)
{
#ifdef RL_OPENCL
	float *df;
	double grad, circum;
	int32_t i, ix, iy;
	rect_t bb, secbox, fr, screen_box = rect(XY0, xy(fb->w-1, fb->h-1));
	recti_t bbi;

	if (intensity==0.)
		return ;

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4

	// calculate the bounding box
	bb.p0 = ceil_xy(sub_xy(pos, set_xy(grad+circrad)));
	bb.p1 = floor_xy(add_xy(pos, set_xy(grad+circrad)));

	if (check_box_box_intersection(bb, screen_box)==0)
		return ;

	bbi.p0 = xy_to_xyi(max_xy(bb.p0, screen_box.p0));
	bbi.p1 = xy_to_xyi(min_xy(bb.p1, screen_box.p1));
	bbi = rshift_recti(bbi, fb->sector_size);

	// calculate the drawing parameters
	circum = circrad/radius;
	if (circlemode==FULLCIRCLE)
		intensity *= (0.5 + 0.5 * erf(circum)) - (0.5 + 0.5 * erf(-circum));	// why is this needed?
	colour.r *= intensity;
	colour.g *= intensity;
	colour.b *= intensity;

	// store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(circlemode==FULLCIRCLE ? DQT_CIRCLE_FULL : DQT_CIRCLE_HOLLOW);
	df[0] = pos.x;
	df[1] = pos.y;
	df[2] = circrad;
	df[3] = 1./radius;
	df[4] = colour.r;
	df[5] = colour.g;
	df[6] = colour.b;

	// find the affected sectors
	for (iy=bbi.p0.y; iy<=bbi.p1.y; iy++)
		for (ix=bbi.p0.x; ix<=bbi.p1.x; ix++)
		{
			secbox.p0.x = ix << fb->sector_size;
			secbox.p0.y = iy << fb->sector_size;
			secbox.p1 = add_xy(secbox.p0, set_xy((1 << fb->sector_size) - 1));

			if (check_box_circle_intersection(secbox, pos, circrad+grad))
				if (circrad-grad <= 0. || check_box_wholly_inside_circle(secbox, pos, circrad-grad)==0)
					drawq_add_sector_id(iy*fb->sector_w + ix);	// add sector reference
		}

	if (circrad-grad <= 0. || circlemode==HOLLOWCIRCLE)
		return ;

	//************PLAIN FILL AREA************

	df = drawq_add_to_main_queue(DQT_PLAIN_FILL);
	df[0] = colour.r;
	df[1] = colour.g;
	df[2] = colour.b;

	// find the affected sectors
	for (iy=bbi.p0.y; iy<=bbi.p1.y; iy++)
		for (ix=bbi.p0.x; ix<=bbi.p1.x; ix++)
		{
			secbox.p0.x = ix << fb->sector_size;
			secbox.p0.y = iy << fb->sector_size;
			secbox.p1 = add_xy(secbox.p0, set_xy((1 << fb->sector_size) - 1));

			if (check_box_wholly_inside_circle(secbox, pos, circrad-grad))	// if we're inside the plain fill area
				drawq_add_sector_id(iy*fb->sector_w + ix);	// add sector reference
		}
#endif
}

void draw_circle_dqnq(const int circlemode, xy_t pos, double circrad, double radius, frgb_t colour, double intensity)
{
	enum dqnq_type type = circlemode == FULLCIRCLE ? DQNQT_CIRCLE_FULL : DQNQT_CIRCLE_HOLLOW;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, float_as_u32(pos.x));
	write_LE32(&p, float_as_u32(pos.y));
	write_LE32(&p, float_as_u32(circrad));
	write_LE32(&p, float_as_u32(radius));
	write_LE32(&p, float_as_u32(colour.r * intensity));
	write_LE32(&p, float_as_u32(colour.g * intensity));
	write_LE32(&p, float_as_u32(colour.b * intensity));

	dqnq_finish_entry(type);
}

void draw_circle(const int circlemode, xy_t pos, double circrad, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	if (fb->discard)
		return;

	//if (circlemode!=HOLLOWCIRCLE)
		radius = drawing_focus_adjust(focus_rlg, radius, circlemode==FULLCIRCLE ? NULL : &intensity, 0);	// adjusts the focus

	/*if (circlemode==HOLLOWCIRCLE)
		draw_circle_with_lines(pos, circrad, radius, colour, blend_add, intensity);
	else*/
		if (fb->use_drawq)
			if (fb->use_dqnq)
				draw_circle_dqnq(circlemode, pos, circrad, radius, col_to_frgb(colour), intensity);
			else
				draw_circle_dq(circlemode, pos, circrad, radius, col_to_frgb(colour), intensity);
		else
			draw_circle_lrgb(circlemode, pos, circrad, radius, col_to_lrgb(colour), bf, intensity);
}

void draw_circle_arc(xy_t pos, xy_t circrad, double th0, double th1, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	int i, count;
	double stepth, oval_ratio = circrad.x / circrad.y;
	xy_t p0, p1;

	count = nearbyint(rangelimit(2.*pi * max_of_xy(circrad)/radius, 8., 2048.) * (th1-th0));
	count = MAXN(count, 2);
	th0 *= 2.*pi;
	th1 *= 2.*pi;
	stepth = (th1-th0) / (double) count;

	for (i=0; i<count; i++)
	{
		p0 = rotate_xy2(xy(0., -circrad.y), th0 + (double) i * stepth);
		p1 = rotate_xy2(xy(0., -circrad.y), th0 + (double) (i+1) * stepth);	// TODO recycle p1 into the next p0 to save on a rotation
		p0.x *= oval_ratio;
		p1.x *= oval_ratio;
		draw_line_thin(add_xy(pos, p0), add_xy(pos, p1), radius, colour, bf, intensity);
	}
}

void draw_circle_with_lines(xy_t pos, double circrad, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	draw_circle_arc(pos, set_xy(circrad), 0., 1., radius, colour, bf, intensity);
}

void draw_rect(rect_t r, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	draw_line_thin(xy(r.p0.x, r.p0.y), xy(r.p0.x, r.p1.y), radius, colour, bf, intensity);
	draw_line_thin(xy(r.p0.x, r.p1.y), xy(r.p1.x, r.p1.y), radius, colour, bf, intensity);
	draw_line_thin(xy(r.p1.x, r.p1.y), xy(r.p1.x, r.p0.y), radius, colour, bf, intensity);
	draw_line_thin(xy(r.p1.x, r.p0.y), xy(r.p0.x, r.p0.y), radius, colour, bf, intensity);
}

void draw_rect_chamfer(rect_t r, double radius, col_t colour, const blend_func_t bf, double intensity, double chamfer)
{
	xy_t p2, p3;
	double cs, csx, csy, sx=1., sy=1.;

	if (r.p1.x-r.p0.x < 0.)
		sx = -1.;
	if (r.p1.y-r.p0.y < 0.)
		sy = -1.;

	cs = chamfer * MINN(fabs(r.p1.x-r.p0.x), fabs(r.p1.y-r.p0.y));
	csx = cs*sx;
	csy = cs*sy;

	p2.x = r.p0.x+csx;
	p3.x = r.p1.x-csx;
	p2.y = r.p0.y+csy;
	p3.y = r.p1.y-csy;

	draw_line_thin(xy(r.p0.x, p2.y), xy(r.p0.x, p3.y), radius, colour, bf, intensity);
	draw_line_thin(xy(p2.x, r.p1.y), xy(p3.x, r.p1.y), radius, colour, bf, intensity);
	draw_line_thin(xy(r.p1.x, p3.y), xy(r.p1.x, p2.y), radius, colour, bf, intensity);
	draw_line_thin(xy(p3.x, r.p0.y), xy(p2.x, r.p0.y), radius, colour, bf, intensity);

	draw_line_thin(xy(r.p0.x, p3.y), xy(p2.x, r.p1.y), radius, colour, bf, intensity);
	draw_line_thin(xy(p3.x, r.p1.y), xy(r.p1.x, p3.y), radius, colour, bf, intensity);
	draw_line_thin(xy(r.p1.x, p2.y), xy(p3.x, r.p0.y), radius, colour, bf, intensity);
	draw_line_thin(xy(p2.x, r.p0.y), xy(r.p0.x, p2.y), radius, colour, bf, intensity);
}

void draw_line_dashed(xy_t p1, xy_t p2, double dash_period, double dash_ratio, double phase, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	xy_t pt1, pt2, pd;
	double t1, t2, t1c, t2c, d;

	d = hypot_xy(p1, p2);
	pd = sub_xy(p2, p1);
	t1 = phase * dash_period;

	while (1)
	{
		t2 = t1 + dash_period*dash_ratio;

		t1c = MAXN(0., t1) / d;
		t2c = MINN(d, t2) / d;

		if (t1 >= d)
			return ;

		pt1 = mad_xy(set_xy(t1c), pd, p1);
		pt2 = mad_xy(set_xy(t2c), pd, p1);

		draw_line_thin(pt1, pt2, radius, colour, bf, intensity);

		t1 += dash_period;
	}
}

int32_t get_dist_to_roundrect(int32_t lx1, int32_t ly1, int32_t lx2, int32_t ly2, int32_t corner, int32_t ixf, int32_t iyf)
{
	int32_t d;
	int32_t xsec, ysec, sec;

	ysec = 2;
	if (iyf < ly1)
		ysec = 1;
	else if (iyf > ly2)
		ysec = 3;

	xsec = 2;
	if (ixf < lx1)
		xsec = 1;
	else if (ixf > lx2)
		xsec = 3;

	sec = (xsec << 2) | ysec;

	// The lesser rectangle is the smaller rectangle from which the desired rounded rectangle is developed
	// It is what would happen if a circle of radius 'corner' was to be convolved with that lesser rectangle

	switch (sec)
	{
		case 5:  d = fphypot(lx1-ixf, ly1-iyf);	break;
		case 7:  d = fphypot(lx1-ixf, ly2-iyf);	break;
		case 13: d = fphypot(lx2-ixf, ly1-iyf);	break;
		case 15: d = fphypot(lx2-ixf, ly2-iyf);	break;
		case 6:  d = lx1 - ixf;	break;
		case 9:  d = ly1 - iyf;	break;
		case 11: d = iyf - ly2;	break;
		case 14: d = ixf - lx2;	break;

		case 10: d = 0;		break;
	}

	d -= corner;	// subtract the corner radius to the distance to the lesser rectangle to get the distance to the rounded rectangle

	return d;
}

void draw_roundrect(rect_t box, double corner, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{	// The corner radius size must be greater than the full radius of the antialiasing (grad) which would be 0.8*2.9 = 2.32 px
	double grad = GAUSSRAD(intensity, radius);
	int32_t ix, iy, fbi, ratio, p, lboundx, lboundy, rboundx, rboundy;
	int32_t d, iradf, x1f, y1f, x2f, y2f, ixf, iyf, cornerf;
	const int32_t fp=16;
	const double fpratio = (double) (1<<fp);

	ratio = 32768. * intensity + 0.5;

	iradf = roundaway(1./radius * fpratio);
	x1f = roundaway((box.p0.x+corner) * fpratio);
	y1f = roundaway((box.p0.y+corner) * fpratio);
	x2f = roundaway((box.p1.x-corner) * fpratio);
	y2f = roundaway((box.p1.y-corner) * fpratio);
	cornerf = roundaway(corner * fpratio);

	lboundx = (int32_t) rangelimit(ceil (box.p0.x - grad), 0., (double) (fb->w-1));
	lboundy = (int32_t) rangelimit(ceil (box.p0.y - grad), 0., (double) (fb->h-1));
	rboundx = (int32_t) rangelimit(floor (box.p1.x + grad), 0., (double) (fb->w-1));
	rboundy = (int32_t) rangelimit(floor (box.p1.y + grad), 0., (double) (fb->h-1));

	for (iy=lboundy; iy<=rboundy; iy++)
	{
		iyf = iy << fp;

		for (ix=lboundx; ix<=rboundx; ix++)
		{
			fbi = iy*fb->w+ix;

			ixf = ix << fp;
			d = (int64_t) get_dist_to_roundrect(x1f, y1f, x2f, y2f, cornerf, ixf, iyf) * iradf >> fp;
			p = fperfr_d0(-d) >> 15;
			p = p * ratio >> 15;

			bf(&fb->r.l[fbi], colour, p);
		}
	}
}

void draw_roundrect_frame(rect_t box1, rect_t box2, double corner1, double corner2, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{	// The corner radius size must be greater than the full radius of the antialiasing (grad) which would be 0.8*2.9 = 2.32 px
	double grad = GAUSSRAD(intensity, radius);
	int32_t ix, iy, fbi, ratio, p, lboundx, lboundy, rboundx, rboundy;
	int32_t din, dout, iradf, x1f, y1f, x2f, y2f, x3f, y3f, x4f, y4f, ixf, iyf, corner1f, corner2f;
	const int32_t fp=16;
	const double fpratio = (double) (1<<fp);

	ratio = 32768. * intensity + 0.5;

	iradf = roundaway(1./radius * fpratio);
	x1f = roundaway((box1.p0.x+corner1) * fpratio);
	y1f = roundaway((box1.p0.y+corner1) * fpratio);
	x2f = roundaway((box1.p1.x-corner1) * fpratio);
	y2f = roundaway((box1.p1.y-corner1) * fpratio);
	x3f = roundaway((box2.p0.x+corner2) * fpratio);
	y3f = roundaway((box2.p0.y+corner2) * fpratio);
	x4f = roundaway((box2.p1.x-corner2) * fpratio);
	y4f = roundaway((box2.p1.y-corner2) * fpratio);
	corner1f = roundaway(corner1 * fpratio);
	corner2f = roundaway(corner2 * fpratio);

	lboundx = (int32_t) rangelimit(ceil (box1.p0.x - grad), 0., (double) (fb->w-1));
	lboundy = (int32_t) rangelimit(ceil (box1.p0.y - grad), 0., (double) (fb->h-1));
	rboundx = (int32_t) rangelimit(floor (box1.p1.x + grad), 0., (double) (fb->w-1));
	rboundy = (int32_t) rangelimit(floor (box1.p1.y + grad), 0., (double) (fb->h-1));

	for (iy=lboundy; iy<=rboundy; iy++)
	{
		iyf = iy << fp;

		for (ix=lboundx; ix<=rboundx; ix++)
		{
			fbi = iy*fb->w+ix;

			ixf = ix << fp;
			dout = (int64_t) get_dist_to_roundrect(x1f, y1f, x2f, y2f, corner1f, ixf, iyf) * iradf >> fp;
			din = (int64_t) get_dist_to_roundrect(x3f, y3f, x4f, y4f, corner2f, ixf, iyf) * iradf >> fp;
			p = fperfr_d0(-dout) - fperfr_d0(-din) >> 15;
			p = p * ratio >> 15;

			bf(&fb->r.l[fbi], colour, p);
		}
	}
}

// TODO optimise using fixed point arithmetic and look-up tables
void draw_polar_glow(double cx, double cy, lrgb_t col, double colmul, double scale, double rad, double gradr, double gradth, double angle, int32_t islog, int32_t riserf, double erfrad, double pixoffset)
{
	int32_t ix, iy, g, ginv;
	double ixf, iyf, r, th, gx, gy;

	for (iy=0; iy<fb->h; iy++)
	{
		iyf = (double) iy - cy;

		for (ix=0; ix<fb->w; ix++)
		{
			ixf = (double) ix - cx;
			th = fastatan2(iyf*65536., ixf*65536.);		// range is (-pi, pi]
			r = sqrt(ixf*ixf + iyf*iyf);
			gy = (rad - (r/scale)) / gradr;
			if (islog)
				if (gy > 0.)
					gy = log(gy);
				else
					gy = 8.;

			if (riserf)	// if it's an erf and not a gaussian
				gy = fasterfrf_d1(gy + 0.5*erfrad) * fasterfrf_d1(-gy + 0.5*erfrad);
				//gy = (0.5*erf(gy + 0.5*erfrad) + 0.5) * (0.5*erf(-gy + 0.5*erfrad) + 0.5);
			else
				gy = fastgaussianf_d1(gy);
			gx = fastgaussianf_d1(rangewrap(th-angle, -pi, pi) * gradth);
			gx *= gy;
			gx *= colmul;	// intensity of colour
			gx += pixoffset;
			if (gx < 0.)
				gx = 0.;
			g = 32768. * gx + 0.5;
			ginv = 32768 - g;

			fb->r.l[iy*fb->w+ix].r = g * col.r + ginv * fb->r.l[iy*fb->w+ix].r >> 15;
			fb->r.l[iy*fb->w+ix].g = g * col.g + ginv * fb->r.l[iy*fb->w+ix].g >> 15;
			fb->r.l[iy*fb->w+ix].b = g * col.b + ginv * fb->r.l[iy*fb->w+ix].b >> 15;
			fb->r.l[iy*fb->w+ix].a = ONEF;
		}
	}
}

// TODO optimise using fixed point arithmetic and look-up tables
void draw_gaussian_gradient(double cx, double cy, lrgb_t c0, lrgb_t c1, double gausrad, double gausoffx, double gausoffy, const blend_func_t bf)
{
	int32_t ix, iy, p;
	double gx, gy;
	lrgb_t gc;

	for (iy=0; iy<fb->h; iy++)
	{
		gy = fastgaussianf_d1((cy - (double) iy) / gausrad + gausoffy);

		for (ix=0; ix<fb->w; ix++)
		{
			gx = fastgaussianf_d1((cx - (double) ix) / gausrad + gausoffx);
			gx *= gy;
			p = 32768. * gx + 0.5;

			gc = c0;
			blend_blend(&gc, c1, p);
			bf(&fb->r.l[iy*fb->w+ix], gc, 32768);
		}
	}
}

void draw_point_lrgb(xy_t pos, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{
	int32_t iy, ix, fbi;
	double grad;
	int32_t p, ratio;		// 0.15
	double bradius;
	int32_t bstartx, bstarty, bendx, bendy;

	const int32_t fp=16, fpr = 29;
	const double fpratio = (double) (1<<fp);
	int32_t xf, yf, radiusf;

	xf = roundaway(pos.x * fpratio);
	yf = roundaway(pos.y * fpratio);

	grad = sqrt(log(1. / (GAUSSLIMIT*intensity)));

	ratio = 32768. * intensity + 0.5;

	bradius = grad * radius;	// 2.36 for a radius of 1
	radius = 1./radius;
	radiusf = roundaway(radius * (double) (1<<29));

	bstartx = (int32_t) ceil(pos.x - bradius);	if (bstartx<0)	bstartx = 0;
	bstarty = (int32_t) ceil(pos.y - bradius);	if (bstarty<0)	bstarty = 0;
	bendx = (int32_t) floor(pos.x + bradius);	if (bendx >= fb->w) bendx = fb->w-1;
	bendy = (int32_t) floor(pos.y + bradius);	if (bendy >= fb->h) bendy = fb->h-1;

	for (iy=bstarty; iy<=bendy; iy++)
	for (ix=bstartx; ix<=bendx; ix++)
	{
		fbi = iy*fb->w+ix;

		p = fpgauss_d0((int64_t) (xf - (ix<<fp)) * radiusf >> fpr) >> 15;	// 0.15
		p *= fpgauss_d0((int64_t) (yf - (iy<<fp)) * radiusf >> fpr) >> 15;
		p = (p>>15) * ratio >> 15;

		bf(&fb->r.l[fbi], colour, p);
	}
}

void draw_point_frgb(xy_t pos, double radius, frgb_t colour, const blend_func_fl_t bf, double intensity)
{
	int32_t iy, ix, fbi;
	float ixf, iyf, p, bradius, ratio=intensity;
	int32_t bstartx, bstarty, bendx, bendy;

	bradius = GAUSSRAD_HQ * radius;

	radius = 1./radius;

	bstartx = (int32_t) ceil(pos.x - bradius);	if (bstartx<0)	bstartx = 0;
	bstarty = (int32_t) ceil(pos.y - bradius);	if (bstarty<0)	bstarty = 0;
	bendx = (int32_t) floor(pos.x + bradius);	if (bendx >= fb->w) bendx = fb->w-1;
	bendy = (int32_t) floor(pos.y + bradius);	if (bendy >= fb->h) bendy = fb->h-1;

	for (iyf=iy=bstarty; iy<=bendy; iy++, iyf+=1.)
	for (ixf=ix=bstartx; ix<=bendx; ix++, ixf+=1.)
	{
		fbi = iy*fb->w+ix;

		p = fastgaussianf_d1((pos.x - ixf) * radius);
		p *= fastgaussianf_d1((pos.y - iyf) * radius);
		p *= ratio;

		bf(&fb->r.f[fbi], colour, p);
	}
}

void draw_point_dq(xy_t pos, double radius, frgb_t colour, double intensity)
{
	double grad;
	int32_t ix, iy;
	float *df;
	recti_t bb;

	grad = GAUSSRAD_HQ * radius;		// gaussian will go to x = ±4, radially

	if (pos.x + grad < 0.)			return ;
	if (pos.y + grad < 0.)			return ;
	if (pos.x - grad > (double) (fb->w-1))	return ;
	if (pos.y - grad > (double) (fb->h-1))	return ;

	// calculate the bounding box
	bb.p0.x = MAXN(ceil(pos.x - grad), 0);
	bb.p0.y = MAXN(ceil(pos.y - grad), 0);
	bb.p1.x = MINN(floor(pos.x + grad), fb->w-1);
	bb.p1.y = MINN(floor(pos.y + grad), fb->h-1);

	bb = rshift_recti(bb, fb->sector_size);

	// store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(DQT_POINT_ADD);
	if (df==NULL)
		return;
	df[0] = pos.x;
	df[1] = pos.y;
	df[2] = 1./radius;
	df[3] = colour.r * intensity;
	df[4] = colour.g * intensity;
	df[5] = colour.b * intensity;

	// go through the affected sectors
	for (iy=bb.p0.y; iy<=bb.p1.y; iy++)
		for (ix=bb.p0.x; ix<=bb.p1.x; ix++)
			drawq_add_sector_id(iy*fb->sector_w + ix);	// add sector reference
}

void draw_point_dqnq(xy_t pos, double radius, frgb_t colour, double intensity)
{
	const enum dqnq_type type = DQNQT_POINT_ADD;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, float_as_u32(pos.x));
	write_LE32(&p, float_as_u32(pos.y));
	write_LE32(&p, float_as_u32(radius));
	write_LE32(&p, float_as_u32(colour.r * intensity));
	write_LE32(&p, float_as_u32(colour.g * intensity));
	write_LE32(&p, float_as_u32(colour.b * intensity));

	dqnq_finish_entry(type);
}

void draw_point(xy_t pos, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	if (fb->discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, &intensity, 1);	// adjusts the focus

	if (fb->use_drawq)
		if (fb->use_dqnq)
			draw_point_dqnq(pos, radius, col_to_frgb(colour), intensity);
		else
			draw_point_dq(pos, radius, col_to_frgb(colour), intensity);
	else if (fb->r.use_frgb)
		draw_point_frgb(pos, radius, col_to_frgb(colour), get_blend_fl_equivalent(bf), intensity);
	else
		draw_point_lrgb(pos, radius, col_to_lrgb(colour), bf, intensity);
}

void draw_point_on_row(xy_t pos, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{
	int32_t ix, fbi, dp;
	double grad = GAUSSRAD(intensity, radius);
	int32_t p, ratio;	// 0.15
	int32_t bstartx, bendx;

	int32_t xf, ixf, iradf;
	const int32_t fp=16;
	const double fpratio = (double) (1<<fp);

	ratio = 32768. * intensity + 0.5;

	iradf = roundaway(1./radius * fpratio);

	bstartx = (int32_t) ceil(pos.x - grad);	if (bstartx<0)	bstartx = 0;
	bendx = (int32_t) floor(pos.x + grad);	if (bendx >= fb->w) bendx = fb->w-1;

	xf = roundaway(pos.x * fpratio);

	for (ix=bstartx; ix<=bendx; ix++)
	{
		fbi = pos.y*fb->w+ix;
		ixf = ix << fp;

		dp = xf - ixf;
		dp = (int64_t) dp * iradf >> fp;

		p = fpgauss_d0(dp) >> 15;
		p = p * ratio >> 15;

		bf(&fb->r.l[fbi], colour, p);
	}
}

void draw_triangle_thin(triangle_t tr, double drawing_thickness, col_t col, const blend_func_t bf, double intensity)
{
	draw_line_thin(tr.a, tr.c, drawing_thickness, col, bf, intensity);
	draw_line_thin(tr.a, tr.b, drawing_thickness, col, bf, intensity);
	draw_line_thin(tr.b, tr.c, drawing_thickness, col, bf, intensity);
}

void draw_mousecursor(xy_t pos)
{
	col_t col = make_grey(0.5), colb = make_grey(0.);
	double sc = zc.iscrscale * 16.;
	triangle_t tr;

	if (mouse.mouse_focus_flag < 0)	// if mouse is out of window
		return ;

	if (mouse.window_focus_flag < 0 && mouse.mouse_focus_flag > 0)	// if the window is out of focus but mouse is over the window
	{
		double d;

		d = zc.iscrscale * (32. - sqrt(2.));
		drawq_bracket_open();
		draw_line_thin(sc_xy(add_xy(pos, xy(0., d))), sc_xy(add_xy(pos, xy(d, 0.))), drawing_thickness, colb, blend_alphablendfg, 2./3.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., -d))), sc_xy(add_xy(pos, xy(-d, 0.))), drawing_thickness, colb, blend_alphablendfg, 2./3.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., d))), sc_xy(add_xy(pos, xy(-d, 0.))), drawing_thickness, colb, blend_alphablendfg, 2./3.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., -d))), sc_xy(add_xy(pos, xy(d, 0.))), drawing_thickness, colb, blend_alphablendfg, 2./3.);
		drawq_bracket_close(DQB_BLEND);

		d = zc.iscrscale * 32.;
		draw_line_thin(sc_xy(add_xy(pos, xy(0., d))), sc_xy(add_xy(pos, xy(d, 0.))), drawing_thickness, col, cur_blend, 1.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., -d))), sc_xy(add_xy(pos, xy(-d, 0.))), drawing_thickness, col, cur_blend, 1.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., d))), sc_xy(add_xy(pos, xy(-d, 0.))), drawing_thickness, col, cur_blend, 1.);
		draw_line_thin(sc_xy(add_xy(pos, xy(0., -d))), sc_xy(add_xy(pos, xy(d, 0.))), drawing_thickness, col, cur_blend, 1.);
		return ;
	}

	if (mouse.showcursor)
		return ;

	tr.a = sc_xy(pos);
	tr.b = sc_xy(add_xy(pos, xy(0.*sc, -1.*sc)));
	tr.c = sc_xy(add_xy(pos, xy(0.64*sc, -0.76837*sc)));

	drawq_bracket_open();
	draw_triangle_thin(triangle_dilate(tr, -1.), drawing_thickness, colb, blend_alphablendfg, 2./3.);
	drawq_bracket_close(DQB_BLEND);

	draw_triangle_thin(tr, drawing_thickness, col, cur_blend, 1.);
}

void draw_polygon_dq(xy_t *p, int p_count, double radius, frgb_t colour, double intensity)
{
	int i;
	float *df;
	double grad;
	xyi_t ip;
	recti_t bbi;

	if (p_count < 3 || p_count > 4)
		return;

	grad = 3. * radius;

	if (drawq_get_bounding_box_for_polygon(p, p_count, set_xy(grad), &bbi) == 0)
		return;

	// Store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(p_count==3 ? DQT_TRIANGLE : DQT_TETRAGON);
	df[0] = 1./radius;
	df[1] = colour.r * intensity;
	df[2] = colour.g * intensity;
	df[3] = colour.b * intensity;
	for (i=0; i < p_count; i++)
	{
		df[4+i*2] = p[i].x;
		df[5+i*2] = p[i].y;
	}

	// Find the affected sectors
	for (ip.y=bbi.p0.y; ip.y<=bbi.p1.y; ip.y++)
		for (ip.x=bbi.p0.x; ip.x<=bbi.p1.x; ip.x++)
			drawq_add_sector_id(ip.y*fb->sector_w + ip.x);	// add sector reference
}

void draw_polygon(xy_t *p, int p_count, double radius, col_t colour, double intensity)
{
	if (fb->discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, NULL, 0);	// adjusts the focus

	if (fb->use_drawq)
		draw_polygon_dq(p, p_count, radius, col_to_frgb(colour), intensity);
	// TODO lrgb version
}

void draw_polygon_wc(xy_t *p, int p_count, double radius, col_t colour, double intensity)
{
	int i;
	xy_t p_sc[16];

	// Convert to screen coordinates in reverse order
	for (i=0; i < p_count; i++)
		p_sc[p_count-1-i] = sc_xy(p[i]);

	draw_polygon(p_sc, p_count, radius, colour, intensity);
}

void draw_triangle(triangle_t tri, double radius, col_t colour, double intensity)
{
	draw_polygon((xy_t *) &tri, 3, radius, colour, intensity);
}

void draw_triangle_wc(triangle_t tri, double radius, col_t colour, double intensity)
{
	draw_polygon_wc((xy_t *) &tri, 3, radius, colour, intensity);
}
