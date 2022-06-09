double dct_type_II_8x8_coef(xyi_t spatialfreq, xyi_t pos)
{
	double u, v, x, y, coef;

	u = spatialfreq.x;
	v = spatialfreq.y;
	x = pos.x;
	y = pos.y;

	coef = cos( (2.*x + 1.) * u * pi / 16. );
	coef *= cos( (2.*y + 1.) * v * pi / 16. );

	return coef;
}

double dct_type_II_8x8_coef_lut(xyi_t spatialfreq, xyi_t pos)
{
	int i, ib;
	static int init=1;
	static double lut[64];

	if (init)
	{
		init = 0;

		for (ib=0; ib<8; ib++)
			for (i=0; i<8; i++)
				lut[ib*8 + i] = cos( (2.*(double) i + 1.) * (double) ib * pi / 16. );
	}

	return lut[spatialfreq.x * 8 + pos.x] * lut[spatialfreq.y * 8 + pos.y];
}

double dct_type_III_8x8_coef(xyi_t spatialfreq, xyi_t pos)
{
	const double alpha0 = sqrt(0.5);
	double u, v, x, y, coef;

	coef = dct_type_II_8x8_coef_lut(spatialfreq, pos);

	if (spatialfreq.x==0)
		coef *= alpha0;
	if (spatialfreq.y==0)
		coef *= alpha0;

	return coef;
}

double dct_type_II_cell(double *b0, xyi_t ip)
{
	xyi_t ifr;
	const double alpha0 = sqrt(0.5);
	double v=0.;

	for (ifr.y=0; ifr.y < 8; ifr.y++)
		for (ifr.x=0; ifr.x < 8; ifr.x++)
			v += (b0[ifr.y * 8 + ifr.x] - 128.) * dct_type_II_8x8_coef_lut(ip, ifr);

	v *= 0.25;

	if (ip.x==0)
		v *= alpha0;
	if (ip.y==0)
		v *= alpha0;

	return v;
}

double dct_type_III_cell(double *freq_block, xyi_t ip)
{
	xyi_t ifr;
	double v = 128.*4.;

	for (ifr.y=0; ifr.y < 8; ifr.y++)
		for (ifr.x=0; ifr.x < 8; ifr.x++)
			v += freq_block[ifr.y * 8 + ifr.x] * dct_type_III_8x8_coef(ifr, ip);

	v *= 0.25;

	return v;
}

void dct_type_II_8x8(double *b0, double *b1)
{
	xyi_t ip;

	for (ip.y=0; ip.y < 8; ip.y++)
		for (ip.x=0; ip.x < 8; ip.x++)
			b1[ip.y * 8 + ip.x] = dct_type_II_cell(b0, ip);
}

void dct_type_III_8x8(double *freq_block, double *space_block)
{
	xyi_t ip, ifr;

	for (ip.y=0; ip.y < 8; ip.y++)
		for (ip.x=0; ip.x < 8; ip.x++)
			space_block[ip.y * 8 + ip.x] = dct_type_III_cell(freq_block, ip);
}
