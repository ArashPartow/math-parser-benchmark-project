#ifdef RL_SDL

#include <SDL_syswm.h>

SDL_Rect make_sdl_rect(int x, int y, int w, int h)
{
	SDL_Rect rs;

	rs.x = x;
	rs.y = y;
	rs.w = w;
	rs.h = h;

	return rs;
}

SDL_Rect recti_to_sdl_rect(recti_t ri)
{
	ri = sort_recti(ri);
	return make_sdl_rect(ri.p0.x, ri.p0.y, ri.p1.x - ri.p0.x + 1, ri.p1.y - ri.p0.y + 1);
}

// Display/window
int sdl_get_window_hz(SDL_Window *window)
{
	SDL_DisplayMode mode;

	if (SDL_GetWindowDisplayMode(window, &mode) < 0)
		fprintf_rl(stderr, "SDL_GetWindowDisplayMode failed: %s\n", SDL_GetError());

	return mode.refresh_rate;
}

int sdl_vsync_sleep(SDL_Window *window, uint32_t time_last_vsync)
{
	int hz = sdl_get_window_hz(window);				// refresh rate (e.g. 60 Hz)
	int ms = (100000 / hz - 60) / 100;	// total time needed (e.g. 60 Hz -> 16 ms)
	int elapsed = SDL_GetTicks() - time_last_vsync;			// ms since last vsync
	int delay = ms - elapsed;

	if (delay > 0)			// if sleeping is needed
		SDL_Delay(delay);

	return delay;
}

recti_t sdl_get_window_rect(SDL_Window *window)
{
	recti_t r;

	SDL_GetWindowSize(window, &r.p1.x, &r.p1.y);
	SDL_GetWindowPosition(window, &r.p0.x, &r.p0.y);
	r.p1 = sub_xyi(add_xyi(r.p0, r.p1), set_xyi(1));

	return r;
}

void sdl_set_window_rect(SDL_Window *window, recti_t r)
{
	SDL_SetWindowSize(window, get_recti_dim(r).x, get_recti_dim(r).y);
	SDL_SetWindowPosition(window, r.p0.x, r.p0.y);
}

xyi_t sdl_get_display_dim(int display_id)
{
	SDL_DisplayMode mode={0};

	if (SDL_GetCurrentDisplayMode(display_id, &mode)==0)
		return xyi(mode.w, mode.h);

	return xyi(-1, -1);
}

recti_t sdl_get_display_rect(int display_id)
{
	SDL_Rect r;

	if (display_id < SDL_GetNumVideoDisplays())
		if (SDL_GetDisplayBounds(display_id, &r)==0)
			return recti( xyi(r.x, r.y), xyi(r.x+r.w-1, r.y+r.h-1));

	return recti(xyi(0,0), xyi(0,0));
}

recti_t sdl_get_display_usable_rect(int display_id)
{
	SDL_Rect r;

	if (display_id < SDL_GetNumVideoDisplays())
		if (SDL_GetDisplayUsableBounds(display_id, &r)==0)
			return recti( xyi(r.x, r.y), xyi(r.x+r.w-1, r.y+r.h-1));

	return recti(xyi(0,0), xyi(0,0));
}

recti_t sdl_screen_max_window_rect()
{
	int i;
	recti_t dr, wr=recti(xyi(0,0), xyi(0,0));

	for (i=0; i < SDL_GetNumVideoDisplays(); i++)
	{
		dr = sdl_get_display_rect(i);
		wr.p0 = min_xyi(wr.p0, dr.p0);
		wr.p1 = max_xyi(wr.p1, dr.p1);
	}

	return wr;
}

xyi_t sdl_screen_max_window_size()
{
	return get_recti_dim(sdl_screen_max_window_rect());
}

recti_t sdl_get_window_border(SDL_Window *window)
{
	recti_t r;

	SDL_GetWindowBordersSize(window, &r.p0.y, &r.p0.x, &r.p1.y, &r.p1.x);

	return r;
}

int sdl_find_point_within_display(xyi_t p)
{
	int i;

	for (i=0; i < SDL_GetNumVideoDisplays(); i++)
		if (check_point_within_box_int(p, sdl_get_display_rect(i)))
			return i;

	return -1;
}

int sdl_get_window_cur_display()	// determined by the max pixel area in a display
{
	int i, area, max_area=0, display_index=0;

	for (i=0; i < SDL_GetNumVideoDisplays(); i++)
	{
		area = mul_x_by_y_xyi(get_recti_dim(recti_intersection(sdl_get_window_rect(fb.window), sdl_get_display_rect(i))));

		if (max_area < area)
		{
			max_area = area;
			display_index = i;
		}
	}

	return display_index;
}

int sdl_is_window_maximised(SDL_Window *window)
{
	return SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED;
}

#ifdef _WIN32
HWND sdl_get_window_hwnd(SDL_Window *window)
{
	SDL_SysWMinfo wmInfo;

	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	return wmInfo.info.win.window;
}
#endif

// Mouse/keyboard input
void sdl_update_mouse(SDL_Window *window, mouse_t *mouse)	// gives the mouse position wrt the window coordinates, even outside the window
{
	xyi_t mpos, wpos, wdim;
	recti_t wr;
	int inside_window, but_state;

	but_state = SDL_GetGlobalMouseState(&mpos.x, &mpos.y);	// 1 = lmb, 2 = mmb, 4 = rmb
	wr = sdl_get_window_rect(fb.window);

	#ifdef __EMSCRIPTEN__					// emscripten doesn't have SDL_GetGlobalMouseState
	but_state = SDL_GetMouseState(&mpos.x, &mpos.y);
	wr.p1 = sub_xyi(wr.p1, wr.p0);
	wr.p0 = XYI0;
	#endif

	inside_window = check_point_within_box_int(mpos, wr);

	if (inside_window && mouse->mouse_focus_flag <= 0)	// if the mouse just entered the window
		mouse->mouse_focus_flag = 2;

	if (inside_window==0 && mouse->mouse_focus_flag >= 0)	// if the mouse just left the window
		mouse->mouse_focus_flag = -2;

	if (mouse->warp_if_move && is0_xy(mouse->d)==0)
	{
		mouse->showcursor = -1;
		mouse->warp = 1;
	}

	if (mouse->warp==0)
		mouse->a = xyi_to_xy(sub_xyi(mpos, wr.p0));

	if (mouse->mouse_focus_flag <= 0)	// only process global buttons if the mouse is outside the window
	{
		mouse_button_update(&mouse->b.lmb, &mouse->b.lmf, get_bit(but_state, 0), 0, mouse);
		mouse_button_update(&mouse->b.rmb, &mouse->b.rmf, get_bit(but_state, 2), 2, mouse);
	}
	mouse_button_update(&mouse->b.mmb, &mouse->b.mmf, get_bit(but_state, 1), 1, mouse);
}

void sdl_mouse_event_proc(mouse_t *mouse, SDL_Event event, zoom_t *zc)
{
	SDL_Keymod mod_state;

	if (event.type==SDL_DROPBEGIN)
		SDL_RaiseWindow(fb.window);

	if (event.type==SDL_WINDOWEVENT)
	{
		// SDL bug: SDL_WINDOWEVENT_ENTER and SDL_WINDOWEVENT_LEAVE aren't always triggered when holding the mouse button down
		/*if (event.window.event==SDL_WINDOWEVENT_ENTER)
			mouse->mouse_focus_flag = 2;

		if (event.window.event==SDL_WINDOWEVENT_LEAVE)
			mouse->mouse_focus_flag = -2;*/

		if (event.window.event==SDL_WINDOWEVENT_FOCUS_GAINED)
			mouse->window_focus_flag = 2;

		if (event.window.event==SDL_WINDOWEVENT_FOCUS_LOST)
			mouse->window_focus_flag = -2;

		if (event.window.event==SDL_WINDOWEVENT_MINIMIZED)
			mouse->window_minimised_flag = 2;

		if (event.window.event==SDL_WINDOWEVENT_RESTORED)
			mouse->window_minimised_flag = -2;
	}

	if (event.type==SDL_MOUSEMOTION)
	{
		if (mouse->discard_warp_first_move==0 || abs(event.motion.xrel)+abs(event.motion.yrel) < 40)
			mouse->d = add_xy(mouse->d, xy(event.motion.xrel, event.motion.yrel));			// only works when the cursor is inside the window or with mouse.warp
		mouse->discard_warp_first_move = 0;
	}

	// Mouse button events
	if (event.type==SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button==SDL_BUTTON_LEFT)
			mouse_button_event(&mouse->b.lmb, &mouse->b.lmf, 1);

		if (event.button.button==SDL_BUTTON_RIGHT)
			mouse_button_event(&mouse->b.rmb, &mouse->b.rmf, 1);

		if (event.button.button==SDL_BUTTON_MIDDLE)
			mouse_button_event(&mouse->b.mmb, &mouse->b.mmf, 1);

		if (event.button.clicks)
			mouse->b.clicks = event.button.clicks;
	}

	if (event.type==SDL_MOUSEBUTTONUP)
	{
		if (event.button.button==SDL_BUTTON_LEFT)
			mouse_button_event(&mouse->b.lmb, &mouse->b.lmf, -1);

		if (event.button.button==SDL_BUTTON_RIGHT)
			mouse_button_event(&mouse->b.rmb, &mouse->b.rmf, -1);

		if (event.button.button==SDL_BUTTON_MIDDLE)
			mouse_button_event(&mouse->b.mmb, &mouse->b.mmf, -1);
	}

	if (event.type==SDL_MOUSEWHEEL)
	{
		#ifdef __EMSCRIPTEN__
		event.wheel.y /= abs(event.wheel.y);		// emscripten reports crazy values like 3 or 100 instead of 1, that fixes it
		#endif
		mouse->b.wheel += event.wheel.y;

		zoom_wheel(zc, mouse->zoom_flag, event.wheel.y);
	}

	// state of modifier keys
	mod_state = SDL_GetModState();

	mouse->mod_key[mouse_mod_ctrl] = mod_state & KMOD_CTRL;
	mouse->mod_key[mouse_mod_alt] = mod_state & KMOD_ALT;
	mouse->mod_key[mouse_mod_shift] = mod_state & KMOD_SHIFT;
	mouse->mod_key[mouse_mod_gui] = mod_state & KMOD_GUI;
}

void sdl_keyboard_event_proc(mouse_t *mouse, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
		keyboard_button_event(&mouse->key_state[event.key.keysym.scancode], &mouse->key_quick[event.key.keysym.scancode], 1, event.key.repeat);

	if (event.type == SDL_KEYUP)
		keyboard_button_event(&mouse->key_state[event.key.keysym.scancode], &mouse->key_quick[event.key.keysym.scancode], -1, event.key.repeat);

	if (event.type == SDL_TEXTINPUT)
		textedit_add(cur_textedit, event.text.text);
}

void sdl_set_mouse_pos_screen(xy_t pos)
{
	SDL_WarpMouseInWindow(NULL, nearbyint(pos.x), nearbyint(pos.y));
}

void sdl_set_mouse_pos_world(xy_t world_pos)
{
	sdl_set_mouse_pos_screen(sc_xy(world_pos));
	mouse.u = world_pos;
}

// Window/graphics
int get_sdl_renderer_index(const char *name)
{
	int i, n;
	SDL_RendererInfo info;

	n = SDL_GetNumRenderDrivers();

	for (i=0; i<n; i++)
	{
		SDL_GetRenderDriverInfo(i, &info);

		if (strcmp(name, info.name)==0)
			return i;
	}

	return -1;
}

int get_sdl_opengl_renderer_index()
{
	int index;

	index = get_sdl_renderer_index("opengl");

	if (index==-1)
	{
		index = get_sdl_renderer_index("opengles2");

		if (index==-1)
			fprintf_rl(stderr, "OpenGL renderer not found, fell back to default (in get_sdl_opengl_renderer_index())\n");
		else
			fprintf_rl(stderr, "OpenGL renderer not found, fell back to OpenGLES2 (in get_sdl_opengl_renderer_index())\n");
	}

	return index;
}

SDL_GLContext init_sdl_gl(SDL_Window *window)
{
	SDL_GLContext ctx=NULL;
#ifdef RL_OPENCL_GL
	GLenum glewError;

	ctx = SDL_GL_CreateContext(window);		// Create context
	if (ctx==NULL)
	{
		fprintf_rl(stderr, "OpenGL context could not be created. SDL Error: %s\n", SDL_GetError());
		return ctx;
	}

	// initialize GLEW
	glewExperimental = 1; 
	glewError = glewInit();
	if (glewError != GLEW_OK)
		fprintf_rl(stderr, "Error initializing GLEW. %s\n", glewGetErrorString(glewError));

#endif
	return ctx;
}

// Things required by SetProcessDpiAwareness
#ifdef _WIN32
#include <shellscalingapi.h>
#ifdef _MSC_VER
#pragma comment (lib, "Shcore.lib")
#endif
#endif

void sdl_graphics_init_full(const char *window_name, xyi_t dim, xyi_t pos, int flags)
{
	static int init=1;
	SDL_DisplayMode dm;

	if (init)
	{
		init = 0;
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO))
			fprintf_rl(stderr, "SDL_Init failed: %s\n", SDL_GetError());

		#ifdef __EMSCRIPTEN__
		em_mmb_capture();		// captures the mouse correctly on a middle-click
		#endif
	}

	SDL_SetHint(SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS, "4");

	// Window
	fb.w = dim.x;
	fb.h = dim.y;

	fb.maxdim = sdl_screen_max_window_size();

	// FIXME SDL_WINDOW_MAXIMIZED flag should probably be dealt with because it doesn't work well with the maxdim initialisation

	// DPI awareness
	flags |= SDL_WINDOW_ALLOW_HIGHDPI;
	#ifdef _WIN32
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	#endif

	fb.window = SDL_CreateWindow (	window_name,			// window title
					-fb.maxdim.x-100,		// initial x position
					SDL_WINDOWPOS_UNDEFINED,	// initial y position
					fb.maxdim.x,			// width, in pixels
					fb.maxdim.y,			// height, in pixels
				#ifdef RL_VULKAN
					SDL_WINDOW_VULKAN | flags	// flags - see https://wiki.libsdl.org/SDL_CreateWindow
				#else
					SDL_WINDOW_OPENGL | flags	// flags - see https://wiki.libsdl.org/SDL_CreateWindow
				#endif
			);

	if (fb.window==NULL)
		fprintf_rl(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());

	// Check that the requested mode can work
	if (fb.use_drawq==1)
	{
		#ifndef RL_OPENCL
		fb.use_drawq = 2;
		#else
		if (check_opencl()==0)
			fprintf_rl(stderr, "In sdl_graphics_init_full(): Cannot render using the OpenCL draw queue\n");
		#endif
	}

	if (fb.use_drawq==2)
		if (check_ssse3()==0 || check_sse41()==0)
		{
			fprintf_rl(stderr, "In sdl_graphics_init_full(): Cannot render using the software draw queue on a CPU that lacks SSSE3 or SSE4.1. Go buy a new computer, this ancient wreck is unworthy of running my code.\n");
			fb.use_drawq = 0;
		}

	// Renderer and texture
	if (fb.use_drawq==1)
	{
		#ifdef RL_VULKAN
		vk_init();

		if (SDL_Vulkan_CreateSurface(fb.window, fb.vk.instance, &fb.vk.surface) == 0)
			fprintf_rl(stderr, "SDL_Vulkan_CreateSurface failed: %s\n", SDL_GetError());
		#else
		#ifdef RL_OPENCL_GL
		fb.gl_ctx = init_sdl_gl(fb.window);
		fb.renderer = SDL_CreateRenderer(fb.window, get_sdl_opengl_renderer_index(), SDL_RENDERER_PRESENTVSYNC);
		if (fb.renderer==NULL)
			fprintf_rl(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
		#endif
		#endif
	}
	else
	{
		fb.renderer = SDL_CreateRenderer(fb.window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (fb.renderer==NULL)
			fprintf_rl(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());

		fb.texture = SDL_CreateTexture(fb.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, fb.w, fb.h);
		if (fb.texture==NULL)
			fprintf_rl(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());

		fb.srgb_order = ORDER_BGRA;

		if (fb.use_drawq==0)
			fb.r = make_raster(NULL, XYI0, fb.maxdim, fb.r.use_frgb ? IMAGE_USE_FRGB : IMAGE_USE_LRGB);
		// fb.r.srgb doesn't need to be allocated if it points to the SDL surface thanks to SDL_LockTexture
	}

	if (fb.use_drawq)
	{
		#ifdef RL_OPENCL
		if (fb.use_drawq==1)
			init_fb_cl();
		#endif

		drawq_alloc();
	}

	SDL_SetWindowSize(fb.window, fb.w, fb.h);
	SDL_GetWindowSize(fb.window, &fb.w, &fb.h);
	#ifndef __APPLE__	// see https://bugzilla.libsdl.org/show_bug.cgi?id=4401
	SDL_SetWindowPosition(fb.window, pos.x, pos.y);
	#endif
	fb.r.dim = xyi(fb.w, fb.h);

	// focus flags, useless since SDL_WINDOW_INPUT_FOCUS is always on when it shouldn't be
/*	mouse.mouse_focus_flag = 1;
	mouse.window_focus_flag = 1;
	mouse.window_minimised_flag = -1;

	if ((SDL_GetWindowFlags(fb.window) & SDL_WINDOW_MOUSE_FOCUS)==0)
		mouse.mouse_focus_flag = -1;

	if ((SDL_GetWindowFlags(fb.window) & SDL_WINDOW_INPUT_FOCUS)==0)
		mouse.window_focus_flag = -1;

	if (SDL_GetWindowFlags(fb.window) & SDL_WINDOW_MINIMIZED)
		mouse.window_minimised_flag = 1;

	fprintf_rl(stdout, "mouse %d focus %d minimised %d\n", mouse.mouse_focus_flag, mouse.window_focus_flag, mouse.window_minimised_flag);*/

	#ifdef __EMSCRIPTEN__
	SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#screen");
	#endif
}

void sdl_graphics_init_autosize(const char *window_name, int flags, int window_index)
{
	recti_t r;

	if (SDL_Init(SDL_INIT_VIDEO))
		fprintf_rl(stderr, "SDL_Init failed: %s\n", SDL_GetError());

	r = sdl_get_display_usable_rect(window_index);
	r = recti_add_margin(r, xyi(-8, -16));
	r.p0.y += 14;
	sdl_graphics_init_full(window_name, get_recti_dim(r), r.p0, flags);	// initialise SDL as well as the framebuffer
}

int sdl_handle_window_resize(zoom_t *zc)
{
	int w, h;

	SDL_GetWindowSize(fb.window, &w, &h);

	if (fb.w == w && fb.h == h)
		return 0;

	#ifdef RL_OPENCL_GL
	if (fb.use_drawq==1)
		clFinish_wrap(fb.clctx.command_queue);	// wait for end of queue
	#endif

	if (fb.use_drawq==2)
		drawq_soft_finish();

	fb.w = w;
	fb.h = h;
	fb.r.dim = xyi(fb.w, fb.h);

	int remake_tex = 1;
	#ifdef RL_OPENCL_GL
	if (fb.use_drawq==1)
		remake_tex = 0;
	#endif

	if (remake_tex)
	{
		if (fb.tex_lock)
		{
			SDL_UnlockTexture(fb.texture);
			fb.tex_lock = 0;
		}

		SDL_DestroyTexture(fb.texture);

		fb.texture = SDL_CreateTexture(fb.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, fb.w, fb.h);
		if (fb.texture==NULL)
			fprintf_rl(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());

		// Blank the resized texture
		int pitch;
		SDL_LockTexture(fb.texture, NULL, &fb.r.srgb, &pitch);
		memset(fb.r.srgb, 0, pitch * fb.r.dim.y);
		SDL_UnlockTexture(fb.texture);
	}

	calc_screen_limits(zc);

	return 1;
}

void sdl_flip_fb()
{
	if (fb.timing==NULL)
		fb.timing = calloc(fb.timing_as = fb.timing_count = 120, sizeof(frame_timing_t));
	fb.timing[fb.timing_index].func_end = get_time_hr();

	if (fb.use_drawq==1)
	{
		#ifdef RL_OPENCL
		if (fb.first_frame_done && mouse.window_minimised_flag <= 0)
		{
			cl_int ret=0;
			#ifdef RL_OPENCL_GL
			if (fb.opt_interop)
			{
				ret = clEnqueueReleaseGLObjects_wrap(fb.clctx.command_queue, 1, &fb.cl_srgb, 0, 0, NULL);		// release the ownership (back to GL)
				CL_ERR_NORET("clEnqueueReleaseGLObjects in sdl_flip_fb()", ret);
			}
			#endif

			// display srgb
			if (fb.opt_clfinish)
			{
				ret = clFinish_wrap(fb.clctx.command_queue);
				CL_ERR_NORET("clFinish in sdl_flip_fb()", ret);
			}

			#ifdef RL_OPENCL_GL
			float hoff = 2. * (fb.h - fb.maxdim.y) / (double) fb.maxdim.y;
			glLoadIdentity();             // Reset the projection matrix
			glViewport(0, 0, fb.maxdim.x, fb.maxdim.y);

			glBegin(GL_QUADS);
			float tscale = 1.f;
			glTexCoord2f(0.f, 0.f);			glVertex2f(-1., 1.+hoff);
			glTexCoord2f(tscale*1.f, 0.f);		glVertex2f(1., 1.+hoff);
			glTexCoord2f(tscale*1.f, tscale*1.f);	glVertex2f(1., -1.+hoff);
			glTexCoord2f(0.f, tscale*1.f);		glVertex2f(-1., -1.+hoff);
			glEnd();

			SDL_GL_SwapWindow(fb.window);

			fb.timing[fb.timing_index].flip_end = get_time_hr();

			#else

			if (fb.tex_lock)
			{
				SDL_UnlockTexture(fb.texture);
				fb.tex_lock = 0;
			}

			SDL_RenderClear(fb.renderer);
			SDL_RenderCopy(fb.renderer, fb.texture, NULL, NULL);
			SDL_RenderPresent(fb.renderer);
			#endif
		}
		fb.first_frame_done = 1;
		#endif
	}

	if (fb.use_drawq==2)
	{
		if (fb.first_frame_done)
		{
			drawq_soft_finish();

			if (fb.tex_lock)
			{
				SDL_UnlockTexture(fb.texture);
				fb.tex_lock = 0;
			}

			SDL_RenderClear(fb.renderer);
			SDL_RenderCopy(fb.renderer, fb.texture, NULL, NULL);
			SDL_RenderPresent(fb.renderer);
			fb.timing[fb.timing_index].flip_end = get_time_hr();
		}
		fb.first_frame_done = 1;
	}

	if (fb.use_drawq)
	{
		if (mouse.window_minimised_flag <= 0)
			drawq_run();
		else				// if the window is minimised just don't do any drawq stuff
		{
			drawq_reinit();
			SDL_Delay(80);		// there's no more vsync therefore the loop can easily run at 500+ FPS without the delay
		}
	}
	else
	{
		// Blits framebuffer to screen
		int pitch;
		SDL_Rect rs;
		rs = make_sdl_rect(0, 0, fb.w, fb.h);
		SDL_LockTexture(fb.texture, &rs, &fb.r.srgb, &pitch);
		#ifdef LRGB_NODITHER
		convert_linear_rgb_to_srgb(NODITHER);
		#else
		convert_linear_rgb_to_srgb(DITHER);
		#endif
		SDL_UnlockTexture(fb.texture);
		//SDL_UpdateTexture(fb.texture, NULL, fb.srgb, fb.w * 4);

		SDL_RenderClear(fb.renderer);
		SDL_RenderCopy(fb.renderer, fb.texture, NULL, NULL);
		SDL_RenderPresent(fb.renderer);
		fb.timing[fb.timing_index].interop_sync_end = get_time_hr();
		fb.timing[fb.timing_index].dq_comp_end = get_time_hr();
		fb.timing[fb.timing_index].cl_copy_end = get_time_hr();
		fb.timing[fb.timing_index].cl_enqueue_end = get_time_hr();
		fb.timing[fb.timing_index].flip_end = get_time_hr();

		screen_blank();
	}

	double t = get_time_hr();
	fb.timing[fb.timing_index].end = t;
	fb.timing_index = circ_index(fb.timing_index+1, fb.timing_count);
	fb.timing[fb.timing_index].start = t;
	sleep_hr(rangelimit(fb.start_sleep_dur - t + fb.timing[circ_index(fb.timing_index-1, fb.timing_count)].flip_end, 0., fb.start_sleep_dur));
	fb.timing[fb.timing_index].start_sleep = get_time_hr();

	fb.frame_count++;
}

void sdl_flip_fb_srgb(srgb_t *sfb)
{
	// Blits framebuffer to screen
	int pitch;
	SDL_Rect rs;
	rs = make_sdl_rect(0, 0, fb.w, fb.h);
	SDL_LockTexture(fb.texture, &rs, &fb.r.srgb, &pitch);
	//memcpy(fb.r.srgb, sfb, mul_x_by_y_xyi(fb.r.dim) * sizeof(srgb_t));
	srgb_change_order(sfb, fb.r.srgb, mul_x_by_y_xyi(fb.r.dim), ORDER_BGRA);
	SDL_UnlockTexture(fb.texture);

	SDL_RenderClear(fb.renderer);
	SDL_RenderCopy(fb.renderer, fb.texture, NULL, NULL);
	SDL_RenderPresent(fb.renderer);

	screen_blank();
}

int sdl_toggle_borderless_fullscreen()
{
	fb.fullscreen_on ^= 1;

	if (fb.fullscreen_on)
	{
		fb.wind_rect = sdl_get_window_rect(fb.window);

		SDL_SetWindowResizable(fb.window, SDL_FALSE);
		SDL_SetWindowBordered(fb.window, SDL_TRUE);
		sdl_set_window_rect(fb.window, sdl_get_display_rect(sdl_get_window_cur_display()));
	}
	else
	{
		sdl_set_window_rect(fb.window, fb.wind_rect);

		SDL_SetWindowResizable(fb.window, SDL_TRUE);
		SDL_SetWindowBordered(fb.window, SDL_TRUE);
	}

	#ifdef __EMSCRIPTEN__
	//em_sync_by_mutex(1);
	em_browser_toggle_fullscreen(fb.fullscreen_on);
	//em_sync_by_mutex(1);
	//em_sync_by_mutex(0);
	//if (fb.fullscreen_on == 0)
	//	SDL_SetWindowSize(fb.window, 900, 600);
	fprintf_rl(stdout, "fb.fullscreen_on %d %d\n", fb.fullscreen_on, rand()&63);
	#endif

	sdl_handle_window_resize(&zc);

	return fb.fullscreen_on;
}

void sdl_quit_actions()
{
	#ifdef RL_OPENCL
	if (fb.use_drawq==1)
		deinit_clctx(&fb.clctx, 1);
	#endif

	if (fb.use_drawq==2)
		drawq_soft_quit();

	#ifdef RL_OPENCL_GL
	SDL_GL_DeleteContext(fb.gl_ctx);
	#endif
	SDL_DestroyRenderer(fb.renderer);
	SDL_DestroyWindow(fb.window);
	SDL_Quit();
}

// Audio
void sdl_init_audio_not_wasapi()
{
	int i;

	SDL_AudioQuit();	// quit the current audio driver, probably wasapi

	// Init the first driver that isn't wasapi
	for (i=0; i < SDL_GetNumAudioDrivers(); i++)
		if (strcmp("wasapi", SDL_GetAudioDriver(i)))	// if the driver isn't called "wasapi"
		{
			SDL_AudioInit(SDL_GetAudioDriver(i));	// initialise it
			return ;
		}
}

// Clipboard
char *sdl_get_clipboard_dos_conv()
{
	char *orig, *edited, byte0, byte1=0;
	int i, offset=0, len;

	orig = SDL_GetClipboardText();
	if (orig==NULL)
		return NULL;

	len = strlen(orig);

	edited = calloc (len+1, sizeof(char));

	for (i=0; i < len; i++)
	{
		byte0 = byte1;
		byte1 = orig[i];

		if (byte0=='\r' && byte1=='\n')
			offset++;

		edited[i-offset] = byte1;
	}

	edited = realloc(edited, len-offset+1);
	SDL_free(orig);

	return edited;
}

// Misc
void sdl_print_sdl_version()
{
	SDL_version compiled, linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	fprintf_rl(stdout, "Compilation SDL version %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
	fprintf_rl(stdout, "Linked SDL version %d.%d.%d %s\n", linked.major, linked.minor, linked.patch, SDL_GetRevision());
}

void sdl_box_printf(const char *title, const char *format, ...)
{
	buffer_t s={0};
	va_list args;

	va_start(args, format);
	vbufprintf(&s, format, args);
	va_end(args);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, s.buf, NULL);
	free_buf(&s);
}

// Drag and drop
dropfile_t dropfile={0};

void dropfile_event_proc(SDL_Event event)
{
	if (dropfile.path_as==0)
		dropfile.id_last = -1;

	if (event.type==SDL_DROPFILE)
	{
		dropfile.id_last++;
		alloc_enough((void **) &dropfile.path, dropfile.id_last+1, &dropfile.path_as, sizeof(char *), 1.5);

		dropfile.path[dropfile.id_last] = make_string_copy(event.drop.file);
		SDL_free(event.drop.file);
	}
}

int dropfile_get_count()
{
	int i, count=0;

	if (dropfile.path)
		for (i=0; i <= dropfile.id_last; i++)
			if (dropfile.path[i])
				count++;

	return count;
}

char *dropfile_pop_first()
{
	int i;
	char *p=NULL;

	if (dropfile.path)
		for (i=0; i <= dropfile.id_last; i++)
			if (dropfile.path[i])
			{
				p = dropfile.path[i];
				dropfile.path[i] = NULL;

				if (i==dropfile.id_last)
					dropfile.id_last = -1;

				break;
			}

	return p;
}

void rl_sdl_standard_main_loop(sdl_main_param_t param)
{
	static int exit_flag=0, init=1;
	SDL_Event event;

	if (init)
	{
		init = 0;

		fb.use_drawq = param.use_drawq;	// OpenCL draw queue

		if (is0_xyi(param.wind_dim))
			sdl_graphics_init_autosize(param.window_name, SDL_WINDOW_RESIZABLE, 0);
		else
			sdl_graphics_init_full(param.window_name, param.wind_dim, param.wind_pos, SDL_WINDOW_RESIZABLE);

		if (param.maximise_window)
			SDL_MaximizeWindow(fb.window);

		zc = init_zoom(&mouse, drawing_thickness);
		calc_screen_limits(&zc);
		mouse = init_mouse();

		#ifdef RL_INCL_VECTOR_TYPE_FILEBALL
		vector_font_load_from_header();
		#else
		make_fallback_font(font);
		#endif

		#ifdef __EMSCRIPTEN__
		SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, "#screen");
		#endif
	}

	#ifdef __EMSCRIPTEN__
	#else
	while (exit_flag==0)
	#endif
	{
		//********Input handling********

		mouse_pre_event_proc(&mouse);
		keyboard_pre_event_proc(&mouse);
		sdl_handle_window_resize(&zc);

		while (SDL_PollEvent(&event))
		{
			dropfile_event_proc(event);
			sdl_mouse_event_proc(&mouse, event, &zc);
			sdl_keyboard_event_proc(&mouse, event);

			if (event.type==SDL_QUIT)
				exit_flag = 1;
		}

		if (mouse.key_state[RL_SCANCODE_RETURN] == 2 && get_kb_alt())
			sdl_toggle_borderless_fullscreen();

		textedit_add(cur_textedit, NULL);	// processes the new keystrokes in the current text editor

		mouse_post_event_proc(&mouse, &zc);

		//-------------input-----------------

		param.func();

		if (param.gui_toolbar)
			gui_layout_edit_toolbar(mouse.key_state[RL_SCANCODE_F6]==2);
		window_manager();

		mousecursor_logic_and_draw();

		sdl_flip_fb();
	}
}

#endif
