int is_composite(int x)  // returns 1 if x is only made of these small primes
{
	int i;
	const int p[3]={2, 3, 5};

	for (i=0; i<3; i++)
		while (x%p[i] == 0)
			x/=p[i];

	return x;
}

int next_composite(int x)   // returns the next integer only made of small primes
{
	while (is_composite(x)!=1)
		x++;

	return x;
}

int next_fast_fft_size(int x)	// returns the next size >= x with which a FFT runs with the lowest execution time 
{
	const int fft_size[] = {60, 64, 72, 75, 80, 100, 120, 125, 128, 135, 144, 150, 160, 180, 200, 225, 240, 256, 300, 320, 375, 400, 405, 432, 500, 512, 540, 576, 625, 640, 648, 720, 768, 800, 810, 864, 900, 960, 1000, 1080, 1152, 1200, 1280, 1296, 1350, 1440, 1500, 1600, 1620, 1728, 1800, 1920, 2000, 2025, 2160, 2304, 2400, 2560, 2700, 2880, 3000, 3200, 3375, 3600, 3840, 4000, 4050, 4320, 4500, 4800, 5120, 5184, 5400, 5625, 6000, 6400, 6480, 6912, 7200, 7500, 8000, 8100, 8640, 8748, 9000, 9375, 9600, 10000, 10368, 10800, 10935, 11520, 12500, 12960, 13500, 13824, 14400, 14580, 15000, 15625, 16000, 16200, 17280, 18000, 19200, 19440, 20000, 20736, 21600, 23040, 24000, 24300, 25920, 27000, 28800, 30000, 30375, 32000, 32400, 34560, 36000, 38400, 40000, 40500, 43200, 45000, 46080, 48000, 50000, 50625, 51840, 54000, 57600, 60000, 62500, 64000, 
		67500, 72000, 72900, 75000, 80000, 84375, 90000, 96000, 97200, 100000, 103680, 104976, 112500, 120000, 125000, 129600, 131220, 140625, 150000, 160000, 162000, 164025, 174960, 187500, 200000, 202500, 207360, 216000, 218700, 234375, 250000, 259200, 270000, 273375, 291600, 312500, 324000, 337500, 345600, 360000, 364500, 390625, 405000, 421875, 432000, 450000, 455625, 486000, 518400, 540000, 562500, 576000, 607500, 648000, 675000, 703125, 720000, 759375, 781250, 800000, 810000, 843750, 864000, 900000, 937500, 1000000, 1012500, 1080000, 1125000, 1171875, 1200000, 1250000, 1265625, 1280000, 1350000, 1406250, 1440000, 1500000, 1562500, 1600000, 1687500, 1875000, 2000000, 2109375, 2250000, 2343750, 2400000, 2500000, 2531250, 2812500, 3125000, 3200000, 3515625, 3750000, 3906250, 4000000, 4100625, 4687500, 5000000, 5062500, 5184000, 5400000, 5467500, 5859375, 6250000, 6328125, 6480000, 6561000, 6635520};

	const int count = sizeof(fft_size) / sizeof(fft_size[0]);
	int i;

	for (i=0; i < count; i++)
		if (fft_size[i] >= x)
			return fft_size[i];

	return next_composite(x);	// if the requested size is larger than the largest table entry then find the next suitable composite number
}

xyi_t calc_2D_fast_convolution_dim(xyi_t a, xyi_t b)
{
	return func1_xyi( sub_xyi(add_xyi(a, b), set_xyi(1)) , next_fast_fft_size );
}

float array_sumf(float *s, const size_t n)
{
	size_t i;
	float sum=0.f;

	for (i=0; i < n; i++)
		sum += s[i];

	return sum;
}

double array_sum(double *s, const size_t n)
{
	size_t i;
	double sum=0.;

	for (i=0; i < n; i++)
		sum += s[i];

	return sum;
}

float array_sum_sqf(float *s, const size_t n)
{
	size_t i;
	float sum=0.f;

	for (i=0; i < n; i++)
		sum += sqf(s[i]);

	return sum;
}

double array_sum_sq(double *s, const size_t n)
{
	size_t i;
	double sum=0.;

	for (i=0; i < n; i++)
		sum += sq(s[i]);

	return sum;
}

float root_mean_squaref(float *s, const size_t n)
{
	return sqrtf(array_sum_sqf(s, n) / (float) n);
}

double root_mean_square(double *s, const size_t n)
{
	return sqrt(array_sum_sq(s, n) / (double) n);
}

float root_mean_squaref_chan(float *s, const size_t n, const int ic, const int chan_count)
{
	size_t i;
	float sum=0.f;

	for (i=ic; i < n*chan_count; i+=chan_count)
		sum += sqf(s[i]);

	return sqrtf(sum / (float) n);
}

double db_to_vol(double db)
{
	return pow(10., db / 20.);
}

double vol_to_db(double vol)
{
	return 20. * log10(vol);
}

double sinc(double x, double fc)		// fc is the cutoff frequency as a multiple of the sampling frequency
{
	double a;

	if (x==0.)
		return 1.;

	a = 2.*pi * x*fc;
	return sin(a)/(a);
}

double blackman(double x, double range)		// spans ]-range , +range[
{
	x /= range;
	ffabs(&x);

	if (x >= 1.)
		return 0.;

	x = pi * x;

	return 0.42 + 0.5*cos(x) + 0.08*cos(2.*x);
}

double short_gaussian_window(double x, double range, double w)	// x = ]-range , +range[, w is the sigma span of the gaussian, high w means more gaussian and thin
{
	x /= range;
	ffabs(&x);

	if (x >= 1.)
		return 0.;

	w *= 0.7071067811865475244;		// scale w so that the given value matches the sigma of a regular gaussian function

	if (w < 1e-4)
		return sq(1. - sq(x));		// squared parabola window

	return sq(gaussian(x*w) - gaussian(w)) / sq(1. - gaussian(w));
}

double short_erf(double x, double w)
{
	x = rangelimit(x, -w, w);
	x *= sqrt(0.5);
	w *= sqrt(0.5);

	// Normalised integral of (exp(-x^2) - exp(-w^2))^2
	return ( sqrt(pi) * exp(w*w) * (sqrt(2.) * exp(w*w) * erf(sqrt(2.) * x) - 4.*erf(x)) + 4. * x )
	     / ( sqrt(pi) * exp(w*w) * (sqrt(2.) * exp(w*w) * erf(sqrt(2.) * w) - 4.*erf(w)) + 4. * w );
}

double cumulative_squared_parabola(double x)	// integral of the squared parabola window, like a shorter erf()
{
	double x2;
	x = rangelimit(x, -1., 1.);
	x2 = x*x;
	return ((0.375*x2 - 1.25)*x2 + 1.875)*x;
}

double cumulative_cubed_parabola(double x)	// integral of the cubed parabola window (1-x^2)^3
{
	double x2;
	x = rangelimit(x, -1., 1.);
	x2 = x*x;
	return (((-0.3125*x2 + 1.3125)*x2 - 2.1875)*x2 + 2.1875)*x;
}

double ramp_kernel(double x)
{
	if (x==0.)
		return 0.25;

	return 0.5*sin(pi*x)/(pi*x) - 0.25*sq(sin(pi*x*0.5)/(pi*x*0.5));
}

double ramp_kernel_discrete(int x)
{
	if (x==0)
		return 0.25;

	if (x&1)
		return -1. / sq((double) x * pi);

	return 0.;
}
