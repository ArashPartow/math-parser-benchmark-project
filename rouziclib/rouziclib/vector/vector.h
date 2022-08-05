// in vector/vector_struct.h:
// seg_t, vobj_t

#define NOC -98765.4321e30	// no coordinate provided

extern vobj_t *alloc_vobj(int32_t count);
extern void free_vobj(vobj_t *o);
extern void join_vobj(vobj_t *o);
extern vobj_t *make_vobj(int32_t count, double scale, xy_t c);
extern vobj_t *duplicate_vobj(vobj_t *o1);
extern vobj_t *cat_vobj(vobj_t *o1, vobj_t *o2, int32_t dofree);
extern vobj_t *scale_vobj(vobj_t *o, xyz_t scale);
extern seg_t seg_make_xy(xy_t p1, xy_t p2, double m);
extern seg_t seg_make_xyz(xyz_t p1, xyz_t p2, double m);
extern seg_t rot_seg(seg_t seg, double scale, double th);
extern void rot_vobj(vobj_t *o, double x, double y, double scale, double angle);
extern rect_t vobj_bounding_rect(vobj_t *o);
extern void draw_vobj_fullarg(vobj_t *o, xy_t p, xy_t scale, double angle, double line_thick, col_t colour);
extern void draw_vobj_fullarg_dq(vobj_t *o, xy_t p, xy_t scale, double angle, double line_thick, frgb_t colour);
extern void draw_vobj_dqnq(vobj_t *o, xy_t pos, double scale, double angle, double line_thick, col_t colour);
extern xy_t *vobj_to_map(vobj_t *o, int32_t dofree);
extern vobj_t *map_to_vobj(xy_t *map, int32_t mapsize, int32_t dofree);

#define draw_vobj(o, p, scale, angle, line_thick, colour)	draw_vobj_fullarg(o, p, set_xy(scale), angle, line_thick, colour)
