// in graphics/blending_struct.h:
// blend_func_t, blend_func_fl_t

extern void blend_solid		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_add		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_add_fl	(frgb_t *bg, frgb_t fg, float p);
extern void blend_add_limit_fl	(frgb_t *bg, frgb_t fg, float p);
extern void blend_sub		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_mul		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_mul4		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_blend		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_alphablend		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_alphablendfg		(lrgb_t *bg, lrgb_t fg, int32_t p);
extern void blend_blendalphaonly	(lrgb_t *bg, lrgb_t fg, int32_t p);
extern blend_func_fl_t get_blend_fl_equivalent(const blend_func_t bf);

extern blend_func_t cur_blend;

extern lrgb_t blend_alphablend_sep_alpha(lrgb_t Cb, lrgb_t Ca, int Ab, int Aa);
#ifdef RL_INTEL_INTR
extern void alphablend_lrgb_on_srgb_simd128(uint8_t *s0, __m128i *l_ptr, int64_t *s1_ptr, int32_t *lut0, int32_t *lut1);  // SSSE3,SSE4.1
#endif
