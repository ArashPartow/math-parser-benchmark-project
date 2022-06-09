#include <time.h>

#ifdef _WIN32
#define timegm _mkgmtime
#define gmtime_r(t, tm) gmtime_s(tm, t)
#define localtime_r(t, tm) localtime_s(tm, t)
#endif

extern uint32_t get_time_ms();
extern double get_time_hr();
extern int32_t get_time_diff(uint32_t *t);
extern double get_time_diff_hr(double *t);
extern double convert_time_to_jd(time_t t);
extern double get_time_day_fraction(time_t t, int gmt);
extern void get_new_york_summer_time_bounds(int tm_year, time_t *start_t, time_t *end_t);
extern time_t new_york_time(time_t utc, struct tm *s);
extern time_t time_new_york(struct tm s);
extern time_t parse_date_time_string(const char *string);
extern double parse_date_time_string_hr(const char *string);
extern void sleep_ms(int ms);
extern void sleep_hr(double t);
extern void time_struct_minimise_elem(struct tm *ts, const int level);
extern time_t time_struct_local_get_next_period(struct tm ts0, const int level);
