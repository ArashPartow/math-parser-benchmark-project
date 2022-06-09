#include "../libraries/xxh64.c"

uint64_t get_pointer_hash(const void *ptr)
{
	return XXH64(&ptr, sizeof(void *), 0);
}

uint64_t get_buffer_hash(const void *ptr, size_t size)
{
	return XXH64(ptr, size, 0);
}

uint64_t get_string_hash(const char *string)
{
	return get_buffer_hash(string, strlen(string));
}

uint64_t get_2D_buffer_hash(const void **ptr, size_t size, size_t count)
{
	int i;
	XXH64_state_t state;

	XXH64_reset(&state, 0);

	for (i=0; i < count; i++)
		XXH64_update(&state, ptr[i], size);

	return XXH64_digest(&state);
}
