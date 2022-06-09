#include "drawqueue/drawqueue_enums.h"

extern void drawq_reinit();
extern void drawq_alloc();
extern void drawq_free();
extern void drawq_add_layer(uint32_t *dataint, const uint32_t layer_type);
extern void drawq_run();
extern int32_t drawq_entry_size(const enum dq_type type);
extern void *drawq_add_to_main_queue(const enum dq_type type);
extern void drawq_add_sector_id_nopending(int32_t sector_id);
extern void drawq_add_sector_id(int32_t sector_id);
extern void drawq_add_sectors_for_area(recti_t bb);
extern void drawq_add_sectors_for_already_set_sectors();
extern void drawq_compile_lists();
extern void drawq_test1();
extern int drawq_get_bounding_box(rect_t box, xy_t rad, recti_t *bbi);
extern int drawq_get_bounding_box_for_polygon(xy_t *p, int p_count, xy_t rad, recti_t *bbi);
extern void drawq_get_inner_box(rect_t box, xy_t rad, recti_t *bbi);
extern void drawq_remove_prev_entry_for_sector(int32_t sector_id, int bracket_search, xyi_t pix_coord);

extern void drawq_bracket_open();
extern void drawq_bracket_close(enum dq_blend blending_mode);
