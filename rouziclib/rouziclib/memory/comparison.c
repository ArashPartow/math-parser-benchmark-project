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

// Sorting into an array of order indices instead of rearranging the original array

_Thread_local uint8_t *array_to_order;
_Thread_local size_t elem_size_to_order;
_Thread_local int (*cmp_for_ordering)(const void *, const void *);

int cmp_array_entry(const size_t *a, const size_t *b)
{
	return cmp_for_ordering(&array_to_order[*a * elem_size_to_order], &array_to_order[*b * elem_size_to_order]);
}

size_t *make_order_index_array(void *array, size_t *order, size_t elem_count, size_t elem_size, int (*cmp)(const void *, const void *), int permutate)
{
	// If order is provided by the caller it should have suitable contents, such as when updating an order

	// Initialise the order array if not already provided
	if (order == NULL)
	{
		order = calloc(elem_count, sizeof(size_t));

		// Initialise the order array to the unsorted indices
		for (size_t i=0; i < elem_count; i++)
			order[i] = i;
	}

	// Globals used by the comparison function to order the array
	array_to_order = array;
	elem_size_to_order = elem_size;
	cmp_for_ordering = cmp;

	// Order the order array
	qsort(order, elem_count, sizeof(size_t), cmp_array_entry);

	// Permutate order so that order[i] gives the index to the entry in the unsorted array rather than the reverse
	if (permutate)
		index_value_permutation(order, elem_count);

	return order;
}

void index_value_permutation(size_t *a, size_t n)
{
	size_t i, i1, i2, ic=0;

start:
	// Look for next cycle
	for (; ic < n; ic++)
		if (a[ic] != ic && a[ic] < n)
			break;
	i = ic;
	ic++;

	// If a cycle was found
	if (i < n)
	{
		i1 = a[i];

		// Permutate this cycle
		while (a[i1] < n)
		{
			i2 = a[i1];	// save the original value
			a[i1] = i + n;	// add n to signal it as being permutated
			i = i1;
			i1 = i2;
		}

		goto start;
	}

	// Remove the n offset
	for (i=0; i < n; i++)
		if (a[i] >= n)
			a[i] -= n;
}

// Comparison functions used by qsort(), bsearch() or array_find_index_by_cmp()

int cmp_int(const int *a, const int *b)
{
	return *a - *b;
}

int cmp_uint64(const uint64_t *a, const uint64_t *b)
{
	if (*a > *b) return 1;
	if (*a == *b) return 0;
	return -1;
}

int cmp_uint64_inv(const uint64_t *a, const uint64_t *b)
{
	return -cmp_uint64(a, b);
}

int cmp_double(const double *a, const double *b)
{
	if (*a > *b) return 1;
	if (*a == *b) return 0;
	return -1;
}

int cmp_xy_by_x(const xy_t *a, const xy_t *b)	// xy comparison function (for qsort) sorting by x
{
	if (a->x > b->x) return 1;
	if (a->x == b->x) return 0;
	return -1;
}
