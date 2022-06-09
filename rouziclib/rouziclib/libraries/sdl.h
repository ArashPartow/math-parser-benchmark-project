#ifdef RL_SDL

#ifdef _MSC_VER
#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")
#endif

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_opengl.h>

typedef struct
{
	char **path;
	int path_as, id_last;
} dropfile_t;

extern dropfile_t dropfile;

extern SDL_Rect make_sdl_rect(int x, int y, int w, int h);
extern SDL_Rect recti_to_sdl_rect(recti_t ri);
extern int sdl_get_window_hz(SDL_Window *window);
extern int sdl_vsync_sleep(SDL_Window *window, uint32_t time_last_vsync);
extern recti_t sdl_get_window_rect(SDL_Window *window);
extern void sdl_set_window_rect(SDL_Window *window, recti_t r);
extern xyi_t sdl_get_display_dim(int display_id);
extern recti_t sdl_get_display_rect(int display_id);
extern recti_t sdl_get_display_usable_rect(int display_id);
extern recti_t sdl_screen_max_window_rect();
extern xyi_t sdl_screen_max_window_size();
extern recti_t sdl_get_window_border(SDL_Window *window);
extern int sdl_find_point_within_display(xyi_t p);
extern int sdl_get_window_cur_display();
extern int sdl_is_window_maximised(SDL_Window *window);
#ifdef _WIN32
extern HWND sdl_get_window_hwnd(SDL_Window *window);
#endif

extern void sdl_update_mouse(SDL_Window *window, mouse_t *mouse);
extern void sdl_mouse_event_proc(mouse_t *mouse, SDL_Event event, zoom_t *zc);
extern void sdl_keyboard_event_proc(mouse_t *mouse, SDL_Event event);
extern void sdl_set_mouse_pos_screen(xy_t pos);
extern void sdl_set_mouse_pos_world(xy_t world_pos);

extern int get_sdl_renderer_index(const char *name);
extern int get_sdl_opengl_renderer_index();
extern SDL_GLContext init_sdl_gl(SDL_Window *window);
extern void sdl_graphics_init_full(const char *window_name, xyi_t dim, xyi_t pos, int flags);
extern void sdl_graphics_init_autosize(const char *window_name, int flags, int window_index);
extern int sdl_handle_window_resize(zoom_t *zc);
extern void sdl_flip_fb();
extern void sdl_flip_fb_srgb(srgb_t *sfb);
extern int sdl_toggle_borderless_fullscreen();
extern void sdl_quit_actions();

extern void sdl_init_audio_not_wasapi();
extern char *sdl_get_clipboard_dos_conv();
extern void sdl_print_sdl_version();
extern void sdl_box_printf(const char *title, const char *format, ...);
extern void dropfile_event_proc(SDL_Event event);
extern int dropfile_get_count();
extern char *dropfile_pop_first();

typedef struct
{
	const char *window_name;
	void (*func)();
	int use_drawq, maximise_window, gui_toolbar;
	xyi_t wind_dim, wind_pos;
} sdl_main_param_t;

extern void rl_sdl_standard_main_loop(sdl_main_param_t param);

#endif
