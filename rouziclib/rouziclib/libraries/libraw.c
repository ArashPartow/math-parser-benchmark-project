#ifdef RL_LIBRAW

rawphoto_t init_rawphoto(int32_t width, int32_t height)
{
	rawphoto_t rp;

	memset(&rp, 0, sizeof(rawphoto_t));

	rp.dim.x = width;
	rp.dim.y = height;
	rp.data = calloc(rp.dim.x*rp.dim.y, sizeof(*rp.data));

	return rp;
}

void free_rawphoto(rawphoto_t *rp)
{
	free (rp->data);
	free_raster(&rp->preview);

	memset(rp, 0, sizeof(rawphoto_t));
}

raster_t load_raw_thumb(libraw_data_t *rd)
{
	int ret;
	libraw_processed_image_t *proc_image;
	raster_t r={0};

	ret = libraw_unpack_thumb(rd);
	if (ret)
	{
		fprintf_rl(stderr, "libraw %s\n", libraw_strerror(ret));
		return make_raster_empty();
	}

	proc_image = libraw_dcraw_make_mem_thumb(rd, &ret);
	if (ret)
		fprintf_rl(stderr, "libraw %s\n", libraw_strerror(ret));
	else if (proc_image->type == LIBRAW_IMAGE_JPEG)
	{
		r = load_image_mem(proc_image->data, proc_image->data_size, IMAGE_USE_FRGB);
	}
	else if (proc_image->colors!=3 || proc_image->bits!=8)
	{
		fprintf_rl(stderr, "Wrong decoded thumbnail format, %d %d-bit channels, type %d\n", proc_image->colors, proc_image->bits, proc_image->type);
		r = make_raster_empty();
	}
	else
	{
		r = make_raster(NULL, xyi(proc_image->width, proc_image->height), XYI0, IMAGE_USE_FRGB);
		free_null(&r.f);
		convert_image_srgb8(&r, proc_image->data, IMAGE_USE_FRGB);
	}

	libraw_dcraw_clear_mem(proc_image);

	return r;
}

rawphoto_t load_raw_photo_bayered(char *path, int load_thumb)
{
	int i, ret;
	rawphoto_t rp={0};
	libraw_data_t *rd = libraw_init(0);
	uint8_t *raw_data;
	size_t raw_data_size;

	raw_data = load_raw_file(path, &raw_data_size);
	if (raw_data==NULL)
	{
		fprintf_rl(stderr, "Could not open image %s\n", path);
		return rp;
	}

	//ret = libraw_open_file(rd, path);
	ret = libraw_open_buffer(rd, raw_data, raw_data_size);
	//free (raw_data);
	if (ret)
	{
		fprintf_rl(stderr, "%s: libraw %s\n", path, libraw_strerror(ret));
		return rp;
	}

	//fprintf_rl(stdout, "Processing %s (%s %s)\n", path, rd->idata.make, rd->idata.model);

	ret = libraw_unpack(rd);
	if (ret)
		fprintf_rl(stderr, "%s: libraw %s\n", path, libraw_strerror(ret));

	// copy the wanted data
	rp = init_rawphoto(rd->rawdata.sizes.raw_width, rd->rawdata.sizes.raw_height);
	memcpy(rp.data, rd->rawdata.raw_image, rp.dim.x*rp.dim.y * sizeof(uint16_t));

	if (load_thumb)
		rp.preview = load_raw_thumb(rd);

	rp.image_area = make_rect_off( xy(rd->rawdata.sizes.left_margin, rd->rawdata.sizes.top_margin), xy(rd->rawdata.sizes.iwidth-1, rd->rawdata.sizes.iheight-1), XY0 );
	rp.image_centre = get_rect_centre(rp.image_area);

	// white balance
	rp.wb = xyz(rd->color.cam_mul[0], (rd->color.cam_mul[1]+rd->color.cam_mul[3])*0.5, rd->color.cam_mul[2]);
	rp.wb = div_xyz(rp.wb, set_xyz(min_of_xyz(rp.wb)));

	// black levels
	for (i=0; i < 4; i++)
		rp.bayer_black[i] = rd->color.black + rd->color.cblack[i];

	// colour invert matrix
	for (i=0; i < 9; i++)
		rp.inv_matrix[i] = rd->color.rgb_cam[i%3][i/3];

	rp.maximum_value = rd->color.maximum;

	fprintf_rl(stdout, "wb: %g %g %g\n", rp.wb.x, rp.wb.y, rp.wb.z);
	fprintf_rl(stdout, "Focal length: %g mm (%gx)\n", rd->other.focal_len, rd->other.focal_len/rd->lens.makernotes.MinFocal);
	if (rd->other.shutter > 0.26)
		fprintf_rl(stdout, "Shutter speed %g sec, ", rd->other.shutter);
	else
		fprintf_rl(stdout, "Shutter speed 1/%g sec, ", 1./rd->other.shutter);
	fprintf_rl(stdout, "F%.1f, ISO %g\n", rd->lens.makernotes.CurAp, rd->other.iso_speed);

	libraw_close(rd);

	return rp;
}

raster_t raw_photo_to_raster(rawphoto_t rp)
{
	int i, bayer_ind, col_ind;
	double vl, v, v_scale[4];
	raster_t r;
	xyi_t ip, im_p0 = xy_to_xyi(rp.image_area.p0), im_p1 = xy_to_xyi(rp.image_area.p1);
	xyi_t im_dim = xy_to_xyi(get_rect_dim(rp.image_area));
	double H, S, L;

	if (rp.data==NULL)
		return make_raster_empty();

	r = make_raster(NULL, add_xyi(im_dim, set_xyi(1)), XYI0, IMAGE_USE_FRGB);

	for (bayer_ind=0; bayer_ind < 4; bayer_ind++)
		v_scale[bayer_ind] = 1. / (rp.maximum_value-rp.bayer_black[bayer_ind]);

	for (ip.y=im_p0.y; ip.y <= im_p1.y; ip.y++)
		for (ip.x=im_p0.x; ip.x <= im_p1.x; ip.x++)
		{
			bayer_ind = (ip.x&1) + ((ip.y&1) << 1);
			col_ind = bayer_ind - (bayer_ind>>1);

			vl = rp.data[ip.y * rp.dim.x + ip.x];
			v = (vl - rp.bayer_black[bayer_ind]) * v_scale[bayer_ind];// * get_xyz_index(rp.wb, col_ind);// * gain;

			set_frgb_channel(&r.f[(ip.y-im_p0.y) * r.dim.x + (ip.x-im_p0.x)], col_ind, v * (col_ind==1 ? 2. : 4.));
		}

	// Demosaicing by +0.5 offset
	frgb_t *new_f = calloc(mul_x_by_y_xyi(r.dim), sizeof(frgb_t));
	for (ip.y=0; ip.y < r.dim.y-1; ip.y++)
		for (ip.x=0; ip.x < r.dim.x-1; ip.x++)
			new_f[ip.y*r.dim.x + ip.x] = mul_scalar_frgb(add_frgb(add_frgb(r.f[ip.y*r.dim.x + ip.x], r.f[ip.y*r.dim.x + ip.x+1]), add_frgb(r.f[(ip.y+1)*r.dim.x + ip.x], r.f[(ip.y+1)*r.dim.x + ip.x+1])), 0.25f);
	free(r.f);
	r.f = new_f;

	//gaussian_blur(r.f, r.f, r.dim, 4, 1.4);

/*	for (ip.y=im_p0.y; ip.y <= im_p1.y; ip.y++)
		for (ip.x=im_p0.x; ip.x <= im_p1.x; ip.x++)
		{
			bayer_ind = (ip.x&1) + ((ip.y&1) << 1);
			col_ind = bayer_ind - (bayer_ind>>1);

			vl = rp.data[ip.y * rp.dim.x + ip.x];
			v = (vl - rp.bayer_black[bayer_ind]) / (rp.maximum_value-rp.bayer_black[bayer_ind]) * get_xyz_index(rp.wb, col_ind);// * gain;

			frgb_to_hsl(r.f[(ip.y-im_p0.y) * r.dim.x + (ip.x-im_p0.x)], &H, &S, &L, HUEDEG);
			r.f[(ip.y-im_p0.y) * r.dim.x + (ip.x-im_p0.x)] = hsl_to_frgb(H, S, v / get_frgb_channel(hsl_to_frgb(H, S, 1., HUEDEG, 0), col_ind) , HUEDEG, 0);

			//set_frgb_channel(&r.f[(ip.y-im_p0.y) * r.dim.x + (ip.x-im_p0.x)], col_ind, v * (col_ind==1 ? 2. : 4.));
		}*/

	return r;
}

raster_t load_raw_photo_dcraw_proc(char *path)
{
	int i, ic, ret;
	rawphoto_t rp={0};
	libraw_data_t *rd = libraw_init(0);
	uint8_t *raw_data;
	size_t raw_data_size;
	libraw_processed_image_t *proc_image;
	raster_t r={0};

	raw_data = load_raw_file(path, &raw_data_size);
	if (raw_data==NULL)
	{
		fprintf_rl(stderr, "Could not open image %s\n", path);
		return r;
	}

	//ret = libraw_open_file(rd, path);
	ret = libraw_open_buffer(rd, raw_data, raw_data_size);
	//free (raw_data);
	if (ret)
	{
		fprintf_rl(stderr, "%s: libraw %s\n", path, libraw_strerror(ret));
		return r;
	}

	//fprintf_rl(stdout, "Processing %s (%s %s)\n", path, rd->idata.make, rd->idata.model);

	ret = libraw_unpack(rd);
	if (ret)
		fprintf_rl(stderr, "%s: libraw %s\n", path, libraw_strerror(ret));

	libraw_set_output_bps(rd, 16);
	rd->params.use_camera_wb  = 1;
	libraw_set_output_color(rd, 1); // 0 = raw, 1 = sRGB
	libraw_set_gamma(rd, 0, 1.f);
	libraw_set_gamma(rd, 1, 1.f);
	libraw_set_highlight(rd, 0); // 0 = clip
	libraw_set_no_auto_bright(rd, 0);
	libraw_set_demosaic(rd, 2); // 2 = PPG, 11 = DHT

	ret = libraw_dcraw_process(rd);
	if (ret)
		fprintf_rl(stderr, "libraw %s\n", libraw_strerror(ret));

	proc_image = libraw_dcraw_make_mem_image(rd, &ret);
	if (ret)
		fprintf_rl(stderr, "libraw %s\n", libraw_strerror(ret));
	else if (proc_image->colors!=3 || proc_image->bits!=16)
	{
		fprintf_rl(stderr, "Wrong decoded image format, %d %d-bit channels, type %d\n", proc_image->colors, proc_image->bits, proc_image->type);
	}
	else
	{
		r = make_raster(NULL, xyi(proc_image->width, proc_image->height), XYI0, IMAGE_USE_FRGB);
		//convert_image_srgb16(&r, proc_image->data, IMAGE_USE_FRGB);
		for (i=0; i < mul_x_by_y_xyi(r.dim); i++)
			for (ic=0; ic < 3; ic++)
				//((float *) r.f)[i*4+ic] = s16lrgb(proc_image->data[i*3+ic]);
				((float *) r.f)[i*4+ic] = ((uint16_t *)proc_image->data)[i*3+ic] * (1.f / 65535.f);
	}

	libraw_dcraw_clear_mem(proc_image);

	return r;
}

#endif
