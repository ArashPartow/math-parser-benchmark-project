// Tiling functions
double fit_n_squares_in_area(xy_t area_dim, int count, xyi_t *grid_count_ptr)
{
	double n, size, max_size=0.;
	xy_t iv, grid_count, g, d1;

	if (count==1)
	{
		*grid_count_ptr = xyi(1, 1);
		return min_of_xy(area_dim);
	}

	n = (double) count;
	size = sqrt(area_dim.x*area_dim.y / n);
	grid_count = floor_xy(d1=div_xy(area_dim, set_xy(size)));	// starting point with minimum size

	for (iv.x=0.; iv.x <= grid_count.x; iv.x+=1.)
		for (iv.y=0.; iv.y <= grid_count.y; iv.y+=1.)
		{
			g = add_xy(grid_count, iv);
			if (g.x*g.y >= n)
			{
				size = min_of_xy(div_xy(area_dim, g));
				if (size > max_size)
				{
					max_size = size;
					if (grid_count_ptr)
						*grid_count_ptr = xy_to_xyi(g);
				}
			}
		}

	return max_size;
}

double fit_n_squares_in_area_fill_x(xy_t area_dim, int count, xyi_t *grid_count_ptr)
{
	double n, size, max_size=0.;
	xy_t iv, grid_count, g, d1;

	if (count==1 || min_of_xy(area_dim)==0.)
	{
		*grid_count_ptr = xyi(1, 1);
		return min_of_xy(area_dim);
	}

	// FIXME the grid_count can be poorly chosen which returns a max_size of 0
	n = (double) count;
	size = sqrt(area_dim.x*area_dim.y / n);
	grid_count = floor_xy(d1=div_xy(area_dim, set_xy(size)));	// starting point with minimum size
	grid_count = max_xy(grid_count, xy(1., 1.));

	for (iv.x=0.; iv.x <= grid_count.x; iv.x+=1.)
		for (iv.y=0.; iv.y <= grid_count.y; iv.y+=1.)
		{
			g = add_xy(grid_count, iv);
			if (g.x*g.y >= n)
			{
				size = min_of_xy(div_xy(area_dim, g));

				if (size * g.x >= double_add_ulp(area_dim.x, -40) || max_size==0.)
				if (size > max_size)
				{
					max_size = size;
					if (grid_count_ptr)
						*grid_count_ptr = xy_to_xyi(g);
				}
			}
		}

	return max_size;
}

xy_t fit_n_rects_in_area(xy_t area_dim, xy_t rect_dim, int count, xyi_t *grid_count_ptr)
{
	double unit_size_sq = fit_n_squares_in_area(div_xy(area_dim, rect_dim), count, grid_count_ptr);

	return mul_xy(set_xy(unit_size_sq), rect_dim);
}

xy_t fit_n_rects_in_area_fill_x(xy_t area_dim, xy_t rect_dim, int count, xyi_t *grid_count_ptr)
{
	double unit_size_sq = fit_n_squares_in_area_fill_x(div_xy(area_dim, rect_dim), count, grid_count_ptr);

	return mul_xy(set_xy(unit_size_sq), rect_dim);
}

xyi_t get_dim_of_tile(xyi_t fulldim, xyi_t tilesize, xyi_t index)
{
	xyi_t rdim;

	rdim = sub_xyi(fulldim, mul_xyi(tilesize, index));
	rdim = min_xyi(tilesize, rdim);

	return rdim;
}

// Hilbert curve functions
// n means the space is n by n, n is a power of 2

int hilbert_curve_coord_to_index(const int n, xyi_t p)
{
	int s, index=0;
	xyi_t r;

	for (s = n>>1; s > 0; s >>= 1)
	{
		r.x = (p.x & s) > 0;
		r.y = (p.y & s) > 0;
		index += s*s * ((3 * r.x) ^ r.y);
		hilbert_curve_rotate(s, &p, r);
	}

	return index;
}

xyi_t hilbert_curve_index_to_coord(const int n, int index)
{
	int s;
	xyi_t r, p={0};

	for (s = 1; s < n; s <<= 1)
	{
		r.x = 1 & (index >> 1);
		r.y = 1 & (index ^ r.x);
		hilbert_curve_rotate(s, &p, r);
		p.x += s * r.x;
		p.y += s * r.y;
		index >>= 2;
	}

	return p;
}

void hilbert_curve_rotate(const int n, xyi_t *p, xyi_t r)	// rotate/flip a quadrant appropriately
{
	if (r.y == 0)
	{
		if (r.x == 1)
		{
			p->x = n-1 - p->x;
			p->y = n-1 - p->y;
		}

		swap_i32(&p->x, &p->y);
	}
}

// Fitting rectangles into rectangles

void area_to_area_transform(rect_t a, rect_t b, xy_t *tmul, xy_t *tadd, const int keep_aspect_ratio)		// find how to multiply and add in order to fit area B into area A
{
	xy_t ad, bd;

	a = sort_rect(a);
	b = sort_rect(b);

	ad = get_rect_dim(a);
	bd = get_rect_dim(b);

	*tmul = div_xy_0(ad, bd);
	if (keep_aspect_ratio)
		*tmul = set_xy(min_of_xy(*tmul));

	*tadd = sub_xy(get_rect_centre(a), mul_xy(get_rect_centre(b), *tmul));
}

xy_t fit_unscaled_rect(rect_t a, rect_t f, double *sm)	// find the offset-scale so that full_frame 'f' can fit inside the container area 'a'
{
	xy_t tmul, tadd;

	area_to_area_transform(a, f, &tmul, &tadd, 1);
	if (sm)
		*sm = min_of_xy(tmul);

	return tadd;
}

xy_t fit_into_area(rect_t area, rect_t box, double margin, double *sm)
{
	return fit_unscaled_rect(area, rect_add_margin(box, set_xy(margin)), sm);
}

rect_t fit_rect_in_area(xy_t r_dim0, rect_t area, xy_t off)
{
	double scale;
	xy_t area_dim, r_dim1, dim_diff;

	area = sort_rect(area);
	area_dim = get_rect_dim(area);
	scale = min_of_xy(div_xy(area_dim, r_dim0));
	r_dim1 = mul_xy(r_dim0, set_xy(scale));
	dim_diff = sub_xy(area_dim, r_dim1);
	return make_rect_off(mad_xy(dim_diff, off, area.p0), r_dim1, XY0);
}

rect_t fit_rect_containing_area(xy_t r_dim0, rect_t area, xy_t off)	// instead of rect fitting in area, area fits inside rect
{
	double scale;
	xy_t area_dim, r_dim1, dim_diff;

	area = sort_rect(area);
	area_dim = get_rect_dim(area);
	scale = max_of_xy(div_xy(area_dim, r_dim0));
	r_dim1 = mul_xy(r_dim0, set_xy(scale));
	dim_diff = sub_xy(area_dim, r_dim1);
	return make_rect_off(mad_xy(dim_diff, off, area.p0), r_dim1, XY0);
}

rect_t get_subdiv_area(rect_t area, xy_t ratio, xy_t offset)
{
	xy_t area_dim, subdiv_dim, pos;

	area_dim = get_rect_dim(area);
	subdiv_dim = mul_xy(area_dim, ratio);

	pos = mad_xy(offset, sub_xy(area_dim, subdiv_dim), sort_rect(area).p0);
	return make_rect_off(pos, subdiv_dim, XY0);
}

xy_t make_dim_from_area_and_aspect_ratio(double area, xy_t aspect_dim)
{
	xy_t dim;

	dim.y = sqrt(area * aspect_dim.y / aspect_dim.x);
	dim.x = area / dim.y;

	return dim;
}
