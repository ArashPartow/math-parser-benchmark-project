// in gui/controls_struct.h:
// window_manager_entry_t, window_manager_t

extern int window_register(int priority, void *window_func, void *window_data, rect_t parent_area, int *wind_on, int num_args, ...);
extern void window_manager();
extern int window_find_id_by_func(void *window_func, void *window_data);
extern void window_set_parent(void *window_func, void *window_data, void *parent_window_func, void *parent_window_data);
extern void window_move_up(int id, int offset);
extern void window_move_to_top(void *window_func, void *window_data);
extern void window_set_parent_area(void *child_func, void *child_data, rect_t area);

extern _Thread_local rect_t cur_parent_area;
extern _Thread_local int *cur_wind_on;
extern _Thread_local void *cur_window_data;
