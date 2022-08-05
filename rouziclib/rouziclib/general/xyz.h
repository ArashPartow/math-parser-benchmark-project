// in general/xyz_struct.h:
// xy_t, xyi_t, xyz_t, xyq_t, matrix_t

#define XY0	xy(0.,0.)
#define XY1	xy(1.,1.)
#define XYI0	xyi(0,0)
#define XYI1	xyi(1,1)
#define XYZ0	xyz(0.,0.,0.)
#define XYQ0	set_xyq(ddouble(0.))
#define XYNAN	xy(NAN,NAN)
#define zyx(z, y, x)	xyz(x, y, z)

extern xy_t xy(const double x, const double y);
extern xyz_t xyz(const double x, const double y, const double z);
extern xyi_t xyi(const int x, const int y);
extern xyq_t xyq(const ddouble_t x, const ddouble_t y);
extern void xy_to_v(xy_t a, double *v1, double *v2);
extern void xyz_to_v(xyz_t a, double *v1, double *v2, double *v3);
extern void xyi_to_v(xyi_t a, int *v1, int *v2);
extern void xyq_to_v(xyq_t a, ddouble_t *v1, ddouble_t *v2);
extern xy_t xyz_to_xy(const xyz_t in);
extern xyz_t xy_to_xyz(const xy_t in);
extern xy_t xyi_to_xy(const xyi_t in);
extern xyz_t xyi_to_xyz(const xyi_t in);
extern xyi_t xy_to_xyi(const xy_t in);
extern xy_t xyq_to_xy(const xyq_t in);
extern xyq_t xy_to_xyq(const xy_t in);
extern xy_t set_xy(const double v);
extern xyz_t set_xyz(const double v);
extern xyi_t set_xyi(const int v);
extern xyq_t set_xyq(const ddouble_t v);

extern int is0_xy(const xy_t v);
extern int is0_xyz(const xyz_t v);
extern int is0_xyi(const xyi_t v);
extern int is0_xyq(const xyq_t v);
extern int equal_xy(const xy_t a, const xy_t b);
extern int equal_xyz(const xyz_t a, const xyz_t b);
extern int equal_xyi(const xyi_t a, const xyi_t b);
extern int equal_xyq(const xyq_t a, const xyq_t b);
extern int equal_ulp_xy(const xy_t a, const xy_t b, const int64_t ulp_tolerance);
extern xy_t add_xy(xy_t a, xy_t b);
extern xyz_t add_xyz(xyz_t a, xyz_t b);
extern xyi_t add_xyi(xyi_t a, xyi_t b);
extern xy_t sub_xy(xy_t a, xy_t b);
extern xyz_t sub_xyz(xyz_t a, xyz_t b);
extern xyi_t sub_xyi(xyi_t a, xyi_t b);
extern xy_t mul_xy(xy_t a, xy_t b);
extern xyz_t mul_xyz(xyz_t a, xyz_t b);
extern xyi_t mul_xyi(xyi_t a, xyi_t b);
extern xy_t div_xy(xy_t a, xy_t b);
extern xy_t div_xy_0(xy_t a, xy_t b);
extern xyz_t div_xyz(xyz_t a, xyz_t b);
extern xyi_t div_xyi(xyi_t a, xyi_t b);
extern xyi_t div_round_up_xyi(xyi_t a, xyi_t b);
extern xy_t neg_xy(xy_t a);
extern xyz_t neg_xyz(xyz_t a);
extern xyi_t neg_xyi(xyi_t a);
extern xy_t inv_xy(xy_t a);
extern xyz_t inv_xyz(xyz_t a);
extern xyi_t inv_xyi(xyi_t a);
extern xy_t neg_x(xy_t a);
extern xy_t neg_y(xy_t a);
extern xyz_t neg_x_xyz(xyz_t a);
extern xyz_t neg_y_xyz(xyz_t a);
extern xyz_t neg_z_xyz(xyz_t a);
extern xy_t sign_xy(xy_t a);
extern xyz_t sign_xyz(xyz_t a);
extern int isnan_xy(xy_t a);
extern int isnan_xyz(xyz_t a);
extern int isfinite_xy(xy_t a);
extern int isfinite_xyz(xyz_t a);
extern xyi_t cmp_ge_xyi(xyi_t a, xyi_t b);

#define abs_xy(a)	func1_xy(a, fabs)
#define abs_xyz(a)	func1_xyz(a, fabs)
#define abs_xyi(a)	func1_xyi(a, abs)
#define sqrt_xy(a)	func1_xy(a, sqrt)
#define cos_xy(a)	func1_xy(a, cos)
#define cos_xyz(a)	func1_xyz(a, cos)
#define sin_xy(a)	func1_xy(a, sin)
#define sin_xyz(a)	func1_xyz(a, sin)
#define floor_xy(a)	func1_xy(a, floor)
#define ceil_xy(a)	func1_xy(a, ceil)
#define nearbyint_xy(a)	func1_xy(a, nearbyint)
#define sq_xy(a)	func1_xy(a, sq)
#define sq_xyz(a)	func1_xyz(a, sq)
#define xy_to_xyi_round(a)  xy_to_xyi(nearbyint_xy(a))
extern xy_t func1_xy(xy_t a, double (*f)(double));
extern xyz_t func1_xyz(xyz_t a, double (*f)(double));
extern xyi_t func1_xyi(xyi_t a, int (*f)(int));
extern xyq_t func1_xyq(xyq_t a, ddouble_t (*f)(ddouble_t));

#define fmod_xy(a, b)	func2_xy(a, b, fmod)
#define copysign_xy(a, b) func2_xy(a, b, copysign)
#define add_xyq(a,b)	func2_xyq(a, b, add_qq)
#define sub_xyq(a,b)	func2_xyq(a, b, sub_qq)
#define mul_xyq(a,b)	func2_xyq(a, b, mul_qq)
#define div_xyq(a,b)	func2_xyq(a, b, div_qq)
#define neg_xyq(a,b)	func2_xyq(a, b, neg_q)
#define inv_xyq(a,b)	func2_xyq(a, b, recip_q)
extern xy_t func2_xy(xy_t a, xy_t b, double (*f)(double,double));
extern xyz_t func2_xyz(xyz_t a, xyz_t b, double (*f)(double,double));
extern xyi_t func2_xyi(xyi_t a, xyi_t b, int (*f)(int,int));
extern xyq_t func2_xyq(xyq_t a, xyq_t b, ddouble_t (*f)(ddouble_t,ddouble_t));

#define mix_xy(a, b, c)		func3_xy(a, b, c, mix)
#define mix_xyz(a, b, c)	func3_xyz(a, b, c, mix)
#define rangelimit_xy(a, b, c)	func3_xy(a, b, c, rangelimit)
#define rangelimit_xyz(a, b, c)	func3_xyz(a, b, c, rangelimit)
#define rangelimit_xyi(a, b, c)	func3_xyi(a, b, c, rangelimit_i32)
extern xy_t func3_xy(xy_t a, xy_t b, xy_t c, double (*f)(double,double,double));
extern xyz_t func3_xyz(xyz_t a, xyz_t b, xyz_t c, double (*f)(double,double,double));
extern xyi_t func3_xyi(xyi_t a, xyi_t b, xyi_t c, int (*f)(int,int,int));
extern xyq_t func3_xyq(xyq_t a, xyq_t b, xyq_t c, ddouble_t (*f)(ddouble_t,ddouble_t,ddouble_t));

extern xyi_t lshift_xyi(xyi_t a, int sh);
extern xyi_t rshift_xyi(xyi_t a, int sh);
extern xyi_t ceil_rshift_xyi(xyi_t a, int sh);
extern xyi_t and_xyi(xyi_t a, int mask);

extern xy_t min_xy(xy_t a, xy_t b);
extern xyz_t min_xyz(xyz_t a, xyz_t b);
extern xyi_t min_xyi(xyi_t a, xyi_t b);
extern xy_t max_xy(xy_t a, xy_t b);
extern xyz_t max_xyz(xyz_t a, xyz_t b);
extern xyi_t max_xyi(xyi_t a, xyi_t b);
extern void minmax_xy(xy_t *a, xy_t *b);
extern void minmax_xyz(xyz_t *a, xyz_t *b);
extern void minmax_xyi(xyi_t *a, xyi_t *b);
extern double min_of_xy(xy_t a);
extern double max_of_xy(xy_t a);
extern double min_of_xyz(xyz_t a);
extern double max_of_xyz(xyz_t a);
extern int min_of_xyi(xyi_t a);
extern int max_of_xyi(xyi_t a);
extern double mul_x_by_y_xy(xy_t a);
extern double div_x_by_y_xy(xy_t a);
extern double div_y_by_x_xy(xy_t a);
extern int mul_x_by_y_xyi(xyi_t a);

extern xy_t mad_xy(xy_t pos, xy_t tmul, xy_t tadd);
extern xyz_t mad_xyz(xyz_t pos, xyz_t tmul, xyz_t tadd);
extern xyi_t mad_xyi(xyi_t pos, xyi_t tmul, xyi_t tadd);
extern double get_xyz_index(xyz_t v, const int index);
extern xy_t swap_xy(xy_t v);

extern matrix_t matrix_xyz(xyz_t x, xyz_t y, xyz_t z);
extern matrix_t matrices_mul(matrix_t a, matrix_t b);
extern xyz_t matrix_mul(xyz_t v, matrix_t m);
