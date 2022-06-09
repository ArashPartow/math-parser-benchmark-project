enum
{
	HUERAD,
	HUEDEG,
	HUE03,
};

#define WEIGHT_R 0.16		// perceptual weights for each channel used to compute perceptual luminosity
#define WEIGHT_G 0.73
#define WEIGHT_B 0.11

#ifdef COL_FRGB
	#define make_colour		make_colour_frgb
	#define frgb_to_col(x)		(x)
	#define lrgb_to_col(x)		lrgb_to_frgb(x)
	#define col_to_frgb(x)		(x)
	#define col_to_lrgb(x)		frgb_to_lrgb(x)
	#define make_colour_srgb	make_colour_srgb_f
	#define make_grey		make_grey_f
	#define make_colour_hsl		make_colour_hsl_f
	#define	make_colour_hsl_cw	make_colour_hsl_cw_f
	#define get_rgb_channel		get_frgb_channel
	#define set_rgb_channel		set_frgb_channel
	#define col_to_rgb		frgb_to_rgb
	#define col_to_xyz		frgb_to_xyz
	#define col_to_hsl		frgb_to_hsl
	#define col_invert_linear	col_invert_linear_f
	#define col_invert_Lab		col_invert_Lab_f
	#define add_col			add_frgba
#else
	#define make_colour		make_colour_lin
	#define frgb_to_col(x)		frgb_to_lrgb(x)
	#define lrgb_to_col(x)		(x)
	#define col_to_frgb(x)		lrgb_to_frgb(x)
	#define col_to_lrgb(x)		(x)
	#define make_colour_srgb	make_colour_srgb_l
	#define make_grey		make_grey_l
	#define make_colour_hsl		make_colour_hsl_l
	#define	make_colour_hsl_cw	make_colour_hsl_cw_l
	#define get_rgb_channel		get_lrgb_channel
	#define set_rgb_channel		set_lrgb_channel
	#define col_to_rgb		lrgb_to_rgb
	#define col_to_xyz		lrgb_to_xyz
	#define col_to_hsl		lrgb_to_hsl
	#define add_col			add_lrgb
#endif

extern lrgb_t make_colour_lin(const double r, const double g, const double b, const double a);
extern frgb_t make_colour_frgb(const double r, const double g, const double b, const double a);
extern srgb_t make_colour_srgb_s(int r, int g, int b, int a);
extern lrgb_t make_colour_srgb_l(int r, int g, int b, int a);
extern frgb_t make_colour_srgb_f(int r, int g, int b, int a);
extern srgb_t make_colour_f_srgb(float r, float g, float b, float a);
extern lrgb_t make_grey_l(double v);
extern frgb_t make_grey_f(double v);
extern double frgb_to_grey_level(frgb_t p);
extern double Lab_L_to_linear(double t);
extern frgb_t Lab_L_to_linear_f(frgb_t c);
extern double linear_to_Lab_L(double t);
extern frgb_t linear_to_Lab_L_f(frgb_t c);
extern double Lab_L_invert(double x);
extern frgb_t col_invert_linear_f(frgb_t c);
extern frgb_t col_invert_Lab_f(frgb_t c);
extern void rgb_to_hsl_cw(double Wr, double Wg, double Wb, double r, double g, double b, double *H, double *S, double *L, int huemode);
extern void rgb_to_hsl(double r, double g, double b, double *H, double *S, double *L, int huemode);
extern void hsl_to_rgb_cw(double Wr, double Wg, double Wb, double H, double S, double L, double *r, double *g, double *b, int huemode, int secboost);
extern void hsl_to_rgb(double H, double S, double L, double *r, double *g, double *b, int huemode, int secboost);
extern frgb_t hsl_to_frgb(double H, double S, double L, int huemode, int secboost);
extern lrgb_t make_colour_hsl_l(double H, double S, double L, int huemode, int secboost);
extern frgb_t make_colour_hsl_f(double H, double S, double L, int huemode, int secboost);
extern lrgb_t make_colour_hsl_cw_l(double Wr, double Wg, double Wb, double H, double S, double L, int huemode, int secboost);
extern frgb_t make_colour_hsl_cw_f(double Wr, double Wg, double Wb, double H, double S, double L, int huemode, int secboost);
extern double get_lrgb_channel(lrgb_t col, int ch);
extern double get_frgb_channel(frgb_t col, int ch);
extern void set_lrgb_channel(lrgb_t *col, int ch, double value);
extern void set_frgb_channel(frgb_t *col, int ch, double value);
extern void lrgb_to_rgb(lrgb_t col, double *r, double *g, double *b);
extern void frgb_to_rgb(frgb_t col, double *r, double *g, double *b);
extern xyz_t lrgb_to_xyz(lrgb_t col);
extern xyz_t frgb_to_xyz(frgb_t col);
extern col_t xyz_to_col(xyz_t v);
extern lrgb_t xyz_to_lrgb(xyz_t v);
extern frgb_t xyz_to_frgb(xyz_t v);
extern int is0_col(col_t col);
extern void lrgb_to_hsl(lrgb_t col, double *H, double *S, double *L, int huemode);
extern void frgb_to_hsl(frgb_t col, double *H, double *S, double *L, int huemode);
extern void colour_blowout_double_cw(double Wr, double Wg, double Wb, double *pred, double *pgrn, double *pblu);
extern void colour_blowout_double(double *pred, double *pgrn, double *pblu);
extern void colour_blowout_int_cw(uint32_t Wr, uint32_t Wg, uint32_t Wb, uint32_t *pred, uint32_t *pgrn, uint32_t *pblu);
extern void colour_blowout_int(uint32_t *pred, uint32_t *pgrn, uint32_t *pblu);
extern void rangelimit_frgb(frgb_t *c);
extern col_t get_colour_seq_linear(double x, xyz_t freq, xyz_t phase, double m, double a);
extern col_t get_colour_seq_fullarg(double x, xyz_t freq, xyz_t phase, double m, double a);
extern col_t get_colour_seq(double x, xyz_t freq, xyz_t phase);
extern col_t colour_mul(col_t col, double m);
extern col_t mix_colours(col_t a, col_t b, double t);
extern col_t adjust_colour_lum(col_t col, double target_lum);

extern raster_t convert_float_array_to_frgb(float *fa, xyi_t dim, raster_t *rp);

extern frgb_t add_frgb(frgb_t a, frgb_t b);
extern frgb_t add_frgba(frgb_t a, frgb_t b);
extern lrgb_t add_lrgb(lrgb_t a, lrgb_t b);
extern frgb_t sub_frgb(frgb_t a, frgb_t b);
extern frgb_t mul_frgb(frgb_t a, frgb_t b);
extern frgb_t div_frgb(frgb_t a, frgb_t b);
extern float min_of_frgb(frgb_t a);
extern float max_of_frgb(frgb_t a);
extern frgb_t mul_scalar_frgb(frgb_t a, float m);
extern frgb_t mul_scalar_frgba(frgb_t a, float m);
extern lrgb_t mul_scalar_lrgb(lrgb_t a, int m);
extern frgb_t func1_frgb(frgb_t a, float (*f)(float));
extern frgb_t clamp_frgba(frgb_t a);
extern frgb_t frgb_diff(frgb_t a, frgb_t b);
extern frgb_t frgb_perceptual_diff(frgb_t a, frgb_t b);
