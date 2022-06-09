enum		// custom unicode colours
{
	sc_start=0xE000,
	sc_white,
	sc_black,
	sc_red,
	sc_green,
	sc_blue,
	sc_baby_azure,
	sc_amber,
	sc_azure,
	sc_grey,

	sc_end
};

extern int draw_vector_char(vector_font_t *font, uint32_t c, xy_t p, xy_t off, double scale, col_t colour, double line_thick, const int mode, const int bidi);
extern int draw_vector_char_lookahead(vector_font_t *font, uint32_t c, const char *string, xy_t p, xy_t *off, double scale, col_t colour, double line_thick, const int mode, const int bidi);
extern void draw_string_full(vector_font_t *font, const char *string, xy_t p, xy_t off, double scale, col_t colour, double intensity, double line_thick, const int mode, int32_t len, double glyph_limit, double line_limit, const int bidi, const int recur, text_param_t *tp);
extern void draw_string_len(vector_font_t *font, const char *string, xy_t p, double scale, col_t colour, double intensity, double line_thick, const int mode, int32_t len, text_param_t *tp);
extern void draw_string(vector_font_t *font, const char *string, xy_t p, double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp);
extern void print_to_screen(xy_t pos, double scale, col_t colour, double intensity, const int32_t mode, const char *format, ...);

extern col_t text_sel_col;

//#define print_to_screen(pos, scale, colour, intensity, mode, format, ...)
