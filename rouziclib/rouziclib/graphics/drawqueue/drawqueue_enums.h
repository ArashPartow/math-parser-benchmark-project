enum
{
	DQ_END = 0,			// points to after the last entered number in the buffer

	// sector_list specific
	DQ_ENTRY_START = 1,		// points to the start of the entry
	DQ_END_HEADER_SL,		// the end of the header, where the first entry should start
};

enum dq_type	// entry types
{
	DQT_NOTYPE,
	DQT_BRACKET_OPEN,
	DQT_BRACKET_CLOSE,
	DQT_LINE_THIN_ADD,
	DQT_POINT_ADD,
	DQT_RECT_FULL,
	DQT_RECT_BLACK,
	DQT_RECT_BLACK_INV,
	DQT_PLAIN_FILL,
	DQT_TRIANGLE,
	DQT_TETRAGON,
	DQT_GAIN,
	DQT_GAIN_PARAB,
	DQT_LUMA_COMPRESS,
	DQT_COL_MATRIX,
	DQT_CLIP,
	DQT_CLAMP,
	DQT_CIRCLE_FULL,
	DQT_CIRCLE_HOLLOW,
	DQT_BLIT_BILINEAR,
	DQT_BLIT_FLATTOP,
	DQT_BLIT_FLATTOP_ROT,
	DQT_BLIT_AANEAREST,
	DQT_BLIT_AANEAREST_ROT,
	DQT_BLIT_PHOTO,
	DQT_TEST1,
};

enum dq_blend	// blending modes
{
	DQB_ADD,
	DQB_SUB,
	DQB_MUL,
	DQB_DIV,
	DQB_BLEND,
	DQB_SOLID,
};
