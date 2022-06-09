typedef struct
{
	int8_t *status;
	int status_as, status_count;
	int cur_start, cur_end;
} seq_selection_t;

extern seq_selection_t init_seq_selection(const int count);
extern void free_seq_selection(seq_selection_t *sel);
extern void seq_selection_click_process(seq_selection_t *sel, int index, int shift, int control);
extern int seq_selection_sel_count(seq_selection_t *sel);
extern int seq_selection_find_first(seq_selection_t *sel);
extern int seq_selection_find_last(seq_selection_t *sel);
