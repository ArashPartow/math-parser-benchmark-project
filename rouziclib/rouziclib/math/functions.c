int32_t fphypot(int32_t x, int32_t y)
{
	return isqrt((int64_t) x*x + (int64_t) y*y);
}

double sq(double x)
{
	return x*x;
}

float sqf(float x)
{
	return x*x;
}

double cos_tr(double x)
{
	return cos(x * 2.*pi);
}

double sin_tr(double x)
{
	return sin(x * 2.*pi);
}

double gaussian(double x)	// gaussian(x) = e^-x²
{
	return exp(-x*x);
}

double erfr(double x)
{
	return 0.5 + 0.5*erf(x);
}

double integral_of_erfr(double x)
{
	return (x*erf(x) + gaussian(x)*(1./sqrt(pi)) + x) * 0.5;
}

double erfinv(double x)		// inverse of erf(x), erf(erfinv(x)) has a max deviation of 8.9e-16
{
	double x2, xm, xm2, y;

	x2 = x*x;
	if (x2 >= 1.)
		return NAN;

	// Map x
	xm = sqrt(-log(1. - x2));

	// Piecewise polynomial
	if (xm <= 1.62)
	{
		xm2 = xm*xm;
		y = ((((6.561773e-06*xm2 - 6.49954821e-05)*xm2 - 0.0002946924)*xm2 + 0.010456586618)*xm2 + 0.886226931376)*xm;
	}
	else if (xm <= 2.47)
		y = ((((0.001253835889*xm - 0.013610475845)*xm + 0.0520867309993)*xm - 0.06216894298)*xm + 0.93259984945)*xm - 0.013894847;
	else if (xm <= 4.18)
		y = ((((-0.0001917937307*xm + 0.00398741467763)*xm - 0.0340370215025)*xm + 0.149647086143)*xm + 0.6708154531)*xm + 0.11615653104;
	else
		y = ((-0.0002530447*xm + 0.0037429335)*xm + 0.991862495)*xm - 0.1713605;

	y = copysign(y, x);

	// Newton-Raphson step 
	y -= 0.5*sqrt(pi) * (erf(y) - x) / gaussian(y);

	return y;
}

double gamma_dist(double x, double a, double b)
{
	return pow(b, a) * pow(x, a-1.) * exp(-b*x) / tgamma(a);
}

double roundaway(double x)	// round away from 0
{
	if (x < 0.)
		return x-0.5;
	else
		return x+0.5;
}

double rangewrap(double x, double low, double high)
{
	double range;

	if (isnan(x))
		return x;

	range = high-low;

	while (x < low)
		x += range;

	while (x > high)
		x -= range;

	return x;
}

double rangelimit(double x, double min, double max)
{
	if (x < min)
		x = min;

	if (x > max)
		x = max;

	return x;
}

float rangelimitf(float x, float min, float max)
{
	if (x < min)
		x = min;

	if (x > max)
		x = max;

	return x;
}

int32_t rangelimit_i32(int32_t x, int32_t min, int32_t max)
{
	if (x < min)
		x = min;

	if (x > max)
		x = max;

	return x;
}

void minmax_double(double *a, double *b)
{
	if (*a > *b)
		swap_double(a, b);
}

void minmax_i32(int32_t *a, int32_t *b)
{
	if (*a > *b)
		swap_i32(a, b);
}

double normalised_notation_split(double number, double *m)	// splits number into m * 10^vexp
{
	int neg=0;
	double vexp, vm;

	if (number < 0.)
	{
		neg = 1;
		number = -number;
	}

	vexp = floor(log10(number));		// 16 million -> 7
	vm = number * pow(10., -vexp);		// 16 million -> 1.6
	if (neg)
		vm = -vm;

	if (m)
		*m = vm;

	return vexp;
}

double fabs_min(double a, double b)
{
	if (sign(a) != sign(b))
		return 0.;		// this gives the absolute minimum over the range

	if (fabs(a) < fabs(b))
		return a;
	else
		return b;
}

double fabs_max(double a, double b)
{
	if (fabs(a) > fabs(b))
		return a;
	else
		return b;
}

int ceil_rshift(int v, int sh)	// does the ceiling version of a right shift, for instance ceil_rshift(65, 3) => 9
{
	int mask = (1 << sh) - 1;

	return (v >> sh) + ((v & mask)!=0);
}

int idiv_ceil(int a, int b)	// 30 / 10 returns 3, 31 / 10 returns 4
{
	int d = a / b;

	if (d*b < a)
		d += 1;

	return d;
}

int find_largest_prime_factor(int n)
{
	int i = 2;

	while (n > 1)
	{
		if (n % i == 0)
			n /= i;
		else
			i++;
	}

	return i;
}

int is_prime(int n)
{
	int i;

	if (n <= 3)
		return n > 1;
	else if ((n % 2 == 0) || (n % 3) == 0)
		return 0;

	for (i=5; i*i <= n; i+=6)
		if ((n % i == 0) || (n % (i+2) == 0))
			return 0;

	return 1;
}

int next_prime(int n)
{
	while (is_prime(n)==0)
		n++;

	return n;
}

int64_t next_power_of_2(int64_t n)
{
	return sign(n) * (1ULL << log2_ffo64(llabs(n)));
}

int modulo_euclidian(int a, int b)	// gives a modulo that is never negative, as needed for circular buffers
{
	int m;

	m = a % b;

	if (m < 0)
		m = (b < 0) ? m - b : m + b;

	return m;
}

int find_closest_entry_double(double *array, int n, double v)	// in a double array find the entry with the value closest to v
{
	int i, index=-1;
	double d, min = DBL_MAX;

	for (i=0; i < n; i++)
	{
		d = fabs(v-array[i]);
		if (d < min)
		{
			min = d;
			index = i;
		}
	}

	return index;
}

double mix(double v0, double v1, double t)	// linear interpolation
{
	return v0 + (v1-v0)*t;
}

double get_interpolated_xy_array_value(double x, xy_t *array, size_t array_size)
{
	size_t i, step, smin, smax, smid;

	if (array==NULL || array_size < 1)
		return NAN;

	if (x <= array[0].x)
		return array[0].y;

	if (x >= array[array_size-1].x)
		return array[array_size-1].y;

	// Do a binary search of x
	step = next_power_of_2(array_size) >> 1;
	smin = 0;
	smax = array_size-1;

	while (step > 0)
	{
		smid = smin + step;
		smid = MINN(smid, smax);

		if (x < array[smid].x)
			smax = smid;
		else
			smin = smid;

		step >>= 1;
	}

	// Interpolate value
	for (i=MAXN(1, smin); i < array_size; i++)
		if (array[i].x > x)
			return mix(array[i-1].y, array[i].y, (x-array[i-1].x)/(array[i].x-array[i-1].x));

	return array[array_size-1].y;
}

double get_interpolated_xy_array_value_nan(double x, xy_t *array, size_t array_size)
{
	if (array==NULL || array_size < 1)
		return NAN;

	if (x <= array[0].x)
		return NAN;

	if (x >= array[array_size-1].x)
		return NAN;

	return get_interpolated_xy_array_value(x, array, array_size);
}

size_t get_latest_xy_array_index(double x, xy_t *array, size_t array_size)
{
	xy_t value = xy(x, 0.);
	return array_find_index_by_cmp(&value, array, array_size, sizeof(xy_t), cmp_xy_by_x);
}

double get_latest_xy_array_value(double x, xy_t *array, size_t array_size)
{
	return array[get_latest_xy_array_index(x, array, array_size)].y;
}
