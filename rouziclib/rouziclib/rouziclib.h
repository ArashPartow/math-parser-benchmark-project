/* Make a .h file in your project containing an include to this file and 
 * add the optional defines you like in it, like this:

#ifndef H_PRL
#define H_PRL
#ifdef __cplusplus
extern "C" {
#endif

#define LBD	12
#define GAUSSLIMIT 0.0002
#define RL_LIBCURL

#include <rouziclib/rouziclib.h>

#ifdef __cplusplus
}
#endif
#endif


 * with MinGW's GCC make sure to use -lwinmm -lcomdlg32 -lole32 -Wno-incompatible-pointer-types (the latter to turn off pointless warnings), and perhaps -DRL_STOREU_SI32 too
 * with Clang remove -DRL_STOREU_SI32 and add -Wno-dangling-else -Wno-parentheses -Wno-pointer-sign -Wno-shift-op-parentheses
 * create a hard link like `mklink /J C:\<usual libs location>\include\rouziclib C:\msys\home\rouziclib` to include using <>

****************/

#ifndef H_ROUZICLIB
#define H_ROUZICLIB
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#include "general/windows_includes.h"

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;	// Visual Studio lacks ssize_t
#endif

#define assert(x)	((void)0)	// this suppresses assert() used by some of the libs below

// Structs and includes needed elsewhere
#include "general/intrinsics.h"
#include "general/threading.h"
#include "general/structs.h"
#include "general/xyz_struct.h"
#include "geometry/rect_struct.h"		// needs xyz
#include "gui/inputprocessing_struct.h"		// needs xyz, rect
#include "general/textedit_struct.h"		// needs xyz, inputprocessing
#include "fileio/dir_struct.h"
#include "gui/focus_struct.h"
#include "libraries/opencl_struct.h"		// used if RL_OPENCL is defined
#include "libraries/vulkan_struct.h"		// used if RL_VULKAN is defined

#include "graphics/graphics_struct.h"		// needs xyz, opencl, vulkan
#include "graphics/blending_struct.h"		// needs graphics
#include "gui/controls_struct.h"		// needs textedit, inputprocessing, graphics
#include "general/keyboard_struct.h"
#include "general/mouse_struct.h"		// needs rect, xyz, controls, keyboard
#include "gui/zoom_struct.h"			// needs rect, xyz, mouse, graphics
#include "vector/vector_struct.h"		// needs xyz
#include "vector_type/vector_type_struct.h"	// needs vector
#include "fileio/fileball_struct.h"
#include "libraries/mpfr.h"			// used if RL_MPFR is defined

#include "general/macros.h"
#include "general/xyz.h"
#include "general/time.h"
#include "general/estimates.h"
#include "general/mouse.h"
#include "general/keyboard.h"
#include "general/hashing.h"
#include "general/crash_dump.h"			// used if RL_CRASHDUMP is defined
#include "general/audio.h"

#include "memory/alloc.h"
#include "memory/fill.h"
#include "memory/swap.h"
#include "memory/circular_buffer.h"
#include "memory/generic_buffer.h"
#include "memory/comparison.h"

#include "geometry/rect.h"
#include "geometry/intersection.h"
#include "geometry/rotation.h"
#include "geometry/fit.h"
#include "geometry/distance.h"
#include "geometry/bezier.h"
#include "geometry/misc.h"
#include "math/functions.h"
#include "math/ieee754.h"
#include "math/double_double_arithmetic.h"
#include "math/rand.h"
#include "math/dsp.h"
#include "math/dct.h"
#include "math/matrix.h"
#include "math/physics.h"
#include "math/debug.h"
#include "math/polynomials.h"
#include "math/polynomials_mpfr.h"		// used if RL_MPFR is defined
#include "approximations/fixed_point.h"		// unused if RL_EXCL_APPROX is defined
#include "approximations/fast_float.h"		// unused if RL_EXCL_APPROX is defined
#include "approximations/fast_cos.h"		// unused if RL_EXCL_APPROX is defined
#include "approximations/high_prec.h"
#include "approximations/simd.h"		// unused if RL_EXCL_APPROX is defined

#include "graphics/graphics.h"
#include "graphics/pixel_conv.h"
#include "graphics/srgb.h"
#include "graphics/sqrgb.h"
#include "graphics/yuv.h"
#include "graphics/colour.h"
#include "graphics/blending.h"
#include "graphics/flattop_interpolation.h"
#include "graphics/blit.h"
#include "graphics/drawline.h"
#include "graphics/drawrect.h"
#include "graphics/drawprimitives.h"
#include "graphics/drawqueue.h"
#include "graphics/drawqueue_enqueue.h"
#include "graphics/drawqueue/drawqueue_soft.h"
#include "graphics/drawqueue/drawrect.h"
#include "graphics/drawqueue/drawline.h"
#include "graphics/drawqueue/blit.h"
#include "graphics/draw_effects.h"
#include "graphics/processing.h"
#include "graphics/mipmap.h"
#include "graphics/cl_memory.h"
#include "graphics/texture_compression.h"
#include "vector/vector.h"
#include "vector/polyline.h"

#include "text/unicode_data.h"			// needs RL_INCL_UNICODE_DATA(_MINI) to be defined
#include "text/unicode.h"
#include "text/unicode_bidi.h"
#include "text/unicode_arabic.h"
#include "text/parse.h"
#include "text/format.h"
#include "text/string.h"
#include "text/edit.h"
#include "text/undo.h"
#include "text/history.h"
#include "vector_type/vector_type.h"		// vector type fileball loading needs RL_INCL_VECTOR_TYPE_FILEBALL
#include "vector_type/make_font.h"
#include "vector_type/draw.h"
#include "vector_type/stats.h"
#include "vector_type/fit.h"
#include "vector_type/cjk.h"
#include "vector_type/insert_rect.h"

#include "gui/zoom.h"
#include "gui/focus.h"
#include "gui/positioning.h"
#include "gui/layout.h"
#include "gui/drawelements.h"
#include "gui/visualisations.h"
#include "gui/inputprocessing.h"
#include "gui/knob_functions.h"
#include "gui/controls.h"
#include "gui/control_array.h"
#include "gui/selection.h"
#include "gui/make_gui.h"
#include "gui/editor_toolbar.h"
#include "gui/floating_window.h"
#include "gui/window_manager.h"

#include "fileio/bits.h"
#include "fileio/open.h"
#include "fileio/endian.h"
#include "fileio/image.h"
#include "fileio/image_bmp.h"
#include "fileio/image_tiff.h"
#include "fileio/image_tiff_lzw.h"
#include "fileio/image_fts.h"
#include "fileio/image_screen.h"	// works if RL_GDI32 is defined on Windows
#include "fileio/sound_format.h"
#include "fileio/sound_aiff.h"
#include "fileio/sound_wav.h"
#include "fileio/path.h"
#include "fileio/dir.h"
#include "fileio/file_management.h"
#include "fileio/process.h"
#include "fileio/fileball.h"
#include "fileio/prefs.h"
#include "fileio/dialog.h"

#include "interpreter/interpreter.h"
#include "interpreter/compilation.h"
#include "interpreter/execution.h"
#include "interpreter/decompilation.h"
#include "interpreter/real_functions.h"
#include "interpreter/expression.h"

#include "libraries/opencl.h"		// used if RL_OPENCL is defined
#include "libraries/sdl.h"		// used if RL_SDL is defined
#include "libraries/vulkan.h"		// used if RL_VULKAN is defined
#include "libraries/clfft.h"		// used if RL_CLFFT is defined
#include "libraries/ffmpeg.h"		// used if RL_FFMPEG is defined
#include "libraries/ffmpeg_enc.h"	// used if RL_FFMPEG is defined
#include "fileio/ffmpeg_sound_player.h"	// used if RL_FFMPEG is defined
#include "libraries/opencv.h"		// used if RL_OPENCV is defined
#include "libraries/devil.h"		// used if RL_DEVIL is defined
#include "libraries/libsndfile.h"	// used if RL_LIBSNDFILE is defined
#include "libraries/libraw.h"		// used if RL_LIBRAW is defined
#include "libraries/libjpeg.h"		// used if RL_LIBJPEG is defined
#include "libraries/libstb_image.h"
#include "libraries/libstb_vorbis.h"
#include "libraries/libminimp3.h"
#include "libraries/libdr_flac.h"
#include "libraries/zlib.h"		// uses zlib if RL_ZLIB is defined, otherwise miniz is used
#include "libraries/fftpack.h"		// used unless RL_EXCL_FFTPACK is defined
#include "libraries/cfftpack.h"		// used unless RL_EXCL_CFFTPACK is defined
#include "libraries/tinyexpr.h"
#include "libraries/libcurl.h"		// used if RL_LIBCURL is defined
#include "libraries/libminiaudio.h"	// used if RL_MINIAUDIO is defined
#include "libraries/openal.h"		// used if RL_OPENAL is defined
#include "libraries/emscripten.h"

#include "general/noop.h"
#include "general/globals.h"


#ifdef __cplusplus
}
#endif
#endif
