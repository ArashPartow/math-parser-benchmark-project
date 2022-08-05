// must match the enum in make_gui.h
const char *layout_elem_type_name[] =
{
	"(null)",
	"none",
	"label",
	"rect",
	"button",
	"checkbox",
	"radio",
	"knob",
	"textedit",
	"selmenu",
};

layout_reg_t layout_reg={0};

void free_layout_elem(layout_elem_t *elem)
{
	free(elem->label);

	if (elem->data)
	{
		switch (elem->type)
		{
			case gui_type_knob:
				free(((knob_t *) elem->data)->fmt_str);
				free(((knob_t *) elem->data)->unit_label);
				break;

			case gui_type_textedit:
				textedit_free((textedit_t *) elem->data);
				break;
		}

		free(elem->data);
		elem->data = NULL;
	}

	memset(elem, 0, sizeof(layout_elem_t));
}

void free_gui_layout(gui_layout_t *layout)
{
	int i;

	if (layout==NULL)
		return;

	for (i=0; i < layout->elem_as; i++)
		free_layout_elem(&layout->elem[i]);

	free(layout->elem);
	free(layout->value);

	memset(layout, 0, sizeof(gui_layout_t));
}

void gui_layout_duplicate_elem(gui_layout_t *layout, const int src_id, int dst_id)
{
	layout_elem_t *src_elem, *dst_elem=NULL;
	knob_t *kd_src, *kd_dst;

	if (layout==NULL)
		return;

	// Check IDs
	if (check_elem_id_validity(layout, src_id, 0)==0)
		 return ;
	src_elem = &layout->elem[src_id];

	if (dst_id < 0 || dst_id > 1000000)
		return ;

	if (check_elem_id_validity(layout, dst_id, 0))	// if the destination ID is already taken
	{
		fprintf_rl(stdout, "ID #%d is already taken, no duplication done.\n", dst_id);
		return ;
	}

	// Allocate new ID
	layout->cur_elem_id = dst_id;
	alloc_enough(&layout->elem, layout->cur_elem_id+1, &layout->elem_as, sizeof(layout_elem_t), 1.5);
	dst_elem = &layout->elem[layout->cur_elem_id];

	// Copy struct
	*dst_elem = *src_elem;
	dst_elem->implemented = 0;

	// Copy label
	if (src_elem->label)
	{
		dst_elem->label = calloc(dst_elem->label_as, sizeof(char));
		strcpy(dst_elem->label, src_elem->label);
	}

	// Copy data
	if (src_elem->data)	// copy or init data
	{
		switch (src_elem->type)
		{
			case gui_type_knob:
				kd_src = src_elem->data;
				kd_dst = dst_elem->data;
				*kd_dst = *kd_src;
				kd_dst->fmt_str = make_string_copy(kd_src->fmt_str);
				kd_dst->unit_label = make_string_copy(kd_src->unit_label);
				break;

			case gui_type_textedit:
				dst_elem->data = calloc(1, sizeof(textedit_t));
				textedit_init(dst_elem->data, 0);
				break;

			case gui_type_selmenu:
				*((ctrl_selectmenu_state_t *) dst_elem->data) = *((ctrl_selectmenu_state_t *) src_elem->data);
				break;
		}
	}
}

void make_gui_layout(gui_layout_t *layout, const char **src, const int linecount, const char *layout_name)
{
	int i, il, n, vint;
	const char *line, *p;
	char a[128], b[32];
	layout_elem_t *cur_elem=NULL;
	layout_value_t *cur_val=NULL;
	knob_t *knob_data;
	textedit_t *te;
	ctrl_selectmenu_state_t *selmenu_data;

	if (layout==NULL)
		return;

	if (layout->init)
	{
		gui_layout_registry_add(layout, layout_name);
		return ;
	}

	layout->init = 1;
	layout->sel_id = -1;

	if (layout->elem && layout->cur_elem_id < layout->elem_as)
		cur_elem = &layout->elem[layout->cur_elem_id];

	for (il=0; il < linecount; il++)
	{
		line = src[il];
		a[0] = '\0';
		n = 0;
		sscanf(line, "%s %n", a, &n);
		p = &line[n];

		if (strcmp(a, "v")==0)			// create new value
		{
			n = 0;
			if (sscanf(line, "v %d %n", &vint, &n)==1)
				if (n && vint >= 0 && vint <= 1000000)
				{
					alloc_enough(&layout->value, vint+1, &layout->value_as, sizeof(layout_value_t), 1.5);
					cur_val = &layout->value[vint];
					memset(cur_val, 0, sizeof(layout_value_t));

					p = &line[n];
					p = string_parse_fractional_12(p, &cur_val->value.x);
					if (p[0])
					{
						p = string_parse_fractional_12(p, &cur_val->value.y);
						cur_val->y_set = 1;
					}
					else
						cur_val->value.y = cur_val->value.x;

					cur_val->set = 1;
				}
		}

		if (strcmp(a, "elem")==0)		// create new element
		{
			if (sscanf(line, "elem %d", &layout->cur_elem_id)==1)
			{
				if (layout->cur_elem_id < 0 || layout->cur_elem_id > 1000000)
				{
					fprintf_rl(stderr, "ID %d is out of the valid [0 , 1000000] range in line %d: \"%s\"\n", layout->cur_elem_id, il, line);
					return ;
				}
				else
				{
					alloc_enough(&layout->elem, layout->cur_elem_id+1, &layout->elem_as, sizeof(layout_elem_t), 1.5);

					cur_elem = &layout->elem[layout->cur_elem_id];

					if (cur_elem->type != 0)		// if an element was already there
						free_layout_elem(cur_elem);	// remove it

					// Default values
					cur_elem->type = gui_type_none;
					cur_elem->colour = GUI_COL_DEF;
					cur_elem->link_pos_id = -1;
					cur_elem->link_pos_off = XYNAN;
					cur_elem->pos_val = -1;
					cur_elem->dim_val = -1;
				}
			}
			else
			{
				fprintf_rl(stderr, "No valid element ID in line %d: \"%s\"\n", il, line);
				return ;
			}
		}

		if (strcmp(a, "type")==0)		// define the type of the element
		{
			for (i=0; i < gui_type_count; i++)
				if (strcmp(p, layout_elem_type_name[i])==0)
				{
					cur_elem->type = i;
					break;
				}

			if (cur_elem->type == gui_type_null)
				fprintf_rl(stderr, "No valid element type in line %d: \"%s\"\n", il, line);

			// initialise the element with some defaults
			switch (cur_elem->type)
			{
				case gui_type_knob:
					cur_elem->data = calloc(1, sizeof(knob_t));
					knob_data = (knob_t *) cur_elem->data;
					*knob_data = make_knob(cur_elem->label, 0., knobf_linear, 0., 1., NULL);
					break;

				case gui_type_textedit:
					cur_elem->data = calloc(1, sizeof(textedit_t));
					te = (textedit_t *) cur_elem->data;
					textedit_init(te, 0);
					break;

				case gui_type_selmenu:
					cur_elem->data = calloc(1, sizeof(ctrl_selectmenu_state_t));
					//selmenu_data = (ctrl_selectmenu_state_t *) cur_elem->data;
					break;
			}
		}

		if (strcmp(a, "label")==0)		// set the label string
		{
			alloc_enough(&cur_elem->label, strlen(p)+1, &cur_elem->label_as, sizeof(char), 1.);
			strcpy(cur_elem->label, p);
			cur_elem->label_set = 1;

			switch (cur_elem->type)
			{
				case gui_type_knob:
					if (cur_elem->data)
						((knob_t *) cur_elem->data)->main_label = cur_elem->label;
					break;

				case gui_type_textedit:
					if (cur_elem->data)
						*((textedit_t *) cur_elem->data) = string_to_textedit(make_string_copy(cur_elem->label));
					break;
			}
		}

		if (strcmp(a, "label_alloc")==0)	// set the minimum allocation size of the label
		{
			vint = 0;
			if (sscanf(line, "label_alloc %d", &vint)==1)
			{
				alloc_enough(&cur_elem->label, vint+1, &cur_elem->label_as, sizeof(char), 1.);
				cur_elem->label_as_set = 1;
			}
			else
				fprintf_rl(stderr, "No valid label allocation size in line %d: \"%s\"\n", il, line);
		}

		// define the area rect
		if (strcmp(a, "pos")==0)
		{
			if (p[0]=='v')
				sscanf(p, "v%d", &cur_elem->pos_val);
			else
			{
				p = string_parse_fractional_12(p, &cur_elem->pos.x);
				p = string_parse_fractional_12(p, &cur_elem->pos.y);
			}
		}

		if (strcmp(a, "dim")==0)
		{
			if (p[0]=='v')
				sscanf(p, "v%d", &cur_elem->dim_val);
			else
			{
				p = string_parse_fractional_12(p, &cur_elem->dim.x);
				if (p[0])
					p = string_parse_fractional_12(p, &cur_elem->dim.y);
				else
					cur_elem->dim.y = cur_elem->dim.x;
			}
		}

		if (strcmp(a, "off")==0)
		{
			p = string_parse_fractional_12(p, &cur_elem->pos_off.x);
			if (p[0])
				p = string_parse_fractional_12(p, &cur_elem->pos_off.y);
			else
				cur_elem->pos_off.y = cur_elem->pos_off.x;
		}

		if (strcmp(a, "link_pos_id")==0)		// sets the ID of the element that gives its position as an offset for this element
		{
			char *offset = cur_elem->link_pos_off_str;
			memset(offset, 0, 3*sizeof(char));
			if (sscanf(line, "link_pos_id %d.%2s", &cur_elem->link_pos_id, offset) < 1)
				fprintf_rl(stderr, "No ID provided for link_pos_id in line %d: \"%s\"\n", il, line);

			cur_elem->link_pos_off = XYNAN;

			// Parse the offset, if specified
			if (offset[0] && offset[1])
			{
				if (offset[0] == '0' || offset[0] == 'l') cur_elem->link_pos_off.x = 0.;
				if (offset[0] == 'm' || offset[0] == 'c') cur_elem->link_pos_off.x = 0.5;
				if (offset[0] == '1' || offset[0] == 'r') cur_elem->link_pos_off.x = 1.;

				if (offset[1] == '0' || offset[1] == 'b') cur_elem->link_pos_off.y = 0.;
				if (offset[1] == 'm' || offset[1] == 'c') cur_elem->link_pos_off.y = 0.5;
				if (offset[1] == '1' || offset[1] == 't') cur_elem->link_pos_off.y = 1.;
			}
		}

		if (strcmp(a, "knob")==0)	// sets the knob data structure
		{
			if (cur_elem->data==NULL)
			{
				fprintf_rl(stderr, "Knob element data should have been initialised by a 'type knob' command before line %d: \"%s\"\n", il, line);
				return ;
			}

			knob_data = (knob_t *) cur_elem->data;

			n = 0;
			if (sscanf(line, "knob %lg %lg %lg %s %n", &knob_data->min, &knob_data->default_value, &knob_data->max, b, &n)==4)
			{
				knob_data->func = knob_func_name_to_ptr(b);
				if (knob_data->func==NULL)
				{
					fprintf_rl(stderr, "The knob function name '%s' isn't valid in line %d: \"%s\"\n", b, il, line);
					return ;
				}

				if (knob_data->min >= knob_data->max)
				{
					fprintf_rl(stderr, "The maximum value of a knob cannot be lower than the minimum in line %d: \"%s\"\n", il, line);
					return ;
				}

				if (knob_data->min > knob_data->default_value || knob_data->default_value > knob_data->max)
				{
					fprintf_rl(stderr, "The default value of a knob cannot be outside of the [min , max] range in line %d: \"%s\"\n", il, line);
					return ;
				}

				if (knob_data->func==knobf_log && MINN(knob_data->min, knob_data->default_value) <= 0.)
				{
					fprintf_rl(stderr, "When the knob function is logarithmic no value can be 0 or lower in line %d: \"%s\"\n", il, line);
					return ;
				}

				if (n==0)
					n = strlen(line);
				p = &line[n];
				free_null(&knob_data->fmt_str);
				knob_data->fmt_str = make_string_copy(p[0] ? p : VALFMT_DEFAULT);
				cur_elem->fmt_str_set = p[0]!='\0';
			}
			else
			{
				fprintf_rl(stderr, "The 'knob' command needs at least the first 4 arguments: '<min> <default> <max> <function (linear|log|recip)> (<format string>)' at line %d: \"%s\"\n", il, line);
				return ;
			}
		}

		if (strcmp(a, "knob_unit")==0)
		{
			if (cur_elem->data==NULL || cur_elem->type != gui_type_knob)
			{
				fprintf_rl(stderr, "Knob element data should have been initialised by a 'type knob' command before line %d: \"%s\"\n", il, line);
				return ;
			}

			knob_data = (knob_t *) cur_elem->data;

			free_null(&knob_data->unit_label);

			if (sscanf(line, "knob_unit %[^\n]", b)==1)
				knob_data->unit_label = make_string_copy(b);
		}

		if (strcmp(a, "knob_arg")==0)	// arguments for knob functions like knobf_logoff or knobf_tan
		{
			if (cur_elem->data==NULL || cur_elem->type != gui_type_knob)
			{
				fprintf_rl(stderr, "Knob element data should have been initialised by a 'type knob' command before line %d: \"%s\"\n", il, line);
				return ;
			}

			knob_data = (knob_t *) cur_elem->data;

			knob_data->arg_count = sscanf(line, "knob_arg %lg %lg %lg %lg", &knob_data->arg[0], &knob_data->arg[1], &knob_data->arg[2], &knob_data->arg[3]);
		}
	}
}

void gui_layout_add_elem(gui_layout_t *layout, int *id, const char **src, const int linecount)
{
	int i;
	char *elem_line;

	if (layout==NULL)
		return;

	if (check_elem_id_validity(layout, *id, 0))			// if the ID is already taken
		for (i=layout->elem_as-1; i >= 0; i--)			// change ID to the free ID above the highest taken ID
			if (layout->elem[i].type == gui_type_null)
				*id = i;
			else
				break;

	elem_line = sprintf_alloc("elem %d", *id);

	layout->init = 0;
	make_gui_layout(layout, &elem_line, 1, NULL);
	free(elem_line);

	if (src && linecount > 0)
	{
		layout->init = 0;
		make_gui_layout(layout, src, linecount, NULL);
	}
}

void sprint_gui_layout(gui_layout_t *layout, char **str, size_t *str_as)
{
	int i, id, any_v_printed=0;
	layout_elem_t *cur_elem=NULL;
	layout_value_t *cur_val=NULL;
	knob_t *knob_data;
	char a[32], b[32];

	if (layout==NULL)
		return;

	sprintf_realloc(str, str_as, 0, "");	// clears/inits the string

	for (id=0; id < layout->value_as; id++)
	{
		cur_val = &layout->value[id];

		if (cur_val->set)
		{
			sprintf_realloc(str, str_as, 1, "v %d\t", id);
			sprintf_realloc(str, str_as, 1, "%s", sprint_fractional_12(a, cur_val->value.x));
			if (cur_val->y_set)
				sprintf_realloc(str, str_as, 1, "\t%s", sprint_fractional_12(a, cur_val->value.y));
			sprintf_realloc(str, str_as, 1, "\n", id);
			any_v_printed = 1;
		}
	}
	if (any_v_printed)
		sprintf_realloc(str, str_as, 1, "\n", id);

	for (id=0; id < layout->elem_as; id++)
	{
		cur_elem = &layout->elem[id];

		if (cur_elem->type != gui_type_null)
		{
			sprintf_realloc(str, str_as, 1, "elem %d\n", id);
			if (cur_elem->type >= 0 && cur_elem->type < gui_type_count)
				sprintf_realloc(str, str_as, 1, "type %s\n", layout_elem_type_name[cur_elem->type]);

			// Label
			if (cur_elem->label_set)
				sprintf_realloc(str, str_as, 1, "label %s\n", cur_elem->label);
			if (cur_elem->label_as_set && cur_elem->label_as > 1)
				sprintf_realloc(str, str_as, 1, "label_alloc %d\n", cur_elem->label_as-1);

			// Data
			if (cur_elem->type == gui_type_knob && cur_elem->data)
			{
				knob_data = (knob_t *) cur_elem->data;

				sprintf_realloc(str, str_as, 1, "knob %g %g %g %s", knob_data->min, knob_data->default_value, knob_data->max, knob_func_ptr_to_name(knob_data->func));
				if (cur_elem->fmt_str_set && knob_data->fmt_str)
					sprintf_realloc(str, str_as, 1, " %s", knob_data->fmt_str);
				sprintf_realloc(str, str_as, 1, "\n");

				if (knob_data->arg_count)
				{
					sprintf_realloc(str, str_as, 1, "knob_arg");
					for (i=0; i < knob_data->arg_count; i++)
						sprintf_realloc(str, str_as, 1, " %lg", knob_data->arg[i]);
					sprintf_realloc(str, str_as, 1, "\n");
				}

				if (knob_data->unit_label)
					sprintf_realloc(str, str_as, 1, "knob_unit %s\n", knob_data->unit_label);
			}

			// Positioning
			if (cur_elem->link_pos_id >= 0)
				if ((isnan(cur_elem->link_pos_off.x) && isnan(cur_elem->link_pos_off.y)) || cur_elem->link_pos_off_str[0]=='\0')
					sprintf_realloc(str, str_as, 1, "link_pos_id %d\n", cur_elem->link_pos_id);
				else
					sprintf_realloc(str, str_as, 1, "link_pos_id %d.%s\n", cur_elem->link_pos_id, cur_elem->link_pos_off_str);

			if (cur_elem->pos_val >= 0)
				sprintf_realloc(str, str_as, 1, "pos\tv%d\n", cur_elem->pos_val);
			else
				sprintf_realloc(str, str_as, 1, "pos\t%s\t%s\n", sprint_fractional_12(a, cur_elem->pos.x), sprint_fractional_12(b, cur_elem->pos.y));

			if (cur_elem->dim_val >= 0)
				sprintf_realloc(str, str_as, 1, "dim\tv%d\n", cur_elem->dim_val);
			else
			{
				sprintf_realloc(str, str_as, 1, "dim\t%s", sprint_fractional_12(a, cur_elem->dim.x));
				if (fastabs64(double_diff_ulp(cur_elem->dim.x, cur_elem->dim.y)) > 1000000)
					sprintf_realloc(str, str_as, 1, "\t%s", sprint_fractional_12(a, cur_elem->dim.y));
				sprintf_realloc(str, str_as, 1, "\n");
			}

			sprintf_realloc(str, str_as, 1, "off\t%s", sprint_fractional_12(a, cur_elem->pos_off.x));
			if (fastabs64(double_diff_ulp(cur_elem->pos_off.x, cur_elem->pos_off.y)) > 1000000)
				sprintf_realloc(str, str_as, 1, "\t%s", sprint_fractional_12(a, cur_elem->pos_off.y));
			sprintf_realloc(str, str_as, 1, "\n");

			sprintf_realloc(str, str_as, 1, "\n");
		}
	}
}

void gui_layout_init_pos_scale(gui_layout_t *layout, xy_t pos, double scale, xy_t offset, int force)
{
	if (layout->init==0 || force)
	{
		layout->sm = scale;
		layout->offset = mad_xy(offset, set_xy(scale), pos);
	}
}

//**** Value functions ****

int check_value_id_validity(gui_layout_t *layout, const int id, const int implemented)
{
	if (layout==NULL)
		return 0;

	if (id < 0 || id >= layout->value_as)
	{
		if (implemented)
			fprintf_rl(stderr, "Error in check_value_id_validity(): ID %d isn't valid (highest ID is %d)\n", id, layout->value_as-1);
		return 0;
	}

	if (layout->value[id].set==0)
	{
		if (implemented)
			fprintf_rl(stderr, "Error in check_value_id_validity(): value at ID %d isn't set\n", id);
		return 0;
	}

	return 1;
}

xy_t *gui_layout_get_value_ptr(gui_layout_t *layout, const int id)
{
	if (check_value_id_validity(layout, id, 0)==0)
		return NULL;

	return &layout->value[id].value;
}

xy_t gui_layout_get_value(gui_layout_t *layout, const int id)
{
	if (check_value_id_validity(layout, id, 0)==0)
		return XY0;

	return layout->value[id].value;
}

//**** Element functions ****

int check_elem_id_validity(gui_layout_t *layout, const int id, const int implemented)
{
	if (layout==NULL)
		return 0;

	if (id < 0 || id >= layout->elem_as)
	{
		if (implemented)
			fprintf_rl(stderr, "Error in check_elem_id_validity(): ID %d isn't valid (highest ID is %zu)\n", id, layout->elem_as-1);
		return 0;
	}

	if (implemented)
		layout->elem[id].implemented = 0;

	if (layout->elem[id].type <= gui_type_null || layout->elem[id].type >= gui_type_count)
	{
		if (implemented)
			fprintf_rl(stderr, "Error in check_elem_id_validity(): element at ID %d %s\n", id, layout->elem[id].type == gui_type_null ? "isn't initialised" : "has an invalid type");
		return 0;
	}

	if (implemented)
		layout->elem[id].implemented = 1;

	return 1;
}

xy_t *get_elem_posdim_ptr(gui_layout_t *layout, const int id, const int which)	// which: 0 is pos, 1 is dim
{
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return NULL;
	cur_elem = &layout->elem[id];

	if ((cur_elem->pos_val >= 0 && which==0) || (cur_elem->dim_val >= 0 && which==1))
		return gui_layout_get_value_ptr(layout, which==0 ? cur_elem->pos_val : cur_elem->dim_val);
	else
		if (which==0)
			return &cur_elem->pos;
		else
			return &cur_elem->dim;
}

xy_t get_elem_pos(gui_layout_t *layout, const int id)
{
	xy_t *pos = get_elem_posdim_ptr(layout, id, 0);

	if (pos==NULL)
		return XY0;
	else
		return *pos;
}

xy_t get_elem_dim(gui_layout_t *layout, const int id)
{
	xy_t *dim = get_elem_posdim_ptr(layout, id, 1);

	if (dim==NULL)
		return XY0;
	else
		return *dim;
}

xy_t gui_layout_get_link_pos(gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;
	xy_t link_pos;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return XY0;
	cur_elem = &layout->elem[id];

	if (check_elem_id_validity(layout, cur_elem->link_pos_id, 0)==0)
		return XY0;

	// Get position of linked element
	link_pos = add_xy(get_elem_pos(layout, cur_elem->link_pos_id) , gui_layout_get_link_pos(layout, cur_elem->link_pos_id));

	// Take link_pos_off into account if at least partially defined
	if (isnan(cur_elem->link_pos_off.x)==0 || isnan(cur_elem->link_pos_off.y)==0)
	{
		// Get the linked element's area
		rect_t link_area = gui_layout_elem_comp_area(layout, cur_elem->link_pos_id);

		// Interpolate between the corners of the linked element's area
		if (isnan(cur_elem->link_pos_off.x)==0)
			link_pos.x = mix(link_area.p0.x, link_area.p1.x, cur_elem->link_pos_off.x);

		if (isnan(cur_elem->link_pos_off.y)==0)
			link_pos.y = mix(link_area.p0.y, link_area.p1.y, cur_elem->link_pos_off.y);
	}

	return link_pos;
}

rect_t gui_layout_elem_comp_area(gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return rect(XY0, XY0);
	cur_elem = &layout->elem[id];

	return make_rect_off(add_xy(get_elem_pos(layout, id), gui_layout_get_link_pos(layout, id)), get_elem_dim(layout, id), cur_elem->pos_off);
}

rect_t gui_layout_elem_comp_area_os(gui_layout_t *layout, const int id, const xy_t offset)
{
	return offset_scale_rect(gui_layout_elem_comp_area(layout, id), add_xy(layout->offset, offset), layout->sm);
}

// takes care of the resizing, returns 1 if ID is invalid
int ctrl_fromlayout_resizing(gui_layout_t *layout, const int id, const int phase)
{
	static mouse_ctrl_id_t ctrl_id_save={0};
	layout_elem_t *cur_elem=NULL;
	rect_t box_os, area;
	xy_t pos, *pos_ptr, *dim_ptr;

	if (layout==NULL)
		return 1;

	if (phase & 1)
	{
		if (check_elem_id_validity(layout, id, 1)==0)	// if id isn't a valid layout element
			return 1;				// instruct caller to abort
		cur_elem = &layout->elem[id];

		if ((cur_elem->type == gui_type_knob || cur_elem->type == gui_type_textedit || cur_elem->type == gui_type_selmenu) && cur_elem->data == NULL)
			return 1;

		if (layout->edit_on)
		{
			area = gui_layout_elem_comp_area(layout, id);
			box_os = offset_scale_rect(area, layout->offset, layout->sm);

			if (layout->sel_id == id)		// if this control is the selected one
			{					// use the resizing rect
				if (ctrl_resizing_rect(&cur_elem->resize_ctrl, &box_os))
				{
					area = offset_scale_inv_rect(box_os, layout->offset, layout->sm);
					pos_ptr = get_elem_posdim_ptr(layout, id, 0);
					dim_ptr = get_elem_posdim_ptr(layout, id, 1);
					pos = *pos_ptr;

					rect_to_pos_dim(area, &pos, dim_ptr, cur_elem->pos_off);
					*pos_ptr = sub_xy(pos, gui_layout_get_link_pos(layout, id));	// remove linked offset
				}
			}
			else if (ctrl_button_invis(box_os, NULL))	// invisible selection button
				layout->sel_id = id;

			ctrl_id_save = *mouse.ctrl_id;		// suspends input processing for following controls so that the resizing controls seem above them
		}
	}

	if (phase & 2)
	{
		if (layout->edit_on)
			*mouse.ctrl_id = ctrl_id_save;
	}

	return 0;
}

void draw_label_fromlayout_in_rect(gui_layout_t *layout, const int id, const int mode, rect_t box_os)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return ;
	cur_elem = &layout->elem[id];

	draw_label(cur_elem->label, box_os, cur_elem->colour, mode);

	ctrl_fromlayout_resizing(layout, id, 2);
}

void draw_label_fromlayout(gui_layout_t *layout, const int id, const int mode)
{
	draw_label_fromlayout_in_rect(layout, id, mode, gui_layout_elem_comp_area_os(layout, id, XY0));
}

void draw_text_block_fromlayout_in_rect(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh, rect_t box_os)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return ;
	cur_elem = &layout->elem[id];

	//draw_text_block(cur_elem->label, box_os, cur_elem->colour, mode, thresh);
	draw_text_block(text_block, box_os, cur_elem->colour, mode, thresh);

	ctrl_fromlayout_resizing(layout, id, 2);
}

void draw_text_block_fromlayout(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh)
{
	draw_text_block_fromlayout_in_rect(layout, id, text_block, mode, thresh, gui_layout_elem_comp_area_os(layout, id, XY0));
}

void draw_text_at_scale_fromlayout_in_rect(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh, rect_t box_os)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return ;
	cur_elem = &layout->elem[id];

	draw_text_at_scale(text_block, box_os, cur_elem->colour, mode, thresh);

	ctrl_fromlayout_resizing(layout, id, 2);
}

void draw_text_at_scale_fromlayout(gui_layout_t *layout, const int id, char *text_block, const int mode, double thresh)
{
	draw_text_at_scale_fromlayout_in_rect(layout, id, text_block, mode, thresh, gui_layout_elem_comp_area_os(layout, id, XY0));
}

void draw_rect_fromlayout_blending(const int type, const blend_func_t bf, gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return ;
	cur_elem = &layout->elem[id];

	rect_t box_sc = sc_rect(gui_layout_elem_comp_area_os(layout, id, XY0));

	switch (type)
	{
		case 0:
			draw_rect(box_sc, drawing_thickness, cur_elem->colour, bf, intensity_scaling(rect_min_side(box_sc), 24.));
			break;

		case 1:
			draw_rect_full(box_sc, drawing_thickness, cur_elem->colour, bf, 1.);
			break;

		case 2:
			draw_black_rect(box_sc, drawing_thickness, 1.);
			break;
	}

	ctrl_fromlayout_resizing(layout, id, 2);
}

int ctrl_button_fromlayout_offset(gui_layout_t *layout, const int id, const xy_t offset)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_button_chamf(cur_elem->label, gui_layout_elem_comp_area_os(layout, id, offset), cur_elem->colour);

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_button_invis_fromlayout_offset(ctrl_button_state_t *butt_state_ptr, gui_layout_t *layout, const int id, const xy_t offset)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_button_invis(gui_layout_elem_comp_area_os(layout, id, offset), butt_state_ptr);

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_checkbox_fromlayout(int *state, gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_checkbox(state, cur_elem->label, gui_layout_elem_comp_area_os(layout, id, XY0), cur_elem->colour);

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_radio_fromlayout_offset(int *state, gui_layout_t *layout, const int id, const int id_off, const xy_t offset)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_radio(state ? id+id_off==*state : 0, cur_elem->label, gui_layout_elem_comp_area_os(layout, id, offset), cur_elem->colour);

	if (ret && state)
		*state = id+id_off;

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_knob_fromlayout(double *v, gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_knob(v, (knob_t *) cur_elem->data, gui_layout_elem_comp_area_os(layout, id, XY0), cur_elem->colour);

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_textedit_fromlayout_in_rect(gui_layout_t *layout, const int id, rect_t box_os)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_textedit(cur_elem->data, box_os, cur_elem->colour);
	draw_rect(sc_rect(box_os), drawing_thickness, cur_elem->colour, cur_blend, 0.25 * intensity_scaling(rect_min_side(sc_rect(box_os)), 24.));	// FIXME maybe use te.rect_brightness instead?

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

int ctrl_textedit_fromlayout(gui_layout_t *layout, const int id)
{
	return ctrl_textedit_fromlayout_in_rect(layout, id, gui_layout_elem_comp_area_os(layout, id, XY0));
}

// Selection menu functions

void gui_layout_selmenu_set_open(const int state, gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	if (cur_elem->data)
		((ctrl_selectmenu_state_t *) cur_elem->data)->next_open = state;
}

void gui_layout_selmenu_set_count(const int count, gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	if (cur_elem->data)
		((ctrl_selectmenu_state_t *) cur_elem->data)->count = count;
}

void gui_layout_selmenu_set_entry_id(const int entry_id, gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	if (cur_elem->data)
		((ctrl_selectmenu_state_t *) cur_elem->data)->sel_id = entry_id;
}

int ctrl_selmenu_fromlayout(gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (ctrl_fromlayout_resizing(layout, id, 1))
		return 0;
	cur_elem = &layout->elem[id];

	ret = ctrl_selectmenu(cur_elem->data, gui_layout_elem_comp_area_os(layout, id, XY0), cur_elem->colour);

	ctrl_fromlayout_resizing(layout, id, 2);
	return ret;
}

void draw_selmenu_entry_fromlayout(const int i, const char *label, gui_layout_t *layout, const int id)
{
	layout_elem_t *cur_elem=NULL;
	ctrl_selectmenu_state_t *selmenu_data;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	selmenu_data = cur_elem->data;
	draw_selectmenu_entry(selmenu_data, gui_layout_elem_comp_area_os(layout, id, XY0), cur_elem->colour, i, label);
}

// Unimplemented element functions

char *gui_layout_make_code_for_unimp_elem(gui_layout_t *layout)
{
	int id;
	size_t str_as=0;
	char *str=NULL;

	if (layout==NULL)
		return str;

	for (id=0; id < layout->elem_as; id++)
	{
		if (layout->elem[id].type && layout->elem[id].implemented==0)
		{
			switch (layout->elem[id].type)
			{
				case gui_type_none:
					break;

				case gui_type_label:
					sprintf_realloc(&str, &str_as, 1, "\tdraw_label_fromlayout(&layout, %d, ALIG_LEFT | MONODIGITS);\n", id);
					break;

				case gui_type_rect:
					sprintf_realloc(&str, &str_as, 1, "\tdraw_rect_fromlayout(1, &layout, %d);\n", id);
					break;

				case gui_type_button:
					sprintf_realloc(&str, &str_as, 1, "\tif (ctrl_button_fromlayout(&layout, %d))\n\t{\n\t}\n", id);
					break;

				case gui_type_checkbox:
					sprintf_realloc(&str, &str_as, 1, "\tstatic int state=0;\n");
					sprintf_realloc(&str, &str_as, 1, "\tctrl_checkbox_fromlayout(&state, &layout, %d);\n", id);
					break;

				case gui_type_radio:
					sprintf_realloc(&str, &str_as, 1, "\tctrl_radio_fromlayout(&state, &layout, %d);\n", id);
					break;

				case gui_type_knob:
					sprintf_realloc(&str, &str_as, 1, "\tstatic double value=NAN;\n");
					sprintf_realloc(&str, &str_as, 1, "\tctrl_knob_fromlayout(&value, &layout, %d);\n", id);
					break;

				case gui_type_textedit:
					sprintf_realloc(&str, &str_as, 1, "\tctrl_textedit_fromlayout(&layout, %d);\n", id);
					break;

				case gui_type_selmenu:
					sprintf_realloc(&str, &str_as, 1, "\tgui_layout_selmenu_set_count(count, &layout, %d);\n\tif (ctrl_selmenu_fromlayout(&layout, %d))\n\t{\n\t\tsel_index = get_selmenu_selid_fromlayout(&layout, %d);\n\t}\n\n\tfor (i=0; i < count; i++)\n\t\tdraw_selmenu_entry_fromlayout(i, menu_label[i], &layout, %d);", id, id, id, id);
					break;
			}
		}
	}

	return str;
}

void gui_layout_unimplemented_elems(gui_layout_t *layout)
{
	int id;

	if (layout==NULL)
		return;

	//if (layout->edit_on==0)
	//	return ;

	for (id=0; id < layout->elem_as; id++)
	{
		if (layout->elem[id].type && layout->elem[id].implemented==0)
		{
			switch (layout->elem[id].type)
			{
				case gui_type_none:
					break;

				case gui_type_label:
					draw_label_fromlayout(layout, id, ALIG_LEFT | MONODIGITS);
					break;

				case gui_type_button:
					ctrl_button_fromlayout(layout, id);
					break;

				case gui_type_checkbox:
					ctrl_checkbox_fromlayout(NULL, layout, id);
					break;

				case gui_type_radio:
					ctrl_radio_fromlayout(NULL, layout, id);
					break;

				case gui_type_knob:
					ctrl_knob_fromlayout(NULL, layout, id);
					break;

				case gui_type_rect:
				case gui_type_textedit:
					draw_rect_fromlayout(1, layout, id);
					break;

				case gui_type_selmenu:
					ctrl_selmenu_fromlayout(layout, id);
					break;
			}

			layout->elem[id].implemented = 0;
		}
	}
}

void gui_set_control_label(const char *new_label, gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)	// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	sprintf_realloc(&cur_elem->label, &cur_elem->label_as, 0, "%s", new_label);
	//cur_elem->label_set = 1;
}

void gui_set_control_colour(col_t colour, gui_layout_t *layout, const int id)
{
	int ret;
	layout_elem_t *cur_elem=NULL;

	if (check_elem_id_validity(layout, id, 0)==0)	// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	cur_elem->colour = colour;
}

void gui_printf_to_label(gui_layout_t *layout, const int id, const int append, const char *format, ...)
{
	int ret;
	layout_elem_t *cur_elem=NULL;
	va_list args;

	if (check_elem_id_validity(layout, id, 0)==0)	// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	va_start(args, format);
	vsprintf_realloc(&cur_elem->label, &cur_elem->label_as, append, format, args);
	va_end(args);
}

void gui_round_elem_posdim(gui_layout_t *layout, const int id, const double rounding)
{
	int ret;
	xy_t rv = set_xy(rounding);
	layout_elem_t *cur_elem=NULL;
	xy_t *pos_ptr, *dim_ptr;

	if (check_elem_id_validity(layout, id, 0)==0)	// if id isn't a valid layout element
		return ;
	cur_elem = &layout->elem[id];

	pos_ptr = get_elem_posdim_ptr(layout, id, 0);
	dim_ptr = get_elem_posdim_ptr(layout, id, 1);
	*pos_ptr = div_xy(nearbyint_xy(mul_xy(*pos_ptr, rv)), rv);
	*dim_ptr = div_xy(nearbyint_xy(mul_xy(*dim_ptr, rv)), rv);
	update_ctrl_resizing_rect_positions(&cur_elem->resize_ctrl, gui_layout_elem_comp_area(layout, id));
}

int print_to_layout_label(gui_layout_t *layout, const int id, const char *format, ...)
{
	va_list args;
	int len, ret;
	layout_elem_t *cur_elem=NULL;

	ret = check_elem_id_validity(layout, id, 0);
	if (ret==0)
		return ret;
	cur_elem = &layout->elem[id];

	va_start(args, format);
	len = vsnprintf(NULL, 0, format, args);	// gets the printed length without actually printing
	va_end(args);

	alloc_enough(&cur_elem->label, len+1, &cur_elem->label_as, sizeof(char), 1.25);

	va_start(args, format);
	vsprintf(cur_elem->label, format, args);
	va_end(args);

	return ret;
}

int print_to_layout_textedit(gui_layout_t *layout, const int id, const int clear_undo, const char *format, ...)
{
	va_list args;
	int len, ret;
	char *string;
	textedit_t *te;

	ret = check_elem_id_validity(layout, id, 0);
	if (ret==0)
		return ret;
	te = (textedit_t *) layout->elem[id].data;

	va_start(args, format);
	len = vsnprintf(NULL, 0, format, args);	// gets the printed length without actually printing
	va_end(args);

	string = calloc(len+1, sizeof(char));

	va_start(args, format);
	vsprintf(string, format, args);
	va_end(args);

	if (clear_undo)
		textedit_clear_then_set_new_text(te, string);
	else
		textedit_set_new_text(te, string);

	te->return_flag = 0;			// suppresses the flagging of modifications in the next ctrl_textedit call

	free(string);

	return ret;
}

int print_to_layout_textedit_append(gui_layout_t *layout, const int id, const int clear_undo, const char *format, ...)
{
	int ret;
	va_list args;
	textedit_t *te;
	buffer_t buf={0};

	ret = check_elem_id_validity(layout, id, 0);
	if (ret==0)
		return ret;
	te = (textedit_t *) layout->elem[id].data;

	bufprintf(&buf, "%s", te->string);

	va_start(args, format);
	vbufprintf(&buf, format, args);
	va_end(args);

	ret = print_to_layout_textedit(layout, id, clear_undo, "%s", buf.buf);

	free_buf(&buf);

	return ret;
}

textedit_t *get_textedit_fromlayout(gui_layout_t *layout, const int id)
{
	textedit_t *te;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return NULL;

	te = (textedit_t *) layout->elem[id].data;
	return te;
}

char *get_textedit_string_fromlayout(gui_layout_t *layout, const int id)
{
	textedit_t *te;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return NULL;

	te = (textedit_t *) layout->elem[id].data;
	return te->string;
}

void set_cur_textedit_fromlayout(gui_layout_t *layout, const int id)
{
	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return;

	cur_textedit = (textedit_t *) layout->elem[id].data;
}

knob_t *get_knob_data_fromlayout(gui_layout_t *layout, const int id)
{
	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return NULL;

	return (knob_t *) layout->elem[id].data;
}

void set_knob_circularity_fromlayout(int circular, gui_layout_t *layout, const int id)
{
	knob_t *knob_data;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;

	knob_data = (knob_t *) layout->elem[id].data;
	knob_data->circular = circular;
}

int get_selmenu_selid_fromlayout(gui_layout_t *layout, const int id)
{
	ctrl_selectmenu_state_t *selmenu_data;

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return -1;

	selmenu_data = (ctrl_selectmenu_state_t *) layout->elem[id].data;
	return selmenu_data->sel_id;
}

void gui_layout_registry_add(gui_layout_t *layout, const char *layout_name)
{
	int i;

	// If the registry hasn't been cleared in the previous frame we don't register
	if (fb->frame_count > layout_reg.last_reset_frame+1)
		return;

	if (layout_name)
	{
		i = layout_reg.reg_count;
		alloc_enough(&layout_reg.reg, layout_reg.reg_count+=1, &layout_reg.reg_as, sizeof(layout_reg_entry_t), 2.);
		strcpy(layout_reg.reg[i].name, layout_name);
		layout_reg.reg[i].lp = layout;

		if (layout==layout_reg.sel_p)
			layout_reg.sel = i;
	}
}

void gui_layout_registry_reset()
{
	memset(layout_reg.reg, 0, layout_reg.reg_count * sizeof(layout_reg_entry_t));
	layout_reg.reg_count = 0;
	layout_reg.last_reset_frame = fb->frame_count;
}

rect_t fit_sublayout_into_area(rect_t area0, gui_layout_t *sublayout, int main_area_id, xy_t offset, int save_os)
{
	rect_t area1;

	if (check_elem_id_validity(sublayout, main_area_id, 0)==0)
	{
		fprintf_rl(stderr, "Invalid element #%d for sublayout in fit_sublayout_into_area()\n", main_area_id);
		return area0;
	}

	area1 = gui_layout_elem_comp_area(sublayout, main_area_id);

	area0 = fit_rect_in_area(get_rect_dim(area1), area0, offset);

	if (save_os)
		sublayout->offset = fit_into_area(area0, area1, 0., &sublayout->sm);
	else
		fit_into_area(area0, area1, 0., NULL);

	return area0;
}

rect_t fit_sublayout_into_layout_rect(gui_layout_t *toplayout, int rect_id, gui_layout_t *sublayout, int main_area_id, xy_t offset)
{
	rect_t area0={0}, area1;

	if (check_elem_id_validity(toplayout, rect_id, 0)==0)
	{
		fprintf_rl(stderr, "Invalid element #%d for toplayout in fit_sublayout_into_layout_rect()\n", rect_id);
		return area0;
	}

	if (check_elem_id_validity(sublayout, main_area_id, 0)==0)
	{
		fprintf_rl(stderr, "Invalid element #%d for sublayout in fit_sublayout_into_layout_rect()\n", main_area_id);
		return area0;
	}

	area0 = gui_layout_elem_comp_area_os(toplayout, rect_id, XY0);
	area1 = gui_layout_elem_comp_area(sublayout, main_area_id);

	area0 = fit_rect_in_area(get_rect_dim(area1), area0, offset);
	sublayout->offset = fit_into_area(area0, area1, 0., &sublayout->sm);

	return area0;
}

xy_t fit_area_into_layout_rect(gui_layout_t *layout, const int id, rect_t area1, xy_t offset, double *sm)
{
	rect_t area0;
	xy_t pos={0};
	*sm = 1.;

	if (check_elem_id_validity(layout, id, 0)==0)
	{
		fprintf_rl(stderr, "Invalid element #%d for layout in fit_area_into_layout_rect()\n", id);
		return pos;
	}

	area0 = gui_layout_elem_comp_area_os(layout, id, XY0);
	area0 = fit_rect_in_area(get_rect_dim(area1), area0, offset);
	pos = fit_into_area(area0, area1, 0., sm);

	return pos;
}

void gui_parse_knob_data_string(gui_layout_t *layout, const int id, const char *line, buffer_t *buferr)
{
	knob_t *knob_data;
	int n;
	const char *p;
	char b[32]={0};

	if (check_elem_id_validity(layout, id, 0)==0)		// if id isn't a valid layout element
		return ;

	knob_data = (knob_t *) layout->elem[id].data;

	n = 0;
	if (sscanf(line, "%lg %lg %lg %s %n", &knob_data->min, &knob_data->default_value, &knob_data->max, b, &n)>=3)
	{
		knob_data->func = knob_func_name_to_ptr(b);
		if (knob_data->func == NULL)
			knob_data->func = knobf_linear;

		if (knob_data->func==NULL)
		{
			bufprintf(buferr, "The knob function name '%s' isn't valid in line \"%s\"\n", b, line);
			return ;
		}

		if (knob_data->min >= knob_data->max)
		{
			bufprintf(buferr, "The maximum value of a knob cannot be lower than the minimum in line \"%s\"\n", line);
			return ;
		}

		if (knob_data->min > knob_data->default_value || knob_data->default_value > knob_data->max)
		{
			bufprintf(buferr, "The default value of a knob cannot be outside of the [min , max] range in line \"%s\"\n", line);
			return ;
		}

		if (knob_data->func==knobf_log && MINN(knob_data->min, knob_data->default_value) <= 0.)
		{
			bufprintf(buferr, "When the knob function is logarithmic no value can be 0 or lower in line \"%s\"\n", line);
			return ;
		}

		if (n==0)
			n = strlen(line);
		p = &line[n];
		free(knob_data->fmt_str);
		knob_data->fmt_str = make_string_copy(p[0] ? p : VALFMT_DEFAULT);
	}
	else
	{
		bufprintf(buferr, "The 'knob' command needs at least the first 3 arguments: '<min> <default> <max> (<function (linear|log|recip)>) (<format string>)' at line \"%s\"\n", line);
		return ;
	}
}
