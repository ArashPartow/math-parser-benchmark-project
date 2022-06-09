void draw_titled_roundrect_frame(xy_t pos, double radius, xy_t c, xy_t space, lrgb_t colour, const blend_func_t bf)
{
	xy_t fr;

	fr = sub_xy(space, set_xy(3.5));
	c = sub_xy(c, set_xy(1.));
	pos.x -= 0.5*fr.x + 0.5;
	pos.y -= 0.5*fr.y + 3.5;

	draw_roundrect_frame(
			rect( pos, xy(pos.x+fr.x + c.x*space.x, pos.y+fr.y + c.y*space.y) ),
			rect( xy(pos.x+1., pos.y+17.5), xy(pos.x+fr.x-1. + c.x*space.x, pos.y+fr.y-1. + c.y*space.y)),
			9., 8., radius, colour, bf, 1.);
}

void draw_label(const uint8_t *label, rect_t box, col_t colour, const int mode)
{
	double intensity, scale = rect_min_side(box), total_scale = scale*zc.scrscale;

	if (total_scale < 1.)
		return ;

	intensity = intensity_scaling(total_scale, 24.);

	//box.p0.x += 2.*scale/LINEVSPACING;
	//box.p1.x -= 2.*scale/LINEVSPACING;

	draw_string_bestfit(font, label, sc_rect(box), 0., 1e30*zc.scrscale, colour, 1.*intensity, drawing_thickness, mode, NULL);
}

void draw_text_block(const uint8_t *label, rect_t box, col_t colour, const int mode, double thresh)
{
	double intensity, scale = rect_min_side(box), total_scale = scale*zc.scrscale;

	if (total_scale < 1.)
		return ;

	intensity = intensity_scaling(total_scale, 24.);

	//box.p0.x += 2.*scale/LINEVSPACING;
	//box.p1.x -= 2.*scale/LINEVSPACING;

	draw_string_fixed_thresh(font, label, sc_rect(box), thresh, 1e30*zc.scrscale, colour, 1.*intensity, drawing_thickness, mode, NULL);
}

void draw_text_at_scale(const uint8_t *label, rect_t box, col_t colour, const int mode, double thresh)
{
	double intensity, scale;

	scale = get_rect_dim(box).x / thresh;
	scale *= zc.scrscale;

	intensity = intensity_scaling(scale, 3.);

	draw_string(font, label, add_xy(xy(0., 8*scale), sc_xy(rect_p01(box))), scale, colour, intensity, drawing_thickness, mode, NULL);
}

void display_dialog_enclosing_frame(rect_t box_os, double scale, char *label, col_t colour)
{
	rect_t label_box;
	double intensity;

	intensity = intensity_scaling(rect_max_side(box_os), 32.);

	draw_rect(box_os, drawing_thickness, colour, cur_blend, intensity);

	label_box = rect_size_mul(box_os, set_xy(1. - 16./144.));

	draw_string_bestfit(font, label, label_box, 0., 1e30, colour, intensity * (0.5+0.5*erf((0.75-scale)*6.)), drawing_thickness, ALIG_CENTRE, NULL);
}

void draw_unit_grid_level(xy_t offset, double sm, double scale, col_t colour)
{
	double p, size_px;
	double thick, bright;
	xy_t start, end;
	rect_t corners;

	size_px = sm * scale * zc.scrscale;
	if (size_px < 7.)
		return ;

	if (sm*scale > 1. && size_px > 100000.)
		return ;

	thick = 0.01 * sm*scale;
	bright = 1.;

	if (size_px < 15.)
		bright *= (size_px - 5.) / (15. - 5.);	// linear transition

	thick *= zc.scrscale;
	thickness_limit(&thick, &bright, drawing_thickness);

	corners = offset_scale_inv_rect(zc.corners_dl, offset, sm);

	start = mul_xy(ceil_xy(div_xy(corners.p0, set_xy(scale))), set_xy(scale));
	start = offset_scale(start, offset, sm);
	end = zc.corners_dl.p1;

	for (p=start.x; p<=end.x; p+=sm*scale)
		draw_line_thin(sc_xy(xy(p, zc.corners_dl.p0.y)), sc_xy(xy(p, zc.corners_dl.p1.y)), drawing_thickness, colour, cur_blend, bright);

	for (p=start.y; p<=end.y; p+=sm*scale)
		draw_line_thin(sc_xy(xy(zc.corners_dl.p0.x, p)), sc_xy(xy(zc.corners_dl.p1.x, p)), drawing_thickness, colour, cur_blend, bright);
}

void draw_unit_grid_col(xy_t offset, double sm, col_t colour)
{
	draw_unit_grid_level(offset, sm, 1000000., colour);
	draw_unit_grid_level(offset, sm, 1000., colour);
	draw_unit_grid_level(offset, sm, 1., colour);
	draw_unit_grid_level(offset, sm, 1./12., colour);
	draw_unit_grid_level(offset, sm, 1./144., colour);
	draw_unit_grid_level(offset, sm, 1./1728., colour);
}

void draw_unit_grid_decimal(xy_t offset, double sm, col_t colour)
{
	draw_unit_grid_level(offset, sm, 1000000., colour);
	draw_unit_grid_level(offset, sm, 1000., colour);
	draw_unit_grid_level(offset, sm, 1., colour);
	draw_unit_grid_level(offset, sm, 1./10., colour);
	draw_unit_grid_level(offset, sm, 1./100., colour);
	draw_unit_grid_level(offset, sm, 1./1000., colour);
	draw_unit_grid_level(offset, sm, 1e-6, colour);
}

void draw_rangebox(rect_t box, const char *label, col_t colour)
{
	if (check_box_on_screen(box)==0 || rect_max_side(box)*zc.scrscale < 0.1)
		return ;

	const double bg_intensity = 2./144.;
	draw_rect_full(sc_rect(box), drawing_thickness, colour, cur_blend, bg_intensity);
	draw_rect(sc_rect(box), drawing_thickness, colour, cur_blend, 0.5 - bg_intensity*0.5);

	draw_string_bestfit(font, label, sc_rect(rect_size_mul(box, xy(10./12., 11./12.))), 0., 1e30*zc.scrscale, colour, 1. - bg_intensity, drawing_thickness, ALIG_CENTRE, NULL);
}
