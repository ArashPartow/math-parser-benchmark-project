#ifdef RL_INTEL_INTR

void dqsb_draw_plain_fill_add(float *le, float *block, int chan_stride)    // SSE
{
	__m128 *bp=(__m128 *) block, col[4];
	int ic, ib=0;

	// Load parameters
	col[0] = _mm_set_ps1(le[0]);
	col[1] = _mm_set_ps1(le[1]);
	col[2] = _mm_set_ps1(le[2]);
	col[3] = _mm_set_ps1(1.f);

	// Add colour plane after plane
	for (ic=0; ic < 4; ic++)
		for (ib=0; ib < chan_stride; ib+=4, bp=&bp[1])
			*bp = _mm_add_ps(*bp, col[ic]);
}

void dqsb_draw_rect_full_add(float *le, float *block, xy_t start_pos, const int bs, int chan_stride)	// SSE2
{
	// Generic variables
	xyi_t ip;
	float y, x;
	__m128 yv, xv, *bp;
	int ic, ib=0;

	// Specific variables
	__m128 p0x, p0y, p1x, p1y, rad, col[4];
	__m128 d0x, d0y, d1x, d1y, weight, wy;
	const float gl = DQS_GAUSS_LIMIT;

	// Load parameters
	p0x = _mm_set_ps1(le[0]);
	p0y = _mm_set_ps1(le[1]);
	p1x = _mm_set_ps1(le[2]);
	p1y = _mm_set_ps1(le[3]);
	rad = _mm_set_ps1(le[4]);
	col[0] = _mm_set_ps1(le[5]);
	col[1] = _mm_set_ps1(le[6]);
	col[2] = _mm_set_ps1(le[7]);
	col[3] = _mm_set_ps1(1.f);

	for (y=start_pos.y, ip.y=0; ip.y < bs; ip.y++, y+=1.f)
	{
		yv = _mm_set_ps1(y);

		for (x=start_pos.x, ip.x=0; ip.x < bs; ip.x+=4, x+=4.f, ib+=4)
		{
			// Initialise coordinates
			xv = _mm_add_ps(_mm_set_ps1(x), _mm_set_ps(3.f, 2.f, 1.f, 0.f));

			// Distances
			d0x = _mm_mul_ps(_mm_sub_ps(xv, p0x), rad);
			d0y = _mm_mul_ps(_mm_sub_ps(yv, p0y), rad);
			d1x = _mm_mul_ps(_mm_sub_ps(xv, p1x), rad);
			d1y = _mm_mul_ps(_mm_sub_ps(yv, p1y), rad);

			// Distance checks
			if (_mm_movemask_ps(_mm_cmpgt_ps(d0x, _mm_set_ps1(-gl)))
			&   _mm_movemask_ps(_mm_cmpgt_ps(d0y, _mm_set_ps1(-gl)))
			&   _mm_movemask_ps(_mm_cmplt_ps(d1x, _mm_set_ps1(gl)))
			&   _mm_movemask_ps(_mm_cmplt_ps(d1y, _mm_set_ps1(gl))))
			{
				// Ends distance checks
				int d0xc = _mm_movemask_ps(_mm_cmplt_ps(d0x, _mm_set_ps1(gl)));		// 0 if all are far from end
				int d0yc = _mm_movemask_ps(_mm_cmplt_ps(d0y, _mm_set_ps1(gl)));
				int d1xc = _mm_movemask_ps(_mm_cmpgt_ps(d1x, _mm_set_ps1(-gl)));
				int d1yc = _mm_movemask_ps(_mm_cmpgt_ps(d1y, _mm_set_ps1(-gl)));

				// Compute pixel x weight
				if (d0xc | d1xc)
				{
					if (d0xc && d1xc)	// if both ends are covered
						weight = _mm_sub_ps( _mm_erfr_d1_ps(d0x) , _mm_erfr_d1_ps(d1x) );
					else if (d0xc)
						weight = _mm_erfr_d1_ps(d0x);
					else
						weight = _mm_erfr_d1_ps(_mm_neg_ps(d1x));
				}
				else
					weight = _mm_set_ps1(1.f);

				// Compute pixel y weight
				if (d0yc | d1yc)
				{
					if (d0yc && d1yc)	// if both ends are covered
						wy = _mm_sub_ps( _mm_erfr_d1_ps(d0y) , _mm_erfr_d1_ps(d1y) );
					else if (d0yc)
						wy = _mm_erfr_d1_ps(d0y);
					else
						wy = _mm_erfr_d1_ps(_mm_neg_ps(d1y));

					weight = _mm_mul_ps(weight, wy);
				}

				// Add weighted colour
				for (ic=0; ic < 4; ic++)
				{
					bp = (__m128 *) &block[ic*chan_stride + ib];
					*bp = _mm_add_ps(_mm_mul_ps(weight, col[ic]), *bp);
				}
			}
		}
	}
}

void dqsb_draw_black_rect(float *le, float *block, xy_t start_pos, const int bs, int chan_stride)	// SSE2
{
	// Generic variables
	xyi_t ip;
	float y, x;
	__m128 yv, xv, *bp;
	int ic, ib=0;

	// Specific variables
	__m128 p0x, p0y, p1x, p1y, rad, intensity;
	__m128 d0x, d0y, d1x, d1y, weight, wy;
	const float gl = DQS_GAUSS_LIMIT;

	// Load parameters
	p0x = _mm_set_ps1(le[0]);
	p0y = _mm_set_ps1(le[1]);
	p1x = _mm_set_ps1(le[2]);
	p1y = _mm_set_ps1(le[3]);
	rad = _mm_set_ps1(le[4]);
	intensity = _mm_set_ps1(le[5]);

	for (y=start_pos.y, ip.y=0; ip.y < bs; ip.y++, y+=1.f)
	{
		yv = _mm_set_ps1(y);

		for (x=start_pos.x, ip.x=0; ip.x < bs; ip.x+=4, x+=4.f, ib+=4)
		{
			// Initialise coordinates
			xv = _mm_add_ps(_mm_set_ps1(x), _mm_set_ps(3.f, 2.f, 1.f, 0.f));

			// Distances
			d0x = _mm_mul_ps(_mm_sub_ps(xv, p0x), rad);
			d0y = _mm_mul_ps(_mm_sub_ps(yv, p0y), rad);
			d1x = _mm_mul_ps(_mm_sub_ps(xv, p1x), rad);
			d1y = _mm_mul_ps(_mm_sub_ps(yv, p1y), rad);

			// Distance checks
			if (_mm_movemask_ps(_mm_cmpgt_ps(d0x, _mm_set_ps1(-gl)))
			&   _mm_movemask_ps(_mm_cmpgt_ps(d0y, _mm_set_ps1(-gl)))
			&   _mm_movemask_ps(_mm_cmplt_ps(d1x, _mm_set_ps1(gl)))
			&   _mm_movemask_ps(_mm_cmplt_ps(d1y, _mm_set_ps1(gl))))
			{
				// Ends distance checks
				int d0xc = _mm_movemask_ps(_mm_cmplt_ps(d0x, _mm_set_ps1(gl)));		// 0 if all are far from end
				int d0yc = _mm_movemask_ps(_mm_cmplt_ps(d0y, _mm_set_ps1(gl)));
				int d1xc = _mm_movemask_ps(_mm_cmpgt_ps(d1x, _mm_set_ps1(-gl)));
				int d1yc = _mm_movemask_ps(_mm_cmpgt_ps(d1y, _mm_set_ps1(-gl)));

				// Compute pixel x weight
				if (d0xc | d1xc)
				{
					if (d0xc && d1xc)	// if both ends are covered
						weight = _mm_sub_ps( _mm_erfr_d1_ps(d0x) , _mm_erfr_d1_ps(d1x) );
					else if (d0xc)
						weight = _mm_erfr_d1_ps(d0x);
					else
						weight = _mm_erfr_d1_ps(_mm_neg_ps(d1x));
				}
				else
					weight = _mm_set_ps1(1.f);

				// Compute pixel y weight
				if (d0yc | d1yc)
				{
					if (d0yc && d1yc)	// if both ends are covered
						wy = _mm_sub_ps( _mm_erfr_d1_ps(d0y) , _mm_erfr_d1_ps(d1y) );
					else if (d0yc)
						wy = _mm_erfr_d1_ps(d0y);
					else
						wy = _mm_erfr_d1_ps(_mm_neg_ps(d1y));

					weight = _mm_mul_ps(weight, wy);
				}

				weight = _mm_mul_ps(weight, intensity);

				// Add weighted colour
				for (ic=0; ic < 4; ic++)
				{
					bp = (__m128 *) &block[ic*chan_stride + ib];
					*bp = _mm_mul_ps(_mm_sub_ps(_mm_set_ps1(1.f), weight), *bp);
				}
			}
		}
	}
}

#endif
