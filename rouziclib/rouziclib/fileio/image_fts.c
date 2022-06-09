int is_file_fts_mem(uint8_t *data)
{
	// Check the beginning of the file
	if (strcmp_len2(data, "SIMPLE  =")==0)
		return 1;
	return 0;
}

double fts_read_double(uint8_t *data, const char *field_name)
{
	const char *p;
	double v=NAN;

	p = strstr_after(data, field_name);
	if (p)
		sscanf(p, " = %lg", &v);
	return v;
}

int fts_read_int(uint8_t *data, const char *field_name)
{
	const char *p;
	int v=-1;

	p = strstr_after(data, field_name);
	if (p)
		sscanf(p, " = %d", &v);
	return v;
}

float *load_fts_mem(uint8_t *data, const size_t data_size, xyi_t *dim, int *out_chan)
{
	int i, bit_depth;
	float *im, black_level, max_level, gain, v;
	const uint8_t *p8;
	const uint16_t *p16;
	const uint32_t *p32;
	xyi_t ip;

	// Read fields
	dim->x = fts_read_int(data, "NAXIS1");
	dim->y = fts_read_int(data, "NAXIS2");
	bit_depth = fts_read_int(data, "BITPIX");
	black_level = fts_read_double(data, "DATAMIN");
	max_level = fts_read_double(data, "DATAMAX");
	gain = 1.f / (max_level - black_level);

	if (*out_chan <= 0)			// 0 loads whatever number of channels there is
		*out_chan = 1;

	// Find pixel data start
	p8 = strstr_after(data, " END ");
	if (p8==NULL)
		return NULL;

	for (i=0; i < data_size; i++)
		if (p8[i] != ' ')
		{
			p8 = &p8[i];
			break;
		}
	p16 = (uint16_t *) p8;
	p32 = (uint32_t *) p8;

	if (p8[0] == ' ')
		return NULL;

	// Allocate
	im = calloc(mul_x_by_y_xyi(*dim) * *out_chan, sizeof(float));

	// Convert pixels
	if (bit_depth==16)
	{
		for (ip.y=0; ip.y < dim->y; ip.y++)
			for (ip.x=0; ip.x < dim->x; ip.x++)
			{
				if ((void *) &p16[ip.y*dim->x + ip.x] < (void *) &data[data_size])
					v = (float) read_BE16(&p16[ip.y*dim->x + ip.x], NULL);
				else
					v = black_level;

				v = (v - black_level) * gain;
				image_float_channel_conversion(&v, 1, &im[(ip.y*dim->x + ip.x) * *out_chan], *out_chan);
			}
	}

	if (bit_depth==32)
	{
		for (ip.y=0; ip.y < dim->y; ip.y++)
			for (ip.x=0; ip.x < dim->x; ip.x++)
			{
				if ((void *) &p32[ip.y*dim->x + ip.x] < (void *) &data[data_size])
					v = (float) read_BE32(&p32[ip.y*dim->x + ip.x], NULL);
				else
					v = black_level;

				v = (v - black_level) * gain;
				image_float_channel_conversion(&v, 1, &im[(ip.y*dim->x + ip.x) * *out_chan], *out_chan);
			}
	}

	return im;
}

raster_t load_fts_mem_raster(uint8_t *data, const size_t data_size)
{
	float *im;
	xyi_t dim={0};
	int out_chan=4;

	im = load_fts_mem(data, data_size, &dim, &out_chan);

	return make_raster(im, dim, XYI0, IMAGE_USE_FRGB);
}
