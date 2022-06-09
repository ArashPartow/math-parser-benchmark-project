extern ssize_t circ_index(ssize_t index, const size_t size);
extern void *memset_circular(void *s, int c, size_t esize, size_t num, ssize_t pos, size_t limit);
extern void *memcpy_circular(void *dest, void *src, size_t esize, size_t num, ssize_t pos, size_t limit);
extern ssize_t memcpy_to_circular(void *dest, void *src, size_t esize, size_t num, ssize_t pos, size_t limit);
