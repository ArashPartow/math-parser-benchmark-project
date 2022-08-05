#define DQNQ_TYPE_SIZE	4

enum dqnq_type	// entry types
{
	DQNQT_NOTYPE,
	DQNQT_BACK_TO_START,
	DQNQT_BRACKET_OPEN,
	DQNQT_BRACKET_CLOSE,
	DQNQT_LINE_THIN_ADD,
	DQNQT_POINT_ADD,
	DQNQT_RECT_FULL,
	DQNQT_RECT_BLACK,
	DQNQT_RECT_BLACK_INV,
	DQNQT_TRIANGLE,
	DQNQT_TETRAGON,
	DQNQT_EFFECT_NOARG,
	DQNQT_EFFECT_FL1,
	DQNQT_COL_MATRIX,
	DQNQT_CIRCLE_FULL,
	DQNQT_CIRCLE_HOLLOW,
	DQNQT_BLIT_BILINEAR,
	DQNQT_BLIT_FLATTOP,
	DQNQT_BLIT_FLATTOP_ROT,
	DQNQT_BLIT_AANEAREST,
	DQNQT_BLIT_AANEAREST_ROT,
	DQNQT_BLIT_PHOTO,
	DQNQT_TEST1,
	DQNQT_VOBJ,

	DQNQT_COUNT
};

extern int32_t dqnqt_arg_size[DQNQT_COUNT];
#define dqnq_entry_size(type)	(dqnqt_arg_size[type] + DQNQ_TYPE_SIZE)

extern void dqnq_init();
extern void dqnq_reset();
extern enum dqnq_type dqnq_read_type_id(volatile uint8_t *data, size_t *index);
extern void dqnq_write_type_id(volatile uint8_t *entry, const enum dqnq_type type);
extern void dqnq_finish_entry(const enum dqnq_type type);
extern volatile uint8_t *dqnq_new_entry(const enum dqnq_type type);
extern int dqnq_thread(void *unused);
extern void dqnq_read_execute(const enum dqnq_type type, size_t *read_pos);
