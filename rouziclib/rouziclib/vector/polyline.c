int ctrl_polyline(polyline_edit_t *pl, rect_t box, xy_t offset, double sm)
{
	xy_t pos;
	int i, j, k, lmb, rmb, ds_alloc;
	char ds_label[8];

	box = offset_scale_rect(box, offset, sm);

	if (check_box_box_intersection(box, zc.corners)==0)
		return 0;

	proc_mouse_xy_ctrl(box, mouse, &pos, &lmb, &rmb);
	pos = offset_scale_inv(pos, offset, sm);

	if (lmb==2)
	{
		// create new dot
		ds_alloc = pl->pv_alloc;
		alloc_enough(&pl->pv, pl->pv_count+=1, &pl->pv_alloc, sizeof(xy_t), 1.5);
		alloc_enough(&pl->ds, pl->pv_count, &ds_alloc, sizeof(ctrl_drag_state_t), 1.5);

		pl->pv[pl->pv_count-1] = pos;
		pl->ds[pl->pv_count-1] = make_drag_state(offset_scale(pos, offset, sm), xy(1., 1.));

		if (mouse.mod_key[mouse_mod_shift]==0)
		{
			if (pl->pv_count >= 2)
			{
				alloc_enough(&pl->line, pl->line_count+=1, &pl->line_alloc, sizeof(xyi_t), 1.5);
				pl->line[pl->line_count-1] = xyi(pl->pv_count-2, pl->pv_count-1);
			}
		}
	}

	for (i=0; i < pl->pv_count; i++)
	{
		sprintf(ds_label, "p%d", i);
		ctrl_drag_set_dim(&pl->ds[i], set_xy(0.25 * sm));
		if (ctrl_draggable(&pl->ds[i]))
			pl->pv[i] = offset_scale_inv(pl->ds[i].pos, offset, sm);

		// Erase a point and any line referencing it
		if (pl->ds[i].down && mouse.mod_key[mouse_mod_ctrl])
		{
			for (j=i; j < pl->pv_count-1; j++)
			{
				pl->pv[j] = pl->pv[j+1];
				pl->ds[j] = pl->ds[j+1];
			}

			pl->pv_count--;

			// remove referencing lines
			for (j=0; j < pl->line_count; j++)
				if (pl->line[j].x == i || pl->line[j].y == i)
				{
					for (k=j; k < pl->line_count-1; k++)
						pl->line[k] = pl->line[k+1];

					pl->line_count--;
				}

			for (j=0; j < pl->line_count; j++)	// decrement any reference beyond i
			{
				if (pl->line[j].x > i)
					pl->line[j].x--;

				if (pl->line[j].y > i)
					pl->line[j].y--;
			}
		}
	}

	for (i=0; i < pl->line_count; i++)
		draw_line_thin(sc_xy(offset_scale(pl->pv[pl->line[i].x], offset, sm)), sc_xy(offset_scale(pl->pv[pl->line[i].y], offset, sm)), drawing_thickness, GUI_COL_DEF, cur_blend, 1.);

	return 0;
}

void free_polyline(polyline_edit_t *pl)
{
	free(pl->pv);
	free(pl->line);
	free(pl->ds);
	memset(pl, 0, sizeof(polyline_edit_t));
}

char *sprint_polyline(polyline_edit_t *pl)
{
	int i, prev_end_point=-1;
	size_t string_alloc=0;
	char *string=NULL, b1[32], b2[32];

	for (i=0; i < pl->pv_count; i++)
		sprintf_realloc(&string, &string_alloc, 1, "p%d\t%s\t%s\n", i+1, sprint_fractional_12(b1, pl->pv[i].x), sprint_fractional_12(b2, pl->pv[i].y));

	for (i=0; i < pl->line_count; i++)
	{
		if (pl->line[i].x == prev_end_point)
			sprintf_realloc(&string, &string_alloc, 1, " p%d", pl->line[i].y+1);
		else
		{
			if (i > 0)
				sprintf_realloc(&string, &string_alloc, 1, "\n");

			sprintf_realloc(&string, &string_alloc, 1, "lines p%d p%d", pl->line[i].x+1, pl->line[i].y+1);
		}

		prev_end_point = pl->line[i].y;
	}
	//sprintf_realloc(&string, &string_alloc, 1, "\n");

	return string;
}

void round_polyline_pv(polyline_edit_t *pl, xy_t offset, double sm)
{
	int i;

	for (i=0; i < pl->pv_count; i++)
	{
		pl->pv[i].x = nearbyint(pl->pv[i].x * 12.) / 12.;
		pl->pv[i].y = nearbyint(pl->pv[i].y * 12.) / 12.;
		pl->ds[i] = make_drag_state(offset_scale(pl->pv[i], offset, sm), xy(1., 1.));
	}
}
