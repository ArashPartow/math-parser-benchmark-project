ssize_t circ_index(ssize_t index, const size_t size)
{
	if (size <= 0)
		return 0;

	while (index < 0)
		index += size;

	while (index >= size)
		index -= size;

	return index;
}

// example call: memset_circular(buffer, 0, sizeof(double), 120, buffer_start, buffer_size);
void *memset_circular(void *s, int c, size_t esize, size_t num, ssize_t pos, size_t limit)
{
	uint8_t *sb = s;

	pos = circ_index(pos, limit);

	if (pos+num <= limit)
		memset(&sb[pos*esize], c, num * esize);
	else
	{
		memset(&sb[pos*esize], c, (limit-pos) * esize);
		memset(s, c, (num-(limit-pos)) * esize);
	}

	return s;
}

// Copy circular buffer from pos to linear buffer from 0
// example call: memcpy_circular(dest, src, sizeof(double), 120, buffer_start, buffer_size);
void *memcpy_circular(void *dest, void *src, size_t esize, size_t num, ssize_t pos, size_t limit)
{
	uint8_t *db = dest, *sb = src;

	pos = circ_index(pos, limit);

	if (pos+num <= limit)
		memcpy(db, &sb[pos*esize], num * esize);
	else
	{
		memcpy(db, &sb[pos*esize], (limit-pos) * esize);
		memcpy(&db[(limit-pos) * esize], sb, (num-(limit-pos)) * esize);
	}

	return dest;
}

// Copy linear buffer from 0 to circular buffer from pos
ssize_t memcpy_to_circular(void *dest, void *src, size_t esize, size_t num, ssize_t pos, size_t limit)
{
	uint8_t *db = dest, *sb = src;

	pos = circ_index(pos, limit);

	if (pos+num <= limit)
		memcpy(&db[pos*esize], sb, num * esize);
	else
	{
		memcpy(&db[pos*esize], sb, (limit-pos) * esize);
		memcpy(db, &sb[(limit-pos) * esize], (num-(limit-pos)) * esize);
	}

	pos = circ_index(pos+num, limit);

	return pos;
}
