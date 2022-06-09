enum te_mode
{
	te_mode_value,
	te_mode_full,
};

typedef struct
{
	char *string;
	size_t alloc_size;
	int curpos;
	uint32_t timestamp;
} textundostate_t;

typedef struct
{
	textundostate_t *state;
	int alloc_count, state_count, cur_state_index, latest_is_saved;
	uint32_t timestamp;
} textundo_t;

typedef struct
{
	char *string;
	size_t alloc_size;
	int curpos, curpos_up, curpos_down, sel0, sel1;
	xy_t click;
	xy_t cur_screen_pos, cur_screen_pos_prev;
	int click_on;
	double max_scale, rect_brightness, scroll_mode_scale, scroll_mode_scale_def;
	textundo_t undo;
	enum te_mode edit_mode;
	int read_only, first_click_no_sel, return_flag, draw_string_mode, was_cur_te, tab_switch, sel_all, scroll_mode;
	xy_t scroll_pos;
	ctrl_drag_state_t vert_scroll, horiz_scroll;
	void *scaling_knob;
} textedit_t;
