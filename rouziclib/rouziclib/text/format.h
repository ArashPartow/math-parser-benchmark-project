#define strend(x)	&x[strlen(x)]

#ifndef fprintf_rl
#define fprintf_rl fprintf
#endif

#define VALFMT_DEFAULT	"%.2f"
#define VALFMT_NEAR_INT	"%.0f"

extern char *sprint_large_num_simple(char *string, double number);
extern char *sprint_fractional_12(char *string, double v);
extern char *get_english_ordinal(int n);
extern char *short_month_to_long_month(char *sm);
extern char *date_macro_to_nice_date(char *string, const char *d);
extern int get_date_macro_year(const char *d);
extern char *sprint_compile_date_fullarg(char *string, const char *location, const char *d, const char *t);
extern void fprint_indent(FILE *file, char *indent, int ind_lvl, char *string);
extern char *sprint_localtime_now(char *string);
extern void fprint_localtime_now(FILE *stream);
extern char *sprint_duration(char *string, double sec);
extern char *sprint_timestamp(char *string, double t, int prec);
extern char *sprint_timestamp_short(char *string, double t, int prec);
extern char *text_to_multiline_c_literal(const char *text, const int linebreak_mode);
extern void fprint_escaped_byte(FILE *fout, unsigned char c0, unsigned char c1);
extern void convert_file_to_header_const_string(const char *in_path);

#define sprint_compile_date(string, location)	sprint_compile_date_fullarg(string, location, __DATE__, __TIME__)
