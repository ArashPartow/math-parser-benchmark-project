#ifdef RL_FFMPEG

#ifdef _MSC_VER
#pragma comment (lib, "avcodec.lib")
#pragma comment (lib, "avformat.lib")
//#pragma comment (lib, "swscale.lib")
#pragma comment (lib, "avutil.lib")
#endif

#ifndef inline
#define inline	__inline
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
#include <libavutil/avutil.h>

typedef struct
{
	int64_t pkt_pos, pts;
	double ts, ts_end;
	int key_frame;
} ffframe_info_t;

typedef struct
{
	AVFormatContext *fmt_ctx;
	AVCodecContext *codec_ctx;
	AVCodec *codec;
	AVFrame *frame;
	int stream_id;

	ffframe_info_t *frame_info;
	int frame_count, frame_as;

	volatile int64_t byte_pos;
} ffstream_t;

extern int ff_init_stream(ffstream_t *s, const int stream_type);
extern ffstream_t ff_load_stream_init(char const *path, const int stream_type);
extern int ff_load_stream_packet(ffstream_t *s);
extern void ffstream_close_free(ffstream_t *s);
extern double ff_get_timestamp(ffstream_t *s, int64_t timestamp);
extern double ff_get_frame_timestamp(ffstream_t *s);
extern int64_t ff_make_timestamp(ffstream_t *s, double t);
extern raster_t ff_frame_to_raster(ffstream_t *s, const int mode);
extern int ff_pix_fmt_byte_count(int pix_fmt);
extern int ff_pix_fmt_bit_depth(int pix_fmt);
extern int ff_pix_fmt_to_buf_fmt(int pix_fmt);
extern int ff_buf_fmt_to_pix_fmt(int buf_fmt);
extern raster_t ff_frame_to_buffer(ffstream_t *s);
extern void ff_seek_timestamp(ffstream_t *s, double ts, int64_t pts, int flush);
extern void ff_seek_byte(ffstream_t *s, int64_t pos, int flush);
extern int ff_find_table_frame_id(ffstream_t *s, double t, const int keyframe);
extern int ff_decode_frame_from_table(ffstream_t *s, double t);
extern int ff_find_keyframe_for_time(ffstream_t *s, const double t);
extern int ff_find_frame_at_time(ffstream_t *s, const double t);
extern ffframe_info_t ff_make_frame_info(ffstream_t *s);
extern void ff_make_frame_table(ffstream_t *s);
extern double ff_get_stream_duration(ffstream_t *s, const char *path, int stream_type);
extern double ff_get_video_duration(ffstream_t *s, const char *path);
extern double ff_get_audio_duration(ffstream_t *s, const char *path);
extern raster_t ff_load_video_raster(ffstream_t *s, const char *path, const int seek_mode, const double t, const int raster_mode);

extern int ff_load_audio_fl32(ffstream_t *s, const char *path, const int seek_mode, const double t, float **bufp, size_t *buf_as, size_t *buf_pos);
extern float *ff_load_audio_fl32_full(const char *path, size_t *sample_count, int *channels, int *samplerate);

#define ff_load_video_next_raster(s, path, mode)	ff_load_video_raster(s, path, 0, 0., mode)
#define ff_load_video_still(s, path, t, mode)	ff_load_video_raster(s, path, 1, t, mode)

#endif
