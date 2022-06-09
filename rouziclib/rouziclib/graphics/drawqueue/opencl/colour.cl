float Lab_L_to_linear(float t)
{
	const float stn=6.f/29.f;

	t = (t+0.16f) / 1.16f;

	if (t > stn)
		return t*t*t;
	else
		return 3.f*stn*stn*(t - 4.f/29.f);
}

float linear_to_Lab_L(float t)
{
	const float thr = 6.f/29.f, thr3 = thr*thr*thr;

	if (t > thr3)
		t = cbrt(t);
	else
		t = t * 841.f/108.f + 4.f/29.f;

	return 1.16f * t - 0.16f;
}

float4 gain_parabolic(float4 pv, float gain)
{
	pv = min(pv, 1.f);
	pv = 1.f - pow((1.f-pv), gain);

	return pv;
}

float4 luma_compression(float4 pv0, float lvl_lin)
{
	float4 pv1;
	float grey0_lin, grey0_perc, grey1_perc, grey1_lin, white1_perc, white1_lin, lvl_perc, ratio;

	grey0_lin = 0.16f*pv0.s0 + 0.73f*pv0.s1 + 0.11f*pv0.s2;
	if (grey0_lin==0.f)
		return pv0;

	grey0_perc = linear_to_Lab_L(grey0_lin);
	lvl_perc = linear_to_Lab_L(lvl_lin);

	grey1_perc = grey0_perc + lvl_perc;
	grey1_lin = Lab_L_to_linear(grey1_perc) - lvl_lin;

	white1_perc = 1.f + lvl_perc;
	white1_lin = Lab_L_to_linear(white1_perc) - lvl_lin;

	ratio = (grey1_lin / grey0_lin) / white1_lin;

	pv1 = pv0 * ratio;

	return pv1;
}

float4 colour_matrix(global float *le, float4 pv)
{
	float4 v;

/*	v.x = le[0]*pv.x + le[1]*pv.y + le[2]*pv.z;
	v.y = le[3]*pv.x + le[4]*pv.y + le[5]*pv.z;
	v.z = le[6]*pv.x + le[7]*pv.y + le[8]*pv.z;
*/
	v.x = le[0]*pv.x + le[3]*pv.y + le[6]*pv.z;
	v.y = le[1]*pv.x + le[4]*pv.y + le[7]*pv.z;
	v.z = le[2]*pv.x + le[5]*pv.y + le[8]*pv.z;
	v.w = pv.w;

	return v;
}

float hue_to_channel(float oh)
{
	float t;

	// equivalent to rangewrap(oh, -1.f, 2.f)
	oh -= 3.f*floor((oh+1.f) * (1.f/3.f));

	t = fabs(clamp(oh, -1.f, 1.f));

	if (t <= 0.5f)
		return 1.f;
	else
		return Lab_L_to_linear(2.f * (1.f - t));
}

float3 hsl_to_rgb_cw(float3 w, float3 hsl)
{
	float3 rgb, rgbw;
	float Y;

	// Hue
	rgb.x = hue_to_channel(hsl.x);
	rgb.y = hue_to_channel(hsl.x-1.f);
	rgb.z = hue_to_channel(hsl.x-2.f);

	// Luminosity
	rgbw = rgb * w;
	Y = rgbw.x + rgbw.y + rgbw.z;
	Y = hsl.z / Y;
	rgb *= Y;

	// Saturation
	rgb = mix(hsl.z, rgb, hsl.y);

	return rgb;
}
