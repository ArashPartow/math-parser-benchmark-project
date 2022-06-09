#ifndef PREF_LOC_DELIM
#define PREF_LOC_DELIM ":"
#endif

typedef struct
{
	char *path;
	char **lines;
	int linecount;
} pref_file_t;

extern pref_file_t pref_def;

extern void pref_file_load(pref_file_t *pf);
extern int pref_file_save(pref_file_t *pf);
extern void free_pref_file(pref_file_t *pf);
extern pref_file_t pref_set_file_by_path(const char *path);
extern pref_file_t pref_set_file_by_appdata_path(const char *folder, const char *filename);
extern int pref_find_loc(pref_file_t *pf, const char *loc);

extern double pref_get_double(pref_file_t *pf, char *loc, double def_value, const char *suffix);
extern void pref_set_double(pref_file_t *pf, char *loc, double new_value, const char *suffix);
extern const char *pref_handle_string(pref_file_t *pf, char *loc, char *string_prefix, const char *string, int mode_set);
extern const char *pref_get_string(pref_file_t *pf, char *loc, const char *def_string);
extern void pref_set_string(pref_file_t *pf, char *loc, const char *new_string);
extern int pref_get_onoff(pref_file_t *pf, char *loc, int def_state);
extern void pref_set_onoff(pref_file_t *pf, char *loc, int new_state);
extern xy_t pref_get_2val(pref_file_t *pf, char *loc, double v1, char *v_delim, double v2, char *suffix);
extern void pref_set_2val(pref_file_t *pf, char *loc, double v1, char *v_delim, double v2, char *suffix);
