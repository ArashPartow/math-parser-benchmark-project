// key names at https://wiki.libsdl.org/SDL_Keycode

extern int get_scancode_by_key_name(const char *name);
extern int get_key_state_by_name(const char *name);
extern int get_kb_shift();
extern int get_kb_ctrl();
extern int get_kb_guikey();
extern int get_kb_alt();
extern int get_kb_enter();
extern int get_kb_all_mods();
extern void keyboard_pre_event_proc(mouse_t *mouse);
extern void keyboard_button_event(int *b, int *quick_b, int way, int repeat);

#ifdef __APPLE__
#define get_kb_cmd	get_kb_guikey
#else
#define get_kb_cmd	get_kb_ctrl
#endif
