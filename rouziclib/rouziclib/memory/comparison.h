extern size_t array_find_index_by_cmp(void *value_to_find, void *array, size_t array_size, size_t elem_size, int (*cmp)(const void *, const void *));

extern int cmp_int(const int *a, const int *b);
extern int cmp_double(const double *a, const double *b);
extern int cmp_xy_by_x(const xy_t *a, const xy_t *b);
