typedef double (*knob_func_t)(double, double, double, double *, const int);

typedef struct
{
	char *main_label, *fmt_str, *unit_label;
	knob_func_t func;
	double min, max, default_value, arg[4];
	textedit_t edit;
	int edit_open, circular, arg_count;
} knob_t;

typedef struct
{
	int init, pinned, hide_corner, hide_pin, draw_bg_always;
	ctrl_drag_state_t bar_drag, corner_drag;
	col_t bg_col, bar_col, border_col, close_hover_col, close_down_col, title_col, close_x_col;
	double bar_height, shadow_strength, bg_opacity;
	xy_t pinned_offset, pinned_offset_preset, parent_fit_offset;
	double pinned_sm, pinned_sm_preset;
} flwindow_t;

typedef struct
{
	int *wind_on, dereg, order, already_ran, newly_registered;
	void *window_func, *parent_window_func;
	void *window_data, *parent_window_data;
	void **ptr_array;
	int ptr_count;
	rect_t parent_area;
} window_manager_entry_t;

typedef struct
{
	window_manager_entry_t *window, **wsor;
	int window_count, window_as, wsor_as;
	int min_order, max_order;
	int manager_is_calling;
} window_manager_t;
