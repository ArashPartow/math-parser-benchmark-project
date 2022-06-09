extern int get_state_checkbox_array(int *array, int len);
extern int ctrl_array_checkbox(int *array, int count, const char **label, col_t *col, int col_count, rect_t box, xy_t pos_inc);
extern int ctrl_array_checkbox_with_all(int *array, int count, const char *all_label, col_t all_col, const char **label, col_t *col, int col_count, rect_t box, xy_t pos_inc);
extern int ctrl_array_radio(int *sel, int count, const char **label, col_t *col, int col_count, rect_t box, xy_t pos_inc);
extern int ctrl_checkbox_subknob(double *v_orig, double step, double ctrl_num, double subknob_num, knob_t *knob, rect_t topbox, col_t colour);
extern int ctrl_array_knob(double *knob_value, knob_t *knob_data, int count, col_t *col, int col_count, rect_t box, xy_t pos_inc);
