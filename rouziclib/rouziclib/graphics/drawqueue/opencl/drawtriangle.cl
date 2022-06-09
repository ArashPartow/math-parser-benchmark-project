float erf_right_triangle_acute_integral(float x, float y)
{
	float x2 = x*x, y2 = y*y;
	float v = (((((-1.6663128e-05f*y2 + 5.104393e-06f)*x2 +
			0.0005496131f*y2 - 5.30433e-05f)*x2 +
			(0.0001584783f*y2 - 0.00741157237f)*y2 - 0.0018265954f)*x2 +
			(-0.003881739f*y2 + 0.0523013844f)*y2 + 0.04582956f)*x2 +
			((-0.00368418f*y2 + 0.03692744f)*y2 - 0.1996548f)*y2 - 0.50360028f)*x2 +
			((-0.0012717f*y2 - 0.0101518f)*y2 + 0.0109084f)*y2 - 1.836892f;
	return native_exp(v) * x2 * y;	// 25 FR
}

float calc_right_triangle_pixel_weight(float2 rp)
{
	float2 rpa;
	int use_obtuse;
	float slope, acute, obtuse;

	rpa = fabs(rp);

	// Pick method
	use_obtuse = rpa.y > rpa.x;
	if (use_obtuse)			// if we use the obtuse method
	{
		// Swap axes
		float t = rp.x;
		rp.x = rp.y;
		rp.y = t;
	}

	// Prepare the arguments (slope and clamped x)
	slope = fabs(rp.x) < 1e-5f ? 0.f : rp.y / rp.x;
	slope = clamp(slope, -1.f, 1.f);
	rp.x = clamp(rp.x, -3.f, 3.f);

	acute = erf_right_triangle_acute_integral(rp.x, slope);
	obtuse = 0.25f * erf_fast(rp.y) * erf_fast(rp.x) - acute;
	acute = copysign(acute, slope);
	obtuse = copysign(obtuse, slope);

	return use_obtuse ? obtuse : acute;
}

float calc_subtriangle_pixel_weight(float2 p0, float2 p1)
{
	float2 rot, r0, r1;
	float weight;

	// Rotate points
	rot = fast_normalize(p1 - p0);
	r0.x = rot.x*p0.y - rot.y*p0.x;
	r0.y = rot.x*p0.x + rot.y*p0.y;
	r1.x = r0.x;
	r1.y = rot.x*p1.x + rot.y*p1.y;

	// Calc weights
	weight = calc_right_triangle_pixel_weight(r1);
	weight -= calc_right_triangle_pixel_weight(r0);

	return weight;
}

float4 draw_triangle(global float *le, float4 pv, const float2 pf)
{
	float rad, weight;
	float2 p0, p1, p2;
	float4 col;

	// Load parameters
	rad = le[0];
	col.s0 = le[1];
	col.s1 = le[2];
	col.s2 = le[3];
	col.s3 = 1.f;
	p0.x = le[4];
	p0.y = le[5];
	p1.x = le[6];
	p1.y = le[7];
	p2.x = le[8];
	p2.y = le[9];

	// Transform triangle coordinates
	p0 = (p0 - pf) * rad;
	p1 = (p1 - pf) * rad;
	p2 = (p2 - pf) * rad;

	// Calculate weight for each subtriangle
	weight = calc_subtriangle_pixel_weight(p0, p1);
	weight += calc_subtriangle_pixel_weight(p1, p2);
	weight += calc_subtriangle_pixel_weight(p2, p0);

	// Apply weight to colour
	pv += weight * col;

	return pv;
}

float4 draw_tetragon(global float *le, float4 pv, const float2 pf)
{
	float rad, weight;
	float2 p0, p1, p2, p3;
	float4 col;

	// Load parameters
	rad = le[0];
	col.s0 = le[1];
	col.s1 = le[2];
	col.s2 = le[3];
	col.s3 = 1.f;
	p0.x = le[4];
	p0.y = le[5];
	p1.x = le[6];
	p1.y = le[7];
	p2.x = le[8];
	p2.y = le[9];
	p3.x = le[10];
	p3.y = le[11];

	// Transform polygon coordinates
	p0 = (p0 - pf) * rad;
	p1 = (p1 - pf) * rad;
	p2 = (p2 - pf) * rad;
	p3 = (p3 - pf) * rad;

	// Calculate weight for each subtriangle
	weight = calc_subtriangle_pixel_weight(p0, p1);
	weight += calc_subtriangle_pixel_weight(p1, p2);
	weight += calc_subtriangle_pixel_weight(p2, p3);
	weight += calc_subtriangle_pixel_weight(p3, p0);

	// Apply weight to colour
	pv += weight * col;

	return pv;
}
