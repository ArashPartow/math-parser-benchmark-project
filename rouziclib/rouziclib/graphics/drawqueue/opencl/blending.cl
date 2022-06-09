float4 blend_pixel(float4 bg, float4 fg, int blendmode)
{
	float4 pv;

	switch (blendmode)
	{
		case DQB_ADD:
			pv = bg + fg;
			break;

		case DQB_SUB:
			pv = bg - fg;
			break;

		case DQB_MUL:
			pv = bg * fg;
			break;

		case DQB_DIV:
			pv = bg / fg;
			break;

		case DQB_BLEND:
			pv = fg * fg.w + bg * (1.f - fg.w);
			break;

		case DQB_SOLID:
			pv = fg;
			break;
	}

	return pv;
}
