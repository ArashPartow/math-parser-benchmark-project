void add_body_force_xy(xy_t p0, xy_t p1, double mass, xy_t *acc)	// adds the force from p1's mass to p0's acceleration
{
	double dbb2, dbb;
	double fmag;

	dbb2 = hypot_xy2(p0, p1);
	dbb = sqrt(dbb2);
	fmag = mass / dbb2;
	*acc = add_xy( *acc, div_xy( mul_xy(set_xy(fmag), sub_xy(p1, p0)) , set_xy(dbb)) );
}

void add_body_force_xyz(xyz_t p0, xyz_t p1, double mass, xyz_t *acc)	// adds the force from p1's mass to p0's acceleration
{
	double dbb2, dbb;
	double fmag;

	dbb2 = hypot_xyz2(p0, p1);
	dbb = sqrt(dbb2);
	fmag = mass / dbb2;
	*acc = add_xyz( *acc, div_xyz( mul_xyz(set_xyz(fmag), sub_xyz(p1, p0)) , set_xyz(dbb)) );
}

void physical_integration_xy(xy_t *pos, xy_t *vel, xy_t acc, double dt)
{
	enum { meth_euler, meth_rk2, meth_rk4 };
	const int method = meth_euler;
	double xo, yo, ax0, ax1, ax2, ay0, ay1, ay2, hvx, hvy;
	xy_t po, a0, a1, a2, hv;

	// f(t) = vx, vy at t

	if (method==meth_euler)
	{
		// Euler method: pn+1 = pn + dt * f(tn+1)
		*vel = mad_xy(set_xy(dt), acc, *vel);	// f(xn+1)
		*pos = mad_xy(set_xy(dt), *vel, *pos);	// xn+1 = xn + dt * (fxn+1)
	}

	if (method==meth_rk2)
	{
		po = *pos;
		hv = mad_xy(acc, set_xy(0.5*dt), *vel);
		*pos = mad_xy(*vel, set_xy(0.5*dt), *pos);
		*vel = mad_xy(acc, set_xy(dt), *vel);
		*pos = mad_xy(hv, set_xy(dt), *pos);
	}

	if (method==meth_rk4)
	{
		// the following doesn't really make sense, clearly using the wrong variables
/*		xo = pos->x;							yo = pos->y;
		ax0 = acc.x;							ay0 = acc.y;
		pos->x = xo + vel->x * 0.5*dt + ax0 * 0.125*dt*dt;		pos->y = yo + vel->y * 0.5*dt + ay0 * 0.125*dt*dt;
		ax1 = acc.x;							ay1 = acc.y;
		pos->x = xo + vel->x * dt + ax1 * 0.5*dt*dt;			pos->y = yo + vel->y * dt + ay1 * 0.5*dt*dt;
		ax2 = acc.x;							ay2 = acc.y;
		pos->x = xo + vel->x * dt + (ax0+ax1*2.)*(1./6.) * dt*dt;	pos->y = yo + vel->y * dt + (ay0+ay1*2.)*(1./6.) * dt*dt;
		vel->x = vel->x + (ax0+ax1*4.+ax2)*(1./6.) * dt;		vel->y = vel->y + (ay0+ay1*4.+ay2)*(1./6.) * dt;*/
	}
}

void physical_integration_xyz(xyz_t *pos, xyz_t *vel, xyz_t acc, double dt)
{
	enum { meth_euler, meth_rk2, meth_rk4 };
	const int method = meth_euler;
	double xo, yo, ax0, ax1, ax2, ay0, ay1, ay2, hvx, hvy;
	xyz_t po, a0, a1, a2, hv;

	// f(t) = vx, vy at t

	if (method==meth_euler)
	{
		// Euler method: pn+1 = pn + dt * f(tn+1)
		*vel = mad_xyz(set_xyz(dt), acc, *vel);	// f(xn+1)
		*pos = mad_xyz(set_xyz(dt), *vel, *pos);	// xn+1 = xn + dt * (fxn+1)
	}

	if (method==meth_rk2)
	{
		po = *pos;
		hv = mad_xyz(acc, set_xyz(0.5*dt), *vel);
		*pos = mad_xyz(*vel, set_xyz(0.5*dt), *pos);
		*vel = mad_xyz(acc, set_xyz(dt), *vel);
		*pos = mad_xyz(hv, set_xyz(dt), *pos);
	}
}
