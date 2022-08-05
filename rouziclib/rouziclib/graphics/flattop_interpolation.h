typedef struct interp_param_t
{
	double top, knee, c0, c1;
	double (*func)(double,double,struct interp_param_t);
} interp_param_t;

typedef struct
{
	xy_t ipscale, pin, kr0, ikr0, kr1, iw;
	xyi_t ip, jp, start, stop, jstart, jstop, dst_dim, src_dim;
	interp_param_t param_x, param_y;
} flattop_param_t;

extern double blit_scale_func_linear(double x, double unit_inv, interp_param_t p);
extern double blit_scale_func_modlin(double x, double unit_inv, interp_param_t p);
extern interp_param_t calc_interp_param_modlin(double n);
extern double calc_flattop_slope(double n);
extern flattop_param_t flattop_init_param(xyi_t dst_dim, xyi_t src_dim, xy_t pscale, xy_t pos);
extern void flattop_calc_j_bounds(flattop_param_t *p, xy_t pos);
extern void flattop_calc_weight_y(flattop_param_t *p);
extern double flattop_calc_weight(flattop_param_t *p);
