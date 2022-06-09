#include "cjkdec_enum.h"

extern void cjkdec_load_data(char *path, vector_font_t *font);
extern void cjkdec_load_data_from_struct(fileball_t *s, char *path, vector_font_t *font);
extern int is_cjkdec_glyph(vector_font_t *font, uint32_t c);
extern int draw_cjkdec_glyph(vector_font_t *font, uint32_t c, xy_t p, double scale, col_t colour, double line_thick, const int mode);
extern void make_cjkdec_vobj(vector_font_t *font, letter_t *l);

extern const char *cjkdec_type_name[];
