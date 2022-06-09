extern xy_t interpolate_xy(xy_t a, xy_t b, double t);
extern xy_t triangle_find_incentre(triangle_t tr);
extern double triangle_find_incircle_radius(triangle_t tr);
extern triangle_t triangle_dilate(triangle_t tr, double d);
extern double polygon_signed_area(xy_t *p, int p_count);
extern double calc_sharp_polygon_pixel_weight(xy_t p, xy_t *corner, int corner_count);
