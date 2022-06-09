#ifdef RL_FFMPEG

typedef struct
{
	AVFormatContext *fmt_ctx;
	AVCodecContext *codec_ctx;	// a shortcut to st->codec
	AVStream *st;
	AVFrame *frame;
	int pts;
	uint16_t *s16_buf;
} ff_videnc_t;

extern ff_videnc_t ff_video_enc_init_file(const char *path, xyi_t dim, double fps, int codec_id, int bit_depth, int crf);
extern void ff_convert_to_frame(void *buf, int buf_fmt, int bpp, AVFrame *frame);
extern int ff_frgb_to_frame(ff_videnc_t *d, raster_t *r);
extern int ff_yuv_to_frame(ff_videnc_t *d, raster_t *r);
extern int ff_video_enc_write_raster(ff_videnc_t *d, raster_t *r);
extern int ff_video_enc_write_frame(ff_videnc_t *d, AVFrame *frame);
extern void ff_video_enc_finalise_file(ff_videnc_t *d);

#endif
