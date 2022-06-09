void font_alloc_one(vector_font_t *font)
{
	alloc_enough(&font->l, font->letter_count+=1, &font->alloc_count, sizeof(letter_t), 2.);
}

void font_create_letter(vector_font_t *font, uint32_t cp)
{
	font_alloc_one(font);
	font->l[font->letter_count-1].codepoint = cp;
	textedit_init(&font->l[font->letter_count-1].glyphdata_edit, 1);

	add_codepoint_letter_lut_reference(font);
}

void font_remove_letter(vector_font_t *font, uint32_t cp)
{
	int i, letter_index;

	letter_index = get_letter_index(font, cp);
	if (letter_index == -1)
		return ;

	// free elements
	free_vobj(font->l[letter_index].obj);
	font->l[letter_index].obj = NULL;
	textedit_free(&font->l[letter_index].glyphdata_edit);

	font->letter_count--;

	// move every next letter one position down
	for (i=letter_index; i < font->letter_count; i++)
	{
		font->l[i] = font->l[i+1];
		font->codepoint_letter_lut[font->l[i].codepoint] = i;	// update new index in the codepoint LUT
	}

	font->codepoint_letter_lut[cp] = -1;	// remove table references
}

void add_codepoint_letter_lut_reference(vector_font_t *font)
{
	font->codepoint_letter_lut[font->l[font->letter_count-1].codepoint] = font->letter_count-1;	// add a LUT reference
}

void font_parse_p_line(char *line, xy_t *pv, int *pid, letter_t *l)
{
	int n=0, ip;
	const char *p;

	p = skip_whitespace(line);
	if (p[0]=='p')
	{
		sscanf(p, "p%d%n", &ip, &n);	// take the p number

		p = &p[n];
		p = string_parse_fractional_12(p, &pv[l->point_count].x);
		p = string_parse_fractional_12(p, &pv[l->point_count].y);
		pid[ip + l->pid_offset] = l->point_count;
		l->point_count++;

		l->max_pid = MAXN(l->max_pid, ip + l->pid_offset);
	}
}

void font_parse_curveseg_line(char *line, xy_t *pv, int *pid, letter_t *l)
{
	int n=0, ip, d1_is_ratio=0, abs_angle=0;
	const char *p;
	double th0=0.5*pi, th1=0., d0, d1=0.;
	xy_t p0=XY0, p1, p2;

	p = skip_string(line, " curveseg %n");
	sscanf(p, "p%d %n", &ip, &n);			// take the p number
	p = &p[n];

	p = string_parse_fractional_12(p, &th1);	// angle (in dozenal twelfths of a turn (0;0;0 to 11;11;11)) of the segment from the previous segment
	if (p[0]=='a')					// if a 'a' follows the angle is considered absolute, only p1 is used
	{
		abs_angle = 1;
		p++;
	}

	th1 += 3.;	// fixes a 90 degree bend
	th1 *= -2.*pi / 12.;				// makes positive angles go clockwise
	p = string_parse_fractional_12(p, &d1);		// distance ratio of the segment compared to the previous one
	if (p[0]=='x')					// if a 'x' follows it's considered a ratio
		d1_is_ratio = 1;

	if (d1==0. || l->point_count < 1)
		return ;

	p1 = pv[l->point_count - 1];
	if (l->point_count - 2 >= 0)
		p0 = pv[l->point_count - 2];
	if (abs_angle==0)
		th0 = atan2(p1.y-p0.y, p1.x-p0.x);		// angle of the previous curve segment

	d0 = hypot_xy(p0, p1);
	if (abs_angle==0 && d1_is_ratio==0)
		d0 = 1.;

	if (d1_is_ratio)
		d1 *= d0;

	p2 = rotate_xy2(xy(0., d1), th0+th1);
	p2 = add_xy(p1, p2);

	pv[l->point_count] = p2;
	pid[ip + l->pid_offset] = l->point_count;
	l->point_count++;

	l->max_pid = MAXN(l->max_pid, ip + l->pid_offset);
}

void font_parse_rect_line(char *line, xy_t *pv, int *pid, letter_t *l)
{
	int i, ip, n=0, pstart=0;
	double num_seg=0., radius=0., start_angle=0.;
	xy_t pn;
	rect_t r;
	const char *p=line;

	sscanf(p, " rect p%d %n", &pstart, &n);
	p = &p[n];

	p = string_parse_fractional_12(p, &r.p0.x);
	p = string_parse_fractional_12(p, &r.p0.y);
	p = string_parse_fractional_12(p, &r.p1.x);
	p = string_parse_fractional_12(p, &r.p1.y);

	for (i=0; i<4; i++)
	{
		ip = pstart + i;
		pn.x = (i&1) ? r.p1.x : r.p0.x;
		pn.y = (i&2) ? r.p1.y : r.p0.y;

		pv[l->point_count] = pn;
		pid[ip + l->pid_offset] = l->point_count;
		l->point_count++;

		l->max_pid = MAXN(l->max_pid, ip + l->pid_offset);
	}
}

void font_parse_circle_line(char *line, xy_t *pv, int *pid, letter_t *l)
{
	int ip, n=0, pstart=0, pend=0;
	double num_seg=0., radius=0., start_angle=0.;
	xy_t centre=XY0, pn;
	const char *p=line;

	sscanf(p, " circle p%d p%d %lf %n", &pstart, &pend, &num_seg, &n);
	p = &p[n];

	p = string_parse_fractional_12(p, &radius);
	p = string_parse_fractional_12(p, &centre.x);
	p = string_parse_fractional_12(p, &centre.y);
	p = string_parse_fractional_12(p, &start_angle);
	start_angle = (start_angle + 0.) * -2.*pi / 12.;	// makes positive angles go clockwise

	if (radius==0.)
		return ;

	radius /= cos(pi / num_seg);		// this makes the ideal circle fit entirely inside the polygon

	for (ip=pstart; ip<=pend; ip++)
	{
		pn = rotate_xy2(xy(0., radius), start_angle - (double) (ip-pstart) * 2.*pi / num_seg);
		pn = add_xy(pn, centre);

		pv[l->point_count] = pn;
		pid[ip + l->pid_offset] = l->point_count;
		l->point_count++;

		l->max_pid = MAXN(l->max_pid, ip + l->pid_offset);
	}
}

void font_parse_mirror_line(char *line, xy_t *pv, int *pid, letter_t *l)
{
	int ip, op, n=0, p_first=0, p_last=0, p_start=0;
	xy_t pn;
	double mirror_pos=0.;
	char hv;
	const char *p=line;

	sscanf(p, " mirror %c %n%*s p%d p%d p%d", &hv, &n, &p_first, &p_last, &p_start);
	p = &p[n];

	p = string_parse_fractional_12(p, &mirror_pos);

	for (op=p_first; op<=p_last; op++)
	{
		ip = p_start + op-p_first;
		pn = pv[pid[op + l->pid_offset]];

		if (hv=='h')
			pn.y = 2*mirror_pos - pn.y;
		else if (hv=='v')
			pn.x = 2*mirror_pos - pn.x;

		pv[l->point_count] = pn;
		pid[ip + l->pid_offset] = l->point_count;
		l->point_count++;

		l->max_pid = MAXN(l->max_pid, ip + l->pid_offset);
	}
}

void font_add_line(int pA, int pB, int *lineA, int *lineB, letter_t *l)
{
	if (pA!=-1)
	{
		if (l->line_count >= 400)
			fprintf_rl(stderr, "l->line_count has become too large in font_add_line()\n");
		lineA[l->line_count] = pA + l->pid_offset;
		lineB[l->line_count] = pB + l->pid_offset;
		l->line_count++;
	}
}

void font_parse_lines_line(char *line, xy_t *pv, int *pid, int *lineA, int *lineB, letter_t *l)
{
	int i, n, wl, to=0, pA=-1, pB, direction;
	const char *p, *pend;

	pend = &line[strlen(line)];		// pointer to line's NULL terminator
	p = skip_string(line, " lines %n");

	while (p < pend)
	{
		wl = 0;		// word length
		n = 0;		// position of the next word
		sscanf(p, "%*s%n %n", &wl, &n);

		if (n==0)		// if the second n is unmatched the behaviour is undefined
			n = wl;

		if (wl==0)
			break;

		if (compare_varlen_word_to_fixlen_word(p, wl, "to"))
			to = 1;
		else
			if (p[0]=='p')
			{
				if (sscanf(p, "p%d", &pB))
				{
					if (pB + l->pid_offset < 0)	// make sure the actual point referenced isn't < 0 when pB is negative
						pB = l->pid_offset;

					if (to)
					{
						to = 0;

						direction = sign(pB - pA);
						if (direction==0)
						{
							fprintf_rl(stderr, "Forbidden \"p%d to p%d\" in line \"%s\"\n", pA, pB, line);
							return ;
						}

						for (i=pA; ; i+=direction)
						{
							if (i==pB)
								break ;

							font_add_line(i, i+direction, lineA, lineB, l);
						}
					}
					else
						font_add_line(pA, pB, lineA, lineB, l);

					pA = pB;
				}
			}

		p = &p[n];
	}
}

void font_parse_bounds_line(char *line, letter_t *l)
{
	const char *p;

	p = skip_string(line, " bounds %n");

	p = string_parse_fractional_12(p, &l->bl);
	p = string_parse_fractional_12(p, &l->br);
}

void font_parse_vbounds_line(char *line, letter_t *l)
{
	const char *p;

	p = skip_string(line, " vbounds %n");

	p = string_parse_fractional_12(p, &l->bb);
	p = string_parse_fractional_12(p, &l->bt);
}

void font_parse_transform_line(char *line, char *a, letter_t *l, glyphdata_t *gd, int group_start, int last_start)
{
	int i, n, todo=0, to_offset=1, start;
	const char *p;
	char b[32];
	double th;
	xy_t o;
	xyz_t v;
	matrix_t m = matrix_xyz(xyz(1., 0., 0.),	// see https://en.wikipedia.org/wiki/File:2D_affine_transformation_matrix.svg
				xyz(0., 1., 0.),
				xyz(0., 0., 1.));

	p = skip_string(line, " %*s %n");

	start = group_start;				// default does the points added from the start of the glyph, not the parents
	if (sscanf(p, "%s %n", b, &n))			// detect if "all" or "loc" is added after the command
	{
		if (strcmp(b, "all")==0)		// all does all the points, even those of the parents (so, probably no point in using that)
		{
			start = 0;
			p = &p[n];
		}

		if (strcmp(b, "last")==0)		// last only does the points added since right before the last copy
		{
			start = last_start;
			p = &p[n];
		}

		if (strcmp(b, "loc")==0)		// all does all the points added locally since after the last copy
		{
			start = l->pid_offset;
			p = &p[n];
		}
	}

	if (strcmp(a, "scale")==0)
	{
		todo = 1;
		p = string_parse_fractional_12(p, &m.x.x);
		p = skip_whitespace(p);
		if (strlen(p) > 0)
			p = string_parse_fractional_12(p, &m.y.y);
		else
			m.y.y = m.x.x;
	}

	if (strcmp(a, "move")==0)
	{
		todo = 1;
		to_offset = 0;
		p = string_parse_fractional_12(p, &m.x.z);
		p = string_parse_fractional_12(p, &m.y.z);
	}

	if (strcmp(a, "rotate")==0)
	{
		todo = 1;
		p = string_parse_fractional_12(p, &th);			// angle, in dozenal twelfths of a turn (0;0;0 to 11;11;11)
		th *= 2.*pi / 12.;
		m.x.x = cos(th);
		m.x.y = sin(th);
		m.y.x = -m.x.y;
		m.y.y = m.x.x;
	}

	if (strcmp(a, "shearX")==0)
	{
		todo = 1;
		p = string_parse_fractional_12(p, &th);			// angle, in dozenal twelfths of a turn (0;0;0 to 11;11;11)
		th *= 2.*pi / 12.;
		m.x.y = tan(th);
	}

	if (strcmp(a, "shearY")==0)
	{
		todo = 1;
		p = string_parse_fractional_12(p, &th);			// angle, in dozenal twelfths of a turn (0;0;0 to 11;11;11)
		th *= 2.*pi / 12.;
		m.y.x = tan(th);
	}

	if (todo)
	{
		// get point to transform around
		if (to_offset)
		{
			p = string_parse_fractional_12(p, &o.x);		// origin X
			p = string_parse_fractional_12(p, &o.y);		// origin Y
			m.x.z = o.x - o.x * m.x.x - o.y * m.x.y;
			m.y.z = o.y - o.x * m.y.x - o.y * m.y.y;
		}

		// do transform to each point
		for (i=start; i<l->point_count; i++)
		{
			v = xyz(gd->pv[i].x, gd->pv[i].y, 1.);
			gd->pv[i] = xyz_to_xy( matrix_mul(v, m) );
		}
	}
}

void process_glyphdata_core(vector_font_t *font, letter_t *l, char *p, glyphdata_t *gd, int req_subgl)
{
	int n=0, group_start, last_start, subgl=0;
	char c, line[128], a[128];
	uint32_t copy_cp, copy_subgl;
	letter_t *lcopy;

	if (p==NULL)
		return ;

	group_start = l->pid_offset;
	last_start = l->max_pid;

	while (sscanf(p, "%[^\n]\n%n", line, &n) && strlen(p)>0)	// go through each line in glyphdata_edit.string
	{
		a[0] = '\0';
		sscanf(line, " %s", a);

		if (strcmp(a, "subglyph")==0)				// entering subglyph section
			if (sscanf(line, " subglyph %c", &c)==1)
				subgl = c;

		if (strcmp(a, "subend")==0)
			subgl = 0;

		if (subgl==req_subgl)
		{
			font_parse_p_line(line, gd->pv, gd->pid, l);		// processes pX lines

			if (strcmp(a, "curveseg")==0)
				font_parse_curveseg_line(line, gd->pv, gd->pid, l);

			if (strcmp(a, "circle")==0)
				font_parse_circle_line(line, gd->pv, gd->pid, l);

			if (strcmp(a, "rect")==0)
				font_parse_rect_line(line, gd->pv, gd->pid, l);

			if (strcmp(a, "mirror")==0)
				font_parse_mirror_line(line, gd->pv, gd->pid, l);

			if (strcmp(a, "lines")==0)
				font_parse_lines_line(line, gd->pv, gd->pid, gd->lineA, gd->lineB, l);

			if (strcmp(a, "bounds")==0)
			{
				font_parse_bounds_line(line, l);
				gd->set_bounds = 1;
			}

			if (strcmp(a, "vbounds")==0)
			{
				font_parse_vbounds_line(line, l);
				gd->set_vbounds = 1;
			}

			if (strcmp(a, "clear_bounds")==0)
			{
				gd->set_bounds = 0;
				l->bl = 0.;
				l->br = 0.;
			}

			if (strcmp(a, "copy")==0)
			{
				last_start = l->max_pid;

				copy_cp = 0;
				copy_subgl = 0;
				if (sscanf(line, " copy '%c'", &c)==1)
					copy_cp = c;
				else
					sscanf(line, " copy %X", &copy_cp);

				if (sscanf(line, " copy %*s %c", &c)==1)
					copy_subgl = c;

				if (copy_cp==l->codepoint && copy_subgl==0)
					fprintf_rl(stderr, "Error in process_glyphdata_core(): glyph %04X tries to copy itself.\n", l->codepoint);
				else
				{
					lcopy = get_letter(font, copy_cp);
					l->pid_offset = l->max_pid;
					if (lcopy)
						process_glyphdata_core(font, l, lcopy->glyphdata_edit.string, gd, copy_subgl);
					l->pid_offset = l->max_pid;
				}
			}

			font_parse_transform_line(line, a, l, gd, group_start, last_start);
		}

		p = &p[n];
		if (n==0)
			break ;
		n = 0;
	}

	//if (l->codepoint==0xFE94)
	//	fprintf_rl(stdout, "group_start = %d\n", group_start);
		//fprintf_rl(stdout, "%d, %d, %d, %d\n", l->point_count, l->line_count, l->pid_offset, l->max_pid);
}

void process_glyphdata(vector_font_t *font, letter_t *l, glyphdata_t *gd)
{
	if (l==NULL)
		return ;

	if (l->glyphdata_edit.string == NULL)
		return ;

	l->pid_offset = 0;
	l->max_pid = 0;
	l->point_count = 0;
	l->line_count = 0;
	gd->set_bounds = 0;
	gd->set_vbounds = 0;
	memset(gd->pid, 0xFF, sizeof(gd->pid));
	memset(gd->pv, 0, sizeof(gd->pv));
	memset(gd->lineA, 0, sizeof(gd->lineA));
	memset(gd->lineB, 0, sizeof(gd->lineB));

	process_glyphdata_core(font, l, l->glyphdata_edit.string, gd, 0);
}

void make_glyph_vobj(letter_t *l, glyphdata_t *gd)
{
	int i, pidA, pidB;
	xy_t vA, vB;

	l->bb = 10.;
	l->bt = 0.;

	// make to vector object from the parsed data
	free_vobj(l->obj);
	l->obj = alloc_vobj(l->line_count);
	for (i=0; i < l->line_count; i++)
	{
		pidA = gd->pid[gd->lineA[i]];
		pidB = gd->pid[gd->lineB[i]];
		if (pidA > -1 && pidB > -1)
		{
			vA = gd->pv[pidA];
			vB = gd->pv[pidB];
			l->obj->seg[i] = seg_make_xy(vA, vB, 1.);

			if (gd->set_bounds==0)
			{
				l->bl = MINN(l->bl, vA.x);
				l->bl = MINN(l->bl, vB.x);
				l->br = MAXN(l->br, vA.x);
				l->br = MAXN(l->br, vB.x);
			}

			if (gd->set_vbounds==0)
			{
				l->bb = MINN(l->bb, vA.y);
				l->bb = MINN(l->bb, vB.y);
				l->bt = MAXN(l->bt, vA.y);
				l->bt = MAXN(l->bt, vB.y);
			}
		}
	}
	l->width = l->br - l->bl;
}

void font_block_process_line(const char *line, vector_font_t *font)
{
	char a[128], c;
	const char *p;
	uint32_t cp;
	int current_count;

	a[0] = '\0';
	sscanf(line, "%s", a);

	if (strcmp(a, "glyph")==0)
	{
		cp = 0;
		if (sscanf(line, "glyph '%c'", &c)==1)
			cp = c;
		else
			sscanf(line, "glyph %X", &cp);

		// in previous glyphdata_edit.string: remove trailing linebreaks, realloc previous glyphdata_edit.string (shrink down)
		if (font->letter_count > 0)
			if (font->l[font->letter_count-1].glyphdata_edit.string)
			{
				font->l[font->letter_count-1].glyphdata_edit.alloc_size = strlen(font->l[font->letter_count-1].glyphdata_edit.string) + 1;

				while (font->l[font->letter_count-1].glyphdata_edit.string[ font->l[font->letter_count-1].glyphdata_edit.alloc_size - 2 ] == '\n')
				{
					font->l[font->letter_count-1].glyphdata_edit.string[ font->l[font->letter_count-1].glyphdata_edit.alloc_size - 2 ] = '\0';
					font->l[font->letter_count-1].glyphdata_edit.alloc_size--;
				}

				font->l[font->letter_count-1].glyphdata_edit.string = realloc(font->l[font->letter_count-1].glyphdata_edit.string, font->l[font->letter_count-1].glyphdata_edit.alloc_size);
			}

		font_create_letter(font, cp);
	}
	else
	{
		p = line;
		if (line[0] != '\n')
			p = skip_whitespace(line);

		if (font->l[font->letter_count - 1].glyphdata_edit.string==NULL)
			current_count = 0;
		else
			current_count = strlen(font->l[font->letter_count-1].glyphdata_edit.string) + 1;
		alloc_enough(&font->l[font->letter_count-1].glyphdata_edit.string, current_count += strlen(p)+1, &font->l[font->letter_count-1].glyphdata_edit.alloc_size, sizeof(1), 2.0);

		strcat(font->l[font->letter_count-1].glyphdata_edit.string, p);			// puts the line into the letter's glyphdata_edit.string
		strcat(font->l[font->letter_count-1].glyphdata_edit.string, "\n");
	}
}

void make_fallback_font(vector_font_t *font)
{
	#include "fallback_font.h"		// contains const char *fallback_font[]

	for (int i=0; i < sizeof(fallback_font)/sizeof(char *); i++)
		font_block_process_line(fallback_font[i], font);
}

void make_font_block(char *path, vector_font_t *font)
{
	int i, linecount;
	char **line;

	line = arrayise_text(load_raw_file_dos_conv(path, NULL), &linecount);
	if (line == NULL)
		return ;

	for (i=0; i < linecount; i++)
		font_block_process_line(line[i], font);

	free_2d(line, 1);
}

void make_font_block_from_struct(fileball_t *s, char *path, vector_font_t *font)
{
	int i, linecount;
	char **line;

	fileball_subfile_t *subfile = fileball_find_subfile(s, path);
	if (subfile == NULL)
	{
		fprintf_rl(stderr, "Subfile \"%s\" not found in make_font_block_from_struct()\n", path);
		return ;
	}

	line = arrayise_text(make_string_copy_len(subfile->data, subfile->len), &linecount);
	if (line == NULL)
		return ;

	for (i=0; i < linecount; i++)
		font_block_process_line(line[i], font);

	free_2d(line, 1);
}

void make_font_aliases_line(char *line, vector_font_t *font)
{
	int ret;
	uint32_t cp, tgt;
	char a[128], c, *p;

	ret = sscanf(line, "%X = %s", &cp, a);

	if (ret==2)
	{
		font_alloc_one(font);
		font->l[font->letter_count-1].codepoint = cp;
		if (a[0]=='\'')
		{
			if (sscanf(a, "'%c'", &c)==1)
				font->l[font->letter_count-1].alias = c;
		}
		else
			sscanf(a, "%X", &font->l[font->letter_count-1].alias);

		add_codepoint_letter_lut_reference(font);
	}
}

void make_font_aliases(char *path, vector_font_t *font)
{
	int i, linecount;
	char **line;

	line = arrayise_text(load_raw_file_dos_conv(path, NULL), &linecount);
	if (line == NULL)
		return ;

	for (i=0; i < linecount; i++)
		make_font_aliases_line(line[i], font);

	free_2d(line, 1);
}

void make_font_aliases_from_struct(fileball_t *s, char *path, vector_font_t *font)
{
	int i, linecount;
	char **line;

	fileball_subfile_t *subfile = fileball_find_subfile(s, path);
	if (subfile == NULL)
	{
		fprintf_rl(stderr, "Subfile \"%s\" not found in make_font_aliases_from_struct()\n", path);
		return ;
	}

	line = arrayise_text(make_string_copy_len(subfile->data, subfile->len), &linecount);
	if (line == NULL)
		return ;

	for (i=0; i < linecount; i++)
		make_font_aliases_line(line[i], font);

	free_2d(line, 1);
}

void process_one_glyph(vector_font_t *font, int i)
{
	glyphdata_t gd;

	if (i < 0 || i >= font->letter_count)
		return ;

	if (font->l[i].alias || font->l[i].obj)
		return ;

	if (font->l[i].glyphdata_edit.string)
	{
		process_glyphdata(font, &font->l[i], &gd);
		make_glyph_vobj(&font->l[i], &gd);
	}
	else
		make_cjkdec_vobj(font, &font->l[i]);
}

vector_font_t *make_font(char *index_path)
{
	vector_font_t *font;
	char dirpath[PATH_MAX*4], **line, a[128], path[PATH_MAX*4];
	int i, linecount, range0, range1;

	font = calloc(1, sizeof(vector_font_t));

	font->l = calloc (font->alloc_count = 256, sizeof(letter_t));
	font->codepoint_letter_lut = calloc (0x110000, sizeof(int32_t));
	memset(font->codepoint_letter_lut, 0xFF, 0x110000 * sizeof(int32_t));

	remove_name_from_path(dirpath, index_path);
	dirpath[strlen(dirpath)+1] = '\0';
	dirpath[strlen(dirpath)] = DIR_CHAR;

	line = arrayise_text(load_raw_file_dos_conv(index_path, NULL), &linecount);
	if (line == NULL)
	{
		make_fallback_font(font);
		return font;
	}

	for (i=0; i < linecount; i++)			// read the index file
	{
		a[0] = '\0';
		sscanf(line[i], "%s", a);

		if (strcmp(a, "range")==0)
		{
			strcpy(path, dirpath);
			sscanf(line[i], "range %X %X \"%[^\"]\"", &range0, &range1, &path[strlen(path)]);
			make_font_block(path, font);
		}

		if (strcmp(a, "substitutions")==0)
		{
			strcpy(path, dirpath);
			sscanf(line[i], "substitutions \"%[^\"]\"", &path[strlen(path)]);
			make_font_aliases(path, font);
		}

		if (strcmp(a, "cjkdecomp")==0)
		{
			strcpy(path, dirpath);
			sscanf(line[i], "cjkdecomp \"%[^\"]\"", &path[strlen(path)]);
			cjkdec_load_data(path, font);
		}
	}

	free_2d(line, 1);

	return font;
}

vector_font_t *make_font_from_fileball(fileball_t *s, const char *index_filename)
{
	vector_font_t *font;
	char dirpath[PATH_MAX*4], **line, a[128], path[PATH_MAX*4];
	int i, linecount, range0, range1;

	font = calloc(1, sizeof(vector_font_t));

	font->l = calloc (font->alloc_count = 256, sizeof(letter_t));
	font->codepoint_letter_lut = calloc (0x110000, sizeof(int32_t));
	memset(font->codepoint_letter_lut, 0xFF, 0x110000 * sizeof(int32_t));

	fileball_subfile_t *subfile = fileball_find_subfile(s, index_filename);
	if (subfile==NULL)
	{
		make_fallback_font(font);
		return font;
	}

	line = arrayise_text(make_string_copy_len(subfile->data, subfile->len), &linecount);
	if (line == NULL)
	{
		make_fallback_font(font);
		return font;
	}

	for (i=0; i < linecount; i++)			// read the index file
	{
		a[0] = '\0';
		sscanf(line[i], "%s", a);

		if (strcmp(a, "range")==0)
		{
			sscanf(line[i], "range %X %X \"%[^\"]\"", &range0, &range1, path);
			make_font_block_from_struct(s, path, font);
		}

		if (strcmp(a, "substitutions")==0)
		{
			sscanf(line[i], "substitutions \"%[^\"]\"", path);
			make_font_aliases_from_struct(s, path, font);
		}

		/*if (strcmp(a, "cjkdecomp")==0)
		{
			sscanf(line[i], "cjkdecomp \"%[^\"]\"", path);
			cjkdec_load_data_from_struct(s, path, font);
		}*/
	}

	free_2d(line, 1);

	return font;
}

vector_font_t *make_font_from_zball(uint8_t *data, size_t data_len)
{
	buffer_t zball={0};

	zball.buf = data;
	zball.len = data_len;

	fileball_t s = fileball_extract_z_mem_to_struct(&zball);
	vector_font_t *font = make_font_from_fileball(&s, "type_index.txt");

	free_fileball_struct(&s);

	return font;
}

void clear_font_vobjs(vector_font_t *font)
{
	int i;

	if (font==NULL)
		return ;

	for (i=0; i<font->letter_count; i++)
	{
		free_vobj (font->l[i].obj);
		font->l[i].obj = NULL;
	}
}

void free_font(vector_font_t *font)
{
	int i;

	if (font==NULL)
		return ;

	for (i=0; i<font->letter_count; i++)
	{
		free_vobj (font->l[i].obj);
		textedit_free(&font->l[i].glyphdata_edit);
	}

	free(font->codepoint_letter_lut);
	free(font->l);
	free(font->cjkdec_pos);
	free(font->cjkdec_data);
	free(font);
}

vector_font_t *remake_font(char *index_path, vector_font_t *oldfont)
{
	static char *old_path=NULL;

	if (index_path)		// copy the path for possible later use
	{
		free(old_path);
		old_path = make_string_copy(index_path);
	}

	free_font(oldfont);

	return make_font(old_path);
}

void save_font_block(char *path, vector_font_t *font, int range0, int range1, char *cp_saved)
{
	FILE *file;
	int i;
	uint32_t cp;

	file = fopen_utf8(path, "wb");
	if (file == NULL)
	{
		fprintf_rl(stderr, "Couldn't save font block to file '%s'.\n", path);
		return ;
	}

	for (i=0; i < font->letter_count; i++)
	{
		cp = font->l[i].codepoint;

		if (cp_saved[i]==0 && cp >= range0 && cp <= range1 && font->l[i].glyphdata_edit.string)
		{	
			cp_saved[i] = 1;

			if (font->l[i].codepoint < 0x80)
				fprintf(file, "glyph '%c'\n", cp);
			else
				fprintf(file, "glyph %04X\n", cp);

			fprint_indent(file, "\t", 1, font->l[i].glyphdata_edit.string);
			fprintf(file, "\n\n");
		}
	}

	fclose (file);
}

void save_font(vector_font_t *font, char *index_path)
{
	char *cp_saved, dirpath[PATH_MAX*4], **line, a[128], path[PATH_MAX*4];
	int i, linecount, range0, range1;

	cp_saved = calloc(font->letter_count, sizeof(char));

	remove_name_from_path(dirpath, index_path);
	dirpath[strlen(dirpath)+1] = '\0';
	dirpath[strlen(dirpath)] = DIR_CHAR;

	line = arrayise_text(load_raw_file_dos_conv(index_path, NULL), &linecount);
	if (line == NULL)
	{
		make_fallback_font(font);
		free(cp_saved);
		return ;
	}

	for (i=0; i < linecount; i++)		// read the index file
	{
		a[0] = '\0';
		sscanf(line[i], "%s", a);

		if (strcmp(a, "range")==0)
		{
			strcpy(path, dirpath);
			sscanf(line[i], "range %X %X \"%[^\"]\"", &range0, &range1, &path[strlen(path)]);
			save_font_block(path, font, range0, range1, cp_saved);
		}
	}

	free(cp_saved);
	free_2d(line, 1);

	return ;
}
