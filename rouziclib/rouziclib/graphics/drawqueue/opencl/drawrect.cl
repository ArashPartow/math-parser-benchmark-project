float4 draw_plain_fill_add(global float *le, float4 pv)
{
	float4 col;

	col.s0 = le[0];
	col.s1 = le[1];
	col.s2 = le[2];
	col.s3 = 1.f;

	pv += col;

	return pv;
}

float4 draw_rect_full_add(global float *le, float4 pv, const float2 pf)
{
	float rad, d;
	float2 p0, p1, d0, d1, gv;
	float4 col;

	p0.x = le[0];
	p0.y = le[1];
	p1.x = le[2];
	p1.y = le[3];
	rad = le[4];
	col.s0 = le[5];
	col.s1 = le[6];
	col.s2 = le[7];
	col.s3 = 1.f;

	d0 = (pf - p0) * rad;
	d1 = (pf - p1) * rad;

	gv.x = erf_fast(d0.x) - erf_fast(d1.x);
	gv.y = erf_fast(d0.y) - erf_fast(d1.y);

	pv += gv.x*gv.y*0.25f * col;

	return pv;
}

float4 draw_black_rect(global float *le, float4 pv, const float2 pf)
{
	float rad, d, intensity;
	float2 p0, p1, d0, d1, gv;

	p0.x = le[0];
	p0.y = le[1];
	p1.x = le[2];
	p1.y = le[3];
	rad = le[4];
	intensity = le[5];

	d0 = (pf - p0) * rad;
	d1 = (pf - p1) * rad;

	gv.x = erf_fast(d0.x) - erf_fast(d1.x);
	gv.y = erf_fast(d0.y) - erf_fast(d1.y);

	pv *= 1.f - 0.25f*gv.x*gv.y*intensity;

	return pv;
}

float4 draw_black_rect_inv(global float *le, float4 pv, const float2 pf)
{
	float rad, d, intensity;
	float2 p0, p1, d0, d1, gv;

	p0.x = le[0];
	p0.y = le[1];
	p1.x = le[2];
	p1.y = le[3];
	rad = le[4];
	intensity = le[5];

	d0 = (pf - p0) * rad;
	d1 = (pf - p1) * rad;

	gv.x = erf_fast(d0.x) - erf_fast(d1.x);
	gv.y = erf_fast(d0.y) - erf_fast(d1.y);

	pv *= 0.25f*gv.x*gv.y * intensity + (1.f-intensity);

	return pv;
}
