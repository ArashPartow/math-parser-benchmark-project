// finds a line that fits within thresh and returns the end word index and the actual line width
double find_line_for_thresh(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, double thresh, int iw_start, int *iw_end)
{
	double line_length=0., ret=0.;
	int iw;

	for (iw=iw_start; line_length <= thresh && iw < ws.word_count; iw++)
	{
		line_length += get_word_length(font, string, ws, mode, iw_start, iw);

		if (line_length <= thresh)
		{
			*iw_end = iw;
			ret = line_length;
		}
	}

	// If the first word was over the threshold
	if (ret==0.)
	{
		*iw_end = iw_start;
		ret = line_length;
	}

	return ret;
}

// finds the number of lines that the string will be broken down to for a certain thresh
int find_line_count_for_thresh(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, double thresh, double *maxwidth)
{
	int iw, iw_end=0, line_count = 1;
	double width;

	if (maxwidth)
		*maxwidth = 0.;

	for (iw=0; iw < ws.word_count; )
	{
		width = find_line_for_thresh(font, string, ws, mode, thresh, iw, &iw_end);	// changes iw_end to the corrent ending word
		if (maxwidth)
			*maxwidth = MAXN(*maxwidth, width);
		iw = iw_end + 1;

		if (iw < ws.word_count)		// if there are still words left after this line
			line_count++;
	}

	return line_count;
}

int search_thresh(vector_font_t *font, search_thresh_t *st, double maxwidth, int nlines, double prec)
{
	double step;

	if (st->n > nlines)		// if we found a new minimum
	{
		st->min = st->thresh;
		st->min_n = st->n;
	}
	else				// or we found a new maximum
	{
		st->max = maxwidth;
		st->max_n = st->n;
	}

	step = 0.5 * (st->max - st->min);
	step = MINN(step, 7.5);		// cap by an arbitrary limit
	if (step < prec)
		return 1;		// stop the search

	if (st->n > nlines)		// if we found a new minimum
		st->thresh += step;
	else				// or we found a new maximum
		st->thresh -= step;

	return 0;			// keep the search going
}

// find best threshold for fitting a string into nlines
double find_string_width_for_nlines(vector_font_t *font, const uint8_t *string, word_stats_t ws, int *nlines, const int mode, double *lower_bound)	// doesn't handle \n or \t
{
	const double space_width = letter_width(font, 0., ' ', 1., mode);
	double maxwidth, total_end_length;
	search_thresh_t st;

	if (*nlines==1)
		return ws.full_length;

	if (ws.word_count==1)
		return ws.full_length;

	total_end_length = ws.full_length - (space_width+LETTERSPACING)*(*nlines-1);	// remove the widths of the spaces that will be turned into line breaks

	*lower_bound = total_end_length / (double) *nlines;	// the threshold couldn't possibly be lower than this
	*lower_bound = MAXN(*lower_bound, ws.max_word_length);	// or this

	memset(&st, 0, sizeof(search_thresh_t));
	st.min = *lower_bound;
	st.max = total_end_length;
	st.thresh = *lower_bound + 0.5*ws.aver_word_length;

	while (1)	// FIXME risks lasting forever, possibly if there are no glyphs to represent the string with
	{
		st.n = find_line_count_for_thresh(font, string, ws, mode, st.thresh, &maxwidth);

		if (search_thresh(font, &st, maxwidth, *nlines, 0.5))
			break;
	}

	*nlines = st.max_n;
	return st.max;
}

// finds best width by testing different line counts
double find_best_string_width(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, xy_t boxdim, int *nlines, double *scale_ratio)
{
	int i, prev_nlines, nl_start;
	double lower_bound=-1., thresh=0., prev_thresh, scale=0., prev_scale;

	if (ws.word_count==1)
	{
		*nlines = 1;
		*scale_ratio = MINN(boxdim.x / ws.full_length, boxdim.y / LINEVSPACING);	// find the scale needed for the text to fit the box with this many lines
		*scale_ratio = MINN(1., *scale_ratio);
		return ws.full_length;
	}

	if (boxdim.x!=0. && boxdim.y!=0.)
		nl_start = sqrt(ws.full_length / (boxdim.x*boxdim.y/LINEVSPACING)) * boxdim.y/LINEVSPACING;	// good starting point
	else
		nl_start = 1;

	nl_start = MAXN(1, MINN(nl_start, ws.word_count - 2));

	boxdim = abs_xy(boxdim);
	if (boxdim.x == 0.)
		boxdim.x = FLT_MAX;
	if (boxdim.y == 0.)
		boxdim.y = FLT_MAX;

	*scale_ratio = 1.;

	for (i=nl_start; lower_bound < thresh && i<=ws.word_count; i++)
	{
		prev_thresh = thresh;
		prev_scale = scale;
		prev_nlines = *nlines;
		*nlines = i;

		thresh = find_string_width_for_nlines(font, string, ws, nlines, mode, &lower_bound);

		if (thresh <= boxdim.x && *nlines*LINEVSPACING <= boxdim.y)		// if it fits without needing to lower the scale
			return thresh;

		scale = MINN(boxdim.x / thresh, boxdim.y / (*nlines*LINEVSPACING));	// find the scale needed for the text to fit the box with this many lines

		if (scale < prev_scale && *nlines > prev_nlines)			// if the previous attempt was the most suitable one
		{
			*nlines = prev_nlines;
			*scale_ratio = prev_scale;
			return prev_thresh;
		}
	}

	*scale_ratio = scale;
	return thresh;		// happens only if the longest line is a single word
}

void draw_string_maxwidth(vector_font_t *font, const uint8_t *string, word_stats_t ws, rect_t box, double scale, col_t colour, double intensity, double line_thick, const int mode, double maxwidth, int nlines, text_param_t *tp)
{
	int i, iw, il, len, line_start=0, line_end=0, line_iw_start=0, line_iw_end=0, new_lw;
	//const double space_width = letter_width(font, 0., ' ', 1., mode);
	double line_width;
	xy_t p;

	box = sort_rect(box);
	p.x = box.p0.x;

	// Horizontal alignment
	if ((mode&3)!=ALIG_LEFT)
	{
		if ((mode&3)==ALIG_CENTRE)
			p.x += (box.p1.x - box.p0.x) * 0.5;

		if ((mode&3)==ALIG_RIGHT)
			p.x += box.p1.x - box.p0.x;
	}

	// Vertical alignment
	if (mode & ALIG_TOP)
		p.y = box.p0.y + 8.*scale;
	else
	{
		p.y = 0.5*(box.p0.y+box.p1.y) + 3.*scale;			// puts the text right in the vertical middle of the box
		p.y -= (double) (nlines-1) * 0.5 * LINEVSPACING * scale;	// shift it up depending on the number of lines
	}

	for (iw=0; iw < ws.word_count; )
	{
		find_line_for_thresh(font, string, ws, mode, maxwidth, iw, &line_iw_end);	// changes line_iw_end to the corrent ending word

		line_start = ws.word_start[iw];
		line_end = ws.word_end[line_iw_end];
		len = 1 + line_end - line_start;
		draw_string_len(font, &string[line_start], p, scale, colour, intensity, line_thick, mode, len, tp);

		iw = line_iw_end + 1;

		p.y += LINEVSPACING * scale;	// move it down one line
	}
}

void draw_string_bestfit(vector_font_t *font, const uint8_t *string, rect_t box, const double border, const double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp)
{
	word_stats_t ws;
	double thresh, box_thresh, scale_ratio;
	int nlines;
	xy_t boxdim, p;

	if (string == NULL)
		return;

	ws = make_word_stats(font, string, mode);

	if (ws.max_word_length <= 0.)
		return ;

	box = sort_rect(box);
	box.p1 = sub_xy(box.p1, set_xy(border*scale));		// remove the border
	box.p0 = add_xy(box.p0, set_xy(border*scale));
	boxdim = abs_xy(div_xy(sub_xy(box.p1, box.p0), set_xy(scale)));

	thresh = find_best_string_width(font, string, ws, mode, boxdim, &nlines, &scale_ratio);
	thresh = double_add_ulp(thresh, 40);	// raises the threshold to deal with rounding errors, as much as 4 ULP have been found to be necessary, using more for safety

	box_thresh = fabs(box.p1.x - box.p0.x) / (scale*scale_ratio);				// thresh based on the calculated scale and the box
	if (box_thresh > thresh)								// if it's larger than thresh
	{
		thresh = box_thresh;								// box_thresh allows to fill the lines fully
		nlines = find_line_count_for_thresh(font, string, ws, mode, thresh, NULL);	// then the number of lines must be recounted
	}

	draw_string_maxwidth(font, string, ws, box, scale*scale_ratio, colour, intensity, line_thick, mode, thresh, nlines, NULL);

	free_word_stats(ws);
}

double draw_string_bestfit_asis(vector_font_t *font, const uint8_t *string, rect_t box, double border, double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp)
{
	int nlines=0;
	double maxwidth, maxscale;
	xy_t boxdim, p, fitdim;
	rect_t fitrect;

	if (string == NULL)
		return 0.;

	box = sort_rect(box);
	border *= rect_min_side(box);
	box.p1 = sub_xy(box.p1, set_xy(border));		// remove the border
	box.p0 = add_xy(box.p0, set_xy(border));
	boxdim = get_rect_dim(box);				// box size

	maxwidth = find_string_maxwidth_and_nlines(font, string, mode, &nlines, 1) + 4.;	// get maxwidth (of the longest line) and number of lines

	maxscale = MINN(boxdim.x / maxwidth, boxdim.y / (nlines*LINEVSPACING));			// find the scale needed for the text to fit the box with this many lines
	scale = MINN(scale, maxscale);

	//fitdim = mul_xy( set_xy(scale) , xy(maxwidth, nlines*LINEVSPACING) );
	//fitrect = make_rect_off( box.p0, fitdim, XY0 );
	//draw_rect_full(fitrect, line_thick, colour, intensity);

	p = box.p0;
	p.x += 2.*scale;
	p.y += 8.*scale;
	draw_string(font, string, p, scale, colour, intensity, line_thick, mode, tp);

	return scale;
}

void draw_string_fixed_thresh(vector_font_t *font, const uint8_t *string, rect_t box, const double thresh, double scale, col_t colour, double intensity, double line_thick, const int mode, text_param_t *tp)
{
	word_stats_t ws;
	double maxscale, maxwidth=0.;
	int nlines;
	xy_t boxdim;

	if (string == NULL)
		return;

	ws = make_word_stats(font, string, mode);

	boxdim = get_rect_dim(box);

	nlines = find_line_count_for_thresh(font, string, ws, mode, thresh, &maxwidth);		// then the number of lines must be recounted

	maxscale = MINN(boxdim.x / maxwidth, boxdim.y / (nlines*LINEVSPACING));			// find the scale needed for the text to fit the box with this many lines
	scale = MINN(scale, maxscale);

	draw_string_maxwidth(font, string, ws, box, scale, colour, intensity, line_thick, mode, thresh, nlines, tp);

	free_word_stats(ws);
}
