// in fileio/dir_struct.h:
// DIR_CHAR, fs_file_t, fs_dir_t

#ifdef _WIN32

#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif

#include "../libraries/dirent.h"

#define DIR_CHAR '\\'
#else
#include <dirent.h>
#define DIR_CHAR '/'
#endif

extern int dir_count(const char *path, int *subdir_count, int *subfile_count);
extern void load_dir(const char *path, fs_dir_t *dir);
extern void load_dir_depth(const char *path, fs_dir_t *dir, int max_depth);
extern void print_dir_depth(fs_dir_t *dir, int current_depth);
extern char *sprint_dir_depth_fullarg(fs_dir_t *dir, int current_depth, char **string, size_t *alloc_count);
extern void free_dir(fs_dir_t *dir);
extern void export_subfiles_to_file(FILE *file, fs_dir_t *dir, const int indent, const int path_full);
extern int export_subfiles_to_path_fullarg(const char *path, fs_dir_t *dir, const int path_full);
extern int export_subfiles_to_path(const char *path, fs_dir_t *dir);
extern void export_whole_dir_flat_to_file(FILE *file, fs_dir_t *dir, const int show_dirs, const int path_start);
extern int export_whole_dir_flat_to_path(const char *path, fs_dir_t *dir, const int show_dirs, const int remove_path);
extern int dirent_test(const char *path);
extern void get_volumes_path();
extern int64_t get_volume_free_space(const char *path);
extern double get_volume_free_space_gb(const char *path);

#define sprint_dir_depth(dir, current_depth)	sprint_dir_depth_fullarg(dir, current_depth, NULL, NULL)
#define export_subfiles_to_path(path, dir)	export_subfiles_to_path_fullarg(path, dir, 0)
