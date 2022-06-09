void swap_float(float *a, float *b)
{
	float c = *a;

	*a = *b;
	*b = c;
}

void swap_double(double *a, double *b)
{
	double c = *a;

	*a = *b;
	*b = c;
}

void swap_xy_xy(xy_t *a, xy_t *b)
{
	xy_t c = *a;

	*a = *b;
	*b = c;
}

void swap_i32(int32_t *a, int32_t *b)
{
	int32_t c = *a;

	*a = *b;
	*b = c;
}

void swap_int(int *a, int *b)
{
	int c = *a;

	*a = *b;
	*b = c;
}

void swap_ptr(void **a, void **b)
{
	void *c = *a;

	*a = *b;
	*b = c;
}

void swap_char(char *a, char *b)
{
	char c = *a;

	*a = *b;
	*b = c;
}
