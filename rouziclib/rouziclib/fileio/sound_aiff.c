double read_BE80_float_to_double(const uint8_t *buf, size_t *index)	// probably doesn't handle NANs or denorms, who cares
{
	uint16_t e80;
	uint64_t m80, i64;

	if (index)
		*index += 10;

	e80 = read_BE16(buf, NULL);
	m80 = read_BE64(&buf[2], NULL);
	i64 = (uint64_t) (e80 & 0x8000) << 48;		// sign
	i64 |= (uint64_t) ((int) e80-0x3C00) << 52;	// re-offset, mask and shift the exponent
	i64 |= (m80 & 0x7FFFFFFFFFFFFFFFLL) >> 11;	// shift the mantissa, discard the leading 1

	return *((double *) &i64);
}

void double_to_BE80_float(double d, uint8_t *buf)
{
	uint16_t e80;
	uint64_t m80, i64;

	i64 = *((uint64_t *) &d);
	m80 = (i64 & 0x000FFFFFFFFFFFFFLL) << 11;		// mantissa
	m80 |= 0x8000000000000000LL;				// leading 1
	e80 = (i64 & 0x8000000000000000LL) >> 48;		// sign
	e80 |= ((i64 & 0x7FF0000000000000LL) >> 52) + 0x3C00;	// exponent

	print_BE16(buf, e80);
	print_BE64(&buf[2], m80);
}

float *load_sound_aiff_mem(const uint8_t *data, size_t data_len, size_t *sample_count, int *channels, int *samplerate)
{
	uint8_t *p;
	int chunk_size, bit_depth, byte_depth, compression=0;
	size_t i, full_count;
	float *output, vol;
	int32_t (*func_read)(const uint8_t *, size_t *) = read_byte8s;

	// Common chunk
	p = memmem_rl(data, data_len, "COMM", 4);
	if (p==NULL)
	{
		fprintf_rl(stderr, "In load_sound_aiff_mem(): No COMM tag found, not a valid AIFF file.\n");
		return NULL;
	}
	p = &p[4];

	chunk_size = read_BE32(p, (size_t *) &p);
	*channels = read_BE16(p, (size_t *) &p);
	*sample_count = read_BE32(p, (size_t *) &p);
	bit_depth = read_BE16(p, (size_t *) &p);
	*samplerate = nearbyint(read_BE80_float_to_double(p, (size_t *) &p));
	if (chunk_size > 18)		// if there's a compression specified
	{
		if (strncmp(p, "sowt", 4)==0)	compression = 1;	// LE snd
		if (strncmp(p, "fl32", 4)==0)	compression = 2;	// BE float snd
		if (strncmp(p, "FL32", 4)==0)	compression = 2;	// BE float snd
		if (strncmp(p, "fl64", 4)==0)	compression = 3;	// BE double snd
	}

	// Prepare decoding parameters
	full_count = *sample_count * (size_t) *channels;
	byte_depth = ceil_rshift(bit_depth, 3);		// bytes per sample
	vol = 1.f / (float) (1LL << 8*byte_depth);	// volume multiplier
	switch (byte_depth)
	{
		case 2:	func_read = compression==1 ? read_LE16s : read_BE16s;	break;	
		case 3:	func_read = compression==1 ? read_LE24s : read_BE24s;	break;	
		case 4:	func_read = compression==1 ? read_LE32 : read_BE32;	break;	
	}

	// Sound data
	p = memmem_rl(data, data_len, "SSND", 4);
	if (p==NULL)
	{
		fprintf_rl(stderr, "In load_sound_aiff_mem(): No SSND tag found, not a valid AIFF file.\n");
		return NULL;
	}
	p = &p[16];

	output = calloc(*sample_count, *channels * sizeof(float));

	switch (compression)
	{
		case 0:		// integer BE
		case 1:		// integer LE
			for (i=0; i < full_count; i++)
				output[i] = func_read(&p[i * byte_depth], NULL) * vol;
			break;

		case 2:		// float BE
			for (i=0; i < full_count; i++)
				output[i] = u32_as_float(read_BE32(&p[i * 4], NULL));
			break;

		case 3:		// double BE
			for (i=0; i < full_count; i++)
				output[i] = u64_as_double(read_BE64(&p[i * 8], NULL));
			break;
	}

	return output;
}

float *load_sound_aiff_file(const char *path, size_t *sample_count, int *channels, int *samplerate)
{
	uint8_t *data;
	size_t data_len;
	float *output;

	*sample_count = 0;
	data = load_raw_file(path, &data_len);
	if (data==NULL)
		return NULL;

	output = load_sound_aiff_mem(data, data_len, sample_count, channels, samplerate);
	free(data);

	return output;
}

void save_sound_aiff_fl32_file(const char *path, float *snd, size_t sample_count, int channels, int samplerate)
{
	FILE *file;
	uint8_t be80[10];
	size_t i, full_count = sample_count * (size_t) channels;

	if (snd==NULL || sample_count==0)
		return ;

	file = fopen_utf8(path, "wb");
	if (file==NULL)
	{
		fprintf_rl(stderr, "save_sound_aiff_file() couldn't open file '%s' for writing.\n", path);
		return ;
	}

	fprintf(file, "FORM");
	fwrite_BE32(file, 4+12+(8+2+4+2+10+4+18)+(8+8+full_count*sizeof(float)));	// size of the whole file - 8 bytes
	fprintf(file, "AIFC");			// format

	fprintf(file, "FVER");
	fwrite_BE32(file, 4);
	fwrite_BE32(file, 0xA2805140);		// format version (May 23, 1990, 2:40 p.m.)

	fprintf(file, "COMM");
	fwrite_BE32(file, 2+4+2+10+4+18);	// chunk size
	fwrite_BE16(file, channels);
	fwrite_BE32(file, sample_count);
	fwrite_BE16(file, 32);			// bit depth
	double_to_BE80_float(samplerate, be80);
	fwrite(be80, 1, 10, file);		// sample rate
	fprintf(file, "fl32");			// compression
	fprintf(file, "\021IEEE 32-bit float");	// Pascal string (first byte is 17, the length)

	fprintf(file, "SSND");
	fwrite_BE32(file, 8+full_count*sizeof(float));	// chunk size
	fwrite_BE32(file, 0);			// not needed
	fwrite_BE32(file, 0);			// not needed

	// write snd in BE 32-bit float
	for (i=0; i < full_count; i++)
		fwrite_BE32(file, float_as_u32(snd[i]));

	fclose(file);
}
