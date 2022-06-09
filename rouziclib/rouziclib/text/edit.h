// in general/textedit_struct.h:
// textedit_t, enum te_mode

extern void textedit_init(textedit_t *te, const int alloc);
extern void textedit_free(textedit_t *te);
extern textedit_t string_to_textedit(char *string);
extern void textedit_erase_selection(textedit_t *te, int *len);
extern void textedit_copy_selection_clipboard(textedit_t *te);
extern int textedit_find_prev_linebreak(textedit_t *te);
extern int textedit_find_next_linebreak(textedit_t *te);
extern int textedit_find_prev_wordstart(textedit_t *te);
extern int textedit_find_next_wordstart(textedit_t *te);
extern int textedit_find_next_wordend(textedit_t *te);
extern void textedit_set_new_text(textedit_t *te, char *str);
extern void textedit_clear_then_set_new_text(textedit_t *te, char *str);
extern void textedit_add(textedit_t *te, char *str);
extern void textedit_prev_next_logic(textedit_t *te);
extern int ctrl_textedit(textedit_t *te, rect_t box, col_t colour);
extern void draw_textedit_cursor(xy_t offset, double scale, int bidi, int bidi_change, double drawing_thickness);

extern textedit_t *cur_textedit, *prev_textedit, *next_textedit;
