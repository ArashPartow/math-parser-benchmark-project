#ifdef __EMSCRIPTEN__
#define RL_THREADING_PLATFORM_FAKING
#define __APPLE__
#endif

#ifdef _WIN32
// WinBase.h
#define INFINITE            0xFFFFFFFF
#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateWaitableTimerA(
    _In_opt_ LPSECURITY_ATTRIBUTES lpTimerAttributes,
    _In_     BOOL bManualReset,
    _In_opt_ LPCSTR lpTimerName
    );
#ifndef UNICODE
#define CreateWaitableTimer  CreateWaitableTimerA
#endif

// winerror.h
#define ERROR_TIMEOUT                    1460L
#endif

#define THREAD_U64 uint64_t
#define THREAD_IMPLEMENTATION
#include "../libraries/orig/thread.h"

int thread_detach(rl_thread_t thread)
{
	#if defined( _WIN32 )

	return CloseHandle((HANDLE) thread) != 0;

	#elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )

	return pthread_detach((pthread_t) thread) == 0;

	#else 
	#error Unknown platform.
	#endif
}

void thread_set_low_priority()
{
	#if defined( _WIN32 )

	SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_LOWEST );

	#elif defined( __linux__ ) || defined( __APPLE__ ) || defined( __ANDROID__ )

	nice(39);

	#else 
	#error Unknown platform.
	#endif
}

int rl_thread_create(rl_thread_t *thread_handle, int (*func)(void *), void *arg)
{
	*thread_handle = th_thread_create(func, arg, NULL, 0);

	if (*thread_handle==NULL)
		return 0;
	return 1;
}

int rl_thread_create_detached(int (*func)(void *), void *arg)
{
	rl_thread_t thread_handle={0};

	if (rl_thread_create(&thread_handle, func, arg) == 0)
		return 0;

	return rl_thread_detach(thread_handle);
}

int rl_thread_join_and_null(rl_thread_t *thread_handle)
{
	int ret;

	if (thread_handle==NULL)
		return 0;

	if (*thread_handle==NULL)
		return 0;

	ret = rl_thread_join(*thread_handle);

	memset(thread_handle, 0, sizeof(rl_thread_t));

	return ret;
}

rl_mutex_t *rl_mutex_init_alloc()
{
	rl_mutex_t *mutex = calloc(1, sizeof(rl_mutex_t));
	rl_mutex_init(mutex);

	return mutex;
}

void rl_mutex_destroy_free(rl_mutex_t **mutex)
{
	if (mutex)
	{
		rl_mutex_destroy(*mutex);
		free(*mutex);
		memset(mutex, 0, sizeof(rl_mutex_t));
	}
}

int32_t rl_atomic_get_and_set(volatile int32_t *ptr, int32_t new_value)
{
	#ifdef _WIN32
	return InterlockedExchange(ptr, new_value);

	#elif defined(__linux__) || defined(__APPLE__) || defined(__ANDROID__)

	return __atomic_exchange_n(ptr, new_value, __ATOMIC_ACQ_REL);
	/*int32_t old_value = (int32_t) __sync_lock_test_and_set(ptr, new_value);
	__sync_lock_release(ptr);
	return old_value;*/

	#else 
	#error Unknown platform.
	#endif
}

// Wrappers
void rl_mutex_init   (rl_mutex_t *mutex) { thread_mutex_init((thread_mutex_t *) mutex); }
void rl_mutex_destroy(rl_mutex_t *mutex) { thread_mutex_term((thread_mutex_t *) mutex); }
void rl_mutex_lock   (rl_mutex_t *mutex) { thread_mutex_lock((thread_mutex_t *) mutex); }
void rl_mutex_unlock (rl_mutex_t *mutex) { thread_mutex_unlock((thread_mutex_t *) mutex); }

#ifdef RL_THREADING_PLATFORM_FAKING
#undef __APPLE__
#endif
