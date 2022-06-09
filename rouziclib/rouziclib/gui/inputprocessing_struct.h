typedef struct
{
	int over, down, once, uponce, doubleclick, orig, out_of_screen, too_small;
} ctrl_button_state_t;

typedef struct
{
	double vert_delta;
	int down, downonce, uponce, doubleclick, rightclick;
} ctrl_knob_state_t;

typedef struct
{
	xy_t pos, dim, offset, freedom, click_offset;
	int down, over, uponce;
} ctrl_drag_state_t;

typedef struct
{
	int open, next_open, sel_id, hover_id, count;
} ctrl_selectmenu_state_t;

typedef struct
{
	int type;	// 0 for obstructing rect, 1 for nearest-centre circle
	int id;		// identifies different controls with the same box
	rect_t box;	// rect coordinates that define the control
	xy_t pos;	// position of the type 1 circle
	double radius;	// radius of the type 1 circle
} ctrl_id_t;

typedef struct
{
	int init, dragged, prev_dragged;
	ctrl_drag_state_t drag[9];
} ctrl_resize_rect_t;
