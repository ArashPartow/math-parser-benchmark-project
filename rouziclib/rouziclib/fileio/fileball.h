// in fileio/fileball_struct.h
// fileball_t, fileball_subfile_t

extern void fileball_add_file(buffer_t *sout, const char *path, const char *name, int abs_path_len);
extern void fileball_add_subfiles(buffer_t *sout, fs_dir_t *dir, int abs_path_len);
extern void fileball_add_whole_path(buffer_t *sout, const char *path, const int depth);
extern buffer_t fileball_make_uncompressed(char **paths, int path_count, const int depth);
extern void fileball_make_uncompressed_file(char *out_path, char **paths, int path_count, const int depth);
extern buffer_t fileball_make_z(char **paths, int path_count, const int depth);
extern void fileball_make_z_file(char *out_path, char **paths, int path_count, const int depth);
extern void fileball_make_header_file(char *out_path, char **paths, int path_count, const int depth);
extern void fileball_extract_mem_to_path(buffer_t *ball, const char *extract_path);
extern void fileball_extract_z_mem_to_path(buffer_t *zball, const char *extract_path);
extern void fileball_extract_z_file_to_path(const char *in_path, const char *extract_path);
extern fileball_t fileball_extract_z_mem_to_struct(buffer_t *zball);
extern fileball_subfile_t *fileball_find_subfile(fileball_t *s, const char *name);
extern void free_fileball_struct(fileball_t *s);
