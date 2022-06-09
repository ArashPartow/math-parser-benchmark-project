#ifndef RL_EXCL_APPROX
#ifdef RL_INTEL_INTR

extern __m128i _mm_index_from_vom_ps(__m128 x, const float offset, const uint32_t mask);  // SSE2
extern __m128 _mm_eval_poly_d1_lut_ps(__m128 x, const float *lut, __m128i index);	// SSE2
extern __m128 _mm_eval_poly_d2_lut_ps(__m128 x, const float *lut, __m128i index);	// SSE2
extern __m128d _mm_eval_poly_d3_lut_pd(__m128d x, const double *lut, __m128i index);	// SSE2

extern __m128 _mm_gaussian_d1_ps(__m128 x);	// SSE2
extern __m128 _mm_erfr_d1_ps(__m128 x);		// SSE2
extern __m128 _mm_frgb_to_srgb(__m128 x);	// SSE4.1
extern __m128d _mm_fastcos_tr_d3(__m128d x);	// SSE2

#endif
#endif
