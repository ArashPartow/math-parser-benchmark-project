double glyph_width(vector_font_t *font, double pos, uint32_t c, double scale, const int mode)	// includes inter-letter spacing
{
	double tabx = 0.;
	letter_t *l;
	int lowerscale = 0;

	if (font==NULL)
		return 0.;

	if (c > 0x10FFFF)
		return 0.;

	if (c=='\t')
	{
		while (tabx < pos + LETTERSPACING*scale)
			tabx += 8.*(4.+LETTERSPACING) * scale;

		return tabx - pos;
	}

	process_one_glyph(font, get_letter_index(font, c));

	l = get_dominant_letter(font, c, &lowerscale);
	if (l)
	if (l->obj)
		if ((mode&12)==PROPORTIONAL || (((mode&12)==MONODIGITS) && (c<'0' || c>'9')))
			return (l->width * (lowerscale ? LOWERCASESCALE : 1.) + LETTERSPACING) * scale;
		else
			return (4. + LETTERSPACING) * scale;

	if (is_cjkdec_glyph(font, c))
		return (6. + LETTERSPACING) * scale;

	return 0.;
}

double letter_width(vector_font_t *font, double pos, uint32_t c, double scale, const int mode)	// includes inter-letter spacing
{
	unicode_data_t ucd;

	if (c > 0x10FFFF)
		return 0.;

	ucd = get_unicode_data(c);

	if (ucd.bidicat==bidicat_NSM)			// non-spacing (combining) mark
		return 0.;

	if (ucd.decomp_type==decomp_wide)
		return (6. + LETTERSPACING) * scale;

	return glyph_width(font, pos, c, scale, mode);
}

double calc_strwidth_len(vector_font_t *font, const uint8_t *string, double scale, const int mode, int32_t len)
{
	size_t i;
	int con_prev=0;
	uint32_t c, co, c_prev=0;
	double w = 0.;
	unicode_data_t ucd;

	if (len < 0)
		len = strlen(string);

	for (i=0; i<len; i++)
	{
		co = utf8_to_unicode32(&string[i], &i);
		if (co == 0xFFFFFFFF)
			break;

		// Arabic form substitution
		c = get_arabic_form(co, &string[i+1], len-(i+1), con_prev);	// substitute for Arabic form if needed
		ucd = get_unicode_data(c);
		if (ucd.bidicat!=bidicat_NSM)					// if character that is not a combining mark
			con_prev = unicode_arabic_can_connect(co, 1);		// if the current character connects with the next (in Arabic)

		// Ligature exceptions
		if (c >= cp_ins_start && c < cp_ins_end)
			if (c_prev >= cp_ins_start && c_prev < cp_ins_end)	// there's no LETTERSPACING between two cp_ins spaces
				w -= LETTERSPACING * scale;

		w += letter_width(font, w, c, scale, mode);

		c_prev = c;
	}

	w -= LETTERSPACING * scale;	// removes the end space FIXME wrong if last char is small letter
	w = MAXN(0., w);

	return w;
}

double calc_strwidth(vector_font_t *font, const uint8_t *string, double scale, const int mode)
{
	return calc_strwidth_len(font, string, scale, mode, -1);
}

word_stats_t make_word_stats(vector_font_t *font, const uint8_t *string, const int mode)
{
	size_t i, is, iw, len = strlen(string);
	int prev_was_space=1;
	uint32_t c, c_prev=0;
	word_stats_t ws;

	ws.full_length = calc_strwidth(font, string, 1., mode);

	// Count spaces (and therefore words)
	for (ws.word_count=1, i=0; i < len; i++)
		if (string[i]==' ' && string[i+1]!='\0')	// TODO do better than just count spaces
			ws.word_count++;

	ws.word_length = calloc(ws.word_count, sizeof(double));
	ws.word_start = calloc(ws.word_count, sizeof(int));
	ws.word_end = calloc(ws.word_count, sizeof(int));

	ws.aver_word_length = (ws.full_length - (double) (ws.word_count-1)*(letter_width(font, 0., ' ', 1., mode)+LETTERSPACING)) / (double) ws.word_count;

	// find individual word length and the final length sum of all the lines
	ws.max_word_length = 0.;
	for (iw=0, i=0; i<len; i++)
	{
		is = i;			// save i at start (it might get incremented right below)
		c = utf8_to_unicode32(&string[i], &i);

		if (c==' ')
		{
			ws.word_length[iw] -= LETTERSPACING;	// removes the end space
			ws.max_word_length = MAXN(ws.max_word_length, ws.word_length[iw]);
			iw++;
			prev_was_space = 1;
		}
		else
		{
			ws.word_length[iw] += letter_width(font, 0., c, 1., mode);

			// Ligature exceptions
			if (c >= cp_ins_start && c < cp_ins_end)
				if (c_prev >= cp_ins_start && c_prev < cp_ins_end)	// there's no LETTERSPACING between two cp_ins spaces
					ws.word_length[iw] -= LETTERSPACING;

			if (i == len-1)		// if we've reached the end
			{
				ws.word_length[iw] -= LETTERSPACING;	// removes the end space
				ws.max_word_length = MAXN(ws.max_word_length, ws.word_length[iw]);
			}

			ws.word_end[iw] = i;

			if (prev_was_space)
				ws.word_start[iw] = is;
			prev_was_space = 0;
		}

		c_prev = c;
	}

	return ws;
}

void free_word_stats(word_stats_t ws)
{
	free(ws.word_length);
	free(ws.word_start);
	free(ws.word_end);
}

// gives to correct word length to use for adding to the length of the line starting at iw_start
double get_word_length(vector_font_t *font, const uint8_t *string, word_stats_t ws, const int mode, int iw_start, int iw)
{
	const double space_width = letter_width(font, 0., ' ', 1., mode);
	double width;

	width = ws.word_length[iw];

	if (iw>iw_start)
		width += space_width + LETTERSPACING;

	return width;
}

double find_string_maxwidth_and_nlines(vector_font_t *font, const uint8_t *string, const int mode, int *nlines, int empty_lines_count)
{
	const char *sol=string, *eol;
	double width, maxwidth=0.;

	*nlines = 0;

	while (1)
	{
		eol = strchr(sol, '\n');
		if (eol==NULL)
			width = calc_strwidth_len(font, sol, 1., mode, -1);
		else
			width = calc_strwidth_len(font, sol, 1., mode, eol-sol);

		maxwidth = MAXN(maxwidth, width);

		if (sol[0] || empty_lines_count)	// if this "line" isn't just a \0
			(*nlines)++;

		if (eol==NULL)
			return maxwidth;

		sol = eol+1;
	}
}

double calc_strwidth_firstline(vector_font_t *font, const uint8_t *string, double scale, const int mode, int32_t len, int *sonl)
{
	const char *sol=string, *eol;
	double width, maxwidth=0.;
	int32_t len_n;

	if (len < 0)
		len = strlen(string);

	eol = strchr(sol, '\n');
	if (eol==NULL)
		len_n = len;
	else
		len_n = MINN(len, eol-sol);

	width = calc_strwidth_len(font, sol, scale, mode, len_n);

	if (sonl)
	{
		(*sonl) += len_n;		// set start of next line

		while (string[*sonl]=='\n')
			(*sonl)++;
	}

	return width;
}
