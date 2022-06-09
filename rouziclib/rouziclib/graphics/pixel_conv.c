// Convert to frgb
frgb_t lrgb_to_frgb(lrgb_t l)
{
	frgb_t f;
	const float ratio = 1.f/ONEF;

	f.r = (float) l.r * ratio;
	f.g = (float) l.g * ratio;
	f.b = (float) l.b * ratio;
	f.a = (float) l.a * ratio;

	return f;
}

frgb_t srgb_to_frgb(srgb_t s)
{
	static float *lut=NULL;
	frgb_t f;

	if (lut==NULL)
		lut = get_lut_slrgb().flut;

	f.r = lut[s.r];
	f.g = lut[s.g];
	f.b = lut[s.b];
	f.a = lut[s.a];

	return f;
}

frgb_t sqrgb_to_frgb(sqrgb_t s)
{
	frgb_t f;
	const float mul_rb = 1.f / (1023.f*1023.f);
	const float mul_g = 1.f / (4092.f*4092.f);

	f.r = (float) (s.r*s.r) * mul_rb;
	f.g = (float) (s.g*s.g) * mul_g;
	f.b = (float) (s.b*s.b) * mul_rb;
	f.a = 1.f;

	return f;
}

#ifdef RL_INTEL_INTR
__m128 _mm_lrgb_to_ps(lrgb_t l)
{
	__m128 f;

	// Load and convert to floats
	f = _mm_cvtepi32_ps(_mm_set_epi32(l.a, l.b, l.g, l.r));

	// Multiply
	f = _mm_mul_ps(f, _mm_set_ps1(1.f/ONEF));

	return f;
}

__m128 _mm_srgb_to_ps(srgb_t s)
{
	static float *lut=NULL;
	__m128 f;

	if (lut==NULL)
		lut = get_lut_slrgb().flut;

	// Lookups
	f = _mm_set_ps(lut[s.a], lut[s.b], lut[s.g], lut[s.r]);

	return f;
}

__m128 _mm_sqrgb_to_ps(sqrgb_t s)
{
	__m128 f, m, sv;
	const float mul_rb = 1.f / (1023.f*1023.f);
	const float mul_g = 1.f / (4092.f*4092.f);

	m = _mm_set_ps(1.f, mul_rb, mul_g, mul_rb);	// multipliers

	// Load and convert to floats
	sv = _mm_cvtepi32_ps(_mm_set_epi32(1, s.b, s.g, s.r));

	// Multiply by itself and then by the multipliers
	sv = _mm_mul_ps(sv, sv);
	f = _mm_mul_ps(sv, m);

	return f;
}

// Get pixel at index to frgb
__m128 _mm_get_raster_pixel_frgb_to_ps(raster_t *r, const size_t index)
{
	__m128 v = _mm_loadu_ps((float *) &r->f[index]);
	return v;
}

__m128 _mm_get_raster_pixel_lrgb_to_ps(raster_t *r, const size_t index)
{
	__m128 v = _mm_lrgb_to_ps(r->l[index]);
	return v;
}

__m128 _mm_get_raster_pixel_srgb_to_ps(raster_t *r, const size_t index)
{
	__m128 v = _mm_srgb_to_ps(r->srgb[index]);
	return v;
}

__m128 _mm_get_raster_pixel_sqrgb_to_ps(raster_t *r, const size_t index)
{
	__m128 v = _mm_sqrgb_to_ps(r->sq[index]);
	return v;
}
#endif

// Convert from frgb
lrgb_t frgb_to_lrgb(frgb_t cf)
{
	lrgb_t c;

	c.r = MINN(1., cf.r) * ONEF + 0.5;
	c.g = MINN(1., cf.g) * ONEF + 0.5;
	c.b = MINN(1., cf.b) * ONEF + 0.5;
	c.a = MINN(1., cf.a) * ONEF + 0.5;

	return c;
}

srgb_t frgb_to_srgb(frgb_t cf)
{
	srgb_t c;

	c.r = fast_lsrgbf(MINN(1., cf.r)) * 255.f + 0.5;
	c.g = fast_lsrgbf(MINN(1., cf.g)) * 255.f + 0.5;
	c.b = fast_lsrgbf(MINN(1., cf.b)) * 255.f + 0.5;
	c.a = fast_lsrgbf(MINN(1., cf.a)) * 255.f + 0.5;

	return c;
}

sqrgb_t frgb_to_sqrgb(frgb_t f)
{
	sqrgb_t s;

	s.r = sqrtf(rangelimitf(f.r, 0.f, 1.f)) * 1023. + 0.5;
	s.g = sqrtf(rangelimitf(f.g, 0.f, 1.f)) * 4092. + 0.5;
	s.b = sqrtf(rangelimitf(f.b, 0.f, 1.f)) * 1023. + 0.5;

	return s;
}

#ifdef RL_INTEL_INTR
void _mm_set_raster_pixel_ps_to_frgb(raster_t *r, const size_t index, __m128 f)
{
	_mm_storeu_ps((float *) &r->f[index], f);
}

#ifdef __GNUC__
__attribute__((__target__("ssse3")))
#endif
void _mm_set_raster_pixel_ps_to_lrgb(raster_t *r, const size_t index, __m128 f)
{
	__m128i lv;
	uint32_t la[4];
	lrgb_t l;

	// Clamp and multiply
	f = _mm_clamp_ps(f);
	f = _mm_mul_ps(f, _mm_set_ps1(ONEF));

	// Convert from float to lrgb
	lv = _mm_cvtps_epi32(f);	// floats to 32-bit integers
	lv = _mm_cvtepu32_epi16(lv);
	_mm_storeu_si64(&r->l[index], lv);
}

#ifdef __GNUC__
__attribute__((__target__("ssse3")))
#endif
void _mm_set_raster_pixel_ps_to_srgb(raster_t *r, const size_t index, __m128 f)
{
	__m128i sv;
	uint32_t sa[4];
	srgb_t s;

	f = _mm_clamp_ps(f);			// clamp
	f = _mm_frgb_to_srgb(f);		// convert to sRGB [0 , 1]
	f = _mm_mul_ps(f, _mm_set_ps1(255.f));	// => [0 , 255]

	// Convert from float to srgb
	sv = _mm_cvtps_epi32(f);	// floats to 32-bit integers
	sv = _mm_cvtepu32_epi8(sv);
	_mm_storeu_si32(&r->srgb[index], sv);
}

void _mm_set_raster_pixel_ps_to_sqrgb(raster_t *r, const size_t index, __m128 f)
{
	__m128i sv;
	uint32_t sa[4];
	sqrgb_t s;

	f = _mm_clamp_ps(f);			// clamp
	f = _mm_sqrt_ps(f);			// square root
	f = _mm_mul_ps(f, _mm_set_ps(1.f, 1023.f, 4092.f, 1023.f));

	// Convert from float to sqrgb
	sv = _mm_cvtps_epi32(f);
	_mm_store_si128((__m128i *) sa, sv);	// put integers in array
	s.r = sa[0];			// store 32-bit integers in packed sqrgb format
	s.g = sa[1];
	s.b = sa[2];

	r->sq[index] = s;
}
#endif

void image_float_channel_conversion(float *in, int in_chan, float *out, int out_chan)
{
	int ic;

	if (in_chan >= 3 && out_chan==1)	// RGB to gray
	{
		out[0] = (in[0] + in[1] + in[2]) * 0.33333333f;
		return ;
	}

	if (out_chan >= 4)
		out[3] = 1.f;			// set default alpha channel

	memset(out, 0, MINN(3, out_chan) * sizeof(float));
	memcpy(out, in, MINN(in_chan, out_chan) * sizeof(float));

	// Copy first channel to other channels if needed
	if (in_chan < 3 && out_chan >= 3)
		for (ic=in_chan; ic < MINN(3, out_chan); ic++)
			out[ic] = out[0];
}
