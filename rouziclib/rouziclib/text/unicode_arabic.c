int unicode_arabic_can_connect(uint32_t c, int next)	// finds if the codepoint is an Arabic letter whose context-appropriate presentation form can connect to the previous or next letter
{
	uint32_t i;
	unicode_data_t ucd;

	if (c < 0x0622 || c > 0x064A)	// doesn't deal with hardcoded presentation form characters
		return 0;

	// look for presentation forms of the codepoint
	for (i=0xFE70; i <= 0xFEFF; i++)
	{
		ucd = get_unicode_data(i);

		if (ucd.combo1==c)
			if (ucd.decomp_type==decomp_medial || (next==0 && ucd.decomp_type==decomp_final) || (next && ucd.decomp_type==decomp_initial))
				return 1;
	}

	return 0;
}

uint32_t find_arabic_form(uint32_t c, int form_type)	// get the codepoint for the specified presentation form type
{
	uint32_t i;
	unicode_data_t ucd;

	if (form_type==decomp_isolated)
		return c;

	if (c < 0x0622 || c > 0x064A)
		return c;

	// look for presentation forms of the codepoint
	for (i=0xFE70; i <= 0xFEFF; i++)
	{
		ucd = get_unicode_data(i);

		if (ucd.combo1==c)
			if (ucd.decomp_type==form_type)
				return i;
	}
	return c;
}

uint32_t get_arabic_form(uint32_t c, const uint8_t *string, int len, int prev_con1)
{
	size_t i;
	int con0, con1, next_con0=0, form=0;
	uint32_t cn;
	unicode_data_t ucd;

	if (c < 0x0600 || c > 0x06FF)
		return c;

	con0 = unicode_arabic_can_connect(c, 0);
	con1 = unicode_arabic_can_connect(c, 1);

	// if this letter (c) can connect to the next letter
	if (con1)
	{
		// find next letter, ignoring combining marks
		for (i=0; i<len; i++)
		{
			cn = utf8_to_unicode32(&string[i], &i);
			ucd = get_unicode_data(cn);

			// find if it connects or not
			if (ucd.bidicat!=bidicat_NSM)	// next character that is not a combining mark
			{
				next_con0 = unicode_arabic_can_connect(cn, 0);		// change con1 to 0 if it doesn't connect
				break;
			}
		}

	}

	// determine form type from the two connection states
	con0 &= prev_con1;
	con1 &= next_con0;
	form = (con1 << 1) | con0;

	switch (form)
	{
		case 0:	form = decomp_isolated;	break;
		case 1:	form = decomp_final;	break;
		case 2:	form = decomp_initial;	break;
		case 3:	form = decomp_medial;	break;
	}

	// find the codepoint for the correct form type, if any
	return find_arabic_form(c, form);
}
