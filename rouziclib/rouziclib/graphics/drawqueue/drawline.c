#ifdef RL_INTEL_INTR

void dqsb_draw_line_thin_add(float *le, float *block, xy_t start_pos, const int bs, int chan_stride)	// SSE2
{
	// Generic variables
	xyi_t ip;
	float y, x;
	__m128 yv, xv, *bp;
	int ic, ib=0;

	// Specific variables
	__m128 r1x, r1y, r2x, costh, sinth, col[4];
	__m128 rpx, rpy, ycos, ysin, weight;
	__m128 d1y, d1x, d2x;
	const float gl = DQS_GAUSS_LIMIT;

	// Load parameters
	r1x = _mm_set_ps1(le[0]);
	r1y = _mm_set_ps1(le[1]);
	r2x = _mm_set_ps1(le[2]);
	costh = _mm_set_ps1(le[3]);
	sinth = _mm_set_ps1(le[4]);
	col[0] = _mm_set_ps1(le[5]);
	col[1] = _mm_set_ps1(le[6]);
	col[2] = _mm_set_ps1(le[7]);
	col[3] = _mm_set_ps1(le[8]);

	for (y=start_pos.y, ip.y=0; ip.y < bs; ip.y++, y+=1.f)
	{
		yv = _mm_set_ps1(y);
		ycos = _mm_mul_ps(yv, costh);
		ysin = _mm_mul_ps(yv, sinth);

		for (x=start_pos.x, ip.x=0; ip.x < bs; ip.x+=4, x+=4.f, ib+=4)
		{
			// Initialise coordinates
			xv = _mm_add_ps(_mm_set_ps1(x), _mm_set_ps(3.f, 2.f, 1.f, 0.f));

			// Rotate coordinates
			rpx = _mm_mul_ps(xv, costh);	rpy = _mm_mul_ps(xv, sinth);
			rpx = _mm_sub_ps(rpx, ysin);	rpy = _mm_add_ps(rpy, ycos);

			// Distances
			d1y = _mm_abs_ps(_mm_sub_ps(rpy, r1y));
			d2x = _mm_sub_ps(rpx, r2x);
			d1x = _mm_sub_ps(rpx, r1x);

			// Distance checks
			if (_mm_movemask_ps(_mm_cmplt_ps(d1y, _mm_set_ps1(gl)))
			&   _mm_movemask_ps(_mm_cmplt_ps(d2x, _mm_set_ps1(gl)))
			&   _mm_movemask_ps(_mm_cmpgt_ps(d1x, _mm_set_ps1(-gl))))
			{
				// Ends distance checks
				int d1c = _mm_movemask_ps(_mm_cmplt_ps(d1x, _mm_set_ps1(gl)));		// 0 if all are far from end
				int d2c = _mm_movemask_ps(_mm_cmpgt_ps(d2x, _mm_set_ps1(-gl)));

				// Compute pixel weight
				weight = _mm_gaussian_d1_ps(d1y);

				if (d1c | d2c)
				{
					if (d1c && d2c)		// if both ends are covered
						weight = _mm_mul_ps(weight, _mm_sub_ps( _mm_erfr_d1_ps(d1x) , _mm_erfr_d1_ps(d2x) ));
					else if (d1c)
						weight = _mm_mul_ps(weight, _mm_erfr_d1_ps(d1x));
					else
						weight = _mm_mul_ps(weight, _mm_erfr_d1_ps(_mm_neg_ps(d2x)));
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

void dqsb_draw_point_add(float *le, float *block, xy_t start_pos, const int bs, int chan_stride)	// SSE2
{
	// Generic variables
	xyi_t ip;
	float y, x;
	__m128 yv, xv, *bp;
	int ic, ib=0;

	// Specific variables
	__m128 cx, cy, rad, col[4];
	__m128 weight, d, dy2, dx2;
	const float gl = DQS_GAUSS_LIMIT;

	// Load parameters
	cx = _mm_set_ps1(le[0]);
	cy = _mm_set_ps1(le[1]);
	rad = _mm_set_ps1(le[2]);
	col[0] = _mm_set_ps1(le[3]);
	col[1] = _mm_set_ps1(le[4]);
	col[2] = _mm_set_ps1(le[5]);
	col[3] = _mm_set_ps1(1.f);

	for (y=start_pos.y, ip.y=0; ip.y < bs; ip.y++, y+=1.f)
	{
		yv = _mm_set_ps1(y);
		dy2 = _mm_sub_ps(yv, cy);
		dy2 = _mm_mul_ps(dy2, dy2);

		for (x=start_pos.x, ip.x=0; ip.x < bs; ip.x+=4, x+=4.f, ib+=4)
		{
			// Initialise coordinates
			xv = _mm_add_ps(_mm_set_ps1(x), _mm_set_ps(3.f, 2.f, 1.f, 0.f));
			dx2 = _mm_sub_ps(xv, cx);
			dx2 = _mm_mul_ps(dx2, dx2);

			// Distance
			d = _mm_sqrt_ps(_mm_add_ps(dx2, dy2));

			// Distance check
			if (_mm_movemask_ps(_mm_cmplt_ps(d, _mm_set_ps1(gl))))
			{
				// Compute pixel weight
				weight = _mm_gaussian_d1_ps(d);

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

#endif
