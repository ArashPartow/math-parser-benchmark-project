void *memset32(void *buf, uint32_t word, size_t word_count)
{
	size_t i;
	uint32_t *buf32=buf;

	for (i=0; i < word_count; i++)
		buf32[i] = word;

	return buf;
}

void *memset64(void *buf, uint64_t word, size_t word_count)
{
	size_t i;
	uint64_t *buf64=buf;

	for (i=0; i < word_count; i++)
		buf64[i] = word;

	return buf;
}
