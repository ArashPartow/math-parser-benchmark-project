void drawq_reinit()
{
	// Copy last data space to data_cl
	if (fb.data_space_start > fb.data_copy_start)
		cl_copy_buffer_to_device(&fb.data[fb.data_copy_start], fb.data_copy_start, fb.data_space_start - fb.data_copy_start);

	memset(fb.drawq_data, 0, fb.drawq_data[DQ_END] * sizeof(int32_t));
	memset(fb.sector_count, 0, fb.sectors * sizeof(int32_t));
	memset(fb.pending_bracket, 0, fb.sectors * sizeof(int32_t));
	memset(fb.entry_list, 0, fb.entry_list_end * sizeof(int32_t));
	memset(fb.sector_list, 0, fb.sector_list[DQ_END] * sizeof(int32_t));

	fb.sector_list[DQ_END] = DQ_END_HEADER_SL;
	fb.sector_list[DQ_ENTRY_START] = DQ_END_HEADER_SL;
	fb.drawq_data[DQ_END] = 1;
	fb.entry_count = 0;

	if (fb.use_drawq)
		cl_data_table_prune_unused();

	fb.must_recalc_free_space = 1;
}

void drawq_alloc()
{
	int32_t i;
	int32_t *dataint;
	double ss;

	#ifdef RL_OPENCL
	if (fb.use_drawq==1)
		clFinish_wrap(fb.clctx.command_queue);	// wait for end of queue
	#endif

	if (fb.use_drawq==2)
		drawq_soft_finish();

	drawq_free();

	data_cl_alloc(1);

	fb.max_sector_count = 17000;
	fb.sector_size = 4;				// can't be smaller than 4 (16x16 px)

ss_calc:
	ss = (double) (1<<fb.sector_size);
	fb.sectors = ceil((double) fb.maxdim.x / ss) * ceil((double) fb.maxdim.y / ss);
	fb.sector_w = ceil((double) fb.maxdim.x / ss);
	if (fb.sectors >= fb.max_sector_count)
	{
		fb.sector_size++;
		goto ss_calc;
	}

	fb.drawq_data = calloc (fb.drawq_as = 1 << 18, sizeof(int32_t));
	fb.sector_pos = calloc (fb.max_sector_count, sizeof(int32_t));
	fb.entry_list = calloc (fb.entry_list_as = 1 << 12, sizeof(int32_t));
	fb.sector_list = calloc (fb.sector_list_as = 1 << 12, sizeof(int32_t));
	fb.entry_pos = calloc (fb.entry_pos_as = 1 << 10, sizeof(int32_t));
	fb.sector_count = calloc (fb.max_sector_count, sizeof(int32_t));
	fb.pending_bracket = calloc (fb.max_sector_count, sizeof(int32_t));

	drawq_reinit();
}

void drawq_free()
{
	if (fb.drawq_data)
	{
		free(fb.drawq_data);
		free(fb.sector_pos);
		free(fb.entry_list);
		free(fb.sector_list);
		free(fb.sector_count);
		free(fb.pending_bracket);
		free(fb.entry_pos);

		fb.drawq_data = NULL;
	}
}

void drawq_run()
{
	#ifdef RL_OPENCL
	const char clsrc_draw_queue[] =
	#include "drawqueue/opencl/drawqueue.cl.h"

	int32_t i;
	cl_int ret, randseed;
	cl_event ev;
	static int init=1;
	size_t global_work_offset[2], global_work_size[2];

	if (fb.use_drawq==1)
	{
		if (init)
		{
			init=0;
			ret = build_cl_program_filecache(&fb.clctx, &fb.clctx.program, clsrc_draw_queue);
			CL_ERR_NORET("build_cl_program_filecache (in drawq_run)", ret);

			#ifdef RL_OPENCL_GL
			ret = create_cl_kernel(&fb.clctx, fb.clctx.program, &fb.clctx.kernel, "draw_queue_srgb_kernel");
			#else
			ret = create_cl_kernel(&fb.clctx, fb.clctx.program, &fb.clctx.kernel, "draw_queue_srgb_buf_kernel");
			#endif
			CL_ERR_NORET("create_cl_kernel (in drawq_run)", ret);
		}
		if (fb.clctx.kernel==NULL)
			return ;

		#ifdef RL_OPENCL_GL
		if (fb.opt_glfinish)
		{
			glFlush();
			glFinish();
		}

		if (fb.opt_interop)
		{
			#if 1
			ret = clEnqueueAcquireGLObjects_wrap(fb.clctx.command_queue, 1,  &fb.cl_srgb, 0, NULL, NULL);	// get the ownership of cl_srgb
			#else
			ret = clEnqueueAcquireGLObjects(fb.clctx.command_queue, 1,  &fb.cl_srgb, 0, NULL, &ev);		// get the ownership of cl_srgb
			CL_ERR_NORET("clEnqueueAcquireGLObjects (in drawq_run(), for fb.cl_srgb)", ret);
			clWaitForEvents(1, &ev);
			clReleaseEvent(ev);
			#endif
		}
		#endif
	}
	#endif

	fb.timing[fb.timing_index].interop_sync_end = get_time_hr();

	// Make entry list for each sector
	drawq_compile_lists();
	fb.timing[fb.timing_index].dq_comp_end = get_time_hr();

	if (fb.use_drawq==2)
		drawq_soft_run();

	if (fb.use_drawq==1)
	{
		#ifdef RL_OPENCL

		// Get profiling times
		clWaitForEvents_wrap(1, &fb.clctx.ev);
		clGetEventProfilingInfo_wrap(fb.clctx.ev, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &fb.clctx.queue_time, NULL);
		clGetEventProfilingInfo_wrap(fb.clctx.ev, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &fb.clctx.start_time, NULL);
		clGetEventProfilingInfo_wrap(fb.clctx.ev, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &fb.clctx.end_time, NULL);
		clReleaseEvent_wrap(fb.clctx.ev);
		frame_timing_t *timing = &fb.timing[circ_index(fb.timing_index-1, fb.timing_count)];
		timing->thread_start = timing->cl_enqueue_end;// + (double) (fb.clctx.start_time - fb.clctx.queue_time)*1e-9;
		timing->thread_end = timing->cl_enqueue_end + (double) (fb.clctx.end_time-fb.clctx.queue_time)*1e-9;
		//fprintf_rl(stdout, "OpenCL kernel: %ld ns - %ld ns\n", fb.clctx.start_time - fb.clctx.queue_time, fb.clctx.end_time-fb.clctx.start_time);

		// Copy compiled lists to data_cl
		cl_ulong drawq_data_index = cl_add_buffer_to_data_table(fb.drawq_data, fb.drawq_data[DQ_END]*sizeof(int32_t), sizeof(int32_t), NULL);
		cl_ulong sector_pos_index = cl_add_buffer_to_data_table(fb.sector_pos, fb.sectors*sizeof(int32_t), sizeof(int32_t), NULL);
		cl_ulong entry_list_index = cl_add_buffer_to_data_table(fb.entry_list, fb.entry_list_end*sizeof(int32_t), sizeof(int32_t), NULL);

		// Copy last data space to data_cl
		ret = clEnqueueWriteBuffer_wrap(fb.clctx.command_queue, fb.data_cl, CL_FALSE, fb.data_copy_start, fb.data_space_start - fb.data_copy_start, &fb.data[fb.data_copy_start], 0, NULL, &ev);
		CL_ERR_NORET("clEnqueueWriteBuffer(in drawq_run, for fb.data_cl)", ret);
		fb.data_copy_start = fb.data_space_start;

		// Remove compiled lists from data_cl
		cl_data_table_remove_entry_by_host_ptr(fb.drawq_data);
		cl_data_table_remove_entry_by_host_ptr(fb.sector_pos);
		cl_data_table_remove_entry_by_host_ptr(fb.entry_list);

		// Compute the random seed
		randseed = rand32();

		// wait for the input data copies to end
		clWaitForEvents_wrap(1, &ev);	// somehow this also waits for the kernel to end, which isn't good
		clReleaseEvent_wrap(ev);
		fb.timing[fb.timing_index].cl_copy_end = get_time_hr();

		// Run the fb.clctx.kernel
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 0, sizeof(cl_ulong), &drawq_data_index);	CL_ERR_NORET("clSetKernelArg (in drawq_run, for drawq_data_index)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 1, sizeof(cl_ulong), &sector_pos_index);	CL_ERR_NORET("clSetKernelArg (in drawq_run, for sector_pos_index)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 2, sizeof(cl_ulong), &entry_list_index);	CL_ERR_NORET("clSetKernelArg (in drawq_run, for entry_list_index)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 3, sizeof(cl_mem), &fb.data_cl);		CL_ERR_NORET("clSetKernelArg (in drawq_run, for fb.data_cl)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 4, sizeof(cl_mem), &fb.cl_srgb);		CL_ERR_NORET("clSetKernelArg (in drawq_run, for fb.cl_srgb)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 5, sizeof(cl_int), &fb.sector_w);		CL_ERR_NORET("clSetKernelArg (in drawq_run, for fb.sector_w)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 6, sizeof(cl_int), &fb.sector_size);		CL_ERR_NORET("clSetKernelArg (in drawq_run, for fb.sector_size)", ret);
		ret = clSetKernelArg_wrap(fb.clctx.kernel, 7, sizeof(cl_int), &randseed);		CL_ERR_NORET("clSetKernelArg (in drawq_run, for randseed)", ret);

		global_work_offset[0] = 0;
		global_work_offset[1] = 0;
		global_work_size[0] = fb.w;
		global_work_size[1] = fb.h;
		ret = clEnqueueNDRangeKernel_wrap(fb.clctx.command_queue, fb.clctx.kernel, 2, global_work_offset, global_work_size, NULL, 0, NULL, &fb.clctx.ev);
		CL_ERR_NORET("clEnqueueNDRangeKernel (in drawq_run)", ret);

		ret = clFlush_wrap(fb.clctx.command_queue);
		CL_ERR_NORET("clFlush (in drawq_run)", ret);
		fb.timing[fb.timing_index].cl_enqueue_end = get_time_hr();

		#ifndef RL_OPENCL_GL
		int pitch;
		SDL_LockTexture(fb.texture, NULL, &fb.r.srgb, &pitch);
		fb.tex_lock = 1;
		ret = clEnqueueReadBuffer_wrap(fb.clctx.command_queue, fb.cl_srgb, CL_FALSE, 0, mul_x_by_y_xyi(fb.r.dim)*4, fb.r.srgb, 0, NULL, NULL);
		CL_ERR_NORET("clEnqueueReadBuffer (in drawq_run(), for fb.cl_srgb)", ret);
		#endif
		#endif
	}

	drawq_reinit();	// clear/reinit the buffers
}

int32_t drawq_entry_size(const enum dq_type type)
{
	switch (type)
	{
		case DQT_BRACKET_OPEN:		return 0;
		case DQT_BRACKET_CLOSE:		return 1;
		case DQT_LINE_THIN_ADD:		return 9;
		case DQT_POINT_ADD:		return 6;
		case DQT_RECT_FULL:		return 8;
		case DQT_RECT_BLACK:		return 6;
		case DQT_RECT_BLACK_INV:	return 6;
		case DQT_PLAIN_FILL:		return 3;
		case DQT_TRIANGLE:		return 10;
		case DQT_TETRAGON:		return 12;
		case DQT_GAIN:			return 1;
		case DQT_GAIN_PARAB:		return 1;
		case DQT_LUMA_COMPRESS:		return 1;
		case DQT_COL_MATRIX:		return 9;
		case DQT_CLIP:			return 1;
		case DQT_CLAMP:			return 0;
		case DQT_CIRCLE_FULL:		return 7;
		case DQT_CIRCLE_HOLLOW:		return 7;
		//case DQT_BLIT_BILINEAR:		return 8;
		case DQT_BLIT_FLATTOP:		return 11;
		case DQT_BLIT_FLATTOP_ROT:	return 11;
		case DQT_BLIT_AANEAREST:	return 9;
		case DQT_BLIT_AANEAREST_ROT:	return 10;
		//case DQT_BLIT_PHOTO:		return 13;
		default:			return 0;
	}
}

void *drawq_add_to_main_queue(const enum dq_type type)
{
	int32_t end, *di = fb.drawq_data;
	int entry_size = drawq_entry_size(type);

	if (di==NULL)
		return NULL;

	if (fb.discard)
		return NULL;

	// store the drawing parameters in the main drawing queue
	end = di[DQ_END];
	alloc_enough(&fb.drawq_data, end + entry_size + 1, &fb.drawq_as, sizeof(int32_t), 2.);
	di = fb.drawq_data;

	di[end] = type;
	end++;

	di[DQ_END] += entry_size + 1;

	alloc_enough(&fb.sector_list, fb.sector_list[DQ_END] + 1, &fb.sector_list_as, sizeof(int32_t), 2.);
	fb.sector_list[DQ_ENTRY_START] = fb.sector_list[DQ_END];				// set the start of the new entry
	fb.sector_list[DQ_END]++;								// sector_list becomes 1 larger by having the sector count (=0) for the new entry added
	alloc_enough(&fb.entry_pos, fb.entry_count+=1, &fb.entry_pos_as, sizeof(int32_t), 2.);
	fb.entry_pos[fb.entry_count-1] = fb.sector_list[DQ_ENTRY_START];			// reference the start of this entry in sector_list

	return &di[end];
}

void drawq_add_sector_id_nopending(int32_t sector_id)
{
	if (fb.discard)
		return;

	fb.sector_count[sector_id]++;				// increment the count of entries for this sector

	alloc_enough(&fb.sector_list, fb.sector_list[DQ_END] + 1, &fb.sector_list_as, sizeof(int32_t), 2.);

	fb.sector_list[fb.sector_list[DQ_END]] = sector_id;	// add the sector to the list
	fb.sector_list[fb.sector_list[DQ_ENTRY_START]]++;	// increment the sector count for this entry
	fb.sector_list[DQ_END]++;				// sector_list becomes 1 larger
}

void drawq_add_sector_id(int32_t sector_id)	// like drawq_add_sector_id_nopending but clears the pending bracket count
{
	drawq_add_sector_id_nopending(sector_id);
	fb.pending_bracket[sector_id] = 0;
}

void drawq_add_sectors_for_area(recti_t bb)
{
	int ix, iy;

	if (fb.discard)
		return;

	for (iy=bb.p0.y; iy <= bb.p1.y; iy++)
		for (ix=bb.p0.x; ix <= bb.p1.x; ix++)
			drawq_add_sector_id(iy*fb.sector_w + ix);	// add sector reference
}

void drawq_add_sectors_for_already_set_sectors()	// adds sectors for the current main queue entry only if the sectors already had something to draw (useful for applied effects, such as multiplication)
{
	int sector_id;
	xyi_t ip, bb0, bb1;

	bb0 = xyi(0, 0);
	bb1 = xyi(fb.w-1 >> fb.sector_size, fb.h-1 >> fb.sector_size);

	// go through the affected sectors
	for (ip.y=bb0.y; ip.y<=bb1.y; ip.y++)
		for (ip.x=bb0.x; ip.x<=bb1.x; ip.x++)
		{
			sector_id = ip.y*fb.sector_w + ip.x;

			// if the sector contains something at the current bracket level
			if (fb.sector_count[sector_id] > 0 && fb.pending_bracket[sector_id] == 0)
				drawq_add_sector_id(sector_id);
		}
}

void drawq_compile_lists()		// makes entry_list and sector_pos
{
	int32_t i, j, end_i, end_j, main_i, sector, secpos, count, pos=0;

	for (i=0; i < fb.sectors; i++)
	{
		// fill the sector position list
		if (fb.sector_count[i] > 0)			// if the sector contains entries
		{
			fb.sector_pos[i] = pos;			// this is where the sector starts in entry_list
			pos += fb.sector_count[i] + 1;		// add to the position the count of entries for each sector + 1 for the count of entries
		}
		else						// if the sector is empty
		{
			fb.sector_pos[i] = -1;			// it is nowhere in entry_list
		}
	}
	fb.entry_list_end = pos;				// remembers how filled entry_list is

	end_i = fb.sector_list[DQ_END];
	main_i = 1;						// the first entry in the main queue starts at that position
	for (i=DQ_END_HEADER_SL; i <= end_i; i++)		// go through each entry
	{
		end_j = fb.sector_list[i];
		for (j=1; j <= end_j; j++)			// go through each sector for this entry
		{
			sector = fb.sector_list[i+j];

			if (sector >= 0)			// negative sector id indicates a removed sector
			{
				secpos = fb.sector_pos[sector];		// sector position in the entry list for each sector

				if (secpos >= 0)
				{
					count = 1;
					if (secpos < fb.entry_list_as)
						count = fb.entry_list[secpos] + 1;

					alloc_enough(&fb.entry_list, secpos + count + 1, &fb.entry_list_as, sizeof(int32_t), 2.);
					fb.entry_list[secpos] = count;
					fb.entry_list[secpos + count] = main_i;	// store the position of this entry in the main queue
				}
			}
		}

		i += end_j;

		// increment the main queue entry position by the size of the entry for its type + 1 (its type takes 1)
		main_i += drawq_entry_size(fb.drawq_data[main_i]) + 1;
	}
}

void drawq_test1()		// BRDF test
{
	int32_t ix, iy;
	xyi_t bb0, bb1;

	bb0 = xyi(0, 0);
	bb1 = xyi(fb.w-1 >> fb.sector_size, fb.h-1 >> fb.sector_size);

	// store the drawing parameters in the main drawing queue
	drawq_add_to_main_queue(DQT_TEST1);

	// go through the affected sectors
	for (iy=bb0.y; iy<=bb1.y; iy++)
		for (ix=bb0.x; ix<=bb1.x; ix++)
			drawq_add_sector_id(iy*fb.sector_w + ix);	// add sector reference
}

int drawq_get_bounding_box(rect_t box, xy_t rad, recti_t *bbi)
{
	rect_t bb, fb_box = rect(XY0, xy(fb.w-1, fb.h-1));

	box = sort_rect(box);

	// Calculate the bounding box
	bb.p0 = ceil_xy(sub_xy(box.p0, rad));
	bb.p1 = floor_xy(add_xy(box.p1, rad));

	// Check against framebuffer boundaries
	if (check_box_box_intersection(bb, fb_box)==0)
		return 0;

	// Convert to sector coordinates
	bbi->p0 = xy_to_xyi(max_xy(bb.p0, fb_box.p0));
	bbi->p1 = xy_to_xyi(min_xy(bb.p1, fb_box.p1));
	*bbi = rshift_recti(*bbi, fb.sector_size);

	return 1;
}

int drawq_get_bounding_box_for_polygon(xy_t *p, int p_count, xy_t rad, recti_t *bbi)
{
	int i;
	rect_t bb, fb_box = rect(XY0, xy(fb.w-1, fb.h-1));

	// Calculate the bounding box
	bb.p0 = ceil_xy(sub_xy(p[0], rad));
	bb.p1 = floor_xy(add_xy(p[0], rad));
	for (i=1; i < p_count; i++)
	{
		bb.p0 = min_xy(bb.p0, ceil_xy(sub_xy(p[i], rad)));
		bb.p1 = max_xy(bb.p1, floor_xy(add_xy(p[i], rad)));
	}

	// Check against framebuffer boundaries
	if (check_box_box_intersection(bb, fb_box)==0)
		return 0;

	// Convert to sector coordinates
	bbi->p0 = xy_to_xyi(max_xy(bb.p0, fb_box.p0));
	bbi->p1 = xy_to_xyi(min_xy(bb.p1, fb_box.p1));
	*bbi = rshift_recti(*bbi, fb.sector_size);

	return 1;
}

void drawq_get_inner_box(rect_t box, xy_t rad, recti_t *bbi)
{
	rect_t bb, fb_box = rect(XY0, xy(fb.w-1, fb.h-1));

	box = sort_rect(box);

	// Calculate the inner box
	bb.p0 = floor_xy(add_xy(box.p0, rad));
	bb.p1 = ceil_xy(sub_xy(box.p1, rad));

	bbi->p0 = xy_to_xyi(max_xy(bb.p0, fb_box.p0));
	bbi->p1 = xy_to_xyi(min_xy(bb.p1, fb_box.p1));
	*bbi = rshift_recti(*bbi, fb.sector_size);
}

void drawq_remove_prev_entry_for_sector(int32_t sector_id, int bracket_search, xyi_t pix_coord)
{
	int i, is, sector_count_for_entry, sector_count, cur_sector_w;
	int32_t *sector_list_for_entry;

	// Bracket search looks only for entries that cover every sector, like brackets do
	// since bracket sectors are written sequentially the sector can be found quickly
	if (bracket_search)
	{
		sector_count = mul_x_by_y_xyi(add_xyi(set_xyi(1), xyi(fb.w-1 >> fb.sector_size, fb.h-1 >> fb.sector_size)));
		cur_sector_w = (fb.w-1 >> fb.sector_size) + 1;

		for (i=fb.entry_count-1; i >= 0; i--)			// go through each main queue entry in sector_list from the last
		{
			sector_count_for_entry = fb.sector_list[ fb.entry_pos[i] ];

			if (sector_count_for_entry == sector_count)
			{
				sector_list_for_entry = &fb.sector_list[ fb.entry_pos[i]+1 ];	// point to the first sector of this entry's list of sectors

				is = pix_coord.y * cur_sector_w + pix_coord.x;		// sequential position of the pixel

				if (sector_list_for_entry[is] == sector_id)		// if we found the previous entry for this sector
				{
					sector_list_for_entry[is] = -1;			// remove it
					fb.sector_count[sector_id] -= 1;		// decrement the number of entries for this sector
					return ;
				}
			}
		}

		fprintf_rl(stderr, "Bracket entry for sector_id %d not found in drawq_remove_prev_entry_for_sector()\n", sector_id);
	}

	// Slow search, probably shouldn't be used
	for (i=fb.entry_count-1; i >= 0; i--)			// go through each main queue entry in sector_list from the last
	{
		sector_count_for_entry = fb.sector_list[ fb.entry_pos[i] ];
		sector_list_for_entry = &fb.sector_list[ fb.entry_pos[i]+1 ];	// point to the first sector of this entry's list of sectors

		for (is=0; is < sector_count_for_entry; is++)
			if (sector_list_for_entry[is] == sector_id)	// if we found the previous entry for this sector
			{
				sector_list_for_entry[is] = -1;		// remove it
				fb.sector_count[sector_id] -= 1;	// decrement the number of entries for this sector
				return ;
			}
	}

	fprintf_rl(stderr, "Entry to remove for sector_id %d not found in drawq_remove_prev_entry_for_sector()\n", sector_id);
}

void drawq_bracket_open()
{
	int sector_id;
	xyi_t ip, bb0, bb1;

	if (fb.use_drawq==0)
		return;

	if (fb.discard)
		return;

	bb0 = xyi(0, 0);
	bb1 = xyi(fb.w-1 >> fb.sector_size, fb.h-1 >> fb.sector_size);

	// store the drawing parameters in the main drawing queue
	drawq_add_to_main_queue(DQT_BRACKET_OPEN);

	// go through the affected sectors
	for (ip.y=bb0.y; ip.y<=bb1.y; ip.y++)
		for (ip.x=bb0.x; ip.x<=bb1.x; ip.x++)
		{
			sector_id = ip.y*fb.sector_w + ip.x;

			fb.pending_bracket[sector_id]++;		// increment the pending open bracket count
			drawq_add_sector_id_nopending(sector_id);	// add sector reference
		}
}

void drawq_bracket_close(enum dq_blend blending_mode)	// blending modes are listed in drawqueue_enums.h
{
	int sector_id;
	int32_t *di;
	xyi_t ip, bb0, bb1;

	if (fb.use_drawq==0)
		return;

	if (fb.discard)
		return;

	bb0 = xyi(0, 0);
	bb1 = xyi(fb.w-1 >> fb.sector_size, fb.h-1 >> fb.sector_size);

	// store the drawing parameters in the main drawing queue
	di = drawq_add_to_main_queue(DQT_BRACKET_CLOSE);
	di[0] = blending_mode;

	// go through the affected sectors
	for (ip.y=bb0.y; ip.y<=bb1.y; ip.y++)
		for (ip.x=bb0.x; ip.x<=bb1.x; ip.x++)
		{
			sector_id = ip.y*fb.sector_w + ip.x;

			// entry removal turned off due to high CPU usage
			/*if (fb.pending_bracket[sector_id])				// if there's a pending open bracket
				drawq_remove_prev_entry_for_sector(sector_id, 1, ip);	// remove the DQT_BRACKET_OPEN entry for this sector
			else*/
				drawq_add_sector_id_nopending(sector_id);		// add sector reference

			fb.pending_bracket[sector_id]--;		// decrement the pending open bracket count
			if (fb.pending_bracket[sector_id] < 0)
				fb.pending_bracket[sector_id] = 0;
		}
}
