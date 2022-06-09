#ifdef _MSC_VER
#define snprintf _snprintf	// Microsoft is stupid, like seriously
#define strcasecmp stricmp
#endif

extern const char *skip_string(const char *string, const char *skipstring);
extern const char *skip_whitespace(const char *string);
extern const char *skip_line(const char *string);
extern int string_count_fields(const char *string, const char *delim);
extern int string_get_field(const char *string, const char *delim, int n, char *field);
extern const char *string_parse_fractional_12(const char *string, double *v);
extern double doztof(const char *string);
extern xy_t doztof_xy(const char *str_x, const char *str_y);
extern char *remove_after_char(char *string, const char c);
extern int strlen_until_after_char(const char *string, const char c);
extern char *remove_after_char_copy(const char *string, const char c);
extern size_t get_string_linecount(const char *text, size_t len);
extern int string_find_start_nth_line(const char *text, int len, int n);
extern char **arrayise_text(char *text, int *linecount);
extern const char *strstr_i(const char *fullstr, const char *substr);
extern const char *strstr_after(const char *fullstr, const char *substr);
extern void *memmem_rl(const uint8_t *l, size_t l_len, const uint8_t *s, size_t s_len);
extern int compare_varlen_word_to_fixlen_word(const char *var, size_t varlen, const char *fix);
extern int strcmp_len2(const char *str1, const char *str2);
extern const char *find_pattern_in_string(const char *str, const char *pat);
extern const char *find_date_time_in_string(const char *str);
extern double parse_timestamp(const char *ts);
extern int find_line_indentation_depth(const char *line);
extern void parse_xy_array_file(char *path, xy_t **xy_array, size_t *xy_array_size);
extern char *xml_copy_field_string(const char *parent_start, const char *parent_end, const char *tag_start, const char *tag_end);
extern double xml_copy_field_number(const char *parent_start, const char *parent_end, const char *tag_start);
extern double parse_music_note(const char *string);
