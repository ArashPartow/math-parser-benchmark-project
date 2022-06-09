// like bsearch() except returns an index from a pre-sorted array that matches or immediately precedes the value to find
size_t array_find_index_by_cmp(void *value_to_find, void *array, size_t array_size, size_t elem_size, int (*cmp)(const void *, const void *))
{
	size_t i, step, smin, smax, smid;

	if (array==NULL || array_size < 1)
		return 0;

	if (cmp(value_to_find, (char*)array+elem_size*0) <= 0)
		return 0;

	if (cmp(value_to_find, (char*)array+elem_size*(array_size-1)) >= 0)
		return array_size-1;

	// Do a binary search of value_to_find
	step = next_power_of_2(array_size) >> 1;
	smin = 0;
	smax = array_size-1;

	while (step > 0)
	{
		smid = smin + step;
		smid = MINN(smid, smax);

		if (cmp(value_to_find, (char*)array+elem_size*smid) < 0)
			smax = smid;
		else
			smin = smid;

		step >>= 1;
	}

	// Get value's index
	for (i=MAXN(1, smin); i < array_size; i++)
		if (cmp(value_to_find, (char*)array+elem_size*i) < 0)
			return i-1;

	return array_size-1;
}

// Comparison functions used by qsort(), bsearch() or array_find_index_by_cmp()

int cmp_int(const int *a, const int *b)
{
	return *a - *b;
}

int cmp_double(const double *a, const double *b)
{
	if (a > b) return 1;
	if (a == b) return 0;
	return -1;
}

int cmp_xy_by_x(const xy_t *a, const xy_t *b)	// xy comparison function (for qsort) sorting by x
{
	if (a->x > b->x) return 1;
	if (a->x == b->x) return 0;
	return -1;
}
