void draw_rect_full_dq(rect_t box, double radius, frgb_t colour, double intensity)
{
	float *df;
	double grad;
	xyi_t ip;
	rect_t fr, screen_box = rect(XY0, xy(fb->w-1, fb->h-1));
	recti_t bbi, fri;

	if (intensity==0.)
		return ;

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4

	if (drawq_get_bounding_box(box, set_xy(grad), &bbi)==0)
			return ;

	box = sort_rect(box);

	// calculate the fill rectangle, which is the inner rectangle where sectors are just filled plainly
	fr.p0 = ceil_xy(add_xy(box.p0, set_xy(grad)));
	fr.p1 = floor_xy(sub_xy(box.p1, set_xy(grad)));

	fri.p0 = xy_to_xyi(max_xy(fr.p0, screen_box.p0));
	fri.p1 = xy_to_xyi(min_xy(fr.p1, screen_box.p1));
	fri = rshift_recti(fri, fb->sector_size);

	if (fri.p1.x <= fri.p0.x || fri.p1.y <= fri.p0.y)	// if there is no plain fill area
		fri = recti(xyi(-1,-1), xyi(-1,-1));

	// calculate the drawing parameters
	colour.r *= intensity;
	colour.g *= intensity;
	colour.b *= intensity;

	// store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(DQT_RECT_FULL);
	df[0] = box.p0.x;
	df[1] = box.p0.y;
	df[2] = box.p1.x;
	df[3] = box.p1.y;
	df[4] = 1./radius;
	df[5] = colour.r;
	df[6] = colour.g;
	df[7] = colour.b;

	// find the affected sectors
	for (ip.y=bbi.p0.y; ip.y<=bbi.p1.y; ip.y++)
		for (ip.x=bbi.p0.x; ip.x<=bbi.p1.x; ip.x++)
			if (check_point_within_box_int(ip, fri)!=1)			// if we're not inside the plain fill area
				drawq_add_sector_id(ip.y*fb->sector_w + ip.x);	// add sector reference

	if (fri.p0.x == -1)
		return ;

	//************PLAIN FILL AREA************

	df = drawq_add_to_main_queue(DQT_PLAIN_FILL);
	df[0] = colour.r;
	df[1] = colour.g;
	df[2] = colour.b;

	// find the affected sectors
	for (ip.y=fri.p0.y; ip.y<=fri.p1.y; ip.y++)
		for (ip.x=fri.p0.x; ip.x<=fri.p1.x; ip.x++)
			if (check_point_within_box_int(xyi(ip.x, ip.y), fri)==1)	// if we're inside the plain fill area
				drawq_add_sector_id(ip.y*fb->sector_w + ip.x);	// add sector reference
}

void draw_rect_full_lrgb(rect_t box, double radius, lrgb_t colour, const blend_func_t bf, double intensity)
{
	double grad;
	xyi_t ip, pf, d0, d1, gv;
	rect_t gr, fr, screen_box = rect(XY0, xy(fb->w-1, fb->h-1));
	recti_t gri, fri, rfp;
	int32_t fbi, p, iradf, ratio;
	const int32_t fp=16;
	const double fpratio = (double) (1<<fp);

	ratio = 32768. * intensity + 0.5;
	if (ratio == 0)
		return ;

	iradf = roundaway(1./radius * fpratio);

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4

	box = sort_rect(box);
	rfp = rect_to_recti_fixedpoint(box, fpratio);

	// calculate the gauss rectangle, which is the outer rectangle that contains all the pixels
	gr.p0 = ceil_xy(sub_xy(box.p0, set_xy(grad)));
	gr.p1 = floor_xy(add_xy(box.p1, set_xy(grad)));

	gri.p0 = xy_to_xyi(max_xy(gr.p0, screen_box.p0));
	gri.p1 = xy_to_xyi(min_xy(gr.p1, screen_box.p1));

	// calculate the fill rectangle, which is the inner rectangle where pixels are just filled plainly
	fr.p0 = ceil_xy(add_xy(box.p0, set_xy(grad)));
	fr.p1 = floor_xy(sub_xy(box.p1, set_xy(grad)));

	fri.p0 = xy_to_xyi(max_xy(fr.p0, screen_box.p0));
	fri.p1 = xy_to_xyi(min_xy(fr.p1, screen_box.p1));

	if (fri.p1.x <= fri.p0.x || fri.p1.y <= fri.p0.y)	// if there is no plain fill area
	{
		for (ip.y=gri.p0.y; ip.y<=gri.p1.y; ip.y++)
		{
			pf.y = ip.y << fp;
			d0.y = (int64_t) (pf.y - rfp.p0.y) * iradf >> fp;
			d1.y = (int64_t) (pf.y - rfp.p1.y) * iradf >> fp;
			gv.y = (fperfr_d0(d0.y) - fperfr_d0(d1.y)) >> 15;

			for (ip.x=gri.p0.x; ip.x<=gri.p1.x; ip.x++)
			{
				fbi = ip.y*fb->w + ip.x;

				pf.x = ip.x << fp;
				d0.x = (int64_t) (pf.x - rfp.p0.x) * iradf >> fp;
				d1.x = (int64_t) (pf.x - rfp.p1.x) * iradf >> fp;
				gv.x = (fperfr_d0(d0.x) - fperfr_d0(d1.x)) >> 15;
				p = gv.x * gv.y >> 15;
				p = p * ratio >> 15;

				bf(&fb->r.l[fbi], colour, p);
			}
		}
	}
	else
	{
		// first Y section
		for (ip.y=gri.p0.y; ip.y < fri.p0.y; ip.y++)
		{
			pf.y = ip.y << fp;
			d0.y = (int64_t) (pf.y - rfp.p0.y) * iradf >> fp;
			gv.y = fperfr_d0(d0.y) >> 15;

			for (ip.x=gri.p0.x; ip.x < fri.p0.x; ip.x++)	// first X section
			{
				pf.x = ip.x << fp;
				d0.x = (int64_t) (pf.x - rfp.p0.x) * iradf >> fp;
				gv.x = fperfr_d0(d0.x) >> 15;
				p = gv.x * gv.y >> 15;
				p = p * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}

			p = gv.y * ratio >> 15;
			for (; ip.x <= fri.p1.x; ip.x++)		// mid X section
				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);

			for (; ip.x <= gri.p1.x; ip.x++)		// last X section
			{
				pf.x = ip.x << fp;
				d1.x = (int64_t) (pf.x - rfp.p1.x) * iradf >> fp;
				gv.x = fperfr_d0(-d1.x) >> 15;
				p = gv.x * gv.y >> 15;
				p = p * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}
		}

		// mid Y section
		for (; ip.y <= fri.p1.y; ip.y++)
		{
			for (ip.x=gri.p0.x; ip.x < fri.p0.x; ip.x++)	// first X section
			{
				pf.x = ip.x << fp;
				d0.x = (int64_t) (pf.x - rfp.p0.x) * iradf >> fp;
				gv.x = fperfr_d0(d0.x) >> 15;
				p = gv.x * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}

			for (; ip.x <= fri.p1.x; ip.x++)		// mid X section
				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, ratio);

			for (; ip.x <= gri.p1.x; ip.x++)		// last X section
			{
				pf.x = ip.x << fp;
				d1.x = (int64_t) (pf.x - rfp.p1.x) * iradf >> fp;
				gv.x = fperfr_d0(-d1.x) >> 15;
				p = gv.x * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}
		}

		// last Y section
		for (; ip.y <= gri.p1.y; ip.y++)
		{
			pf.y = ip.y << fp;
			d1.y = (int64_t) (pf.y - rfp.p1.y) * iradf >> fp;
			gv.y = fperfr_d0(-d1.y) >> 15;

			// this block of code is the same as in the first Y section
			for (ip.x=gri.p0.x; ip.x < fri.p0.x; ip.x++)	// first X section
			{
				pf.x = ip.x << fp;
				d0.x = (int64_t) (pf.x - rfp.p0.x) * iradf >> fp;
				gv.x = fperfr_d0(d0.x) >> 15;
				p = gv.x * gv.y >> 15;
				p = p * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}

			p = gv.y * ratio >> 15;
			for (; ip.x <= fri.p1.x; ip.x++)		// mid X section
				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);

			for (; ip.x <= gri.p1.x; ip.x++)		// last X section
			{
				pf.x = ip.x << fp;
				d1.x = (int64_t) (pf.x - rfp.p1.x) * iradf >> fp;
				gv.x = fperfr_d0(-d1.x) >> 15;
				p = gv.x * gv.y >> 15;
				p = p * ratio >> 15;

				bf(&fb->r.l[ip.y*fb->w + ip.x], colour, p);
			}
		}
	}
}

void draw_rect_full_dqnq(rect_t box, double radius, frgb_t colour, double intensity)
{
	const enum dqnq_type type = DQNQT_RECT_FULL;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, float_as_u32(box.p0.x));
	write_LE32(&p, float_as_u32(box.p0.y));
	write_LE32(&p, float_as_u32(box.p1.x));
	write_LE32(&p, float_as_u32(box.p1.y));
	write_LE32(&p, float_as_u32(radius));
	write_LE32(&p, float_as_u32(colour.r * intensity));
	write_LE32(&p, float_as_u32(colour.g * intensity));
	write_LE32(&p, float_as_u32(colour.b * intensity));

	dqnq_finish_entry(type);
}

void draw_rect_full(rect_t box, double radius, col_t colour, const blend_func_t bf, double intensity)
{
	if (fb->discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, NULL, 0);	// adjusts the focus

	if (fb->use_drawq)
		if (fb->use_dqnq)
			draw_rect_full_dqnq(box, radius, col_to_frgb(colour), intensity);
		else
			draw_rect_full_dq(box, radius, col_to_frgb(colour), intensity);
	else
		draw_rect_full_lrgb(box, radius, col_to_lrgb(colour), bf, intensity);
}

void draw_black_rect_dq(rect_t box, double radius, double intensity)
{
	float *df;
	double grad;
	xyi_t ip;
	recti_t bbi;

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4

	if (drawq_get_bounding_box(box, set_xy(grad), &bbi)==0)
			return ;

	box = sort_rect(box);

	// Store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(DQT_RECT_BLACK);
	df[0] = box.p0.x;
	df[1] = box.p0.y;
	df[2] = box.p1.x;
	df[3] = box.p1.y;
	df[4] = 1./radius;
	df[5] = intensity;

	// Find the affected sectors
	for (ip.y=bbi.p0.y; ip.y<=bbi.p1.y; ip.y++)
		for (ip.x=bbi.p0.x; ip.x<=bbi.p1.x; ip.x++)
		{
			int32_t sector_id = ip.y*fb->sector_w + ip.x;
			if (fb->sector_count[sector_id] > 0 && fb->pending_bracket[sector_id] == 0)	// if the sector contains something at the current bracket level
				drawq_add_sector_id(sector_id);	// add sector reference
		}

	// TODO clear lists in obscured sectors, don't add to empty sectors
}

void draw_black_rect_dqnq(rect_t box, double radius, double intensity)
{
	const enum dqnq_type type = DQNQT_RECT_BLACK;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, float_as_u32(box.p0.x));
	write_LE32(&p, float_as_u32(box.p0.y));
	write_LE32(&p, float_as_u32(box.p1.x));
	write_LE32(&p, float_as_u32(box.p1.y));
	write_LE32(&p, float_as_u32(radius));
	write_LE32(&p, float_as_u32(intensity));

	dqnq_finish_entry(type);
}

void draw_black_rect(rect_t box, double radius, double intensity)
{
	if (fb->discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, NULL, 0);	// adjusts the focus

	if (fb->use_drawq)
		if (fb->use_dqnq)
			draw_black_rect_dqnq(box, radius, intensity);
		else
			draw_black_rect_dq(box, radius, intensity);
	else
		draw_rect_full_lrgb(box, radius, col_to_lrgb(make_grey(0.)), blend_alphablendfg, intensity);
}

void draw_black_rect_inverted_dq(rect_t box, double radius, double intensity)
{
	float *df;
	double grad;
	xyi_t ip;
	recti_t bbi;

	grad = GAUSSRAD_HQ * radius;		// erfr and gaussian can go up to x = ±4

	drawq_get_inner_box(box, set_xy(grad), &bbi);

	box = sort_rect(box);

	// Store the drawing parameters in the main drawing queue
	df = drawq_add_to_main_queue(DQT_RECT_BLACK_INV);
	df[0] = box.p0.x;
	df[1] = box.p0.y;
	df[2] = box.p1.x;
	df[3] = box.p1.y;
	df[4] = 1./radius;
	df[5] = intensity;

	// Find the affected sectors (all sectors outside the inner box)
	rect_t screen_box = rect(XY0, xy(fb->w-1, fb->h-1));
	for (ip.y=0; ip.y <= fb->h-1 >> fb->sector_size; ip.y++)
		for (ip.x=0; ip.x <= fb->w-1 >> fb->sector_size; ip.x++)
			if (ip.x <= bbi.p0.x || ip.y <= bbi.p0.y || ip.x >= bbi.p1.x || ip.y >= bbi.p1.y)
			{
				int32_t sector_id = ip.y*fb->sector_w + ip.x;
				if (fb->sector_count[sector_id] > 0 && fb->pending_bracket[sector_id] == 0)	// if the sector contains something at the current bracket level
					drawq_add_sector_id(sector_id);	// add sector reference
			}
}

void draw_black_rect_inverted_dqnq(rect_t box, double radius, double intensity)
{
	const enum dqnq_type type = DQNQT_RECT_BLACK_INV;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, float_as_u32(box.p0.x));
	write_LE32(&p, float_as_u32(box.p0.y));
	write_LE32(&p, float_as_u32(box.p1.x));
	write_LE32(&p, float_as_u32(box.p1.y));
	write_LE32(&p, float_as_u32(radius));
	write_LE32(&p, float_as_u32(intensity));

	dqnq_finish_entry(type);
}

void draw_black_rect_inverted(rect_t box, double radius, double intensity)
{
	if (fb->discard)
		return;

	radius = drawing_focus_adjust(focus_rlg, radius, NULL, 0);	// adjusts the focus

	if (fb->use_drawq)
		if (fb->use_dqnq)
			draw_black_rect_inverted_dqnq(box, radius, intensity);
		else
			draw_black_rect_inverted_dq(box, radius, intensity);
	// TODO lrgb version
}
