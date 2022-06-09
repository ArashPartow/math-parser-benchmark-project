int equal_ctrl_id(ctrl_id_t a, ctrl_id_t b)	// returns 1 if the controls are identical
{
	if (a.type != b.type)
		return 0;

	switch (a.type)
	{
		case 0:
			if (equal_rect(a.box, b.box) == 0)
				return 0;
			break;

		case 1:
			if (equal_xy(a.pos, b.pos) == 0 || a.radius != b.radius)
				return 0;
			break;
	}

	if (a.id != b.id)
		return 0;

	return 1;
}

int check_ctrl_id(rect_t box, xy_t pos, double radius, mouse_t mouse, int type)	// returns 0 if the current control should be ignored
{
	int mouse_hovers = 0;
	double d_current, d_hovnew;

	mouse.ctrl_id->current.type = type;
	mouse.ctrl_id->current.box = box;
	mouse.ctrl_id->current.pos = pos;
	mouse.ctrl_id->current.radius = radius;

	// Increment current.id if needed to separate controls with the same box or circle
	if (mouse.ctrl_id->hover.type == type)
	{
		// if this control has the same box or position and size and type as the previous hovered control in this frame
		if ((type==0 && equal_rect(mouse.ctrl_id->hover_new.box, box)) || (type==1 && equal_xy(mouse.ctrl_id->hover_new.pos, pos) && mouse.ctrl_id->hover_new.radius == radius))
			mouse.ctrl_id->current.id++;				// increment the ID to differentiate between stacked same-box controls
		// else if it matches the previous frame's hovered control
		else if ((type==0 && equal_rect(mouse.ctrl_id->hover.box, box)) || (type==1 && equal_xy(mouse.ctrl_id->hover.pos, pos) && mouse.ctrl_id->hover.radius == radius))
		{
			if (mouse.ctrl_id->hover_box_matched==0)	// if this control is the first one that matches the previous frame's hover control
				mouse.ctrl_id->hover_box_matched = 1;	// only mark it as matched to avoid incrementing once too many
			else
				mouse.ctrl_id->current.id++;		// otherwise increment
		}
	}

	// Find if the mouse hovers the control (all this is ultimately discarded in mouse_pre_event_proc() if the lmb is down)
	switch (type)
	{
		case 0:
			mouse_hovers = check_point_within_box(mouse.u, box);
			break;

		case 1:
			d_current = hypot_xy(mouse.u, pos);
			d_hovnew = (mouse.ctrl_id->hover_new.type == type) ? hypot_xy(mouse.u, mouse.ctrl_id->hover_new.pos) : FLT_MAX;

			if (d_current <= radius && d_current <= d_hovnew)
				mouse_hovers = 1;
			break;
	}

	// Set hover_new to current if the mouse is hovering
	if (mouse_hovers)						// if the mouse hovers the control
		mouse.ctrl_id->hover_new = mouse.ctrl_id->current;	// the hovered ID becomes the ID of the current control

	// Compare current and hover
	if (equal_ctrl_id(mouse.ctrl_id->current, mouse.ctrl_id->hover))
	{
		mouse.ctrl_id->hover_ided = 1;	// this lets anyone who cares know that the one control being hovered has definitively been identified
		return 1;
	}
	return 0;
}

void proc_mouse_ctrl_button(int mb, int clicks, ctrl_button_state_t *state, const int cur_point_within_box, const int orig_point_within_box)
{
	if (orig_point_within_box && mb != -1)
		state->orig = 1;

	if (cur_point_within_box)
	{
		state->over = 1;

		if (mb != -1)					// if there is clicking going on
			if (orig_point_within_box)		// check the click originated in the same box
			{
				if (mb > 0)
					state->down = 1;

				if (mb == 2)
					state->once = 1;

				if (mb == -2)
					state->uponce = 1;

				if (mb == -2 && clicks == 2)
					state->doubleclick = 1;
			}
			else
				state->over = 0;		// if the click originated somewhere else we don't even care if the mouse is now over the box
	}
}

ctrl_button_state_t *proc_mouse_rect_ctrl_lrmb(rect_t box, mouse_t mouse)
{
	static ctrl_button_state_t state[2];
	int cur_point_within_box, orig_point_within_box;

	memset(state, 0, sizeof(state));

	if (check_ctrl_id_rect(box, mouse)==0)
		return state;

	orig_point_within_box = check_point_within_box(mouse.b.orig, box);
	cur_point_within_box = check_point_within_box(mouse.u, box);

	proc_mouse_ctrl_button(mouse.b.lmb, mouse.b.clicks, &state[0], cur_point_within_box, orig_point_within_box);
	proc_mouse_ctrl_button(mouse.b.rmb, mouse.b.clicks, &state[1], cur_point_within_box, orig_point_within_box);

	return state;
}

ctrl_button_state_t *proc_mouse_circ_ctrl_lrmb(xy_t pos, double radius, mouse_t mouse, const int check_bypass)
{
	static ctrl_button_state_t state[2];
	int cur_point_within_circle, orig_point_within_circle;

	memset(state, 0, sizeof(state));

	// the check_bypass is necessary to get button states while dragging and releasing (uponce)
	if (check_ctrl_id_circle(pos, radius, mouse)==0 && check_bypass==0)
		return state;

	cur_point_within_circle = check_bypass | check_point_within_circle(mouse.u, pos, radius);
	orig_point_within_circle = check_bypass | check_point_within_circle(mouse.b.orig, pos, radius);
	proc_mouse_ctrl_button(mouse.b.lmb, mouse.b.clicks, &state[0], cur_point_within_circle, orig_point_within_circle);
	proc_mouse_ctrl_button(mouse.b.rmb, mouse.b.clicks, &state[1], cur_point_within_circle, orig_point_within_circle);

	return state;
}

ctrl_knob_state_t proc_mouse_knob_ctrl(rect_t box, mouse_t mouse)
{
	ctrl_knob_state_t state;

	memset(&state, 0, sizeof(state));

	if (check_ctrl_id_rect(box, mouse)==0)
		return state;

	if (check_point_within_box(mouse.b.orig, box))	// check the click originated in the same box
	{
		if (mouse.b.clicks == 2)
		{
			if (mouse.b.lmb >= 2)
				state.doubleclick = 1;
		}
		else
		{
			if (mouse.b.lmb >= 1)
			{
				//state.vert_delta = (mouse.u.y - mouse.prev_u.y) / get_rect_dim(box).y;
				state.vert_delta = -mouse.d.y;					

				if (mouse.mod_key[mouse_mod_shift])
				{
					state.vert_delta *= 1./32.;

					if (mouse.mod_key[mouse_mod_ctrl])
						state.vert_delta *= 1./256.;
				}
			}

			if (mouse.b.lmb > 0)
				state.down = 1;

			if (mouse.b.lmb == 2)
				state.downonce = 1;

			if (mouse.b.lmb == -2)
				state.uponce = 1;

			if (mouse.b.rmb == 2)
				state.rightclick = 1;
		}
	}

	return state;
}

int proc_mouse_draggable_ctrl(ctrl_drag_state_t *state, rect_t box, mouse_t mouse)
{
	int ret=0, ctrl_id_check;

	state->offset = XY0;

	ctrl_id_check = check_ctrl_id_rect(box, mouse);

	state->uponce = 0;

	if (mouse.b.lmb < 0)				// if LMB is released
	{
		if (state->down)
			state->uponce = 1;

		state->down = 0;			// the control is deselected
		state->click_offset = set_xy(0.5);
	}

	if (mouse.b.lmb==2 && ctrl_id_check && mouse.mouse_focus_flag==1)		// if LMB was just clicked and the control was hovered
	{
		state->down = 1;			// the control is now selected
		state->click_offset = pos_to_rect_ratio(mouse.u, box);
	}

	if (mouse.b.lmb==1 && state->down)		// if the control is being dragged
	{
		mouse.ctrl_id->hover_ided = 1;	// this lets anyone who cares know that the one control being hovered has definitively been identified
		xy_t new_pos = get_rect_centre(make_rect_off(mouse.u, state->dim, state->click_offset));
		//state->offset = mul_xy(state->freedom, sub_xy(mouse.u, mouse.prev_u) );
		state->offset = mul_xy(state->freedom, sub_xy(new_pos, state->pos) );
		state->pos = add_xy(state->pos, state->offset);
		ret = 1;
	}

	state->over = check_point_within_box(mouse.u, box) && ctrl_id_check && state->down==0;

	return ret;
}

int proc_mouse_xy_ctrl(rect_t box, mouse_t mouse, xy_t *pos, int *lmb, int *rmb)
{
	int change = 0;

	*pos = XY0;
	*lmb = 0;
	*rmb = 0;

	if (check_ctrl_id_rect(box, mouse)==0)
		return 0;

	*pos = mouse.u;
	*lmb = mouse.b.lmb;
	*rmb = mouse.b.rmb;

	if (*lmb != -1 || *rmb != -1)
		change = 1;

	return change;
}

ctrl_button_state_t proc_mouse_circular_ctrl(xy_t *pos, double radius, mouse_t mouse, int dragged)
{
	ctrl_button_state_t butt={0};

	butt = proc_mouse_circ_ctrl_lrmb(*pos, radius, mouse, dragged)[0];

	if (butt.down)
		*pos = add_xy(*pos, sub_xy(mouse.u, mouse.prev_u));	// TODO maybe replicate changes done in proc_mouse_draggable_ctrl()

	return butt;
}
