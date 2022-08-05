#ifdef RL_TINYEXPR

#include "orig/tinyexpr.h"

#define RL_EXPR_FUNC								\
	{"gaussian", gaussian, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"erf", erf, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"erfr", erfr, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"erfinv", erfinv, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"integral_erfr", integral_of_erfr, TE_FUNCTION1 | TE_FLAG_PURE},	\
	{"lgamma", lgamma, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"gamma", tgamma, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"gamma_dist", gamma_dist, TE_FUNCTION3 | TE_FLAG_PURE},		\
	{"sinc", sinc, TE_FUNCTION2 | TE_FLAG_PURE},				\
	{"blackman", blackman, TE_FUNCTION2 | TE_FLAG_PURE},			\
	{"short_erf", short_erf, TE_FUNCTION2 | TE_FLAG_PURE},			\
	{"lab_to_linear", Lab_L_to_linear, TE_FUNCTION1 | TE_FLAG_PURE},	\
	{"linear_to_lab", linear_to_Lab_L, TE_FUNCTION1 | TE_FLAG_PURE},	\
	{"lab_invert", Lab_L_invert, TE_FUNCTION1 | TE_FLAG_PURE},		\
	{"lsrgb", lsrgb, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"slrgb", slrgb, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"db_to_vol", db_to_vol, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"vol_to_db", vol_to_db, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"nearbyint", nearbyint, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"min", min_tefunc, TE_FUNCTION2 | TE_FLAG_PURE},			\
	{"max", max_tefunc, TE_FUNCTION2 | TE_FLAG_PURE},			\
	{"clamp", clamp_tefunc, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"rangelimit", rangelimit, TE_FUNCTION3 | TE_FLAG_PURE},		\
	{"sign", sign_tefunc, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"sgn", sign_tefunc, TE_FUNCTION1 | TE_FLAG_PURE},			\
	{"trunc", trunc, TE_FUNCTION1 | TE_FLAG_PURE},				\
	{"sq", sq, TE_FUNCTION1 | TE_FLAG_PURE}

extern double min_tefunc(double a, double b);
extern double max_tefunc(double a, double b);
extern double clamp_tefunc(double v);
extern double sign_tefunc(double v);
//#define etof(expr) te_interp(expr, NULL)
extern int etoi(const char *expr);

#endif
