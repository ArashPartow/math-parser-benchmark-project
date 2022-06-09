extern void draw_line_thin_lrgb(xy_t p1, xy_t p2, double radius, lrgb_t colour, const blend_func_t bf, double intensity);
extern void draw_line_thin_frgb(xy_t p1, xy_t p2, double radius, frgb_t colour, const blend_func_fl_t bf, double intensity);
extern void draw_line_thin_dq(xy_t p1, xy_t p2, double radius, frgb_t colour, const int bf, double intensity, int quality);
extern void draw_line_thin(xy_t p1, xy_t p2, double radius, col_t colour, const blend_func_t bf, double intensity);
extern void draw_line_thin_rectclip(xy_t p1, xy_t p2, xy_t b1, xy_t b2, double radius, col_t colour, const blend_func_t bf, double intensity);
extern void draw_line_thin_short(xy_t p1, xy_t p2, double u1, double u2, double radius, col_t colour, const blend_func_t bf, double intensity);
extern void bres_func_lrgb(xyi_t ip, raster_t *r, lrgb_t *col, void *arg3, void *arg4);
extern void bresenham_line_core(xyi_t b0, xyi_t b1, void (*func)(xyi_t,void*,void*,void*,void*), void *arg1, void *arg2, void *arg3, void *arg4);
