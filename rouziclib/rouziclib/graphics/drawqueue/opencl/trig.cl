float acos_tr_fast_xpositive(float x)	// output is in turns in the range [0 , 0.25]
{
	float r;

	// 8 FR + 2 FR once
	r = (0.0081f*x - 0.0326f)*x + 0.24993433f;	// error 1/17942 turns (0.02 deg)
	r *= native_sqrt(1.f - x);

	return r;
}

float acos_tr_fast(float x)	// output is in turns in the range [0 , 0.5]
{
	float r;

	// 10 FR + 2 FR once
	r = acos_tr_fast_xpositive(fabs(x));

	return x < 0.f ? 0.5f-r : r;
}

float asin_tr_fast(float x)
{
	return 0.25f - acos_tr_fast(x);
}
