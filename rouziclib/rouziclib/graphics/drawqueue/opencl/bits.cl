int idiv_ceil(int a, int b)	// 30 / 10 returns 3, 31 / 10 returns 4
{
	int d = a / b;

	if (d*b < a)
		d += 1;

	return d;
}

ulong get_bits_in_stream(global uchar *stream, ulong start_bit, uint bit_count)
{
	ulong r=0, b, start_byte, actual_start_bit;
	int bits_to_read, b_sh;
	uchar mask;

	if (bit_count==0)
		return 0;

	start_byte = start_bit >> 3;
	start_bit &= 7;
	bits_to_read = min((int) (8-start_bit), (int) bit_count);
	b_sh = max((int) 0, (int) (bit_count - bits_to_read));

	while (bit_count > 0)	// AAAaaaBB BbbbCCCc logic
	{
		bits_to_read = min((int) (8-start_bit), (int) bit_count);			// how many bits to read in this byte
		actual_start_bit = 8-start_bit - bits_to_read;
		mask = (((1<<bits_to_read)-1) << actual_start_bit);
		b = (stream[start_byte] & mask) >> actual_start_bit;
		r |= b << b_sh;

		b_sh = max((int) 0, (int) (b_sh-8));
		bit_count -= bits_to_read;				// decrement count of bits left to write

		start_bit = 0;
		start_byte++;
	}

	return r;
}

ulong get_bits_in_stream_inc(global uchar *stream, ulong *start_bit, uint bit_count)
{
	ulong r = get_bits_in_stream(stream, *start_bit, bit_count);
	*start_bit += bit_count;
	return r;
}
