double fps_estimate_simple(double ifps, double frame_s, double scale)
{
	double t;
       
	t = frame_s * scale;		// smoothing depends on the latest frame duration and the scale
	t = MINN(t, 1.);

	ifps = frame_s*t + ifps*(1.-t);

	return ifps;
}

double fps_estimate_2speeds(double frame_s, int reset)
{
	static double ifpsA = 0., ifpsB = 0., t, td;
	double d;
	static int transition = 0;

	if (reset)
		ifpsA = ifpsB = frame_s;

	ifpsA = fps_estimate_simple(ifpsA, frame_s, 0.4);
	ifpsB = fps_estimate_simple(ifpsB, frame_s, 4.);

	d = fabs(ifpsA / ifpsB);
	if (d < 1.)
		d = 1. / d;

	if (d > 1.2)
	{
		transition = 1;
		t = 0.;
	}

	if (transition)
	{
		td = rangelimit(frame_s / 0.2, 0., 1.);				// does the transition in 0.2 s (actually takes longer for large changes)
		ifpsA = ifpsA + td * (ifpsB - ifpsA) / (1.-t);
		t += td;

		if (t >= 0.999)
			transition = 0;
	}

	return ifpsA;
}
