#ifdef RL_OPENCV

#ifdef _MSC_VER
#pragma comment (lib, "opencv_world340.lib") 
#endif

#define CV_IGNORE_DEBUG_BUILD_GUARD

//#include <opencv/cv.h>
#include <opencv2/videoio/videoio_c.h>

extern void convert_cvimage_to_raster(IplImage *frame, raster_t *image, const int mode);
extern void convert_srgb_to_cvimage(raster_t *image, IplImage *frame);
extern int get_webcam_frame(raster_t *image, char *debug_str, const int mode);
extern int get_video_frame(raster_t *image, char *path, const int mode);
extern void write_video_frame(raster_t *image, char *path, double fps, int action);

#endif
