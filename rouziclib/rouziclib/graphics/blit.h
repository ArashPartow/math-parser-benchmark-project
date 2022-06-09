enum
{	// alignments
	A_CEN,
	A_LEF,
	A_RIG,
	A_TOP,
	A_BOT,
};

enum
{	// interpolation and filtering modes
	NO_FILTER,
	LINEAR_FILTER,

	NEAREST_INTERP,
	AA_NEAREST_INTERP,
	LINEAR_INTERP,
	GAUSSIAN_INTERP,
};

extern int sprite_offsets_old(int32_t fbw, int32_t fbh, int32_t spw, int32_t sph, int32_t *pos_x, int32_t *pos_y, int32_t *offset_x, int32_t *offset_y, int32_t *start_x, int32_t *start_y, int32_t *stop_x, int32_t *stop_y, int hmode, int vmode);
extern int sprite_offsets(raster_t r, xyi_t *pos, xyi_t *offset, xyi_t *start, xyi_t *stop, int hmode, int vmode);
extern int calc_blit_bounds(xyi_t in_dim, xyi_t out_dim, xyi_t offset, recti_t *bounds);
extern void blit_sprite(raster_t r, xyi_t pos, const blend_func_t bf, int hmode, int vmode);
extern void blit_layout(raster_t r);
extern void blit_scale_lrgb(raster_t r, xy_t pscale, xy_t pos, int interp);
extern void blit_scale_frgb(raster_t r, xy_t pscale, xy_t pos, int interp);
extern void blit_scale_dq(raster_t *r, xy_t pscale, xy_t pos, int interp);
extern void blit_scale(raster_t *r, xy_t pscale, xy_t pos, int interp);
extern void blit_scale_rotated(raster_t *r, xy_t pscale, xy_t pos, double angle, xy_t rot_centre, int interp);
extern rect_t blit_in_rect_rotated(raster_t *raster, rect_t r, int keep_aspect_ratio, double angle, xy_t rot_centre, int interp);

#define blit_in_rect(raster, r, keep_aspect_ratio, interp)	blit_in_rect_rotated(raster, r, keep_aspect_ratio, 0., XY0, interp)
