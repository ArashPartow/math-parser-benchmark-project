extern double find_line_for_thresh(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, double thresh, int iw_start, int *iw_end);
extern int find_line_count_for_thresh(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, double thresh, double *maxwidth);
extern int search_thresh(vector_font_t *font, search_thresh_t *st, double maxwidth, int nlines, double prec);
extern double find_string_width_for_nlines(vector_font_t *font, const uint8_t *string, word_stats_t ws, int *nlines, const int mode, double *lower_bound);
extern double find_best_string_width(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, xy_t boxdim, int *nlines, double *scale_ratio);
extern void draw_string_maxwidth(vector_font_t *font, const uint8_t *string, word_stats_t ws, rect_t box, double scale, col_t colour, double intensity, double line_thick, const int mode, double maxwidth, int nlines, text_param_t *tp);
extern void draw_string_bestfit(vector_font_t *font, const uint8_t *string, rect_t box, const double border, double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp);
extern double draw_string_bestfit_asis(vector_font_t *font, const uint8_t *string, rect_t box, double border, const double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp);
extern void draw_string_fixed_thresh(vector_font_t *font, const uint8_t *string, rect_t box, const double thresh, double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp);
