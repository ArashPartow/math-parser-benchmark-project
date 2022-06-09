int get_bit_32(const uint32_t word, const int pos)
{
	return (word >> pos) & 1;
}

uint64_t get_bits_in_stream(uint8_t *stream, size_t start_bit, int bit_count)
{
	uint64_t r=0, b, start_byte, actual_start_bit;
	int bits_to_read, b_sh;
	uint8_t mask;

	if (bit_count==0)
		return 0;

	start_byte = start_bit >> 3;
	start_bit &= 7;
	bits_to_read = MINN(8-start_bit, bit_count);
	b_sh = MAXN(0, bit_count - bits_to_read);

	while (bit_count > 0)	// AAAaaaBB BbbbCCCc logic
	{
		bits_to_read = MINN(8-start_bit, bit_count);			// how many bits to read in this byte
		actual_start_bit = 8-start_bit - bits_to_read;
		mask = (((1<<bits_to_read)-1) << actual_start_bit);
		b = (stream[start_byte] & mask) >> actual_start_bit;
		r |= b << b_sh;

		b_sh = MAXN(0, b_sh-8);
		bit_count -= bits_to_read;				// decrement count of bits left to write

		start_bit = 0;
		start_byte++;
	}

	return r;
}

uint64_t get_bits_in_stream_inc(uint8_t *stream, size_t *start_bit, int bit_count)
{
	uint64_t r = get_bits_in_stream(stream, *start_bit, bit_count);
	*start_bit += bit_count;
	return r;
}

void set_bits_in_stream(uint8_t *stream, size_t start_bit, int bit_count, uint64_t b)
{
	size_t start_byte, actual_start_bit;
	int bits_to_write, b_sh;
	uint8_t mask;

	if (bit_count==0)
		return;

	start_byte = start_bit >> 3;
	start_bit &= 7;
	bits_to_write = MINN(8-start_bit, bit_count);
	b_sh = MAXN(0, bit_count - bits_to_write);

	/*while (bit_count > 0)	// bbAAAaaa CcccBBBb logic
	{
		bits_to_write = MINN(8-start_bit, bit_count);		// how many bits to write in this byte
		mask = (((1<<bits_to_write)-1) << start_bit);
		stream[start_byte] &= ~mask;				// mask bits to write
		stream[start_byte] |= (b << start_bit) & mask;		// add bits to write

		b >>= bits_to_write;					// remove bits just written
		bit_count -= bits_to_write;				// decrement count of bits left to write

		start_bit = 0;
		start_byte++;
	}*/

	while (bit_count > 0)	// AAAaaaBB BbbbCCCc logic
	{
		bits_to_write = MINN(8-start_bit, bit_count);			// how many bits to write in this byte
		actual_start_bit = 8-start_bit - bits_to_write;
		mask = (((1<<bits_to_write)-1) << actual_start_bit);
		stream[start_byte] &= ~mask;					// mask bits to write
		stream[start_byte] |= ((b>>b_sh) << actual_start_bit) & mask;	// add bits to write

		b_sh = MAXN(0, b_sh-8);
		bit_count -= bits_to_write;				// decrement count of bits left to write

		start_bit = 0;
		start_byte++;
	}
}

void set_bits_in_stream_inc(uint8_t *stream, size_t *start_bit, int bit_count, uint64_t b)
{
	set_bits_in_stream(stream, *start_bit, bit_count, b);
	*start_bit += bit_count;
}

uint32_t reverse_bits32(uint32_t v)	// from http://graphics.stanford.edu/~seander/bithacks.html#ReverseParallel
{
	v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
	v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
	v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
	v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
	return (v >> 16           ) | ( v              << 16);
}

uint64_t reverse_bits64(uint64_t v)
{
	v = ((v >> 1) & 0x5555555555555555ULL) | ((v & 0x5555555555555555ULL) << 1);
	v = ((v >> 2) & 0x3333333333333333ULL) | ((v & 0x3333333333333333ULL) << 2);
	v = ((v >> 4) & 0x0F0F0F0F0F0F0F0FULL) | ((v & 0x0F0F0F0F0F0F0F0FULL) << 4);
	v = ((v >> 8) & 0x00FF00FF00FF00FFULL) | ((v & 0x00FF00FF00FF00FFULL) << 8);
	v = ((v >>16) & 0x0000FFFF0000FFFFULL) | ((v & 0x0000FFFF0000FFFFULL) << 16);
	return (v >> 32                      ) | ( v                          << 32);
}

uint32_t reverse_n_bits32(uint32_t v, int n)
{
	return reverse_bits32(v) >> (32-n);
}

uint64_t reverse_n_bits64(uint64_t v, int n)
{
	return reverse_bits64(v) >> (64-n);
}

uint32_t reverse_iterator_bits32(int *i, uint32_t count)	// i should not be the for loop iterator but rather a variable that starts from 0 and isn't touched outside of this function
{
	uint32_t ir;
	int bits = log2_ffo32(count-1);

shuffle_start:
	ir = reverse_n_bits32(*i, bits);		// reverse the correct number of bits
	(*i)++;						// iterate i for the next call to this function
	if (ir >= count)				// if ir is too large
		goto shuffle_start;			// get the next ir in the sequence (jumps back up to 3 times)

	return ir;
}

xyi_t reverse_iterator_bits_2d(uint64_t *i, xyi_t dim)
{
	xyi_t ir, dim_bits;
	int ib, sh, shift;
       
	shift = log2_ffo32(MAXN(dim.x, dim.y) - 1) - 1;	// number of bits needed for each dimension

shuffle_start:
	// Shuffle bits from i into ir.x and ir.y
	ir.x = 0;
	ir.y = 0;
	sh = shift;
	for (ib=0; *i >> ib; ib++, sh--)
	{
		ir.x |= get_bit(*i, ib) << sh;
		ib++;
		ir.y |= get_bit(*i, ib) << sh;
	}

	(*i)++;						// iterate i for the next call to this function
	if (ir.x >= dim.x || ir.y >= dim.y)		// if ir is too large
		goto shuffle_start;			// get the next ir in the sequence

	return ir;
}
