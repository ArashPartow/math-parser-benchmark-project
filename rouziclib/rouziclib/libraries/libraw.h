#ifdef RL_LIBRAW

#ifdef _MSC_VER
#pragma comment (lib, "libraw.lib")
#endif

#ifdef _WIN32
 #ifndef WIN32
  #define WIN32
  #define TODO_UNDEF_WIN32
 #endif
#endif

#include "libraw/libraw.h"

#ifdef TODO_UNDEF_WIN32
 #undef WIN32
 #undef TODO_UNDEF_WIN32
#endif

typedef struct
{
	uint16_t *data;
	xyi_t dim;
	xyz_t wb;
	double bayer_black[4];
	double maximum_value;
	double inv_matrix[9];
	rect_t image_area;
	xy_t image_centre;
	raster_t preview;
} rawphoto_t;

extern rawphoto_t init_rawphoto(int32_t width, int32_t height);
extern void free_rawphoto(rawphoto_t *rp);
extern raster_t load_raw_thumb(libraw_data_t *rd);
extern rawphoto_t load_raw_photo_bayered(char *path, int load_thumb);
extern raster_t raw_photo_to_raster(rawphoto_t rp);
extern raster_t load_raw_photo_dcraw_proc(char *path);

#endif
