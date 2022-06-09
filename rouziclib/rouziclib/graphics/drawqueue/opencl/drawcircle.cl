float4 draw_circle_full_add(global float *le, float4 pv, const float2 pf)
{
	float4 col;
	float2 pc;
	float circrad, rad, dc, dn, df;

	pc.x = le[0];
	pc.y = le[1];
	circrad = le[2];
	rad = le[3];
	col.s0 = le[4];
	col.s1 = le[5];
	col.s2 = le[6];
	col.s3 = 1.f;

	dc = fast_distance(pf, pc);	// Distance to center
	dn = (circrad - dc) * rad;	// Near edge distance
	df = -(circrad + dc) * rad;	// Far edge distance

	pv += (erf_fast(dn) - erf_fast(df)) * 0.5f * col;

	return pv;
}

float4 draw_circle_hollow_add(global float *le, float4 pv, const float2 pf)
{
	float4 col;
	float2 pc;
	float circrad, rad, dc, dn, df;

	pc.x = le[0];
	pc.y = le[1];
	circrad = le[2];
	rad = le[3];
	col.s0 = le[4];
	col.s1 = le[5];
	col.s2 = le[6];
	col.s3 = 1.f;

	dc = fast_distance(pf, pc);	// Distance to center
	dn = (circrad - dc) * rad;	// Near edge distance
	df = -(circrad + dc) * rad;	// Far edge distance

	pv += (gaussian(dn) + gaussian(df)) * col;

	return pv;
}
