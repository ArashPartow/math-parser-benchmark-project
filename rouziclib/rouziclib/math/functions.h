#define RL_PI 3.1415926535897931
#define pi RL_PI

#define sign(x)		(((x) > 0) - ((x) < 0))
#define MAXN(x, y)	(((x) > (y)) ? (x) : (y))
#define MINN(x, y)	(((x) < (y)) ? (x) : (y))

extern int32_t fphypot(int32_t x, int32_t y);
extern double sq(double x);
extern float sqf(float x);
extern double cos_tr(double x);
extern double sin_tr(double x);
extern double gaussian(double x);
extern double erfr(double x);
extern double integral_of_erfr(double x);
extern double erfinv(double x);
extern double gamma_dist(double x, double a, double b);

extern double roundaway(double x);
extern double rangewrap(double x, double low, double high);
extern double rangelimit(double x, double min, double max);
extern float rangelimitf(float x, float min, float max);
extern int32_t rangelimit_i32(int32_t x, int32_t min, int32_t max);
extern void minmax_double(double *a, double *b);
extern void minmax_i32(int32_t *a, int32_t *b);
extern double normalised_notation_split(double number, double *m);
extern double fabs_min(double a, double b);
extern double fabs_max(double a, double b);
extern int ceil_rshift(int v, int sh);
extern int idiv_ceil(int a, int b);
extern int find_largest_prime_factor(int n);
extern int is_prime(int n);
extern int next_prime(int n);
extern int64_t next_power_of_2(int64_t n);
extern int modulo_euclidian(int a, int b);
extern int find_closest_entry_double(double *array, int n, double v);
extern double mix(double v0, double v1, double t);
extern double get_interpolated_xy_array_value(double x, xy_t *array, size_t array_size);
extern double get_interpolated_xy_array_value_nan(double x, xy_t *array, size_t array_size);
extern size_t get_latest_xy_array_index(double x, xy_t *array, size_t array_size);
extern double get_latest_xy_array_value(double x, xy_t *array, size_t array_size);
