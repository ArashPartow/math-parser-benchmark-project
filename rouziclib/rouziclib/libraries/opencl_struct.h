#ifdef RL_OPENCL

#define clew_STATIC
#include "orig/clew.h"

#ifdef RL_OPENCL_GL
	#ifdef RL_BUILTIN_GLEW
		#define GLEW_STATIC
		#include "glew_minimal.h"
	#else
		#ifdef _MSC_VER
			#include <GL/glew.h>
		#endif
	#endif

	#ifdef _MSC_VER
		#pragma comment (lib, "opengl32.lib")

		#ifndef RL_BUILTIN_GLEW
			#pragma comment (lib, "glew32.lib")
		#endif
	#endif

	#ifdef __APPLE__
		#include <OpenCL/cl_gl.h>
		#include <OpenCL/cl_gl_ext.h>
	#endif
#endif

typedef struct
{
	cl_device_id	 device_id;
	cl_context	 context;
	cl_command_queue command_queue;
	cl_program	 program;
	cl_kernel	 kernel;
	cl_event	 ev;		// clEnqueueNDRangeKernel event
	cl_ulong queue_time, start_time, end_time;
} clctx_t;

#endif
