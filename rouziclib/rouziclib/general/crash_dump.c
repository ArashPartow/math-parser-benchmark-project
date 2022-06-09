#ifdef RL_CRASHDUMP
#ifdef _WIN32
#include <winver.h>
#include <timezoneapi.h>
#include <DbgHelp.h>

#ifdef _MSC_VER
#pragma comment (lib, "DbgHelp.lib")
#endif

const char *crashdump_dir_path=NULL;

wchar_t *crashdump_make_dump_path()
{
	wchar_t *wpath;
	buffer_t path={0};
	char datestamp[32];
	time_t now = time(NULL);
	strftime(datestamp, sizeof(datestamp), "%Y-%m-%d %H.%M.%S", localtime(&now));

	if (crashdump_dir_path)
		bufprintf(&path, "%s%cCrash dump of %s.dmp", crashdump_dir_path, DIR_CHAR, datestamp);
	else
		bufprintf(&path, "Crash dump of %s.dmp", datestamp);

	wpath = utf8_to_wchar(path.buf, NULL);
	free_buf(&path);
	return wpath;
}

void crashdump_write_minidump(EXCEPTION_POINTERS *exception_ptr)
{
	MINIDUMP_EXCEPTION_INFORMATION dump_info;

	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);

	wchar_t *wpath = crashdump_make_dump_path();

	dump_info.ThreadId = GetCurrentThreadId();
	dump_info.ExceptionPointers = exception_ptr;
	dump_info.ClientPointers = 0;

	MiniDumpWriteDump(GetCurrentProcess(),
			GetCurrentProcessId(),
			CreateFileW((LPCWSTR) wpath, GENERIC_READ | GENERIC_WRITE, 0, NULL, 2 /*CREATE_ALWAYS*/, FILE_ATTRIBUTE_NORMAL, NULL),
			MiniDumpWithDataSegs,
			&dump_info,
			NULL, NULL);

	show_file_in_explorerW(wpath);
}

LONG WINAPI crashdump_callback(EXCEPTION_POINTERS *exception_ptr)
{
	crashdump_write_minidump(exception_ptr);

	return EXCEPTION_CONTINUE_SEARCH;
}
#endif
#endif

// crashdump_init(make_appdata_path("Program name", NULL, 1));
void crashdump_init(const char *path)
{
#ifdef RL_CRASHDUMP
#ifdef _WIN32
	static int init=1;

	if (init==0)
		return;
	init = 0;

	crashdump_dir_path = path;

	SetUnhandledExceptionFilter(crashdump_callback);
	ULONG ulong = 16384;
	SetThreadStackGuarantee(&ulong);
#endif
#endif
}
