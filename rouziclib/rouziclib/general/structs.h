typedef struct
{
	int32_t init;	// TODO remove
	int32_t i, lut_size;
	double lut_range, lut_range_inv;
	double mul, add;
	double *lut;
	float *flut;
	int32_t *lutint;	// same as lut except in fixed point format
	uint8_t *lutb;		// for values from 0 to 255 (like sRGB colours)
} lut_t;

typedef struct
{
	uint8_t *buf;
	size_t as, len;		// len for strings excludes the nul end character
} buffer_t;

typedef struct
{
	double hi, lo;
} ddouble_t;
