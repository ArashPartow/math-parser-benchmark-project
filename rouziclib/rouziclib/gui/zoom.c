zoom_t init_zoom(mouse_t *mouse, double drawing_thickness)
{
	zoom_t zc;

	memset(&zc, 0, sizeof(zc));

	zc.zoomscale = 1.;
	zc.mouse = mouse;
	zc.drawing_thickness = drawing_thickness;

	return zc;
}

double to_screen_coord_x(zoom_t zc, double x)
{
	x -= zc.offset_u.x;

	return x * zc.scrscale + 0.5*(double)fb->w - 0.5;
}

double to_screen_coord_y(zoom_t zc, double y)
{
	y -= zc.offset_u.y;
	return -y * zc.scrscale + 0.5*(double)fb->h - 0.5;
}

xy_t to_screen_coord_xy(zoom_t zc, xy_t p)
{
	return xy(to_screen_coord_x(zc, p.x), to_screen_coord_y(zc, p.y));
}

double to_world_coord_x(zoom_t zc, double x)
{
	return (x - 0.5*(double)fb->w + 0.5) * zc.iscrscale + zc.offset_u.x;
}

double to_world_coord_y(zoom_t zc, double y)
{
	return -(y - 0.5*(double)fb->h + 0.5) * zc.iscrscale + zc.offset_u.y;
}

xy_t to_world_coord_xy(zoom_t zc, xy_t p)
{
	return xy(to_world_coord_x(zc, p.x), to_world_coord_y(zc, p.y));
}

rect_t to_screen_coord_rect(zoom_t zc, rect_t r)
{
	return rect( sc_xy(r.p0) , sc_xy(r.p1) );
}

rect_t to_world_coord_rect(zoom_t zc, rect_t r)
{
	return rect( wc_xy(r.p0) , wc_xy(r.p1) );
}

void pinned_os_to_world_os(xy_t pinned_offset, double pinned_sm, xy_t *world_offset, double *world_sm)
{
	*world_sm = pinned_sm / zc.zoomscale;
	*world_offset = mad_xy(set_xy(*world_sm), pinned_offset, zc.offset_u);
}

void world_os_to_pinned_os(xy_t world_offset, double world_sm, xy_t *pinned_offset, double *pinned_sm)
{
	*pinned_sm = world_sm * zc.zoomscale;
	*pinned_offset = div_xy(sub_xy(world_offset, zc.offset_u), set_xy(world_sm));
}

void zoom_toggle(zoom_t *zc, int *flag_zoom_key)
{
	*flag_zoom_key ^= 1;		// toggle zoom

	if (*flag_zoom_key==0)		// if the cursor is to be shown and we switched from zoom on to zoom off
	{
		// Uncapture and move cursor to the centre of the screen
		#ifdef RL_SDL
		SDL_SetRelativeMouseMode(0);
		SDL_WarpMouseInWindow(fb->window, fb->w/2, fb->h/2);
		#endif
		zc->mouse->a = xy(fb->w/2, fb->h/2);
		zc->mouse->u = to_world_coord_xy(*zc, zc->mouse->a);

		#ifdef __EMSCRIPTEN__
		em_release_cursor();
		#endif
	}

	calc_screen_limits(zc);
}

void zoom_reset(zoom_t *zc, int *flag_zoom_key)
{
	zc->zoomscale = 1.;
	zc->offset_u = XY0;
	zc->offset_uq = XYQ0;
	zc->just_reset = 1;
	zc->zoom_key_time = 0;

	if (*flag_zoom_key == 1)
		zoom_toggle(zc, flag_zoom_key);
	else
		calc_screen_limits(zc);
}

void zoom_key_released(zoom_t *zc, int *flag_zoom_key, int source)	// source 1 is when the button is released, source 2 is while the button is being held down
{
	int td;
	int zko = *flag_zoom_key;						// save the original zoom_key state

	td = get_time_ms() - zc->zoom_key_time;					// time difference

	if (source==1 && *flag_zoom_key==0 && zc->zoom_key_time)		// if the button was just released as the zoom was off and the timer running
		zoom_toggle(zc, flag_zoom_key);					// turn the zoom on
	else if (source==1 && *flag_zoom_key && zc->zoom_key_time && td <= 500)	// if the button has been pressed for less than 0.5s and released
		zoom_toggle(zc, flag_zoom_key);					// turn off the zoom mode, don't reset the view

	if (source==2 && zc->zoom_key_time && td > 500)				// if the button is held down and for more than 0.5s and the button timer is running
		zoom_reset(zc, flag_zoom_key);					// reset everything
}

void zoom_wheel(zoom_t *zc, int flag_zoom_key, int y)
{
	double ratio;

	if (flag_zoom_key)			// if the zoom key is down
	{
		ratio = pow(2., 1./2. * (double) y);
		zc->zoomscale *= ratio;

		//zc->offset_u = sub_xy(zc->mouse->u, div_xy(sub_xy(zc->mouse->u, zc->offset_u), set_xy(ratio)));	// zoom using the cursor position as an anchor point

		calc_screen_limits(zc);
	}
}

void calc_screen_limits(zoom_t *zc)
{
	int x, y;

	#ifdef ZOOM_Q
	// offset_u copies offset_uq
	zc->offset_u = xyq_to_xy(zc->offset_uq);
	#endif

	if (3*fb->w > 3*fb->h)				// if widescreen (more than 3:3 (formerly 4:3))
		zc->scrscale = (double) fb->h / 18.;	// for 1920x1080 srcscale would be 60
	else
		zc->scrscale = (double) fb->w / 18.;
	zc->scrscale_unzoomed = zc->scrscale;

	zc->limit_u = mul_xy(xy(fb->w, fb->h), set_xy(0.5/zc->scrscale_unzoomed));

	zc->scrscale *= zc->zoomscale;
	zc->iscrscale = 1. / zc->scrscale;

	zc->drawlim_u = set_xy(zc->iscrscale * GAUSSRAD_HQ * zc->drawing_thickness);

	xy_t dim = mul_xy(xy(fb->w, fb->h), set_xy(0.5*zc->iscrscale));
	zc->corners.p0 = sub_xy(zc->offset_u, dim);
	zc->corners.p1 = add_xy(zc->offset_u, dim);
	zc->corners_dl.p0 = sub_xy(zc->corners.p0, zc->drawlim_u);
	zc->corners_dl.p1 = add_xy(zc->corners.p1, zc->drawlim_u);
	fb->window_dl.p0 = set_xy(-GAUSSRAD_HQ * zc->drawing_thickness);			// drawing limit in pixels
	fb->window_dl.p1 = sub_xy( xy(fb->w-1, fb->h-1), fb->window_dl.p0 );
}

void toggle_guizoom(zoom_t *zc, int on)	// used for temporarily disabling zooming to display objects independently of the zooming system
{
	static double stored_zoomscale=1.;
	static xy_t stored_offset_u;
	static xyq_t stored_offset_uq;

	if (on)
	{
		zc->zoomscale = stored_zoomscale;
		#ifdef ZOOM_Q
		zc->offset_uq = stored_offset_uq;
		#else
		zc->offset_u = stored_offset_u;
		#endif
	}
	else
	{
		stored_zoomscale = zc->zoomscale;
		#ifdef ZOOM_Q
		stored_offset_uq = zc->offset_uq;
		zc->offset_uq = XYQ0;
		#else
		stored_offset_u = zc->offset_u;
		zc->offset_u = XY0;
		#endif

		zc->zoomscale = 1.;
	}

	calc_screen_limits(zc);
}

void change_zoom(xy_t pos, double zoom_scale)
{
	if (isnan_xy(pos)==0)
	{
		zc.offset_u = pos;
		zc.offset_uq = xy_to_xyq(pos);
	}

	if (isnan(zoom_scale)==0)
		zc.zoomscale = zoom_scale;

	calc_screen_limits(&zc);
}

void change_zoom_and_turn_off_zoom_mode(xy_t pos, double zoom_scale)
{
	zc.zoom_key_time = get_time_ms();

	if (mouse.zoom_flag)
		zoom_key_released(&zc, &mouse.zoom_flag, 1);

	change_zoom(pos, zoom_scale);
}

void zoom_keyboard_control(zoom_t *zc, int *flag_zoom_key)
{
	xy_t move_vector=XY0;
	double zoom_way = 0.;
	const double rep_inc=0.25;
	int s;

	if (zc->mouse->zoom_allowed && get_kb_alt())
	{
		// Toggle or reset zoom with (Shift-)Alt-Z or toggle the overlay controls with Ctrl-Alt-Z
		if (zc->mouse->key_state[RL_SCANCODE_Z]==2)
			if (get_kb_shift()==0)
				if (get_kb_ctrl())
					zc->overlay_ctrl ^= 1;
				else
					zoom_toggle(zc, flag_zoom_key);
			else
				zoom_reset(zc, flag_zoom_key);

		// Scroll with Alt-WASD
		if ((s=zc->mouse->key_state[RL_SCANCODE_A]) >= 2)	move_vector.x -= s==2 ? 1. : rep_inc;
		if ((s=zc->mouse->key_state[RL_SCANCODE_D]) >= 2)	move_vector.x += s==2 ? 1. : rep_inc;
		if ((s=zc->mouse->key_state[RL_SCANCODE_S]) >= 2)	move_vector.y -= s==2 ? 1. : rep_inc;
		if ((s=zc->mouse->key_state[RL_SCANCODE_W]) >= 2)	move_vector.y += s==2 ? 1. : rep_inc;

		// Zoom in or out
		if (zc->mouse->key_state[RL_SCANCODE_Q]==2)	zoom_way = -1.;
		if (zc->mouse->key_state[RL_SCANCODE_E]==2)	zoom_way = 1.;
	}

	// Apply the move
	if (is0_xy(move_vector)==0 || zoom_way)
	{
		move_vector = mul_xy(move_vector, set_xy(4./zc->zoomscale));	// move by steps of 4 units
		zc->zoomscale *= pow(2., 1./2. * zoom_way);
		#ifdef ZOOM_Q
		zc->offset_uq = add_xyq(zc->offset_uq, xy_to_xyq(move_vector));
		#else
		zc->offset_u = add_xy(zc->offset_u, move_vector);
		#endif
		calc_screen_limits(zc);
		zc->mouse->u = to_world_coord_xy(*zc, zc->mouse->a);
		zc->mouse->b.orig = zc->mouse->u;
	}
}

void zoom_overlay_control(zoom_t *zc, int *flag_zoom_key)
{
	xy_t move_vector=XY0;
	double zoom_way = 0.;

	if (mouse.window_minimised_flag > 0)
		return;

	// Overlay controls
	if (zc->overlay_ctrl)
	{
		static gui_layout_t layout={0};
		const char *layout_src[] = {
			"v 1	1;3", "",
			"elem 10", "type button", "label \342\207\247", "pos	0	3", "dim	v1", "off	0;6", "",
			"elem 11", "type button", "label \342\207\251", "pos	0	-3", "dim	v1", "off	0;6", "",
			"elem 12", "type button", "label \342\207\246", "pos	-3	0", "dim	v1", "off	0;6", "",
			"elem 13", "type button", "label \342\207\250", "pos	3	0", "dim	v1", "off	0;6", "",
			"elem 20", "type button", "label -", "pos	-2	3", "dim	v1", "off	0;6", "",
			"elem 21", "type button", "label +", "pos	2	3", "dim	v1", "off	0;6", "",
		};

		layout.offset = zc->offset_u;
		layout.sm = 1./zc->zoomscale;
		make_gui_layout(&layout, layout_src, sizeof(layout_src)/sizeof(char *), "Zoom control overlay");

		// Controls
		if (ctrl_button_fromlayout(&layout, 10))	move_vector.y += 1.;
		if (ctrl_button_fromlayout(&layout, 11))	move_vector.y -= 1.;
		if (ctrl_button_fromlayout(&layout, 12))	move_vector.x -= 1.;
		if (ctrl_button_fromlayout(&layout, 13))	move_vector.x += 1.;
		if (ctrl_button_fromlayout(&layout, 20))	zoom_way = -1.;
		if (ctrl_button_fromlayout(&layout, 21))	zoom_way = 1.;
	}

	// Apply the move
	if (is0_xy(move_vector)==0 || zoom_way)
	{
		move_vector = mul_xy(move_vector, set_xy(20./12./zc->zoomscale));	// move by steps of 1;8 units
		zc->zoomscale *= pow(2., 1./2. * zoom_way);
		#ifdef ZOOM_Q
		zc->offset_uq = add_xyq(zc->offset_uq, xy_to_xyq(move_vector));
		#else
		zc->offset_u = add_xy(zc->offset_u, move_vector);
		#endif
		calc_screen_limits(zc);
		zc->mouse->u = to_world_coord_xy(*zc, zc->mouse->a);
		zc->mouse->b.orig = zc->mouse->u;
	}
}
