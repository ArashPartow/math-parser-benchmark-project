// in gui/inputprocessing_struct.h:
// ctrl_button_state_t, ctrl_knob_state_t, ctrl_drag_state_t, ctrl_id_t

extern int equal_ctrl_id(ctrl_id_t a, ctrl_id_t b);
extern int check_ctrl_id(rect_t box, xy_t pos, double radius, mouse_t mouse, int type);
extern void proc_mouse_ctrl_button(int mb, int clicks, ctrl_button_state_t *state, const int cur_point_within_box, const int orig_point_within_box);
extern ctrl_button_state_t *proc_mouse_rect_ctrl_lrmb(rect_t box, mouse_t mouse);
extern ctrl_button_state_t *proc_mouse_circ_ctrl_lrmb(xy_t pos, double radius, mouse_t mouse, const int check_bypass);
extern ctrl_knob_state_t proc_mouse_knob_ctrl(rect_t box, mouse_t mouse);
extern int proc_mouse_draggable_ctrl(ctrl_drag_state_t *state, rect_t box, mouse_t mouse);
extern int proc_mouse_xy_ctrl(rect_t box, mouse_t mouse, xy_t *pos, int *lmb, int *rmb);
extern ctrl_button_state_t proc_mouse_circular_ctrl(xy_t *pos, double radius, mouse_t mouse, int dragged);

#define proc_mouse_rect_ctrl(box, mouse)	proc_mouse_rect_ctrl_lrmb(box, mouse)[0]
#define check_ctrl_id_rect(box, mouse)	check_ctrl_id(box, XY0, 0., mouse, 0)
#define check_ctrl_id_circle(pos, radius, mouse)	check_ctrl_id(rect(XY0,XY0), pos, radius, mouse, 1)
