// Open directory stream DIRNAME for read and return a pointer to the internal working area that is used to retrieve individual directory entries
_WDIR *_wopendir(const wchar_t *dirname)
{
	_WDIR *dirp = NULL;
	int error;

	// Must have directory name
	if (dirname == NULL)
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	if (dirname[0] == '\0')
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	// Allocate new _WDIR structure
	dirp = (_WDIR*) malloc (sizeof (struct _WDIR));
	if (dirp != NULL)
	{
		DWORD n;

		// Reset _WDIR structure
		dirp->handle = INVALID_HANDLE_VALUE;
		dirp->patt = NULL;
		dirp->cached = 0;

		/* Compute the length of full path plus zero terminator
		 * 
		 * Note that on WinRT there's no way to convert relative paths
		 * into absolute paths, so just assume its an absolute path.
		 */
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
		n = wcslen(dirname);
#else
		n = GetFullPathNameW (dirname, 0, NULL, NULL);
#endif

		// Allocate room for absolute directory name and search pattern
		dirp->patt = (wchar_t*) malloc (sizeof (wchar_t) * n + 16);
		if (dirp->patt)
		{
			/*
			 * Convert relative directory name to an absolute one.  This
			 * allows rewinddir() to function correctly even when current
			 * working directory is changed between opendir() and rewinddir().
			 * 
			 * Note that on WinRT there's no way to convert relative paths
			 * into absolute paths, so just assume its an absolute path.
			 */
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
			wcsncpy_s(dirp->patt, n+1, dirname, n);
#else
			n = GetFullPathNameW (dirname, n, dirp->patt, NULL);
#endif
			if (n > 0)
			{
				wchar_t *p;

				// Append search pattern \* to the directory name
				p = dirp->patt + n;
				if (dirp->patt < p)
				{
					switch (p[-1])
					{
						case '\\':
						case '/':
						case ':':
							// Directory ends in path separator, e.g. c:\temp\
							//NOP;
							break;

						default:
							// Directory name doesn't end in path separator
							*p++ = '\\';
					}
				}
				*p++ = '*';
				*p = '\0';

				// Open directory stream and retrieve the first entry
				if (dirent_first (dirp))
				{
					// Directory stream opened successfully
					error = 0;
				}
				else
				{
					// Cannot retrieve first entry
					error = 1;
					dirent_set_errno(ENOENT);
				}

			}
			else
			{
				// Cannot retrieve full path name
				dirent_set_errno(ENOENT);
				error = 1;
			}

		}
		else
		{
			// Cannot allocate memory for search pattern
			error = 1;
		}

	}
	else
	{
		// Cannot allocate _WDIR structure
		error = 1;
	}

	// Clean up in case of error
	if (error  &&  dirp)
	{
		_wclosedir (dirp);
		dirp = NULL;
	}

	return dirp;
}

/*
 * Read next directory entry.  The directory entry is returned in dirent
 * structure in the d_name field.  Individual directory entries returned by
 * this function include regular files, sub-directories, pseudo-directories
 * "." and ".." as well as volume labels, hidden files and system files.
 */
struct _wdirent *_wreaddir(_WDIR *dirp)
{
	WIN32_FIND_DATAW *datap;
	struct _wdirent *entp;

	// Read next directory entry
	datap = dirent_next (dirp);
	if (datap)
	{
		size_t n;
		DWORD attr;

		// Pointer to directory entry to return
		entp = &dirp->ent;

		/* 
		 * Copy file name as wide-character string.  If the file name is too
		 * long to fit in to the destination buffer, then truncate file name
		 * to PATH_MAX characters and zero-terminate the buffer.
		 */
		n = 0;
		while (n + 1 < PATH_MAX  &&  datap->cFileName[n] != 0)
		{
			entp->d_name[n] = datap->cFileName[n];
			n++;
		}
		dirp->ent.d_name[n] = 0;

		// Length of file name excluding zero terminator
		entp->d_namlen = n;

		// File type
		attr = datap->dwFileAttributes;
		if ((attr & FILE_ATTRIBUTE_DEVICE) != 0)
		{
			entp->d_type = DT_CHR;
		} else if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
		{
			entp->d_type = DT_DIR;
		}
		else
		{
			entp->d_type = DT_REG;
		}

		// Reset dummy fields
		entp->d_ino = 0;
		entp->d_reclen = sizeof (struct _wdirent);

	}
	else
	{
		// Last directory entry read
		entp = NULL;

	}

	return entp;
}

/*
 * Close directory stream opened by opendir() function.  This invalidates the
 * DIR structure as well as any directory entry read previously by
 * _wreaddir().
 */
int _wclosedir(_WDIR *dirp)
{
	int ok;
	if (dirp)
	{
		// Release search handle
		if (dirp->handle != INVALID_HANDLE_VALUE)
		{
			FindClose (dirp->handle);
			dirp->handle = INVALID_HANDLE_VALUE;
		}

		// Release search pattern
		if (dirp->patt)
		{
			free (dirp->patt);
			dirp->patt = NULL;
		}

		// Release directory structure
		free (dirp);
		ok = /*success*/0;

	}
	else
	{
		// Invalid directory stream
		dirent_set_errno(EBADF);
		ok = /*failure*/-1;
	}
	return ok;
}

// Rewind directory stream such that _wreaddir() returns the very first file name again
void _wrewinddir(_WDIR *dirp)
{
	if (dirp)
	{
		// Release existing search handle
		if (dirp->handle != INVALID_HANDLE_VALUE)
		{
			FindClose (dirp->handle);
		}

		// Open new search handle
		dirent_first (dirp);
	}
}

// Get first directory entry (internal)
WIN32_FIND_DATAW *dirent_first(_WDIR *dirp)
{
	WIN32_FIND_DATAW *datap;

	// Open directory and retrieve the first entry
	dirp->handle = FindFirstFileExW(
			dirp->patt, FindExInfoStandard, &dirp->data,
			FindExSearchNameMatch, NULL, 0);
	if (dirp->handle != INVALID_HANDLE_VALUE)
	{
		// a directory entry is now waiting in memory
		datap = &dirp->data;
		dirp->cached = 1;

	}
	else
	{
		// Failed to re-open directory: no directory entry in memory
		dirp->cached = 0;
		datap = NULL;

	}
	return datap;
}

// Get next directory entry (internal)
WIN32_FIND_DATAW *dirent_next(_WDIR *dirp)
{
	WIN32_FIND_DATAW *p;

	// Get next directory entry
	if (dirp->cached != 0)
	{
		// A valid directory entry already in memory
		p = &dirp->data;
		dirp->cached = 0;

	} else if (dirp->handle != INVALID_HANDLE_VALUE)
	{
		// Get the next directory entry from stream
		if (FindNextFileW (dirp->handle, &dirp->data) != FALSE)
		{
			// Got a file
			p = &dirp->data;
		}
		else
		{
			// The very last entry has been processed or an error occured
			FindClose (dirp->handle);
			dirp->handle = INVALID_HANDLE_VALUE;
			p = NULL;
		}

	}
	else
	{
		// End of directory stream reached
		p = NULL;

	}

	return p;
}

// Set errno variable
void dirent_set_errno(int error)
{
#if defined(_MSC_VER)  &&  _MSC_VER >= 1400

	// Microsoft Visual Studio 2005 and later
	_set_errno(error);

#else

	// Non-Microsoft compiler or older Microsoft compiler
	errno = error;

#endif
}

// Open directory stream using plain old C-string
DIR *opendir(const char *dirname) 
{
	struct DIR *dirp;
	int error;

	// Must have directory name
	if (dirname == NULL)
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	if (dirname[0] == '\0')
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	// Allocate memory for DIR structure
	dirp = (DIR*) malloc (sizeof (struct DIR));
	if (dirp)
	{
		wchar_t wname[PATH_MAX*4];	// for some reason MultiByteToWideChar requires more space than it actually needs

		// Convert directory name to wide-character string
		utf8_to_utf16(dirname, wname);

		// Open directory stream using wide-character name
		dirp->wdirp = _wopendir (wname);
		if (dirp->wdirp)
		{
			// Directory stream opened
			error = 0;
		}
		else
		{
			// Failed to open directory stream
			error = 1;
		}
	}
	else
	{
		// Cannot allocate DIR structure
		error = 1;
	}

	// Clean up in case of error
	if (error  &&  dirp)
	{
		free (dirp);
		dirp = NULL;
	}

	return dirp;
}

/*
 * Read next directory entry.
 *
 * When working with text consoles, please note that file names returned by
 * readdir() are represented in the default ANSI code page while any output to
 * console is typically formatted on another code page.  Thus, non-ASCII
 * characters in file names will not usually display correctly on console.  The
 * problem can be fixed in two ways: (1) change the character set of console
 * to 1252 using chcp utility and use Lucida Console font, or (2) use
 * _cprintf function when writing to console.  The _cprinf() will re-encode
 * ANSI strings to the console code page so many non-ASCII characters will
 * display correcly.
 */
struct dirent *readdir(DIR *dirp) 
{
	WIN32_FIND_DATAW *datap;
	struct dirent *entp;

	// Read next directory entry
	datap = dirent_next (dirp->wdirp);
	if (datap)
	{
		utf16_to_utf8(datap->cFileName, dirp->ent.d_name);

		DWORD attr;

		// Initialize directory entry for return
		entp = &dirp->ent;

		// Length of file name excluding zero terminator
		entp->d_namlen = strlen(dirp->ent.d_name);

		// File attributes
		attr = datap->dwFileAttributes;
		if ((attr & FILE_ATTRIBUTE_DEVICE) != 0)
		{
			entp->d_type = DT_CHR;
		} else if ((attr & FILE_ATTRIBUTE_DIRECTORY) != 0)
		{
			entp->d_type = DT_DIR;
		}
		else
		{
			entp->d_type = DT_REG;
		}

		// Reset dummy fields
		entp->d_ino = 0;
		entp->d_reclen = sizeof (struct dirent);
	}
	else
		entp = NULL;	// No more directory entries

	return entp;
}

// Close directory stream
int closedir(DIR *dirp) 
{
	int ok;
	if (dirp)
	{
		// Close wide-character directory stream
		ok = _wclosedir (dirp->wdirp);
		dirp->wdirp = NULL;

		// Release multi-byte character version
		free (dirp);

	}
	else
	{
		// Invalid directory stream
		dirent_set_errno(EBADF);
		ok = /*failure*/-1;

	}
	return ok;
}

// Rewind directory stream to beginning
void rewinddir(DIR* dirp) 
{
	// Rewind wide-character string directory stream
	_wrewinddir (dirp->wdirp);
}

char *realpath(const char *file_name, char *resolved_name)
{
	wchar_t wpath[PATH_MAX*4], wres[PATH_MAX*4];
	int ret;

	if (file_name == NULL)
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	if (file_name[0] == '\0')
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	if (resolved_name==NULL)
		resolved_name = (char *) calloc (PATH_MAX*4, sizeof(char));

	utf8_to_utf16(file_name, wpath);

	ret = GetFullPathNameW (wpath, PATH_MAX*4, wres, NULL);
	if (ret==0)
	{
		dirent_set_errno(ENOENT);
		return NULL;
	}

	utf16_to_utf8(wres, resolved_name);

	return resolved_name;
}
