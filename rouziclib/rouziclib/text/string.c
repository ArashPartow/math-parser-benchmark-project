char *make_string_copy(const char *orig)
{
	char *copy;

	if (orig==NULL)
		return NULL;

	copy = calloc(strlen(orig)+1, sizeof(char));
	strcpy(copy, orig);

	return copy;
}

char *make_string_copy_len(const char *orig, size_t len)
{
	char *copy;

	if (orig==NULL)
		return NULL;

	len = MINN(len, strlen(orig));

	copy = calloc(len+1, sizeof(char));
	strncpy(copy, orig, len);

	return copy;
}

char *make_string_copy_between_ptrs(const char *start, const char *end)		// copies a string between two points. The char that end points to is excluded
{
	return make_string_copy_len(start, end-start);
}

char **make_string_array_copy(const char **orig, const size_t count)
{
	size_t i;
	char **copy;

	copy = calloc(count, sizeof(char *));
	if (copy==NULL)
		return NULL;

	for (i=0; i < count; i++)
		copy[i] = make_string_copy(orig[i]);

	return copy;
}

void strcpy_then_free(char *dest, char *src)
{
	strcpy(dest, src);
	free(src);
}

char *replace_char(char *str, char find, char replace)	// ASCII replacement of one char with another
{
	char *current_pos = strchr(str,find);

	while (current_pos)
	{
		*current_pos = replace;
		current_pos = strchr(current_pos+1, find);
	}

	return str;
}

char *string_tolower(char *str)
{
	char *p = str;

	if (str==NULL)
		return NULL;

	while (*p)
	{
		*p = tolower(*p);
		p++;
	}

	return str;
}

char *vsprintf_realloc(char **string, size_t *alloc_count, const int append, const char *format, va_list args)
{
	int len0=0, len1;
	size_t zero=0;
	char *p=NULL;
	va_list args_copy;

	if (string==NULL)				// if there's no string then we create one
		string = &p;				// so that ultimately it's p that will be returned

	if (alloc_count==NULL)				// if alloc_count isn't provided
		alloc_count = &zero;			// use 0 which will realloc string to an adequate size

	va_copy(args_copy, args);
	len1 = vsnprintf(NULL, 0, format, args_copy);	// gets the printed length without actually printing
	va_end(args_copy);

	if (string)
		if (append && *string)
			len0 = strlen(*string);

	alloc_enough(string, len0+len1+1, alloc_count, sizeof(char), (*alloc_count)==0 ? 1. : 1.5);

	vsnprintf(&(*string)[len0], *alloc_count - len0, format, args);

	return *string;
}

char *sprintf_realloc(char **string, size_t *alloc_count, const int append, const char *format, ...)	// like sprintf but expands the string alloc if needed
{
	va_list args;
	char *p=NULL;

	if (string==NULL)				// if there's no string then we create one
		string = &p;

	va_start(args, format);
	vsprintf_realloc(string, alloc_count, append, format, args);
	va_end(args);

	return *string;
}

char *vsprintf_alloc(const char *format, va_list args)	// like vsprintf but allocates a new string
{
	int len;
	char *str;
	va_list args_copy;

	va_copy(args_copy, args);
	len = vsnprintf(NULL, 0, format, args_copy);	// gets the printed length without actually printing
	va_end(args_copy);

	str = calloc(len+1, sizeof(char));
	vsnprintf(str, len+1, format, args);

	return str;
}

char *sprintf_ret(char *str, const char *format, ...)	// like sprintf but returns the string
{
	va_list args;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);

	return str;
}

char **string_array_insert_lines(char **array, int *linecount, char **ins, int ins_count, int ins_pos)	// destroys array and makes a new one with lines inserted
{
	int i;
	buffer_t s={0};

	ins_pos = MINN(ins_pos, *linecount);

	// Add the first part of the array line by line to s
	for (i=0; i < ins_pos; i++)
		bufprintf(&s, "%s\n", array[i]);

	// Add the lines to insert to s
	for (i=0; i < ins_count; i++)
		bufprintf(&s, "%s\n", ins[i]);

	// Add the rest of the array to s
	for (i=ins_pos; i < *linecount; i++)
		bufprintf(&s, "%s\n", array[i]);

	free_2d(array, 1);

	return arrayise_text(s.buf, linecount);
}

char **string_array_insert_line(char **array, int *linecount, char *ins, int ins_pos)
{
	return string_array_insert_lines(array, linecount, &ins, 1, ins_pos);
}

char **string_array_replace_line(char **array, int *linecount, char *repl, int repl_pos)	// destroys array and makes a new one with line replaced
{
	int i;
	buffer_t s={0};

	// Copy every line except switch the line to replace
	for (i=0; i < *linecount; i++)
		bufprintf(&s, "%s\n", (i==repl_pos) ? repl : array[i]);

	free_2d(array, 1);

	return arrayise_text(s.buf, linecount);
}
