_Thread_local rect_t cur_parent_area;
_Thread_local int *cur_wind_on;
_Thread_local void *cur_window_data;

void window_run(window_manager_entry_t *w)
{
	void *f = w->window_func;
	void **p = w->ptr_array;

	// Don't run a child window with an unset parent area
	if (w->already_ran || (w->parent_window_func && is0_rect(w->parent_area)))
		return ;

	// Don't run if window is detachable but not detached and parent window isn't registered
	int parent_id = window_find_id_by_func(w->parent_window_func, w->parent_window_data);
	if (w->parent_window_func && parent_id == -1)
	{
		if (w->wind_on)
			if (*w->wind_on == 0)
				return;
	}

	// Set the globals (parent area, wind_on and data)
	cur_parent_area = w->parent_area;
	if (w->wind_on)
		if (*w->wind_on==1 && w->newly_registered)
			*w->wind_on = 2;
	cur_wind_on = w->wind_on;
	cur_window_data = w->window_data;

	// Run the window function
	switch (w->ptr_count)
	{
			case 0:	((void (*)())f)();
		break;	case 1:	((void (*)(void*))f)(p[0]);
		break;	case 2:	((void (*)(void*,void*))f)(p[0], p[1]);
		break;	case 3:	((void (*)(void*,void*,void*))f)(p[0], p[1], p[2]);
		break;	case 4:	((void (*)(void*,void*,void*,void*))f)(p[0], p[1], p[2], p[3]);
		break;	case 5:	((void (*)(void*,void*,void*,void*,void*))f)(p[0], p[1], p[2], p[3], p[4]);
		break;	case 6:	((void (*)(void*,void*,void*,void*,void*,void*))f)(p[0], p[1], p[2], p[3], p[4], p[5]);
		break;	case 7:	((void (*)(void*,void*,void*,void*,void*,void*,void*))f)(p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
		break;	case 8:	((void (*)(void*,void*,void*,void*,void*,void*,void*,void*))f)(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
		break;	default: fprintf_rl(stderr, "In window_run(): Unsupported number of pointers (%d)\n", w->ptr_count);
	}

	// Update the flags
	w->already_ran = 1;
	if (w->wind_on)
		if (*w->wind_on==2 && w->newly_registered)
			*w->wind_on = 1;

	// Run all undetached children
	int i;
	for (i=0; i < wind_man.window_count; i++)
	{
		// Look for children
		if (wind_man.window[i].parent_window_func == w->window_func && wind_man.window[i].parent_window_data == w->window_data)
			if (wind_man.window[i].wind_on)				// that can be detached
				if (*wind_man.window[i].wind_on == 0)		// but aren't
					window_run(&wind_man.window[i]);	// and run them right after their parent
	}
}

int window_register(int priority, void *window_func, void *window_data, rect_t parent_area, int *wind_on, int num_args, ...)
{
	int i, ia;
	va_list ap;
	window_manager_entry_t *entry=NULL, entry_s={0};

	// Don't bother actually registering if this runs from the manager, just run the window function
	if (wind_man.manager_is_calling)
	{
		entry = &entry_s;
		entry->window_func = window_func;
		entry->window_data = window_data;
		entry->ptr_count = num_args;
		entry->ptr_array = calloc(entry->ptr_count, sizeof(void *));
		i = -1;

		goto skip_add2;		// skip to filling the entry and run the function
	}

	// Check if the window function is already registered
	for (i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].window_func == window_func)
		if (wind_man.window[i].window_data == window_data)
		{
			entry = &wind_man.window[i];
			entry->newly_registered = 0;
			goto skip_add2;
		}

	// Look for a free slot in the registry
	for (i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].window_func == NULL)
			goto skip_add1;

	// Add new window at the end of the registry
	i = wind_man.window_count;
	alloc_enough(&wind_man.window, wind_man.window_count+=1, &wind_man.window_as, sizeof(window_manager_entry_t), 2.);

skip_add1:
	entry = &wind_man.window[i];
	entry->window_func = window_func;
	entry->window_data = window_data;
	entry->ptr_count = num_args;
	entry->ptr_array = calloc(entry->ptr_count, sizeof(void *));
	entry->newly_registered = 1;

	// Set window orders
	wind_man.min_order = entry->order = wind_man.min_order - 1;

	if (priority==1)
		window_move_to_top(window_func, window_data);

skip_add2:
	// Copy pointers to array
	va_start(ap, num_args);
	for (ia=0; ia < num_args; ia++)
		entry->ptr_array[ia] = va_arg(ap, void *);
	va_end(ap);

	if (isnan_rect(parent_area)==0)
		entry->parent_area = parent_area;
	entry->wind_on = wind_on;
	entry->dereg = 0;

	// Run here if window has a close button and is "closed"
	if (wind_on)
		if (*wind_on == 0 && entry->parent_window_func == NULL)
			window_run(entry);

	if (wind_man.manager_is_calling)
		free(entry->ptr_array);

	return i;
}

int cmp_window_man_order(const window_manager_entry_t **a, const window_manager_entry_t **b)
{
	return (*a)->order - (*b)->order;
}

void window_man_sort(int reg_count)
{
	int i, j;

	// Sort
	alloc_enough((void **) &wind_man.wsor, reg_count, &wind_man.wsor_as, sizeof(window_manager_entry_t *), 2.);
	for (j=0, i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].window_func)
		{
			wind_man.wsor[j] = &wind_man.window[i];
			j++;
		}

	qsort(wind_man.wsor, reg_count, sizeof(window_manager_entry_t *), cmp_window_man_order);

	// Set new order
	for (i=0; i < reg_count; i++)
		wind_man.wsor[i]->order = i;
	wind_man.min_order = 0;
	wind_man.max_order = reg_count-1;
}

void window_manager()
{
	int i, j, prev_hover_ided = mouse.ctrl_id->hover_ided, reg_count=0;

	// Clear deregistered windows
	for (i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].dereg)
		{
			free(wind_man.window[i].ptr_array);
			memset(&wind_man.window[i], 0, sizeof(window_manager_entry_t));
		}
		else if (wind_man.window[i].window_func)
			reg_count++;

	// Sort registered windows
	window_man_sort(reg_count);

	// Run all windows in sorted order
	wind_man.manager_is_calling = 1;
	for (i=0; i < reg_count; i++)
		if (wind_man.wsor[i]->window_func)
		{
			window_run(wind_man.wsor[i]);

			// Put this window on top if one of its controls has been clicked
			if (prev_hover_ided != mouse.ctrl_id->hover_ided && (mouse.b.lmb>=1 || mouse.b.rmb>=1))
				window_move_to_top(wind_man.wsor[i]->window_func, wind_man.wsor[i]->window_data);

			prev_hover_ided = mouse.ctrl_id->hover_ided;
		}
	wind_man.manager_is_calling = 0;

	// Mark all windows for deregistration
	for (i=0; i < wind_man.window_count; i++)
	{
		wind_man.window[i].dereg = 1;
		wind_man.window[i].already_ran = 0;
	}
}

int window_find_id_by_func(void *window_func, void *window_data)
{
	for (int i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].window_func == window_func)
		if (wind_man.window[i].window_data == window_data)
			return i;

	return -1;
}

void window_set_parent(void *window_func, void *window_data, void *parent_window_func, void *parent_window_data)
{
	int window_id;

	window_id = window_find_id_by_func(window_func, window_data);
	if (window_id == -1)
		return ;

	wind_man.window[window_id].parent_window_func = parent_window_func;
	wind_man.window[window_id].parent_window_data = parent_window_data;
}

void window_move_up(int id, int offset)
{
	int i;

	// Move window up
	wind_man.window[id].order += offset;

	// Move children up
	for (i=0; i < wind_man.window_count; i++)
		if (wind_man.window[i].parent_window_func == wind_man.window[id].window_func)
		if (wind_man.window[i].parent_window_data == wind_man.window[id].window_data)
			window_move_up(i, offset);
}

void window_move_to_top(void *window_func, void *window_data)
{
	int i, window_id, offset;

	window_id = window_find_id_by_func(window_func, window_data);
	if (window_id == -1)
		return ;

	// The window must move up by enough ranks that it's above the others
	offset = wind_man.max_order+1 - wind_man.window[window_id].order;

	// Recursively move the window and its descendants by the offset
	window_move_up(window_id, offset);

	wind_man.max_order += offset;
}

void window_set_parent_area(void *child_func, void *child_data, rect_t area)
{
	int id = window_find_id_by_func(child_func, child_data);
	if (id > -1)
		wind_man.window[id].parent_area = area;
}
