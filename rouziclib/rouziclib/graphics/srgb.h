enum
{
	NODITHER,
	DITHER,
};

enum
{
	ORDER_RGBA,
	ORDER_ABGR,
	ORDER_BGRA,
	ORDER_ARGB
};

extern double lsrgb(double linear);
extern frgb_t lsrgb_fast_frgb(frgb_t v);
extern double slrgb(double s);
extern double s8lrgb(double s8);
extern lut_t get_lut_lsrgb();
extern lut_t get_lut_slrgb();
extern lut_t get_lut_s16lrgb();
extern float s16lrgb(uint16_t v16);
extern lut_t get_lut_lsrgb_fl();
extern int32_t lsrgb_fl(float v, int32_t *lut);
extern lut_t dither_lut_init();
extern lut_t bytecheck_lut_init(int border);
extern void convert_lrgb_to_srgb(int mode);
extern void convert_frgb_to_srgb(int mode);
extern void blit_lrgb_on_srgb(srgb_t *srgb, srgb_t *srgb1);
extern void convert_linear_rgb_to_srgb(int mode);
extern void convert_srgb_to_lrgb();
extern void convert_frgb_to_lrgb();
extern void convert_frgb_to_lrgb_ratio(const float ratio);
extern srgb_t srgb_change_order_pixel(const srgb_t in, const int order);
extern void srgb_change_order(srgb_t *in, srgb_t *out, const size_t count, const int order);
