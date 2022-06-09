void fileball_add_file(buffer_t *sout, const char *path, const char *name, int abs_path_len)
{
	uint8_t *data;
	size_t i, fsize;
	char fullpath[PATH_MAX*4], savepath[PATH_MAX*4];

	append_name_to_path(fullpath, path, name);
	data = load_raw_file(fullpath, &fsize);

	// Saving the relative path
	strcpy(savepath, &fullpath[abs_path_len]);
	replace_char(savepath, DIR_CHAR, '/');
	bufprintf(sout, "\n%s\n%d\n", savepath, fsize);

	// Save data
	bufwrite(sout, data, fsize);

	free(data);
}

void fileball_add_subfiles(buffer_t *sout, fs_dir_t *dir, int abs_path_len)
{
	int i;

	// Go through the subdirs recursively
	for (i=0; i < dir->subdir_count; i++)
		if (strcmp(dir->subdir[i].name, ".") && strcmp(dir->subdir[i].name, ".."))
			fileball_add_subfiles(sout, &dir->subdir[i], abs_path_len);

	for (i=0; i < dir->subfile_count; i++)
		fileball_add_file(sout, dir->subfile[i].parent->path, dir->subfile[i].name, abs_path_len);
}

void fileball_add_whole_path(buffer_t *sout, const char *path, const int depth)
{
	fs_dir_t dir={0};
	int len;

	len = strlen(path);
	if (len==0)
		return ;

	if (path[len-1] != DIR_CHAR)
		len++;

	load_dir_depth(path, &dir, depth);
	fileball_add_subfiles(sout, &dir, len);
}

buffer_t fileball_make_uncompressed(char **paths, int path_count, const int depth)
{
	int i;
	buffer_t sout={0};

	bufprintf(&sout, "fileball 1.0");

	for (i=0; i < path_count; i++)
		fileball_add_whole_path(&sout, paths[i], depth);

	return sout;
}

void fileball_make_uncompressed_file(char *out_path, char **paths, int path_count, const int depth)
{
	buffer_t sout = fileball_make_uncompressed(paths, path_count, depth);
	save_raw_file(out_path, "wb", sout.buf, sout.len);
	free(sout.buf);
}

buffer_t fileball_make_z(char **paths, int path_count, const int depth)
{
	buffer_t bz={0}, sunc;
       
	sunc = fileball_make_uncompressed(paths, path_count, depth);
	bz = gz_compress_to_buffer(sunc.buf, sunc.len, Z_BEST_COMPRESSION);
	free(sunc.buf);

	return bz;
}

void fileball_make_z_file(char *out_path, char **paths, int path_count, const int depth)
{
	buffer_t sout;

	sout = fileball_make_z(paths, path_count, depth);

	save_raw_file(out_path, "wb", sout.buf, sout.len);
	free(sout.buf);
}

void fileball_make_header_file(char *out_path, char **paths, int path_count, const int depth)
{
	int i;
	buffer_t sz;
	FILE *fout;

	sz = fileball_make_z(paths, path_count, depth);

	create_dirs_for_file(out_path);
	fout = fopen_utf8(out_path, "wb");
	if (fout==NULL)
		return ;

	fprintf(fout, "\"");

	for (i=0; i < sz.len; i++)
	{
		fprint_escaped_byte(fout, i==0 ? 0 : sz.buf[i-1], sz.buf[i]);

		if ((i % 2000) == 0 && i)		// this cuts up the string to please compilers
			fprintf(fout, "\"\n\"");
	}

	free(sz.buf);
	fprintf(fout, "\";");
	fclose (fout);
}

void fileball_extract_mem_to_path(buffer_t *ball, const char *extract_path)
{
	int n=0, filesize;
	char *p, *pend, abs_path[PATH_MAX*4], rel_path[PATH_MAX*4];
	double version=0.;

	p = ball->buf;
	pend = &ball->buf[ball->len];

	sscanf(p, "fileball %lg%n", &version, &n);
	p = &p[n];
	if (n==0)
		return ;
	n = 0;
	while (p < pend)
	{
		// read the relative path to extract to
		sscanf(p, "\n%[^\n]\n%n", rel_path, &n);
		p = &p[n];
		if (n==0)
			break ;
		n = 0;

		// read the size of the file to write
		filesize = 0;
		sscanf(p, "%d\n%n", &filesize, &n);
		p = &p[n];
		if (n==0)
			break ;
		n = 0;

		// save the file
		replace_char(rel_path, '/', DIR_CHAR);
		append_name_to_path(abs_path, extract_path, rel_path);
		create_dirs_for_file(abs_path);
		save_raw_file(abs_path, "wb", p, filesize);
		p = &p[filesize];
	}
}

void fileball_extract_z_mem_to_path(buffer_t *zball, const char *extract_path)
{
	buffer_t ball={0};

	gz_decompress(zball->buf, zball->len, &ball.buf, &ball.len);	// decompress zball into ball
	fileball_extract_mem_to_path(&ball, extract_path);		// extract files to path
	free(ball.buf);
}

void fileball_extract_z_file_to_path(const char *in_path, const char *extract_path)
{
	buffer_t zball={0};

	zball.buf = load_raw_file(in_path, &zball.len);
	fileball_extract_z_mem_to_path(&zball, extract_path);
	free(zball.buf);
}

fileball_t fileball_extract_z_mem_to_struct(buffer_t *zball)
{
	buffer_t ball={0};
	fileball_t s={0};
	size_t s_as = 0;

	gz_decompress(zball->buf, zball->len, &ball.buf, &ball.len);	// decompress zball into ball
	s.original_array = ball.buf;

	int n=0;
	char *p, *pend;
	double version=0.;

	p = ball.buf;
	pend = &ball.buf[ball.len];

	sscanf(p, "fileball %lg%n", &version, &n);
	p = &p[n];
	if (n==0)
		return s;
	n = 0;
	while (p < pend)
	{
		// read the relative path to extract to
		sscanf(p, "\n%*[^\n]%n", &n);
		if (n)
		{
			alloc_enough(&s.file, s.file_count+=1, &s_as, sizeof(fileball_subfile_t), 2.);
			s.file[s.file_count-1].path = &p[1];
			p[n] = '\0';	// makes the .path suitable
			p = &p[n+1];
		}
		else
			break ;
		n = 0;

		// read the size of the subfile
		sscanf(p, "%zu\n%n", &s.file[s.file_count-1].len, &n);
		p = &p[n];
		if (n==0)
			break ;
		n = 0;

		// file data pointer
		s.file[s.file_count-1].data = p;
		p = &p[s.file[s.file_count-1].len];
	}

	return s;
}

fileball_subfile_t *fileball_find_subfile(fileball_t *s, const char *name)
{
	for (int i=0; i < s->file_count; i++)
		if (strcmp(name, s->file[i].path)==0)
			return &s->file[i];

	return NULL;
}

void free_fileball_struct(fileball_t *s)
{
	free(s->file);
	free(s->original_array);

	memset(s, 0, sizeof(fileball_t));
}
