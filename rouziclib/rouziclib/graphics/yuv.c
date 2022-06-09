// For all the following functions frbg_t is gamma compressed, not linear
frgb_t yuv_to_frgb(xyz_t yuv)
{
	double y, u, v, r, g, b;
	frgb_t pv;

	y = yuv.x - 16.;
	y *= 255. / 219.;
	u = yuv.y - 128.;
	v = yuv.z - 128.;

	r = y + 1.596 * v;
        g = y - 0.813 * v - 0.391 * u;
        b = y + 2.018 * u;

	pv.r = s8lrgb(r);
	pv.g = s8lrgb(g);
	pv.b = s8lrgb(b);
	pv.a = 1.;

	return pv;
}

double frgb_to_yuv_y(frgb_t pv)
{
	return 0.2569*pv.r + 0.5044*pv.g + 0.0979*pv.b + 16.;
}

double frgb_to_yuv_u(frgb_t pv)
{
	return -0.1483*pv.r - 0.2911*pv.g + 0.4394*pv.b + 128.;
}

double frgb_to_yuv_v(frgb_t pv)
{
	return 0.4394*pv.r - 0.3679*pv.g - 0.0715*pv.b + 128.;
}

xyz_t frgb_to_yuv(frgb_t pv)
{
	return xyz( frgb_to_yuv_y(pv), frgb_to_yuv_u(pv), frgb_to_yuv_v(pv) );
}

// the frgb_t input here is linear
void frgb_2x2_to_yuv420(frgb_t *l0, frgb_t *l1, float *y, float *u, float *v)
{
	frgb_t av;

	av = mul_scalar_frgb(add_frgb(add_frgb(l0[0], l0[1]), add_frgb(l1[0], l1[1])), 0.25f);
	av = mul_scalar_frgb(lsrgb_fast_frgb(av), 255.f);

	y[0] = frgb_to_yuv_y(mul_scalar_frgb(lsrgb_fast_frgb(l0[0]), 255.));
	y[1] = frgb_to_yuv_y(mul_scalar_frgb(lsrgb_fast_frgb(l0[1]), 255.));
	y[2] = frgb_to_yuv_y(mul_scalar_frgb(lsrgb_fast_frgb(l1[0]), 255.));
	y[3] = frgb_to_yuv_y(mul_scalar_frgb(lsrgb_fast_frgb(l1[1]), 255.));
	*u = frgb_to_yuv_u(av);
	*v = frgb_to_yuv_v(av);
}
