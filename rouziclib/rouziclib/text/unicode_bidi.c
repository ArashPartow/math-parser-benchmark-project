int bidicat_direction(int bc)
{
	switch (bc)
	{
		case bidicat_L:
		case bidicat_LRE:
		case bidicat_LRO:
			return 2;	// LTR

		case bidicat_R:
		case bidicat_AL:
		case bidicat_RLE:
		case bidicat_RLO:
			return -2;	// RTL

		case bidicat_PDF:
			return 10;	// stop direction

		case bidicat_EN:
		case bidicat_ES:
		case bidicat_ET:
		case bidicat_AN:
		case bidicat_CS:
			return 1;	// sub-LTR

		case bidicat_NSM:
		case bidicat_BN:
		case bidicat_B:
		case bidicat_S:
		case bidicat_WS:
		case bidicat_ON:
			return 0;	// neutral
	}

	return 0;
}

int find_len_bidi_section(const char *string, int len, int bidi)
{
	size_t i, is;
	int last_non_NSM=0, len_sec=0;
	uint32_t c;
	unicode_data_t ucd;
	int c_bidi;

	if (bidi==2)		// LTR
		return len;	// a strong LTR section encompasses everything, as everything else is just a sub-section

	if (len < 0)
		len = strlen(string);

	for (i=0; i < len; i++)
	{
		is = i;
		c = utf8_to_unicode32(&string[i], &i);
		ucd = get_unicode_data(c);
		c_bidi = bidicat_direction(ucd.bidicat);

		if (c=='\n')			// end section at line return
			return len_sec;

		if (bidi==-2)			// RTL
			if (c_bidi >= 2)	// change to LTR
				return len_sec;

		if (bidi==1)			// weak LTR inside parent RTL section
			if (c_bidi!=1)
				return len_sec;

		if (bidi==c_bidi)		// if directions strongly match
			len_sec = i + 1;	// set length to include the full current character

		if (ucd.bidicat!=bidicat_NSM)	// take note of the last character that is not a combining mark
			last_non_NSM = is;

		if (ucd.bidicat==bidicat_NSM && len_sec>=last_non_NSM)	// include combining marks attached to the last included character
			len_sec = i + 1;
	}

	return len_sec;
}
