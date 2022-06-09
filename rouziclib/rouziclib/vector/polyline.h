typedef struct
{
	xy_t *pv;
	xyi_t *line;
	ctrl_drag_state_t *ds;
	int pv_count, pv_alloc;
	int line_count, line_alloc;
} polyline_edit_t;

extern int ctrl_polyline(polyline_edit_t *pl, rect_t box, xy_t offset, double sm);
extern void free_polyline(polyline_edit_t *pl);
extern char *sprint_polyline(polyline_edit_t *pl);
extern void round_polyline_pv(polyline_edit_t *pl, xy_t offset, double sm);
