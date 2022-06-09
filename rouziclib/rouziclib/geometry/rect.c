rect_t rect(const xy_t p0, const xy_t p1)
{
	rect_t r;

	r.p0 = p0;
	r.p1 = p1;

	return r;
}

recti_t recti(const xyi_t p0, const xyi_t p1)
{
	recti_t r;

	r.p0 = p0;
	r.p1 = p1;

	return r;
}

rectq_t rectq(const xyq_t p0, const xyq_t p1)
{
	rectq_t r;

	r.p0 = p0;
	r.p1 = p1;

	return r;
}

triangle_t triangle(const xy_t a, const xy_t b, const xy_t c)
{
	triangle_t tr;

	tr.a = a;
	tr.b = b;
	tr.c = c;

	return tr;
}

recti_t rect_to_recti(const rect_t r)
{
	return recti(xy_to_xyi(r.p0), xy_to_xyi(r.p1));
}

recti_t rect_to_recti_round(const rect_t r)
{
	return recti(xy_to_xyi_round(r.p0), xy_to_xyi_round(r.p1));
}

rect_t recti_to_rect(const recti_t ri)
{
	return rect(xyi_to_xy(ri.p0), xyi_to_xy(ri.p1));
}

recti_t rect_to_recti_fixedpoint(const rect_t r, const double fpratio)	// fpratio should be something like 1<<16
{
	recti_t rfp;
	rfp.p0.x = roundaway(r.p0.x * fpratio);
	rfp.p0.y = roundaway(r.p0.y * fpratio);
	rfp.p1.x = roundaway(r.p1.x * fpratio);
	rfp.p1.y = roundaway(r.p1.y * fpratio);

	return rfp;
}

xy_t rect_p01(rect_t r)
{
	return xy(r.p0.x, r.p1.y);
}

xy_t rect_p10(rect_t r)
{
	return xy(r.p1.x, r.p0.y);
}

xyi_t recti_p01(recti_t r)
{
	return xyi(r.p0.x, r.p1.y);
}

xyi_t recti_p10(recti_t r)
{
	return xyi(r.p1.x, r.p0.y);
}

void rect_set_p01(rect_t *r, xy_t c)
{
	r->p0.x = c.x;
	r->p1.y = c.y;
}

void rect_set_p10(rect_t *r, xy_t c)
{
	r->p1.x = c.x;
	r->p0.y = c.y;
}

rect_t mul_rect(rect_t r, xy_t m)
{
	return rect(mul_xy(r.p0, m), mul_xy(r.p1, m));
}

recti_t rshift_recti(recti_t r, int sh)
{
	return recti( rshift_xyi(r.p0, sh), rshift_xyi(r.p1, sh) );
}

xy_t get_rect_centre(rect_t r)
{
	return mul_xy(set_xy(0.5), add_xy(r.p0, r.p1));
}

xyi_t get_recti_centre(recti_t r)
{
	return rshift_xyi(add_xyi(r.p0, r.p1), 1);
}

xy_t get_rect_dim(rect_t r)
{
	return abs_xy(sub_xy(r.p1, r.p0));
}

xyi_t get_recti_dim(recti_t r)		// assuming that r represents a grid defined by its lowest (r.p0) and highest (r.p1) indices
{
	return add_xyi(set_xyi(1), sub_xyi(r.p1, r.p0));
}

double get_rect_area(rect_t r)
{
	xy_t dim = get_rect_dim(r);
	return dim.x * dim.y;
}

rect_t get_rect_centred_coord(rect_t r)		// get a centre coord and width/height from a rect
{
	return rect( get_rect_centre(r) , get_rect_dim(r) );
}

recti_t get_recti_centred_coord(recti_t r)		// get a centre coord and width/height from a recti
{
	return recti( get_recti_centre(r) , get_recti_dim(r) );
}

rect_t make_rect_centred(const xy_t c, const xy_t wh)	// make rect from a centre coord and width/height
{
	return rect(sub_xy(c, mul_xy(set_xy(0.5), wh)), mad_xy(set_xy(0.5), wh, c));
}

rect_t make_rect_off(const xy_t pos, const xy_t dim, const xy_t off)
{
	return rect(sub_xy(pos, mul_xy(off, dim)), mad_xy(sub_xy(set_xy(1.), off), dim, pos));
}

recti_t make_recti_off(const xyi_t pos, const xyi_t dim, const xyi_t off)
{
	return recti(sub_xyi(pos, mul_xyi(off, dim)), mad_xyi(sub_xyi(set_xyi(1), off), dim, pos));
}

void rect_to_pos_dim(rect_t r, xy_t *pos, xy_t *dim, xy_t off)
{
	*dim = sub_xy(r.p1, r.p0);
	*pos = mad_xy(off, *dim, r.p0);
}

rect_t rect_size_mul(rect_t r, xy_t scale)
{
	r = get_rect_centred_coord(r);
	r.p1 = mul_xy(r.p1, scale);
	return make_rect_centred(r.p0, r.p1);
}

rect_t rect_add_margin(rect_t r, xy_t margin)
{
	r = get_rect_centred_coord(r);
	r.p1 = mad_xy(set_xy(2.), margin, r.p1);
	return make_rect_centred(r.p0, r.p1);
}

recti_t recti_add_margin(recti_t r, xyi_t margin)
{
	r = sort_recti(r);
	r.p0 = sub_xyi(r.p0, margin);
	r.p1 = add_xyi(r.p1, margin);

	return r;
}

rect_t rect_add_margin_offset(rect_t r, xy_t margin, xy_t offset)
{
	xy_t m0, m1;

	margin = mul_xy(margin, set_xy(2.));
	m0 = mul_xy(offset, margin);
	m1 = mul_xy(sub_xy(XY1, offset), margin);

	r = sort_rect(r);
	r.p0 = sub_xy(r.p0, m0);
	r.p1 = add_xy(r.p1, m1);

	return r;
}

rect_t rect_move(rect_t r, xy_t v)
{
	r.p0 = add_xy(r.p0, v);
	r.p1 = add_xy(r.p1, v);

	return r;
}

rect_t rect_neg_y(rect_t r)
{
	return sort_rect(rect( neg_y(r.p0) , neg_y(r.p1) ));
}

rect_t make_rect_ulcorner(xy_t ulc, xy_t wh)
{
	return sort_rect(rect( ulc, add_xy(ulc, neg_y(abs_xy(wh))) ));
}

rect_t make_rect_urcorner(xy_t ulc, xy_t wh)
{
	return sort_rect(rect( ulc, add_xy(ulc, neg_xy(abs_xy(wh))) ));
}

double rect_min_side(rect_t r)
{
	return min_of_xy(get_rect_dim(r));
}

double rect_max_side(rect_t r)
{
	return max_of_xy(get_rect_dim(r));
}

double rect_height_width_ratio(rect_t r)
{
	xy_t dim = get_rect_dim(r);

	return dim.y/dim.x;
}

rect_t sort_rect(rect_t r)
{
	minmax_xy(&r.p0, &r.p1);
	return r;
}

recti_t sort_recti(recti_t r)
{
	minmax_xyi(&r.p0, &r.p1);
	return r;
}

rect_t add_rect_xy(rect_t r, xy_t a)
{
	return rect(add_xy(r.p0, a), add_xy(r.p1, a));
}

int equal_rect(rect_t r1, rect_t r2)
{
	r1 = sort_rect(r1);
	r2 = sort_rect(r2);

	return equal_xy(r1.p0, r2.p0) && equal_xy(r1.p1, r2.p1);
}

int isnan_rect(rect_t r)
{
	return isnan_xy(r.p0) || isnan_xy(r.p1);
}

int is0_rect(const rect_t r)
{
	return is0_xy(r.p0) && is0_xy(r.p1);
}

xy_t pos_in_rect_by_ratio(rect_t r, xy_t ratio)
{
	return mad_xy(ratio, sub_xy(r.p1, r.p0), r.p0);
}

xy_t pos_to_rect_ratio(xy_t pos, rect_t r)
{
	return div_xy(sub_xy(pos, r.p0), sub_xy(r.p1, r.p0));
}

rect_t resize_rect_around_offset(rect_t r, xy_t dim1, xy_t offset)
{
	return make_rect_off(pos_in_rect_by_ratio(r, offset), dim1, offset);
}

rect_t rect_boolean_intersection(rect_t a, rect_t b)
{
	rect_t c;

	a = sort_rect(a);
	b = sort_rect(b);

	c.p0 = max_xy(a.p0, b.p0);
	c.p1 = min_xy(a.p1, b.p1);

	return c;
}

recti_t recti_boolean_intersection(recti_t a, recti_t b)
{
	recti_t c;

	a = sort_recti(a);
	b = sort_recti(b);

	c.p0 = max_xyi(a.p0, b.p0);
	c.p1 = min_xyi(a.p1, b.p1);

	return c;
}

// Inputs are range, a rectangle in destination coordinates, and dim, an image dimension in pixels
// scale and offset are used to turn integer coordinates within dim into real coordinates within the range rect
// like: pos = mad_xy(xyi_to_xy(ip), r_scale, r_offset);
void rect_range_and_dim_to_scale_offset(rect_t range, xyi_t dim, xy_t *r_scale, xy_t *r_offset, int range_edge_is_pix_centre)
{
	rect_t r_dim;

	if (range_edge_is_pix_centre)	// range rect = centre of edge pixels
		r_dim = rect(xy(0., dim.y-1.), xy(dim.x-1., 0.));
	else				// range rect = outer edge of edge pixels
		r_dim = rect(xy(-0.5, dim.y-0.5), xy(dim.x-0.5, -0.5));

	*r_scale = div_xy(sub_xy(range.p1, range.p0), sub_xy(r_dim.p1, r_dim.p0));
	*r_offset = sub_xy(range.p0, mul_xy(*r_scale, r_dim.p0));
}

// Inverse of the above so that: pix_pos = mad_xy(pos, r_scale, r_offset);
void rect_range_and_dim_to_scale_offset_inv(rect_t range, xyi_t dim, xy_t *r_scale, xy_t *r_offset, int range_edge_is_pix_centre)
{
	rect_range_and_dim_to_scale_offset(range, dim, r_scale, r_offset, range_edge_is_pix_centre);
	*r_scale = inv_xy(*r_scale);
	*r_offset = mul_xy(neg_xy(*r_offset), *r_scale);
}
