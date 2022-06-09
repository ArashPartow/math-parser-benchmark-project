extern frgb_t lrgb_to_frgb(lrgb_t l);
extern frgb_t srgb_to_frgb(srgb_t s);
extern frgb_t sqrgb_to_frgb(sqrgb_t s);

#ifdef RL_INTEL_INTR
extern __m128 _mm_lrgb_to_ps(lrgb_t l);    // SSE2
extern __m128 _mm_srgb_to_ps(srgb_t s);    // SSE
extern __m128 _mm_sqrgb_to_ps(sqrgb_t s);  // SSE2

extern __m128 _mm_get_raster_pixel_frgb_to_ps(raster_t *r, const size_t index);   // SSE
extern __m128 _mm_get_raster_pixel_lrgb_to_ps(raster_t *r, const size_t index);   // SSE2
extern __m128 _mm_get_raster_pixel_srgb_to_ps(raster_t *r, const size_t index);   // SSE
extern __m128 _mm_get_raster_pixel_sqrgb_to_ps(raster_t *r, const size_t index);  // SSE2
#endif

extern lrgb_t frgb_to_lrgb(frgb_t cf);
extern srgb_t frgb_to_srgb(frgb_t cf);
extern sqrgb_t frgb_to_sqrgb(frgb_t f);

#ifdef RL_INTEL_INTR
extern void _mm_set_raster_pixel_ps_to_frgb(raster_t *r, const size_t index, __m128 f);  // SSE
extern void _mm_set_raster_pixel_ps_to_lrgb(raster_t *r, const size_t index, __m128 f);  // SSSE3
extern void _mm_set_raster_pixel_ps_to_srgb(raster_t *r, const size_t index, __m128 f);  // SSSE3, calls SSE4.1
extern void _mm_set_raster_pixel_ps_to_sqrgb(raster_t *r, const size_t index, __m128 f); // SSE2
#endif

extern void image_float_channel_conversion(float *in, int in_chan, float *out, int out_chan);
