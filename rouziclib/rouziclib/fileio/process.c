#ifdef _WIN32

PROCESS_INFORMATION create_process_direct(const char *cmd, DWORD flags)
{
	STARTUPINFOW si={0};
	PROCESS_INFORMATION procinf={0};
	wchar_t wcmd[32768];

	si.cb = sizeof(si);

	utf8_to_wchar(cmd, wcmd);

	// Start the child process.
	if( !CreateProcessW( NULL,		// No module name (use command line)
				wcmd,		// Command line
				NULL,		// Process handle not inheritable
				NULL,		// Thread handle not inheritable
				FALSE,		// Set handle inheritance to FALSE
				flags,		// No creation flags
				NULL,		// Use parent's environment block
				NULL,		// Use parent's starting directory 
				&si,		// Pointer to STARTUPINFO structure
				&procinf)	// Pointer to PROCESS_INFORMATION structure
	  ) 
	{
		fprintf_rl(stderr, "CreateProcessW failed (%d) in create_process_direct(%s)\n", GetLastError(), cmd);
		return procinf;
	}

	return procinf;
}

PROCESS_INFORMATION create_process_flags(const char *cmd, DWORD flags, int close_handles)
{
	STARTUPINFOW si={0};
	PROCESS_INFORMATION procinf={0};
	char full_cmd[32768];
	wchar_t wcmd[32768];

	si.cb = sizeof(si);

	sprintf(full_cmd, "C:\\Windows\\System32\\cmd.exe /C \"%s\"", cmd);
	utf8_to_wchar(full_cmd, wcmd);

	// Start the child process.
	if( !CreateProcessW( NULL,		// No module name (use command line)
				wcmd,		// Command line
				NULL,		// Process handle not inheritable
				NULL,		// Thread handle not inheritable
				FALSE,		// Set handle inheritance to FALSE
				flags,		// No creation flags
				NULL,		// Use parent's environment block
				NULL,		// Use parent's starting directory 
				&si,		// Pointer to STARTUPINFO structure
				&procinf)	// Pointer to PROCESS_INFORMATION structure
	  ) 
	{
		fprintf_rl(stderr, "CreateProcessW failed (%d) in create_process_flags(%s)\n", GetLastError(), cmd);
		return procinf;
	}

	if (close_handles)
	{		
		CloseHandle(procinf.hProcess);
		CloseHandle(procinf.hThread);
		procinf.hProcess = NULL;
		procinf.hThread = NULL;
	}

	return procinf;
}

void wait_process_end(PROCESS_INFORMATION *procinf)
{
//fprintf_rl(stdout, "Waiting...\n");
	// Wait until child process exits
//fprintf_rl(stdout, "return %d\n", WaitForSingleObject(procinf->hProcess, 0));
	WaitForSingleObject(procinf->hProcess, INFINITE);
//fprintf_rl(stdout, "return %d\n", WaitForSingleObject(procinf->hProcess, 0));
//fprintf_rl(stdout, "Done.\n");

	// Close process and thread handles
	CloseHandle(procinf->hProcess);
	CloseHandle(procinf->hThread);
}

void send_SIGINT(HANDLE hProcess)	// probably better to use TerminateProcess(hProcess, 0);
{
	DWORD pid = GetProcessId(hProcess);
	FreeConsole();
	if (AttachConsole(pid))
	{
		// Disable Ctrl-C handling for our program
		SetConsoleCtrlHandler(NULL, 1);

		GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0); // SIGINT

		//Re-enable Ctrl-C handling or any subsequently started
		//programs will inherit the disabled state.
		SetConsoleCtrlHandler(NULL, 0);

		WaitForSingleObject(hProcess, 10000);
	}
}

int is_process_running(HANDLE hProcess)
{
	DWORD exit_code=0;

	if (hProcess == NULL)
		return 0;

	GetExitCodeProcess(hProcess, &exit_code);

	return exit_code == STILL_ACTIVE;
}

#endif

#if defined(__APPLE__)	// copied from https://github.com/apple/swift/blob/master/stdlib/public/stubs/CommandLine.cpp
// NOTE: forward declare this rather than including crt_externs.h as not all SDKs provide it
extern char ***_NSGetArgv(void);
extern int *_NSGetArgc(void);
#endif

#ifdef _WIN32

// from ShlObj.h
#ifndef SHSTDAPI
#if defined(_SHELL32_)
#define SHSTDAPI          STDAPI
#define SHSTDAPI_(type)   STDAPI_(type)
#else
#define SHSTDAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define SHSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif
#endif // SHSTDAPI

// from shellapi.h
SHSTDAPI_(LPWSTR *)  CommandLineToArgvW(_In_ LPCWSTR lpCmdLine, _Out_ int* pNumArgs);

#endif

char **get_argv(int *argc)
{
#ifdef _WIN32
	LPWSTR *argv_w = CommandLineToArgvW(GetCommandLineW(), argc);
	char **argv = calloc(*argc, sizeof(char *));

	for (int i=0; i < *argc; i++)
		argv[i] = wchar_to_utf8(argv_w[i], NULL);

	LocalFree(argv_w);

#elif defined(__APPLE__)
	*argc = *_NSGetArgc();
	char **argv = make_string_array_copy(*_NSGetArgv(), *argc);

#else
	// TODO (probably read from /proc/self/cmdline)
	char **argv = NULL;
	*argc = 0;
#endif

	return argv;
}
