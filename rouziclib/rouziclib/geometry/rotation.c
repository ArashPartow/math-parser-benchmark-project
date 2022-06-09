xy_t rotate_xy2_pre(xy_t p, double costh, double sinth)
{
	xy_t r;

	r.x = p.x * costh - p.y * sinth;
	r.y = p.x * sinth + p.y * costh;

	return r;
}

xy_t rotate_xy2(xy_t p, double th)	// 2D rotation
{
	return rotate_xy2_pre(p, cos(th), sin(th));
}

xy_t rotate_xy2_pre_around_point(xy_t p, xy_t c, double costh, double sinth)
{
	return add_xy(c, rotate_xy2_pre(sub_xy(p, c), costh, sinth));
}

xyz_t rotate_xy(xyz_t p, double th)
{
	return rotate_z_pre(p, cos(th), sin(th));
}

xyz_t rotate_zxy(xyz_t p, xyz_t th)
{
	return rotate_zxy_pre(p, cos_xyz(th), sin_xyz(th));
}

xyz_t rotate_x_pre(xyz_t p, double costh, double sinth)		// Rot X
{
	xyz_t r;

	r.x = p.x;
	r.y = p.y*costh - p.z*sinth;
	r.z = p.y*sinth + p.z*costh;

	return r;
}

xyz_t rotate_y_pre(xyz_t p, double costh, double sinth)		// Rot Y
{
	xyz_t r;

	r.x = p.x*costh + p.z*sinth;
	r.y = p.y;
	r.z = -p.x*sinth + p.z*costh;

	return r;
}

xyz_t rotate_z_pre(xyz_t p, double costh, double sinth)		// Rot Z
{
	xyz_t r;

	r.x = p.x*costh - p.y*sinth;
	r.y = p.x*sinth + p.y*costh;
	r.z = p.z;

	return r;
}

xyz_t rotate_zxy_pre(xyz_t p, xyz_t costh, xyz_t sinth)
{
	p = rotate_z_pre(p, costh.z, sinth.z);		// Rot Z
	p = rotate_x_pre(p, costh.x, sinth.x);		// Rot X
	p = rotate_y_pre(p, costh.y, sinth.y);		// Rot Y

	return p;
}

xyz_t rotate_pt_matrix(xyz_t p, matrix_t m)
{
	xyz_t r;

	r.x = p.x*m.x.x + p.y*m.x.y + p.z*m.x.z;
	r.y = p.x*m.y.x + p.y*m.y.y + p.z*m.y.z;
	r.z = p.x*m.z.x + p.y*m.z.y + p.z*m.z.z;

	return r;
}

matrix_t rotation_matrix_zxy(xyz_t th)	// makes a 3x3 rotation matrix of 3D Euler angles
{
	xyz_t costh, sinth;
	matrix_t m = {	{1., 0., 0.},
			{0., 1., 0.},
			{0., 0., 1.}};

	costh = cos_xyz(th);
	sinth = sin_xyz(th);

	m = matrices_mul(m, matrix_xyz(	xyz(costh.y,	0.,  sinth.y), 	// rot Y matrix
					xyz(	0.,  	1.,	0.), 
					xyz(-sinth.y,	0.,  costh.y) ));

	m = matrices_mul(m, matrix_xyz(	xyz(	1.,	0.,	0.), 	// rot X matrix
					xyz(	0.,  costh.x, -sinth.x), 
					xyz(	0.,  sinth.x,  costh.x) ));

	m = matrices_mul(m, matrix_xyz(	xyz(costh.z, -sinth.z,	0.), 	// rot Z matrix
					xyz(sinth.z,  costh.z,	0.), 
					xyz(	0.,	0.,	1.) ));

	return m;
}

xyz_t cross_product_xyz(xyz_t a, xyz_t b)
{
	return xyz(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
