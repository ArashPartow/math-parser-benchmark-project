void elem_te_val(gui_layout_t *layout, const int id, gui_layout_t *lp, int *val, const int sel_change)
{
	textedit_t *te;

	if (check_elem_id_validity(layout, id, 0)==0)
		return ;

	if (layout->elem[id].type != gui_type_textedit)
		return ;

	te = layout->elem[id].data;
	te->edit_mode = te_mode_value;

	if (sel_change)
		if (lp && check_elem_id_validity(lp, lp->sel_id, 0))
			print_to_layout_textedit(layout, id, 1, "%d", *val);
		else
			print_to_layout_textedit(layout, id, 1, "");

	if (ctrl_textedit_fromlayout(layout, id)==1 && val)
		*val = atoi(te->string);
}

void gui_layout_markup_window(int *markup_te_ret, gui_layout_t **markup_layout)
{
	static gui_layout_t layout={0}, *lp=NULL;
	char **new_elem_src, string[64];

	const char *layout_src[] = {
		"elem 0", "type rect", "label Markup", "pos	0	0", "dim	5;6	8;9", "off	0	1", "",
		"elem 80", "type textedit", "pos	0;3	-0;9", "dim	5	7;9", "off	0	1", "",
	};

	make_gui_layout(&layout, layout_src, sizeof(layout_src)/sizeof(char *), "Layout markup");

	if (mouse.window_minimised_flag > 0)
		return;

	// Window
	static flwindow_t window={0};
	flwindow_init_defaults(&window);
	window.bg_opacity = 0.94;
	window.shadow_strength = 0.5*window.bg_opacity;
	draw_dialog_window_fromlayout(&window, cur_wind_on, &cur_parent_area, &layout, 0);

	// Controls
	get_textedit_fromlayout(&layout, 80)->edit_mode = te_mode_full;
	get_textedit_fromlayout(&layout, 80)->scroll_mode = 1;
	get_textedit_fromlayout(&layout, 80)->scroll_mode_scale_def = 40. * 4.5;
	*markup_te_ret = ctrl_textedit_fromlayout(&layout, 80);
	*markup_layout = &layout;
}

void gui_layout_edit_toolbar_core(int *toggle_edit_on, int *markup_te_ret, gui_layout_t **markup_layout)
{
	static int pinned=0;
	textedit_t *te;
	knob_t *knob_data;
	ctrl_selectmenu_state_t *selmenu_data;
	static int sel_id = -1, elem_id = 0, elem_id_prev = -1;
	const int label_te_id = 31;
	static int sel_change = 0;
	static double rounding_prec_v=NAN;

	int i;
	static gui_layout_t layout={0}, *lp=NULL;
	char **new_elem_src, string[64];

	const char *layout_src[] = {
		"v 1	0;0;6	0;4;6", "v 2	1;10	0;4", "v 3	0	-0;8", "v 4	2	0;6", "v 5	0	-0;7", "v 6	2;4	0;1", "v 7	0;4;6	0;0;11", "",
		"elem 0", "type rect", "label GUI Layout Editor", "pos	0	-0;6", "dim	2;4	12;11", "off	0;6	1", "",
		"elem 20", "type textedit", "pos	-0;1	-2;3", "dim	0;11	0;6", "off	1", "",
		"elem 21", "type label", "label Sel ID", "link_pos_id 20", "pos	-0;5;6	0;3", "dim	0;10	0;2;6", "off	0;6	1", "",
		"elem 22", "type textedit", "link_pos_id 20", "pos	0;2	0", "dim	0;11	0;6", "off	0	1", "",
		"elem 23", "type label", "label Elem ID", "link_pos_id 22", "pos	0;5;6	0;3", "dim	0;10	0;2;6", "off	0;6	1", "",
		"elem 30", "type label", "label Label", "link_pos_id 31", "pos	v1", "dim	v2", "off	0;6	1", "",
		"elem 31", "type textedit", "link_pos_id 64", "pos	0	-1", "dim	2	0;8", "off	0;6	1", "",
		"elem 40", "type rect", "pos	0	-3", "dim	v6", "off	0;6	1", "",
		"elem 41", "type label", "label Create", "link_pos_id 50", "pos	v1", "dim	v2", "off	0;6	1", "",
		"elem 50", "type selmenu", "link_pos_id 40", "pos	v5", "dim	v4", "off	0;6	1", "",
		"elem 60", "type rect", "link_pos_id 40", "pos	0	-1;4", "dim	v6", "off	0;6	1", "",
		"elem 61", "type label", "label Edit", "link_pos_id 62", "pos	v1", "dim	v2", "off	0;6	1", "",
		"elem 62", "type button", "label Duplicate", "link_pos_id 60", "pos	v5", "dim	v4", "off	0;6	1", "",
		"elem 63", "type button", "label Delete", "link_pos_id 62", "pos	v3", "dim	v4", "off	0;6	1", "",
		"elem 64", "type button", "label Round pos/dim to _;__;\356\200\234\363\240\204\200", "link_pos_id 63", "pos	v3", "dim	v4", "off	0;6	1", "",
		"elem 70", "type textedit", "link_pos_id 31", "pos	-0;3	-1;1", "dim	0;9	0;6", "off	1", "",
		"elem 71", "type label", "label Linked pos ID", "link_pos_id 70", "pos	-0;8;6	0;3", "dim	0;8	0;2;6", "off	0	1", "",
		"elem 72", "type textedit", "link_pos_id 70", "pos	0;7;6	0", "dim	0;6;6	0;6", "off	1", "",
		"elem 73", "type label", "label Pos v#", "link_pos_id 72", "pos	-0;6	0;3", "dim	0;5;6	0;2;6", "off	0	1", "",
		"elem 74", "type textedit", "link_pos_id 72", "pos	0;7;6	0", "dim	0;6;6	0;6", "off	1", "",
		"elem 75", "type label", "label Dim v#", "link_pos_id 74", "pos	-0;6	0;3", "dim	0;5;6	0;2;6", "off	0	1", "",
		"elem 80", "type none", "link_pos_id 101", "pos	0;2	-0;9;6", "dim	0;11	1;5;6", "off	0;6	1", "",
		"elem 81", "type label", "label Markup", "link_pos_id 80", "pos	0	0;3;6", "dim	0;9	0;3", "off	0;6	1", "",
		"elem 82", "type button", "label Generate markup", "link_pos_id 80", "pos	1;1	0", "dim	0;11	0;4", "off	0;6	1", "",
		"elem 83", "type button", "label Copy C literal to clipboard", "link_pos_id 80", "pos	0;7;6	-0;8;6", "dim	0;6	0;4", "off	0	1", "",
		"elem 84", "type button", "label Apply markup", "link_pos_id 80", "pos	1;1	-1;1;6", "dim	0;11	0;4", "off	0;6	1", "",
		"elem 85", "type checkbox", "label Generate markup continuously", "link_pos_id 80", "pos	1;1	-0;5", "dim	0;11	0;2;6", "off	0;6	1", "",
		"elem 86", "type label", "label Line breaks at:", "link_pos_id 83", "pos	0;11	0", "dim	0;4;6	0;1", "off	1", "",
		"elem 87", "type radio", "label Every line", "link_pos_id 83", "pos	0;11	-0;1;1", "dim	v7", "off	1", "",
		"elem 88", "type radio", "label Every paragraph", "link_pos_id 87", "pos	0	-0;1", "dim	v7", "off	1", "",
		"elem 89", "type radio", "label No breaks", "link_pos_id 88", "pos	0	-0;1", "dim	v7", "off	1", "",
		"elem 90", "type textedit", "link_pos_id 80", "pos	0	-1;10", "dim	0;11	0;7", "off	0;6	1", "",
		"elem 91", "type label", "label C code for unimplemented elems", "link_pos_id 90", "pos	0	0;3;6", "dim	0;9	0;3", "off	0;6	1", "",
		"elem 92", "type button", "label Generate C code", "link_pos_id 90", "pos	0	-0;8", "dim	0;11	0;3", "off	0;6	1", "",
		"elem 100", "type label", "label Position offset", "link_pos_id 107", "pos	0;8;6	0;3;6", "dim	1;10	0;3", "off	0;6	1", "",
		"elem 101", "type radio", "label X 0 | Y 0", "link_pos_id 104", "pos	0	-0;2;6", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 102", "type radio", "label X \302\275 | Y 0", "link_pos_id 101", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 103", "type radio", "label X 1 | Y 0", "link_pos_id 102", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 104", "type radio", "label X 0 | Y \302\275", "link_pos_id 107", "pos	0	-0;2;6", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 105", "type radio", "label X \302\275 | Y \302\275", "link_pos_id 104", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 106", "type radio", "label X 1 | Y \302\275", "link_pos_id 105", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 107", "type radio", "label X 0 | Y 1", "link_pos_id 70", "pos	-0;5;6	-0;11", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 108", "type radio", "label X \302\275 | Y 1", "link_pos_id 107", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 109", "type radio", "label X 1 | Y 1", "link_pos_id 108", "pos	0;8;6	0", "dim	0;7	0;2", "off	0;6	1", "",
		"elem 110", "type checkbox", "label Keep the same on-screen position", "link_pos_id 100", "pos	-0;6;6	-0;11", "dim	0;11	0;2", "off	0;6	1", "",
		"elem 120", "type selmenu", "pos	0	-1;6;6", "dim	2	0;3;6", "off	0;6	1", "",
		"elem 121", "type label", "label Layout selection", "link_pos_id 120", "pos	-0;0;6	0;0;6", "dim	v2", "off	0;6	0", "",
	};

	gui_layout_init_pos_scale(&layout, xy(-16., -16.), 1., XY0, 0);
	make_gui_layout(&layout, layout_src, sizeof(layout_src)/sizeof(char *), "Layout editing toolbar");

	if (mouse.window_minimised_flag > 0)
		return;

	// Selection logic and display unimplemented elements
	if (lp)
	{
		lp->edit_on ^= *toggle_edit_on;

		if (check_elem_id_validity(lp, lp->sel_id, 0)==0)
			lp->sel_id = -1;

		if (sel_id != lp->sel_id)			// if the element selected has changed
		{
			sel_id = lp->sel_id;
			sel_change = 1;
		}

		gui_layout_unimplemented_elems(lp);
	}

	// Layout elements

	// Draw editing grid and toolbar window
	if (lp && lp != &layout)
		draw_unit_grid(lp->offset, lp->sm);

	static flwindow_t window={0};
	flwindow_init_defaults(&window);
	window.pinned_sm_preset = 1.3;
	draw_dialog_window_fromlayout(&window, NULL, NULL, &layout, 0);

	if (lp && lp == &layout)
		draw_unit_grid(lp->offset, lp->sm);

	// IDs
	draw_label_fromlayout(&layout, 21, ALIG_LEFT);
	draw_label_fromlayout(&layout, 23, ALIG_LEFT);

	te = layout.elem[20].data;
	te->edit_mode = te_mode_value;

	if (sel_change)
		print_to_layout_textedit(&layout, 20, 1, "%d", sel_id);

	if (ctrl_textedit_fromlayout(&layout, 20)==1)	// sel_id's te
	{
		if (check_elem_id_validity(&layout, 20, 0))
		{
			sel_id = atoi(te->string);
			if (lp)
				lp->sel_id = sel_id;
			sel_change = 1;
		}
	}

	// update elem_id's te
	te = layout.elem[22].data;
	te->edit_mode = te_mode_value;

	if (elem_id != elem_id_prev)
		if (print_to_layout_textedit(&layout, 22, 1, "%d", elem_id))
			elem_id_prev = elem_id;

	if (ctrl_textedit_fromlayout(&layout, 22)==1)	// elem_id's te
		if (check_elem_id_validity(&layout, 22, 0))
			elem_id = atoi(te->string);

	draw_label_fromlayout(&layout, 30, ALIG_LEFT);

	// Label editor
	te = layout.elem[label_te_id].data;
	te->edit_mode = te_mode_value;

	// copy the current element label to the text editor
	if (sel_change)				// if the element selected has changed
		if (check_elem_id_validity(lp, sel_id, 0) && (sel_id != label_te_id || lp != &layout))
			textedit_clear_then_set_new_text(te, lp->elem[sel_id].label);	

	if (ctrl_textedit_fromlayout(&layout, label_te_id)==1 && check_elem_id_validity(lp, sel_id, 0) && (sel_id != label_te_id || lp != &layout) && lp)		// text editor modifies element label
	{
		sprintf_realloc(&lp->elem[sel_id].label, &lp->elem[sel_id].label_as, 0, "%s", te->string);
		lp->elem[sel_id].label_set = 1;

		if (lp->elem[sel_id].type==gui_type_knob)
		{
			knob_data = lp->elem[sel_id].data;
			knob_data->main_label = lp->elem[sel_id].label;
		}
	}

	// Create section
	draw_rect_fromlayout(1, &layout, 40);
	draw_label_fromlayout(&layout, 41, ALIG_LEFT);

	// Editing section
	draw_rect_fromlayout(1, &layout, 60);
	draw_label_fromlayout(&layout, 61, ALIG_LEFT);

	// Duplicate element
	if (ctrl_button_fromlayout(&layout, 62))
	{
		gui_layout_duplicate_elem(lp, sel_id, elem_id);
		lp->sel_id = elem_id;
	}

	// Remove element
	if (ctrl_button_fromlayout(&layout, 63))
		if (check_elem_id_validity(lp, sel_id, 0))
			free_layout_elem(&lp->elem[sel_id]);

	// Round off pos/dim
	reset_insert_rect_array();
	if (ctrl_button_fromlayout(&layout, 64))
		gui_round_elem_posdim(lp, sel_id, 144./nearbyint(rounding_prec_v));

	// Insert knob in the button
	static knob_t roundprec_knob={0};
	if (roundprec_knob.main_label==NULL)
		roundprec_knob = make_knob("", 6., knobf_log, 1., 12., "%.0f");
	ctrl_knob(&rounding_prec_v, &roundprec_knob, insert_rect_change_height(get_insert_rect(0), -3., 9.), GUI_COL_DEF);

	// Link pos
	draw_label_fromlayout(&layout, 71, ALIG_LEFT);
	elem_te_val(&layout, 70, lp, lp==NULL ? NULL : &lp->elem[sel_id].link_pos_id, sel_change);

	// Pos v#
	draw_label_fromlayout(&layout, 73, ALIG_LEFT);
	elem_te_val(&layout, 72, lp, lp==NULL ? NULL : &lp->elem[sel_id].pos_val, sel_change);

	// Dim v#
	draw_label_fromlayout(&layout, 75, ALIG_LEFT);
	elem_te_val(&layout, 74, lp, lp==NULL ? NULL : &lp->elem[sel_id].dim_val, sel_change);

	// Position offset
	static int offset_radio = -1;
	draw_label_fromlayout(&layout, 100, ALIG_LEFT);

	static int keep_screen_pos=0;
	ctrl_checkbox_fromlayout(&keep_screen_pos, &layout, 110);

	if (sel_change)
		if (check_elem_id_validity(lp, sel_id, 0))
			offset_radio = 101 + (int) nearbyint(lp->elem[sel_id].pos_off.x*2.) + 3 * (int) nearbyint(lp->elem[sel_id].pos_off.y*2.);
		else
			offset_radio = -1;

	xy_t po0, po1;
	for (i=101; i <= 109; i++)
		if (ctrl_radio_fromlayout(&offset_radio, &layout, i))
		{
			po0 = lp->elem[sel_id].pos_off;
			po1 = xy( (double) ((i-101) % 3) * 0.5 , (double) ((i-101) / 3) * 0.5 );
			lp->elem[sel_id].pos_off = po1;

			if (keep_screen_pos)
				lp->elem[sel_id].pos = mad_xy(get_elem_dim(lp, sel_id), sub_xy(po1, po0), lp->elem[sel_id].pos);
		}

	// Markup
	draw_label_fromlayout(&layout, 81, ALIG_LEFT);
	window_set_parent_area(gui_layout_markup_window, NULL, gui_layout_elem_comp_area_os(&layout, 80, XY0));	// Markup subwindow

	static int cont_gen_markup = 1;
	ctrl_checkbox_fromlayout(&cont_gen_markup, &layout, 85);

	te = get_textedit_fromlayout(*markup_layout, 80);
	if (ctrl_button_fromlayout(&layout, 82) || (cont_gen_markup && mouse.b.lmb==-1 && cur_textedit != te && *markup_te_ret==0))	// Generate markup
	{
		char *new_src=NULL;
		size_t new_src_as=0;
		sprint_gui_layout(lp, &new_src, &new_src_as);
		if (new_src)
			if (strcmp(new_src, get_textedit_string_fromlayout(*markup_layout, 80)))	// only print if markup changed
				print_to_layout_textedit(*markup_layout, 80, 0, "%s", new_src);
		free(new_src);
	}

	static int breaks_radio=88;
	draw_label_fromlayout(&layout, 86, ALIG_LEFT);
	ctrl_radio_fromlayout(&breaks_radio, &layout, 87);
	ctrl_radio_fromlayout(&breaks_radio, &layout, 88);
	ctrl_radio_fromlayout(&breaks_radio, &layout, 89);	

	if (ctrl_button_fromlayout(&layout, 83))	// Copy C literal to clipboard
	{
		char *c_src;
		c_src = text_to_multiline_c_literal(te->string, breaks_radio-87);
		#ifdef RL_SDL
		SDL_SetClipboardText(c_src);
		#endif
		free(c_src);
	}

	int apply_markup = 0;
	if (ctrl_button_fromlayout(&layout, 84) || (cont_gen_markup && *markup_te_ret==2))	// Apply markup
		apply_markup = 1;

	// Unimplemented elems code
	draw_label_fromlayout(&layout, 91, ALIG_LEFT);
	te = layout.elem[90].data;
	te->max_scale = 1./6.;
	ctrl_textedit_fromlayout(&layout, 90);

	if (ctrl_button_fromlayout(&layout, 92))	// Generate C code
	{
		char *unimp_code;
		unimp_code = gui_layout_make_code_for_unimp_elem(lp);
		print_to_layout_textedit(&layout, 90, 1, "%s", unimp_code ? unimp_code : "");
		free(unimp_code);
	}

	// Create buttons
	selmenu_data = layout.elem[50].data;
	gui_layout_selmenu_set_count(gui_type_count-gui_type_none, &layout, 50);
	if (ctrl_selmenu_fromlayout(&layout, 50))
	{
		new_elem_src = (char **) calloc_2d(5, 32, sizeof(char));
		sprintf(new_elem_src[0], "type %s", layout_elem_type_name[selmenu_data->sel_id+gui_type_none]);
		sprintf(new_elem_src[1], "pos	0	0");
		if (selmenu_data->sel_id+gui_type_none == gui_type_knob)
			sprintf(new_elem_src[2], "dim	1");
		else
			sprintf(new_elem_src[2], "dim	2	1");
		sprintf(new_elem_src[3], "off	0	1");

		if (selmenu_data->sel_id==gui_type_knob)
			sprintf(new_elem_src[4], "knob 0 0 1 linear");

		gui_layout_add_elem(lp, &elem_id, new_elem_src, 5);

		free_2d(new_elem_src, 5);

		if (lp)
			lp->sel_id = elem_id;
	}

	for (i=gui_type_none; i < gui_type_count; i++)
		draw_selmenu_entry_fromlayout(i-gui_type_none, layout_elem_type_name[i], &layout, 50);

	// Layout selection
	draw_label_fromlayout(&layout, 121, ALIG_LEFT);	

	selmenu_data = layout.elem[120].data;
	gui_layout_selmenu_set_count(layout_reg.reg_count, &layout, 120);
	if (ctrl_selmenu_fromlayout(&layout, 120))
		lp = layout_reg.sel_p = layout_reg.reg[selmenu_data->sel_id % layout_reg.reg_count].lp;

	for (i=0; i < layout_reg.reg_count; i++)
		draw_selmenu_entry_fromlayout(i, layout_reg.reg[i].name, &layout, 120);

	// Logic

	sel_change = 0;

	if (apply_markup && lp)
	{
		te = (*markup_layout)->elem[80].data;
		if (strlen(te->string) > 0)
		{
			gui_layout_t new_layout={0}, layout_copy;
			char **new_src;
			int new_src_linecount=0;

			new_src = arrayise_text(make_string_copy(te->string), &new_src_linecount);

			// free elems and arrays from the old layout without blanking it
			layout_copy = *lp;
			free_gui_layout(&layout_copy);

			// make the new layout
			make_gui_layout(&new_layout, new_src, new_src_linecount, NULL);
			free_2d(new_src, 1);

			// reference new arrays and their sizes
			lp->elem = new_layout.elem;
			lp->elem_as = new_layout.elem_as;
			lp->value = new_layout.value;
			lp->value_as = new_layout.value_as;
			sel_change = 1;
		}
	}

	gui_layout_registry_reset();
	gui_layout_registry_add(NULL, "(none)");
}

void gui_layout_edit_toolbar(int toggle_edit_on)
{
	static int toggle_edit_on_copy, markup_window_detached=0, markup_te_ret=0;
	static gui_layout_t *markup_layout=NULL;

	toggle_edit_on_copy = toggle_edit_on;
	window_register(1, gui_layout_markup_window, NULL, RECTNAN, &markup_window_detached, 2, &markup_te_ret, &markup_layout);
	window_set_parent(gui_layout_markup_window, NULL, gui_layout_edit_toolbar_core, NULL);
	window_register(1, gui_layout_edit_toolbar_core, NULL, rect(XY0, XY0), NULL, 3, &toggle_edit_on_copy, &markup_te_ret, &markup_layout);
}
