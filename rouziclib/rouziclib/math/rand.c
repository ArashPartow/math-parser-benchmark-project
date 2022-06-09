uint32_t rand_xsm32_state = 1;

// Xorshift-multiply hashing PRNG based on github.com/skeeto/hash-prospector, github.com/skeeto/hash-prospector/issues/19#issuecomment-1120105785
uint32_t rand_xsm32(uint32_t x)		// x can be seen as a sequence position
{
	//x += 0x3243f6a8u;	// suggested by nullprogram.com/blog/2021/09/14/, avoids 0 -> 0
	x ^= x >> 16;
	x *= 0x21f0aaadu;
	x ^= x >> 15;
	x *= 0x735a2d97u;
	x ^= x >> 15;
	return x;
}

uint32_t rand32()
{
	return rand_xsm32(rand_xsm32_state++);
	//return (rand()&0x7FE0)<<17 | (rand()&0x7FF0)<<7 | (rand()&0x7FF0)>>4;
}

double randrange(double low, double high)
{
	double range;

	range = high-low;

	if (range <= 0.)
		return 0.;

	return range * (double)rand32() / 4294967295. + low;
}

double gaussian_rand()
{
	double v1, v2, s;

	do
	{
		v1 = randrange(-1., 1.);
		v2 = randrange(-1., 1.);
		s = v1*v1 + v2*v2;
	}
	while (s >= 1.);	// clips points inside the unit square but outside the unit circle

	return sqrt(-2. * fastlog(s) / s) * v1;
	//y = sqrt(-2. * fastlog(s) / s) * v2;
}

xy_t gaussian_rand_xy()
{
	double v1, v2, s;

	do
	{
		v1 = randrange(-1., 1.);
		v2 = randrange(-1., 1.);
		s = v1*v1 + v2*v2;
	}
	while (s >= 1.);	// clips points inside the unit square but outside the unit circle

	return xy( sqrt(-2. * fastlog(s) / s) * v1 , sqrt(-2. * fastlog(s) / s) * v2 );
}

double gaussian_rand_approx()							// max error: 0.00865 at ±0.772135
{
	double r = ((double) rand32() - 2147483647.5) * 4.656612874e-10;	// r = ]-1 , 1[
	return copysign(0.8862269254 * sqrt(- fastlog(1. - r*r)), r);		// gives a e^-x^2 distribution, [-4.286 , 4.286]
}

double gaussian_rand_approx_pos(uint32_t pos)
{
	double r = ((double) rand_xsm32(pos) - 2147483647.5) * 4.656612874e-10;
	return copysign(0.8862269254 * sqrt(- fastlog(1. - r*r)), r);		// 0.8862.. is sqrt(pi)/2.
}

xy_t gaussian_rand_approx_xy()
{
	return xy( gaussian_rand_approx(), gaussian_rand_approx() );
}
