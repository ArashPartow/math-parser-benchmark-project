extern void draw_effect_noarg(enum dq_type type);
extern void draw_effect_arg_double(enum dq_type type, double v);
extern void draw_colour_matrix(double *matrix);

#define draw_clamp()			draw_effect_noarg(DQT_CLAMP)
#define draw_gain(v)			draw_effect_arg_double(DQT_GAIN, v)
#define draw_gain_parabolic(v)		draw_effect_arg_double(DQT_GAIN_PARAB, v)
#define draw_luma_compression(v)	draw_effect_arg_double(DQT_LUMA_COMPRESS, v)
#define draw_clip(v)			draw_effect_arg_double(DQT_CLIP, v)
