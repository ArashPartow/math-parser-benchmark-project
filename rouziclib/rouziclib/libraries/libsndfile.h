#ifdef RL_LIBSNDFILE

#ifdef _WIN32
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#endif
#include <sndfile.h>

extern SNDFILE *sf_open_utf8(char *path, int mode, SF_INFO *sfinfo);

#endif
