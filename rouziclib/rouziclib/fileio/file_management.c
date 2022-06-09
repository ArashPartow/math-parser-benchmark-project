#ifndef _WIN32
#include <sys/stat.h>
#endif

int create_symlink(const char *oldname, const char *newname, const int is_dir)	// returns 0 if successful
{
	#ifdef _WIN32
	wchar_t oldname_wc[PATH_MAX*2], newname_wc[PATH_MAX*2];

	utf8_to_wchar(oldname, oldname_wc);
	utf8_to_wchar(newname, newname_wc);
	return CreateSymbolicLinkW(newname_wc, oldname_wc, is_dir) == 0;

	#else

	return symlink(oldname, newname);
	#endif
}

int create_dir(const char *path)	// returns 0 if successful
{
	#ifdef _WIN32
	wchar_t wpath[PATH_MAX*2];

	utf8_to_wchar(path, wpath);
	return CreateDirectoryW(wpath, NULL) == 0;

	#else

	return mkdir(path, 0755);
	#endif
}

int create_dir_recursive(const char *path)
{
	char parent_path[PATH_MAX*4];

	if (path==NULL)
		return -1;
	if (path[0]=='\0')
		return -1;

	if (check_dir_exists(path))
		return 0;

	if (create_dir(path) == 0)			// if successful
		return 0;

	remove_name_from_path(parent_path, path);
	if (create_dir_recursive(parent_path))		// if creating the parents failed
		return -1;

	return create_dir(path);			// create the dir after the parents have been created
}

int create_dirs_for_file(const char *filepath)
{
	char parent_path[PATH_MAX*4];

	remove_name_from_path(parent_path, filepath);
	return create_dir_recursive(parent_path);
}

int move_file(const char *path, const char *newpath)	// returns 0 if successful
{
	#ifdef _WIN32
	wchar_t wpath[PATH_MAX*2], wnewpath[PATH_MAX*2];

	utf8_to_wchar(path, wpath);
	utf8_to_wchar(newpath, wnewpath);
	return MoveFileW(wpath, wnewpath)==0;

	#else

	return rename(path, newpath);
	#endif
}

int copy_file(const char *path, const char *newpath, const int overwrite)	// returns 0 if successful
{
	#ifdef _WIN32
	wchar_t wpath[PATH_MAX*2], wnewpath[PATH_MAX*2];

	utf8_to_wchar(path, wpath);
	utf8_to_wchar(newpath, wnewpath);
	return CopyFileW(wpath, wnewpath, overwrite==0)==0;

	#else

	size_t data_size;
	uint8_t *data;
	int ret;

	// FIXME bad approach if the file is large
	data = load_raw_file(path, &data_size);
	if (data==NULL)
		return 1;

	if (check_file_is_readable(newpath) && overwrite==0)		// if we can't overwrite the destination file
		return 1;

	ret = save_raw_file(newpath, "wb", data, data_size)==0;
	free(data);

	return ret;
	#endif
}

int remove_file(const char *path)	// returns 0 if successful
{
	#ifdef _WIN32
	wchar_t wpath[PATH_MAX*2];

	utf8_to_wchar(path, wpath);
	return _wremove(wpath);

	#else

	return remove(path);
	#endif
}

int remove_empty_dir(const char *path)
{
	#ifdef _WIN32
	wchar_t wpath[PATH_MAX*2];

	utf8_to_wchar(path, wpath);
	return RemoveDirectoryW(wpath);

	#else

	return rmdir(path);
	#endif
}

int remove_every_file(const char *path)		// returns 0 if successful on every single file
{
	int i, ret=0;
	fs_dir_t dir;
	char ffp[PATH_MAX*4];

	memset(&dir, 0, sizeof(fs_dir_t));

	load_dir_depth(path, &dir, 0);

	for (i=0; i<dir.subfile_count; i++)
		if (dir.subfile[i].name)
			ret |= remove_file(append_name_to_path(ffp, path, dir.subfile[i].name));

	free_dir(&dir);

	return ret;
}

int remove_dir(const char *path)
{
	int i, ret=0;
	fs_dir_t dir;
	char ffp[PATH_MAX*4];

	memset(&dir, 0, sizeof(fs_dir_t));

	load_dir_depth(path, &dir, 0);

	for (i=0; i<dir.subdir_count; i++)
		if (dir.subdir[i].path)
			ret |= remove_dir(dir.subdir[i].path);

	for (i=0; i<dir.subfile_count; i++)
		if (dir.subfile[i].name)
			ret |= remove_file(append_name_to_path(ffp, path, dir.subfile[i].name));

	remove_empty_dir(path);

	free_dir(&dir);

	return ret;
}

#ifdef _WIN32
#ifndef SHSTDAPI
#if defined(_SHELL32_)
#define SHSTDAPI          STDAPI
#define SHSTDAPI_(type)   STDAPI_(type)
#else
#define SHSTDAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define SHSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif
#endif // SHSTDAPI

SHSTDAPI_(HINSTANCE) ShellExecuteW(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR lpOperation, _In_ LPCWSTR lpFile, _In_opt_ LPCWSTR lpParameters, _In_opt_ LPCWSTR lpDirectory, _In_ INT nShowCmd);
#endif

#ifndef __APPLE__
void system_open(const char *path)
{
	#ifdef _WIN32
	wchar_t path_w[PATH_MAX*2];

	utf8_to_wchar(path, path_w);
	ShellExecuteW(NULL, NULL, path_w, NULL, NULL, 1 /*SW_SHOWNORMAL*/);	// not using L"open" in the 2nd argument opens with the correct associated program
	#endif
}
#endif

#ifndef __APPLE__
void system_open_url(const char *url)
{
	#ifdef _WIN32
	system_open(url);
	#endif
}
#endif

#ifdef _WIN32
#include <shtypes.h>
typedef ULONG SFGAOF;

SHSTDAPI SHParseDisplayName(_In_ PCWSTR pszName, _In_opt_ IBindCtx *pbc, _Outptr_ PIDLIST_ABSOLUTE *ppidl, _In_ SFGAOF sfgaoIn, _Out_opt_ SFGAOF *psfgaoOut);
SHSTDAPI SHOpenFolderAndSelectItems(_In_ PCIDLIST_ABSOLUTE pidlFolder, UINT cidl, _In_reads_opt_(cidl) PCUITEMID_CHILD_ARRAY apidl, DWORD dwFlags);
#endif

void show_file_in_explorerW(const wchar_t *wpath)
{
	#ifdef _WIN32
	CoInitialize(NULL);

	// Parse the path into a pidl
	PIDLIST_ABSOLUTE pidl;
	SFGAOF flags;
	SHParseDisplayName(wpath, NULL, &pidl, 0, &flags);

	// Open Explorer and select the file
	SHOpenFolderAndSelectItems(pidl, 0, NULL, 0);

	// Use the task allocator to free to returned pidl
	CoTaskMemFree(pidl);
	CoUninitialize();
	#endif
}

void show_file_in_explorer(const char *path)
{
	wchar_t *wpath = utf8_to_wchar(path, NULL);

	show_file_in_explorerW(wpath);

	free(wpath);
}
