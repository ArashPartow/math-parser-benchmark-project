#ifdef __EMSCRIPTEN__

EM_JS(int, em_get_memory_size, (),
{
	return HEAP8.length;
});

EM_JS(void, em_disable_context_menu, (),
{
	document.addEventListener("contextmenu", function(event) {event.preventDefault();}, false);
});

EM_JS(void, em_mmb_capture, (),
{
	document.body.onmousedown = function(e)
	{
		if (e.button === 1)
		{
			canvas.requestPointerLock();
			return false;
		}
	}
});

EM_JS(void, em_capture_cursor, (),
{
	canvas.requestPointerLock();
});

EM_JS(void, em_release_cursor, (),
{
	document.exitPointerLock();
});

void em_sync_by_mutex(int lock)
{
	static int init=1;
	static rl_mutex_t my_mutex;

	if (init)
	{
		init = 0;
		rl_mutex_init(&my_mutex);
	}
fprintf_rl(stdout, "em_sync_by_mutex(%d) %d\n", lock, rand()&63);

	if (lock)
		rl_mutex_lock(&my_mutex);
	else
		rl_mutex_unlock(&my_mutex);
}

/*EM_JS(void, em_browser_toggle_fullscreen, (int state),
{
Asyncify.handleAsync(async () => {
	if (state)
		await canvas.requestFullscreen();
	else
		await em_exit_fullscreen_ret_promise();
});
});*/

EM_JS(void, em_browser_toggle_fullscreen, (int state),
{
	if (state)
		canvas.requestFullscreen();
	else
		em_exit_fullscreen_ret_promise();
});

/*void em_browser_toggle_fullscreen(int state)
{
	if (state)
	{
		EmscriptenFullscreenStrategy strat={0};
		strat.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
		strat.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
		strat.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_NEAREST;
		emscripten_request_fullscreen_strategy(NULL, 1, &strat);
	}
	else
	{
		emscripten_exit_fullscreen();
	}
}*/

void em_fit_canvas_to_innerwindow()
{
	if (fb.fullscreen_on)
		return ;

	SDL_SetWindowSize(fb.window, MINN(fb.maxdim.x, EM_ASM_INT((return window.innerWidth;))), MINN(fb.maxdim.y, EM_ASM_INT((return window.innerHeight;))));
	sdl_handle_window_resize(&zc);
}

EM_JS(void, em_enumerate_av_devices, (),
{
	em_enumerate_av_devices();
});

typedef struct
{
	int id, order;
	char *string;
} em_string_reg_entry_t;

/* IDs:
   1327 (avd): list of audio devices
*/

char *em_string_registry(int id, char *str)
{
	int i, min_order=INT_MAX;
	static em_string_reg_entry_t *entry=NULL;
	static size_t entry_count=0, entry_as=0;
	static int order=0;

	// If we're adding a string
	if (str)
	{
		order++;

		// Look for free entry
		for (i=0; i < entry_count; i++)
			if (entry[i].id == 0)
				goto skip_add1;

		// otherwise add new entry
		i = entry_count;
		alloc_enough(&entry, entry_count+=1, &entry_as, sizeof(em_string_reg_entry_t), 1.5);
skip_add1:
		entry[i].id = id;
		entry[i].string = str;
		entry[i].order = order;
		return str;
	}

	// If we're retrieving a string
	// Find entry with correct ID and lowest order, delete it and return the string
	for (i=0; i < entry_count; i++)
		if (entry[i].id == id && entry[i].order < min_order)
		{
			min_order = entry[i].order;
			str = entry[i].string;
			memset(&entry[i], 0, sizeof(em_string_reg_entry_t));
		}

	return str;
}

#endif
