uint rand_xsm32(uint x)
{
	x ^= x >> 16;
	x *= 0x21f0aaadu;
	x ^= x >> 15;
	x *= 0x735a2d97u;
	x ^= x >> 15;
	return x;
}

float gaussian_rand_approx(uint pos)	// max error of the resulting Gaussian distribution: 9.8e-3
{
	float r = ((float) rand_xsm32(pos) - 2147483647.5f) * 4.6566125e-10f;		// r = ]-1 , 1[

	return copysign(0.88622693f * native_sqrt(- native_log(1.f - r*r)), r);		// gives a e^-x^2 distribution, [-3.54 , 3.54]
}
