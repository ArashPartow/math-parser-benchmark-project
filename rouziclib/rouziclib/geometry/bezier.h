typedef struct
{
	xy_t p0, p1, p2, p3;
} bezier_seg_t;

extern int xy_array_to_bezier_seg_array(xy_t *pa, int p_count, bezier_seg_t **bap, size_t *ba_as);
extern void bezier_seg_array_flatten_slopes(bezier_seg_t *ba, int b_count);
extern double bezier_seg_x_to_t(bezier_seg_t seg, double x);
extern int cmp_bezier_seg_by_x(const bezier_seg_t *a, const bezier_seg_t *b);
extern double bezier_seg_array_eval_x(bezier_seg_t *ba, int b_count, double x);
