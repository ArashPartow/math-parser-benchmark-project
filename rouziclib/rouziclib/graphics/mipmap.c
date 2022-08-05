void alloc_mipmap_level(mipmap_level_t *ml, xyi_t fulldim, xyi_t tilesize, const int mode)
{
	xyi_t it, rdim;
	size_t elem_size = get_raster_mode_elem_size(mode);

	ml->tiledim = tilesize;
	ml->fulldim = fulldim;
	ml->tilecount = div_round_up_xyi(fulldim , tilesize);

	ml->r = malloc(mul_x_by_y_xyi(ml->tilecount) * sizeof(raster_t));	// array of raster tiles
	ml->total_bytes = mul_x_by_y_xyi(ml->tilecount) * sizeof(raster_t);

	// Contiguous allocation
	ml->total_bytes += mul_x_by_y_xyi(fulldim) * elem_size;
	uint8_t *ptr = calloc(mul_x_by_y_xyi(fulldim), elem_size);

	for (it.y=0; it.y < ml->tilecount.y; it.y++)
		for (it.x=0; it.x < ml->tilecount.x; it.x++)
		{
			rdim = get_dim_of_tile(fulldim, tilesize, it);
			ml->r[it.y*ml->tilecount.x + it.x] = make_raster(ptr, rdim, XYI0, mode);
			ptr = &ptr[mul_x_by_y_xyi(rdim) * elem_size];
		}
}

void *get_tile_pixel_ptr(mipmap_level_t ml, xyi_t pos, const int mode)
{
	xyi_t ti, pt;
	raster_t *tile_ptr;

	if (check_pixel_within_image(pos, ml.fulldim)==0)
		return NULL;				// returns NULL pointer if pixel is out of bounds

	ti = div_xyi(pos, ml.tiledim);			// tile index
	pt = sub_xyi(pos, mul_xyi(ti, ml.tiledim));	// position in tile

	tile_ptr = &ml.r[ti.y * ml.tilecount.x + ti.x];
	uint8_t *buf = get_raster_buffer_for_mode(*tile_ptr, mode);
	size_t pix_size = get_raster_mode_elem_size(mode);

	return &buf[(pt.y * tile_ptr->dim.x + pt.x)*pix_size];
}

void mipmap_set_functions(mipmap_t *m, const int mode)
{
	#ifdef RL_INTEL_INTR
	switch (mode)
	{
		case IMAGE_USE_FRGB:
			m->get_pixel_ps = _mm_get_raster_pixel_frgb_to_ps;
			m->set_pixel_ps = _mm_set_raster_pixel_ps_to_frgb;
			break;

		case IMAGE_USE_LRGB:
			m->get_pixel_ps = _mm_get_raster_pixel_lrgb_to_ps;
			m->set_pixel_ps = _mm_set_raster_pixel_ps_to_lrgb;
			break;

		case IMAGE_USE_SRGB:
			m->get_pixel_ps = _mm_get_raster_pixel_srgb_to_ps;
			m->set_pixel_ps = _mm_set_raster_pixel_ps_to_srgb;
			break;

		case IMAGE_USE_SQRGB:
			m->get_pixel_ps = _mm_get_raster_pixel_sqrgb_to_ps;
			m->set_pixel_ps = _mm_set_raster_pixel_ps_to_sqrgb;
			break;

		default:
			fprintf_rl(stderr, "Invalid raster mode %d specified in mipmap_set_functions()\n", mode);
	}
	#endif
}

void copy_from_raster_to_tiles(raster_t r, mipmap_level_t ml, const int mode)
{
	xyi_t it, rdim, tilestart, pstart;
	int iy;
	frgb_t *pp;
	size_t pix_size = get_raster_mode_elem_size(mode);
	uint8_t *buf = get_raster_buffer_for_mode(r, mode);

	for (it.y=0; it.y < ml.tilecount.y; it.y++)
		for (it.x=0; it.x < ml.tilecount.x; it.x++)	// this copies a rect from the raster into the matching tile, line by line
		{
			tilestart = mul_xyi(ml.tiledim, it);
			rdim = get_dim_of_tile(ml.fulldim, ml.tiledim, it);

			for (iy=0; iy<rdim.y; iy++)
			{
				pstart = add_xyi(tilestart, xyi(0, iy));
				pp = get_tile_pixel_ptr(ml, pstart, mode);

				memcpy(pp, &buf[(pstart.y*r.dim.x + pstart.x)*pix_size], rdim.x*pix_size);
			}
		}
}

/*void tile_downscale_fast_box(mipmap_level_t ml0, mipmap_level_t ml1, const xyi_t ratio)
{
	xyi_t ip0, ip1;
	recti_t pixbox;
	xyz_t fsum, pix0;
	double fratio;

	for (ip1.y=0; ip1.y < ml1.fulldim.y; ip1.y++)
	{
		for (ip1.x=0; ip1.x < ml1.fulldim.x; ip1.x++)
		{
			memset(&fsum, 0, sizeof(fsum));
			fratio = 0.;

			pixbox.p0 = mul_xyi(ip1, ratio);
			pixbox.p1 = min_xyi( add_xyi(pixbox.p0, ratio) , ml0.fulldim );

			for (ip0.y = pixbox.p0.y; ip0.y < pixbox.p1.y; ip0.y++)
			{
				for (ip0.x = pixbox.p0.x; ip0.x < pixbox.p1.x; ip0.x++)
				{
					pix0 = frgb_to_xyz(get_tile_pixel(ml0, ip0));

					fsum = add_xyz(fsum, pix0);
					fratio += 1.;
				}
			}

			fratio = 1./fratio;
			fsum = mul_xyz(fsum, set_xyz(1. / mul_x_by_y_xyi(ratio)));		// weighting of the sum with a fixed ratio
			set_tile_pixel(ml1, ip1, make_colour_frgb(fsum.x, fsum.y, fsum.z, mul_x_by_y_xyi(ratio) * fratio) );
		}
	}
}*/

void tile_pixel_sum_float(raster_t *tile0, const int i0, raster_t *tile1, const int i1, const int width0, const int partial)
{
	frgb_t sum, *tp0 = &tile0->f[i0];

	switch (partial)
	{
		case 0:	sum = add_frgba( add_frgba(tp0[0], tp0[1]) , add_frgba(tp0[width0], tp0[width0+1]) );	break;
		case 1:	sum = add_frgba(tp0[0], tp0[width0]);							break;
		case 2:	sum = add_frgba(tp0[0], tp0[1]);							break;
		default:
		case 3:	sum = tp0[0];										break;
	}

	tile1->f[i1] = mul_scalar_frgba(sum, 0.25);
}

void tile_pixel_sum_sq(raster_t *tile0, const int i0, raster_t *tile1, const int i1, const int width0, const int partial)
{
	sqrgb_t sum, *tp0 = &tile0->sq[i0];

	switch (partial)
	{
		case 0:	sum = average_sqrgb_4(tp0[0], tp0[1], tp0[width0], tp0[width0+1]);	break;
		case 1:	sum = average_sqrgb_2(tp0[0], tp0[width0]);				break;
		case 2:	sum = average_sqrgb_2(tp0[0], tp0[1]);					break;
		default:
		case 3:	sum = average_sqrgb_1(tp0[0]);						break;
	}

	tile1->sq[i1] = sum;
}


void tile_downscale_box_2x2(mipmap_level_t ml0, mipmap_level_t ml1, const int mode)
{
	xyi_t it0, it1, ip0, ip1, off1, partial;
	raster_t *tile0, *tile1;
	int y0w, y1w;
	void (*tile_pixel_sum_func)(raster_t *, const int, raster_t *, const int, const int, const int);

	if (mode & IMAGE_USE_SQRGB)
		tile_pixel_sum_func = &tile_pixel_sum_sq;
	else
		tile_pixel_sum_func = &tile_pixel_sum_float;

	for (it0.y=0; it0.y < ml0.tilecount.y; it0.y++)
	{
		it1.y = it0.y >> 1;
		off1.y = (it0.y - (it1.y << 1)) * (ml0.tiledim.y >> 1);			// position offset for the tile0s on the bottom side

		for (it0.x=0; it0.x < ml0.tilecount.x; it0.x++)
		{
			it1.x = it0.x >> 1;
			off1.x = (it0.x - (it1.x << 1)) * (ml0.tiledim.x >> 1);		// position offset for the tile0s on the right side

			tile0 = &ml0.r[it0.y*ml0.tilecount.x + it0.x];
			tile1 = &ml1.r[it1.y*ml1.tilecount.x + it1.x];

			if ((tile0->dim.x & 1) + (tile0->dim.y & 1) == 0)		// if tile0 doesn't have partial 2x2 blocks
			{
				for (ip0.y=0; ip0.y < tile0->dim.y; ip0.y+=2)
				{
					ip1.y = (ip0.y >> 1) + off1.y;
					y0w = ip0.y*tile0->dim.x;
					y1w = ip1.y*tile1->dim.x;

					for (ip0.x=0; ip0.x < tile0->dim.x; ip0.x+=2)
					{
						ip1.x = (ip0.x >> 1) + off1.x;

						tile_pixel_sum_func(tile0, y0w + ip0.x, tile1, y1w + ip1.x, tile0->dim.x, 0);
					}
				}
			}
			else		// if it has partial 2x2 blocks
			{
				for (ip0.y=0; ip0.y < tile0->dim.y; ip0.y+=2)
				{
					ip1.y = (ip0.y >> 1) + off1.y;
					y0w = ip0.y*tile0->dim.x;
					y1w = ip1.y*tile1->dim.x;
					partial.y = (tile0->dim.y - ip0.y < 2) << 1;	// is set to 2 if partial in y

					for (ip0.x=0; ip0.x < tile0->dim.x; ip0.x+=2)
					{
						ip1.x = (ip0.x >> 1) + off1.x;
						partial.x = tile0->dim.x - ip0.x < 2;	// is set to 1 if partial in x

						tile_pixel_sum_func(tile0, y0w + ip0.x, tile1, y1w + ip1.x, tile0->dim.x, partial.y | partial.x);
					}
				}
			}
		}
	}
}

mipmap_t raster_to_tiled_mipmaps_fast(raster_t r, xyi_t tilesize, xyi_t mindim, const int mode)
{
	int i;
	mipmap_t m={0};

	m.fulldim = r.dim;
	m.lvl_count = 1. + log2(max_of_xy(div_xy(xyi_to_xy(m.fulldim), xyi_to_xy(mindim))));
	m.lvl_count = MAXN(m.lvl_count, 1);
	m.lvl = calloc(m.lvl_count, sizeof(mipmap_level_t));
	m.total_bytes = m.lvl_count * sizeof(mipmap_level_t);

	// the first level is a tiled copy of the original
	m.lvl[0].scale = set_xy(1.);
	alloc_mipmap_level(&m.lvl[0], m.fulldim, tilesize, mode);
	m.total_bytes += m.lvl[0].total_bytes;
	copy_from_raster_to_tiles(r, m.lvl[0], mode);

	for (i=1; i < m.lvl_count; i++)
	{
		m.lvl[i].fulldim = div_round_up_xyi(m.lvl[i-1].fulldim, set_xyi(2));
		m.lvl[i].scale = mul_xy(m.lvl[i-1].scale, set_xy(2.));
		alloc_mipmap_level(&m.lvl[i], m.lvl[i].fulldim, tilesize, mode);
		m.total_bytes += m.lvl[i].total_bytes;

		//tile_downscale_fast_box(m.lvl[i-1], m.lvl[i], set_xyi(2));
		tile_downscale_box_2x2(m.lvl[i-1], m.lvl[i], mode);
	}

	return m;
}

#ifdef RL_INTEL_INTR

#define LC 5
__m128 mipmap_make_fast_pixel_lvl4(mipmap_t *m, const xyi_t iro, xyi_t ipo)
{
	__m128 pix[LC][4], ave[LC];
	int i, i1, i2, i3, i4, il, ilo=LC-1, posy[LC], stride[LC];
	xyi_t ip[LC], ir[LC], ge;
	raster_t *rp[LC];

	il = LC-1;
	ir[il] = iro;
	ip[il] = ipo;

	// ir and ip for each level
	for (il=LC-2; il >= 0; il--)
	{
		// Calculate the next values
		ip[il] = lshift_xyi(ip[il+1], 1);	// next pixel start position (tile-relative)
		ir[il] = lshift_xyi(ir[il+1], 1);	// next tile position

		// Adjust values if the next 4 pixels are on another tile
		ge = cmp_ge_xyi(ip[il], m->lvl[il].tiledim);	// 1 if we must move to the next tile
		ir[il] = add_xyi(ir[il], ge);
		ip[il] = sub_xyi(ip[il], mul_xyi(ge, m->lvl[il].tiledim));
	}

	for (il=LC-1; il >= 0; il--)
	{
		rp[il] = &m->lvl[il].r[ir[il].y * m->lvl[il].tilecount.x + ir[il].x];
		stride[il] = rp[il]->dim.x;
		posy[il] = ip[il].y * stride[il];
	}

	// This is how I derecursivise the last levels of mipmap lmao
	i4=0;
	i3=0;
lvl2_start:
	i2=0;
lvl1_start:
	i1=0;
lvl0_start:
	// Read the four pixels from mipmap level 0
	pix[0][0] = m->get_pixel_ps(rp[0], posy[0] + ip[0].x);
	pix[0][1] = m->get_pixel_ps(rp[0], posy[0] + ip[0].x+1);
	pix[0][2] = m->get_pixel_ps(rp[0], posy[0] + stride[0] + ip[0].x);
	pix[0][3] = m->get_pixel_ps(rp[0], posy[0] + stride[0] + ip[0].x+1);

	// Level 1 average and write pixel to mipmap
	pix[1][i1] = _mm_mul_ps(_mm_set_ps1(0.25f), _mm_add_ps(_mm_add_ps(pix[0][0], pix[0][1]) , _mm_add_ps(pix[0][2], pix[0][3])));
	m->set_pixel_ps(rp[1], posy[1] + ip[1].x, pix[1][i1]);

	switch (i1)
	{
		case 0:
			i1 = 2;
			posy[1] += stride[1];
			posy[0] += stride[0]<<1;
			goto lvl0_start;
			break;

		case 2:
			i1 = 3;
			ip[1].x += 1;
			ip[0].x += 2;
			goto lvl0_start;
			break;

		case 3:
			i1 = 1;
			posy[1] -= stride[1];
			posy[0] -= stride[0]<<1;
			goto lvl0_start;
			break;

		case 1:
			ip[1].x -= 1;
			ip[0].x -= 2;
			break;
	}

	// Level 2 average and write pixel to mipmap
	pix[2][i2] = _mm_mul_ps(_mm_set_ps1(0.25f), _mm_add_ps(_mm_add_ps(pix[1][0], pix[1][1]) , _mm_add_ps(pix[1][2], pix[1][3])));
	m->set_pixel_ps(rp[2], posy[2] + ip[2].x, pix[2][i2]);

	switch (i2)
	{
		case 0:
			i2 = 2;
			posy[2] += stride[2];
			posy[1] += stride[1]<<1;
			posy[0] += stride[0]<<2;
			goto lvl1_start;
			break;

		case 2:
			i2 = 3;
			ip[2].x += 1;
			ip[1].x += 2;
			ip[0].x += 4;
			goto lvl1_start;
			break;

		case 3:
			i2 = 1;
			posy[2] -= stride[2];
			posy[1] -= stride[1]<<1;
			posy[0] -= stride[0]<<2;
			goto lvl1_start;
			break;

		case 1:
			ip[2].x -= 1;
			ip[1].x -= 2;
			ip[0].x -= 4;
			break;
	}

	// Level 3 average and write pixel to mipmap
	pix[3][i3] = _mm_mul_ps(_mm_set_ps1(0.25f), _mm_add_ps(_mm_add_ps(pix[2][0], pix[2][1]) , _mm_add_ps(pix[2][2], pix[2][3])));
	m->set_pixel_ps(rp[3], posy[3] + ip[3].x, pix[3][i3]);

	switch (i3)
	{
		case 0:
			i3 = 2;
			posy[3] += stride[3];
			posy[2] += stride[2]<<1;
			posy[1] += stride[1]<<2;
			posy[0] += stride[0]<<3;
			goto lvl2_start;
			break;

		case 2:
			i3 = 3;
			ip[3].x += 1;
			ip[2].x += 2;
			ip[1].x += 4;
			ip[0].x += 8;
			goto lvl2_start;
			break;

		case 3:
			i3 = 1;
			posy[3] -= stride[3];
			posy[2] -= stride[2]<<1;
			posy[1] -= stride[1]<<2;
			posy[0] -= stride[0]<<3;
			goto lvl2_start;
			break;

		case 1:
			ip[3].x -= 1;
			ip[2].x -= 2;
			ip[1].x -= 4;
			ip[0].x -= 8;
			break;
	}

	// Level 4 average and write pixel to mipmap
	pix[4][i4] = _mm_mul_ps(_mm_set_ps1(0.25f), _mm_add_ps(_mm_add_ps(pix[3][0], pix[3][1]) , _mm_add_ps(pix[3][2], pix[3][3])));
	m->set_pixel_ps(rp[4], posy[4] + ip[4].x, pix[4][i4]);

	return pix[4][0];
}
#undef LC

__m128 mipmap_make_fast_pixel_recursively(mipmap_t *m, const int il0, const xyi_t ir0, xyi_t ip0)
{
	__m128 pix0, pix1, pix2, pix3;
	int il1;
	xyi_t ip1, ir1, ge;
	mipmap_level_t *ml;
	raster_t *rp;

	// Calculate the next values
	il1 = il0-1;			// next mipmap level
	ip1 = lshift_xyi(ip0, 1);	// next pixel start position (tile-relative)
	ir1 = lshift_xyi(ir0, 1);	// next tile position

	// Adjust values if the next 4 pixels are on another tile
	ge = cmp_ge_xyi(ip1, m->lvl[il1].tiledim);	// 1 if we must move to the next tile
	ir1 = add_xyi(ir1, ge);
	ip1 = sub_xyi(ip1, mul_xyi(ge, m->lvl[il1].tiledim));

	switch (il1)
	{
		case 4:
			// Obtain the four needed pixels using epic spaghetti code
			pix0 = mipmap_make_fast_pixel_lvl4(m, ir1, ip1);
			ip1.x++;
			pix1 = mipmap_make_fast_pixel_lvl4(m, ir1, ip1);
			ip1.y++;
			pix3 = mipmap_make_fast_pixel_lvl4(m, ir1, ip1);
			ip1.x--;
			pix2 = mipmap_make_fast_pixel_lvl4(m, ir1, ip1);
			break;

		case 0:
			// Read the four pixels from mipmap level 0
			ml = &m->lvl[il1];
			rp = &ml->r[ir1.y * ml->tilecount.x + ir1.x];
			pix0 = m->get_pixel_ps(rp, ip1.y * rp->dim.x + ip1.x);
			pix1 = m->get_pixel_ps(rp, ip1.y * rp->dim.x + ip1.x+1);
			pix2 = m->get_pixel_ps(rp, (ip1.y+1) * rp->dim.x + ip1.x);
			pix3 = m->get_pixel_ps(rp, (ip1.y+1) * rp->dim.x + ip1.x+1);
			break;

		default:
			// Recursively obtain the four needed pixels
			pix0 = mipmap_make_fast_pixel_recursively(m, il1, ir1, ip1);
			ip1.x++;
			pix1 = mipmap_make_fast_pixel_recursively(m, il1, ir1, ip1);
			ip1.y++;
			pix3 = mipmap_make_fast_pixel_recursively(m, il1, ir1, ip1);
			ip1.x--;
			pix2 = mipmap_make_fast_pixel_recursively(m, il1, ir1, ip1);
	}

	// Average the 4 pixels into one
	pix0 = _mm_add_ps(pix0, pix1);
	pix2 = _mm_add_ps(pix2, pix3);
	pix0 = _mm_add_ps(pix0, pix2);
	pix0 = _mm_mul_ps(pix0, _mm_set_ps1(0.25f));

	// Write the pixel to the mipmap
	ml = &m->lvl[il0];
	rp = &ml->r[ir0.y * ml->tilecount.x + ir0.x];
	m->set_pixel_ps(rp, ip0.y * rp->dim.x + ip0.x, pix0);

	return pix0;
}

__m128 mipmap_make_edge_pixel_recursively(mipmap_t *m, const int il0, const xyi_t ir0, xyi_t ip0, const int end_lvl)
{
	__m128 pix0, pix1, pix2, pix3;
	int il1, exist[4]={0};
	xyi_t ip1, ir1, ge;
	mipmap_level_t *ml;
	raster_t *rp;

	// Calculate the next values
	il1 = il0-1;			// next mipmap level
	ip1 = lshift_xyi(ip0, 1);	// next pixel start position (tile-relative)
	ir1 = lshift_xyi(ir0, 1);	// next tile position

	// Adjust values if the next 4 pixels are on another tile
	ge = cmp_ge_xyi(ip1, m->lvl[il1].tiledim);	// 1 if we must move to the next tile
	ir1 = add_xyi(ir1, ge);
	ip1 = sub_xyi(ip1, mul_xyi(ge, m->lvl[il1].tiledim));

	ml = &m->lvl[il1];
	rp = &ml->r[ir1.y * ml->tilecount.x + ir1.x];

	// Check if the pixels all exist
	exist[1] = (ip1.x+1 < rp->dim.x);
	exist[2] = (ip1.y+1 < rp->dim.y);
	exist[3] = (ip1.x+1 < rp->dim.x && ip1.y+1 < rp->dim.y);

	if (exist[1]==0) pix1 = _mm_setzero_ps();
	if (exist[2]==0) pix2 = _mm_setzero_ps();
	if (exist[3]==0) pix3 = _mm_setzero_ps();

	if (il1==end_lvl)
	{
		// Read the four pixels from mipmap level 0
		pix0 = m->get_pixel_ps(rp, ip1.y * rp->dim.x + ip1.x);
		if (exist[1]) pix1 = m->get_pixel_ps(rp, ip1.y * rp->dim.x + ip1.x+1);
		if (exist[2]) pix2 = m->get_pixel_ps(rp, (ip1.y+1) * rp->dim.x + ip1.x);
		if (exist[3]) pix3 = m->get_pixel_ps(rp, (ip1.y+1) * rp->dim.x + ip1.x+1);
	}
	else
	{
		// Recursively obtain the four needed pixels
		pix0 = mipmap_make_edge_pixel_recursively(m, il1, ir1, ip1, end_lvl);
		ip1.x++;
		if (exist[1]) pix1 = mipmap_make_edge_pixel_recursively(m, il1, ir1, ip1, end_lvl);
		ip1.y++;
		if (exist[3]) pix3 = mipmap_make_edge_pixel_recursively(m, il1, ir1, ip1, end_lvl);
		ip1.x--;
		if (exist[2]) pix2 = mipmap_make_edge_pixel_recursively(m, il1, ir1, ip1, end_lvl);
	}

	// Average the 4 pixels into one
	pix0 = _mm_add_ps(pix0, pix1);
	pix2 = _mm_add_ps(pix2, pix3);
	pix0 = _mm_add_ps(pix0, pix2);
	pix0 = _mm_mul_ps(pix0, _mm_set_ps1(0.25f));

	// Write the pixel to the mipmap
	ml = &m->lvl[il0];
	rp = &ml->r[ir0.y * ml->tilecount.x + ir0.x];
	m->set_pixel_ps(rp, ip0.y * rp->dim.x + ip0.x, pix0);

	return pix0;
}

mipmap_t raster_to_tiled_mipmaps_fast_backwards(raster_t r, xyi_t tilesize, xyi_t mindim, const int mode)
{
	int i, start_lvl=0, final_lvl;
	mipmap_t m={0};
	xyi_t ip, ipt, ir, fast_dim;
	__m128 pv;

	// Init mipmap structure
	m.fulldim = r.dim;
	m.lvl_count = 1. + log2(max_of_xy(div_xy(xyi_to_xy(m.fulldim), xyi_to_xy(mindim))));
	m.lvl_count = MAXN(m.lvl_count, 1);
	final_lvl = m.lvl_count-1;
	m.lvl = calloc(m.lvl_count, sizeof(mipmap_level_t));
	m.total_bytes = m.lvl_count * sizeof(mipmap_level_t);
	mipmap_set_functions(&m, mode);

	// Make the first level, a tiled copy of the original
	m.lvl[0].scale = set_xy(1.);
	alloc_mipmap_level(&m.lvl[0], m.fulldim, tilesize, mode);
	m.total_bytes += m.lvl[0].total_bytes;
	copy_from_raster_to_tiles(r, m.lvl[0], mode);

	if (m.lvl_count==0)
		return m;

	// Allocate all levels
	for (i=1; i < m.lvl_count; i++)
	{
		m.lvl[i].fulldim = div_round_up_xyi(m.lvl[i-1].fulldim, set_xyi(2));
		m.lvl[i].scale = mul_xy(m.lvl[i-1].scale, set_xy(2.));
		alloc_mipmap_level(&m.lvl[i], m.lvl[i].fulldim, tilesize, mode);
		m.total_bytes += m.lvl[i].total_bytes;
	}

	// Select a level to start from
	fast_dim = m.fulldim;
	for (i=m.lvl_count-1; i > 0; i--)
	{
		int fast_count, edge_count;
		fast_dim = and_xyi(m.fulldim, -(1<<i));
		fast_count = mul_x_by_y_xyi(fast_dim);
		edge_count = mul_x_by_y_xyi(m.fulldim) - fast_count;

		if (fast_count > edge_count * 50 )	// if fast pixels are > 50x more than edge pixels
		{
			start_lvl = i;
			fast_dim = rshift_xyi(fast_dim, start_lvl);
			break;
		}
	}

	// Collect the pixels
	if (start_lvl > 0)
	for (ir.y=0, ip.y=0, ipt.y=0; ip.y < fast_dim.y; ip.y++, ipt.y++)
	{
		if (ipt.y == m.lvl[start_lvl].tiledim.y)	// if we need to move to the next tile
		{
			ir.y++;
			ipt.y = 0;
		}

		// Fast pixels
		for (ir.x=0, ip.x=0, ipt.x=0; ip.x < fast_dim.x; ip.x++, ipt.x++)
		{
			if (ipt.x == m.lvl[start_lvl].tiledim.x)
			{
				ir.x++;
				ipt.x = 0;
			}

			mipmap_make_fast_pixel_recursively(&m, start_lvl, ir, ipt);
		}

		// Right edge pixels
		for (; ip.x < m.lvl[start_lvl].fulldim.x; ip.x++, ipt.x++)
		{
			if (ipt.x == m.lvl[start_lvl].tiledim.x)
			{
				ir.x++;
				ipt.x = 0;
			}

			mipmap_make_edge_pixel_recursively(&m, start_lvl, ir, ipt, 0);
		}
	}

	// Collect the potential bottom edge pixels
	if (start_lvl > 0)
	if (fast_dim.y < m.lvl[start_lvl].fulldim.y)
	for (; ip.y < m.lvl[start_lvl].fulldim.y; ip.y++, ipt.y++)
	{
		if (ipt.y == m.lvl[start_lvl].tiledim.y)	// if we need to move to the next tile
		{
			ir.y++;
			ipt.y = 0;
		}

		for (ir.x=0, ip.x=0, ipt.x=0; ip.x < m.lvl[start_lvl].fulldim.x; ip.x++, ipt.x++)
		{
			if (ipt.x == m.lvl[start_lvl].tiledim.x)
			{
				ir.x++;
				ipt.x = 0;
			}

			mipmap_make_edge_pixel_recursively(&m, start_lvl, ir, ipt, 0);
		}
	}

	// Collect the pixels for the remaining levels
	if (final_lvl > start_lvl)
	for (ir.y=0, ip.y=0, ipt.y=0; ip.y < m.lvl[final_lvl].fulldim.y; ip.y++, ipt.y++)
	{
		if (ipt.y == m.lvl[final_lvl].tiledim.y)	// if we need to move to the next tile
		{
			ir.y++;
			ipt.y = 0;
		}

		// All pixels
		for (ir.x=0, ip.x=0, ipt.x=0; ip.x < m.lvl[final_lvl].fulldim.x; ip.x++, ipt.x++)
		{
			if (ipt.x == m.lvl[final_lvl].tiledim.x)
			{
				ir.x++;
				ipt.x = 0;
			}

			mipmap_make_edge_pixel_recursively(&m, final_lvl, ir, ipt, start_lvl);
		}
	}

	return m;
}

#endif

mipmap_t raster_to_tiled_mipmaps_fast_defaults(raster_t r, const int mode)
{
	#ifdef RL_INTEL_INTR
	if (check_ssse3() && check_sse41())
		return raster_to_tiled_mipmaps_fast_backwards(r, set_xyi(MIPMAP_TILE_SIZE), set_xyi(MIPMAP_MIN_SIZE), mode);
	#endif

	return raster_to_tiled_mipmaps_fast(r, set_xyi(MIPMAP_TILE_SIZE), set_xyi(MIPMAP_MIN_SIZE), mode);
}

mipmap_t raster_to_mipmap_then_free(raster_t *r, const int mode)
{
	mipmap_t mm;

	mm = raster_to_tiled_mipmaps_fast_defaults(*r, mode);
	free_raster(r);

	return mm;
}

void free_mipmap_level(mipmap_level_t *ml)
{
	int i;

	if (ml->r == NULL)
		return;

	//for (i=0; i < mul_x_by_y_xyi(ml->tilecount); i++)
	//	free_raster(&ml->r[i]);
	free_raster(&ml->r[0]);		// contiguous allocation
	free(ml->r);

	memset(ml, 0, sizeof(mipmap_level_t));
}

void free_mipmap(mipmap_t *m)
{
	int i;

	if (m==NULL)
		return;

	if (m->lvl)
		for (i=0; i < m->lvl_count; i++)
			free_mipmap_level(&m->lvl[i]);
	free(m->lvl);

	memset(m, 0, sizeof(mipmap_t));
}

void free_mipmap_array(mipmap_t *m, int count)
{
	int i;

	if (m == NULL)
		return ;

	for (i=0; i < count; i++)
		free_mipmap(&m[i]);
}

void remove_mipmap_levels_above_dim(mipmap_t *m, xyi_t dim)
{
	int i;

	for (i=0; i < m->lvl_count; i++)
		if (m->lvl[i].fulldim.x > dim.x || m->lvl[i].fulldim.y > dim.y)
		{
			m->total_bytes -= m->lvl[i].total_bytes;
			free_mipmap_level(&m->lvl[i]);
		}
}

void blit_mipmap_rotated(mipmap_t m, xy_t pscale, xy_t pos, double angle, xy_t rot_centre, int interp)
{
	int i;
	xyi_t it;
	xy_t pscale_inv = inv_xy(pscale), ml_scale;
	mipmap_level_t *ml = &m.lvl[0];

	// find the right mipmap level
	for (i=1; i < m.lvl_count; i++)
		if (m.lvl[i].r)			// skip over any lower level that have might been removed to save memory
			if ((m.lvl[i].scale.x <= pscale_inv.x && m.lvl[i].scale.y <= pscale_inv.y) || ml->r==NULL)
				ml = &m.lvl[i];
			else
				break;

	ml_scale = mul_xy(ml->scale, pscale);
	pos = sub_xy( mad_xy(ml_scale, set_xy(0.5), pos) , mul_xy(pscale, set_xy(0.5)) );	// add an offset necessary for higher mipmap levels

	for (it.y=0; it.y < ml->tilecount.y; it.y++)
		for (it.x=0; it.x < ml->tilecount.x; it.x++)
			blit_scale_rotated(&ml->r[it.y*ml->tilecount.x + it.x], ml_scale, mad_xy(ml_scale, xyi_to_xy(mul_xyi(it, ml->tiledim)), pos), angle, rot_centre, interp);
}

rect_t blit_mipmap_in_rect_rotated(mipmap_t m, rect_t r, int keep_aspect_ratio, double angle, xy_t rot_centre, int interp)
{
	xy_t pscale, pos;
	rect_t image_frame = r;

	if (m.lvl_count < 1 || m.lvl==NULL)
		return wc_rect(image_frame);

	if (keep_aspect_ratio)
		image_frame = fit_rect_in_area( xyi_to_xy(m.fulldim), image_frame, xy(0.5, 0.5) );

	pscale = div_xy(get_rect_dim(image_frame), xyi_to_xy(m.fulldim));
	pos = mad_xy(pscale, set_xy(0.5), keep_aspect_ratio ? image_frame.p0 : rect_p01(image_frame));

	blit_mipmap_rotated(m, pscale, pos, angle, rot_centre, interp);

	return wc_rect(image_frame);
}

int get_largest_mipmap_lvl_index(mipmap_t m)
{
	int i;

	for (i=0; i < m.lvl_count; i++)
		if (m.lvl[i].r)
			return i;

	return -1;
}

xyi_t get_largest_mipmap_lvl_dim(mipmap_t m)
{
	int i;

	for (i=0; i < m.lvl_count; i++)
		if (m.lvl[i].r)
			return m.lvl[i].fulldim;

	return xyi(0, 0);
}

void fwrite_mipmap(FILE *file, mipmap_t m)
{
	int il, ir;

	// Write top level info
	fwrite_byte8(file, m.lvl_count);
	fwrite_LE32(file, m.fulldim.x);
	fwrite_LE32(file, m.fulldim.y);
	fwrite_LE32(file, m.total_bytes);

	// Write each level
	for (il=0; il < m.lvl_count; il++)
	{
		fwrite_LE32(file, m.lvl[il].fulldim.x);
		fwrite_LE32(file, m.lvl[il].fulldim.y);
		fwrite_LE16(file, m.lvl[il].tiledim.x);
		fwrite_LE16(file, m.lvl[il].tiledim.y);
		fwrite_LE16(file, m.lvl[il].tilecount.x);
		fwrite_LE16(file, m.lvl[il].tilecount.y);
		fwrite_LE32(file, float_as_u32(m.lvl[il].scale.x));
		fwrite_LE32(file, float_as_u32(m.lvl[il].scale.y));
		fwrite_LE32(file, m.lvl[il].total_bytes);

		// Write each tile
		for (ir=0; ir < mul_x_by_y_xyi(m.lvl[il].tilecount); ir++)
		{
			raster_t r = m.lvl[il].r[ir];

			fwrite_LE16(file, r.dim.x);
			fwrite_LE16(file, r.dim.y);
			int mode = get_raster_mode(r);
			fwrite_byte8(file, mode);
			if (mode == IMAGE_USE_BUF)
			{
				fwrite_byte8(file, r.buf_fmt);
				fwrite_LE32(file, r.buf_size);
			}

			// Write pixel data buffer
			void *p = get_raster_buffer_for_mode(r, mode);
			fwrite(p, get_raster_mode_elem_size(mode), mode == IMAGE_USE_BUF ? r.buf_size : mul_x_by_y_xyi(r.dim), file);
		}
	}
}

mipmap_t fread_mipmap(FILE *file)
{
	mipmap_t m={0};
	int il, ir;
	uint8_t *ptr;

	// Read top level info
	m.lvl_count = fread_byte8(file);
	m.lvl = calloc(m.lvl_count, sizeof(mipmap_level_t));
	m.fulldim.x = fread_LE32(file);
	m.fulldim.y = fread_LE32(file);
	m.total_bytes = fread_LE32(file);

	// Read each level
	for (il=0; il < m.lvl_count; il++)
	{
		m.lvl[il].fulldim.x = fread_LE32(file);
		m.lvl[il].fulldim.y = fread_LE32(file);
		m.lvl[il].tiledim.x = fread_LE16(file);
		m.lvl[il].tiledim.y = fread_LE16(file);
		m.lvl[il].tilecount.x = fread_LE16(file);
		m.lvl[il].tilecount.y = fread_LE16(file);
		m.lvl[il].scale.x = u32_as_float(fread_LE32(file));
		m.lvl[il].scale.y = u32_as_float(fread_LE32(file));
		m.lvl[il].total_bytes = fread_LE32(file);

		// Alloc contiguous pixel buffer for whole mipmap level
		ptr = calloc(m.lvl[il].total_bytes - mul_x_by_y_xyi(m.lvl[il].tilecount) * sizeof(raster_t), 1);

		// Alloc array of tiles
		if (mul_x_by_y_xyi(m.lvl[il].tilecount))
			m.lvl[il].r = malloc(mul_x_by_y_xyi(m.lvl[il].tilecount) * sizeof(raster_t));
		else
			m.lvl[il].r = NULL;

		// Read each tile
		for (ir=0; ir < mul_x_by_y_xyi(m.lvl[il].tilecount); ir++)
		{
			raster_t r={0};

			r.dim.x = fread_LE16(file);
			r.dim.y = fread_LE16(file);
			int mode = fread_byte8(file);

			// Point to contiguous data buffer
			r = make_raster(ptr, r.dim, XYI0, mode);

			if (mode == IMAGE_USE_BUF)
			{
				r.buf_fmt = fread_byte8(file);
				r.buf_size = fread_LE32(file);
			}

			// Read pixel data buffer
			int elem_size = get_raster_mode_elem_size(mode);
			fread(ptr, elem_size, mode == IMAGE_USE_BUF ? r.buf_size : mul_x_by_y_xyi(r.dim), file);

			m.lvl[il].r[ir] = r;
			if (mode == IMAGE_USE_BUF)
				ptr = &ptr[r.buf_size];
			else
				ptr = &ptr[mul_x_by_y_xyi(r.dim) * elem_size];
		}
	}

	return m;
}
