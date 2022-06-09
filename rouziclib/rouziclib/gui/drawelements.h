extern void draw_titled_roundrect_frame(xy_t pos, double radius, xy_t c, xy_t space, lrgb_t colour, const blend_func_t bf);
extern void draw_label(const uint8_t *label, rect_t box, col_t colour, const int mode);
extern void draw_text_block(const uint8_t *label, rect_t box, col_t colour, const int mode, double thresh);
extern void draw_text_at_scale(const uint8_t *label, rect_t box, col_t colour, const int mode, double thresh);
extern void display_dialog_enclosing_frame(rect_t box_os, double scale, char *label, col_t colour);
extern void draw_unit_grid_level(xy_t offset, double sm, double scale, col_t colour);
extern void draw_unit_grid_col(xy_t offset, double sm, col_t colour);
extern void draw_unit_grid_decimal(xy_t offset, double sm, col_t colour);
extern void draw_rangebox(rect_t box, const char *label, col_t colour);

#define draw_unit_grid(offset, sm)	draw_unit_grid_col(offset, sm, make_grey(0.012))

#ifndef GUI_COL_DEF
#define GUI_COL_DEF	make_grey(0.25)
#endif
