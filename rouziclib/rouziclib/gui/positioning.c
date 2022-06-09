xy_t offset_scale2(xy_t pos, xy_t offset, xy_t sm2)
{
	return mad_xy(pos, sm2, offset);
}

xy_t offset_scale(xy_t pos, xy_t offset, double sm)
{
	return offset_scale2(pos, offset, set_xy(sm));
}

rect_t offset_scale2_rect(rect_t r, xy_t offset, xy_t sm2)
{
	return rect(	offset_scale2(r.p0, offset, sm2),
			offset_scale2(r.p1, offset, sm2));
}

rect_t offset_scale_rect(rect_t r, xy_t offset, double sm)
{
	return offset_scale2_rect(r, offset, set_xy(sm));
}

xy_t offset_scale_inv(xy_t pos, xy_t offset, double sm)
{
	return div_xy( sub_xy(pos, offset) , set_xy(sm));
}

rect_t offset_scale_inv_rect(rect_t r, xy_t offset, double sm)
{
	return rect(	offset_scale_inv(r.p0, offset, sm),
			offset_scale_inv(r.p1, offset, sm));
}
