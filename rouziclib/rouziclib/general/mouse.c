mouse_t init_mouse()
{
	mouse_t mouse;

	memset(&mouse, 0, sizeof(mouse_t));
	mouse.ctrl_id = calloc(1, sizeof(mouse_ctrl_id_t));

	mouse.b.lmb = mouse.b.mmb = mouse.b.rmb = -1;
	mouse.zoom_allowed = 1;

	return mouse;
}

void flag_update_mouse_button(int *mb, mousebut_flags_t *flags)
{
	flag_update(*mb);

	if (flags->quick)
	{
		*mb = flags->quick * 2;
		flags->quick = 0;
	}
}

void mouse_pre_event_proc(mouse_t *mouse)
{
	mouse->d = XY0;
	mouse->prev_u = mouse->u_stored;
	mouse->b.wheel = 0;
	if (mouse->b.lmb <= 0)						// if LMB is being pressed the hovered ID stays the same as before no matter what
		mouse->ctrl_id->hover = mouse->ctrl_id->hover_new;
	memset(&mouse->ctrl_id->hover_new, 0, sizeof(ctrl_id_t));
	memset(&mouse->ctrl_id->current, 0, sizeof(ctrl_id_t));
	mouse->ctrl_id->hover_box_matched = 0;
	mouse->ctrl_id->hover_ided = 0;

	flag_update_mouse_button(&mouse->b.lmb, &mouse->b.lmf);
	flag_update_mouse_button(&mouse->b.mmb, &mouse->b.mmf);
	flag_update_mouse_button(&mouse->b.rmb, &mouse->b.rmf);
	flag_update(mouse->window_focus_flag);
	flag_update(mouse->window_minimised_flag);
	flag_update(mouse->mouse_focus_flag);
	mouse->d = XY0;
}

void mouse_button_event(int *mb, mousebut_flags_t *flags, int way)
{
	#ifdef MOUSE_LOG
	if (*mb * way == -2)
		bufprintf(&mouse.log, "[%d] mouse_button_event() quick press\n", mouse.frame_index);
	else
		bufprintf(&mouse.log, "[%d] mouse_button_event() mb %d -> %d\n", mouse.frame_index, *mb, 2 * way);
	#endif

	if (*mb * way == -2)		// if quick press situation
		flags->quick = way;
	else
	{
		if (*mb != way)		// if not *mb -1 -> -2 (happens when the click release comes from global polling and again later from event polling)
			*mb = 2 * way;
		#ifdef MOUSE_LOG
		else
			bufprintf(&mouse.log, "[%d] mouse_button_event() *mb %d -> %d avoided\n", mouse.frame_index, *mb, 2 * way);
		#endif
	}

	#ifdef MOUSE_LOG
	if (*mb == -2 && flags->block)
		bufprintf(&mouse.log, "[%d] mouse_button_event() released click blocking\n", mouse.frame_index);
	#endif

	if (*mb == -2)			// release click blocking when the click is released
		flags->block = 0;
}

void mouse_button_update(int *mb, mousebut_flags_t *flags, int new_state, int button_index, mouse_t *mouse)	// button index is 0 for lmb, 1 for mmb, 2 for rmb
{
	if (abs(*mb)==2)	// we don't need to update the mouse button state from global polling if the event did it fine
		return;

	if (new_state == 0 && *mb >= 0)		// if the button is being released
	{
		*mb = -2;
		flags->block = 0;

		#ifdef MOUSE_LOG
		bufprintf(&mouse->log, "[%d] mouse_button_update() button released\n", mouse->frame_index);
		#endif
	}

	if (new_state && *mb <= 0)		// if the button is pressed
	{
		if (mouse->window_focus_flag == 2 && (button_index==0 || button_index==2))
			flags->block = 1;

		if (mouse->mouse_focus_flag >= 0 && mouse->window_focus_flag >= 0 && flags->block==0)	// make sure the click is in the window
			*mb = 2;

		#ifdef MOUSE_LOG
		if (mouse->mouse_focus_flag >= 0 && mouse->window_focus_flag >= 0 && flags->block==0)
			bufprintf(&mouse->log, "[%d] mouse_button_update() new click (*mb %d, mouse focus flag %d)\n", mouse->frame_index, *mb, mouse->mouse_focus_flag);
		else
			bufprintf(&mouse->log, "[%d] mouse_button_update() new click blocked (mouse focus %d window focus %d block %d)\n", mouse->frame_index, mouse->mouse_focus_flag, mouse->window_focus_flag, flags->block);
		#endif
	}
}

// see libraries/sdl.c for sdl_mouse_event_proc()

void mouse_post_event_proc(mouse_t *mouse, zoom_t *zc)
{
	zc->just_reset = 0;

	#ifdef RL_SDL
	sdl_update_mouse(fb.window, mouse);
	#endif

	zoom_keyboard_control(zc, &mouse->zoom_flag);

	if (mouse->b.mmb == -2 && mouse->zoom_allowed)
		zoom_key_released(zc, &mouse->zoom_flag, 1);

	if (mouse->b.mmb == 2 && mouse->zoom_allowed)
		zc->zoom_key_time = get_time_ms();

	mouse->u = to_world_coord_xy(*zc, mouse->a);
	xy_t du = mul_xy(neg_y(mouse->d), set_xy(zc->iscrscale));

	if (mouse->zoom_flag && mouse->zoom_scroll_freeze==0)	// if we're scrolling the zoom
	{
		#ifdef ZOOM_Q
		zc->offset_uq = add_xyq(xy_to_xyq(mul_xy(du, set_xy(2.))), zc->offset_uq);
		#else
		zc->offset_u = mad_xy(du, set_xy(2.), zc->offset_u);	// the factor of 2 is arbitrary, doesn't have to be integer
		#endif
		calc_screen_limits(zc);
	}

	// Post-input logic
	#ifdef __EMSCRIPTEN__
	if (mouse->warp != mouse->warp_prev)
	{
		if (mouse->warp)
			em_capture_cursor();
		else
			em_release_cursor();
	}
	#endif

	if (mouse->warp != mouse->warp_prev)	// prevent recording jumps when switching warp modes
		mouse->discard_warp_first_move = 1;

	mouse->warp_prev = mouse->warp;
	if (mouse->warp_if_move==0)
	{
		mouse->showcursor = 0;
		mouse->warp = 0;
	}

	if (mouse->window_focus_flag < 0)
		mouse->warp = 0;

	if (mouse->b.mmb > 0 && mouse->zoom_allowed)		// when to reset the zoom (when MMB is held down)
		zoom_key_released(zc, &mouse->zoom_flag, 2);

	if (mouse->zoom_flag && mouse->window_focus_flag == -2)	// if we left the window while zoom is on
	{
		zc->zoom_key_time = get_time_ms();
		zoom_key_released(zc, &mouse->zoom_flag, 1);
	}

	if (mouse->zoom_flag)
		mouse->u = zc->offset_u;
	mouse->u_stored = mouse->u;			// store mouse->u before it gets changed by temporary zoom changes

	if (mouse->b.clicks==1 && (mouse->b.lmb==2 || mouse->b.rmb==2))		// store the origin of a click
	{
		mouse->b.orig = mouse->u;

		if (mouse->mouse_focus_flag != 1)	// if the mouse focus is regained at the same time as the click this means drag and drop
			mouse->b.orig = set_xy(FLT_MAX); // set the click location far out so it doesn't click on any control
	}

	if (mouse->window_focus_flag == 2)		// if focus was regained through a click
		mouse->b.orig = set_xy(FLT_MAX);	// set the click location far out so it doesn't click on any control

	if (mouse->b.lmb==2)				// on click unselect any text editor
		cur_textedit = NULL;

	#ifdef MOUSE_LOG
	// Write summary
	//bufprintf(&mouse->log, "mouse_post_event_proc() summary:\n\ta %g %g   u %g %g   d %g %g   u_stored %g %g   prev_u %g %g\n", mouse->a.x, mouse->a.y, mouse->u.x, mouse->u.y, mouse->d.x, mouse->d.y, mouse->u_stored.x, mouse->u_stored.y, mouse->prev_u.x, mouse->prev_u.y);

	// Trim and save
	buf_tail(&mouse->log, 120);
	mouse->frame_index++;

	if (mouse->key_state[RL_SCANCODE_F8]==2 && get_kb_shift() && get_kb_cmd())
	{
		// Generate log filename
		buffer_t filename={0};
		bufprintf(&filename, "mouse log ");
		bufprint_gmtime(&filename, time(NULL));
		bufprintf(&filename, ".txt");
		char *path = make_appdata_path("rouziclib", filename.buf, 1);
		free_buf(&filename);

		// Save and open
		buf_save_raw_file(&mouse->log, path, "wb");
		fprintf_rl(stdout, "Mouse log saved to %s\n", path);
		system_open(path);
		free(path);
	}
	#endif

	reset_insert_rect_array();			// nothing to do with the mouse but this is about the right place to put it

	// Drawwing queue discard logic
	if (fb.use_drawq && mouse->window_minimised_flag == 2)
	{
		fb.discard = 1;
		data_cl_realloc(-1);
	}

	if (fb.use_drawq && mouse->window_minimised_flag == -2)
	{
		fb.discard = 0;
		data_cl_realloc(1L << 20);
	}
}

void mousecursor_logic_and_draw()
{
	if (mouse.zoom_flag)
	{
		#ifdef RL_SDL
		SDL_SetRelativeMouseMode(1);
		sdl_set_mouse_pos_world(mouse.u);
		#endif

		if (mouse.showcursor == 1)
			mouse.showcursor = 0;
	}
	else
	{
		#ifdef RL_SDL
		SDL_SetRelativeMouseMode(mouse.warp);

		if (mouse.warp_prev || mouse.warp)		// set the mouse position during warp or after exiting warp mode
			sdl_set_mouse_pos_world(mouse.b.orig);
		#endif
	}

	//if (mouse.window_focus_flag < 0)
	//	mouse.showcursor = 0;

	#ifdef RL_SDL
	SDL_ShowCursor(mouse.showcursor==1);
	#endif
	draw_mousecursor(mouse.u);

	// Zoom overlay control
	zoom_overlay_control(&zc, &mouse.zoom_flag);
}
