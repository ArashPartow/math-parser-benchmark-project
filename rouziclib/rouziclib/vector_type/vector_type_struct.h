typedef struct
{
	uint32_t codepoint, alias;
	vobj_t *obj;
	double bl, br, bb, bt;	// bounds to the left and right, bottom and top
	double width;
	textedit_t glyphdata_edit;
	int point_count, line_count;
	int pid_offset, max_pid;
} letter_t;

typedef struct
{
	letter_t *l;
	int letter_count, alloc_count;
	int32_t *codepoint_letter_lut;
	int32_t *cjkdec_pos, *cjkdec_data;
	int cjkdec_data_count, cjkdec_alloc_count;
} vector_font_t;

typedef struct
{
	xy_t pos;
	double scale;
	int bidi;
} text_pos_t;

static text_pos_t make_text_pos(xy_t pos, double scale, int bidi)
{
	text_pos_t tp;

	tp.pos = pos;
	tp.scale = scale;
	tp.bidi = bidi;

	return tp;
}

typedef struct
{
	int getpos_count;
	text_pos_t *getpos;
} text_param_t;
