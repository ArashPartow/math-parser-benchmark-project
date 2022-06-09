char *vbufprintf(buffer_t *s, const char *format, va_list args)		// like vfprintf except for a buffer_t
{
	if (s==NULL)
		return NULL;

	vsprintf_realloc(&s->buf, &s->as, 1, format, args);

	s->len = strlen(s->buf);

	return s->buf;
}

char *bufprintf(buffer_t *s, const char *format, ...)			// like fprintf except for a buffer_t
{
	va_list args;
	int len1;

	if (s==NULL)
		return NULL;

	va_start(args, format);
	vbufprintf(s, format, args);
	va_end(args);

	return s->buf;
}

char *bufnprintf(buffer_t *s, size_t n, const char *format, ...) 	// like fprintf except for a buffer_t and only n chars like snprintf
{
	va_list args;
	int len1;

	if (s==NULL)
		return NULL;

	va_start(args, format);
	len1 = vsnprintf(NULL, 0, format, args);	// gets the printed length without actually printing
	va_end(args);
	len1 = MINN(n, len1);				// limit the length to add to n

	alloc_enough(&s->buf, s->len + len1 + 1, &s->as, sizeof(char), s->as==0 ? 1. : 1.5);

	va_start(args, format);
	vsnprintf(&s->buf[s->len], len1+1, format, args);
	va_end(args);

	s->len += len1;

	return s->buf;
}

char *bufwrite(buffer_t *s, uint8_t *ptr, size_t size)		// like fwrite except for a buffer_t
{
	if (s==NULL)
		return NULL;

	if (ptr)
	{
		alloc_enough(&s->buf, size + s->len+1, &s->as, sizeof(char), 1.5);
		memcpy(&s->buf[s->len], ptr, size);
		s->len += size;
	}

	return s->buf;
}

void buf_alloc_enough(buffer_t *s, size_t req_size)
{
	alloc_enough(&s->buf, req_size, &s->as, sizeof(char), 1.);
}

void free_buf(buffer_t *s)
{
	free(s->buf);
	memset(s, 0, sizeof(buffer_t));
}

void clear_buf(buffer_t *s)
{
	if (s==NULL)
		return ;

	s->len = 0;
	if (s->buf && s->as > 0)
		s->buf[0] = '\0';
}

buffer_t *append_buf(buffer_t *a, buffer_t *b)		// append b to a
{
	if (b==NULL)
		return a;

	if (b->len <= 0)
		return a;

	if (a==NULL)
		return a;

	alloc_enough(&a->buf, a->len + b->len,  &a->as, sizeof(char), 1.5);
	memcpy(&a->buf[a->len], b->buf, b->len);
	a->len += b->len;

	return a;
}

buffer_t buf_copy_part(buffer_t src, size_t start, size_t len)
{
	buffer_t dst={0};

	buf_alloc_enough(&dst, len+1);
	bufwrite(&dst, &src.buf[start], len);

	return dst;
}

void buf_remove_first_bytes(buffer_t *s, size_t n)
{
	if (s->buf==NULL || s->as <= 0 || n==0)
		return ;

	if (s->as < n)
	{
		memset(s->buf, 0, s->as);
		s->len = 0;
		return ;
	}

	memmove(s->buf, &s->buf[n], s->as - n);
	memset(&s->buf[s->as - n], 0, n);

	s->len = MAXN(s->len - n, 0);
}

int buf_tail(buffer_t *s, int n)	// keeps only the n last lines
{
	int linecount, start;

	if (s->buf==NULL || s->as <= 0)
		return 0;

	linecount = get_string_linecount(s->buf, s->len);			// count the lines
	start = string_find_start_nth_line(s->buf, s->len, linecount-n);	// find the start of the nth line from the bottom
	buf_remove_first_bytes(s, start);					// remove everything before it

	return MINN(n, linecount);
}

void bufprint_gmtime(buffer_t *s, time_t t)
{
	char datestamp[32];
	strftime(datestamp, 32, "%Y-%m-%d %H.%M.%S", gmtime(&t));

	bufprintf(s, "%s", datestamp);
}

buffer_t buf_load_raw_file(const char *path)
{
	buffer_t s={0};

	s.buf = load_raw_file(path, &s.len);
	s.as = s.len + 1;

	return s;
}

buffer_t buf_load_raw_file_dos_conv(const char *path)
{
	buffer_t s={0};

	s.buf = load_raw_file_dos_conv(path, &s.len);
	s.as = s.len + 1;

	return s;
}

int buf_save_raw_file(buffer_t *s, const char *path, const char *mode)
{
	return save_raw_file(path, mode, s->buf, s->len);
}
