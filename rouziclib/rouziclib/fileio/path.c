const char *find_last_dirchar(const char *path, int ignore_trailing)
{
	int i, len;

	if (path==NULL)
		return NULL;

	len = strlen(path);
	if (ignore_trailing)
		len -= 1;
	if (len <= 0)
		return path;

	for (i = len-1; i >= 0; i--)
		if (path[i] == '/' || path[i] == '\\')
			return &path[i];

	return NULL;
}

char *remove_name_from_path(char *dirpath, const char *fullpath)	// removes the file or dir name after DIR_CHAR and DIR_CHAR itself
{
	const char *p;
	int len;

	if (dirpath)
		dirpath[0] = '\0';

	if (fullpath==NULL)
	{
		fprintf_rl(stderr, "fullpath is NULL in remove_name_from_path()\n");
		return NULL;
	}

	p = find_last_dirchar(fullpath, 1);	// look for the last '\' or '/', ignoring trailing ones
	if (p == NULL)
		return NULL;

	len = p - fullpath;

	if (dirpath==NULL)
		dirpath = calloc(len + 1, sizeof(char));

	memcpy(dirpath, fullpath, len);
	dirpath[len] = 0;

	return dirpath;
}

char *remove_extension_from_path(char *dirpath, const char *fullpath)
{
	char *p;
	int len;

	if (dirpath)
		dirpath[0] = '\0';

	if (fullpath==NULL)
	{
		fprintf_rl(stderr, "fullpath is NULL in remove_extension_from_path()\n");
		return NULL;
	}

	p = strrchr(fullpath, '.');
	if (p == NULL)
		return NULL;

	len = p - fullpath;

	if (dirpath==NULL)
		dirpath = calloc(len + 1, sizeof(char));

	memcpy(dirpath, fullpath, len);
	dirpath[len] = 0;

	return dirpath;
}

const char *get_filename_from_path(const char *fullpath)	// returns a pointer to the filename in the path
{
	const char *p;

	if (fullpath==NULL)
	{
		fprintf_rl(stderr, "fullpath is NULL in get_filename_from_path()\n");
		return NULL;
	}

	p = find_last_dirchar(fullpath, 0);
	if (p)
		return &p[1];

	return fullpath;
}

char *append_name_to_path(char *dest, const char *path, const char *name)	// appends name to path properly regardless of how path is ended
{
	int path_len, name_len, path_has_dirchar=0;

	if (path==NULL && name==NULL)
	{
		if (dest)
			dest[0] = '\0';
		return dest;
	}

	if (name==NULL)
	{
		if (dest)
			sprintf(dest, "%s", path);
		return dest;
	}

	if (path==NULL)
	{
		if (dest)
			sprintf(dest, "%s", name);
		return dest;
	}

	path_len = strlen(path);
	name_len = strlen(name);

	if (path_len > 0)
		if (path[path_len-1] == DIR_CHAR)
			path_has_dirchar = 1;

	if (dest==NULL)
		dest = calloc(path_len + name_len + 2, sizeof(char));

	if (dest==path)		// in-place appending
	{
		if (path_has_dirchar)
			sprintf(&dest[path_len], "%s", name);
		else
			sprintf(&dest[path_len], "%c%s", DIR_CHAR, name);
	}
	else
	{
		if (path_has_dirchar)
			sprintf(dest, "%s%s", path, name);
		else
			sprintf(dest, "%s%c%s", path, DIR_CHAR, name);
	}

	return dest;
}

char *extract_file_extension(const char *path, char *ext)
{
	int len, i, j;

	if (ext==NULL)
		return NULL;
	ext[0] = '\0';
	if (path==NULL)
		return NULL;

	len = strlen(path);
	i = len - 1;				// start from the end of the string

	if (i <= 0)
		return NULL;

	while (path[i] != '.' && i > 0)		// decrement until a . or the beginning
		i--;

	if (path[i] == '.')
	{
		if (ext==NULL)
			ext = calloc(len-(i+1)+1, sizeof(char));

		strcpy(ext, &path[i+1]);	// copy extension
	}
	else
	{
		if (ext==NULL)
			ext = calloc(1, sizeof(char));

		ext[0] = '\0';
	}

	string_tolower(ext);

	return ext;
}

#ifdef _WIN32
#ifndef SHFOLDERAPI
#if defined(_SHFOLDER_) || defined(_SHELL32_)
#define SHFOLDERAPI           STDAPI
#else
#define SHFOLDERAPI           EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#endif
#endif
SHFOLDERAPI SHGetFolderPathW(_Reserved_ HWND hwnd, _In_ int csidl, _In_opt_ HANDLE hToken, _In_ DWORD dwFlags, _Out_writes_(MAX_PATH) LPWSTR pszPath);
#endif

char *win_get_system_folder_path(int csidl)
{
	char *path = NULL;

	#ifdef _WIN32
	wchar_t path_w[PATH_MAX];

	SHGetFolderPathW(NULL, csidl, NULL, 0, path_w);
	//SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, path_w);
	path = wchar_to_utf8(path_w, NULL);
	#endif

	return path;
}

#ifdef __APPLE__
#include <glob.h>
#endif

char *make_appdata_path(const char *dirname, const char *filename, const int make_subdir)
{
	char *path=NULL, *dirpath=NULL;

	#ifdef _WIN32

	char *origpath = win_get_system_folder_path(0x001a /*CSIDL_APPDATA*/);

	#elif defined(__APPLE__)

	glob_t globbuf;
	char *origpath=NULL;

	if (glob("~/Library/Application Support/", GLOB_TILDE | GLOB_MARK, NULL, &globbuf)==0)	// globbuf.gl_pathv[0] is the path
		origpath = globbuf.gl_pathv[0];
	else
	{
		globfree(&globbuf);
		return NULL;
	}

	#else
	char origpath[] = "~/.config/";
	#endif

	dirpath = append_name_to_path(NULL, origpath, dirname);

	if (make_subdir)
		create_dir(dirpath);

	if (filename)
	{
		path = append_name_to_path(NULL, dirpath, filename);
		free(dirpath);
	}
	else
		path = dirpath;

	#ifdef _WIN32
	free(origpath);
	#endif

	#ifdef __APPLE__
	globfree(&globbuf);
	#endif

	return path;
}

int check_path_against_extension_list(const char *path, const char *list_ext[], size_t list_count)
{
	int i;
	char ext[32];		// file extension

	extract_file_extension(path, ext);
	if (ext[0] == '\0')
		return 0;

	for (i=0; i < list_count; i++)
		if (strcmp(ext, list_ext[i])==0)
			return 1;			// indicate it's a valid extension

	return 0;
}

int is_path_image_file(const char *path)
{
	const char *list_ext[] = {"jpg", "jpeg", "png", "tga", "targa", "bmp", "psd", "gif", "tif", "tiff", "fts"};

	return check_path_against_extension_list(path, list_ext, sizeof(list_ext)/sizeof(char *));
}

int is_path_video_file(const char *path)
{
	const char *list_ext[] = {"avi", "mp4", "mkv", "mov", "webm", "m2ts", "flv"};

	return check_path_against_extension_list(path, list_ext, sizeof(list_ext)/sizeof(char *));
}

int chdir_utf8(const char *dirname)
{
#ifdef _WIN32
	int ret;
	wchar_t *wpath;

	wpath = utf8_to_utf16(dirname, NULL);
	ret = _wchdir(wpath);
	free(wpath);

	return ret;
#else
	return chdir(dirname);
#endif
}
