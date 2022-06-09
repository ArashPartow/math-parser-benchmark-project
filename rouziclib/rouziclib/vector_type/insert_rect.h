enum		// inserting-spacing codepoints (must match font in ../vector_type/private_use.txt)
{
	cp_ins_start=0xE010,
	cp_ins_w0=cp_ins_start,		// \356\200\22_
	cp_ins_w1,
	cp_ins_w2,
	cp_ins_w3,
	cp_ins_w4,
	cp_ins_w5,
	cp_ins_w6,
	cp_ins_w7,
	cp_ins_w8,			// \356\200\23_
	cp_ins_w9,
	cp_ins_w10,
	cp_ins_w11,
	cp_ins_w12,
	cp_ins_w0_1,
	cp_ins_w0_2,
	cp_ins_w0_3,
	cp_ins_w0_4,			// \356\200\24_
	cp_ins_w0_5,
	cp_ins_w0_6,
	cp_ins_w24,
	cp_ins_w36,
	cp_ins_w48,
	cp_ins_w60,
	cp_ins_w72,
	cp_ins_w84,			// \356\200\25_
	cp_ins_w96,
	cp_ins_w108,
	cp_ins_w120,
	cp_ins_w240,
	cp_ins_w360,
	cp_ins_w480,
	cp_ins_w600,

	cp_ins_nul=0xE030,		// \356\200\26_

	cp_ins_end,

	cp_ins_index_base=0xE0100	// variation selectors, represents index 0, starts at \363\240\204\200
};

extern void reset_insert_rect_array();
extern void report_insert_rect_pos(xy_t pos, xy_t dim, int bidi, int index);
extern int parse_insert_rect_charseq(xy_t p, xy_t *off, double scale, int bidi, int cp0, const char *string);
extern rect_t get_insert_rect_zc(zoom_t zc, int index);
extern rect_t insert_rect_change_height(rect_t r, double low, double high);

#define get_insert_rect(index)	get_insert_rect_zc(zc, index)
