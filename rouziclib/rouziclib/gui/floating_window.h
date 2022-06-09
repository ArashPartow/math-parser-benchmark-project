// in gui/controls_struct.h:
// flwindow_t

extern void flwindow_init_defaults(flwindow_t *w);
extern void flwindow_init_pinned(flwindow_t *w);
extern void draw_dialog_window_fromlayout(flwindow_t *w, int *diag_on, rect_t *parent_area, gui_layout_t *layout, const int id);
