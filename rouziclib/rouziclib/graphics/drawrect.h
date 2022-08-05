extern void draw_rect_full_dq(rect_t box, double radius, frgb_t colour, double intensity);
extern void draw_black_rect_dq(rect_t box, double radius, double intensity);
extern void draw_black_rect_inverted_dq(rect_t box, double radius, double intensity);

extern void draw_rect_full(rect_t box, double radius, col_t colour, const blend_func_t bf, double intensity);
extern void draw_black_rect(rect_t box, double radius, double intensity);
extern void draw_black_rect_inverted(rect_t box, double radius, double intensity);
