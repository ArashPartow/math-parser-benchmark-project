#ifdef RL_LIBJPEG

jpeg_comp_dct_t *libjpeg_get_dct_data(const char *filepath)
{
	int ic, ret;
	xyi_t ib;
	uint8_t *filedata;
	size_t filedata_size;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	jvirt_barray_ptr *coefs;
	jpeg_comp_dct_t *out=NULL;
	JBLOCKARRAY dct;
	jpeg_component_info *compinf;

	filedata = load_raw_file(filepath, &filedata_size);
	if (filedata==NULL)
		return NULL;

	// allocate and initialize JPEG decompression object
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, filedata, filedata_size);
	//jpeg_stdio_src(&cinfo, file);		// specify file

	ret = jpeg_read_header(&cinfo, TRUE);	// read file header
	if (ret != 1)
		fprintf_rl(stderr, "File '%s' cannot be read by jpeg_read_header()\n", filepath);
	else
	{
		coefs = jpeg_read_coefficients(&cinfo);	// read all the coefs (DCT, quantisation table etc)

		if (coefs)
		{
			out = calloc(3, sizeof(jpeg_comp_dct_t));

			// copy every DCT block and the quantisation table for every component
			for (ic=0; ic<3; ic++)
			{
				compinf = &cinfo.comp_info[ic];
				out[ic].image_dim = xyi(cinfo.image_width, cinfo.image_height);
				out[ic].block_dim = xyi(compinf->width_in_blocks, compinf->height_in_blocks);
				dct = (cinfo.mem->access_virt_barray) ((j_common_ptr) (&cinfo), coefs[ic], 0, compinf->v_samp_factor, FALSE);

				memcpy(out[ic].quant, compinf->quant_table->quantval, DCTSIZE2 * sizeof(uint16_t));	// copy quantisation table

				// copy DCT blocks
				out[ic].dct_block = calloc(mul_x_by_y_xyi(out[ic].block_dim), sizeof(int16_t *));
				for (ib.y=0; ib.y < out[ic].block_dim.y; ib.y++)
					for (ib.x=0; ib.x < out[ic].block_dim.x; ib.x++)
					{
						out[ic].dct_block[ib.y * out[ic].block_dim.x + ib.x] = calloc(DCTSIZE2, sizeof(int16_t));
						memcpy(out[ic].dct_block[ib.y * out[ic].block_dim.x + ib.x], dct[ib.y][ib.x], DCTSIZE2 * sizeof(int16_t));
					}
			}
		}
	}

	// free the libjpeg stuff
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	free(filedata);

	return out;
}

void free_jpeg_comp_dct(jpeg_comp_dct_t *data)
{
	int ic;

	if (data==NULL)
		return ;

	for (ic=0; ic<3; ic++)
		free_2d(data[ic].dct_block, mul_x_by_y_xyi(data[ic].block_dim));

	free(data);
}

float *decode_jpeg_dct(jpeg_comp_dct_t *data, xyi_t *decoded_dim)	// decoded_dim is multiple of 8x8, >= image_dim
{
	int i, block_start;
	xyi_t ib, ip;
	float *im;
	double freq_block[64], quant_block[64];

	*decoded_dim = mul_xyi(data->block_dim, xyi(8,8));

	im = calloc(mul_x_by_y_xyi(*decoded_dim), sizeof(float));

	for (i=0; i<64; i++)
		quant_block[i] = data->quant[i];

	for (ib.y=0; ib.y < data->block_dim.y; ib.y++)
		for (ib.x=0; ib.x < data->block_dim.x; ib.x++)
		{
			block_start = ib.y * data->block_dim.x + ib.x;

			for (i=0; i<64; i++)
				freq_block[i] = (double) data->dct_block[block_start][i] * quant_block[i];

			block_start = ib.y * data->block_dim.x*64 + ib.x*8;

			for (ip.y=0; ip.y<8; ip.y++)
				for (ip.x=0; ip.x<8; ip.x++)
					im[block_start + ip.y*decoded_dim->x + ip.x] = slrgb(dct_type_III_cell(freq_block, ip) * (1./255.));
		}

	return im;
}

void copy_convert_8x8_block(float *im, xyi_t dim, xyi_t ib, double *block)	// extracts a linear 8x8 block from array, convert to 0-255 gamma-compressed range
{
	int block_start;
	xyi_t ip;

	block_start = ib.y*8 * dim.x + ib.x*8;

	for (ip.y=0; ip.y<8; ip.y++)
		for (ip.x=0; ip.x<8; ip.x++)
			block[ip.y*8 + ip.x] = lsrgb(im[block_start + ip.y*dim.x + ip.x]) * 255.;
}

void paste_convert_8x8_block(float *im, xyi_t dim, xyi_t ib, double *block)	// paste a 0-255 gamma block into the linear array
{
	int block_start;
	xyi_t ip;

	block_start = ib.y*8 * dim.x + ib.x*8;

	for (ip.y=0; ip.y<8; ip.y++)
		for (ip.x=0; ip.x<8; ip.x++)
			im[block_start + ip.y*dim.x + ip.x] = slrgb(block[ip.y*8 + ip.x] * (1./255.));
}

raster_t load_image_mem_libjpeg(uint8_t *raw_data, size_t size, const int mode)
{
	struct jpeg_decompress_struct cinfo={0};
	struct jpeg_error_mgr jerr;
	int ret;
	xyi_t ip;
	raster_t im={0};
	uint8_t *scanline, *p0, *p1;

	// allocate and initialize JPEG decompression object
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	jpeg_mem_src(&cinfo, raw_data, size);

	ret = jpeg_read_header(&cinfo, TRUE);	// read file header
	if (ret != 1)
	{
		fprintf_rl(stderr, "Image cannot be read by jpeg_read_header()\n");
	}
	else
	{
		jpeg_calc_output_dimensions(&cinfo);

		im = make_raster(NULL, xyi(cinfo.output_width, cinfo.output_height), XYI0, IMAGE_USE_SRGB);
		scanline = malloc(cinfo.output_width * cinfo.output_components);

		jpeg_start_decompress(&cinfo);

		for (ip.y=0; ip.y < im.dim.y; ip.y++)
		{
			jpeg_read_scanlines(&cinfo, &scanline, 1);

			for (ip.x=0; ip.x < im.dim.x; ip.x++)
			{
				p0 = &scanline[ip.x * cinfo.output_components];
				p1 = &im.srgb[ip.y*im.dim.x + ip.x];
				p1[0] = p0[0];
				p1[1] = p0[1];
				p1[2] = p0[2];
			}
		}

		free(scanline);
	}

	// free the libjpeg stuff
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	convert_image_srgb8(&im, im.srgb, mode);		// fills all the necessary buffers with the image data

	return im;
}

#endif

int check_data_is_jpeg(uint8_t *raw_data, size_t size)
{
	if (size < 3)
		return 0;

	return memcmp(raw_data, "\xFF\xD8\xFF", 3) == 0;
}

raster_t load_image_mem_libjpeg_if_possible(uint8_t *raw_data, size_t size, const int mode)
{
	#ifdef RL_LIBJPEG
	if (check_data_is_jpeg(raw_data, size))
		return load_image_mem_libjpeg(raw_data, size, mode);
	else
		return load_image_mem_lib(NULL, raw_data, size, mode);
	#else
	return load_image_mem_lib(NULL, raw_data, size, mode);
	#endif
}
