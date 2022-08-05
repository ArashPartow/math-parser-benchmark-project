#ifdef RL_TINYEXPR

#define TE_POW_FROM_RIGHT
#define TE_NAT_LOG
#undef pi

#pragma function (ceil)		// needed to avoid C2099 errors
#pragma function (floor)

#include "orig/tinyexpr.c"
#define pi RL_PI

double min_tefunc(double a, double b)
{
	return MINN(a, b);
}

double max_tefunc(double a, double b)
{
	return MAXN(a, b);
}

double clamp_tefunc(double v)
{
	return rangelimit(v, 0., 1.);
}

double sign_tefunc(double v)
{
	if (v < 0.)
		return -1.;

	if (v > 0.)
		return 1.;

	return 0.;
}

int etoi(const char *expr)
{
	double d = etof(expr);
	int i = (int) nearbyint(d);
	return i;
}

#endif
