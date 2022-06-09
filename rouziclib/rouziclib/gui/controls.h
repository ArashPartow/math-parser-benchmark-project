// in gui/controls_struct.h:
// knob_t

// in gui/inputprocessing_struct.h
// ctrl_button_state_t, ctrl_knob_state_t, ctrl_drag_state_t, ctrl_selectmenu_state_t, ctrl_id_t, ctrl_resize_rect_t

extern int ctrl_button_invis(rect_t box, ctrl_button_state_t *butt_state_ptr);
extern int ctrl_button_chamf(const uint8_t *name, rect_t box, col_t colour);
extern ctrl_button_state_t ctrl_button_chamf_state(const uint8_t *name, rect_t box, col_t colour);
extern int ctrl_checkbox(int *state, const uint8_t *name, rect_t box, col_t colour);
extern ctrl_button_state_t ctrl_checkbox_pin(int *state, rect_t box, col_t colour);
extern int ctrl_radio(int state, const uint8_t *name, rect_t box, col_t colour);
extern knob_t make_knob(char *main_label, double default_value, const knob_func_t func, double min, double max, char *fmt_str);
extern rect_t selectmenu_rect(rect_t box, const int id);
extern int ctrl_selectmenu(ctrl_selectmenu_state_t *state, rect_t box, col_t colour);
extern void draw_selectmenu_entry(ctrl_selectmenu_state_t *state, rect_t box, col_t colour, int id, const char *label);
extern int ctrl_knob(double *v_orig, knob_t *knob, rect_t box, col_t colour);
extern ctrl_drag_state_t make_drag_state(xy_t pos, xy_t freedom);
extern void ctrl_drag_set_dim(ctrl_drag_state_t *state, xy_t dim1);
extern int ctrl_draggable(ctrl_drag_state_t *state);
extern int ctrl_draggable_circle_invis(xy_t *pos, double radius, int *sel_id, int cur_id, int *dragged, ctrl_button_state_t *butt_state_ptr);
extern int ctrl_draggable_circle(xy_t *pos, double radius, int *sel_id, int cur_id, int *dragged, col_t colour);
extern void update_ctrl_resizing_rect_positions(ctrl_resize_rect_t *state, rect_t box);
extern int ctrl_resizing_rect(ctrl_resize_rect_t *data, rect_t *box);
