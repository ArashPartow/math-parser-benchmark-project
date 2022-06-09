#ifndef RL_EXCL_APPROX
#ifdef RL_INTEL_INTR

__m128i _mm_index_from_vom_ps(__m128 x, const float offset, const uint32_t mask)	// make index from value+offset&mask
{
	__m128i r;
	r = _mm_castps_si128(_mm_and_ps(_mm_add_ps(x, _mm_set_ps1(offset)), _mm_castsi128_ps(_mm_set1_epi32(mask))));
	return r;
}

__m128 _mm_eval_poly_d1_lut_ps(__m128 x, const float *lut, __m128i index)
{
	__m128 r, c0, c1;

	// Look up coefs in LUT
	c0 = _mm_i32sgather_ps(lut, index);			// lookup c0
	index = _mm_add_epi32(index, _mm_set1_epi32(1));	// index+1
	c1 = _mm_i32sgather_ps(lut, index);			// lookup c1

	// Polynomial
	r = _mm_mul_ps(c1, x);		// faster than _mm_fmadd_ps because the mulps can be done earlier
	r = _mm_add_ps(r, c0);
	return r;
}

__m128 _mm_eval_poly_d2_lut_ps(__m128 x, const float *lut, __m128i index)
{
	__m128 r, c0, c1, c2;

	// Look up coefs in LUT
	c0 = _mm_i32sgather_ps(lut, index);			// lookup c0
	index = _mm_add_epi32(index, _mm_set1_epi32(1));	// index+1
	c1 = _mm_i32sgather_ps(lut, index);			// lookup c1
	index = _mm_add_epi32(index, _mm_set1_epi32(1));	// index+1
	c2 = _mm_i32sgather_ps(lut, index);			// lookup c2

	// Polynomial
	r = _mm_mul_ps(c2, x);
	r = _mm_add_ps(r, c1);
	r = _mm_mul_ps(r, x);
	r = _mm_add_ps(r, c0);
	return r;
}

__m128d _mm_eval_poly_d3_lut_pd(__m128d x, const double *lut, __m128i index)
{
	__m128d r, c0, c1, c2, c3;

	// Look up coefs in LUT
	c0 = _mm_i64sgather_pd(lut, index);			// lookup c0
	index = _mm_add_epi64(index, _mm_set1_epi64x(1));	// index+1
	c1 = _mm_i64sgather_pd(lut, index);			// lookup c1
	index = _mm_add_epi64(index, _mm_set1_epi64x(1));	// index+1
	c2 = _mm_i64sgather_pd(lut, index);			// lookup c2
	index = _mm_add_epi64(index, _mm_set1_epi64x(1));	// index+1
	c3 = _mm_i64sgather_pd(lut, index);			// lookup c3

	// Polynomial
	r = _mm_mul_pd(c3, x);
	r = _mm_add_pd(r, c2);
	r = _mm_mul_pd(r, x);
	r = _mm_add_pd(r, c1);
	r = _mm_mul_pd(r, x);
	r = _mm_add_pd(r, c0);
	return r;
}

__m128 _mm_gaussian_d1_ps(__m128 x) 	// runs in 8 cycles
{
	#include "tables/fastgauss_d1.h"	// contains the LUT, offset and limit
	__m128i index;

	x = _mm_abs_ps(x);						// x = |x|
	x = _mm_min_ps(x, _mm_set_ps1(limit));				// x > 4 becomes 4

	index = _mm_index_from_vom_ps(x, offset, 0x007FFFFE);		// FIXME rounding probably selects for wrong indices
	return _mm_eval_poly_d1_lut_ps(x, fastgauss_lut, index);
}

__m128 _mm_erfr_d1_ps(__m128 x)
{
	#include "tables/fasterfr_d1.h"	// contains the LUT, offset and limit
	__m128i index;

	x = _mm_max_ps(x, _mm_set_ps1(-limit));				// x < -4 becomes -4
	x = _mm_min_ps(x, _mm_set_ps1(limit));				// x > 4 becomes 4

	index = _mm_index_from_vom_ps(x, offset, 0x007FFFFE);
	return _mm_eval_poly_d1_lut_ps(x, fasterfr_lut, index);
}

#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
__m128 _mm_frgb_to_srgb(__m128 x)	// output is [0.f , 1.f]
{
	static const float lut[] = 
	#include "tables/fastlsrgb.h"		// 34 x 3 floats, 408 bytes, contains order (2), ish
	__m128 r;
	__m128i index, offset = _mm_set1_epi32(0x3B4D2E1C);	// 0.0031308f

	// Clamp x
	x = _mm_clamp_ps(x);

	// Make index
	index = _mm_sub_epi32(_mm_castps_si128(_mm_add_ps(x, _mm_set_ps1(0.0031308f))), offset);
	index = _mm_mullo_epi32(_mm_srli_epi32(index, ish), _mm_set1_epi32(3));

	r = _mm_eval_poly_d2_lut_ps(x, lut, index);
	return r;
}

__m128d _mm_fastcos_tr_d3(__m128d x)	// max error: 1.88958e-009
{
	static const double lut[] = 
	#include "tables/fastcos_d3.h"		// 3 kB
	const int ish = 32+17-lutsp-2;		// the -2 is for the *4 index multiplication
	__m128i lutind;

	// x = ]-inf , +inf[ --> x = [0 , 1]
	x = _mm_get_fractional_part_positive(x);

	// Add offset and mask mantissa
	lutind = _mm_castpd_si128(_mm_and_pd(_mm_add_pd(x, _mm_set1_pd(2.)), _mm_castsi128_pd(_mm_set1_epi64x(0x000FF00000000000ULL))));

	// Shift mantissa to make index (premultiplied by 4)
	lutind = _mm_srli_epi64(lutind, ish);

	return _mm_eval_poly_d3_lut_pd(x, lut, lutind);
}

#endif
#endif
