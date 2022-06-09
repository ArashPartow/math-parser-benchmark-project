void lzw_dict_init(buffer_t **dict, size_t *dict_as)
{
	uint8_t byte;

	if (*dict_as == 0)
		alloc_enough(dict, 4096, dict_as, sizeof(buffer_t), 1.);

	for (int i=0; i < *dict_as; i++)
	{
		clear_buf(&(*dict)[i]);

		if (i < 256)			// set the first 256 elements to i as a one byte entry
		{
			byte = i;
			bufwrite(&(*dict)[i], &byte, sizeof(byte));
		}
	}
}

void lzw_add_to_dict(buffer_t **dict, size_t *dict_as, size_t index, int append, uint8_t *data, size_t data_len, int *bpc)
{
	alloc_enough(dict, index+2, dict_as, sizeof(buffer_t), 2.);	// make room for the requested entry

	if (append==0)
		clear_buf(&(*dict)[index]);
	bufwrite(&(*dict)[index], data, data_len);
}

void tiff_lzw_calc_maxcode(int bpc, int *maxcode)
{
	*maxcode = ((1L<<bpc)-1) - 1;
}

void tiff_lzw_calc_bpc(int new_index, int *bpc, int *maxcode)
{
	if (new_index > *maxcode)
	{
		(*bpc)++;
		tiff_lzw_calc_maxcode(*bpc, maxcode);
	}
}

void tiff_lzw_decode(uint8_t *coded, buffer_t *dec, int bytesperstrip)
{
	buffer_t word={0}, outstring={0};
	size_t coded_pos;	// position in bits
	int i=0, new_index, code, maxcode, bpc, dec_limit;

	buffer_t *dict={0};
	size_t dict_as=0;

	bpc = 9;				// starts with 9 bits per code, increases later
	tiff_lzw_calc_maxcode(bpc, &maxcode);	// starts at 510, which indicates where new_index triggers an increment of bpc
	new_index = 258;			// index at which new dict entries begin
	coded_pos = 0;				// bit position
	dec_limit = dec->len + bytesperstrip;	// we must stop decoding based on the number of decoded bytes per strip

	lzw_dict_init(&dict, &dict_as);

	while ((code = get_bits_in_stream(coded, coded_pos, bpc)) != 257)	// while ((Code = GetNextCode()) != EoiCode) 
	{
		coded_pos += bpc;

		if (code > new_index)
		{
			fprintf_rl(stderr, "Out of range code %d (new_index %d)\n", code, new_index);
			break;
		}

		if (code == 256)						// if (Code == ClearCode)
		{
			lzw_dict_init(&dict, &dict_as);				// InitializeTable();
			bpc = 9;
			tiff_lzw_calc_maxcode(bpc, &maxcode);
			new_index = 258;

			code = get_bits_in_stream(coded, coded_pos, bpc);	// Code = GetNextCode();
			coded_pos += bpc;

			if (code == 257)					// if (Code == EoiCode)
				break;

			append_buf(dec, &dict[code]);				// WriteString(StringFromCode(Code));

			clear_buf(&word);
			append_buf(&word, &dict[code]);				// OldCode = Code;
		}
		else if (code < 4096)
		{
			if (dict[code].len)					// if (IsInTable(Code))
			{
				append_buf(dec, &dict[code]);			// WriteString(StringFromCode(Code));

				lzw_add_to_dict(&dict, &dict_as, new_index, 0, word.buf, word.len, &bpc);
				lzw_add_to_dict(&dict, &dict_as, new_index, 1, dict[code].buf, 1, &bpc);	// AddStringToTable
			}
			else
			{
				clear_buf(&outstring);
				append_buf(&outstring, &word);
				bufwrite(&outstring, word.buf, 1);		// OutString = StringFromCode(OldCode) + FirstChar(StringFromCode(OldCode));

				append_buf(dec, &outstring);			// WriteString(OutString);

				lzw_add_to_dict(&dict, &dict_as, new_index, 0, outstring.buf, outstring.len, &bpc);	// AddStringToTable
			}

			if (dec->len >= dec_limit)
				break;

			new_index++;
			tiff_lzw_calc_bpc(new_index, &bpc, &maxcode);

			clear_buf(&word);
			append_buf(&word, &dict[code]);			// OldCode = Code;
		}
	}

	free_buf(&word);
	free_buf(&outstring);
	for (i=0; i < dict_as; i++)
		free_buf(&dict[i]);
	free(dict);
}

void tiff_lzw_diff_decode(uint8_t *d, tiff_info_t info)
{
	xyi_t ip;
	int ic, prev;
	int8_t *p8;

	// 8-bit (and somehow 16-bit) version
	for (ip.y=0; ip.y < info.dim.y; ip.y++)
	{
		for (ic=0; ic < info.chan; ic++)
		{
			prev = 0;

			for (ip.x=0; ip.x < info.dim.x; ip.x++)
			{
				p8 = &d[(ip.y*info.dim.x + ip.x)*info.chan + ic];

				p8[0] += prev;
				prev = p8[0];
			}
		}
	}
}
