// UTF-8

int utf8_char_size(const uint8_t *c)
{
	const uint8_t	m0x	= 0x80, c0x	= 0x00,
	      		m10x	= 0xC0, c10x	= 0x80,
	      		m110x	= 0xE0, c110x	= 0xC0,
	      		m1110x	= 0xF0, c1110x	= 0xE0,
	      		m11110x	= 0xF8, c11110x	= 0xF0;

	if ((c[0] & m0x) == c0x)
		return 1;

	if ((c[0] & m110x) == c110x)
	if ((c[1] & m10x) == c10x)
		return 2;

	if ((c[0] & m1110x) == c1110x)
	if ((c[1] & m10x) == c10x)
	if ((c[2] & m10x) == c10x)
		return 3;

	if ((c[0] & m11110x) == c11110x)
	if ((c[1] & m10x) == c10x)
	if ((c[2] & m10x) == c10x)
	if ((c[3] & m10x) == c10x)
		return 4;

	if ((c[0] & m10x) == c10x)	// not a first UTF-8 byte
		return 0;

	return -1;			// if c[0] is a first byte but the other bytes don't match
}

int codepoint_utf8_size(const uint32_t c)
{
	if (c < 0x0080) return 1;
	if (c < 0x0800) return 2;
	if (c < 0x10000) return 3;
	if (c < 0x110000) return 4;

	return 0;
}

uint32_t utf8_to_unicode32(const uint8_t *c, size_t *index)
{
	uint32_t v;
	size_t size;
	const uint8_t m6 = 63, m5 = 31, m4 = 15, m3 = 7;

	if (c==NULL)
		return 0;

	size = utf8_char_size(c);

	if (size > 0 && index)
		*index += size-1;

	switch (size)
	{
		case 1:
			v = c[0];
			break;
		case 2:
			v = c[0] & m5;
			v = v << 6 | (c[1] & m6);
			break;
		case 3:
			v = c[0] & m4;
			v = v << 6 | (c[1] & m6);
			v = v << 6 | (c[2] & m6);
			break;
		case 4:
			v = c[0] & m3;
			v = v << 6 | (c[1] & m6);
			v = v << 6 | (c[2] & m6);
			v = v << 6 | (c[3] & m6);
			break;
		case 0:				// not a first UTF-8 byte
		case -1:			// corrupt UTF-8 letter
		default:
			v = -1;
			break;
	}

	return v;
}

uint8_t *sprint_unicode(uint8_t *str, uint32_t c)	// str must be able to hold 1 to 5 bytes and will be null-terminated by this function
{
	const uint8_t m6 = 63;
	const uint8_t	c10x	= 0x80,
	      		c110x	= 0xC0,
	      		c1110x	= 0xE0,
	      		c11110x	= 0xF0;

	if (c < 0x0080)
	{
		str[0] = c;
		if (c > 0)
			str[1] = '\0';
	}
	else if (c < 0x0800)
	{
		str[1] = (c & m6) | c10x;
		c >>= 6;
		str[0] = c | c110x;
		str[2] = '\0';
	}
	else if (c < 0x10000)
	{
		str[2] = (c & m6) | c10x;
		c >>= 6;
		str[1] = (c & m6) | c10x;
		c >>= 6;
		str[0] = c | c1110x;
		str[3] = '\0';
	}
	else if (c < 0x200000)
	{
		str[3] = (c & m6) | c10x;
		c >>= 6;
		str[2] = (c & m6) | c10x;
		c >>= 6;
		str[1] = (c & m6) | c10x;
		c >>= 6;
		str[0] = c | c11110x;
		str[4] = '\0';
	}
	else
		str[0] = '\0';		// Unicode character doesn't map to UTF-8

	return str;
}

int find_prev_utf8_char(const uint8_t *str, int pos)
{
	if (pos > 0)
	{
		do
		{
			pos--;
		}
		while (utf8_char_size(&str[pos])==0 && pos > 0);
	}

	return pos;
}

int find_next_utf8_char(const uint8_t *str, int pos)
{
	int il;

	if (pos < strlen(str))
	{
		il = utf8_char_size(&str[pos]);
		if (il==-1 || il==0)	// corrupt letter or non-first byte
			il = 1;
		pos += il;
	}

	return pos;
}

// UTF-16

size_t strlen_utf16(const uint16_t *str)
{
	size_t i;

	for (i=0; ; i++)
		if (str[i]==0)
			return i;
}

int utf16_char_size(const uint16_t *c)
{
	if (c[0] <= 0xD7FF || c[0] >= 0xE000)
		return 1;
	else if (c[1]==0)			// if there's an abrupt mid-character stream end
		return 1;
	else
		return 2;
}

int codepoint_utf16_size(uint32_t c)
{
	if (c < 0x10000) return 1;
	if (c < 0x110000) return 2;

	return 0;
}

uint32_t utf16_to_unicode32(const uint16_t *c, size_t *index)
{
	uint32_t v;
	size_t size;

	size = utf16_char_size(c);

	if (size > 0 && index)
		*index += size-1;

	switch (size)
	{
		case 1:
			v = c[0];
			break;
		case 2:
			v = c[0] & 0x3FF;
			v = v << 10 | (c[1] & 0x3FF);
			v += 0x10000;
			break;
	}

	return v;
}

uint16_t *sprint_utf16(uint16_t *str, uint32_t c)	// str must be able to hold 1 to 3 entries and will be null-terminated by this function
{
	int c_size;

	if (str==NULL)
		return NULL;

	c_size = codepoint_utf16_size(c);

	switch (c_size)
	{
		case 1:
			str[0] = c;
			if (c > 0)
				str[1] = '\0';
			break;

		case 2:
			c -= 0x10000;
			str[0] = 0xD800 + (c >> 10);
			str[1] = 0xDC00 + (c & 0x3FF);
			str[2] = '\0';
			break;

		default:
			str[0] = '\0';
	}

	return str;
}

size_t strlen_utf8_to_utf16(const uint8_t *str)
{
	size_t i, count;
	uint32_t c;

	for (i=0, count=0; ; i++)
	{
		if (str[i]==0)
			return count;

		c = utf8_to_unicode32(&str[i], &i);
		count += codepoint_utf16_size(c);
	}
}

size_t strlen_utf16_to_utf8(const uint16_t *str)
{
	size_t i, count;
	uint32_t c;

	for (i=0, count=0; ; i++)
	{
		if (str[i]==0)
			return count;

		c = utf16_to_unicode32(&str[i], &i);
		count += codepoint_utf8_size(c);
	}
}

uint16_t *utf8_to_utf16(const uint8_t *utf8, uint16_t *utf16)
{
	size_t i, j;
	uint32_t c;

	if (utf8==NULL)
		return NULL;

	if (utf16==NULL)
		utf16 = calloc(strlen_utf8_to_utf16(utf8) + 1, sizeof(uint16_t));

	for (i=0, j=0, c=1; c; i++)
	{
		c = utf8_to_unicode32(&utf8[i], &i);
		sprint_utf16(&utf16[j], c);
		j += codepoint_utf16_size(c);
	}

	return utf16;
}

uint8_t *utf16_to_utf8(const uint16_t *utf16, uint8_t *utf8)
{
	size_t i, j;
	uint32_t c;

	if (utf16==NULL)
		return NULL;

	if (utf8==NULL)
		utf8 = calloc(strlen_utf16_to_utf8(utf16) + 1, sizeof(uint8_t));

	for (i=0, j=0, c=1; c; i++)
	{
		c = utf16_to_unicode32(&utf16[i], &i);
		sprint_unicode(&utf8[j], c);
		j += codepoint_utf8_size(c);
	}

	return utf8;
}
