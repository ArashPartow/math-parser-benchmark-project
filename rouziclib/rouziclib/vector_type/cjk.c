const char *cjkdec_type_name[] = {"a", "a_m", "a_s", "a_t", "ba", "ba_o", "bd", "bd_m", "bd_t", "built", "c", "cbl_o", "ctl_t", "ctlbr_t", "d", "d_m", "d_o", "d_s", "d_t", "lock", "mb", "mc", "me", "ml", "mo", "mo0", "mo2", "mo4", "mo5", "mr", "msp", "mt", "mtl", "r_a", "r3a", "r3d", "r3d_m", "r3gw", "r3st", "r3stl", "r3str", "r3tr", "r4a", "r4d", "r4dia", "r4ref_t", "r4sq", "r5p", "r5x", "ra", "ra_m", "rd", "rd_m", "rd_s", "rd_t", "refh", "refr", "refv", "rot", "rrefd", "rrefl", "rrefl_m", "rrefr", "rrefr_m", "rrefr_o", "rrefr_t", "rrotd", "rrotr", "rrotu", "rs", "rsb", "rsbr", "rsq", "rst", "rstl", "s", "s_t", "sb", "sbl", "sbl_m", "sbl_o", "sbr", "sl", "sl_m", "sl_s", "sr", "st", "st_t", "stl", "stl_m", "stl_s", "str", "str_o", "w", "w_o", "w_t", "wa", "wb", "wbl", "wbr", "wd", "wl", "wl_t", "wr", "wt", "wt_t", "wtl", "wtr"};

void cjkdec_load_data(char *path, vector_font_t *font)
{
	FILE *file;
	int i, ret, dec_type, start;
	char line[128], arg[4][8];
	uint32_t cp;

	file = fopen_utf8(path, "rb");
	if (file == NULL)
		return ;

	font->cjkdec_pos = calloc(0x110000, sizeof(int32_t));
	memset(font->cjkdec_pos, 0xFF, 0x110000*sizeof(int32_t));
	font->cjkdec_alloc_count = 48;
	font->cjkdec_data = calloc(font->cjkdec_alloc_count, sizeof(int32_t));

	while (fgets(line, sizeof(line), file))
	{
		ret = sscanf(line, "%s %d %s %s %s", arg[0], &dec_type, arg[1], arg[2], arg[3]);

		if (ret >= 2)
		{
			start = font->cjkdec_data_count;
			alloc_enough(&font->cjkdec_data, font->cjkdec_data_count += ret, &font->cjkdec_alloc_count, sizeof(uint32_t), 2.);

			cp = utf8_to_unicode32(arg[0], NULL);

			font->cjkdec_data[start] = cp;
			font->cjkdec_data[start+1] = ((ret-2) << 16) | dec_type;

			for (i=2; i < ret; i++)
				font->cjkdec_data[start+i] = utf8_to_unicode32(arg[i-1], NULL);

			font->cjkdec_pos[cp] = start;	// position of the data for this codepoint

			if (font->codepoint_letter_lut[cp]==-1)		// if codepoint isn't already taken
			{
				// add to font->letter
				font_alloc_one(font);
				font->l[font->letter_count-1].codepoint = cp;
				add_codepoint_letter_lut_reference(font);
			}
		}
	}

	fclose(file);
}

int is_cjkdec_glyph(vector_font_t *font, uint32_t c)
{
	if (font)
		if (font->cjkdec_pos)
			if (c < 0x110000)
				if (font->cjkdec_pos[c] >= 0)
					return 1;

	return 0;
}

int draw_cjkdec_glyph(vector_font_t *font, uint32_t c, xy_t p, double scale, col_t colour, double line_thick, const int mode)
{
	rect_t area;

	if (is_cjkdec_glyph(font, c)==0)
		return 0;

	area = make_rect_off(p, set_xy(6.*scale), xy(0., 1.));
	draw_rect_full(area, line_thick, make_grey(0.01), cur_blend, 1.);

	return 1;
}

vobj_t *vobj_fitted_cat(vobj_t **o, int count, rect_t *fit_rect, rect_t *obj_rect)
{
	int i, io, seg_base;
	vobj_t *ro;
	xy_t tmul, tadd;

	ro = calloc (1, sizeof(vobj_t));
	for (io=0; io<count; io++)
		ro->count += o[io]->count;
	ro->scale = 1.;
	ro->c = XY0;

	ro->seg = calloc (ro->count, sizeof(seg_t));

	seg_base = 0;
	for (io=0; io<count; io++)
	{
		area_to_area_transform(fit_rect[io], obj_rect[io], &tmul, &tadd, 0);

		for (i=0; i<o[io]->count; i++)
		{
			ro->seg[i+seg_base] = o[io]->seg[i];
			ro->seg[i+seg_base].p1 = xy_to_xyz(mad_xy(xyz_to_xy(o[io]->seg[i].p1), tmul, tadd));
			ro->seg[i+seg_base].p2 = xy_to_xyz(mad_xy(xyz_to_xy(o[io]->seg[i].p2), tmul, tadd));
		}

		seg_base += o[io]->count;
	}

	return ro;
}

vobj_t *make_cjkdec_vobj_switch(const int dec_type, const int arg_count, vobj_t **ao, rect_t *obj_rect)
{
	int i;
	double sum, pos, tr_scale;
	xy_t obj_dim[3];
	rect_t fit_rect[3], obj_rect_new[3];
	vobj_t *obj=NULL, *vo, *ao_new[3];

	for (i=0; i<arg_count; i++)
		obj_dim[i] = get_rect_dim(obj_rect[i]);

	switch (dec_type)
	{
		case cjkdec_a:
		case cjkdec_a_m:
		case cjkdec_a_s:
		case cjkdec_a_t:
			for (i=0, sum=0.; i<arg_count; i++)
				sum += obj_dim[i].x;

			tr_scale = MINN(6. / sum, 1.);		// scale of the transformation

			pos = -sum * 0.5 * tr_scale;
			for (i=0; i<arg_count; i++)
			{
				fit_rect[i] = obj_rect[i];
				fit_rect[i].p0.x = pos;
				pos += obj_dim[i].x * tr_scale;
				fit_rect[i].p1.x = pos;
			}

			obj = vobj_fitted_cat(ao, arg_count, fit_rect, obj_rect);
			break;

		case cjkdec_d:
		case cjkdec_d_m:
		case cjkdec_d_o:
		case cjkdec_d_s:
		case cjkdec_d_t:
			for (i=0, sum=0.; i<arg_count; i++)
				sum += obj_dim[i].y;

			tr_scale = MINN(6. / sum, 1.);		// scale of the transformation

			pos = sum * tr_scale;
			for (i=0; i<arg_count; i++)
			{
				fit_rect[i] = obj_rect[i];
				fit_rect[i].p1.y = pos;
				pos -= obj_dim[i].y * tr_scale;
				fit_rect[i].p0.y = pos;
			}

			obj = vobj_fitted_cat(ao, arg_count, fit_rect, obj_rect);
			break;

		case cjkdec_rrefr:
		case cjkdec_rrefr_m:
		case cjkdec_rrefr_o:
		case cjkdec_rrefr_t:
			ao_new[0] = ao[0];
			ao_new[1] = scale_vobj(duplicate_vobj(ao[0]), xyz(-1., 1., 0.));	// copy and flip the obj
			obj_rect_new[0] = obj_rect[0];
			obj_rect_new[1] = mul_rect(obj_rect[0], xy(-1., 1.));			// flip the rect
			obj = make_cjkdec_vobj_switch(cjkdec_a_t, 2, ao_new, obj_rect_new);
			free_vobj(ao_new[1]);
			break;

		case cjkdec_ba:
		case cjkdec_ba_o:
		case cjkdec_bd:
		case cjkdec_bd_m:
		case cjkdec_bd_t:
		case cjkdec_built:
		case cjkdec_c:
		case cjkdec_cbl_o:
		case cjkdec_ctl_t:
		case cjkdec_ctlbr_t:
		case cjkdec_lock:
		case cjkdec_mb:
		case cjkdec_mc:
		case cjkdec_me:
		case cjkdec_ml:
		case cjkdec_mo:
		case cjkdec_mo0:
		case cjkdec_mo2:
		case cjkdec_mo4:
		case cjkdec_mo5:
		case cjkdec_mr:
		case cjkdec_msp:
		case cjkdec_mt:
		case cjkdec_mtl:
		case cjkdec_r_a:
		case cjkdec_r3a:
		case cjkdec_r3d:
		case cjkdec_r3d_m:
		case cjkdec_r3gw:
		case cjkdec_r3st:
		case cjkdec_r3stl:
		case cjkdec_r3str:
		case cjkdec_r3tr:
		case cjkdec_r4a:
		case cjkdec_r4d:
		case cjkdec_r4dia:
		case cjkdec_r4ref_t:
		case cjkdec_r4sq:
		case cjkdec_r5p:
		case cjkdec_r5x:
		case cjkdec_ra:
		case cjkdec_ra_m:
		case cjkdec_rd:
		case cjkdec_rd_m:
		case cjkdec_rd_s:
		case cjkdec_rd_t:
		case cjkdec_refh:
		case cjkdec_refr:
		case cjkdec_refv:
		case cjkdec_rot:
		case cjkdec_rrefd:
		case cjkdec_rrefl:
		case cjkdec_rrefl_m:
		case cjkdec_rrotd:
		case cjkdec_rrotr:
		case cjkdec_rrotu:
		case cjkdec_rs:
		case cjkdec_rsb:
		case cjkdec_rsbr:
		case cjkdec_rsq:
		case cjkdec_rst:
		case cjkdec_rstl:
		case cjkdec_s:
		case cjkdec_s_t:
		case cjkdec_sb:
		case cjkdec_sbl:
		case cjkdec_sbl_m:
		case cjkdec_sbl_o:
		case cjkdec_sbr:
		case cjkdec_sl:
		case cjkdec_sl_m:
		case cjkdec_sl_s:
		case cjkdec_sr:
		case cjkdec_st:
		case cjkdec_st_t:
		case cjkdec_stl:
		case cjkdec_stl_m:
		case cjkdec_stl_s:
		case cjkdec_str:
		case cjkdec_str_o:
		case cjkdec_w:
		case cjkdec_w_o:
		case cjkdec_w_t:
		case cjkdec_wa:
		case cjkdec_wb:
		case cjkdec_wbl:
		case cjkdec_wbr:
		case cjkdec_wd:
		case cjkdec_wl:
		case cjkdec_wl_t:
		case cjkdec_wr:
		case cjkdec_wt:
		case cjkdec_wt_t:
		case cjkdec_wtl:
		case cjkdec_wtr:
		default:
			if (arg_count==1)
				obj = duplicate_vobj(ao[0]);

			if (arg_count==2)
				obj = cat_vobj(ao[0], ao[1], 0);

			if (arg_count==3)
			{
				vo = cat_vobj(ao[0], ao[1], 0);
				obj = cat_vobj(vo, ao[2], 0);
				free_vobj(vo);
			}
	}

	return obj;
}

void make_cjkdec_vobj(vector_font_t *font, letter_t *l)
{
	uint32_t cp;
	int32_t i, *arg, dec_type, arg_count;
	letter_t *al;
	rect_t bound_rect, obj_rect[3];
	vobj_t *ao[3];

	if (l->obj)
		return ;

	cp = l->codepoint;

	if (is_cjkdec_glyph(font, cp)==0)
		return ;

	arg = &font->cjkdec_data[font->cjkdec_pos[cp]];
	dec_type = arg[1] & 0xFFFF;
	arg_count = arg[1] >> 16;

	for (i=0; i<arg_count; i++)
	{
		process_one_glyph(font, get_letter_index(font, arg[2+i]));
		al = get_letter(font, arg[2+i]);
		if (al)
		{
			obj_rect[i] = rect( xy(al->bl, al->bb), xy(al->br, al->bt) );
			ao[i] = al->obj;
		}
	}

	l->obj = make_cjkdec_vobj_switch(dec_type, arg_count, ao, obj_rect);

	bound_rect = vobj_bounding_rect(l->obj);
	l->bl = bound_rect.p0.x;
	l->br = bound_rect.p1.x;
	l->bb = bound_rect.p0.y;
	l->bt = bound_rect.p1.y;
	l->width = l->br - l->bl;
}
