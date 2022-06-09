char *sprint_large_num_simple(char *string, double number)		// prints a large number in a simple human-readable way into string (overwrites)
{
	static char static_string[32];
	const char *large_units[] = {"thousand", "million", "billion", "trillion"};
	const char *small_units[] = {"thousandths", "millionths", "billionths", "trillionths"};
	char *ptr=NULL;
	int logv, logv3, name_index, neg=0;
	double vm, vexp;
	/*
		logv	number		result
		-5	0.000012345	12.3 millionths
		-4	0.00012345	0.123 thousandths
		-3	0.0012345	1.23 thousandths	<-- general rule ends here
		-2	0.012345	0.012
		-1	0.12345		0.123
		 0	1.2345		1.23
		 1	12.345		12.3
		 2	123.45		123
		 3	1,234.5		1,234
		 4	12,345		12.3 thousand		<-- general rule starts there
		 5	123,456		123 thousand
		 6	1,234,567	1.23 million
		 7	12,345,678	12.3 million
	*/

	if (string==NULL)
		string = static_string;
	string[0] = 0;

	if (number < 0.)
	{
		neg = 1;
		number = -number;
	}

	logv = log10(number);			// 16 million -> 7
	if (number < 1.)
		logv--;

	if (logv < -2)
		logv3 = ((logv-1) / 3) * 3;	// shifts logv3 a notch to our preference
	else
		logv3 = (logv / 3) * 3;		// 16 million -> 7 -> 6

	vexp = pow(10., (double) logv3);	// 16 million -> 1,000,000.
	vm = number / vexp;			// 16 million -> 16
	if (neg)
		vm = -vm;
	name_index = abs(logv3) / 3 - 1;	// 16 million -> 1 ("million")

	switch (logv)
	{
		// special cases
		case -2:
		case -1:
			sprintf(string, "%.3f", vm);
			break;
		case 0:
			sprintf(string, "%.2f", vm);
			break;
		case 1:
			sprintf(string, "%.1f", vm);
			break;
		case 2:
			sprintf(string, "%.0f", vm);
			break;
		case 3:
			sprintf(string, "%.3f", vm);
			ptr = strstr(string, ".");
			if (ptr)
				ptr[0] = ',';
			break;

		// general rule
		default:
			if (name_index > 3)
				sprintf(string, "%.3g e%+03d", vm, logv3);
			else if (logv > 0)
				sprintf(string, "%.3g %s", vm, large_units[name_index]);
			else
				sprintf(string, "%.3g %s", vm, small_units[name_index]);
	}

	return string;
}

char *sprint_fractional_12(char *string, double v)
{
	int d, p1, p2, neg=0, n;

	if (v < 0.)
	{
		neg = 1;
		v = -v;
	}

	d = nearbyint(v * 144.);
	if (d==0)
		neg = 0;
	p2 = d % 12;
	d /= 12;
	p1 = d % 12;
	d /= 12;

	string[0] = 0;
	if (neg)
		sprintf(string, "-");

	if (p2)
		sprintf(&string[strlen(string)], "%d;%d;%d", d, p1, p2);
	else if (p1)
		sprintf(&string[strlen(string)], "%d;%d", d, p1);
	else
		sprintf(&string[strlen(string)], "%d", d);

	return string;
}

char *get_english_ordinal(int n)
{
	int i;
	static char *ord[] = {"th", "st", "nd", "rd"};

	n = abs(n);

	i = n % 10;
	if (i > 3 || n/10 % 10 == 1)		// _4 to _9 or 10 to 19 is th
		i = 0;

	return ord[i];
}

char *short_month_to_long_month(char *sm)
{
	static char *lm[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

	for (int i=0; i < 12; i++)
		if (strncmp(sm, lm[i], 3)==0)
			return lm[i];

	return NULL;
}

char *date_macro_to_nice_date(char *string, const char *d)
{
	int day, year;
	char month[16];

	string[0] = '\0';

	if (sscanf(d, "%s %d %d", month, &day, &year) == 3)
		sprintf(string, "%s %d%s, %d", short_month_to_long_month(month), day, get_english_ordinal(day), year);

	return string;
}

int get_date_macro_year(const char *d)
{
	int year=-1;

	sscanf(d, "%*s %*d %d", &year);

	return year;
}

char *sprint_compile_date_fullarg(char *string, const char *location, const char *d, const char *t)
{
	char nice_date[32];
	sprintf(string, "Compiled on %s at %s", date_macro_to_nice_date(nice_date, d), t);
	if (location)
		sprintf(&string[strlen(string)], " in %s", location);

	#ifdef __STDC_VERSION__
		sprintf(&string[strlen(string)], "\n\nC standard %ld\n", __STDC_VERSION__);
	#else
		sprintf(&string[strlen(string)], "\n\n");
	#endif
	#ifdef __clang_version__
		sprintf(&string[strlen(string)], "Clang %s\n", __clang_version__);
	#endif
	#ifdef __VERSION__
		sprintf(&string[strlen(string)], "GCC %s\n", __VERSION__);
	#endif
	#ifdef _MSC_FULL_VER
		sprintf(&string[strlen(string)], "Microsoft Visual Studio %d.%02d.%05d.%d\n", _MSC_VER/100, _MSC_VER%100, _MSC_FULL_VER%100000, _MSC_BUILD);
	#endif

	return string;
}

void fprint_indent(FILE *file, char *indent, int ind_lvl, char *string)
{
	int i, il, len = strlen(string);
	char c0, c1 = string[0];

	for (il=0; il<ind_lvl; il++)
		fprintf(file, "%s", indent);

	for (i=0; i < len; i++)
	{
		c0 = c1;
		if (i < len-1)
			c1 = string[i+1];
		else
			c1 = '\0';

		fprintf(file, "%c", c0);

		if (c0=='\n' && i < len-1 && c1 != '\n')
			for (il=0; il<ind_lvl; il++)
				fprintf(file, "%s", indent);
	}
}

char *sprint_localtime_now(char *string)
{
	time_t t;

	time(&t);
	strftime(string, 9, "%H.%M.%S", localtime(&t));

	return string;
}

void fprint_localtime_now(FILE *stream)
{
	char str[9];

	fprintf_rl(stream, "%s", sprint_localtime_now(str));
}

char *sprint_duration(char *string, double sec)
{
	if (sec < 60.)
		sprintf(string, "%.0f sec", sec);
	else if (sec < 180.)
		sprintf(string, "%.1f min", sec / 60.);
	else if (sec < 3600.)
		sprintf(string, "%.0f min", sec / 60.);
	else if (sec < 86400.)
		sprintf(string, "%.1f hours", sec / 3600.);
	else if (sec < 2.*86400.)
		sprintf(string, "1 day and %.1f hours", fmod(sec, 86400.) / 3600.);
	else if (sec < 90.*86400.)
		sprintf(string, "%0.f days and %.1f hours", floor(sec / 86400.), fmod(sec, 86400.) / 3600.);
	else
		sprintf(string, "%.2f years", sec / (365.25*86400.));

	return string;
}

char *sprint_timestamp(char *string, double t, int prec)
{
	char *p=string;
	int ti, ts, pm;

	if (t < 0.)
	{
		p[0] = '-';
		p = &p[1];
		t = -t;
	}

	pm = pow(10., prec);		// precision modulo
	ti = nearbyint(t * pm);		// time in integer format
	ts = ti / pm;			// time in integer seconds

	if (prec==0)
		sprintf(string, "%02d:%02d:%02d", ts/3600, (ts/60)%60, ts%60);
	else
		sprintf(string, "%02d:%02d:%02d.%0*d", ts/3600, (ts/60)%60, ts%60, prec, ti%pm);

	return string;
}

char *sprint_timestamp_short(char *string, double t, int prec)
{
	char *p=string;
	int ti, ts, pm;

	if (t < 0.)
	{
		p[0] = '-';
		p = &p[1];
		t = -t;
	}

	pm = pow(10., prec);		// precision modulo
	ti = nearbyint(t * pm);		// time in integer format
	ts = ti / pm;			// time in integer seconds

	if (ts >= 3600)
		sprintf(string, "%d:%02d:%02d", ts/3600, (ts/60)%60, ts%60);
	else if (ts >= 60)
		sprintf(string, "%d:%02d", ts/60, ts%60);
	else
		sprintf(string, "%d", ts);

	if (prec > 0)
		sprintf(&string[strlen(string)], ".%0*d", prec, ti%pm);

	return string;
}

char *text_to_multiline_c_literal(const char *text, const int linebreak_mode)	// linebreak_mode, 0: every line, 1: every paragraph, 2: no breaks
{
	const char line_start[] = "\t\t\"", line_end[] = "\",\n", line_sep[] = "\",";
	char *lit=NULL;
	uint8_t mb_char[5];
	int j, len=0, text_len = strlen(text), line_is_new=1, cp0=0, cp1=-1, cpp;
	size_t i, lit_as=0;

	for (i=0; i < text_len+1; i++)
	{
		if (line_is_new)
		{
			sprintf_realloc(&lit, &lit_as, 1, "%s", line_is_new==1 ? line_start : " \"");
			line_is_new = 0;
		}

		cpp = cp0;
		cp0 = cp1;
		cp1 = utf8_to_unicode32(&text[i], &i);

		if (cp0 != -1)
		{
			if (cp0 == '\n')		// if there's a line break
			{
				if (linebreak_mode==0 || (linebreak_mode==1 && cpp=='\n'))
				{
					sprintf_realloc(&lit, &lit_as, 1, "%s", line_end);
					line_is_new = 1;
				}
				else
				{
					sprintf_realloc(&lit, &lit_as, 1, "%s", line_sep);
					line_is_new = 2;
				}
			}
			else if (cp0 == '\\' || cp0 == '\"' || (cp0 == '?' && cp1 == '?'))	// if it's a printable character that simply must be escaped
				sprintf_realloc(&lit, &lit_as, 1, "\\%c", cp0);
			else if ((cp0 >= 32 && cp0 < 127) || cp0 == '\t')			// if it's a one-byte character
				sprintf_realloc(&lit, &lit_as, 1, "%c", cp0);
			else									// if it's a multi-byte character or control code that must be escaped into an octal sequence
			{
				sprint_unicode(mb_char, cp0);

				for (j=0; j < strlen(mb_char); j++)
					sprintf_realloc(&lit, &lit_as, 1, "\\%03o", mb_char[j]);
			}
		}
	}

	return lit;
}

void fprint_escaped_byte(FILE *fout, unsigned char c0, unsigned char c1)
{
	if (c1 == '\n')
		fprintf(fout, "\\n");
	else if (c1 == '\t')
		fprintf(fout, "\\t");
	else if (c1 == '\\' || c1 == '\"' || (c0 == '?' && c1 == '?'))
		fprintf(fout, "\\%c", c1);
	else if (c1 >= 32 && c1 < 127)
		fprintf(fout, "%c", c1);
	else
		fprintf(fout, "\\%03o", c1);
}

void convert_file_to_header_const_string(const char *in_path)
{
	int ret, i;
	FILE *fin, *fout;
	uint8_t out_path[PATH_MAX*4], c0=0, c1;

	fin = fopen_utf8(in_path, "rb");
	sprintf(out_path, "%s.h", in_path);	// the output path is in_path + '.h'
	fout = fopen_utf8(out_path, "wb");

	fprintf(fout, "\"");

	ret = 1;
	i = 0;
	while (ret==1)
	{
		ret = fread(&c1, 1, 1, fin);

		if (ret)
		{
			fprint_escaped_byte(fout, c0, c1);

			if ((i % 2000) == 0 && i)		// this cuts up the string to please compilers
				fprintf(fout, "\"\n\"");
			i++;
		}

		c0 = c1;
	}

	fprintf(fout, "\";");
	fclose (fin);
	fclose (fout);
}
