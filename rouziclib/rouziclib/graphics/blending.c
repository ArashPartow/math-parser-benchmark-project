blend_func_t cur_blend=blend_add;

// The following functions blend a whole foreground pixel with a background pixel by a ratio of p (1.15 fixed-point format)

void blend_solid(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	*bg = fg;
}

void blend_add(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	int32_t r, g, b;

	r = (fg.r * p >> 15) + bg->r;	if (r>ONE) bg->r = ONE; else bg->r = r;
	g = (fg.g * p >> 15) + bg->g;	if (g>ONE) bg->g = ONE; else bg->g = g;
	b = (fg.b * p >> 15) + bg->b;	if (b>ONE) bg->b = ONE; else bg->b = b;
}

void blend_add_fl(frgb_t *bg, frgb_t fg, float p)
{
	float r, g, b;

	bg->r += fg.r * p;
	bg->g += fg.g * p;
	bg->b += fg.b * p;
}

void blend_add_limit_fl(frgb_t *bg, frgb_t fg, float p)
{
	blend_add_fl(bg, fg, p);
	rangelimit_frgb(bg);
}

void blend_sub(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	int32_t r, g, b;

	r = -(fg.r * p >> 15) + bg->r;	if (r<0) bg->r = 0; else bg->r = r;
	g = -(fg.g * p >> 15) + bg->g;	if (g<0) bg->g = 0; else bg->g = g;
	b = -(fg.b * p >> 15) + bg->b;	if (b<0) bg->b = 0; else bg->b = b;
}

void blend_mul(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	int32_t pinv;

	pinv = 32768 - p;
	bg->r = (bg->r*fg.r >> LBD) * p + bg->r * pinv >> 15;
	bg->g = (bg->g*fg.g >> LBD) * p + bg->g * pinv >> 15;
	bg->b = (bg->b*fg.b >> LBD) * p + bg->b * pinv >> 15;
}

void blend_mul4(lrgb_t *bg, lrgb_t fg, int32_t p)	// multiply by a quarter intensity image (1.0 == sRGB value of 137)
{
	int32_t r, g, b, pinv;

	pinv = 32768 - p;
	r = (bg->r*fg.r >> (LBD-2)) * p + bg->r * pinv >> 15;	if (r>ONE) bg->r = ONE; else bg->r = r;
	g = (bg->g*fg.g >> (LBD-2)) * p + bg->g * pinv >> 15;	if (g>ONE) bg->g = ONE; else bg->g = g;
	b = (bg->b*fg.b >> (LBD-2)) * p + bg->b * pinv >> 15;	if (b>ONE) bg->b = ONE; else bg->b = b;
}

void blend_blend(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	int32_t pinv;

	pinv = 32768 - p;
	bg->r = fg.r * p + bg->r * pinv >> 15;
	bg->g = fg.g * p + bg->g * pinv >> 15;
	bg->b = fg.b * p + bg->b * pinv >> 15;
}

int alphablend_one_channel(int Cb, int Ca, int Ab_ai, int Aa, int Aoi)
{
	int Co;
	Co = ( (int64_t) Ca*Aa + ((int64_t) Cb*Ab_ai >> 15) ) * Aoi >> 30;	// 1.LBD format

	return MINN(ONE, Co);
}

lrgb_t blend_alphablend_sep_alpha(lrgb_t Cb, lrgb_t Ca, int Ab, int Aa)	// pixel a on top of pixel b, with separated 1.15 format alpha values
{
	lrgb_t Co={0};
	int Aai, Ao, Aoi, Ab_ai;

	// Special cases
	if (Aa == 32768)		// if the front pixel is opaque
		return Ca;		// just return the front pixel
	else if (Aa == 0)		// if the front pixel is transparent
		return Cb;		// just return the back pixel
	else if (Ab == 0)		// if the back pixel is blank
	{
		Ca.a = Q15_TO_LBD(Aa);	// update the front pixel's alpha that takes the multiplication by p into account
		return Ca;		// the output pixel is the front pixel
	}

	Aai = 32768 - Aa;
	Ab_ai = Ab * Aai;
	Ao = Aa + (Ab_ai >> 15);	// output alpha in 1.15
	Co.a = Q15_TO_LBD(Ao);
	if (Ao==0)
		return Co;

	Aoi = (1L<<30) / Ao;		// inverted to make the division, 0.30 format

	Co.r = alphablend_one_channel(Cb.r, Ca.r, Ab_ai, Aa, Aoi);
	Co.g = alphablend_one_channel(Cb.g, Ca.g, Ab_ai, Aa, Aoi);
	Co.b = alphablend_one_channel(Cb.b, Ca.b, Ab_ai, Aa, Aoi);

	return Co;
}

void blend_alphablend(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	*bg = blend_alphablend_sep_alpha(*bg, fg, LBD_TO_Q15(bg->a), LBD_TO_Q15(fg.a) * p >> 15);
}

void blend_alphablendfg(lrgb_t *bg, lrgb_t fg, int32_t p)	// alpha blending (doesn't take framebuffer's alpha into account though, assumed to be 1.0)
{
	int32_t pinv;

	p = p * fg.a >> LBD;
	pinv = 32768 - p;

	bg->r = fg.r * p + bg->r * pinv >> 15;
	bg->g = fg.g * p + bg->g * pinv >> 15;
	bg->b = fg.b * p + bg->b * pinv >> 15;
	bg->a = fg.a * p + bg->a * pinv >> 15;
}

void blend_blendalphaonly(lrgb_t *bg, lrgb_t fg, int32_t p)
{
	int32_t pinv;

	pinv = 32768 - p;
	bg->a = fg.a * p + bg->a * pinv >> 15;
}

blend_func_fl_t get_blend_fl_equivalent(const blend_func_t bf)
{
	if (bf==blend_add)
		return blend_add_limit_fl;

	return blend_add_limit_fl;
}

#ifdef RL_INTEL_INTR
#ifdef __GNUC__
__attribute__((__target__("ssse3,sse4.1")))
#endif
void alphablend_lrgb_on_srgb_simd128(uint8_t *s0, __m128i *l_ptr, int64_t *s1_ptr, int32_t *lut0, int32_t *lut1)	// AVX2
{
	__m128i Ca, Cb, Aa, Aai, alpha_mask, Co;

	// Load 2 lrgb pixels
	Ca = _mm_lddqu_si128(l_ptr);					// load 2 lrgb pixels (8 x i16)
	alpha_mask = _mm_set_epi16(0xFFFF, 0, 0, 0, 0xFFFF, 0, 0, 0);

	// Alpha testing
	if (_mm_test_all_zeros(Ca, alpha_mask))				// if all 2 lrgb pixels are transparent
	{
		_mm_storeu_si64(s1_ptr, _mm_loadl_epi64((__m128i *) s0));		// copy the original 2 srgb pixels
		return;
	}

	// Zero alpha values that are 32768
	Aa = _mm_xor_si128(Ca, _mm_set_epi16(0x8000, 0, 0, 0, 0x8000, 0, 0, 0));

	// Blending
	if (_mm_test_all_zeros(Aa, alpha_mask)==0)			// we do the blending math only if Aa != 32768
	{
		// RGBA -> AAAA for the 2 lrgb pixels
		Aa = _mm_shuffle_epi8(Ca, _mm_set_epi8(8+7, 8+6, 8+7, 8+6, 8+7, 8+6, 8+7, 8+6, 7, 6, 7, 6, 7, 6, 7, 6));
		Aai = _mm_sub_epi16(_mm_set1_epi16(0x8000), Aa);	// 32768 - Aa

		// Convert 2 srgb pixels to lrgb
		Cb = _mm_set_epi16(lut0[s0[7]], lut0[s0[6]], lut0[s0[5]], lut0[s0[4]], lut0[s0[3]], lut0[s0[2]], lut0[s0[1]], lut0[s0[0]]);

		// Do the blending math
		Ca = _mm_mulhi_epu16(Ca, Aa);				// Ca*Aa >> 16
		Cb = _mm_mulhi_epu16(Cb, Aai);				// Cb*Aai >> 16
		Ca = _mm_add_epi16(Ca, Cb);
		Ca = _mm_slli_epi16(Ca, 1);				// <<= 1 to convert from 1.14 to 1.15
	}

	// Lookups for linear 1.15 to sRGB 8.5
	uint16_t Cac[8];
	_mm_store_si128((__m128i *) &Cac, Ca);
	Co = _mm_set_epi16(lut1[Cac[7]], lut1[Cac[6]], lut1[Cac[5]], lut1[Cac[4]], lut1[Cac[3]], lut1[Cac[2]], lut1[Cac[1]], lut1[Cac[0]]);

	// Shift and shuffle to pack from 16-bit sRGB 8.5 to 8-bit sRGB
	Co = _mm_srli_epi16(Co, 5);	// >>= 5 to make it 8 bit
	Co = _mm_shuffle_epi8(Co, _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, 14, 12, 10, 8, 6,  4,  2,  0));

	// Store result
	_mm_storeu_si64(s1_ptr, Co);

	/* Blending algorithm
	if (Aa == 32768) return Ca;
	else if (Aa == 0) return Cb;

	Aai = 32768 - Aa;
	Co = ( Ca*Aa + Cb*Aai ) >> 15;	// 1.LBD format*/
}
#endif
