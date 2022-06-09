#include "rand.cl"

float4 colour_blowout(float4 c)
{
	float maxv, t, L;
	
	maxv = max(max(c.s0, c.s1), c.s2);	// max is the maximum value of the 3 colours
	
	if (maxv > 1.f)			// if the colour is out of gamut
	{
		L = 0.16f*c.s0 + 0.73f*c.s1 + 0.11f*c.s2;	// Luminosity of the colour's grey point
		
		if (L < 1.f)		// if the grey point is no brighter than white
		{
			t = (1.f-L) / (maxv-L);
		
			c.s0 = c.s0*t + L*(1.f-t);
			c.s1 = c.s1*t + L*(1.f-t);
			c.s2 = c.s2*t + L*(1.f-t);
		}
		else			// if it's too bright regardless of saturation
		{
			c.s0 = c.s1 = c.s2 = 1.f;
		}
	}

	return c;
}

float lsrgb(float l)	// converts a [0.0, 1.0] linear value into a [0.0, 1.0] sRGB value
{
	float x, line, curve;

	// 13 FR every time + 2 FR once
	line = l * 12.92f;	// 1 FR
	x = native_sqrt(l);	// 4 FR
	curve = ((((0.455f*x - 1.48f)*x + 1.92137f)*x - 1.373254f)*x + 1.51733216f)*x - 0.0404733783f;		// 5 FR + 2 FR once, error 0.145 sRGB units

	return l <= 0.0031308f ? line : curve;	// 3 FR
}

float slrgb(float s)	// converts a [0.0, 1.0] sRGB value into a [0.0, 1.0] linear value
{
	float line, curve;

	// ~8 FR
	line = s * (1.f/12.92f);
	curve = ((((0.05757f*s - 0.2357f)*s + 0.60668f)*s + 0.540468f)*s + 0.0299805f)*s + 0.001010107f;	// error 0.051 sRGB units

	return s <= 0.04045f ? line : curve;
}

float s8lrgb(float s8)
{
	return slrgb(s8 * (1.f/255.f));
}

#define max_s 255.f

float apply_dithering(float pv, float dv)
{
	const float threshold = 1.2f / max_s;
	const float it = 1.f / threshold;
	const float rounding_offset = 0.5f / max_s;

	// Reduce the scale of the dithering if pv is close to 0
	if (pv < threshold)	// 1.2 is the threshold so that the crushing happens at 1.2*sqrt(2) = 1.7 sigma
	{
		if (pv <= 0.f)
			return 0.f;
		else
			dv *= pv * it;
	}

	// Same if pv is close to 1
	if (pv > 1.f - threshold)
	{
		if (pv >= 1.f)
			return 1.f;
		else
			dv *= (1.f-pv) * it;
	}

	return pv += dv + rounding_offset;
}

float4 linear_to_srgb(float4 pl0, uint seed)
{
	float4 pl1;
	float dith;
	const float dith_scale = M_SQRT1_2_F / max_s;

	//pl0 = mix(colour_blowout(pl0), clamp(pl0, 0.f, 1.f), 0.666f);
	pl0 = clamp(pl0, 0.f, 1.f);

	pl1.s0 = lsrgb(pl0.s0);		// blue
	pl1.s1 = lsrgb(pl0.s1);		// green
	pl1.s2 = lsrgb(pl0.s2);		// red

	// Dithering
	dith = gaussian_rand_approx(seed) * dith_scale;

	pl1.s0 = apply_dithering(pl1.s0, dith);
	pl1.s1 = apply_dithering(pl1.s1, dith);
	pl1.s2 = apply_dithering(pl1.s2, dith);

	// Lower bit depth simulation
	if (max_s < 255.f)
		pl1 = round(pl1 * max_s) * (1.f/max_s);

	return pl1;
}
