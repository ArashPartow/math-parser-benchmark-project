typedef struct
{
	void **list;
	size_t len, as;
} alloc_list_t;

extern size_t alloc_enough2(void **buffer, size_t needed_count, size_t alloc_count, size_t size_elem, double inc_ratio);
extern size_t alloc_enough_and_copy2(void **buffer, void *copy_src, size_t needed_count, size_t alloc_count, size_t size_elem, double inc_ratio);
extern size_t alloc_enough_mutex2(void **buffer, size_t needed_count, size_t alloc_count, size_t size_elem, double inc_ratio, rl_mutex_t *mutex);
extern void free_null(void **ptr);
extern void **calloc_2d(const size_t ptr_count, const size_t size_buffers, const size_t size_elem);
extern void **calloc_2d_contig(const size_t ptr_count, const size_t size_buffers, const size_t size_elem);
extern void **array_1d_to_2d_contig(void *array_1d, const size_t ptr_count, const size_t size_buffers);
extern void **memcpy_2d(void **dst, void **src, const size_t ptr_count, const size_t size_buffers);
extern void **copy_2d(void **ptr, const size_t ptr_count, const size_t size_buffers);
extern void **copy_2d_contig(void **ptr, const size_t ptr_count, const size_t size_buffers, const size_t size_elem);
extern void **memset_2d(void **ptr, const int word, const size_t size, const size_t count);
extern void free_2d(void **ptr, const size_t count);
extern void free_null_2d(void ***ptr, const size_t count);
extern void *copy_alloc(void *b0, size_t size);
extern size_t next_aligned_offset(size_t offset, const size_t size_elem);
extern void add_to_alloc_list(void *ptr, alloc_list_t *list);
extern void *malloc_list(size_t size, alloc_list_t *list);
extern void *calloc_list(size_t nitems, size_t size, alloc_list_t *list);
extern void free_alloc_list(alloc_list_t *list);

// alloc_count was originally a pointer, however callers sent a mix of int and size_t which was a problem
#define alloc_enough(b, nc, acp, se, ir)	(*acp) = alloc_enough2(b, nc, (*acp), se, ir)
#define alloc_enough_and_copy(b, cs, nc, acp, se, ir)	(*acp) = alloc_enough_and_copy2(b, cs, nc, (*acp), se, ir)
#define alloc_enough_mutex(b, nc, acp, se, ir, m)	(*acp) = alloc_enough_mutex2(b, nc, (*acp), se, ir, m)
