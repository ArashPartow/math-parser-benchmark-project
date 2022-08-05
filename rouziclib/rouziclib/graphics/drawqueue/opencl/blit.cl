bool check_image_bounds(int2 pi, int2 im_dim)
{
	if (pi.x >= 0 && pi.x < im_dim.x)
		if (pi.y >= 0 && pi.y < im_dim.y)
			return true;
	return false;
}

/*float4 image_interp_nearest(global float4 *im, int2 im_dim, float2 pif)
{
	float4 pv;
	int2 pi;

	pi = convert_int2(pif + 0.5f);

	if (check_image_bounds(pi, im_dim))
		pv = im[pi.y * im_dim.x + pi.x];
	else
		pv = 0.f;

	return pv;
}

float4 get_image_pixel_weighted_linear(global float4 *im, int2 im_dim, float2 pif, float2 pjf)
{
	float4 pv;
	float2 w;
	int2 pj = convert_int2(pjf);

	w = 1.f - fabs(pif-pjf);		// weight for current pixel

	if (check_image_bounds(pj, im_dim))
		pv = im[pj.y * im_dim.x + pj.x] * (w.x*w.y);
	else
		pv = 0.f;

	return pv;
}

float4 image_interp_linear(global float4 *im, int2 im_dim, float2 pif)
{
	float4 pv = 0.f;
	float2 pif00;

	pif00 = floor(pif);

	pv += get_image_pixel_weighted_linear(im, im_dim, pif, pif00);
	pv += get_image_pixel_weighted_linear(im, im_dim, pif, pif00 + (float2)(0.f, 1.f));
	pv += get_image_pixel_weighted_linear(im, im_dim, pif, pif00 + (float2)(1.f, 0.f));
	pv += get_image_pixel_weighted_linear(im, im_dim, pif, pif00 + (float2)(1.f, 1.f));

	return pv;
}*/

float4 read_frgb_pixel(global float4 *im, int index)
{
	return im[index];
}

float4 read_float1_pixel(global float *im, int index)
{
	float4 pv = 0.f;
	pv.x = im[index];
	pv.w = 1.f;
	return pv;
}

float4 read_float2_pixel(global float *im, int index)
{
	float4 pv = 0.f;
	index <<= 1;
	pv.x = im[index];
	pv.y = im[index+1];
	pv.z = 0.f;
	pv.w = 1.f;
	return pv;
}

float4 read_float2_pixel_planar(global float *im, int2 im_dim, int2 i)
{
	int size_full = im_dim.x*im_dim.y;
	int index = i.y * im_dim.x + i.x;
	float4 pv = 0.f;

	pv.x = im[index];
	pv.y = im[index + size_full];
	pv.z = 0.f;
	pv.w = 1.f;
	return pv;
}

float4 read_float3_pixel(global float *im, int index)
{
	float4 pv;
	index *= 3;
	pv.x = im[index];
	pv.y = im[index+1];
	pv.z = im[index+2];
	pv.w = 1.f;
	return pv;
}

float4 read_float3_pixel_planar(global float *im, int2 im_dim, int2 i)
{
	int size_full = im_dim.x*im_dim.y;
	int index = i.y * im_dim.x + i.x;
	float4 pv = 0.f;

	pv.x = im[index];
	pv.y = im[index + size_full];
	pv.z = im[index + size_full*2];
	pv.w = 1.f;
	return pv;
}


float4 read_sqrgb_pixel(global uint *im, int index)
{
	float4 pv;
	uint4 pvi;
	uint v;
	const float mul_rb = 1.f / (1023.f*1023.f);
	const float mul_g = 1.f / (4092.f*4092.f);
	const float4 mul_pvi = (float4) (mul_rb, mul_g, mul_rb, 1.f);

	v = im[index];
	pvi.z = v >> 22;
	pvi.y = (v >> 10) & 4095;
	pvi.x = v & 1023;
	pvi.w = 1;

	pv = convert_float4(pvi*pvi) * mul_pvi;

	return pv;
}

float4 read_srgb_pixel(global uint *im, int index)
{
	float4 pv;
	uint v;

	v = im[index];
	pv.z = s8lrgb((v >> 16) & 255);
	pv.y = s8lrgb((v >> 8) & 255);
	pv.x = s8lrgb(v & 255);
	pv.w = 1.f;

	return pv;
}

float4 read_lrgb_pixel(global ushort *im, int index)
{
	float4 pv;

	pv.x = im[index]   * 0.000030517578125f;
	pv.y = im[index+1] * 0.000030517578125f;
	pv.z = im[index+2] * 0.000030517578125f;
	pv.w = 1.f;

	return pv;
}

float4 raw_yuv_to_lrgb(float3 raw, float depth_mul)
{
	float y, u, v, r, g, b;
	float4 pv;

	raw *= depth_mul;
	y = raw.x - 16.f;
	y *= 255.f / 219.f;
	u = raw.y - 128.f;
	v = raw.z - 128.f;

	r = y + 1.596f * v;
        g = y - 0.813f * v - 0.391f * u;
        b = y + 2.018f * u;

	pv.x = s8lrgb(r);
	pv.y = s8lrgb(g);
	pv.z = s8lrgb(b);
	pv.w = 1.f;

	return pv;
}

float4 raw_yuvj_to_lrgb(float3 raw, float depth_mul)
{
	float y, u, v, r, g, b;
	float4 pv;

	raw *= depth_mul;
	y = raw.x;
	u = raw.y - 128.f;
	v = raw.z - 128.f;

	r = y + 1.596f * v;
        g = y - 0.813f * v - 0.391f * u;
        b = y + 2.018f * u;

	pv.x = s8lrgb(r);
	pv.y = s8lrgb(g);
	pv.z = s8lrgb(b);
	pv.w = 1.f;

	return pv;
}

float4 read_yuv420p8_pixel(global uchar *im, int2 im_dim, int2 i)
{
	float4 pv;
	float y, u, v, r, g, b;
	int2 im_dimh = im_dim / 2;
	int size_full = im_dim.x*im_dim.y, size_half = size_full/4, y_index, uv_index;
	global uchar *u_plane, *v_plane;

	u_plane = &im[size_full];
	v_plane = &im[size_full + size_half];
	y_index = i.y * im_dim.x + i.x;
	uv_index = i.y/2 * im_dimh.x + i.x/2;	// TODO fix for MPEG-2 layout

	pv = raw_yuv_to_lrgb( (float3) (im[y_index], u_plane[uv_index], v_plane[uv_index]), 1.f );

	return pv;
}

float4 read_yuvj420p8_pixel(global uchar *im, int2 im_dim, int2 i)
{
	float4 pv;
	float y, u, v, r, g, b;
	int2 im_dimh = im_dim / 2;
	int size_full = im_dim.x*im_dim.y, size_half = size_full/4, y_index, uv_index;
	global uchar *u_plane, *v_plane;

	u_plane = &im[size_full];
	v_plane = &im[size_full + size_half];
	y_index = i.y * im_dim.x + i.x;
	uv_index = i.y/2 * im_dimh.x + i.x/2;	// TODO fix for MPEG-2 layout

	pv = raw_yuvj_to_lrgb( (float3) (im[y_index], u_plane[uv_index], v_plane[uv_index]), 1.f );

	return pv;
}

float4 read_yuv420pN_pixel(global ushort *im, int2 im_dim, int2 i, float depth_mul)	// yuv420p formats above 8 bpc
{
	float4 pv;
	float y, u, v, r, g, b;
	int2 im_dimh = im_dim / 2;
	int size_full = im_dim.x*im_dim.y, size_half = size_full/4, y_index, uv_index;
	global ushort *u_plane, *v_plane;

	u_plane = &im[size_full];
	v_plane = &im[size_full + size_half];
	y_index = i.y * im_dim.x + i.x;
	uv_index = i.y/2 * im_dimh.x + i.x/2;

	pv = raw_yuv_to_lrgb( (float3) (im[y_index], u_plane[uv_index], v_plane[uv_index]), depth_mul );

	return pv;
}

// Compressed texture
uint bits_to_mask(uint bits)	// 7 becomes 0x7F
{
	return (1UL << bits) - 1;
}

float bits_to_mul(uint bits)	// 7 becomes 127.
{
	//return (float) ((1UL << bits) - 1);
	return convert_float((int) ((1UL << bits) - 1));
}

float4 decompr_rgb(int bits_col, uchar3 c)
{
	float4 rgb;
	float ratio = 1.f / bits_to_mul(bits_col);

	rgb.x = (float) c.x * ratio;
	rgb.y = (float) c.y * ratio;
	rgb.z = (float) c.z * ratio;

	return rgb;
}

float4 compr_hsl_to_rgb(float3 hsl)
{
	float4 rgb;
	float3 w = (float3) (0.124f, 0.686f, 0.19f);

	hsl.x *= 3.f;					// H in HUE03
	hsl.z = Lab_L_to_linear(hsl.z);			// linear L
	rgb = (float4) (hsl_to_rgb_cw(w, hsl), 1.f);

	rgb.x = linear_to_Lab_L(rgb.x);
	rgb.y = linear_to_Lab_L(rgb.y);
	rgb.z = linear_to_Lab_L(rgb.z);
	return rgb;
}

typedef struct
{
	int init;
	int block_size, bits_per_block, quincunx, bits_col, bits_per_pixel;
	int linew0, linew1, pix;
	int2 block_pos, block_start;
	ulong di;
	float4 col0, col1, colm, pv;
	float pix_mul;
} comp_decode_t;

float4 read_compressed_texture1_pixel(global uchar *d8, int2 im_dim, int2 i, comp_decode_t *d)
{
	global ushort *d16 = (global ushort *) d8;
	ulong di, block_start_bit = 64;
	int line_count0, line_count1;
	int pix, qoff;
	uchar3 c0, c1, cm;
	int2 block_pos, ib;
	float t;

	if (d->init==0)
	{
		#if 0
		// Load decoding parameters
		d->block_size = d16[0];
		d->bits_per_block = d16[1];
		d->quincunx = d8[5];
		d->bits_col = d8[6];
		d->bits_per_pixel = d8[7];
		#else

		// Using hardcoded values goes faster
		d->block_size = 8;
		d->bits_per_block = 240;
		d->quincunx = 1;
		d->bits_col = 8;
		d->bits_per_pixel = 3;
		#endif

		d->linew0 = idiv_ceil(im_dim.x, d->block_size);
		d->linew1 = idiv_ceil(im_dim.x + d->quincunx*(d->block_size>>1), d->block_size);
		d->pix_mul = 2.f / bits_to_mul(d->bits_per_pixel);

		d->init = 1;
		d->block_pos = (int2) (-1, -1);
		d->pix = -1;
	}

	// Calculate block pos
	block_pos.y = (i.y / d->block_size);
	qoff = (block_pos.y&1) * d->quincunx * (d->block_size>>1);
	block_pos.x = (i.x + qoff) / d->block_size;

	// If it's a different block
	if (block_pos.x != d->block_pos.x || block_pos.y != d->block_pos.y)
	{
		// Calculate block start in bits
		line_count0 = (block_pos.y+1) >> 1;
		line_count1 = block_pos.y >> 1;
		di = line_count0*d->linew0 + line_count1*d->linew1;	// y block line start id
		di += block_pos.x;					// x block start id
		di = di*d->bits_per_block + block_start_bit;		// block id to bit position

		// Position in pixels of the first pixel of the block
		d->block_start = block_pos * d->block_size;
		d->block_start.x -= qoff;

		// Read block data
		c0.x = get_bits_in_stream_inc(d8, &di, d->bits_col);
		c0.y = get_bits_in_stream_inc(d8, &di, d->bits_col);
		c0.z = get_bits_in_stream_inc(d8, &di, d->bits_col);
		c1.x = get_bits_in_stream_inc(d8, &di, d->bits_col);
		c1.y = get_bits_in_stream_inc(d8, &di, d->bits_col);
		c1.z = get_bits_in_stream_inc(d8, &di, d->bits_col);
		/*cm.x = get_bits_in_stream_inc(d8, &di, d->bits_col);
		cm.y = get_bits_in_stream_inc(d8, &di, d->bits_col);
		cm.z = get_bits_in_stream_inc(d8, &di, d->bits_col);*/
		d->di = di;

		// Decode colours
		d->col0 = decompr_rgb(d->bits_col, c0);
		d->col1 = decompr_rgb(d->bits_col, c1);
		//d->colm = decompr_rgb(d->bits_col, cm);

		d->block_pos = block_pos;
		d->pix = -1;
	}

	// Read bitmap pixel value
	ib = i - d->block_start;		// position of the pixel in the block
	di = d->di + (ib.y*d->block_size + ib.x) * d->bits_per_pixel;
	pix = get_bits_in_stream(d8, di, d->bits_per_pixel);

	if (pix != d->pix)
	{
		// Translate bitmap value to linear RGB value
		t = convert_float(pix) * d->pix_mul;
		d->pv = mix(d->col0, d->col1, t*0.5f);
		/*if (t < 1.f)
			d->pv = mix(d->col0, d->colm, t);
		else
			d->pv = mix(d->colm, d->col1, t-1.f);*/
		d->pv.x = Lab_L_to_linear(d->pv.x);
		d->pv.y = Lab_L_to_linear(d->pv.y);
		d->pv.z = Lab_L_to_linear(d->pv.z);
		d->pix = pix;
	}
	return d->pv;
}

float4 read_fmt_pixel(const int fmt, global float4 *im, int2 im_dim, int2 i, comp_decode_t *cd1)
{
	switch (fmt)
	{
		case 0:		// frgb_t
			return read_frgb_pixel((global float4 *) im, i.y * im_dim.x + i.x);

		case 1:		// sqrgb_t
			return read_sqrgb_pixel((global uint *) im, i.y * im_dim.x + i.x);

		case 2:		// srgb_t
			return read_srgb_pixel((global uint *) im, i.y * im_dim.x + i.x);

		case 3:		// lrgb_t
			return read_lrgb_pixel((global ushort *) im, 4*(i.y * im_dim.x + i.x));

		case 10:	// YCbCr 420 planar 8-bit (AV_PIX_FMT_YUV420P)
			return read_yuv420p8_pixel((global uchar *) im, im_dim, i);

		case 11:	// YCbCr 420 planar 10-bit LE (AV_PIX_FMT_YUV420P10LE)
			return read_yuv420pN_pixel((global ushort *) im, im_dim, i, 0.25f);

		case 12:	// YCbCr 420 planar 12-bit LE (AV_PIX_FMT_YUV420P12LE)
			return read_yuv420pN_pixel((global ushort *) im, im_dim, i, 0.0625f);

		case 15:	// YCbCr 420 planar full 0-255 range 8-bit (AV_PIX_FMT_YUVJ420P)
			return read_yuvj420p8_pixel((global uchar *) im, im_dim, i);

		case 20:	// Compressed texture format
			return read_compressed_texture1_pixel((global uchar *) im, im_dim, i, cd1);

		case 31:	// 1 channel float
		case 41:
			return read_float1_pixel((global float *) im, i.y * im_dim.x + i.x);

		case 32:	// 2 channel float
			return read_float2_pixel((global float *) im, i.y * im_dim.x + i.x);

		case 33:	// 3 channel float
			return read_float3_pixel((global float *) im, i.y * im_dim.x + i.x);

		case 42:	// 2 channel float planar
			return read_float2_pixel_planar((global float *) im, im_dim, i);

		case 43:	// 3 channel float planar
			return read_float3_pixel_planar((global float *) im, im_dim, i);
	}

	return 0.f;
}

float4 read_fmt_pixel_checked(global float4 *im, int2 im_dim, const int fmt, int2 pi, comp_decode_t *cd1)
{
	float4 pv;

	if (check_image_bounds(pi, im_dim))
		pv = read_fmt_pixel(fmt, im, im_dim, pi, cd1);
	else
		pv = 0.f;

	return pv;
}

float calc_flattop_weight(float2 pif, float2 i, float2 knee, float2 slope, float2 pscale)
{
	float2 d, w;

	d = fabs(pif - i);
	d = max(d, knee);
	w = slope * (d - pscale);

	return w.x * w.y;
}

float4 image_filter_flattop(global float4 *im, int2 im_dim, const int fmt, float2 pif, float2 pscale, float2 slope)
{
	float4 pv = 0.f;
	float2 knee, i, start, end;
	comp_decode_t cd1={0};

	knee = 0.5f - fabs(fmod(pscale, 1.f) - 0.5f);

	start = max(0.f, ceil(pif - pscale));
	end = min(convert_float2(im_dim - 1), floor(pif + pscale));

	for (i.y = start.y; i.y <= end.y; i.y+=1.f)
		for (i.x = start.x; i.x <= end.x; i.x+=1.f)
			pv += read_fmt_pixel(fmt, im, im_dim, convert_int2(i), &cd1) * calc_flattop_weight(pif, i, knee, slope, pscale);

	return pv;
}

float2 calc_aa_nearest_weights(float2 pif, float2 i, float2 pscale)
{
	float2 d, w;

	d = fabs(pif - i);
	w = clamp(native_divide(0.5f - d, pscale) + 0.5f, 0.f, 1.f);

	return w;
}

float4 image_filter_aa_nearest(global float4 *im, int2 im_dim, const int fmt, float2 pif, float2 pscale)
{
	float4 pv = 0.f;
	comp_decode_t cd1={0};
	float2 pif00, w00;
	int2 pi00;
	float w;

	pif00 = floor(pif);
	pi00 = convert_int2(pif00);
	w00 = calc_aa_nearest_weights(pif, pif00, pscale);

	w = w00.x * w00.y;
	pv  = read_fmt_pixel_checked(im, im_dim, fmt, pi00, &cd1) * w;

	if (w < 1.f)
	{
		pv += read_fmt_pixel_checked(im, im_dim, fmt, pi00 + (int2)(0, 1), &cd1) * w00.x * (1.f - w00.y);
		pv += read_fmt_pixel_checked(im, im_dim, fmt, pi00 + (int2)(1, 0), &cd1) * (1.f - w00.x) * w00.y;
		pv += read_fmt_pixel_checked(im, im_dim, fmt, pi00 + (int2)(1, 1), &cd1) * (1.f - w00.x) * (1.f - w00.y);
	}

	return pv;
}

/*float4 blit_sprite_bilinear(global uint *lei, global uchar *data_cl, float4 pv)
{
	const int2 p = (int2) (get_global_id(0), get_global_id(1));
	const float2 pf = convert_float2(p);
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	float2 pscale, pos, pif;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = lef[5];
	pos.x = lef[6];
	pos.y = lef[7];

	pif = pscale * (pf + pos);
	//pv += image_interp_nearest(im, im_dim, pif);
	pv += image_interp_linear(im, im_dim, pif);

	return pv;
}*/

float4 blit_sprite_flattop(global uint *lei, global uchar *data_cl, float4 pv, const float2 pf)
{
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	int fmt;
	float2 pscale, pos, pif, slope;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = lef[5];
	pos.x = lef[6];
	pos.y = lef[7];
	fmt = lei[8];
	slope.x = lef[9];
	slope.y = lef[10];

	pif = pscale * (pf + pos);
	pscale = max(1.f, pscale);
	pv += image_filter_flattop(im, im_dim, fmt, pif, pscale, slope);

	return pv;
}

float4 blit_sprite_flattop_rot(global uint *lei, global uchar *data_cl, float4 pv, const float2 pf)
{
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	int fmt;
	float2 pscale, pos, pif, pifo, slope;
	float costh, sinth;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = pscale.x;
	pos.x = lef[5];
	pos.y = lef[6];
	fmt = lei[7];
	slope.x = lef[8];
	slope.y = slope.x;
	costh = lef[9];
	sinth = lef[10];

	pifo = pscale * (pf + pos);
	pif.x = pifo.x * costh - pifo.y * sinth;
	pif.y = pifo.x * sinth + pifo.y * costh;
	pscale = max(1.f, pscale);
	pv += image_filter_flattop(im, im_dim, fmt, pif, pscale, slope);

	return pv;
}

float4 blit_sprite_aa_nearest(global uint *lei, global uchar *data_cl, float4 pv, const float2 pf)
{
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	int fmt;
	float2 pscale, pos, pif;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = lef[5];
	pos.x = lef[6];
	pos.y = lef[7];
	fmt = lei[8];

	pif = pscale * (pf + pos);
	pv += image_filter_aa_nearest(im, im_dim, fmt, pif, pscale);

	return pv;
}

float4 blit_sprite_aa_nearest_rot(global uint *lei, global uchar *data_cl, float4 pv, const float2 pf)
{
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	int fmt;
	float2 pscale, pos, pif, pifo;
	float costh, sinth;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = pscale.x;
	pos.x = lef[5];
	pos.y = lef[6];
	fmt = lei[7];
	costh = lef[8];
	sinth = lef[9];

	pifo = pscale * (pf + pos);
	pif.x = pifo.x * costh - pifo.y * sinth;
	pif.y = pifo.x * sinth + pifo.y * costh;
	pv += image_filter_aa_nearest(im, im_dim, fmt, pif, pscale);

	return pv;
}

/*float2 set_new_distance_from_point(float2 p0, float2 pc, float dist_mul)
{
	return pc + (p0 - pc) * dist_mul;
}

float inverse_distortion(float a, float x)
{
	float p1, p2, p3;

	p1 = cbrt(2.f / (3.f * a));
	p2 = cbrt( sqrt(3.f*a) * sqrt( 27.f*a*x*x + 4.f ) - 9.f*a*x );
	p3 = cbrt(2.f) * pow(3.f*a, 2.f / 3.f);

	return p1/p2 - p2/p3;	// http://www.wolframalpha.com/input/?i=inverse+of+x+*+(1+%2B+11*x%5E2)
}

float4 blit_photo(global uint *lei, global uchar *data_cl, float4 pv)
{
	const int2 p = (int2) (get_global_id(0), get_global_id(1));
	const float2 pf = convert_float2(p);
	global float *lef = (global float *) lei;
	global float4 *im;
	int2 im_dim;
	float2 pscale, pos, pif, pc;
	float distortion, dist_scale, gain, distortion_mul, d;

	im = (global float4 *) &data_cl[lei[0]+(lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = lef[5];
	pos.x = lef[6];
	pos.y = lef[7];
	pc.x = lef[8];
	pc.y = lef[9];
	distortion = lef[10];
	dist_scale = lef[11];
	gain = lef[12];

	pif = pscale * (pf + pos);

	d = fast_distance(pif, pc) * dist_scale;
	if (distortion==0.f)
		distortion_mul = 1.f;
	else
		distortion_mul = inverse_distortion(distortion, d) / d;
	pif = set_new_distance_from_point(pif, pc, distortion_mul);

	//pv += image_interp_nearest(im, im_dim, pif);
	pv += gain * image_interp_linear(im, im_dim, pif);

	return pv;
}*/
