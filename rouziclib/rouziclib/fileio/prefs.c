pref_file_t pref_def={0};
rl_mutex_t pref_save_mutex={0};

void pref_file_load(pref_file_t *pf)
{
	free_2d(pf->lines, 1);

	// Load the file as an array
	if (check_file_is_readable(pf->path))
		pf->lines = arrayise_text(load_raw_file_dos_conv(pf->path, NULL), &pf->linecount);
	else												// if the file doesn't exist
		pf->lines = arrayise_text(make_string_copy(""), &pf->linecount);			// create an empty array
}

int pref_file_save(pref_file_t *pf)
{
	return save_string_array_to_file(pf->path, "wb", pf->lines, pf->linecount);
}

int pref_file_save_thread(pref_file_t *pf)
{
	int ret;

	rl_mutex_lock(&pref_save_mutex);

	ret = pref_file_save(pf);
	free_pref_file(pf);
	free(pf);

	rl_mutex_unlock(&pref_save_mutex);

	return ret;
}

void pref_file_save_thread_launch(pref_file_t *pf)
{
	static rl_thread_t thread_handle=NULL;
	static int init=1;
	pref_file_t *pf_copy;

	pf_copy = calloc(1, sizeof(pref_file_t));

	// Copy the data
	pf_copy->linecount = pf->linecount;
	pf_copy->lines = make_string_array_copy(pf->lines, pf->linecount);
	pf_copy->path = make_string_copy(pf->path);

	// Init the mutex
	if (init)
	{
		init = 0;
		rl_mutex_init(&pref_save_mutex);
	}

	// Wait for the thread to end if already running to avoid conflicts
	#ifndef __EMSCRIPTEN__
	rl_thread_join_and_null(&thread_handle);
	#endif

	// Launch the thread
	rl_thread_create(&thread_handle, pref_file_save_thread, pf_copy);
	//rl_thread_create_detached(pref_file_save_thread, pf_copy);
}

void free_pref_file(pref_file_t *pf)
{
	free(pf->path);
	free_2d(pf->lines, 1);

	memset(pf, 0, sizeof(pref_file_t));
}

pref_file_t pref_set_file_by_path(const char *path)
{
	pref_file_t pf={0};

	pf.path = make_string_copy(path);
	pref_file_load(&pf);

	return pf;
}

pref_file_t pref_set_file_by_appdata_path(const char *folder, const char *filename)
{
	pref_file_t pf={0};

	pf.path = make_appdata_path(folder, filename, 1);
	pref_file_load(&pf);

	return pf;
}

int pref_find_loc_depth(pref_file_t *pf, const char *loc, int depth, int start, int end)
{
	int i, ret, start_next=-1;
	char key[64];

	// Find the key at the given depth
	memset(key, '\t', depth);					// indent the key
	if (string_get_field(loc, PREF_LOC_DELIM, depth, &key[depth]) == 0)
		return -1;						// if loc isn't that deep

	// Find where the key is declared (start)
	for (i=start; i < end; i++)
		if (strncmp(pf->lines[i], key, strlen(key))==0)
		{
			start_next = i;
			break;
		}

	if (start_next < 0)	// if the key wasn't found
	{
		// Add a blank line if this is a new 0 depth section
		if (depth==0 && pf->linecount > 0)
		{
			start_next = end;
			end = end + 1;
			pf->lines = string_array_insert_line(pf->lines, &pf->linecount, "", start_next);
		}

		start_next = end;
		end = end + 1;

		// Insert the key
		pf->lines = string_array_insert_line(pf->lines, &pf->linecount, key, start_next);
	}
	else
	{
		// Find the end of the current key
		for (i=start_next+1; i < end; i++)
		{
			if (find_line_indentation_depth(pf->lines[i]) <= depth)
			{
				end = i;
				break ;
			}
		}
	}

	// Find the next key at the next depth
	ret = pref_find_loc_depth(pf, loc, depth+1, start_next+1, end);

	// Determine the position of loc
	if (ret == -1)			// if this is the final key
		return start_next;

	return ret;
}

int pref_find_loc(pref_file_t *pf, const char *loc)
{
	if (pf->path==NULL || pf->lines==NULL)
	{
		fprintf_rl(stderr, "Pref file not initialised in pref_find_loc()\n");
		return -2;
	}

	return pref_find_loc_depth(pf, loc, 0, 0, pf->linecount);
}

// v = pref_get_double(&pref_def, "Audio output:Sample rate", 44100, "Hz");
// Audio output
// 	Sample rate: 44100 Hz
double pref_handle_double(pref_file_t *pf, char *loc, double value, const char *suffix, int mode_set)
{
	int i, line_pos, depth;
	char key[64], *new_line;
	double read_value=NAN;

	// Find the line for loc
	line_pos = pref_find_loc(pf, loc);
	if (line_pos < 0)
		return NAN;

	// Make key string
	depth = string_count_fields(loc, PREF_LOC_DELIM) - 1;			// find the indentation depth
	memset(key, '\t', depth);						// indent the key
	if (string_get_field(loc, PREF_LOC_DELIM, depth, &key[depth]) == 0)	// get the key in the last field
		return NAN;

	// Try to read the value in the line
	const char *p = strstr_after(pf->lines[line_pos], key);			// find what's after the key in the key's line
	if (p)
		if (sscanf(p, ": %lg", &read_value) == 1)			// if the value is found
			if (read_value == value)				// return if it's the same as the one written
				return read_value;

	// Remake the line if mode is get mode and the value is new or set mode and the value must be set anyway
	if (mode_set || isnan(read_value))
	{
		// Recreate the line with the provided value
		new_line = sprintf_alloc("%s: %g%s", key, value, suffix ? suffix : "");
		pf->lines = string_array_replace_line(pf->lines, &pf->linecount, new_line, line_pos);
		free(new_line);
		read_value = value;

		pref_file_save_thread_launch(pf);
	}

	return read_value;
}

double pref_get_double(pref_file_t *pf, char *loc, double def_value, const char *suffix)
{
	return pref_handle_double(pf, loc, def_value, suffix, 0);
}

void pref_set_double(pref_file_t *pf, char *loc, double new_value, const char *suffix)
{
	pref_handle_double(pf, loc, new_value, suffix, 1);
}

const char *pref_handle_string(pref_file_t *pf, char *loc, char *string_prefix, const char *string, int mode_set)
{
	int i, n=0, line_pos, depth;
	char key[64], *new_line;
	const char *read_string=NULL;

	// Find the line for loc
	line_pos = pref_find_loc(pf, loc);
	if (line_pos < 0)
		return NULL;

	// Make key string
	depth = string_count_fields(loc, PREF_LOC_DELIM) - 1;			// find the indentation depth
	memset(key, '\t', depth);						// indent the key
	if (string_get_field(loc, PREF_LOC_DELIM, depth, &key[depth]) == 0)	// get the key in the last field
		return NULL;

	// Try to read the string in the line
	const char *p = strstr_after(pf->lines[line_pos], key);			// find what's after the key in the key's line
	if (p)
	{
		if (strncmp(p, string_prefix, strlen(string_prefix))==0)	// if the prefix matches
		{
			read_string = &p[strlen(string_prefix)];

			if (string==NULL)					// if there's no default string set just return the read string
				return read_string;
			else if (strcmp(read_string, string)==0)		// in set mode if it's the same string as the one written
				return read_string;
		}
	}

	// Remake the line if mode is get mode and the value is new or set mode and the value must be set anyway
	if (mode_set || read_string==NULL)
	{
		// Recreate the line with the provided string
		new_line = sprintf_alloc("%s%s%s", key, string_prefix, string);
		n = strlen(key) + strlen(string_prefix);
		pf->lines = string_array_replace_line(pf->lines, &pf->linecount, new_line, line_pos);
		free(new_line);
		read_string = &pf->lines[line_pos][n];

		pref_file_save_thread_launch(pf);
	}

	return read_string;		// pointer to the written string in the updated line
}

const char *pref_get_string(pref_file_t *pf, char *loc, const char *def_string)
{
	return pref_handle_string(pf, loc, ": ", def_string, 0);
}

void pref_set_string(pref_file_t *pf, char *loc, const char *new_string)
{
	pref_handle_string(pf, loc, ": ", new_string, 1);
}

int pref_get_onoff(pref_file_t *pf, char *loc, int def_state)
{
	const char *p;

	p = pref_handle_string(pf, loc, ": ", def_state ? "on" : "off", 0);
	if (p == NULL)
		return -1;

	if (strcmp(p, "on")==0)		return 1;
	if (strcmp(p, "off")==0)	return 0;

	return -1;
}

void pref_set_onoff(pref_file_t *pf, char *loc, int new_state)
{
	pref_handle_string(pf, loc, ": ", new_state ? "on" : "off", 1);
}

xy_t pref_handle_2val(pref_file_t *pf, char *loc, double v1, char *v_delim, double v2, char *suffix, int mode_set)
{
	char *string;
	const char *p;
	xy_t v = xy(NAN,NAN);

	// Create string
	string = sprintf_alloc("%g%s%g%s", v1, v_delim, v2, suffix ? suffix : "");

	p = pref_handle_string(pf, loc, ": ", string, mode_set);
	free(string);
	if (p == NULL)
		return v;

	if (mode_set==0)
	{
		char *field = calloc(strlen(p)+1, sizeof(char));

		if (string_get_field(p, v_delim, 0, field))
			v.x = strtod(field, NULL);

		if (string_get_field(p, v_delim, 1, field))
			v.y = strtod(field, NULL);

		free(field);
	}

	return v;
}

xy_t pref_get_2val(pref_file_t *pf, char *loc, double v1, char *v_delim, double v2, char *suffix)
{
	return pref_handle_2val(pf, loc, v1, v_delim, v2, suffix, 0);
}

void pref_set_2val(pref_file_t *pf, char *loc, double v1, char *v_delim, double v2, char *suffix)
{
	pref_handle_2val(pf, loc, v1, v_delim, v2, suffix, 1);
}
