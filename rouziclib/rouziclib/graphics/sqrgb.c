double ssqrgb(double s)	// converts a [0.0, 1.0] sRGB value into a [0.0, 1.0] squared value
{
	return sqrt(slrgb(s));
}

lut_t get_lut_ssqrgb()		// table is 8-bit sRGB to 12-bit sqrt of linear
{
	int32_t i;
	static int init=1;
	static lut_t ssqrgb_l;

	if (init)
	{
		init = 0;
		ssqrgb_l.lutint = calloc (ssqrgb_l.lut_size = 256, sizeof(int32_t));

		for (i=0; i<ssqrgb_l.lut_size; i++)
			ssqrgb_l.lutint[i] = sqrt(slrgb(((double) i / 255.))) * 4092. + 0.5;	// 4092 is the max for 12-bit so that >>2 makes it 10-bit (1023)
	}

	return ssqrgb_l;
}

sqrgb_t average_sqrgb_1(sqrgb_t a)	// average of 4 pixels, 3 of them are absent
{
	sqrgb_t sum;

	sum.r = a.r >> 1;	// sum = sqrt( a^2 / 4 ) = a / 2
	sum.g = a.g >> 1;
	sum.b = a.b >> 1;

	return sum;
}

sqrgb_t average_sqrgb_2(sqrgb_t a, sqrgb_t b)	// average of 4 pixels, 2 of them are absent
{
	sqrgb_t sum;

	sum.r = isqrt(a.r*a.r + b.r*b.r >> 2);
	sum.g = isqrt(a.g*a.g + b.g*b.g >> 2);
	sum.b = isqrt(a.b*a.b + b.b*b.b >> 2);

	return sum;
}

sqrgb_t average_sqrgb_4(sqrgb_t a, sqrgb_t b, sqrgb_t c, sqrgb_t d)
{
	sqrgb_t sum;

	sum.r = isqrt(a.r*a.r + b.r*b.r + c.r*c.r + d.r*d.r >> 2);
	sum.g = isqrt(a.g*a.g + b.g*b.g + c.g*c.g + d.g*d.g >> 2);
	sum.b = isqrt(a.b*a.b + b.b*b.b + c.b*c.b + d.b*d.b >> 2);

	return sum;
}
