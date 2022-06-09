const char *skip_string(const char *string, const char *skipstring)		// skipstring must be terminated by a %n
{
	int n=0;
	sscanf(string, skipstring, &n);
	return &string[n];
}

const char *skip_whitespace(const char *string)
{
	return skip_string(string, " %n");
}

const char *skip_line(const char *string)
{
	return skip_string(string, "%*[^\n]\n%n");
}

int string_count_fields(const char *string, const char *delim)
{
	int count = 0;
	const char *p = string;

	// Count fields
	while (p)
	{
		count++;
		p = strstr(p, delim);
		if (p)
			p = &p[1];
	}

	return count;
}

int string_get_field(const char *string, const char *delim, int n, char *field)	// copies the Nth field (0 indexed) of string into field
{
	int i;
	size_t delim_len = strlen(delim);
	const char *end;

	// If n is negative it means we count from the end, -1 is last, -2 the one before etc...
	if (n < 0)
		n = string_count_fields(string, delim) + n;	// -x becomes count-x

	// Find field start
	for (i=0; i < n; i++)
	{
		string = strstr(string, delim);			// look for the next delimiter

		if (string==NULL)				// if the next delimiter needed isn't found
			return 0;				// 0 means failure to find the field

		string += delim_len;				// set string to right after the delimiter that indicates the start
	}

	// Find field end
	end = strstr(string, delim);				// look for the next delimiter that marks the end of the field

	// Copy field
	if (end==NULL)						// if it was the last field
		strcpy(field, string);				// copy all that is left
	else							// otherwise
	{
		snprintf(field, 1+end-string, "%s", string);	// only copy what's in the field
		field[end-string] = 0;
	}

	return 1;
}

const char *string_parse_fractional_12(const char *string, double *v)
{
	int i, n=0, ret=1, count=0, neg=0;
	double divisor=1., digit;
	const char *p = string;

	*v = 0.;

	p = skip_whitespace(p);

	// Detect minus sign to first process the number as positive
	if (p[0] == '-')
	{
		neg = 1;
		p++;
	}

	// Loop through the semicolon-separated numbers
	for (i=0; i < 20 && ret==1; i++)
	{
		n=0;
		ret = sscanf(p, "%lf%n", &digit, &n);
		p = &p[n];
		if (ret==1)
		{
			count++;
			*v += digit / divisor;
			divisor *= 12.;
		}

		// Skip next semicolon
		n=0;
		sscanf(p, ";%n", &n);
		p = &p[n];

		// Detect whitespace so that the next sscanf avoids reading the numbers after the whitespace
		if (p[0]==' ' || p[0]=='\t')
			ret = 0;
	}

	if (count==0)
		return string;

	if (neg)
		*v = -*v;

	return p;
}

double doztof(const char *string)
{
	double v;

	string_parse_fractional_12(string, &v);

	return v;
}

xy_t doztof_xy(const char *str_x, const char *str_y)
{
	return xy(doztof(str_x), doztof(str_y));
}

char *remove_after_char(char *string, const char c)
{
	char *p;

	p = strrchr(string, c);
	if (p)
		p[1] = '\0';

	return string;
}

int strlen_until_after_char(const char *string, const char c)	// length of a string until last occurence of c (included)
{
	const char *p;

	p = strrchr(string, c);
	if (p)
		return p-string + 1;
	else
		return 0;
}

char *remove_after_char_copy(const char *string, const char c)	// makes a cut copy of a string
{
	int len;
	char *cut;

	len = strlen_until_after_char(string, c);
	if (len==0)
		return NULL;

	cut = calloc(len+1, sizeof(char));

	strncpy(cut, string, len);

	return cut;
}

size_t get_string_linecount(const char *text, size_t len)
{
	size_t i, linecount=0;

	if (text==NULL)
		return linecount;

	if (text[0]=='\0')
		return linecount;

	if (len <= 0)
		len = strlen(text);

	linecount = 1;
	for (i=0; i < len-1; i++)
		if (text[i] == '\n')
			linecount++;

	return linecount;
}

int string_find_start_nth_line(const char *text, int len, int n)	// n is the index of the line to find, the char index is returned
{
	int i, il;

	if (text==NULL)
		return -1;

	if (text[0]=='\0')
		return -1;

	if (n <= 0)
		return 0;

	if (len <= 0)
		len = strlen(text);

	il = 0;
	for (i=0; i < len-1; i++)
	{
		if (n == il)
			return i;

		if (text[i] == '\n')
			il++;
	}

	return i;
}

char **arrayise_text(char *text, int *linecount)	// turns line breaks into null chars, makes an array of pointers to the beginning of each lines
{
	size_t i, ia, len;
	char **array;

	*linecount = 0;
	if (text==NULL)
		return NULL;

	len = strlen(text);
	if (len==0)		// if the text is empty
	{
		array = calloc(1, sizeof(char *));
		array[0] = text;

		return array;
	}

	*linecount = get_string_linecount(text, len);

	array = calloc(*linecount, sizeof(char *));
	array[0] = text;

	// Set the pointers to the start of each line and replace all line breaks with \0
	for (ia=1, i=0; i < len-1; i++)
		if (text[i] == '\n')
		{
			array[ia] = &text[i+1];
			text[i] = '\0';
			ia++;
		}

	if (text[len-1] == '\n')
		text[len-1] = '\0';

	return array;
}

const char *strstr_i(const char *fullstr, const char *substr)		// case insensitive substring search
{
	char *fullstr_low, *substr_low;
	const char *p, *ret = NULL;

	if (fullstr==NULL || substr==NULL)
		return NULL;

	fullstr_low = string_tolower(make_string_copy(fullstr));	// make lowercase copy
	substr_low = string_tolower(make_string_copy(substr));

	p = strstr(fullstr_low, substr_low);
	if (p)
		ret = fullstr + (p - fullstr_low);

	free(fullstr_low);
	free(substr_low);

	return ret;
}

const char *strstr_after(const char *fullstr, const char *substr)		// points to after the substring
{
	const char *p;

	if (fullstr==NULL || substr==NULL)
		return NULL;

	p = strstr(fullstr, substr);
	if (p)
		return &p[strlen(substr)];

	return NULL;
}

void *memmem_rl(const uint8_t *l, size_t l_len, const uint8_t *s, size_t s_len)	// like strstr but binary, like memmem but availability is lacking on Windows and Emscripten
{
	int i;

	if (l==NULL || s==NULL || l_len<=0 || s_len<=0 || l_len < s_len)
		return NULL;

	if (s_len == 1)		// special case where s_len is 1
		return memchr(l, s[0], l_len);

	for (i=0; i <= l_len - s_len; i++)
		if (l[i] == s[0])
			if (memcmp(&l[i], s, s_len) == 0)
				return (void *) &l[i];

	return NULL;
}

int compare_varlen_word_to_fixlen_word(const char *var, size_t varlen, const char *fix)		// returns 1 if the words are equal
{
	size_t fixlen = strlen(fix);

	if (fixlen != varlen)
		return 0;

	return strncmp(var, fix, varlen)==0;
}

int strcmp_len2(const char *str1, const char *str2)
{
	return strncmp(str1, str2, strlen(str2));
}

const char *find_pattern_in_string(const char *str, const char *pat)	// looks for matches from the end
{
	int i, ip, str_len, pat_len, match;

	if (str==NULL || pat==NULL)
		return NULL;

	str_len = strlen(str);
	pat_len = strlen(pat);

	for (i = str_len-pat_len; i >= 0; i--)
	{
		match = 1;
		for (ip=0; ip < pat_len && match; ip++)
		{
			switch (pat[ip])
			{
				case '\377':			// 0xFF, matches any char
					break;

				case '\376':			// 0xFE, matches any digit
					if (str[i+ip] < '0' || str[i+ip] > '9')
						match = 0;
					break;

				// '\365' and up are available

				default:			// 0x00 to 0xF4, match a valid UTF-8 byte
					if (str[i+ip] != pat[ip])
						match = 0;
					break;
			}
		}

		if (match)
			return &str[i];
	}

	return NULL;
}

const char *find_date_time_in_string(const char *str)
{
	// pattern matches YYYY-MM-DD<?>hh.mm.ss
	return find_pattern_in_string(str, "\376\376\376\376-\376\376-\376\376\377\376\376.\376\376.\376\376");
}

double parse_timestamp(const char *ts)
{
	double t = NAN, hh=0., mm=0., ss=0.;
	const char *p;

	if (p = find_pattern_in_string(ts, "\376\376:\376\376:\376\376"))	// see if it contains hours (HH)
		sscanf(p, "%lg:%lg:%lg", &hh, &mm, &ss);
	else if (p = find_pattern_in_string(ts, "\376:\376\376:\376\376"))	// see if it contains hours (H)
		sscanf(p, "%lg:%lg:%lg", &hh, &mm, &ss);
	else if (p = find_pattern_in_string(ts, "\376\376:\376\376"))		// see if it contains minutes (MM)
		sscanf(p, "%lg:%lg", &mm, &ss);
	else if (p = find_pattern_in_string(ts, "\376:\376\376"))		// see if it contains minutes (M)
		sscanf(p, "%lg:%lg", &mm, &ss);
	else									// it contains only seconds
		sscanf(ts, "%lg", &ss);

	return (hh*60. + mm)*60. + ss;
}

int find_line_indentation_depth(const char *line)	// returns how many \t the line starts with
{
	int depth = 0;

	for (int i=0; line[i]; i++)
		if (line[i] == '\t')
			depth++;
		else
			return depth;

	return depth;
}

void parse_xy_array_file(char *path, xy_t **xy_array, size_t *xy_array_size)
{
	int i, lineoff=0, linecount, xfield=0, yfield=1;
	char delim[8]={'\t'}, field[64];
	char **array = arrayise_text(load_raw_file_dos_conv(path, NULL), &linecount);

	if (sscanf(array[0], "separator=\"%[^\"]\" x=%d y=%d", delim, &xfield, &yfield) > 0)
		lineoff = 1;

	free(*xy_array);
	*xy_array = calloc(*xy_array_size=linecount-lineoff, sizeof(xy_t));

	for (i=0; i < *xy_array_size; i++)
	{
		if (string_get_field(array[i+lineoff], delim, xfield, field))
			(*xy_array)[i].x = atof(field);

		if (string_get_field(array[i+lineoff], delim, yfield, field))
			(*xy_array)[i].y = atof(field);
	}

	free_2d(array, 1);
}

char *xml_copy_field_string(const char *parent_start, const char *parent_end, const char *tag_start, const char *tag_end)
{
	const char *p, *p_end;
	char *field=NULL;

	// Find tag start
	p = strstr_after(parent_start, tag_start);

	if (p && p < parent_end)		// if it's found inside the parent
	{
		// Find the tag end
		p_end = strstr(p, tag_end);

		if (p_end==NULL || p_end > parent_end)
			return NULL;

		// Copy string
		field = make_string_copy_between_ptrs(p, p_end);
	}

	return field;
}

double xml_copy_field_number(const char *parent_start, const char *parent_end, const char *tag_start)
{
	const char *p;
	double v = 0.;

	// Find tag start
	p = strstr_after(parent_start, tag_start);

	if (p && p < parent_end)		// if it's found inside the parent
		v = atof(p);

	return v;
}

double parse_music_note(const char *string)	// parse a note string into a number of semitones from C0
{
	int i, ret, octave=0;
	double cents=0.;
	char note[32], letter[4];
	const char *note_name[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	// string looks like "C#4+05.231" or "F-1-42" or "C1"
	if (sscanf(string, "%31s", note) == 0)
		return NAN;

	ret = sscanf(note, "%2[A-G#]%d%lg", letter, &octave, &cents);
	if (ret < 2)
		return NAN;

	for (i=0; i < 12; i++)
		if (strcmp(letter, note_name[i])==0)
			return (double) (octave*12 + i) + cents*0.01;

	return NAN;
}
