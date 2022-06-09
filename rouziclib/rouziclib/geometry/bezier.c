int xy_array_to_bezier_seg_array(xy_t *pa, int p_count, bezier_seg_t **bap, size_t *ba_as)
{
	int i, b_count = p_count-1;
	double slope;
	bezier_seg_t *ba;

	if (b_count <= 0)
		return 0;

	alloc_enough(bap, b_count, ba_as, sizeof(bezier_seg_t), 1.);
	ba = *bap;

	// Copy points
	for (i=0; i < b_count; i++)
	{
		ba[i].p0 = pa[i];
		ba[i].p3 = pa[i+1];
	}

	// Handle the one segment case
	if (b_count == 1)
	{
		ba[i].p1 = mix_xy(pa[0], pa[1], set_xy(1./3.));
		ba[i].p2 = mix_xy(pa[1], pa[0], set_xy(1./3.));
		return b_count;
	}

	// Set control points except the first and last
	for (i=1; i < b_count; i++)
	{
		ba[i-1].p2.x = mix(pa[i].x, pa[i-1].x, 1./3.);
		ba[ i ].p1.x = mix(pa[i].x, pa[i+1].x, 1./3.);

		slope = (pa[i+1].y - pa[i-1].y) / (pa[i+1].x - pa[i-1].x);
		ba[i-1].p2.y = pa[i].y + slope * 1./3. * (pa[i-1].x - pa[i].x);
		ba[ i ].p1.y = pa[i].y + slope * 1./3. * (pa[i+1].x - pa[i].x);
	}

	// Make the first handle point to the second handle
	ba[0].p1 = mix_xy(ba[0].p0, ba[0].p2, set_xy(0.5));
	// and the last handle point the the penultimate handle
	i = b_count-1;
	ba[i].p2 = mix_xy(ba[i].p3, ba[i].p1, set_xy(0.5));

	return b_count;
}

void bezier_seg_array_flatten_slopes(bezier_seg_t *ba, int b_count)
{
	int i;

	for (i=0; i < b_count; i++)
	{
		ba[i].p1.y = ba[i].p0.y;
		ba[i].p2.y = ba[i].p3.y;
	}
}

double bezier_seg_x_to_t(bezier_seg_t seg, double x)
{
	double new=0.5, prev=-1., t, tc, p1x, p2x, scale;
	double min_t=0., max_t=1., min_x=0., max_x=1.;
	int count=0;

	// Normalise to p0.x=0 and p3.x=1
	scale = 1. / (seg.p3.x - seg.p0.x);
	x = (x - seg.p0.x) * scale;

	// No need to search, t = x if the handles are at thirds
	if (abs((int) double_diff_ulp(seg.p1.x, mix(seg.p0.x, seg.p3.x, 1./3.))) < 10 && 
	    abs((int) double_diff_ulp(seg.p2.x, mix(seg.p3.x, seg.p0.x, 1./3.))) < 10)
		return x;

	p1x = (seg.p1.x - seg.p0.x) * scale;
	p2x = (seg.p2.x - seg.p0.x) * scale;

	// Search for t
	while (new != prev && count < 50)
	{
		t = ((x-min_x) / (max_x-min_x)) * (max_t-min_t) + min_t;
		tc = 1. - t;
		prev = new;
		new = 3.*tc*tc*t*p1x + 3.*tc*t*t*p2x + t*t*t;
		if (new < x)
		{
			min_t = t;
			min_x = new;
		}
		if (new > x)
		{
			max_t = t;
			max_x = new;
		}

		count++;
	}

	return t;
}

int cmp_bezier_seg_by_x(const bezier_seg_t *a, const bezier_seg_t *b)	// bezier_seg_t comparison function (for qsort) sorting by x
{
	if (a->p0.x > b->p0.x) return 1;
	if (a->p0.x == b->p0.x) return 0;
	return -1;
}

double bezier_seg_array_eval_x(bezier_seg_t *ba, int b_count, double x)
{
	int i;
	double t, tc;
	bezier_seg_t v={0};

	// Find the segment that contains x
	v.p0.x = x;
	i = array_find_index_by_cmp(&v, ba, b_count, sizeof(bezier_seg_t), cmp_bezier_seg_by_x);

	if (x < ba[i].p0.x || x > ba[i].p3.x)
		return NAN;

	// Find t from x
	t = bezier_seg_x_to_t(ba[i], x);
	tc = 1. - t; 

	// Compute y
	return tc*tc*tc*ba[i].p0.y + 3.*tc*tc*t*ba[i].p1.y + 3.*tc*t*t*ba[i].p2.y + t*t*t*ba[i].p3.y;
}
