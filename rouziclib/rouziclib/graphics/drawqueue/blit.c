#ifdef RL_INTEL_INTR

__m128 dqs_read_frgb_pixel(frgb_t *im, const size_t index)
{
	__m128 v = _mm_loadu_ps((float *) &im[index]);
	return v;
}

__m128 dqs_read_sqrgb_pixel(sqrgb_t *im, const size_t index)
{
	__m128 v = _mm_sqrgb_to_ps(im[index]);
	return v;
}

__m128 dqs_read_srgb_pixel(srgb_t *im, const size_t index)
{
	__m128 v = _mm_srgb_to_ps(im[index]);
	return v;
}

__m128 dqs_raw_yuv_to_lrgb(float y, float u, float v, float depth_mul)
{
	float r, g, b;
	__m128 pv;

	y = y*depth_mul - 16.f;
	y *= 255.f / 219.f;
	u = u*depth_mul - 128.f;
	v = v*depth_mul - 128.f;

	r = y + 1.596f * v;
        g = y - 0.813f * v - 0.391f * u;
        b = y + 2.018f * u;

	pv = _mm_set_ps(1.f, b, g, r);
	pv = _mm_mul_ps(pv, _mm_set_ps1(1.f/255.f));
	pv = _mm_mul_ps(pv, pv);

	// TODO proper conversion
	/*pv.x = s8lrgb(r);
	pv.y = s8lrgb(g);
	pv.z = s8lrgb(b);
	pv.w = 1.;*/

	return pv;
}

__m128 dqs_read_yuv420p8_pixel(uint8_t *im, xyi_t im_dim, xyi_t i)
{
	__m128 pv;
	float y, u, v, r, g, b;
	xyi_t im_dimh = rshift_xyi(im_dim, 1);
	int size_full = im_dim.x*im_dim.y, size_half = size_full>>2, y_index, uv_index;
	uint8_t *u_plane, *v_plane;

	u_plane = &im[size_full];
	v_plane = &im[size_full + size_half];
	y_index = i.y * im_dim.x + i.x;
	uv_index = (i.y>>1) * im_dimh.x + (i.x>>1);	// TODO fix for MPEG-2 layout

	pv = dqs_raw_yuv_to_lrgb((float) im[y_index], (float) u_plane[uv_index], (float) v_plane[uv_index], 1.f );

	return pv;
}

typedef struct
{
	int init;
	int block_size, bits_per_block, quincunx, bits_ch, bits_cs, bits_cl, bits_per_pixel;
	int linew0, linew1, pix;
	xyi_t block_pos, block_start;
	uint64_t di;
	frgb_t col0, col1, colm, pv;
	float pix_mul;
} comp_decode_t;

__m128 dqs_calc_flattop_weight(__m128 pif, __m128 i, __m128 knee, __m128 slope, __m128 pscale)
{
	__m128 d, w;

	d = _mm_abs_ps(_mm_sub_ps(pif, i));
	d = _mm_max_ps(d, knee);
	d = _mm_mul_ps(slope, _mm_sub_ps(d, pscale));
	w = _mm_hlomul_ss(d);
	w = _mm_shuffle_ps(w, w, 0);

	return w;
}

#ifdef __GNUC__
__attribute__((__target__("sse4.1")))
#endif
__m128 dqs_image_filter_flattop(uint8_t *im, xyi_t im_dim, __m128 im_lim, const int fmt, __m128 pif, __m128 pscale, __m128 slope, __m128 knee, comp_decode_t *cd1)
{
	__m128 sum, pv, wv;
	__m128 i, startv, endv, incv;
	xyi_t ip, start, end;
	int index;

	sum = _mm_setzero_ps();
	startv = _mm_ceil_ps(_mm_max_ps(sum, _mm_sub_ps(pif, pscale)));
	endv = _mm_floor_ps(_mm_min_ps(im_lim, _mm_add_ps(pif, pscale)));
	_mm_storel_epi64((__m128i *) &start, _mm_cvtps_epi32(startv));
	_mm_storel_epi64((__m128i *) &end, _mm_cvtps_epi32(endv));
	incv = _mm_set_ps(0.f, 0.f, 0.f, 1.f);

	for (ip.y = start.y; ip.y <= end.y; ip.y++)
	{
		i = _mm_set_ps(0.f, 0.f, ip.y, start.x);
		index = ip.y * im_dim.x + start.x;

		for (ip.x = start.x; ip.x <= end.x; ip.x++, index++)
		{
			wv = dqs_calc_flattop_weight(pif, i, knee, slope, pscale);

			switch (fmt)
			{
					case 0:  pv = dqs_read_frgb_pixel((frgb_t *) im, index);
				break;	case 1:  pv = dqs_read_sqrgb_pixel((sqrgb_t *) im, index);
				break;	case 2:  pv = dqs_read_srgb_pixel((srgb_t *) im, index);
				break;	case 10: pv = dqs_read_yuv420p8_pixel(im, im_dim, ip);
				/*break;	case 11: pv = dqs_read_yuv420pN_pixel(im, im_dim, i, 0.25f);
				break;	case 12: pv = dqs_read_yuv420pN_pixel(im, im_dim, i, 0.0625f);
				break;	case 12: pv = dqs_read_compressed_texture1_pixel(im, im_dim, i, cd1);*/
				break;	default: pv = _mm_setzero_ps();
			}

			sum = _mm_add_ps(sum, _mm_mul_ps(pv, wv));
			i = _mm_add_ps(i, incv);
		}
	}

	return sum;
}

void dqsb_blit_sprite_flattop(float *lef, uint8_t *data, float *block, xy_t start_pos, const int bs, int chan_stride)
{
	comp_decode_t cd1={0};
	uint8_t *im;
	uint32_t *lei = (uint32_t *) lef;
	int ic, ib=0;
	xy_t pf, pscale, pscale_capped, pos, pif, slope, knee;
	xyi_t im_dim;
	int fmt;
	__m128 pv, pscalev, pifv, slopev, kneev, im_limv;
	float p4[4];

	// Load parameters
	im = &data[(uint64_t) lei[0]+((uint64_t) lei[1]<<32)];
	im_dim.x = lei[2];
	im_dim.y = lei[3];
	pscale.x = lef[4];
	pscale.y = lef[5];
	pos.x = lef[6];
	pos.y = lef[7];
	fmt = lei[8];
	slope.x = lef[9];
	slope.y = lef[10];

	pscale_capped = max_xy(XY1, pscale);
	knee = sub_xy(set_xy(0.5), abs_xy(sub_xy(fmod_xy(pscale_capped, XY1), set_xy(0.5))));

	pscalev = _mm_xy_to_ps(pscale_capped);
	slopev = _mm_xy_to_ps(slope);
	kneev = _mm_xy_to_ps(knee);
	im_limv = _mm_xyi_to_ps(sub_xyi(im_dim, set_xyi(1)));

	for (pf.y=start_pos.y; pf.y < start_pos.y+bs; pf.y+=1.)
		for (pf.x=start_pos.x; pf.x < start_pos.x+bs; pf.x+=1., ib++)
		{
			pif = mul_xy(pscale, add_xy(pf, pos));
			pifv = _mm_xy_to_ps(pif);
			pv = dqs_image_filter_flattop(im, im_dim, im_limv, fmt, pifv, pscalev, slopev, kneev, &cd1);

			// Store each channel
			_mm_storeu_ps(p4, pv);
			for (ic=0; ic < 4; ic++)
				block[ic*chan_stride + ib] += p4[ic];
		}
}

#endif
