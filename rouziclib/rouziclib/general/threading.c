#ifdef __EMSCRIPTEN__
#define RL_THREADING_PLATFORM_FAKING
#define __APPLE__
#endif

#ifdef _WIN32
// WinBase.h
#define INFINITE            0xFFFFFFFF
#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX

WINBASEAPI _Ret_maybenull_ HANDLE WINAPI CreateWaitableTimerA( _In_opt_ LPSECURITY_ATTRIBUTES lpTimerAttributes, _In_ BOOL bManualReset, _In_opt_ LPCSTR lpTimerName);
#ifndef UNICODE
#define CreateWaitableTimer  CreateWaitableTimerA
#endif

WINBASEAPI _Ret_maybenull_ HANDLE WINAPI CreateSemaphoreA( _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes, _In_ LONG lInitialCount, _In_ LONG lMaximumCount, _In_opt_ LPCSTR lpName);
#ifndef UNICODE
#define CreateSemaphore  CreateSemaphoreA
#endif

// winerror.h
#define ERROR_TIMEOUT                    1460L
#endif

#define THREAD_U64 uint64_t
#define THREAD_IMPLEMENTATION
#include "../libraries/orig/thread.h"

int rl_thread_detach(rl_thread_t thread)
{
	#ifdef _WIN32
	return CloseHandle((HANDLE) thread) != 0;

	#elif defined(NOT_WINDOWS)
	return pthread_detach((pthread_t) thread) == 0;

	#else 
	#error Unknown platform.
	#endif
}

void rl_thread_set_priority_low()
{
	#ifdef _WIN32
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);

	#elif defined(NOT_WINDOWS)
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

// Semaphores

void rl_sem_init(rl_sem_t *sem, int value)
{
	#ifdef _WIN32
	*sem = CreateSemaphore(NULL, value, INT_MAX, NULL);

	#elif defined(NOT_WINDOWS)
	sem_init(sem, 0, value);

	#else
	#error Unknown platform.
	#endif
}

void rl_sem_destroy(rl_sem_t *sem)
{
	#ifdef _WIN32
	CloseHandle(*sem);

	#elif defined(NOT_WINDOWS)
	sem_destroy(sem);

	#else
	#error Unknown platform.
	#endif
}

void rl_sem_wait(rl_sem_t *sem)
{
	#ifdef _WIN32
	WaitForSingleObject(*sem, INFINITE);

	#elif defined(NOT_WINDOWS)
	sem_wait(sem);

	#else
	#error Unknown platform.
	#endif
}

void rl_sem_post(rl_sem_t *sem)
{
	#ifdef _WIN32
	ReleaseSemaphore(*sem, 1, NULL);

	#elif defined(NOT_WINDOWS)
	sem_post(sem);

	#else
	#error Unknown platform.
	#endif
}

// Mutexes

int thread_mutex_trylock(thread_mutex_t *mutex)
{
	#ifdef _WIN32
	return TryEnterCriticalSection((CRITICAL_SECTION *) mutex) != 0;

	#elif defined(NOT_WINDOWS)
	return pthread_mutex_trylock((pthread_mutex_t *) mutex) == 0;

	#else
	#error Unknown platform.
	#endif
}

void rl_mutex_init   (rl_mutex_t *mutex) { thread_mutex_init((thread_mutex_t *) mutex); }
void rl_mutex_destroy(rl_mutex_t *mutex) { thread_mutex_term((thread_mutex_t *) mutex); }
void rl_mutex_lock   (rl_mutex_t *mutex) { thread_mutex_lock((thread_mutex_t *) mutex); }
int  rl_mutex_trylock(rl_mutex_t *mutex) { return thread_mutex_trylock((thread_mutex_t *) mutex); }
void rl_mutex_unlock (rl_mutex_t *mutex) { thread_mutex_unlock((thread_mutex_t *) mutex); }

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

// Atomics

int32_t rl_atomic_load_i32(volatile int32_t *ptr)
{
	#ifdef _WIN32
	return InterlockedCompareExchange(ptr, 0, 0);

	#elif defined(NOT_WINDOWS)
	return __atomic_load_n(ptr, __ATOMIC_ACQ_REL);

	#else
	#error Unknown platform.
	#endif
}

void rl_atomic_store_i32(volatile int32_t *ptr, int32_t value)
{
	#ifdef _WIN32
	InterlockedExchange(ptr, value);

	#elif defined(NOT_WINDOWS)
	__atomic_store_n(ptr, value, __ATOMIC_ACQ_REL);

	#else
	#error Unknown platform.
	#endif
}

int32_t rl_atomic_add_i32(volatile int32_t *ptr, int32_t value)
{
	#ifdef _WIN32
	return InterlockedExchangeAdd(ptr, value);

	#elif defined(NOT_WINDOWS)
	return __atomic_add_fetch(ptr, value, __ATOMIC_ACQ_REL);

	#else
	#error Unknown platform.
	#endif
}

int32_t rl_atomic_get_and_set(volatile int32_t *ptr, int32_t new_value)
{
	#ifdef _WIN32
	return InterlockedExchange(ptr, new_value);

	#elif defined(NOT_WINDOWS)
	return __atomic_exchange_n(ptr, new_value, __ATOMIC_ACQ_REL);

	#else 
	#error Unknown platform.
	#endif
}

#ifdef RL_THREADING_PLATFORM_FAKING
#undef __APPLE__
#endif
