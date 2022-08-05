#ifdef RL_OPENCL

#include "orig/clew.c"

#ifdef RL_OPENCL_GL
#ifdef RL_BUILTIN_GLEW
#include "glew_minimal.c"
#endif
#endif

const char *get_cl_error_string(cl_int err)
{
	switch (err)
	{
		case 0: return "CL_SUCCESS";
		case -1: return "CL_DEVICE_NOT_FOUND";
		case -2: return "CL_DEVICE_NOT_AVAILABLE";
		case -3: return "CL_COMPILER_NOT_AVAILABLE";
		case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case -5: return "CL_OUT_OF_RESOURCES";
		case -6: return "CL_OUT_OF_HOST_MEMORY";
		case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case -8: return "CL_MEM_COPY_OVERLAP";
		case -9: return "CL_IMAGE_FORMAT_MISMATCH";
		case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case -11: return "CL_BUILD_PROGRAM_FAILURE";
		case -12: return "CL_MAP_FAILURE";
		case -13: return "CL_MISALIGNED_SUB";
		case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case -15: return "CL_COMPILE_PROGRAM";
		case -16: return "CL_LINKER_NOT_AVAILABLE";
		case -17: return "CL_LINK_PROGRAM_FAILURE";
		case -18: return "CL_DEVICE_PARTITION_FAILED";
		case -19: return "CL_MAP_FAILURE";

		case -30: return "CL_INVALID_VALUE";
		case -31: return "CL_INVALID_DEVICE_TYPE";
		case -32: return "CL_INVALID_PLATFORM";
		case -33: return "CL_INVALID_DEVICE";
		case -34: return "CL_INVALID_CONTEXT";
		case -35: return "CL_INVALID_QUEUE_PROPERTIES";
		case -36: return "CL_INVALID_COMMAND_QUEUE";
		case -37: return "CL_INVALID_HOST_PTR";
		case -38: return "CL_INVALID_MEM_OBJECT";
		case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case -40: return "CL_INVALID_IMAGE_SIZE";
		case -41: return "CL_INVALID_SAMPLER";
		case -42: return "CL_INVALID_BINARY";
		case -43: return "CL_INVALID_BUILD_OPTIONS";
		case -44: return "CL_INVALID_PROGRAM";
		case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
		case -46: return "CL_INVALID_KERNEL_NAME";
		case -47: return "CL_INVALID_KERNEL_DEFINITION";
		case -48: return "CL_INVALID_KERNEL";
		case -49: return "CL_INVALID_ARG_INDEX";
		case -50: return "CL_INVALID_ARG_VALUE";
		case -51: return "CL_INVALID_ARG_SIZE";
		case -52: return "CL_INVALID_KERNEL_ARGS";
		case -53: return "CL_INVALID_WORK_DIMENSION";
		case -54: return "CL_INVALID_WORK_GROUP_SIZE";
		case -55: return "CL_INVALID_WORK_ITEM_SIZE";
		case -56: return "CL_INVALID_GLOBAL_OFFSET";
		case -57: return "CL_INVALID_EVENT_WAIT_LIST";
		case -58: return "CL_INVALID_EVENT";
		case -59: return "CL_INVALID_OPERATION";
		case -60: return "CL_INVALID_GL_OBJECT";
		case -61: return "CL_INVALID_BUFFER_SIZE";
		case -62: return "CL_INVALID_MIP_LEVEL";
		case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
		case -64: return "CL_INVALID_PROPERTY";
		case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
		case -66: return "CL_INVALID_COMPILER_OPTIONS";
		case -67: return "CL_INVALID_LINKER_OPTIONS";
		case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";
		case -69: return "CL_INVALID_PIPE_SIZE";
		case -70: return "CL_INVALID_DEVICE_QUEUE";

		case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
		case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
		case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
		case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
		case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
		case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
		case -1006: return "CL_INVALID_D3D11_DEVICE_KHR";
		case -1007: return "CL_INVALID_D3D11_RESOURCE_KHR";
		case -1008: return "CL_D3D11_RESOURCE_ALREADY_ACQUIRED_KHR";
		case -1009: return "CL_D3D11_RESOURCE_NOT_ACQUIRED_KHR";
		case -1010: return "CL_INVALID_D3D9_DEVICE_NV/INTEL";
		case -1011: return "CL_INVALID_D3D9_RESOURCE_NV/INTEL";
		case -1012: return "CL_D3D9_RESOURCE_ALREADY_ACQUIRED_NV/INTEL";
		case -1013: return "CL_D3D9_RESOURCE_NOT_ACQUIRED_NV/INTEL";
		case -1092: return "CL_EGL_RESOURCE_NOT_ACQUIRED_KHR";
		case -1093: return "CL_INVALID_EGL_OBJECT_KHR";
		case -1094: return "CL_INVALID_ACCELERATOR_INTEL";
		case -1095: return "CL_INVALID_ACCELERATOR_TYPE_INTEL";
		case -1096: return "CL_INVALID_ACCELERATOR_DESCRIPTOR_INTEL";
		case -1097: return "CL_ACCELERATOR_TYPE_NOT_SUPPORTED_INTEL";
		case -1098: return "CL_INVALID_VA_API_MEDIA_ADAPTER_INTEL";
		case -1099: return "CL_INVALID_VA_API_MEDIA_SURFACE_INTEL";
		case -1100: return "CL_VA_API_MEDIA_SURFACE_ALREADY_ACQUIRED_INTEL";
		case -1101: return "CL_VA_API_MEDIA_SURFACE_NOT_ACQUIRED_INTEL";

		case -9999: return "NVidia clEnqueueNDRangeKernel Illegal read or write to a buffer";

		#ifdef RL_CLFFT
		case 4096: return "CLFFT_BUGCHECK";
		case 4097: return "CLFFT_NOTIMPLEMENTED";
		case 4098: return "CLFFT_TRANSPOSED_NOTIMPLEMENTED";
		case 4099: return "CLFFT_FILE_NOT_FOUND";
		case 4100: return "CLFFT_FILE_CREATE_FAILURE";
		case 4101: return "CLFFT_VERSION_MISMATCH";
		case 4102: return "CLFFT_INVALID_PLAN";
		case 4103: return "CLFFT_DEVICE_NO_DOUBLE";
		case 4104: return "CLFFT_DEVICE_MISMATCH";
		#endif

		// Personnal codes
		case -1024: return "clew initialisation failed";

		default: return "Unknown OpenCL error";
	}
}

void check_compilation_log(clctx_t *c, cl_program program)
{
	size_t loglen;
	char *log;

	clGetProgramBuildInfo(program, c->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &loglen);
	log = calloc(loglen, sizeof(char));
	clGetProgramBuildInfo(program, c->device_id, CL_PROGRAM_BUILD_LOG, loglen, log, NULL);
	fprintf_rl(stderr, "OpenCL compilation failed:\n%s\n\n", log);
	free (log);
}

char *cl_get_device_string(clctx_t *c, cl_device_info param_name)
{
	cl_int ret=0;
	size_t info_size;
	char *string=NULL;

	ret = clGetDeviceInfo(c->device_id, param_name, 0, NULL, &info_size);
	string = calloc(info_size, sizeof(char));
	ret = clGetDeviceInfo(c->device_id, param_name, info_size, string, NULL);

	return string;
}

#ifdef RL_OPENCL_GL
#ifdef __APPLE__
extern CGLContextObj CGLGetCurrentContext(void);
#endif
#endif

cl_int init_cl_context_from_gl(clctx_t *c, cl_platform_id platform)
{
	cl_int ret=0;

	ret = clewInit();
	if (ret)
	{
		fprintf_rl(stderr, "clewInit() failed with code %d\n", ret);
		return -1024;
	}

	#ifdef RL_OPENCL_GL

	#if defined(_WIN32)		// Windows	from http://stackoverflow.com/a/30529217/1675589
	cl_context_properties properties[] =
	{
		CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
		CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform,
		0
	};
	#elif defined(__APPLE__)	// OS X
	CGLContextObj     kCGLContext     = CGLGetCurrentContext();
	CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);

	cl_context_properties properties[] =
	{
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties) kCGLShareGroup,
		0
	};
	#else				// Linux
	cl_context_properties properties[] =
	{
		CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform,
		0
	};
	#endif

	//c->context = clCreateContext(NULL, ret_num_devices, device_id, NULL, NULL, &ret);
	c->context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &ret);
	CL_ERR_RET("clCreateContextFromType (in init_cl_context_from_gl)", ret);

	#endif
	return ret;
}

cl_int init_cl_context(clctx_t *c, const int from_gl)
{
	cl_int i, ret, pf_index=-1;
	cl_platform_id	platform_id[16]={0};
	cl_device_id	device_id[16]={0};
	cl_uint		ret_num_platforms=0;
	cl_uint		ret_num_devices=0;

	ret = clewInit();
	if (ret)
	{
		fprintf_rl(stderr, "clewInit() failed with code %d\n", ret);
		return -1024;
	}

	ret = clGetPlatformIDs(sizeof(platform_id)/sizeof(*platform_id), platform_id, &ret_num_platforms);	// get all the platforms
	CL_ERR_RET("clGetPlatformIDs (in init_cl_context)", ret);

	for (i=0; i<ret_num_platforms; i++)		// go through all the platforms
	{
		ret = clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_GPU, sizeof(device_id)/sizeof(*device_id), device_id, &ret_num_devices);	// get all the suitable GPU devices

		if (ret_num_devices > 0)		// stop trying platforms when a suitable device is found
		{
			pf_index = i;
			break;
		}
	}

	#if 0
	if (ret_num_devices==0)				// if a non-GPU wasn't found try again with CPUs included
		for (i=0; i<ret_num_platforms; i++)	// go through all the platforms
		{
			ret = clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_ALL, sizeof(device_id)/sizeof(*device_id), device_id, &ret_num_devices);	// get all the suitable devices, CPU included

			if (ret_num_devices > 0)
			{
				pf_index = i;
				break;
			}
		}
	#endif
	CL_ERR_RET("clGetDeviceIDs (in init_cl_context)", ret);
	c->device_id = device_id[0];

	if (from_gl)	// get context from OpenGL
	{
		ret = init_cl_context_from_gl(c, platform_id[pf_index]);
		CL_ERR_RET("init_cl_context_from_gl (in init_cl_context)", ret);
	}
	else
	{
		c->context = clCreateContext(NULL, ret_num_devices, device_id, NULL, NULL, &ret);
		CL_ERR_RET("clCreateContext (in init_cl_context)", ret);
	}

	c->command_queue = clCreateCommandQueue(c->context, device_id[0], 0*CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | 1*CL_QUEUE_PROFILING_ENABLE, &ret);
	CL_ERR_RET("clCreateCommandQueue (in init_cl_context)", ret);

	return ret;
}

void deinit_clctx(clctx_t *c, int deinit_kernel)
{
	if (deinit_kernel)
	{
		clReleaseKernel(c->kernel);
		clReleaseProgram(c->program);
	}
	clReleaseCommandQueue(c->command_queue);
	clReleaseContext(c->context);
}

uint64_t cl_make_program_and_device_hash(clctx_t *c, const char *src, const char *compil_opt)
{
	int i;
	uint64_t hash;
	buffer_t buf={0};
	char *string;
	cl_device_info param[] = { CL_DEVICE_NAME, CL_DEVICE_VERSION, CL_DRIVER_VERSION, CL_DEVICE_OPENCL_C_VERSION, CL_DEVICE_EXTENSIONS };

	// Print everything needed to make the hash to a string
	for (i=0; i < sizeof(param)/sizeof(*param); i++)
	{
		string = cl_get_device_string(c, param[i]);
		bufprintf(&buf, "%s\n", string);
		free(string);
	}

	bufprintf(&buf, "%s\n", src);
	bufprintf(&buf, "%s\n", compil_opt);

	// Make the hash
	hash = get_string_hash(buf.buf);
	free_buf(&buf);

	return hash;
}

cl_int build_cl_program(clctx_t *c, cl_program *program, const char *src)
{
	cl_int ret;
	size_t src_len;
	const char compil_opt[] = "-cl-single-precision-constant -cl-denorms-are-zero -cl-mad-enable -cl-no-signed-zeros -cl-unsafe-math-optimizations -cl-finite-math-only -cl-fast-relaxed-math";	// removed options: -save-temps

	src_len = strlen(src);

	// Compile source
	*program = clCreateProgramWithSource(c->context, 1, &src, &src_len, &ret);
	CL_ERR_RET("clCreateProgramWithSource (in build_cl_program)", ret);

	ret = clBuildProgram(*program, 1, &c->device_id, compil_opt, NULL, NULL);
	if (ret != CL_SUCCESS)
		check_compilation_log(c, *program);
	CL_ERR_RET("clBuildProgram (in build_cl_program)", ret);

	return ret;
}

char *make_cl_filecache_path(clctx_t *c, const char *src, const char *compil_opt)
{
	uint64_t hash;
	char name[64];

	// Hash to find binary program file
	hash = cl_make_program_and_device_hash(c, src, compil_opt);
	sprintf(name, "OpenCL cached program %llx.bin", hash);
	return make_appdata_path("rouziclib", name, 1);
}

cl_int build_cl_program_filecache(clctx_t *c, cl_program *program, const char *src)
{
	cl_int ret, binary_status;
	size_t src_len;
	const char compil_opt[] = "-cl-single-precision-constant -cl-denorms-are-zero -cl-mad-enable -cl-no-signed-zeros -cl-unsafe-math-optimizations -cl-finite-math-only -cl-fast-relaxed-math";	// removed options: -save-temps
	char *path;
	buffer_t buf={0};
	int binary_loaded=0;

	// Try to load binary source
	path = make_cl_filecache_path(c, src, compil_opt);
	if (check_file_is_readable(path))
	{
		buf = buf_load_raw_file(path);
		*program = clCreateProgramWithBinary(c->context, 1, &c->device_id, &buf.len, &buf.buf, &binary_status, &ret);
		free_buf(&buf);

		if (ret == CL_SUCCESS && binary_status == CL_SUCCESS)
			binary_loaded = 1;
		else
			fprintf_rl(stderr, "clCreateProgramWithBinary() in build_cl_program_filecache() failed with ret = %s and binary_status = %s\n", get_cl_error_string(ret), get_cl_error_string(binary_status));
	}

	// Otherwise use text source
	if (binary_loaded == 0)
	{
		src_len = strlen(src);
		*program = clCreateProgramWithSource(c->context, 1, &src, &src_len, &ret);
		CL_ERR_RET("clCreateProgramWithSource (in build_cl_program_filecache)", ret);
	}

	// Compile program
	ret = clBuildProgram(*program, 1, &c->device_id, compil_opt, NULL, NULL);
	if (ret != CL_SUCCESS)
		check_compilation_log(c, *program);
	CL_ERR_RET("clBuildProgram (in build_cl_program_filecache)", ret);

	// Store program binary if needed
	if (binary_loaded == 0)
	{
		// Get the binary
		ret = clGetProgramInfo(*program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &buf.len, NULL);
		CL_ERR_RET("clGetProgramInfo (in build_cl_program_filecache)", ret);
		buf_alloc_enough(&buf, buf.len+1);
		ret = clGetProgramInfo(*program, CL_PROGRAM_BINARIES, sizeof(char *), &buf.buf, NULL);
		CL_ERR_RET("clGetProgramInfo (in build_cl_program_filecache)", ret);

		// Save it
		buf_save_raw_file(&buf, path, "wb");
	}

	free(path);

	return ret;
}

cl_int create_cl_kernel(clctx_t *c, cl_program program, cl_kernel *kernel, const char *name)
{
	cl_int ret;

	*kernel = clCreateKernel(program, name, &ret);
	if (ret != CL_SUCCESS)
		check_compilation_log(c, program);

	return ret;
}

cl_int zero_cl_mem(clctx_t *c, cl_mem buffer, size_t size)
{
	cl_int ret;
	uint32_t z = 0;

	ret = clEnqueueFillBuffer (c->command_queue, buffer, &z, sizeof(z), 0, size, 0, NULL, NULL);
	CL_ERR_RET("clEnqueueFillBuffer (in zero_cl_mem)", ret);

	return ret;
}

void init_framebuffer_cl(const clctx_t *clctx)		// inits the linear CL buffer and copies the data from frgb
{
	cl_int ret;

	if (fb->clctx.command_queue==NULL)
		fb->clctx = *clctx;		// copy the original cl context
}

void cl_make_srgb_tex()
{
	cl_int ret=0;
#ifdef RL_OPENCL_GL

	// Detect whether or not to do interop sync
	size_t info_size;
	cl_bool val;
	ret = clGetDeviceInfo(fb->clctx.device_id, CL_DEVICE_PREFERRED_INTEROP_USER_SYNC, sizeof(cl_bool), &val, &info_size);
	fb->interop_sync = val;

	// Create an OpenGL 2D texture normally
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &fb->gltex);						// generate the texture ID
	glBindTexture(GL_TEXTURE_2D, fb->gltex);				// binding the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// regular sampler params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	// need to set GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0); 		// set the base and max mipmap levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fb->maxdim.x, fb->maxdim.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);		// specify texture dimensions, format etc

	fb->cl_srgb = clCreateFromGLTexture(fb->clctx.context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, fb->gltex, &ret);	// Creating the OpenCL image corresponding to the texture (once)
	CL_ERR_NORET("clCreateFromGLTexture (in cl_make_srgb_tex(), for fb->cl_srgb)", ret);

	if (fb->interop_sync==0)		// acquire the GL texture with OpenCL only once if no interop sync is needed
	{
		ret = clEnqueueAcquireGLObjects_wrap(fb->clctx.command_queue, 1,  &fb->cl_srgb, 0, 0, NULL);		// get the ownership of cl_srgb
		CL_ERR_NORET("clEnqueueAcquireGLObjects (in cl_make_srgb_tex(), for fb->cl_srgb)", ret);

		fb->opt_glfinish = 1;
	}
	else
	{
		fb->opt_clfinish = 1;
		fb->opt_glfinish = 1;
		fb->opt_interop = 1;
	}

#else
	fb->cl_srgb = clCreateBuffer(fb->clctx.context, CL_MEM_WRITE_ONLY, mul_x_by_y_xyi(fb->maxdim)*4, NULL, &ret);
	CL_ERR_NORET("clCreateBuffer (in cl_make_srgb_tex(), for fb->cl_srgb)", ret);
#endif
}

cl_int init_fb_cl()
{
	cl_int ret;

	if (fb->clctx.command_queue)
	{
		clReleaseMemObject(fb->data_cl);
		deinit_clctx(&fb->clctx, 0);
	}

	#ifdef RL_OPENCL_GL
	ret = init_cl_context(&fb->clctx, 1);
	#else
	ret = init_cl_context(&fb->clctx, 0);
	#endif
	CL_ERR_RET("init_cl_context", ret);

	cl_make_srgb_tex();

	return ret;
}

// OpenCL API wrappers to help identify leaks
cl_int clEnqueueNDRangeKernel_wrap(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	return clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
}

cl_int clFinish_wrap(cl_command_queue command_queue)
{
	return clFinish(command_queue);
}

cl_int clEnqueueWriteBuffer_wrap(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	return clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
}

cl_int clEnqueueReadBuffer_wrap(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	return clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
}

cl_int clEnqueueReleaseGLObjects_wrap(cl_command_queue command_queue, cl_uint num_objects, const cl_mem *mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	return clEnqueueReleaseGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);
}

cl_int clEnqueueAcquireGLObjects_wrap(cl_command_queue command_queue, cl_uint num_objects, const cl_mem *mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event)
{
	return clEnqueueAcquireGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);
}

cl_int clWaitForEvents_wrap(cl_uint num_events, const cl_event *event_list)
{
	return clWaitForEvents(num_events, event_list);
}

cl_int clGetEventProfilingInfo_wrap(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret)
{
	return clGetEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
}

cl_int clReleaseEvent_wrap(cl_event event)
{
	return clReleaseEvent(event);
}

cl_int clSetKernelArg_wrap(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value)
{
	return clSetKernelArg(kernel, arg_index, arg_size, arg_value);
}

cl_int clFlush_wrap(cl_command_queue command_queue)
{
	return clFlush(command_queue);
}

#endif

int check_opencl()
{
#ifdef RL_OPENCL
	clctx_t clctx={0};
	cl_int ret;
	static int init=0, init_failed=0;

	if (init_failed)
		return 0;

	if (init)
		return 1;

	init_failed = 1;

	// Try creating a context then destroy it
	ret = init_cl_context(&clctx, 0);
	CL_ERR_RET("check_opencl", ret);
	deinit_clctx(&clctx, 0);

	init_failed = 0;
	init = 1;
	return 1;
#else
	return 0;
#endif
}

void dialog_cl_gl_interop_options()
{
	#ifdef RL_OPENCL
	// GUI layout
	static gui_layout_t layout={0};
	const char *layout_src[] = {
		"elem 0", "type none", "label OpenCL/GL Interop Options", "pos	-0;6	8;3", "dim	4	9;4", "off	0	1", "",
		"elem 10", "type checkbox", "label clFinish()", "pos	0	5;11", "dim	3	0;10", "off	0	1", "",
		"elem 11", "type checkbox", "label glFinish()", "link_pos_id 10._b", "pos	0	-0;1", "dim	3	0;10", "off	0	1", "",
		"elem 12", "type checkbox", "label Interop sync", "link_pos_id 11._b", "pos	0	-0;1", "dim	3	0;10", "off	0	1", "",
		"elem 20", "type label", "pos	0	7;5", "dim	3	0;10", "off	0	1", "",
		"elem 21", "type label", "link_pos_id 20", "pos	0	-0;11", "dim	3	0;7", "off	0	1", "",
		"elem 30", "type checkbox", "label Test pattern", "pos	0	-0;2", "dim	3	0;6", "off	0	1", "",
	};

	make_gui_layout(&layout, layout_src, sizeof(layout_src)/sizeof(char *), "CL/GL options");

	if (mouse.window_minimised_flag > 0)
		return;

	// Window
	static flwindow_t window={0};
	flwindow_init_defaults(&window);
	draw_dialog_window_fromlayout(&window, cur_wind_on, &cur_parent_area, &layout, 0);

	// Controls
	ctrl_checkbox_fromlayout(&fb->opt_clfinish, &layout, 10);
	ctrl_checkbox_fromlayout(&fb->opt_glfinish, &layout, 11);
	ctrl_checkbox_fromlayout(&fb->opt_interop, &layout, 12);

	// FPS and info
	double td = fb->timing[circ_index(fb->timing_index-1, fb->timing_count)].flip_end - fb->timing[circ_index(fb->timing_index-2, fb->timing_count)].flip_end;
	gui_printf_to_label(&layout, 20, 0, "%.1f FPS", 1./fps_estimate_2speeds(td, 0));
	gui_printf_to_label(&layout, 21, 0, "CL_DEVICE_PREFERRED_INTEROP_USER_SYNC is %s", fb->interop_sync ? "true" : "false");
	draw_label_fromlayout(&layout, 20, ALIG_CENTRE | MONODIGITS);
	draw_label_fromlayout(&layout, 21, ALIG_CENTRE | MONODIGITS);

	// Box visual test
	static int pattern_on=1;
	ctrl_checkbox_fromlayout(&pattern_on, &layout, 30);

	if (pattern_on)
	{
		static int is=0;
		xy_t ip;

		is = (is+1) % 9;
		ip = xy(is/3, is%3);
		draw_rect_full(sc_rect(offset_scale_rect(make_rect_off(ip, XY1, XY0), layout.offset, layout.sm)), drawing_thickness, make_grey(0.5), blend_add, 1.);
	}
	#endif
}
