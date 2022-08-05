// _Thread_local definition
#if defined(_MSC_VER) && !defined(_Thread_local)
    #define _Thread_local __declspec(thread)
#endif

#if !(defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201102L)) && !defined(_Thread_local)
    #if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
        #define _Thread_local __thread
    #endif
#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && (((__GNUC__ << 8) | __GNUC_MINOR__) < ((4 << 8) | 9))
    #define _Thread_local __thread
#endif

#if defined(__linux__) || defined(__APPLE__) || defined(__ANDROID__) || defined(__EMSCRIPTEN__)
    #define NOT_WINDOWS
    #include <errno.h>
    #include <unistd.h>
    #include <semaphore.h>
#endif

// Thread function prototypes from the original header
typedef void* rl_thread_t;
extern void thread_set_high_priority(void);
extern void thread_yield(void);
extern  int thread_join(rl_thread_t thread);
#define rl_thread_set_priority_high thread_set_high_priority
#define rl_thread_yield	thread_yield
#define rl_thread_join thread_join

// My original thread functions
extern int rl_thread_create(rl_thread_t *thread_handle, int (*func)(void *), void *arg);
extern int rl_thread_create_detached(int (*func)(void *), void *arg);
extern int rl_thread_join_and_null(rl_thread_t *thread_handle);
extern int rl_thread_detach(rl_thread_t thread);
extern void rl_thread_set_priority_low();

// Semaphores
#ifdef _WIN32
typedef HANDLE rl_sem_t;
#elif defined(NOT_WINDOWS)
typedef sem_t rl_sem_t;
#endif

extern void rl_sem_init(rl_sem_t *sem, int value);
extern void rl_sem_destroy(rl_sem_t *sem);
extern void rl_sem_wait(rl_sem_t *sem);
extern void rl_sem_post(rl_sem_t *sem);

// Mutexes
typedef union 
{	// copied from the original header's thread_mutex_t
	void *align; 
	char data[64];
} rl_mutex_t;

extern void rl_mutex_init(rl_mutex_t *mutex);
extern void rl_mutex_destroy(rl_mutex_t *mutex);
extern void rl_mutex_lock(rl_mutex_t *mutex);
extern  int rl_mutex_trylock(rl_mutex_t *mutex);
extern void rl_mutex_unlock(rl_mutex_t *mutex);
extern rl_mutex_t *rl_mutex_init_alloc();
extern void rl_mutex_destroy_free(rl_mutex_t **mutex);

// Atomics
extern int32_t rl_atomic_load_i32(volatile int32_t *ptr);
extern void rl_atomic_store_i32(volatile int32_t *ptr, int32_t value);
extern int32_t rl_atomic_add_i32(volatile int32_t *ptr, int32_t value);
extern int32_t rl_atomic_get_and_set(volatile int32_t *ptr, int32_t new_value);
