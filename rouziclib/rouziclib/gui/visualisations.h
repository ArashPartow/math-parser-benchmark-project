typedef struct
{
	int onscreen_index0, onscreen_index1, hover_index;
	double hover_pos, sm;
	xy_t offset;
} draw_graph_bar_ret_t;

extern draw_graph_bar_ret_t draw_graph_data_bar(rect_t area, float *data, float *label_data, int count, const char *format, double min_data_height, double max_data_height, int norm, double bar_width, col_t col);
