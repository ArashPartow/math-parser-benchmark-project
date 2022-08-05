extern size_t array_find_index_by_cmp(void *value_to_find, void *array, size_t array_size, size_t elem_size, int (*cmp)(const void *, const void *));
extern size_t *make_order_index_array(void *array, size_t *order, size_t elem_count, size_t elem_size, int (*cmp)(const void *, const void *), int permutate);
extern void index_value_permutation(size_t *a, size_t n);

extern int cmp_int(const int *a, const int *b);
extern int cmp_uint64(const uint64_t *a, const uint64_t *b);
extern int cmp_uint64_inv(const uint64_t *a, const uint64_t *b);
extern int cmp_double(const double *a, const double *b);
extern int cmp_xy_by_x(const xy_t *a, const xy_t *b);
