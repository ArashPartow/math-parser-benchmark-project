#ifdef _WIN32
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

uint32_t get_time_ms()
{
	return timeGetTime();
}

#else
#include <sys/types.h> 
#include <sys/time.h>

uint32_t get_time_ms()
{
	struct timeval now;

	gettimeofday(&now, NULL);

	return now.tv_sec * 1000 + now.tv_usec / 1000;
}

#endif

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#ifdef _WIN32
#include <profileapi.h>
#endif

double get_time_hr()	// High-resolution timing
{
	static double tick_dur = 0.;

	// Find the tick duration in seconds only once
	if (tick_dur==0.)
	{
		#ifdef _WIN32
		LARGE_INTEGER rate;
		QueryPerformanceFrequency(&rate);
		tick_dur = 1. / (double) rate.QuadPart;

		#elif __APPLE__
		mach_timebase_info_data_t rate_nsec;
		mach_timebase_info(&rate_nsec);
		tick_dur = 1e-9 * (double) rate_nsec.numer / (double) rate_nsec.denom;

		#else
		struct timespec rate;
		clock_getres(CLOCK_MONOTONIC_RAW, &rate);
		tick_dur = 1e-9 * (double) rate.tv_nsec;

		#endif
	}

	#ifdef _WIN32
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	return (double) now.QuadPart * tick_dur;

	#elif __APPLE__
	return (double) mach_absolute_time() * tick_dur;

	#elif __EMSCRIPTEN__
	return emscripten_get_now() * 1e-3;
	//return (double) get_time_ms() * 1e-3;		// Emscripten doesn't work well with my clock_gettime() code below

	#else
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	return (double) ((uint64_t) now.tv_sec*1000000000LL + now.tv_nsec) * tick_dur;
	#endif
}

// the caller should give a pointer to the old time value for it to be replaced with the new value, and the difference is returned
int32_t get_time_diff(uint32_t *t)
{
	uint32_t now, diff;

	now = get_time_ms();
	diff = now - *t;
	*t = now;

	return diff;
}

double get_time_diff_hr(double *t)
{
	double now, diff;

	now = get_time_hr();
	diff = now - *t;
	*t = now;

	return diff;
}

double convert_time_to_jd(time_t t)
{
	// reference time is January 1st, 2017 at 00:00:00 UTC, date of the latest leap second (see https://hpiers.obspm.fr/iers/bul/bulc/Leap_Second.dat)
	const double ref_jd = 2400000.5 + 57754.0;	// Julian date for the reference time
	const time_t ref_ut = 1483228800;		// Unix time for the reference time

	#ifdef _WIN32
	if (t >= 32535200000)
		t %= 32535200000;			// Windows doesn't like post year 3000 times
	#endif

	double dts = difftime(t, ref_ut);		// time in seconds since reference

	return ref_jd + dts / 86400.;			// Julian date for t
}

double get_time_day_fraction(time_t t, int gmt)
{
	struct tm *ts;

	#ifdef _WIN32
	if (t >= 32535200000)
		t %= 32535200000;	// Windows difftime() has a year 3001 bug
	#endif

	if (gmt)
		ts = gmtime(&t);
	else
		ts = localtime(&t);
	return (ts->tm_hour + (ts->tm_min + ts->tm_sec/60.)/60.) / 24.;
}

void get_new_york_summer_time_bounds(int tm_year, time_t *start_t, time_t *end_t)
{
	struct tm start_s={0}, end_s={0};

	// Find summer time start and end in Unix time
	start_s.tm_year = tm_year;	// same year
	start_s.tm_mon = 3-1;		// March
	start_s.tm_mday = 8;		// 8th
	start_s.tm_hour = 2;		// 2 am (winter time)

	end_s.tm_year = tm_year;	// same year
	end_s.tm_mon = 11-1;		// November
	end_s.tm_mday = 1;		// 1st
	end_s.tm_hour = 1;		// 1 am (winter time)

	// Get the day of the week
	*start_t = timegm(&start_s);
	*end_t = timegm(&end_s);
	gmtime_r(start_t, &start_s);
	gmtime_r(end_t, &end_s);

	// Find the next Sundays
	start_s.tm_mday += (7 - start_s.tm_wday) % 7;
	end_s.tm_mday += (7 - end_s.tm_wday) % 7;

	*start_t = timegm(&start_s);
	*end_t = timegm(&end_s);
}

time_t new_york_time(time_t utc, struct tm *s)		// only valid starting in 2007. s can be NULL
{
	time_t et = utc - 5*3600, start_t, end_t;
	struct tm ss;

	if (s==NULL)
		s = &ss;

	// Convert winter time to structure
	gmtime_r(&et, s);

	// Get start and end of summer time
	get_new_york_summer_time_bounds(s->tm_year, &start_t, &end_t);

	// Compare times to check for summer time
	if (et >= start_t && et < end_t)
	{
		et += 3600;
		gmtime_r(&et, s);
		s->tm_isdst = 1;
	}

	return et;
}

time_t time_new_york(struct tm s)		// Convert New York time to UTC time_t
{
	time_t et, utc, start_t, end_t;
	
	et = timegm(&s);
	utc = et + 5*3600;			// add 5 hours to convert to UTC

	// Get start and end of summer time
	get_new_york_summer_time_bounds(s.tm_year, &start_t, &end_t);

	// Subtract extra summer hour
	if (et >= start_t && et < end_t)
		utc -= 3600;

	return utc;
}

time_t parse_date_time_string(const char *string)	// expected format is "YYYY-MM-DD hh*mm*ss"
{
	struct tm ts={0};

	if (string==NULL)
		return 0;

	sscanf(string, "%d-%d-%d %d%*c%d%*c%d", &ts.tm_year, &ts.tm_mon, &ts.tm_mday, &ts.tm_hour, &ts.tm_min, &ts.tm_sec);

	ts.tm_year -= 1900;
	ts.tm_mon -= 1;

	return timegm(&ts);
}

double parse_date_time_string_hr(const char *string)	// expected format is "YYYY-MM-DD hh*mm*ss(.sss)"
{
	struct tm ts={0};
	time_t tt;
	double sec=0.;

	if (string==NULL)
		return 0;

	sscanf(string, "%d-%d-%d %d%*c%d%*c%lg", &ts.tm_year, &ts.tm_mon, &ts.tm_mday, &ts.tm_hour, &ts.tm_min, &sec);

	ts.tm_year -= 1900;
	ts.tm_mon -= 1;

	tt = timegm(&ts);

	return (double) tt + sec;
}

#ifdef _WIN32
#include <synchapi.h>
#endif

void sleep_ms(int ms)
{
	#ifdef _WIN32
	Sleep(ms);

	#elif __EMSCRIPTEN__
	emscripten_sleep(ms);

	#else
	struct timespec t;

	t.tv_sec  = ms / 1000;
	t.tv_nsec = (ms - t.tv_sec) * 1000000;

	nanosleep(&t, NULL);
	#endif
}

#ifdef _WIN32
#ifndef _NTDEF_
typedef _Return_type_success_(return >= 0) LONG NTSTATUS;	// taken from bcrypt.h
#endif

typedef NTSTATUS (NTAPI *NtDelayExecution_func)(BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);
NtDelayExecution_func NtDelayExecution;
typedef NTSTATUS (NTAPI *ZwSetTimerResolution_func)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution);
ZwSetTimerResolution_func ZwSetTimerResolution;

#include <libloaderapi.h>
#endif

void sleep_hr(double t)
{
	#ifdef _WIN32
	static int init=1;

	if (init)
	{
		NtDelayExecution = (NtDelayExecution_func) GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution");
		ZwSetTimerResolution = (ZwSetTimerResolution_func) GetProcAddress(GetModuleHandleA("ntdll.dll"), "ZwSetTimerResolution");
		ULONG actualResolution;
		ZwSetTimerResolution(1, TRUE, &actualResolution);
		init = 0;
	}

	LARGE_INTEGER interval;
	interval.QuadPart = -1e7 * t;
	NtDelayExecution(FALSE, &interval);

	#elif __EMSCRIPTEN__
	emscripten_sleep(nearbyint(t * 1000.));

	#else
	struct timespec ts;

	ts.tv_sec  = t;
	ts.tv_nsec = (t - (double) ts.tv_sec) * 1e9;

	nanosleep(&ts, NULL);
	#endif
}

void time_struct_minimise_elem(struct tm *ts, const int level)
{
	// Set DST to unknown to handle DST changes properly
	ts->tm_isdst = -1;

	// Set the elements to their lowest value depending on the given level
	switch (level)
	{
		case 5: ts->tm_mon = 0;
		case 4: ts->tm_mday = 1;
		case 3: ts->tm_hour = 0;
		case 2: ts->tm_min = 0;
		case 1: ts->tm_sec = 0;
	}
}

time_t time_struct_local_get_next_period(struct tm ts0, const int level)
{
	struct tm ts1 = ts0, ts1_copy;
	time_t tt0, tt1;
	int isdst;

	// Convert to time_t
	tt0 = mktime(&ts0);
	tt1 = tt0;

	// Over-increment based on the level
	switch (level)
	{
			case 5:	tt1 += 367 * 24 * 3600;
		break;	case 4: tt1 += 33 * 24 * 3600;
		break;	case 3: tt1 += 25 * 3600 + 1;
		break;	case 2: tt1 += 3601;
		break;	case 1: tt1 += 61;
		break;	case 0: tt1 += 1;
	}

	// Convert over-incremented time to struct tm
	localtime_r(&tt1, &ts1);

	// Take care of fall DST change (albeit not quite right)
	if (level <= 2 && ts0.tm_isdst > ts1.tm_isdst)
		ts1.tm_isdst = 0;

	// Set to the lowest level to set the incrementation just right
	isdst = ts1.tm_isdst;
	time_struct_minimise_elem(&ts1, level);
	ts1.tm_isdst = isdst;

	return mktime(&ts1);
}
