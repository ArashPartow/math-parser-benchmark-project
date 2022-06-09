// in libraries/opencl_struct.h:
// clctx_t, clew.h

#ifdef RL_OPENCL

extern const char *get_cl_error_string(cl_int err);
extern void check_compilation_log(clctx_t *c, cl_program program);
extern char *cl_get_device_string(clctx_t *c, cl_device_info param_name);
extern cl_int init_cl_context_from_gl(clctx_t *c, cl_platform_id platform);
extern cl_int init_cl_context(clctx_t *c, const int from_gl);
extern void deinit_clctx(clctx_t *c, int deinit_kernel);
extern uint64_t cl_make_program_and_device_hash(clctx_t *c, const char *src, const char *compil_opt);
extern cl_int build_cl_program(clctx_t *c, cl_program *program, const char *src);
extern cl_int build_cl_program_filecache(clctx_t *c, cl_program *program, const char *src);
extern cl_int create_cl_kernel(clctx_t *c, cl_program program, cl_kernel *kernel, const char *name);
extern cl_int zero_cl_mem(clctx_t *c, cl_mem buffer, size_t size);
extern void init_framebuffer_cl(const clctx_t *clctx);
extern void cl_make_srgb_tex();
extern cl_int init_fb_cl();

extern cl_int clEnqueueNDRangeKernel_wrap(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
extern cl_int clFinish_wrap(cl_command_queue command_queue);
extern cl_int clEnqueueWriteBuffer_wrap(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
extern cl_int clEnqueueReadBuffer_wrap(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void *ptr, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
extern cl_int clEnqueueReleaseGLObjects_wrap(cl_command_queue command_queue, cl_uint num_objects, const cl_mem *mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
extern cl_int clEnqueueAcquireGLObjects_wrap(cl_command_queue command_queue, cl_uint num_objects, const cl_mem *mem_objects, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event);
extern cl_int clWaitForEvents_wrap(cl_uint num_events, const cl_event *event_list);
extern cl_int clGetEventProfilingInfo_wrap(cl_event event, cl_profiling_info param_name, size_t param_value_size, void *param_value, size_t *param_value_size_ret);
extern cl_int clReleaseEvent_wrap(cl_event event);
extern cl_int clSetKernelArg_wrap(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void *arg_value);
extern cl_int clFlush_wrap(cl_command_queue command_queue);

#define CL_ERR_RET(name, ret)	if (ret != CL_SUCCESS) { fprintf_rl(stderr, "%s failed (err %d: %s)\n", name, ret, get_cl_error_string(ret));	return ret; }
#define CL_ERR_NORET(name, ret)	if (ret != CL_SUCCESS) { fprintf_rl(stderr, "%s failed (err %d: %s)\n", name, ret, get_cl_error_string(ret));	return ; }

#endif

extern int check_opencl();
extern void dialog_cl_gl_interop_options();
