extern void *memset32(void *buf, uint32_t word, size_t word_count);
extern void *memset64(void *buf, uint64_t word, size_t word_count);

#define memset_fl32(buf, v, word_count)	memset32(buf, float_as_u32(v), word_count)
#define memset_fl64(buf, v, word_count)	memset64(buf, double_as_u64(v), word_count)
