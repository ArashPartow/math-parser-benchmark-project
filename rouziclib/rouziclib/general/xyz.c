xy_t xy(const double x, const double y)
{
	xy_t out;

	out.x = x;
	out.y = y;
	return out;
}

xyz_t xyz(const double x, const double y, const double z)
{
	xyz_t out;

	out.x = x;
	out.y = y;
	out.z = z;
	return out;
}

xyi_t xyi(const int x, const int y)
{
	xyi_t out;

	out.x = x;
	out.y = y;
	return out;
}

xyq_t xyq(const ddouble_t x, const ddouble_t y)
{
	xyq_t out;

	out.x = x;
	out.y = y;
	return out;
}

void xy_to_v(xy_t a, double *v1, double *v2)
{
	*v1 = a.x;
	*v2 = a.y;
}

void xyz_to_v(xyz_t a, double *v1, double *v2, double *v3)
{
	*v1 = a.x;
	*v2 = a.y;
	*v3 = a.z;
}

void xyi_to_v(xyi_t a, int *v1, int *v2)
{
	*v1 = a.x;
	*v2 = a.y;
}

void xyq_to_v(xyq_t a, ddouble_t *v1, ddouble_t *v2)
{
	*v1 = a.x;
	*v2 = a.y;
}

xy_t xyz_to_xy(const xyz_t in)
{
	xy_t out;

	out.x = in.x;
	out.y = in.y;
	return out;
}

xyz_t xy_to_xyz(const xy_t in)
{
	xyz_t out;

	out.x = in.x;
	out.y = in.y;
	out.z = 0.;
	return out;
}

xy_t xyi_to_xy(const xyi_t in)
{
	xy_t out;

	out.x = in.x;
	out.y = in.y;
	return out;
}

xyz_t xyi_to_xyz(const xyi_t in)
{
	xyz_t out;

	out.x = in.x;
	out.y = in.y;
	out.z = 0.;
	return out;
}

xyi_t xy_to_xyi(const xy_t in)
{
	xyi_t out;

	out.x = in.x;
	out.y = in.y;
	return out;
}

xy_t xyq_to_xy(const xyq_t in)
{
	xy_t out;

	out.x = in.x.hi;
	out.y = in.y.hi;
	return out;
}

xyq_t xy_to_xyq(const xy_t in)
{
	xyq_t out;

	out.x = ddouble(in.x);
	out.y = ddouble(in.y);
	return out;
}

xy_t set_xy(const double v)
{
	return xy(v, v);
}

xyz_t set_xyz(const double v)
{
	return xyz(v, v, v);
}

xyi_t set_xyi(const int v)
{
	return xyi(v, v);
}

xyq_t set_xyq(const ddouble_t v)
{
	return xyq(v, v);
}

int is0_xy(const xy_t v)
{
	return (v.x==0. && v.y==0.);
}

int is0_xyz(const xyz_t v)
{
	return (v.x==0. && v.y==0. && v.z==0.);
}

int is0_xyi(const xyi_t v)
{
	return (v.x==0 && v.y==0);
}

int is0_xyq(const xyq_t v)
{
	return (v.x.hi==0. && v.x.lo==0. && v.y.hi==0. && v.y.lo==0.);
}

int equal_xy(const xy_t a, const xy_t b)
{
	return (a.x==b.x && a.y==b.y);
}

int equal_xyz(const xyz_t a, const xyz_t b)
{
	return (a.x==b.x && a.y==b.y && a.z==b.z);
}

int equal_xyi(const xyi_t a, const xyi_t b)
{
	return (a.x==b.x && a.y==b.y);
}

int equal_xyq(const xyq_t a, const xyq_t b)
{
	return (cmp_qq(&a.x, &b.x) == 0 && cmp_qq(&a.y, &b.y) == 0);
}

int equal_ulp_xy(const xy_t a, const xy_t b, const int64_t ulp_tolerance)
{
	int64_t ulp_x, ulp_y;

	// Measure the differences in ULP
	ulp_x = llabs(double_diff_ulp(a.x, b.x));
	ulp_y = llabs(double_diff_ulp(a.y, b.y));

	return ulp_tolerance > MAXN(ulp_x, ulp_y);
}

xy_t add_xy(xy_t a, xy_t b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

xyz_t add_xyz(xyz_t a, xyz_t b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

xyi_t add_xyi(xyi_t a, xyi_t b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

xy_t sub_xy(xy_t a, xy_t b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

xyz_t sub_xyz(xyz_t a, xyz_t b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

xyi_t sub_xyi(xyi_t a, xyi_t b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

xy_t mul_xy(xy_t a, xy_t b)
{
	a.x *= b.x;
	a.y *= b.y;
	return a;
}

xyz_t mul_xyz(xyz_t a, xyz_t b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return a;
}

xyi_t mul_xyi(xyi_t a, xyi_t b)
{
	a.x *= b.x;
	a.y *= b.y;
	return a;
}

xy_t div_xy(xy_t a, xy_t b)
{
	a.x /= b.x;
	a.y /= b.y;
	return a;
}

xy_t div_xy_0(xy_t a, xy_t b)
{
	if (b.x!=0.)
		a.x /= b.x;
	else
		a.x = 0.;

	if (b.y!=0.)
		a.y /= b.y;
	else
		a.y = 0.;
	return a;
}

xyz_t div_xyz(xyz_t a, xyz_t b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return a;
}

xyi_t div_xyi(xyi_t a, xyi_t b)
{
	a.x /= b.x;
	a.y /= b.y;
	return a;
}

xyi_t div_round_up_xyi(xyi_t a, xyi_t b)
{
	return div_xyi( add_xyi( a , sub_xyi(b, set_xyi(1)) ) , b );
}

xy_t neg_xy(xy_t a)
{
	a.x = -a.x;
	a.y = -a.y;
	return a;
}

xyz_t neg_xyz(xyz_t a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	return a;
}

xyi_t neg_xyi(xyi_t a)
{
	a.x = -a.x;
	a.y = -a.y;
	return a;
}

xy_t inv_xy(xy_t a)	// reciprocal
{
	a.x = 1. / a.x;
	a.y = 1. / a.y;
	return a;
}

xyz_t inv_xyz(xyz_t a)
{
	a.x = 1. / a.x;
	a.y = 1. / a.y;
	a.z = 1. / a.z;
	return a;
}

xyi_t inv_xyi(xyi_t a)
{
	a.x = 1. / a.x;
	a.y = 1. / a.y;
	return a;
}

xy_t neg_x(xy_t a)
{
	a.x = -a.x;
	return a;
}

xy_t neg_y(xy_t a)
{
	a.y = -a.y;
	return a;
}

xyz_t neg_x_xyz(xyz_t a)
{
	a.x = -a.x;
	return a;
}

xyz_t neg_y_xyz(xyz_t a)
{
	a.y = -a.y;
	return a;
}

xyz_t neg_z_xyz(xyz_t a)
{
	a.z = -a.z;
	return a;
}

xy_t sign_xy(xy_t a)
{
	a.x = sign(a.x);
	a.y = sign(a.y);
	return a;
}

xyz_t sign_xyz(xyz_t a)
{
	a.x = sign(a.x);
	a.y = sign(a.y);
	a.z = sign(a.z);
	return a;
}

int isnan_xy(xy_t a)
{
	return isnan(a.x) || isnan(a.y);
}

int isnan_xyz(xyz_t a)
{
	return isnan(a.x) || isnan(a.y) || isnan(a.z);
}

int isfinite_xy(xy_t a)
{
	return isfinite(a.x) && isfinite(a.y);
}

int isfinite_xyz(xyz_t a)
{
	return isfinite(a.x) && isfinite(a.y) && isfinite(a.z);
}

xyi_t cmp_ge_xyi(xyi_t a, xyi_t b)
{
	a.x = a.x >= b.x;
	a.y = a.y >= b.y;
	return a;
}

xy_t func1_xy(xy_t a, double (*f)(double))
{
	a.x = f(a.x);
	a.y = f(a.y);
	return a;
}

xyz_t func1_xyz(xyz_t a, double (*f)(double))
{
	a.x = f(a.x);
	a.y = f(a.y);
	a.z = f(a.z);
	return a;
}

xyi_t func1_xyi(xyi_t a, int (*f)(int))
{
	a.x = f(a.x);
	a.y = f(a.y);
	return a;
}

xyq_t func1_xyq(xyq_t a, ddouble_t (*f)(ddouble_t))
{
	a.x = f(a.x);
	a.y = f(a.y);
	return a;
}

xy_t func2_xy(xy_t a, xy_t b, double (*f)(double,double))
{
	a.x = f(a.x, b.x);
	a.y = f(a.y, b.y);
	return a;
}

xyz_t func2_xyz(xyz_t a, xyz_t b, double (*f)(double,double))
{
	a.x = f(a.x, b.x);
	a.y = f(a.y, b.y);
	a.z = f(a.z, b.z);
	return a;
}

xyi_t func2_xyi(xyi_t a, xyi_t b, int (*f)(int,int))
{
	a.x = f(a.x, b.x);
	a.y = f(a.y, b.y);
	return a;
}

xyq_t func2_xyq(xyq_t a, xyq_t b, ddouble_t (*f)(ddouble_t,ddouble_t))
{
	a.x = f(a.x, b.x);
	a.y = f(a.y, b.y);
	return a;
}

xy_t func3_xy(xy_t a, xy_t b, xy_t c, double (*f)(double,double,double))
{
	a.x = f(a.x, b.x, c.x);
	a.y = f(a.y, b.y, c.y);
	return a;
}

xyz_t func3_xyz(xyz_t a, xyz_t b, xyz_t c, double (*f)(double,double,double))
{
	a.x = f(a.x, b.x, c.x);
	a.y = f(a.y, b.y, c.y);
	a.z = f(a.z, b.z, c.z);
	return a;
}

xyi_t func3_xyi(xyi_t a, xyi_t b, xyi_t c, int (*f)(int,int,int))
{
	a.x = f(a.x, b.x, c.x);
	a.y = f(a.y, b.y, c.y);
	return a;
}

xyq_t func3_xyq(xyq_t a, xyq_t b, xyq_t c, ddouble_t (*f)(ddouble_t,ddouble_t,ddouble_t))
{
	a.x = f(a.x, b.x, c.x);
	a.y = f(a.y, b.y, c.y);
	return a;
}

xyi_t lshift_xyi(xyi_t a, int sh)
{
	a.x <<= sh;
	a.y <<= sh;
	return a;
}

xyi_t rshift_xyi(xyi_t a, int sh)
{
	a.x >>= sh;
	a.y >>= sh;
	return a;
}

xyi_t ceil_rshift_xyi(xyi_t a, int sh)
{
	a.x = ceil_rshift(a.x, sh);
	a.y = ceil_rshift(a.y, sh);
	return a;
}

xyi_t and_xyi(xyi_t a, int mask)
{
	a.x &= mask;
	a.y &= mask;
	return a;
}

// The following functions return individual minimums or maximums
xy_t min_xy(xy_t a, xy_t b)
{
	a.x = MINN(a.x, b.x);
	a.y = MINN(a.y, b.y);
	return a;
}

xyz_t min_xyz(xyz_t a, xyz_t b)
{
	a.x = MINN(a.x, b.x);
	a.y = MINN(a.y, b.y);
	a.z = MINN(a.z, b.z);
	return a;
}

xyi_t min_xyi(xyi_t a, xyi_t b)
{
	a.x = MINN(a.x, b.x);
	a.y = MINN(a.y, b.y);
	return a;
}

xy_t max_xy(xy_t a, xy_t b)
{
	a.x = MAXN(a.x, b.x);
	a.y = MAXN(a.y, b.y);
	return a;
}

xyz_t max_xyz(xyz_t a, xyz_t b)
{
	a.x = MAXN(a.x, b.x);
	a.y = MAXN(a.y, b.y);
	a.z = MAXN(a.z, b.z);
	return a;
}

xyi_t max_xyi(xyi_t a, xyi_t b)
{
	a.x = MAXN(a.x, b.x);
	a.y = MAXN(a.y, b.y);
	return a;
}

void minmax_xy(xy_t *a, xy_t *b)
{
	minmax_double(&a->x, &b->x);
	minmax_double(&a->y, &b->y);
}

void minmax_xyz(xyz_t *a, xyz_t *b)
{
	minmax_double(&a->x, &b->x);
	minmax_double(&a->y, &b->y);
	minmax_double(&a->z, &b->z);
}

void minmax_xyi(xyi_t *a, xyi_t *b)
{
	minmax_i32(&a->x, &b->x);
	minmax_i32(&a->y, &b->y);
}

// the following functions return minimums or maximums of all components
double min_of_xy(xy_t a)
{
	return MINN(a.x, a.y);
}

double max_of_xy(xy_t a)
{
	return MAXN(a.x, a.y);
}

double min_of_xyz(xyz_t a)
{
	return MINN(MINN(a.x, a.y), a.z);
}

double max_of_xyz(xyz_t a)
{
	return MAXN(MAXN(a.x, a.y), a.z);
}

int min_of_xyi(xyi_t a)
{
	return MINN(a.x, a.y);
}

int max_of_xyi(xyi_t a)
{
	return MAXN(a.x, a.y);
}

double mul_x_by_y_xy(xy_t a)
{
	return a.x * a.y;
}

double div_x_by_y_xy(xy_t a)
{
	return a.x / a.y;
}

double div_y_by_x_xy(xy_t a)
{
	return a.y / a.x;
}

int mul_x_by_y_xyi(xyi_t a)
{
	return a.x * a.y;
}

xy_t mad_xy(xy_t pos, xy_t tmul, xy_t tadd)
{
	return add_xy(mul_xy(pos, tmul), tadd);
}

xyz_t mad_xyz(xyz_t pos, xyz_t tmul, xyz_t tadd)
{
	return add_xyz(mul_xyz(pos, tmul), tadd);
}

xyi_t mad_xyi(xyi_t pos, xyi_t tmul, xyi_t tadd)
{
	return add_xyi(mul_xyi(pos, tmul), tadd);
}

double get_xyz_index(xyz_t v, const int index)
{
	switch (index)
	{
		case 0:	return v.x;
		case 1:	return v.y;
		case 2:	return v.z;
	}

	return 0.;
}

xy_t swap_xy(xy_t v)
{
	swap_double(&v.x, &v.y);
	return v;
}

matrix_t matrix_xyz(xyz_t x, xyz_t y, xyz_t z)
{
	matrix_t out;

	out.x = x;
	out.y = y;
	out.z = z;
	return out;
}

matrix_t matrices_mul(matrix_t a, matrix_t b)
{
	matrix_t c;

	c.x = xyz( a.x.x*b.x.x + a.x.y*b.y.x + a.x.z*b.z.x , a.x.x*b.x.y + a.x.y*b.y.y + a.x.z*b.z.y , a.x.x*b.x.z + a.x.y*b.y.z + a.x.z*b.z.z );
	c.y = xyz( a.y.x*b.x.x + a.y.y*b.y.x + a.y.z*b.z.x , a.y.x*b.x.y + a.y.y*b.y.y + a.y.z*b.z.y , a.y.x*b.x.z + a.y.y*b.y.z + a.y.z*b.z.z );
	c.z = xyz( a.z.x*b.x.x + a.z.y*b.y.x + a.z.z*b.z.x , a.z.x*b.x.y + a.z.y*b.y.y + a.z.z*b.z.y , a.z.x*b.x.z + a.z.y*b.y.z + a.z.z*b.z.z );
	return c;
}

xyz_t matrix_mul(xyz_t v, matrix_t m)
{
	xyz_t r;

	r.x = v.x*m.x.x + v.y*m.x.y + v.z*m.x.z;
	r.y = v.x*m.y.x + v.y*m.y.y + v.z*m.y.z;
	r.z = v.x*m.z.x + v.y*m.z.y + v.z*m.z.z;

	return r;
}
