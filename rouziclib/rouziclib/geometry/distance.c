// 2D
double hypot_d_xy2(xy_t d)
{
	return d.x*d.x + d.y*d.y;
}

double hypot_d_xy(xy_t d)
{
	return sqrt(hypot_d_xy2(d));
}

double hypot_xy2(xy_t a, xy_t b)
{
	return hypot_d_xy2( sub_xy(a, b) );
}

double hypot_xy(xy_t a, xy_t b)
{
	return sqrt(hypot_xy2(a, b));
}

// 3D
double hypot_d_xyz2(xyz_t d)
{
	return d.x*d.x + d.y*d.y + d.z*d.z;
}

double hypot_d_xyz(xyz_t d)
{
	return sqrt(hypot_d_xyz2(d));
}

double hypot_xyz2(xyz_t a, xyz_t b)
{
	return hypot_d_xyz2( sub_xyz(a, b) );
}

double hypot_xyz(xyz_t a, xyz_t b)
{
	return sqrt(hypot_xyz2(a, b));
}

xy_t set_new_distance_from_point(xy_t p0, xy_t pc, double dist_mul)
{
	return mad_xy(sub_xy(p0, pc), set_xy(dist_mul), pc);
}
