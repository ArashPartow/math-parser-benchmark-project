// Drawqueue
void draw_effect_noarg_dq(enum dq_type effect_type)
{
	float *df = drawq_add_to_main_queue(effect_type);
	if (df==NULL)
		return;

	drawq_add_sectors_for_already_set_sectors();
}

void draw_effect_arg_double_dq(enum dq_type effect_type, double v)
{
	float *df = drawq_add_to_main_queue(effect_type);
	if (df==NULL)
		return;
	df[0] = v;

	drawq_add_sectors_for_already_set_sectors();
}

void draw_colour_matrix_dq(double *matrix)
{
	float *df = drawq_add_to_main_queue(DQT_COL_MATRIX);
	if (df==NULL)
		return;

	for (int i=0; i < 9; i++)
		df[i] = isnan(matrix[i]) ? 0.f : matrix[i];

	drawq_add_sectors_for_already_set_sectors();
}

// Drawqueue-enqueue
void draw_effect_noarg_dqnq(enum dq_type effect_type)
{
	const enum dqnq_type type = DQNQT_EFFECT_NOARG;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, effect_type);

	dqnq_finish_entry(type);
}

void draw_effect_arg_double_dqnq(enum dq_type effect_type, double v)
{
	const enum dqnq_type type = DQNQT_EFFECT_FL1;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	write_LE32(&p, effect_type);
	write_LE32(&p, float_as_u32(v));

	dqnq_finish_entry(type);
}

void draw_colour_matrix_dqnq(double *matrix)
{
	const enum dqnq_type type = DQNQT_COL_MATRIX;

	// Get pointer to data buffer
	uint8_t *p = (uint8_t *) dqnq_new_entry(type);

	// Write arguments to buffer
	for (int i=0; i < 9; i++)
		write_LE32(&p, float_as_u32(matrix[i]));

	dqnq_finish_entry(type);
}

// Generic
void draw_effect_noarg(enum dq_type effect_type)
{
	if (fb->use_dqnq)
		draw_effect_noarg_dqnq(effect_type);
	else
		draw_effect_noarg_dq(effect_type);
}

void draw_effect_arg_double(enum dq_type effect_type, double v)
{
	if (fb->use_dqnq)
		draw_effect_arg_double_dqnq(effect_type, v);
	else
		draw_effect_arg_double_dq(effect_type, v);
}

void draw_colour_matrix(double *matrix)
{
	if (fb->use_dqnq)
		draw_colour_matrix_dqnq(matrix);
	else
		draw_colour_matrix_dq(matrix);
}
