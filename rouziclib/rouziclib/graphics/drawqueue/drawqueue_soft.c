#ifdef RL_INTEL_INTR

#ifdef __GNUC__
__attribute__((__target__("ssse3")))
#endif
void dqs_block_to_srgb(srgb_t *srgb, float *block, int r_pitch, int srgb_order, xyi_t dim, int ss, int chan_stride) // SSSE3, calls SSE4.1
{
	xyi_t ip;
	int i, ib;
	__m128 f, sf;
	__m128i sv, shuf_mask;

	switch (srgb_order)
	{
		case ORDER_RGBA:
			shuf_mask = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 8, 4, 0);

		case ORDER_ABGR:
			shuf_mask = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 8, 4, 12);
			break;

		default:
		case ORDER_BGRA:
			shuf_mask = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, 0, 4, 8);
			break;

		case ORDER_ARGB:
			shuf_mask = _mm_set_epi8(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, 4, 0, 12);
			break;
	}

	for (ip.y=0; ip.y < dim.y; ip.y++)
	{
		i = ip.y * r_pitch;
		ib = ip.y << ss;

		for (ip.x=0; ip.x < dim.x; ip.x++, i++, ib++)
		{
			// Load frgb from block channel planes
			f = _mm_set_ps(block[chan_stride*3 + ib], block[chan_stride*2 + ib], block[chan_stride + ib], block[ib]);
			sf = _mm_mul_ps(_mm_frgb_to_srgb(f), _mm_set_ps1(255.f));	// convert and multiply by 255
			sv = _mm_cvtps_epi32(sf);					// cast to 32-bit int (rounded, no dithering)
			sv = _mm_shuffle_epi8(sv, shuf_mask);				// reorder the channels and pack them into the lower 32-bits
			_mm_storeu_si32(&srgb[i], sv);					// save final pixel to framebuffer
		}
	}
}

#endif

typedef struct
{
	volatile int thread_on;
	rl_thread_t thread_handle;
	rl_mutex_t proc_mtx, cont_mtx;
	int current_locks;
	uint8_t *data;
	int32_t *drawq_data, *sector_pos, *entry_list;
	volatile size_t data_as, drawq_as, sector_list_as, entry_list_as;
	volatile int sector_size, sector_w, r_pitch, srgb_order;
	srgb_t *srgb;
	volatile xyi_t r_dim;
	float **block;
	int thread_id, thread_count;
	frame_timing_t *timing;
} drawq_soft_data_t;

#ifndef DQS_THREADS
#define DQS_THREADS 1
#endif
drawq_soft_data_t *dqs_data=NULL;

int drawq_soft_thread(drawq_soft_data_t *d)
{
#ifdef RL_INTEL_INTR
	xyi_t ip, is, bpos, sec_dim, out_dim;
	float *df;
	int32_t *di;
	int ss, sec_pix, chan_stride;
	int i, eli, qi, sec, entry_count;
	xy_t pos;
	int brlvl;

	rl_mutex_unlock(&d->cont_mtx);		// unlock cont_mtx so that the calling thread can go on
	rl_thread_set_priority_high();

	while (d->thread_on)
	{
		rl_mutex_lock(&d->proc_mtx);

		if (d->thread_id==0)
			d->timing->thread_start = get_time_hr();


		df = (float *) d->drawq_data;
		di = d->drawq_data;
		ss = d->sector_size;
		sec_pix = 1 << ss;		// 1 << 4 = 16
		chan_stride = sec_pix*sec_pix;
		//sec_dim = rshift_xyi(d->r_dim, ss);			// 1920x1080 >> 4 = 120x67
		sec_dim = ceil_rshift_xyi(d->r_dim, ss);		// 1920x1080 >> 4 = 120x68
		brlvl = 0;			// bracket level

		// Go through each sector
		for (is.y=d->thread_id; is.y < sec_dim.y; is.y+=d->thread_count)
			for (is.x=0; is.x < sec_dim.x; is.x++)
			{
				bpos = lshift_xyi(is, ss);
				out_dim = min_xyi(sub_xyi(d->r_dim, bpos), set_xyi(sec_pix));

				sec = is.y * d->sector_w + is.x;	// sector index
				eli = d->sector_pos[sec];		// entry list index

				if (eli < 0)				// if the index is -1 that means there's nothing to do
				{
					// Blank the whole sector
					for (ip.y = bpos.y; ip.y < bpos.y+out_dim.y; ip.y++)
						memset(&d->srgb[ip.y*d->r_pitch + bpos.x], 0, out_dim.x*sizeof(srgb_t));
				}
				else
				{
					memset(d->block[0], 0, chan_stride*4*sizeof(float));

					pos = xyi_to_xy(bpos);
					entry_count = d->entry_list[eli];

					// Go through each entry for this sector
					for (i=0; i < entry_count; i++)
					{
						qi = d->entry_list[eli + i + 1];	// queue index

						switch (di[qi])				// type of the entry
						{
								case DQT_LINE_THIN_ADD:		dqsb_draw_line_thin_add	(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_POINT_ADD:		dqsb_draw_point_add	(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_RECT_FULL:		dqsb_draw_rect_full_add	(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_RECT_BLACK:		dqsb_draw_black_rect	(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_PLAIN_FILL:		dqsb_draw_plain_fill_add(&df[qi+1], d->block[brlvl],               chan_stride);
							/*break;	case DQT_GAIN:			dqsb_pv * df[qi+1];
							break;	case DQT_GAIN_PARAB:		dqsb_gain_parabolic(pv, df[qi+1]);
							break;	case DQT_LUMA_COMPRESS:		dqsb_luma_compression(pv, df[qi+1]);
							break;	case DQT_COL_MATRIX:		dqsb_colour_matrix(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_CLIP:			dqsb_min(pv, df[qi+1]);
							break;	case DQT_CLAMP:			dqsb_clamp(pv, 0.f, 1.f);
							break;	case DQT_CIRCLE_FULL:		dqsb_draw_circle_full_add(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_CIRCLE_HOLLOW:		dqsb_draw_circle_hollow_add(&df[qi+1], d->block[brlvl], pos, sec_pix, chan_stride);
							break;	//case DQT_BLIT_BILINEAR:	dqsb_blit_sprite_bilinear(&df[qi+1], d->data, d->block[brlvl], pos, sec_pix, chan_stride);*/
							break;	case DQT_BLIT_FLATTOP:		dqsb_blit_sprite_flattop(&df[qi+1], d->data, d->block[brlvl], pos, sec_pix, chan_stride);
							/*break;	case DQT_BLIT_FLATTOP_ROT:	dqsb_blit_sprite_flattop_rot(&df[qi+1], d->data, d->block[brlvl], pos, sec_pix, chan_stride);
							break;	//case DQT_BLIT_PHOTO:		dqsb_blit_photo(&df[qi+1], d->data, d->block[brlvl], pos, sec_pix, chan_stride);
							break;	case DQT_TEST1:			dqsb_drawgradienttest(d->block[brlvl], pos, sec_pix, chan_stride);
							*/break;
						}
					}

					dqs_block_to_srgb(&d->srgb[bpos.y*d->r_pitch + bpos.x], d->block[0], d->r_pitch, d->srgb_order, out_dim, ss, chan_stride);
				}
			}

		d->timing->thread_end = get_time_hr();

		rl_mutex_unlock(&d->proc_mtx);
		rl_mutex_lock(&d->cont_mtx);		// Wait to be allowed to continue by drawq_soft_finish
		rl_mutex_unlock(&d->cont_mtx);
	}

#endif
	return 0;
}

void drawq_soft_run()
{
	int i, r_pitch=0;

	// Init once
	if (dqs_data==NULL)
	{
		dqs_data = calloc(DQS_THREADS, sizeof(drawq_soft_data_t));

		for (i=0; i < DQS_THREADS; i++)
		{
			drawq_soft_data_t *d = &dqs_data[i];

			// Init everything permanent
			d->thread_on = 1;
			rl_mutex_init(&d->proc_mtx);
			rl_mutex_init(&d->cont_mtx);
			d->thread_id = i;
			d->thread_count = DQS_THREADS;
			d->block = (float **) calloc_2d(4, 1 << 2*fb->sector_size, 4*sizeof(float));	// alloc float blocks once, one block per bracket level

			// Create thread
			rl_mutex_lock(&d->proc_mtx);		// lock proc_mtx so the thread has to wait to proceed
			rl_mutex_lock(&d->cont_mtx);
			rl_thread_create(&d->thread_handle, drawq_soft_thread, d);
			rl_mutex_lock(&d->cont_mtx);		// double lock cont_mtx so we can't go on until the thread unlocks it
			rl_mutex_unlock(&d->cont_mtx);
		}
	}

	// Acquire destination texture
	#ifdef RL_SDL
	fb->tex_lock = 1;
	SDL_LockTexture(fb->texture, NULL, &fb->r.srgb, &r_pitch);
	#endif
	r_pitch /= sizeof(srgb_t);

	for (i=0; i < DQS_THREADS; i++)
	{
		drawq_soft_data_t *d = &dqs_data[i];
		drawq_soft_data_t *d0 = &dqs_data[0];

		// Realloc and copy data
		if (i==0)
		{
			alloc_enough_and_copy(&d->data, fb->data, fb->data_cl_as, &d->data_as, 1, 1.);
			alloc_enough_and_copy(&d->drawq_data, fb->drawq_data, fb->drawq_data[DQ_END], &d->drawq_as,  sizeof(int32_t), 1.5);
			alloc_enough_and_copy(&d->sector_pos, fb->sector_pos, fb->sectors, &d->sector_list_as,       sizeof(int32_t), 1.5);
			alloc_enough_and_copy(&d->entry_list, fb->entry_list, fb->entry_list_end, &d->entry_list_as, sizeof(int32_t), 1.5);
		}
		else
		{
			d->data = d0->data;
			d->drawq_data = d0->drawq_data;
			d->sector_pos = d0->sector_pos;
			d->entry_list = d0->entry_list;
		}

		d->sector_size = fb->sector_size;
		d->sector_w = fb->sector_w;
		d->timing = &fb->timing[fb->timing_index];

		d->srgb = fb->r.srgb;
		d->r_dim = fb->r.dim;
		d->srgb_order = fb->srgb_order;
		d->r_pitch = r_pitch;

		d->current_locks++;
		rl_mutex_lock(&d->cont_mtx);	// will make the thread stop after processing is done
		rl_mutex_unlock(&d->proc_mtx);	// this makes the thread start processing this frame
	}

	fb->timing[fb->timing_index].cl_copy_end = get_time_hr();

	fb->timing[fb->timing_index].cl_enqueue_end = get_time_hr();
}

void drawq_soft_finish()
{
	int i;

	if (dqs_data==NULL)
		return ;

	for (i=0; i < DQS_THREADS; i++)
	{
		drawq_soft_data_t *d = &dqs_data[i];

		if (d)
		if (d->current_locks==1)
		{
			d->current_locks--;
			rl_mutex_lock(&d->proc_mtx);		// will make the thread wait for drawq_soft_run() to add the new frame data
			rl_mutex_unlock(&d->cont_mtx);		// makes the thread complete the loop and wait for proc_mtx
			//rl_thread_join_and_null(&d->thread_handle);
		}
	}
}

void drawq_soft_quit()
{
	int i;

	if (dqs_data==NULL)
		return ;

	for (i=0; i < DQS_THREADS; i++)
	{
		drawq_soft_data_t *d = &dqs_data[i];

		if (d)
		{
			d->thread_on = 0;
			rl_mutex_unlock(&d->cont_mtx);
			rl_thread_join_and_null(&d->thread_handle);
		}
	}
}
