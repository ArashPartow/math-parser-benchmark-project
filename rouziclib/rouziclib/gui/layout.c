int dialog_enclosing_frame(xy_t offset, double sm, rect_t main_frame, double margin, char *label, col_t colour)
{
	rect_t full_frame, box_os;

	full_frame = rect_add_margin(main_frame, set_xy(margin));
	box_os = offset_scale_rect(full_frame, offset, sm);
	if (check_box_on_screen(box_os)==0)
		return 1;

	display_dialog_enclosing_frame(sc_rect(box_os), sm*zc.scrscale, label, colour);

	return 0;
}

rect_t make_title_rect(rect_t main_frame, double title_pos, double title_height)
{
	return make_rect_off( xy(get_rect_centre(main_frame).x, title_pos), xy(get_rect_dim(main_frame).x, title_height), xy(0.5, 0.) );
}

xy_t get_grid_position(xy_t orig, int index, xyi_t grid_count, xy_t step, int horizontal)
{
	if (horizontal)
	{
		if (grid_count.x==0)
			grid_count.x = 1;

		return mad_xy(step, xy( index % grid_count.x, index / grid_count.x ), orig);
	}
	else
	{
		if (grid_count.y==0)
			grid_count.y = 1;

		return mad_xy(step, xy( index / grid_count.y, index % grid_count.y ), orig);
	}
}

rect_t get_grid_cell_rect(xyi_t ip, xy_t origin, xy_t cell_dim)
{
	rect_t r;

	r.p0 = mad_xy(xyi_to_xy(ip), cell_dim, origin);
	r.p1 = add_xy(r.p0, cell_dim);

	return r;
}

xyi_t get_grid_index_at_point(xy_t p, xy_t origin, xy_t cell_dim)
{
	return xy_to_xyi(floor_xy(div_xy( sub_xy(p, origin) , cell_dim )));
}

recti_t get_grid_index_rect(rect_t r, xy_t origin, xy_t cell_dim)
{
	return recti( get_grid_index_at_point(r.p0, origin, cell_dim), get_grid_index_at_point(r.p1, origin, cell_dim) );
}
