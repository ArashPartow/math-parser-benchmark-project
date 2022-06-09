void draw_effect_noarg(enum dq_type type)
{
	float *df = drawq_add_to_main_queue(type);
	if (df==NULL)
		return;

	drawq_add_sectors_for_already_set_sectors();
}

void draw_effect_arg_double(enum dq_type type, double v)
{
	float *df = drawq_add_to_main_queue(type);
	if (df==NULL)
		return;
	df[0] = v;

	drawq_add_sectors_for_already_set_sectors();
}

void draw_colour_matrix(double *matrix)
{
	float *df = drawq_add_to_main_queue(DQT_COL_MATRIX);
	if (df==NULL)
		return;

	for (int i=0; i < 9; i++)
		df[i] = isnan(matrix[i]) ? 0.f : matrix[i];

	drawq_add_sectors_for_already_set_sectors();
}
