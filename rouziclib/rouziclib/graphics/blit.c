// only used in spacewar's blit_hrgb_sprite* (game.c)
int sprite_offsets_old(int32_t fbw, int32_t fbh, int32_t spw, int32_t sph, int32_t *pos_x, int32_t *pos_y, int32_t *offset_x, int32_t *offset_y, int32_t *start_x, int32_t *start_y, int32_t *stop_x, int32_t *stop_y, int hmode, int vmode)
{
	if (hmode==A_CEN)	*pos_x -= (spw>>1);
	if (hmode==A_RIG)	*pos_x -= (spw-1);
	if (vmode==A_CEN)	*pos_y -= (sph>>1);
	if (vmode==A_BOT)	*pos_y -= (sph-1);

	*offset_x = *pos_x;
	*offset_y = *pos_y;
	if (*pos_x < 0)		*start_x = -*pos_x;	else	*start_x = 0;
	if (*pos_y < 0)		*start_y = -*pos_y;	else	*start_y = 0;
	if (*pos_x+spw >= fbw)	*stop_x = fbw - *pos_x;	else	*stop_x = spw;
	if (*pos_y+sph >= fbh)	*stop_y = fbh - *pos_y;	else	*stop_y = sph;

	if (*stop_x <= *start_x || *stop_y <= *start_y)
		return 1;					// a return value of 1 means the sprite is off-screen
	return 0;
}

int sprite_offsets(raster_t r, xyi_t *pos, xyi_t *offset, xyi_t *start, xyi_t *stop, int hmode, int vmode)
{
	if (hmode==A_CEN)	pos->x -= (r.dim.x>>1);
	if (hmode==A_RIG)	pos->x -= (r.dim.x-1);
	if (vmode==A_CEN)	pos->y -= (r.dim.y>>1);
	if (vmode==A_BOT)	pos->y -= (r.dim.y-1);

	offset->x = pos->x;
	offset->y = pos->y;
	if (pos->x < 0)			start->x = -pos->x;		else	start->x = 0;
	if (pos->y < 0)			start->y = -pos->y;		else	start->y = 0;
	if (pos->x+r.dim.x >= fb->r.dim.x)	stop->x = fb->r.dim.x - pos->x;	else	stop->x = r.dim.x;
	if (pos->y+r.dim.y >= fb->r.dim.y)	stop->y = fb->r.dim.y - pos->y;	else	stop->y = r.dim.y;

	if (stop->x <= start->x || stop->y <= start->y)
		return 1;					// a return value of 1 means the sprite is off-screen
	return 0;
}

int calc_blit_bounds(xyi_t in_dim, xyi_t out_dim, xyi_t offset, recti_t *bounds)
{
	bounds->p0 = max_xyi(neg_xyi(offset), XYI0);
	bounds->p1 = min_xyi(sub_xyi(out_dim, offset), in_dim);

	if (bounds->p1.x <= bounds->p0.x || bounds->p1.y <= bounds->p0.y)
		return 1;
	return 0;
}

#include <string.h>	// for memcpy
void blit_sprite(raster_t r, xyi_t pos, const blend_func_t bf, int hmode, int vmode)
{
	int32_t iy_r0, iy_r1;
	int32_t ix, iy;
	xyi_t offset, start, stop;

	if (sprite_offsets(r, &pos, &offset, &start, &stop, hmode, vmode))
		return ;

	if (bf==blend_solid)	// if the sprite is opaque then it can be blitted whole lines at a time
	{
		for (iy=start.y; iy<stop.y; iy++)
		{
			iy_r0 = (iy + offset.y) * fb->r.dim.x + offset.x;
			iy_r1 = iy * r.dim.x;
			memcpy(&fb->r.l[iy_r0+start.x], &r.l[iy_r1+start.x], (stop.x-start.x) * sizeof(lrgb_t));
		}
		return;
	}

	for (iy=start.y; iy<stop.y; iy++)
	{
		iy_r0 = (iy + offset.y) * fb->r.dim.x + offset.x;
		iy_r1 = iy * r.dim.x;

		for (ix=start.x; ix<stop.x; ix++)
		{
			bf(&fb->r.l[iy_r0+ix], r.l[iy_r1+ix], 32768);
		}
	}
}

void blit_layout(raster_t r)
{
	int32_t i, wh;
	lrgb_t *p;

	// Current layout: ONES: 349998   MIDS: 20470   ZEROS: 169436
	// Cycles:	ONES: 7		MIDS: 11	ZEROS: ~0

	wh = fb->r.dim.x * fb->r.dim.y;
	for (i=0; i<wh; i++)
	{
		p = &r.l[i];

		if (p->a)
		if (p->a==ONE)
			fb->r.l[i] = *p;
		else
		{
			fb->r.l[i].r = (((int32_t) p->r - (int32_t) fb->r.l[i].r) * p->a >> LBD) + fb->r.l[i].r;
			fb->r.l[i].g = (((int32_t) p->g - (int32_t) fb->r.l[i].g) * p->a >> LBD) + fb->r.l[i].g;
			fb->r.l[i].b = (((int32_t) p->b - (int32_t) fb->r.l[i].b) * p->a >> LBD) + fb->r.l[i].b;
		}
	}
}

void blit_scale_nearest(raster_t r, xy_t pos, xy_t ipscale, xyi_t start, xyi_t stop)
{
	int32_t ix, iy, biyw;
	static int32_t lastw=0, *xluti=NULL;

	if (r.l==NULL)
		return ;

	if (lastw <= fb->r.dim.x)		// if the width of the screen has increased
	{
		lastw = fb->r.dim.x;
		if (xluti) free (xluti);
		xluti = calloc (fb->r.dim.x, sizeof(int32_t));	// change the size of xluti
	}

	for (ix=start.x; ix<stop.x; ix++)	// recompute LUT
		xluti[ix] = rangelimit_i32( nearbyint(((double) ix - pos.x) * ipscale.x) , 0, r.dim.x-1);

	for (iy=start.y; iy<stop.y; iy++)
	{
		biyw = rangelimit_i32( nearbyint(((double) iy - pos.y) * ipscale.y) , 0, r.dim.y-1) * r.dim.x;

		for (ix=start.x; ix<stop.x; ix++)
		{
			fb->r.l[iy*fb->r.dim.x + ix] = r.l[biyw + xluti[ix]];
		}
	}
}

void blit_scale_lrgb(raster_t r, xy_t pscale, xy_t pos, int interp)
{
	int32_t i, ic, iy, ix, jx, jy;
	xyi_t start, stop, jstart, jstop;
	float sumf[4];
	xy_t p0, p1, pin, kr0, ikr0, kr1, ipscale = inv_xy(pscale), iw;
	int32_t nsx, nsy;	// number of samples to get
	double iw_xy;
	interp_param_t param_x, param_y;

	if (r.l==NULL && r.sq==NULL)
		return ;

	switch (interp)
	{
		case NEAREST_INTERP:
			kr1 = set_xy(0.5);	// kernel radiuses at the rescaled level
			break;

		case LINEAR_INTERP:
			kr1 = set_xy(1.0);
			break;

		case GAUSSIAN_INTERP:
			kr1 = set_xy(2.4);	// pretty arbitrary
			break;
	}

	kr0 = kr1;				// kernel radiuses at the unscaled level
	if (pscale.x < 1.)
		kr0.x *= ipscale.x;

	if (pscale.y < 1.)
		kr0.y *= ipscale.y;

	ikr0 = inv_xy(kr0);			// ikr0 = ]0 , 1]

	param_x = calc_interp_param_modlin(ikr0.x);
	param_y = calc_interp_param_modlin(ikr0.y);

	nsx = kr0.x * 2.;			// number of input samples necessary for each pixel
	nsy = kr0.y * 2.;

	// find start and stop indices
	p0 = mad_xy(pscale, neg_xy(kr1), pos);
	p1 = mad_xy(pscale, add_xy(kr1, xy(r.dim.x-1, r.dim.y-1)), pos);

	start.x = MAXN(0, floor(MINN(p0.x, p1.x)));
	start.y = MAXN(0, floor(MINN(p0.y, p1.y)));
	stop.x = MINN(fb->r.dim.x, ceil(MAXN(p0.x, p1.x)+1));	// not sure about the logic of the +1 but it works with LINEAR_INTERP
	stop.y = MINN(fb->r.dim.y, ceil(MAXN(p0.y, p1.y)+1));

	if (nsx*nsy == 1)		// if unfiltered nearest neighbour (only 1 pixel in -> 1 pixel out)
	{
		blit_scale_nearest(r, pos, ipscale, start, stop);
	}
	else
	{
		for (iy=start.y; iy<stop.y; iy++)
		{
			pin.y = ((double) iy - pos.y) * ipscale.y;
			jstart.y = floor(pin.y - kr0.y)+1;		if (jstart.y < 0) jstart.y = 0;
			jstop.y = ceil(pin.y + kr0.y);			if (jstop.y > r.dim.y) jstop.y = r.dim.y;

			for (ix=start.x; ix<stop.x; ix++)
			{
				pin.x = ((double) ix - pos.x) * ipscale.x;
				jstart.x = floor(pin.x - kr0.x)+1;	if (jstart.x < 0) jstart.x = 0;
				jstop.x = ceil(pin.x + kr0.x);		if (jstop.x > r.dim.x) jstop.x = r.dim.x;
				//jstop.x = jstart.x + nsx;	if (jstop.x > r.dim.x) jstop.x = r.dim.x;

				memset(sumf, 0, 4*sizeof(float));		// blank the new sum pixel

				for (jy=jstart.y; jy<jstop.y; jy++)
				{
					iw.y = param_y.func((double) jy - pin.y, ikr0.y, param_y);

					for (jx=jstart.x; jx<jstop.x; jx++)
					{
						iw.x = param_x.func((double) jx - pin.x, ikr0.x, param_x);
						iw_xy = iw.x * iw.y;		// interpolation weight
						i = jy * r.dim.x + jx;

						if (r.sq)
						{
							*((frgb_t *)(&sumf)) = add_frgba(*((frgb_t *)(&sumf)), mul_scalar_frgba(sqrgb_to_frgb(r.sq[i]), ONEF*iw_xy));
						}
						else
						{
							for (ic=0; ic<3; ic++)
							{
								sumf[ic] += ((uint16_t *) &r.l[i])[ic] * iw_xy;
							}
						}
					}
				}

				for (ic=0; ic<3; ic++)
					((uint16_t *) &fb->r.l[iy*fb->r.dim.x + ix])[ic] = ((uint16_t *) &fb->r.l[iy*fb->r.dim.x + ix])[ic] + (uint16_t) (sumf[ic] + 0.5f);
			}
		}
	}
}

void blit_scale_frgb(raster_t r, xy_t pscale, xy_t pos, int interp)
{
	if (r.f==NULL || fb->r.f==NULL)
		return ;

	blit_scale_float(fb->r.f, fb->r.dim, r.f, r.dim, 4, pscale, pos, get_pixel_address_contig);
}

void blit_scale_dq(raster_t *r, xy_t pscale, xy_t pos, int interp)
{
	int ix, iy;
	int32_t *di;
	float *df;
	uint64_t dqbuf_da;
	xy_t rad;
	recti_t bbi;
	int flattop=0, aa_nearest=0;

	if (r->f==NULL && r->sq==NULL && r->srgb==NULL && r->buf==NULL && r->l==NULL)
		return ;

	//if (pscale.x < 1. || pscale.y < 1.)
		flattop = 1;

	if (interp==AA_NEAREST_INTERP && pscale.x >= 1. && pscale.y >= 1.)
	{
		flattop = 0;
		aa_nearest = 1;
	}

	if (aa_nearest)
		rad = add_xy(max_xy(set_xy(0.5), pscale), XY1);
	else
		rad = max_xy(set_xy(1.), pscale);	// for interp == LINEAR_INTERP where the radius is 1 * pscale

	if (drawq_get_bounding_box(make_rect_off(pos, mul_xy( xyi_to_xy(sub_xyi(r->dim, xyi(1, 1))) , pscale ), XY0), rad, &bbi)==0)
		return ;

	dqbuf_da = cl_add_raster_to_data_table(r);

	// Store the drawing parameters in the main drawing queue
	di = drawq_add_to_main_queue(flattop ? DQT_BLIT_FLATTOP : (aa_nearest ? DQT_BLIT_AANEAREST : DQT_BLIT_BILINEAR));
	df = (float *) di;
	di[0] = dqbuf_da;
	di[1] = dqbuf_da >> 32;
	di[2] = r->dim.x;
	di[3] = r->dim.y;
	df[4] = 1./pscale.x;
	df[5] = 1./pscale.y;
	df[6] = -pos.x;
	df[7] = -pos.y;
	if (r->buf)
		di[8] = r->buf_fmt;
	else
		di[8] = r->sq ? 1 : (r->srgb ? 2 : (r->l ? 3 : 0));

	if (flattop)
	{
		pscale = min_xy(pscale, set_xy(1.));
		df[9] = calc_flattop_slope(1./pscale.x);
		df[10] = calc_flattop_slope(1./pscale.y);
	}

	// Go through the affected sectors
	for (iy=bbi.p0.y; iy<=bbi.p1.y; iy++)
		for (ix=bbi.p0.x; ix<=bbi.p1.x; ix++)
			drawq_add_sector_id(iy*fb->sector_w + ix);	// add sector reference
}

void blit_scale(raster_t *r, xy_t pscale, xy_t pos, int interp)
{
	if (fb->discard)
		return;

	if (fb->use_drawq)
		blit_scale_dq(r, pscale, pos, interp);
	else if (fb->r.use_frgb==0)
		blit_scale_lrgb(*r, pscale, pos, interp);
	else
		blit_scale_frgb(*r, pscale, pos, interp);
}

void blit_scale_rotated_dq(raster_t *r, xy_t pscale, xy_t pos, double angle, xy_t rot_centre, int interp)
{
	int i, ix, iy;
	int32_t *di;
	float *df;
	uint64_t dqbuf_da;
	xy_t rad;
	recti_t bbi;
	double costh=1., sinth=0.;
	rect_t obr, rbr;
	xy_t rp[4];
	int aa_nearest=0;

	if (r->f==NULL && r->sq==NULL && r->srgb==NULL && r->buf==NULL && r->l==NULL)
		return ;

	if (interp==AA_NEAREST_INTERP && pscale.x >= 1. && pscale.y >= 1.)
		aa_nearest = 1;

	if (aa_nearest)
		rad = add_xy(max_xy(set_xy(0.5), pscale), XY1);
	else
		rad = max_xy(set_xy(1.), pscale);	// for interp == LINEAR_INTERP where the radius is 1 * pscale

	costh = cos(angle);
	sinth = sin(angle);

	// pos originally is the screen position of the first pixel if angle was 0
	// we must turn it into the screen position after rotation around rot_centre
	obr = rect_add_margin(make_rect_off(pos, mul_xy( xyi_to_xy(sub_xyi(r->dim, xyi(1, 1))) , pscale ), XY0), rad);		// original bounding rectangle
	pos = rotate_xy2_pre_around_point(pos, rot_centre, costh, sinth);
	rp[0] = rotate_xy2_pre_around_point(obr.p0, rot_centre, costh, sinth);
	rp[1] = rotate_xy2_pre_around_point(rect_p01(obr), rot_centre, costh, sinth);
	rp[2] = rotate_xy2_pre_around_point(rect_p10(obr), rot_centre, costh, sinth);
	rp[3] = rotate_xy2_pre_around_point(obr.p1, rot_centre, costh, sinth);
	rbr.p0 = rp[0];
	rbr.p1 = rp[0];
	for (i=1; i < 4; i++)		// rbr is a bounding rectangle that contains the rotated rectangle
	{
		rbr.p0 = min_xy(rbr.p0, rp[i]);
		rbr.p1 = max_xy(rbr.p1, rp[i]);
	}

	if (drawq_get_bounding_box(rbr, rad, &bbi)==0)
		return ;

	dqbuf_da = cl_add_raster_to_data_table(r);

	// store the drawing parameters in the main drawing queue
	di = drawq_add_to_main_queue(aa_nearest ? DQT_BLIT_AANEAREST_ROT : DQT_BLIT_FLATTOP_ROT);
	df = (float *) di;
	di[0] = dqbuf_da;
	di[1] = dqbuf_da >> 32;
	di[2] = r->dim.x;
	di[3] = r->dim.y;
	df[4] = 1./pscale.x;
	df[5] = -pos.x;
	df[6] = -pos.y;
	if (r->buf)
		di[7] = r->buf_fmt;
	else
		di[7] = r->sq ? 1 : (r->srgb ? 2 : (r->l ? 3 : 0));

	if (aa_nearest)
	{
		df[8] = costh;
		df[9] = -sinth;
	}
	else
	{
		pscale = min_xy(pscale, set_xy(1.));
		df[8] = calc_flattop_slope(1./pscale.x);
		df[9] = costh;
		df[10] = -sinth;
	}

	// go through the affected sectors
	for (iy=bbi.p0.y; iy<=bbi.p1.y; iy++)
		for (ix=bbi.p0.x; ix<=bbi.p1.x; ix++)
			drawq_add_sector_id(iy*fb->sector_w + ix);	// add sector reference
}

void blit_scale_rotated(raster_t *r, xy_t pscale, xy_t pos, double angle, xy_t rot_centre, int interp)
{
	if (fb->discard)
		return;

	if (angle==0.)
	{
		blit_scale(r, pscale, pos, interp);
		return ;
	}

	if (fb->use_drawq)
		blit_scale_rotated_dq(r, pscale, pos, angle, rot_centre, interp);
}

rect_t blit_in_rect_off_rotated(raster_t *raster, rect_t r, xy_t off, int keep_aspect_ratio, double angle, xy_t rot_centre, int interp)
{
	xy_t pscale, pos;
	rect_t image_frame = r;

	if (keep_aspect_ratio)
		image_frame = fit_rect_in_area( xyi_to_xy(raster->dim), image_frame, off );

	pscale = div_xy(get_rect_dim(image_frame), xyi_to_xy(raster->dim));
	pos = mad_xy(pscale, set_xy(0.5), keep_aspect_ratio ? image_frame.p0 : rect_p01(image_frame));

	blit_scale_rotated(raster, pscale, pos, angle, rot_centre, interp);

	return wc_rect(image_frame);
}

rect_t blit_in_rect_rotated(raster_t *raster, rect_t r, int keep_aspect_ratio, double angle, xy_t rot_centre, int interp)
{
	return blit_in_rect_off_rotated(raster, r, xy(0.5, 0.5), keep_aspect_ratio, angle, rot_centre, interp);
}
