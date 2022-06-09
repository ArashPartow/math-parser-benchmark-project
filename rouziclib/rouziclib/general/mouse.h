// in general/mouse_struct.h:
// mouse_ctrl_id_t, mousebut_t, mouse_t

extern mouse_t init_mouse();
extern void mouse_pre_event_proc(mouse_t *mouse);
extern void mouse_button_event(int *mb, mousebut_flags_t *flags, int way);
extern void mouse_button_update(int *mb, mousebut_flags_t *flags, int new_state, int button_index, mouse_t *mouse);
extern void mouse_post_event_proc(mouse_t *mouse, zoom_t *zc);
extern void mousecursor_logic_and_draw();

/*	#ifdef MOUSE_LOG
	bufprintf(&mouse.log, "[%d] \n", mouse.frame_index);
	#endif*/
