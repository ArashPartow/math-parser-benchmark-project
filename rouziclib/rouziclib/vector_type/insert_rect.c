rect_t *rect_insert=NULL;	// array that contains the rectangles matching the screen positions of the provided insert-space characters
int insert_rect_alloc=0;

void reset_insert_rect_array()
{
	if (rect_insert)
		memset(rect_insert, 0xFF, insert_rect_alloc*sizeof(rect_t));
}

void report_insert_rect_pos(xy_t pos, xy_t dim, int bidi, int index)
{
	alloc_enough(&rect_insert, index+1, &insert_rect_alloc, sizeof(rect_t), 2);

	rect_insert[index] = make_rect_off( pos, dim, xy(bidi==-2 ? 1. : 0., 0.) );
}

int parse_insert_rect_charseq(xy_t p, xy_t *off, double scale, int bidi, int cp0, const char *string)
{
	size_t i, ir=0;
	uint32_t cn;
	double width=0.;
	letter_t *l;
	xy_t pos = add_xy(p, *off);

	if (l = get_letter(font, cp0))
		if (l->obj)
			width = l->width;

	for (i=0; string[i]!='\0'; i++)
	{
		cn = utf8_to_unicode32(&string[i], &i);

		if (cn >= cp_ins_start && cn < cp_ins_end)	// extra space characters add to the width
		{
			ir = i+1;

			if (l = get_letter(font, cn))
				if (l->obj)
				{
					width += l->width;
					off->x += l->width * scale;
				}
		}
		else if (cn >= cp_ins_index_base && cn <= cp_ins_index_base+239)	// index, meaning the end of a valid sequence
		{
			report_insert_rect_pos(pos, mul_xy(xy(width, -6.), set_xy(scale)), bidi, cn - cp_ins_index_base);
			return i+1;
		}
		else
			return ir;
	}

	return ir;
}

rect_t get_insert_rect_zc(zoom_t zc, int index)
{
	if (index < 0 || index >= insert_rect_alloc || rect_insert==NULL)
		return rect( xy(NAN, NAN) , xy(NAN, NAN) );

	return wc_rect(rect_insert[index]);
}

rect_t insert_rect_change_height(rect_t r, double low, double high)
{
	double y, m;

	y = r.p0.y;
	m = (r.p1.y - r.p0.y) / 6.;

	r.p0.y = low * m + y;
	r.p1.y = high * m + y;

	return r;
}
