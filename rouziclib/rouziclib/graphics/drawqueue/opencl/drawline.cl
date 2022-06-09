float4 draw_line_thin_add(global float *le, float4 pv, const float2 pf)
{
	float v, r1x, r1y, r2x, costh, sinth;
	float2 rp;
	float4 col;

	r1x = le[0];
	r1y = le[1];
	r2x = le[2];
	costh = le[3];
	sinth = le[4];
	col.s0 = le[5];
	col.s1 = le[6];
	col.s2 = le[7];
	col.s3 = le[8];

	// 40 FR without branching
	rp.x = pf.x * costh - pf.y * sinth;	// 3 FR
	rp.y = pf.x * sinth + pf.y * costh;	// 2 FR

	v = (erf_fast(rp.x-r1x) - erf_fast(rp.x-r2x)) * 0.5f;	// 26 FR
	v *= gaussian(rp.y-r1y);				// 8 FR
	pv += v * col;						// 1 FR

	return pv;
}

float4 draw_point_add(global float *le, float4 pv, const float2 pf)
{
	float rad, d;
	float2 dp;
	float4 col;

	dp.x = le[0];
	dp.y = le[1];
	rad = le[2];
	col.s0 = le[3];
	col.s1 = le[4];
	col.s2 = le[5];
	col.s3 = 1.f;

	d = fast_distance(dp, pf) * rad;	// distance of the pixel from the centre of the dot, scaled

	pv += gaussian(d) * col;

	return pv;
}
