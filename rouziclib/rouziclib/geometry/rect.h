// in geometry/rect_struct.h:
// rect_t, recti_t, rectq_t, triangle_t

#define RECT0	rect(XY0,XY0)
#define RECTNAN	rect(XYNAN,XYNAN)

extern rect_t rect(const xy_t p0, const xy_t p1);
extern recti_t recti(const xyi_t p0, const xyi_t p1);
extern rectq_t rectq(const xyq_t p0, const xyq_t p1);
extern triangle_t triangle(const xy_t a, const xy_t b, const xy_t c);
extern recti_t rect_to_recti(const rect_t r);
extern recti_t rect_to_recti_round(const rect_t r);
extern rect_t recti_to_rect(const recti_t ri);
extern recti_t rect_to_recti_fixedpoint(const rect_t r, const double fpratio);
extern xy_t rect_p01(rect_t r);
extern xy_t rect_p10(rect_t r);
extern xyi_t recti_p01(recti_t r);
extern xyi_t recti_p10(recti_t r);
extern void rect_set_p01(rect_t *r, xy_t c);
extern void rect_set_p10(rect_t *r, xy_t c);
extern rect_t mul_rect(rect_t r, xy_t m);
extern recti_t rshift_recti(recti_t r, int sh);
extern rect_t make_rect_centred(const xy_t c, const xy_t wh);
extern rect_t make_rect_off(const xy_t pos, const xy_t dim, const xy_t off);
extern recti_t make_recti_off(const xyi_t pos, const xyi_t dim, const xyi_t off);
extern void rect_to_pos_dim(rect_t r, xy_t *pos, xy_t *dim, xy_t off);
extern xy_t get_rect_centre(rect_t r);
extern xyi_t get_recti_centre(recti_t r);
extern xy_t get_rect_dim(rect_t r);
extern xyi_t get_recti_dim(recti_t r);
extern double get_rect_area(rect_t r);
extern rect_t get_rect_centred_coord(rect_t r);
extern recti_t get_recti_centred_coord(recti_t r);
extern rect_t rect_size_mul(rect_t r, xy_t scale);
extern rect_t rect_add_margin(rect_t r, xy_t margin);
extern recti_t recti_add_margin(recti_t r, xyi_t margin);
extern rect_t rect_add_margin_offset(rect_t r, xy_t margin, xy_t offset);
extern rect_t rect_move(rect_t r, xy_t v);
extern rect_t rect_neg_y(rect_t r);
extern rect_t make_rect_ulcorner(xy_t ulc, xy_t wh);
extern rect_t make_rect_urcorner(xy_t ulc, xy_t wh);
extern double rect_min_side(rect_t r);
extern double rect_max_side(rect_t r);
extern double rect_height_width_ratio(rect_t r);
extern rect_t sort_rect(rect_t r);
extern recti_t sort_recti(recti_t r);
extern rect_t add_rect_xy(rect_t r, xy_t a);
extern int equal_rect(rect_t r1, rect_t r2);
extern int isnan_rect(rect_t r);
extern int is0_rect(const rect_t r);
extern xy_t pos_in_rect_by_ratio(rect_t r, xy_t ratio);
extern xy_t pos_to_rect_ratio(xy_t pos, rect_t r);
extern rect_t resize_rect_around_offset(rect_t r, xy_t dim1, xy_t offset);
extern rect_t rect_boolean_intersection(rect_t a, rect_t b);
extern recti_t recti_boolean_intersection(recti_t a, recti_t b);
extern void rect_range_and_dim_to_scale_offset(rect_t range, xyi_t dim, xy_t *r_scale, xy_t *r_offset, int range_edge_is_pix_centre);
extern void rect_range_and_dim_to_scale_offset_inv(rect_t range, xyi_t dim, xy_t *r_scale, xy_t *r_offset, int range_edge_is_pix_centre);
