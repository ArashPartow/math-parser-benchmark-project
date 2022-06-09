extern char *make_string_copy(const char *orig);
extern char *make_string_copy_len(const char *orig, size_t len);
extern char *make_string_copy_between_ptrs(const char *start, const char *end);
extern char **make_string_array_copy(const char **orig, const size_t count);
extern void strcpy_then_free(char *dest, char *src);
extern char *replace_char(char *str, char find, char replace);
extern char *string_tolower(char *str);
extern char *vsprintf_realloc(char **string, size_t *alloc_count, const int append, const char *format, va_list args);
extern char *sprintf_realloc(char **string, size_t *alloc_count, const int append, const char *format, ...);
extern char *vsprintf_alloc(const char *format, va_list args);
extern char *sprintf_ret(char *str, const char *format, ...);
extern char **string_array_insert_lines(char **array, int *linecount, char **ins, int ins_count, int ins_pos);
extern char **string_array_insert_line(char **array, int *linecount, char *ins, int ins_pos);
extern char **string_array_replace_line(char **array, int *linecount, char *repl, int repl_pos);

#define sprintf_alloc(format, ...) sprintf_realloc(NULL, NULL, 0, format, ##__VA_ARGS__)
