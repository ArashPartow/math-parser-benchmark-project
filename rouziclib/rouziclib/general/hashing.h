extern uint64_t get_pointer_hash(const void *ptr);
extern uint64_t get_buffer_hash(const void *ptr, size_t size);
extern uint64_t get_string_hash(const char *string);
extern uint64_t get_2D_buffer_hash(const void **ptr, size_t size, size_t count);
