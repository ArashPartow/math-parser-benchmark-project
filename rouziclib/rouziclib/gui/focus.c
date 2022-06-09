focus_t focus_rlg = { 0.8, 0.8, 0., 6., 1., 0.};

double drawing_focus_adjust(focus_t f, double min_thick, double *lum, int is_point)
{
	double thick, odi, fdi, bokeh_size;

	if (f.obj_dist==0.)
		return min_thick;

	odi = 1. / f.obj_dist;	// object distance inverse
	fdi = 1. / f.dist;	// focus distance inverse
	bokeh_size = (odi - fdi) * f.aperture;

	thick = hypot(bokeh_size, min_thick);
	if (lum)
	{
		*lum *= min_thick / thick;
		if (is_point)
			*lum *= min_thick / thick;
	}

	return thick;
}
