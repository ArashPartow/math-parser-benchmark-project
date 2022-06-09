#define get_bit(word, pos)	(((word) >> (pos)) & 1)

extern int get_bit_32(const uint32_t word, const int pos);
extern uint64_t get_bits_in_stream(uint8_t *stream, size_t start_bit, int bit_count);
extern uint64_t get_bits_in_stream_inc(uint8_t *stream, size_t *start_bit, int bit_count);
extern void set_bits_in_stream(uint8_t *stream, size_t start_bit, int bit_count, uint64_t b);
extern void set_bits_in_stream_inc(uint8_t *stream, size_t *start_bit, int bit_count, uint64_t b);
extern uint32_t reverse_bits32(uint32_t v);
extern uint64_t reverse_bits64(uint64_t v);
extern uint32_t reverse_n_bits32(uint32_t v, int n);
extern uint64_t reverse_n_bits64(uint64_t v, int n);
extern uint32_t reverse_iterator_bits32(int *i, uint32_t count);
extern xyi_t reverse_iterator_bits_2d(uint64_t *i, xyi_t dim);
