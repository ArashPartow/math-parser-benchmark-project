#ifdef RL_DEVIL

#ifdef _MSC_VER
#pragma comment (lib, "DevIL.lib")
#pragma comment (lib, "ILU.lib")
#pragma comment (lib, "ILUT.lib")
#endif

#include <IL/il.h>
#include <IL/ilu.h>

extern raster_t load_image_mem_libdevil(ILubyte *raw_data, ILuint size, const int mode);

#ifndef load_image_mem
#define load_image_mem	load_image_mem_libdevil

#define load_image_libdevil(path, mode)	load_image_lib(load_image_mem_libdevil, path, mode)
#endif

#endif
