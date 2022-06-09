#ifdef _WIN32
	#define fseek(stream, offset, origin)	_fseeki64(stream, offset, origin)
	#define ftell(stream)			_ftelli64(stream)
#else
#ifndef __APPLE__
	#ifndef __EMSCRIPTEN__
		#define fseek(stream, offset, origin)	fseeko64(stream, offset, origin)
		#define ftell(stream)			ftello64(stream)
	#else
		#define fseek(stream, offset, origin)	fseeko(stream, offset, origin)
		#define ftell(stream)			ftello(stream)
	#endif
#endif
#endif

#define H_FOPEN_UTF8
extern FILE *fopen_utf8(const char *path, const char *mode);
extern FILE *fopen_mkdirs(const char *path, const char *mode);
extern size_t get_file_size(const char *path);
extern uint8_t *load_raw_file(const char *path, size_t *size);
extern uint8_t *load_raw_file_dos_conv(const char *path, size_t *size);
extern int save_raw_file(const char *path, const char *mode, uint8_t *data, size_t data_size);
extern int save_string_to_file(const char *path, const char *mode, char *string);
extern int save_string_array_to_file(const char *path, const char *mode, char **array, int linecount);
extern int32_t count_linebreaks(FILE *file);
extern int check_file_is_readable(const char *path);
extern int check_dir_exists(const char *path);
