float u32_as_float(const uint32_t i)
{
	return *((float *) &i);
}

double u64_as_double(const uint64_t i)
{
	return *((double *) &i);
}

uint32_t float_as_u32(const float f)
{
	return *((uint32_t *) &f);
}

uint64_t double_as_u64(const double f)
{
	return *((uint64_t *) &f);
}

int float_get_exponent(const float f)
{
	uint32_t i = *((uint32_t *) &f);
	int e;

	e = (i >> 23) & 0xFF;
	e -= 127;

	return e;
}

int double_get_exponent(const double f)
{
	uint64_t i = *((uint64_t *) &f);
	int e;

	e = (i >> 52) & 0x07FF;
	e -= 1023;

	return e;
}

uint32_t float_get_mantissa(const float f)
{
	return float_as_u32(f) & 0x007FFFFF;
}

uint64_t double_get_mantissa(const double f)
{
	return double_as_u64(f) & 0x000FFFFFFFFFFFFF;
}

float get_fractional_part_signedf(float f)	// gets the fractional part of the number in the [0 , 1[ range, conserves the sign
{
	//return f - truncf(f);
	int64_t i = f * 4294967296.f;		// f can't be >= 2^31
	i &= 0xFFFFFFFF;
	f = i * 2.3283064e-10f;
	return f;
}

#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
double get_fractional_part_signed(double f)
{
	#ifdef RL_INTEL_INTR
	if (check_sse41())
	{
		__m128d md, mt;
		md = _mm_set_sd(f);
		mt = _mm_round_sd(md, md, _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC);	// SSE4.1 trunc(f)
		md = _mm_sub_sd(md, mt);
		return _mm_cvtsd_f64(md);
	}
	#endif

	return f - trunc(f);
}

float get_fractional_part_positivef(float f)
{
	return f - floorf(f);
}

#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
double get_fractional_part_positive(double f)
{
	//return f - floor(f);			// too slow if compiler doesn't use roundsd

	#ifdef RL_INTEL_INTR

	// Produces same opcodes as f - floor(f) with roundsd. Not checking for SSE4.1 because it impacts performance by a lot
	__m128d md, mt;
	md = _mm_set_sd(f);
	mt = _mm_round_sd(md, md, _MM_FROUND_TO_NEG_INF |_MM_FROUND_NO_EXC);	// SSE4.1 floor(f)
	md = _mm_sub_sd(md, mt);
	return _mm_cvtsd_f64(md);

	#endif

	int64_t i = f * 4294967296.;		// f can't be >= 2^31
	i &= 0xFFFFFFFF;
	f = i * 2.3283064365386963e-10;
	return f;
}

#ifdef RL_INTEL_INTR
#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
__m128d _mm_get_fractional_part_positive(__m128d md)
{
	__m128d mt = _mm_round_pd(md, _MM_FROUND_TO_NEG_INF |_MM_FROUND_NO_EXC);	// SSE4.1 floor(f)
	return _mm_sub_pd(md, mt);
}
#endif

xy_t get_fractional_part_positive_xy(xy_t f)
{
	#ifdef RL_INTEL_INTR

	__m128d md = _mm_load_pd((double *) &f);
	md = _mm_get_fractional_part_positive(md);
	_mm_storeu_pd((double *) &f, md);
	return f;

	#endif

	return func1_xy(f, get_fractional_part_positive);
}

double double_add_ulp(double x, int ulp)	// add an integer to the mantissa of a double
{
	uint64_t xi = *((uint64_t *) &x);
	double r;

	xi += ulp;
	r = *((double *) &xi);

	return r;
}

int64_t double_diff_ulp(double a, double b)	// gives the (signed) difference between two doubles in ulp
{
	uint64_t ai = *((uint64_t *) &a);
	uint64_t bi = *((uint64_t *) &b);

	return ai - bi;
}

double double_increment_minulp(double v0, double inc)	// guarantees a minimal incrementation if the increment is too small to increment anything
{
	double v1;

	v1 = v0 + inc;

	if (v1==v0)
		v1 = double_add_ulp(v0, sign(inc));

	return v1;
}
