#ifdef RL_LIBSNDFILE

SNDFILE *sf_open_utf8(char *path, int mode, SF_INFO *sfinfo)
{
#ifdef _WIN32
	uint16_t wpath[PATH_MAX];

	utf8_to_wchar(path, wpath);
	return sf_wchar_open(wpath, mode, sfinfo);
#else
	return sf_open(path, mode, sfinfo);
#endif
}

#endif
