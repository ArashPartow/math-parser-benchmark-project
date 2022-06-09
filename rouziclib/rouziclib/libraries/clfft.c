#ifdef RL_OPENCL
#ifdef RL_CLFFT

void print_clfft_version()
{
	cl_uint major, minor, patch;

	clfftGetVersion(&major, &minor, &patch);

	fprintf_rl(stdout, "clFFT v%d.%d.%d\n", major, minor, patch);
}

void clfft_setup(const int new_state)	// 1 inits clFFT, 0 uninits it
{
	static int state = 0;
	cl_int ret;
	clfftSetupData fftSetup;

	if (state != new_state)
	{
		if (new_state==1)		// init
		{
			ret = clfftInitSetupData(&fftSetup);
			CL_ERR_NORET("clfftInitSetupData (in clfft_setup)", ret);
			ret = clfftSetup(&fftSetup);
			CL_ERR_NORET("clfftSetup (in clfft_setup)", ret);
		}
		else
		{
			clfftTeardown();
		}

		state = new_state;
	}
}

void clfft_create_tmpbuf(clctx_t *clctx, clfftPlanHandle planid, cl_mem *tmp_buf)
{
	cl_int ret;
	size_t old_size, new_size;

	ret = clfftGetTmpBufSize(planid, &new_size);
	CL_ERR_NORET("clfftGetTmpBufSize (in clfft_create_tmpbuf)", ret);

	if (*tmp_buf)										// if a buffer already exists
	{
		ret = clGetMemObjectInfo(*tmp_buf, CL_MEM_SIZE, sizeof(old_size), &old_size, NULL);
		CL_ERR_NORET("clGetMemObjectInfo (in clfft_create_tmpbuf)", ret);

		if (old_size == new_size)							// and is already the right size
			return ;								// do nothing
		else										// otherwise
		{
			ret = clReleaseMemObject(*tmp_buf);					// free the old buffer
			CL_ERR_NORET("clReleaseMemObject (in clfft_create_tmpbuf)", ret);
		}
	}

	if (new_size > 0)									// create a new one if needed
	{
		*tmp_buf = clCreateBuffer(clctx->context, CL_MEM_READ_WRITE, new_size, NULL, &ret);
		CL_ERR_NORET("clCreateBuffer (in clfft_create_tmpbuf)", ret);
	}
}

void clfft_make_plan_1d(clctx_t *clctx, clfftPlanHandle *planid, int fft_size, int prec, int layout_in, int layout_out, int location, cl_mem *tmp_buf)
{
	cl_int ret;
	size_t dim[1] = {fft_size};

	clfft_setup(1);		// init clFFT just in case it's not already

	// Create a default plan for a complex FFT
	ret = clfftCreateDefaultPlan(planid, clctx->context, CLFFT_1D, dim);
	CL_ERR_NORET("clfftCreateDefaultPlan (in clfft_make_plan_1d)", ret);

	// Set plan parameters
	ret = clfftSetPlanPrecision(*planid, prec);
	CL_ERR_NORET("clfftSetPlanPrecision (in clfft_make_plan_1d)", ret);
	ret = clfftSetLayout(*planid, layout_in, layout_out);
	CL_ERR_NORET("clfftSetLayout (in clfft_make_plan_1d)", ret);
	ret = clfftSetResultLocation(*planid, location);
	CL_ERR_NORET("clfftSetResultLocation (in clfft_make_plan_1d)", ret);
	clfftSetPlanScale(*planid, CLFFT_FORWARD, 1.f/(float) fft_size);
	clfftSetPlanScale(*planid, CLFFT_BACKWARD, 1.f);

	ret = clfftBakePlan(*planid, 1, &clctx->command_queue, NULL, NULL);	// "bake" the plan, which compiles the kernel
	CL_ERR_NORET("clfftBakePlan (in clfft_make_plan_1d)", ret);

	clfft_create_tmpbuf(clctx, *planid, tmp_buf);				// create temporary buffer if needed
}

void clfft_make_plan_2d(clctx_t *clctx, clfft_plan_t *plan, xyi_t fft_dim, int prec, int layout_in, int layout_out, int location)
{
	cl_int ret;
	size_t dim[2] = {fft_dim.x, fft_dim.y};

	clfft_setup(1);		// init clFFT just in case it's not already

	memset(plan, 0, sizeof(clfft_plan_t));

	// Create a default plan for a complex FFT
	ret = clfftCreateDefaultPlan(&plan->planid, clctx->context, CLFFT_2D, dim);
	CL_ERR_NORET("clfftCreateDefaultPlan (in clfft_make_plan_2d)", ret);

	// Set plan parameters
	ret = clfftSetPlanPrecision(plan->planid, prec);
	CL_ERR_NORET("clfftSetPlanPrecision (in clfft_make_plan_2d)", ret);
	ret = clfftSetLayout(plan->planid, layout_in, layout_out);
	CL_ERR_NORET("clfftSetLayout (in clfft_make_plan_2d)", ret);
	ret = clfftSetResultLocation(plan->planid, location);
	CL_ERR_NORET("clfftSetResultLocation (in clfft_make_plan_2d)", ret);
	clfftSetPlanScale(plan->planid, CLFFT_FORWARD, 1.f/(float) mul_x_by_y_xyi(fft_dim));
	clfftSetPlanScale(plan->planid, CLFFT_BACKWARD, 1.f);

	ret = clfftBakePlan(plan->planid, 1, &clctx->command_queue, NULL, NULL);	// "bake" the plan, which compiles the kernel
	CL_ERR_NORET("clfftBakePlan (in clfft_make_plan_2d)", ret);

	clfft_create_tmpbuf(clctx, plan->planid, &plan->tmp_buf);				// create temporary buffer if needed

	plan->fft_dim = fft_dim;
	plan->gpu_buf = clCreateBuffer(clctx->context, CL_MEM_READ_WRITE, mul_x_by_y_xyi(fft_dim) * 2 * sizeof(float), NULL, &ret);
	CL_ERR_NORET("clCreateBuffer (in clfft_make_plan_2d)", ret);
}

void clfft_free_plan(clfft_plan_t *plan)
{
	clReleaseMemObject(plan->gpu_buf);
	clReleaseMemObject(plan->tmp_buf);
	clfftDestroyPlan(&plan->planid);	// destroy the plan
	memset(plan, 0, sizeof(clfft_plan_t));
}

void clfft_update_plan_2d(clctx_t *clctx, clfft_plan_t *plan, xyi_t fft_dim)
{
	if (equal_xyi(plan->fft_dim, fft_dim))
		return ;

	if (is0_xyi(plan->fft_dim) == 0)
		clfft_free_plan(plan);

	clfft_make_plan_2d(clctx, plan, fft_dim, CLFFT_SINGLE, CLFFT_COMPLEX_INTERLEAVED, CLFFT_COMPLEX_INTERLEAVED, CLFFT_INPLACE);
}

void clfft_2d(clctx_t *clctx, clfft_plan_t *plan, float *cpu_buf, xyi_t dim, int direction)
{
	cl_int ret;

	clfft_update_plan_2d(clctx, plan, dim);

	ret = clEnqueueWriteBuffer(clctx->command_queue, plan->gpu_buf, CL_FALSE, 0, mul_x_by_y_xyi(dim)*2*sizeof(float), cpu_buf, 0, NULL, NULL);
	CL_ERR_NORET("clEnqueueWriteBuffer (in clfft_2d)", ret);

	ret = clfftEnqueueTransform(plan->planid, direction==0 ? CLFFT_FORWARD : CLFFT_BACKWARD, 1, &clctx->command_queue, 0, NULL, NULL, &plan->gpu_buf, NULL, plan->tmp_buf);	// enqueue FFT
	CL_ERR_NORET("clfftEnqueueTransform (in clfft_2d)", ret);

	ret = clEnqueueReadBuffer(clctx->command_queue, plan->gpu_buf, CL_FALSE, 0, mul_x_by_y_xyi(dim)*2*sizeof(float), cpu_buf, 0, NULL, NULL);
	CL_ERR_NORET("clEnqueueReadBuffer (in clfft_2d)", ret);

	ret = clFinish(clctx->command_queue);
	CL_ERR_NORET("clFinish (in clfft_2d)", ret);
}

void clfft_1d_selfcontained(clctx_t *clctx, cl_mem in, cl_mem out, const int direction, const int fft_size)
{
	int i;
	cl_int ret;
	clfftPlanHandle planid;
	cl_mem tmp_buf = NULL;

	if (direction==CLFFT_FORWARD)
		clfft_make_plan_1d(clctx, &planid, fft_size, CLFFT_SINGLE, CLFFT_REAL, CLFFT_HERMITIAN_INTERLEAVED, CLFFT_OUTOFPLACE, &tmp_buf);	// create plan and temporary buffer
	else
		clfft_make_plan_1d(clctx, &planid, fft_size, CLFFT_SINGLE, CLFFT_HERMITIAN_INTERLEAVED, CLFFT_REAL, CLFFT_OUTOFPLACE, &tmp_buf);	// create plan and temporary buffer

	ret = clfftEnqueueTransform(planid, direction, 1, &clctx->command_queue, 0, NULL, NULL, &in, &out, tmp_buf);	// enqueue FFT
	CL_ERR_NORET("clfftEnqueueTransform (in clfft_1d_selfcontained)", ret);

	ret = clFinish(clctx->command_queue);
	CL_ERR_NORET("clFinish (in clfft_1d_selfcontained)", ret);

	clReleaseMemObject(tmp_buf);		// free tmp_buf
	ret = clfftDestroyPlan(&planid);	// destroy the plan
	clfft_setup(0);				// deinit clFFT
}

void clfft_1d_selfcontained_local(clctx_t *clctx, float *in, float *out, const int direction, const int fft_size)
{
	cl_int ret;
	cl_mem cl_in, cl_out;
	const int in_size  = direction==CLFFT_FORWARD ? fft_size : fft_size+2;
	const int out_size = direction==CLFFT_FORWARD ? fft_size+2 : fft_size;

	cl_in = clCreateBuffer(clctx->context, CL_MEM_READ_WRITE, in_size * sizeof(float), NULL, &ret);
	CL_ERR_NORET("clCreateBuffer (in clfft_1d_selfcontained_local)", ret);
	cl_out = clCreateBuffer(clctx->context, CL_MEM_READ_WRITE, out_size * sizeof(float), NULL, &ret);
	CL_ERR_NORET("clCreateBuffer (in clfft_1d_selfcontained_local)", ret);

	ret = clEnqueueWriteBuffer(clctx->command_queue, cl_in, CL_FALSE, 0, in_size*sizeof(float), in, 0, NULL, NULL);
	CL_ERR_NORET("clEnqueueWriteBuffer (in clfft_1d_selfcontained_local)", ret);

	clfft_1d_selfcontained(clctx, cl_in, cl_out, direction, fft_size);

	ret = clEnqueueReadBuffer(clctx->command_queue, cl_out, CL_FALSE, 0, out_size*sizeof(float), out, 0, NULL, NULL);

	clReleaseMemObject(cl_in);
	clReleaseMemObject(cl_out);

	ret = clFinish(clctx->command_queue);
	CL_ERR_NORET("clFinish (in clfft_1d_selfcontained_local)", ret);
}

#endif
#endif
