// Based on https://github.com/tuwien-cms/xprec/blob/mainline/csrc/dd_arith.h itself based on https://github.com/scibuilder/QD/blob/master/include/qd/inline.h / https://github.com/scibuilder/QD/blob/master/include/qd/dd_inline.h

// in ../general/structs.h
// ddouble_t

extern ddouble_t ddouble(const double v);

extern ddouble_t add_dd_q_quick(double a, double b);
extern ddouble_t add_dd_q(double a, double b);
extern ddouble_t sub_dd_q(double a, double b);
extern ddouble_t mul_dd_q(double a, double b);

extern ddouble_t add_qd(ddouble_t a, double b);
extern ddouble_t sub_qd(ddouble_t a, double b);
extern ddouble_t sub_dq(double a, ddouble_t b);
extern ddouble_t mul_qd(ddouble_t a, double b);
extern ddouble_t div_qd(ddouble_t a, double b);
extern ddouble_t div_dq(double a, ddouble_t b);

extern ddouble_t add_qq(ddouble_t a, ddouble_t b);
extern ddouble_t sub_qq(ddouble_t a, ddouble_t b);
extern ddouble_t mul_qq(ddouble_t a, ddouble_t b);
extern ddouble_t mad_qqq(ddouble_t a, ddouble_t b, ddouble_t c);
extern ddouble_t div_qq(ddouble_t a, ddouble_t b);
extern ddouble_t neg_q(ddouble_t a);
extern ddouble_t abs_q(ddouble_t a);
extern ddouble_t copysign_q(ddouble_t a, ddouble_t b);
extern ddouble_t sq_q(ddouble_t a);
extern ddouble_t recip_q(ddouble_t b);
extern ddouble_t mul_qd_simple(ddouble_t a, double m);

extern int cmp_qq(const ddouble_t *a, const ddouble_t *b);
extern int cmp_qd(const ddouble_t a, const double b);

extern ddouble_t min_qq(ddouble_t a, ddouble_t b);
extern ddouble_t max_qq(ddouble_t a, ddouble_t b);
extern ddouble_t rangelimit_qqq(ddouble_t x, ddouble_t min, ddouble_t max);
extern ddouble_t floor_q(ddouble_t a);
extern ddouble_t ceil_q(ddouble_t a);
extern ddouble_t trunc_q(ddouble_t a);
extern ddouble_t nearbyint_q(ddouble_t a);

extern ddouble_t string_to_ddouble(const char *string, char **endptr);

static const ddouble_t Q_ZERO =	  {0., 0.};
static const ddouble_t Q_ONE =	  {1., 0.};
static const ddouble_t Q_NAN =	  {NAN, NAN};
static const ddouble_t Q_2PI =	  {6.2831853071795862, 2.4492935982947064e-16};
static const ddouble_t Q_PI =	  {3.1415926535897931, 1.2246467991473532e-16};
static const ddouble_t Q_PI_2 =   {1.5707963267948966, 6.123233995736766e-17};
static const ddouble_t Q_PI_4 =   {0.7853981633974483, 3.061616997868383e-17};
static const ddouble_t Q_1_2PI =  {0.15915494309189535, -9.8393383375912429e-18};
static const ddouble_t Q_1_PI =   {0.31830988618379069, -1.9678676675182486e-17};
static const ddouble_t Q_E =	  {2.7182818284590451, 1.4456468917292502e-16};
static const ddouble_t Q_LOG2 =   {0.69314718055994528, 2.3190468138462996e-17};
static const ddouble_t Q_LOG10 =  {2.3025850929940459, -2.1707562233822494e-16};
static const ddouble_t Q_1_LOG2 = {1.4426950408889634, 2.0355273740931033e-17};
