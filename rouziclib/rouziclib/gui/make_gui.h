enum
{
	gui_type_null,
	gui_type_none,
	gui_type_label,
	gui_type_rect,
	gui_type_button,
	gui_type_checkbox,
	gui_type_radio,
	gui_type_knob,
	gui_type_textedit,
	gui_type_selmenu,

	gui_type_count
};
// this enum must match the string array in make_gui.c
extern const char *layout_elem_type_name[];

typedef struct
{
	int type;
	xy_t pos, dim, pos_off;
	char *label;
	size_t label_as;
	col_t colour;
	void *data;
	ctrl_resize_rect_t resize_ctrl;
	int label_set, label_as_set, fmt_str_set, pos_val, dim_val;
	int implemented;
	int link_pos_id;
	xy_t link_pos_off;
	char link_pos_off_str[3];
} layout_elem_t;

typedef struct
{
	xy_t value;
	int set, y_set;
} layout_value_t;

typedef struct
{
	int init, edit_on, sel_id, cur_elem_id;
	size_t elem_as;
	layout_elem_t *elem;
	xy_t offset;
	double sm;

	layout_value_t *value;
	int value_as;
} gui_layout_t;

typedef struct
{
	char name[64];
	gui_layout_t *lp;
} layout_reg_entry_t;

typedef struct
{
	layout_reg_entry_t *reg;
	gui_layout_t *sel_p;
	int reg_as, reg_count, sel;
	int64_t last_reset_frame;
} layout_reg_t;

extern layout_reg_t layout_reg;

extern void free_layout_elem_data(layout_elem_t *elem);
extern void free_gui_layout(gui_layout_t *layout);
extern void gui_layout_duplicate_elem(gui_layout_t *layout, const int src_id, int dst_id);
extern void make_gui_layout(gui_layout_t *layout, const char **src, const int linecount, const char *layout_name);
extern void gui_layout_add_elem(gui_layout_t *layout, int *id, const char **src, const int linecount);
extern void sprint_gui_layout(gui_layout_t *layout, char **str, size_t *str_as);
extern void gui_layout_init_pos_scale(gui_layout_t *layout, xy_t pos, double scale, xy_t offset, int force);

extern int check_value_id_validity(gui_layout_t *layout, const int id, const int implemented);
extern xy_t *gui_layout_get_value_ptr(gui_layout_t *layout, const int id);
extern xy_t gui_layout_get_value(gui_layout_t *layout, const int id);
extern int check_elem_id_validity(gui_layout_t *layout, const int id, const int implemented);
extern xy_t *get_elem_posdim_ptr(gui_layout_t *layout, const int id, const int which);
extern xy_t get_elem_pos(gui_layout_t *layout, const int id);
extern xy_t get_elem_dim(gui_layout_t *layout, const int id);
extern xy_t gui_layout_get_link_pos(gui_layout_t *layout, const int id);
extern rect_t gui_layout_elem_comp_area(gui_layout_t *layout, const int id);
extern rect_t gui_layout_elem_comp_area_os(gui_layout_t *layout, const int id, const xy_t offset);
extern int ctrl_fromlayout_resizing(gui_layout_t *layout, const int id, const int phase);

extern void draw_label_fromlayout_in_rect(gui_layout_t *layout, const int id, const int mode, rect_t box_os);
extern void draw_label_fromlayout(gui_layout_t *layout, const int id, const int mode);
extern void draw_text_block_fromlayout_in_rect(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh, rect_t box_os);
extern void draw_text_block_fromlayout(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh);
extern void draw_text_at_scale_fromlayout_in_rect(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh, rect_t box_os);
extern void draw_text_at_scale_fromlayout(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh);
extern void draw_rect_fromlayout_blending(const int type, const blend_func_t bf, gui_layout_t *layout, const int id);
extern void draw_rect_fromlayout(const int type, gui_layout_t *layout, const int id);
extern int ctrl_button_fromlayout_offset(gui_layout_t *layout, const int id, const xy_t offset);
extern int ctrl_button_invis_fromlayout_offset(ctrl_button_state_t *butt_state_ptr, gui_layout_t *layout, const int id, const xy_t offset);

extern int ctrl_checkbox_fromlayout(int *state, gui_layout_t *layout, const int id);
extern int ctrl_radio_fromlayout_offset(int *state, gui_layout_t *layout, const int id, const int id_off, const xy_t offset);
extern int ctrl_knob_fromlayout(double *v, gui_layout_t *layout, const int id);
extern int ctrl_textedit_fromlayout_in_rect(gui_layout_t *layout, const int id, rect_t box_os);
extern int ctrl_textedit_fromlayout(gui_layout_t *layout, const int id);
extern void gui_layout_selmenu_set_count(const int count, gui_layout_t *layout, const int id);
extern void gui_layout_selmenu_set_open(const int state, gui_layout_t *layout, const int id);
extern void gui_layout_selmenu_set_entry_id(const int entry_id, gui_layout_t *layout, const int id);
extern int ctrl_selmenu_fromlayout(gui_layout_t *layout, const int id);
extern void draw_selmenu_entry_fromlayout(const int i, const char *label, gui_layout_t *layout, const int id);
extern char *gui_layout_make_code_for_unimp_elem(gui_layout_t *layout);
extern void gui_layout_unimplemented_elems(gui_layout_t *layout);
extern void gui_set_control_label(const char *new_label, gui_layout_t *layout, const int id);
extern void gui_set_control_colour(col_t colour, gui_layout_t *layout, const int id);
extern void gui_printf_to_label(gui_layout_t *layout, const int id, const int append, const char *format, ...);
extern void gui_round_elem_posdim(gui_layout_t *layout, const int id, const double rounding);
extern int print_to_layout_label(gui_layout_t *layout, const int id, const char *format, ...);
extern int print_to_layout_textedit(gui_layout_t *layout, const int id, const int clear_undo, const char *format, ...);
extern int print_to_layout_textedit_append(gui_layout_t *layout, const int id, const int clear_undo, const char *format, ...);
extern textedit_t *get_textedit_fromlayout(gui_layout_t *layout, const int id);
extern char *get_textedit_string_fromlayout(gui_layout_t *layout, const int id);
extern void set_cur_textedit_fromlayout(gui_layout_t *layout, const int id);
extern knob_t *get_knob_data_fromlayout(gui_layout_t *layout, const int id);
extern void set_knob_circularity_fromlayout(int circular, gui_layout_t *layout, const int id);
extern int get_selmenu_selid_fromlayout(gui_layout_t *layout, const int id);
extern void gui_layout_registry_add(gui_layout_t *layout, const char *layout_name);
extern void gui_layout_registry_reset();
extern rect_t fit_sublayout_into_area(rect_t area0, gui_layout_t *sublayout, int main_area_id, xy_t offset, int save_os);
extern rect_t fit_sublayout_into_layout_rect(gui_layout_t *toplayout, int rect_id, gui_layout_t *sublayout, int main_area_id, xy_t offset);
extern xy_t fit_area_into_layout_rect(gui_layout_t *layout, const int id, rect_t area1, xy_t offset, double *sm);
extern void gui_parse_knob_data_string(gui_layout_t *layout, const int id, const char *line, buffer_t *buferr);

#define ctrl_button_fromlayout(layout, id)	ctrl_button_fromlayout_offset(layout, id, XY0)
#define ctrl_button_invis_fromlayout(state, layout, id)	ctrl_button_invis_fromlayout_offset(state, layout, id, XY0)
#define ctrl_radio_fromlayout(state, layout, id)	ctrl_radio_fromlayout_offset(state, layout, id, 0, XY0)
#define draw_rect_fromlayout(type, layout, id)	draw_rect_fromlayout_blending(type, blend_add, layout, id)

/* Available commands for layout source

v <value ID>	<x y value>

elem		<array ID>
type		<name of type>
label		<label string>
label_alloc	<alloc size>

link_pos_id	<ID of the element to take an offset from>
pos		<x y position of area> | v<value ID>
dim		<x y dimensions of area> | v<value ID>
off		<x y position offset for area>

knob		<min> <default> <max> <function (linear|log|recip)> (<format string>)
knob_unit	<string to display below the number>
knob_arg	<arg0> (<arg1> <arg2> <arg3>)

TODO colour
*/
