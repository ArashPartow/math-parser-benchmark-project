float gaussian(float x)
{
	return native_exp(-x*x);	// ~6 FR
}

float erf_fast(float x)
{
	float y, xa = fabs(x);

	// erf(x) ~= 1 - exp(<polynomial>) for x >= 0, max error 1/4249
	// 2 mad, 1 mul, 1 +-, 1 copysign, 1 exp = ~9 FR
	y = ((-0.06388f*xa - 0.66186f)*xa - 1.123613f)*xa;
	y = 1.f - native_exp(y);
	y = copysign(y, x);

	return y;
}
