#ifndef RL_EXCL_FFTPACK

void radb2(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1)
{
	//* System generated locals */
	int32_t cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ti2, tr2;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_offset = 1 + cc_dim1 * 3;
	cc -= cc_offset;
	--wa1;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[((k << 1) + 1) * cc_dim1 + 1] + 
		cc[ido + ((k << 1) + 2) * cc_dim1];
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cc[((k << 1) + 1) * cc_dim1 
		+ 1] - cc[ido + ((k << 1) + 2) * cc_dim1];
//* L101: */
	}
	if ((i__1 = ido - 2) < 0) {
	goto L107;
	} else if (i__1 == 0) {
	goto L105;
	} else {
	goto L102;
	}
L102:
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + ((k << 1) + 
			1) * cc_dim1] + cc[ic - 1 + ((k << 1) + 2) * cc_dim1];
		tr2 = cc[i__ - 1 + ((k << 1) + 1) * cc_dim1] - cc[ic - 1 + ((k << 
			1) + 2) * cc_dim1];
		ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + ((k << 1) + 1) * 
			cc_dim1] - cc[ic + ((k << 1) + 2) * cc_dim1];
		ti2 = cc[i__ + ((k << 1) + 1) * cc_dim1] + cc[ic + ((k << 1) + 2) 
			* cc_dim1];
		ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * tr2 
			- wa1[i__ - 1] * ti2;
		ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * ti2 + 
			wa1[i__ - 1] * tr2;
//* L103: */
	}
//* L104: */
	}
	if (ido % 2 == 1) {
	return;
	}
L105:
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ch[ido + (k + ch_dim2) * ch_dim1] = cc[ido + ((k << 1) + 1) * 
		cc_dim1] + cc[ido + ((k << 1) + 1) * cc_dim1];
	ch[ido + (k + (ch_dim2 << 1)) * ch_dim1] = -(cc[((k << 1) + 2) * 
		cc_dim1 + 1] + cc[((k << 1) + 2) * cc_dim1 + 1]);
//* L106: */
	}
L107:
	return;
} //* radb2_ */

void radb3(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2)
{
	//* Initialized data */

	static double taur = (double) -0.5;
	static double taui = 
		(double) 0.8660254037844386467637231707529361834710262690519031402790348975;

	//* System generated locals */
	int32_t cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, ci3, di2, di3, cr2, cr3, dr2, dr3, ti2, tr2;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_offset = 1 + (cc_dim1 << 2);
	cc -= cc_offset;
	--wa1;
	--wa2;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	tr2 = cc[ido + (k * 3 + 2) * cc_dim1] + cc[ido + (k * 3 + 2) * 
		cc_dim1];
	cr2 = cc[(k * 3 + 1) * cc_dim1 + 1] + taur * tr2;
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[(k * 3 + 1) * cc_dim1 + 1] + tr2;
	ci3 = taui * (cc[(k * 3 + 3) * cc_dim1 + 1] + cc[(k * 3 + 3) * 
		cc_dim1 + 1]);
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cr2 - ci3;
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cr2 + ci3;
//* L101: */
	}
	if (ido == 1) {
	return;
	}
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		tr2 = cc[i__ - 1 + (k * 3 + 3) * cc_dim1] + cc[ic - 1 + (k * 3 + 
			2) * cc_dim1];
		cr2 = cc[i__ - 1 + (k * 3 + 1) * cc_dim1] + taur * tr2;
		ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + (k * 3 + 1) *
			 cc_dim1] + tr2;
		ti2 = cc[i__ + (k * 3 + 3) * cc_dim1] - cc[ic + (k * 3 + 2) * 
			cc_dim1];
		ci2 = cc[i__ + (k * 3 + 1) * cc_dim1] + taur * ti2;
		ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * 3 + 1) * 
			cc_dim1] + ti2;
		cr3 = taui * (cc[i__ - 1 + (k * 3 + 3) * cc_dim1] - cc[ic - 1 + (
			k * 3 + 2) * cc_dim1]);
		ci3 = taui * (cc[i__ + (k * 3 + 3) * cc_dim1] + cc[ic + (k * 3 + 
			2) * cc_dim1]);
		dr2 = cr2 - ci3;
		dr3 = cr2 + ci3;
		di2 = ci2 + cr3;
		di3 = ci2 - cr3;
		ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * dr2 
			- wa1[i__ - 1] * di2;
		ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * di2 + 
			wa1[i__ - 1] * dr2;
		ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * dr3 - 
			wa2[i__ - 1] * di3;
		ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * di3 + wa2[
			i__ - 1] * dr3;
//* L102: */
	}
//* L103: */
	}
	return;
} //* radb3_ */

void radb4(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2, double *wa3)
{
	//* Initialized data */

	static double sqrt2 = 
		(double) 1.41421356237309504880168872420969807856967187536948073176679738;

	//* System generated locals */
	int32_t cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, ci3, ci4, cr2, cr3, cr4, ti1, ti2, ti3, ti4, tr1, tr2, 
		tr3, tr4;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_offset = 1 + cc_dim1 * 5;
	cc -= cc_offset;
	--wa1;
	--wa2;
	--wa3;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	tr1 = cc[((k << 2) + 1) * cc_dim1 + 1] - cc[ido + ((k << 2) + 4) * 
		cc_dim1];
	tr2 = cc[((k << 2) + 1) * cc_dim1 + 1] + cc[ido + ((k << 2) + 4) * 
		cc_dim1];
	tr3 = cc[ido + ((k << 2) + 2) * cc_dim1] + cc[ido + ((k << 2) + 2) *
		 cc_dim1];
	tr4 = cc[((k << 2) + 3) * cc_dim1 + 1] + cc[((k << 2) + 3) * cc_dim1 
		+ 1];
	ch[(k + ch_dim2) * ch_dim1 + 1] = tr2 + tr3;
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = tr1 - tr4;
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = tr2 - tr3;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = tr1 + tr4;
//* L101: */
	}
	if ((i__1 = ido - 2) < 0) {
	goto L107;
	} else if (i__1 == 0) {
	goto L105;
	} else {
	goto L102;
	}
L102:
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		ti1 = cc[i__ + ((k << 2) + 1) * cc_dim1] + cc[ic + ((k << 2) + 4) 
			* cc_dim1];
		ti2 = cc[i__ + ((k << 2) + 1) * cc_dim1] - cc[ic + ((k << 2) + 4) 
			* cc_dim1];
		ti3 = cc[i__ + ((k << 2) + 3) * cc_dim1] - cc[ic + ((k << 2) + 2) 
			* cc_dim1];
		tr4 = cc[i__ + ((k << 2) + 3) * cc_dim1] + cc[ic + ((k << 2) + 2) 
			* cc_dim1];
		tr1 = cc[i__ - 1 + ((k << 2) + 1) * cc_dim1] - cc[ic - 1 + ((k << 
			2) + 4) * cc_dim1];
		tr2 = cc[i__ - 1 + ((k << 2) + 1) * cc_dim1] + cc[ic - 1 + ((k << 
			2) + 4) * cc_dim1];
		ti4 = cc[i__ - 1 + ((k << 2) + 3) * cc_dim1] - cc[ic - 1 + ((k << 
			2) + 2) * cc_dim1];
		tr3 = cc[i__ - 1 + ((k << 2) + 3) * cc_dim1] + cc[ic - 1 + ((k << 
			2) + 2) * cc_dim1];
		ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = tr2 + tr3;
		cr3 = tr2 - tr3;
		ch[i__ + (k + ch_dim2) * ch_dim1] = ti2 + ti3;
		ci3 = ti2 - ti3;
		cr2 = tr1 - tr4;
		cr4 = tr1 + tr4;
		ci2 = ti1 + ti4;
		ci4 = ti1 - ti4;
		ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * cr2 
			- wa1[i__ - 1] * ci2;
		ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * ci2 + 
			wa1[i__ - 1] * cr2;
		ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * cr3 - 
			wa2[i__ - 1] * ci3;
		ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * ci3 + wa2[
			i__ - 1] * cr3;
		ch[i__ - 1 + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 2] * cr4 
			- wa3[i__ - 1] * ci4;
		ch[i__ + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 2] * ci4 + 
			wa3[i__ - 1] * cr4;
//* L103: */
	}
//* L104: */
	}
	if (ido % 2 == 1) {
	return;
	}
L105:
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ti1 = cc[((k << 2) + 2) * cc_dim1 + 1] + cc[((k << 2) + 4) * cc_dim1 
		+ 1];
	ti2 = cc[((k << 2) + 4) * cc_dim1 + 1] - cc[((k << 2) + 2) * cc_dim1 
		+ 1];
	tr1 = cc[ido + ((k << 2) + 1) * cc_dim1] - cc[ido + ((k << 2) + 3) *
		 cc_dim1];
	tr2 = cc[ido + ((k << 2) + 1) * cc_dim1] + cc[ido + ((k << 2) + 3) *
		 cc_dim1];
	ch[ido + (k + ch_dim2) * ch_dim1] = tr2 + tr2;
	ch[ido + (k + (ch_dim2 << 1)) * ch_dim1] = sqrt2 * (tr1 - ti1);
	ch[ido + (k + ch_dim2 * 3) * ch_dim1] = ti2 + ti2;
	ch[ido + (k + (ch_dim2 << 2)) * ch_dim1] = -sqrt2 * (tr1 + ti1);
//* L106: */
	}
L107:
	return;
} //* radb4_ */

void radb5(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2, double *wa3, 
	double *wa4)
{
	//* Initialized data */

	static double tr11 = 
		(double) 0.3090169943749474241022934171828195886015458990288143106772431137;
	static double ti11 = 
		(double) 0.9510565162951535721164393337938214340569863412575022244730564442;
	static double tr12 = 
		(double) -0.8090169943749474241022934171828190588601545899028814310677431135;
	static double ti12 = 
		(double) 0.5877852522924731291687059546390727685976524376431459107227248076;

	//* System generated locals */
	int32_t cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, ci3, ci4, ci5, di3, di4, di5, di2, cr2, cr3, cr5, cr4, 
		ti2, ti3, ti4, ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_offset = 1 + cc_dim1 * 6;
	cc -= cc_offset;
	--wa1;
	--wa2;
	--wa3;
	--wa4;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k * 5 + 3) * cc_dim1 + 1] + cc[(k * 5 + 3) * cc_dim1 + 1];
	ti4 = cc[(k * 5 + 5) * cc_dim1 + 1] + cc[(k * 5 + 5) * cc_dim1 + 1];
	tr2 = cc[ido + (k * 5 + 2) * cc_dim1] + cc[ido + (k * 5 + 2) * 
		cc_dim1];
	tr3 = cc[ido + (k * 5 + 4) * cc_dim1] + cc[ido + (k * 5 + 4) * 
		cc_dim1];
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[(k * 5 + 1) * cc_dim1 + 1] + tr2 
		+ tr3;
	cr2 = cc[(k * 5 + 1) * cc_dim1 + 1] + tr11 * tr2 + tr12 * tr3;
	cr3 = cc[(k * 5 + 1) * cc_dim1 + 1] + tr12 * tr2 + tr11 * tr3;
	ci5 = ti11 * ti5 + ti12 * ti4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cr2 - ci5;
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cr3 - ci4;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cr3 + ci4;
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = cr2 + ci5;
//* L101: */
	}
	if (ido == 1) {
	return;
	}
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		ti5 = cc[i__ + (k * 5 + 3) * cc_dim1] + cc[ic + (k * 5 + 2) * 
			cc_dim1];
		ti2 = cc[i__ + (k * 5 + 3) * cc_dim1] - cc[ic + (k * 5 + 2) * 
			cc_dim1];
		ti4 = cc[i__ + (k * 5 + 5) * cc_dim1] + cc[ic + (k * 5 + 4) * 
			cc_dim1];
		ti3 = cc[i__ + (k * 5 + 5) * cc_dim1] - cc[ic + (k * 5 + 4) * 
			cc_dim1];
		tr5 = cc[i__ - 1 + (k * 5 + 3) * cc_dim1] - cc[ic - 1 + (k * 5 + 
			2) * cc_dim1];
		tr2 = cc[i__ - 1 + (k * 5 + 3) * cc_dim1] + cc[ic - 1 + (k * 5 + 
			2) * cc_dim1];
		tr4 = cc[i__ - 1 + (k * 5 + 5) * cc_dim1] - cc[ic - 1 + (k * 5 + 
			4) * cc_dim1];
		tr3 = cc[i__ - 1 + (k * 5 + 5) * cc_dim1] + cc[ic - 1 + (k * 5 + 
			4) * cc_dim1];
		ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + (k * 5 + 1) *
			 cc_dim1] + tr2 + tr3;
		ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * 5 + 1) * 
			cc_dim1] + ti2 + ti3;
		cr2 = cc[i__ - 1 + (k * 5 + 1) * cc_dim1] + tr11 * tr2 + tr12 * 
			tr3;
		ci2 = cc[i__ + (k * 5 + 1) * cc_dim1] + tr11 * ti2 + tr12 * ti3;
		cr3 = cc[i__ - 1 + (k * 5 + 1) * cc_dim1] + tr12 * tr2 + tr11 * 
			tr3;
		ci3 = cc[i__ + (k * 5 + 1) * cc_dim1] + tr12 * ti2 + tr11 * ti3;
		cr5 = ti11 * tr5 + ti12 * tr4;
		ci5 = ti11 * ti5 + ti12 * ti4;
		cr4 = ti12 * tr5 - ti11 * tr4;
		ci4 = ti12 * ti5 - ti11 * ti4;
		dr3 = cr3 - ci4;
		dr4 = cr3 + ci4;
		di3 = ci3 + cr4;
		di4 = ci3 - cr4;
		dr5 = cr2 + ci5;
		dr2 = cr2 - ci5;
		di5 = ci2 - cr5;
		di2 = ci2 + cr5;
		ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * dr2 
			- wa1[i__ - 1] * di2;
		ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 2] * di2 + 
			wa1[i__ - 1] * dr2;
		ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * dr3 - 
			wa2[i__ - 1] * di3;
		ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 2] * di3 + wa2[
			i__ - 1] * dr3;
		ch[i__ - 1 + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 2] * dr4 
			- wa3[i__ - 1] * di4;
		ch[i__ + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 2] * di4 + 
			wa3[i__ - 1] * dr4;
		ch[i__ - 1 + (k + ch_dim2 * 5) * ch_dim1] = wa4[i__ - 2] * dr5 - 
			wa4[i__ - 1] * di5;
		ch[i__ + (k + ch_dim2 * 5) * ch_dim1] = wa4[i__ - 2] * di5 + wa4[
			i__ - 1] * dr5;
//* L102: */
	}
//* L103: */
	}
	return;
} //* radb5_ */

void radbg(int32_t ido, int32_t *ip, int32_t l1, int32_t *
	idl1, double *cc, double *c1, double *c2, double *ch, 
	double *ch2, double *wa)
{
	//* Initialized data */

	static double tpi = 
		(double) 6.283185307179586476925286766559005768394338798750116419498891846;

	//* System generated locals */
	int32_t ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_offset, c1_dim1,
		 c1_dim2, c1_offset, c2_dim1, c2_offset, ch2_dim1, ch2_offset, 
		i__1, i__2, i__3;

	//* Local variables */
	int32_t i__, j, k, l, j2, ic, jc, lc, ik, is;
	double dc2, ai1, ai2, ar1, ar2, ds2;
	int32_t nbd;
	double dcp, arg, dsp, ar1h, ar2h;
	int32_t idp2, ipp2, idij, ipph;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	c1_dim1 = ido;
	c1_dim2 = l1;
	c1_offset = 1 + c1_dim1 * (1 + c1_dim2);
	c1 -= c1_offset;
	cc_dim1 = ido;
	cc_dim2 = *ip;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	ch2_dim1 = *idl1;
	ch2_offset = 1 + ch2_dim1;
	ch2 -= ch2_offset;
	c2_dim1 = *idl1;
	c2_offset = 1 + c2_dim1;
	c2 -= c2_offset;
	--wa;

	//* Function Body */
	arg = tpi / (double) (*ip);
	dcp = cos(arg);
	dsp = sin(arg);
	idp2 = ido + 2;
	nbd = (ido - 1) / 2;
	ipp2 = *ip + 2;
	ipph = (*ip + 1) / 2;
	if (ido < l1) {
	goto L103;
	}
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
		ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * cc_dim2 + 1) * 
			cc_dim1];
//* L101: */
	}
//* L102: */
	}
	goto L106;
L103:
	i__1 = ido;
	for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * cc_dim2 + 1) * 
			cc_dim1];
//* L104: */
	}
//* L105: */
	}
L106:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		ch[(k + j * ch_dim2) * ch_dim1 + 1] = cc[ido + (j2 - 2 + k * 
			cc_dim2) * cc_dim1] + cc[ido + (j2 - 2 + k * cc_dim2) * 
			cc_dim1];
		ch[(k + jc * ch_dim2) * ch_dim1 + 1] = cc[(j2 - 1 + k * cc_dim2) *
			 cc_dim1 + 1] + cc[(j2 - 1 + k * cc_dim2) * cc_dim1 + 1];
//* L107: */
	}
//* L108: */
	}
	if (ido == 1) {
	goto L116;
	}
	if (nbd < l1) {
	goto L112;
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		ic = idp2 - i__;
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = cc[i__ - 1 + ((j 
			<< 1) - 1 + k * cc_dim2) * cc_dim1] + cc[ic - 1 + ((j 
			<< 1) - 2 + k * cc_dim2) * cc_dim1];
		ch[i__ - 1 + (k + jc * ch_dim2) * ch_dim1] = cc[i__ - 1 + ((j 
			<< 1) - 1 + k * cc_dim2) * cc_dim1] - cc[ic - 1 + ((j 
			<< 1) - 2 + k * cc_dim2) * cc_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = cc[i__ + ((j << 1) - 
			1 + k * cc_dim2) * cc_dim1] - cc[ic + ((j << 1) - 2 + 
			k * cc_dim2) * cc_dim1];
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = cc[i__ + ((j << 1) - 
			1 + k * cc_dim2) * cc_dim1] + cc[ic + ((j << 1) - 2 + 
			k * cc_dim2) * cc_dim1];
//* L109: */
		}
//* L110: */
	}
//* L111: */
	}
	goto L116;
L112:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = cc[i__ - 1 + ((j 
			<< 1) - 1 + k * cc_dim2) * cc_dim1] + cc[ic - 1 + ((j 
			<< 1) - 2 + k * cc_dim2) * cc_dim1];
		ch[i__ - 1 + (k + jc * ch_dim2) * ch_dim1] = cc[i__ - 1 + ((j 
			<< 1) - 1 + k * cc_dim2) * cc_dim1] - cc[ic - 1 + ((j 
			<< 1) - 2 + k * cc_dim2) * cc_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = cc[i__ + ((j << 1) - 
			1 + k * cc_dim2) * cc_dim1] - cc[ic + ((j << 1) - 2 + 
			k * cc_dim2) * cc_dim1];
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = cc[i__ + ((j << 1) - 
			1 + k * cc_dim2) * cc_dim1] + cc[ic + ((j << 1) - 2 + 
			k * cc_dim2) * cc_dim1];
//* L113: */
		}
//* L114: */
	}
//* L115: */
	}
L116:
	ar1 = (double) 1.0;
	ai1 = (double) 0.0;
	i__1 = ipph;
	for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
		c2[ik + l * c2_dim1] = ch2[ik + ch2_dim1] + ar1 * ch2[ik + (
			ch2_dim1 << 1)];
		c2[ik + lc * c2_dim1] = ai1 * ch2[ik + *ip * ch2_dim1];
//* L117: */
	}
	dc2 = ar1;
	ds2 = ai1;
	ar2 = ar1;
	ai2 = ai1;
	i__2 = ipph;
	for (j = 3; j <= i__2; ++j) {
		jc = ipp2 - j;
		ar2h = dc2 * ar2 - ds2 * ai2;
		ai2 = dc2 * ai2 + ds2 * ar2;
		ar2 = ar2h;
		i__3 = *idl1;
		for (ik = 1; ik <= i__3; ++ik) {
		c2[ik + l * c2_dim1] += ar2 * ch2[ik + j * ch2_dim1];
		c2[ik + lc * c2_dim1] += ai2 * ch2[ik + jc * ch2_dim1];
//* L118: */
		}
//* L119: */
	}
//* L120: */
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
		ch2[ik + ch2_dim1] += ch2[ik + j * ch2_dim1];
//* L121: */
	}
//* L122: */
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		ch[(k + j * ch_dim2) * ch_dim1 + 1] = c1[(k + j * c1_dim2) * 
			c1_dim1 + 1] - c1[(k + jc * c1_dim2) * c1_dim1 + 1];
		ch[(k + jc * ch_dim2) * ch_dim1 + 1] = c1[(k + j * c1_dim2) * 
			c1_dim1 + 1] + c1[(k + jc * c1_dim2) * c1_dim1 + 1];
//* L123: */
	}
//* L124: */
	}
	if (ido == 1) {
	goto L132;
	}
	if (nbd < l1) {
	goto L128;
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = c1[i__ - 1 + (k + 
			j * c1_dim2) * c1_dim1] - c1[i__ + (k + jc * c1_dim2) 
			* c1_dim1];
		ch[i__ - 1 + (k + jc * ch_dim2) * ch_dim1] = c1[i__ - 1 + (k 
			+ j * c1_dim2) * c1_dim1] + c1[i__ + (k + jc * 
			c1_dim2) * c1_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = c1[i__ + (k + j * 
			c1_dim2) * c1_dim1] + c1[i__ - 1 + (k + jc * c1_dim2) 
			* c1_dim1];
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = c1[i__ + (k + j * 
			c1_dim2) * c1_dim1] - c1[i__ - 1 + (k + jc * c1_dim2) 
			* c1_dim1];
//* L125: */
		}
//* L126: */
	}
//* L127: */
	}
	goto L132;
L128:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = c1[i__ - 1 + (k + 
			j * c1_dim2) * c1_dim1] - c1[i__ + (k + jc * c1_dim2) 
			* c1_dim1];
		ch[i__ - 1 + (k + jc * ch_dim2) * ch_dim1] = c1[i__ - 1 + (k 
			+ j * c1_dim2) * c1_dim1] + c1[i__ + (k + jc * 
			c1_dim2) * c1_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = c1[i__ + (k + j * 
			c1_dim2) * c1_dim1] + c1[i__ - 1 + (k + jc * c1_dim2) 
			* c1_dim1];
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = c1[i__ + (k + j * 
			c1_dim2) * c1_dim1] - c1[i__ - 1 + (k + jc * c1_dim2) 
			* c1_dim1];
//* L129: */
		}
//* L130: */
	}
//* L131: */
	}
L132:
	if (ido == 1) {
	return;
	}
	i__1 = *idl1;
	for (ik = 1; ik <= i__1; ++ik) {
	c2[ik + c2_dim1] = ch2[ik + ch2_dim1];
//* L133: */
	}
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		c1[(k + j * c1_dim2) * c1_dim1 + 1] = ch[(k + j * ch_dim2) * 
			ch_dim1 + 1];
//* L134: */
	}
//* L135: */
	}
	if (nbd > l1) {
	goto L139;
	}
	is = -(ido);
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	is += ido;
	idij = is;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		idij += 2;
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[
			i__ - 1 + (k + j * ch_dim2) * ch_dim1] - wa[idij] * 
			ch[i__ + (k + j * ch_dim2) * ch_dim1];
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[i__ 
			+ (k + j * ch_dim2) * ch_dim1] + wa[idij] * ch[i__ - 
			1 + (k + j * ch_dim2) * ch_dim1];
//* L136: */
		}
//* L137: */
	}
//* L138: */
	}
	goto L143;
L139:
	is = -(ido);
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	is += ido;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		idij = is;
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		idij += 2;
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[
			i__ - 1 + (k + j * ch_dim2) * ch_dim1] - wa[idij] * 
			ch[i__ + (k + j * ch_dim2) * ch_dim1];
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[i__ 
			+ (k + j * ch_dim2) * ch_dim1] + wa[idij] * ch[i__ - 
			1 + (k + j * ch_dim2) * ch_dim1];
//* L140: */
		}
//* L141: */
	}
//* L142: */
	}
L143:
	return;
} //* radbg_ */

void radf2(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1)
{
	//* System generated locals */
	int32_t ch_dim1, ch_offset, cc_dim1, cc_dim2, cc_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ti2, tr2;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_offset = 1 + ch_dim1 * 3;
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_dim2 = l1;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	--wa1;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ch[((k << 1) + 1) * ch_dim1 + 1] = cc[(k + cc_dim2) * cc_dim1 + 1] + 
		cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1];
	ch[ido + ((k << 1) + 2) * ch_dim1] = cc[(k + cc_dim2) * cc_dim1 + 1] 
		- cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1];
//* L101: */
	}
	if ((i__1 = ido - 2) < 0) {
	goto L107;
	} else if (i__1 == 0) {
	goto L105;
	} else {
	goto L102;
	}
L102:
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		tr2 = wa1[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * cc_dim1] 
			+ wa1[i__ - 1] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1];
		ti2 = wa1[i__ - 2] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1] - 
			wa1[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * 
			cc_dim1];
		ch[i__ + ((k << 1) + 1) * ch_dim1] = cc[i__ + (k + cc_dim2) * 
			cc_dim1] + ti2;
		ch[ic + ((k << 1) + 2) * ch_dim1] = ti2 - cc[i__ + (k + cc_dim2) *
			 cc_dim1];
		ch[i__ - 1 + ((k << 1) + 1) * ch_dim1] = cc[i__ - 1 + (k + 
			cc_dim2) * cc_dim1] + tr2;
		ch[ic - 1 + ((k << 1) + 2) * ch_dim1] = cc[i__ - 1 + (k + cc_dim2)
			 * cc_dim1] - tr2;
//* L103: */
	}
//* L104: */
	}
	if (ido % 2 == 1) {
	return;
	}
L105:
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ch[((k << 1) + 2) * ch_dim1 + 1] = -cc[ido + (k + (cc_dim2 << 1)) * 
		cc_dim1];
	ch[ido + ((k << 1) + 1) * ch_dim1] = cc[ido + (k + cc_dim2) * 
		cc_dim1];
//* L106: */
	}
L107:
	return;
} //* radf2_ */

void radf3(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2)
{
	//* Initialized data */

	static double taur = (double) -0.5;
	static double taui = 
		(double) 0.8660254037844386467637231707529361834710262690519031402790348975;

	//* System generated locals */
	int32_t ch_dim1, ch_offset, cc_dim1, cc_dim2, cc_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, di2, di3, cr2, dr2, dr3, ti2, ti3, tr2, tr3;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_offset = 1 + (ch_dim1 << 2);
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_dim2 = l1;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	--wa1;
	--wa2;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	cr2 = cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1] + cc[(k + cc_dim2 * 3) * 
		cc_dim1 + 1];
	ch[(k * 3 + 1) * ch_dim1 + 1] = cc[(k + cc_dim2) * cc_dim1 + 1] + cr2;
	ch[(k * 3 + 3) * ch_dim1 + 1] = taui * (cc[(k + cc_dim2 * 3) * 
		cc_dim1 + 1] - cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1]);
	ch[ido + (k * 3 + 2) * ch_dim1] = cc[(k + cc_dim2) * cc_dim1 + 1] + 
		taur * cr2;
//* L101: */
	}
	if (ido == 1) {
	return;
	}
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		dr2 = wa1[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * cc_dim1] 
			+ wa1[i__ - 1] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1];
		di2 = wa1[i__ - 2] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1] - 
			wa1[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * 
			cc_dim1];
		dr3 = wa2[i__ - 2] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1] + 
			wa2[i__ - 1] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1];
		di3 = wa2[i__ - 2] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1] - wa2[
			i__ - 1] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1];
		cr2 = dr2 + dr3;
		ci2 = di2 + di3;
		ch[i__ - 1 + (k * 3 + 1) * ch_dim1] = cc[i__ - 1 + (k + cc_dim2) *
			 cc_dim1] + cr2;
		ch[i__ + (k * 3 + 1) * ch_dim1] = cc[i__ + (k + cc_dim2) * 
			cc_dim1] + ci2;
		tr2 = cc[i__ - 1 + (k + cc_dim2) * cc_dim1] + taur * cr2;
		ti2 = cc[i__ + (k + cc_dim2) * cc_dim1] + taur * ci2;
		tr3 = taui * (di2 - di3);
		ti3 = taui * (dr3 - dr2);
		ch[i__ - 1 + (k * 3 + 3) * ch_dim1] = tr2 + tr3;
		ch[ic - 1 + (k * 3 + 2) * ch_dim1] = tr2 - tr3;
		ch[i__ + (k * 3 + 3) * ch_dim1] = ti2 + ti3;
		ch[ic + (k * 3 + 2) * ch_dim1] = ti3 - ti2;
//* L102: */
	}
//* L103: */
	}
	return;
} //* radf3_ */

void radf4(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2, double *wa3)
{
	//* Initialized data */

	static double hsqt2 = 
		(double) 0.70710678118654752440084436210484903928483593768474036588339869;

	//* System generated locals */
	int32_t cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, ci3, ci4, cr2, cr3, cr4, ti1, ti2, ti3, ti4, tr1, tr2, 
		tr3, tr4;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_offset = 1 + ch_dim1 * 5;
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_dim2 = l1;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	--wa1;
	--wa2;
	--wa3;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	tr1 = cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1] + cc[(k + (cc_dim2 << 2))
		 * cc_dim1 + 1];
	tr2 = cc[(k + cc_dim2) * cc_dim1 + 1] + cc[(k + cc_dim2 * 3) * 
		cc_dim1 + 1];
	ch[((k << 2) + 1) * ch_dim1 + 1] = tr1 + tr2;
	ch[ido + ((k << 2) + 4) * ch_dim1] = tr2 - tr1;
	ch[ido + ((k << 2) + 2) * ch_dim1] = cc[(k + cc_dim2) * cc_dim1 + 1] 
		- cc[(k + cc_dim2 * 3) * cc_dim1 + 1];
	ch[((k << 2) + 3) * ch_dim1 + 1] = cc[(k + (cc_dim2 << 2)) * cc_dim1 
		+ 1] - cc[(k + (cc_dim2 << 1)) * cc_dim1 + 1];
//* L101: */
	}
	if ((i__1 = ido - 2) < 0) {
	goto L107;
	} else if (i__1 == 0) {
	goto L105;
	} else {
	goto L102;
	}
L102:
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		cr2 = wa1[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * cc_dim1] 
			+ wa1[i__ - 1] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1];
		ci2 = wa1[i__ - 2] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1] - 
			wa1[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * 
			cc_dim1];
		cr3 = wa2[i__ - 2] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1] + 
			wa2[i__ - 1] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1];
		ci3 = wa2[i__ - 2] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1] - wa2[
			i__ - 1] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1];
		cr4 = wa3[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 2)) * cc_dim1] 
			+ wa3[i__ - 1] * cc[i__ + (k + (cc_dim2 << 2)) * cc_dim1];
		ci4 = wa3[i__ - 2] * cc[i__ + (k + (cc_dim2 << 2)) * cc_dim1] - 
			wa3[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 2)) * 
			cc_dim1];
		tr1 = cr2 + cr4;
		tr4 = cr4 - cr2;
		ti1 = ci2 + ci4;
		ti4 = ci2 - ci4;
		ti2 = cc[i__ + (k + cc_dim2) * cc_dim1] + ci3;
		ti3 = cc[i__ + (k + cc_dim2) * cc_dim1] - ci3;
		tr2 = cc[i__ - 1 + (k + cc_dim2) * cc_dim1] + cr3;
		tr3 = cc[i__ - 1 + (k + cc_dim2) * cc_dim1] - cr3;
		ch[i__ - 1 + ((k << 2) + 1) * ch_dim1] = tr1 + tr2;
		ch[ic - 1 + ((k << 2) + 4) * ch_dim1] = tr2 - tr1;
		ch[i__ + ((k << 2) + 1) * ch_dim1] = ti1 + ti2;
		ch[ic + ((k << 2) + 4) * ch_dim1] = ti1 - ti2;
		ch[i__ - 1 + ((k << 2) + 3) * ch_dim1] = ti4 + tr3;
		ch[ic - 1 + ((k << 2) + 2) * ch_dim1] = tr3 - ti4;
		ch[i__ + ((k << 2) + 3) * ch_dim1] = tr4 + ti3;
		ch[ic + ((k << 2) + 2) * ch_dim1] = tr4 - ti3;
//* L103: */
	}
//* L104: */
	}
	if (ido % 2 == 1) {
	return;
	}
L105:
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	ti1 = -hsqt2 * (cc[ido + (k + (cc_dim2 << 1)) * cc_dim1] + cc[ido + 
		(k + (cc_dim2 << 2)) * cc_dim1]);
	tr1 = hsqt2 * (cc[ido + (k + (cc_dim2 << 1)) * cc_dim1] - cc[ido + (
		k + (cc_dim2 << 2)) * cc_dim1]);
	ch[ido + ((k << 2) + 1) * ch_dim1] = tr1 + cc[ido + (k + cc_dim2) * 
		cc_dim1];
	ch[ido + ((k << 2) + 3) * ch_dim1] = cc[ido + (k + cc_dim2) * 
		cc_dim1] - tr1;
	ch[((k << 2) + 2) * ch_dim1 + 1] = ti1 - cc[ido + (k + cc_dim2 * 3) *
		 cc_dim1];
	ch[((k << 2) + 4) * ch_dim1 + 1] = ti1 + cc[ido + (k + cc_dim2 * 3) *
		 cc_dim1];
//* L106: */
	}
L107:
	return;
} //* radf4_ */

void radf5(int32_t ido, int32_t l1, double *cc, 
	double *ch, double *wa1, double *wa2, double *wa3, 
	double *wa4)
{
	//* Initialized data */

	static double tr11 = 
		(double) 0.3090169943749474241022934171828195886015458990288143106772431137;
	static double ti11 = 
		(double) 0.9510565162951535721164393337938214340569863412575022244730564442;
	static double tr12 = 
		(double) -0.8090169943749474241022934171828190588601545899028814310677431135;
	static double ti12 = 
		(double) 0.5877852522924731291687059546390727685976524376431459107227248076;

	//* System generated locals */
	int32_t cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_offset, i__1, i__2;

	//* Local variables */
	int32_t i__, k, ic;
	double ci2, di2, ci4, ci5, di3, di4, di5, ci3, cr2, cr3, dr2, dr3, 
		dr4, dr5, cr5, cr4, ti2, ti3, ti5, ti4, tr2, tr3, tr4, tr5;
	int32_t idp2;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_offset = 1 + ch_dim1 * 6;
	ch -= ch_offset;
	cc_dim1 = ido;
	cc_dim2 = l1;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	--wa1;
	--wa2;
	--wa3;
	--wa4;

	//* Function Body */
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	cr2 = cc[(k + cc_dim2 * 5) * cc_dim1 + 1] + cc[(k + (cc_dim2 << 1)) * 
		cc_dim1 + 1];
	ci5 = cc[(k + cc_dim2 * 5) * cc_dim1 + 1] - cc[(k + (cc_dim2 << 1)) * 
		cc_dim1 + 1];
	cr3 = cc[(k + (cc_dim2 << 2)) * cc_dim1 + 1] + cc[(k + cc_dim2 * 3) * 
		cc_dim1 + 1];
	ci4 = cc[(k + (cc_dim2 << 2)) * cc_dim1 + 1] - cc[(k + cc_dim2 * 3) * 
		cc_dim1 + 1];
	ch[(k * 5 + 1) * ch_dim1 + 1] = cc[(k + cc_dim2) * cc_dim1 + 1] + cr2 
		+ cr3;
	ch[ido + (k * 5 + 2) * ch_dim1] = cc[(k + cc_dim2) * cc_dim1 + 1] + 
		tr11 * cr2 + tr12 * cr3;
	ch[(k * 5 + 3) * ch_dim1 + 1] = ti11 * ci5 + ti12 * ci4;
	ch[ido + (k * 5 + 4) * ch_dim1] = cc[(k + cc_dim2) * cc_dim1 + 1] + 
		tr12 * cr2 + tr11 * cr3;
	ch[(k * 5 + 5) * ch_dim1 + 1] = ti12 * ci5 - ti11 * ci4;
//* L101: */
	}
	if (ido == 1) {
	return;
	}
	idp2 = ido + 2;
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		dr2 = wa1[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * cc_dim1] 
			+ wa1[i__ - 1] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1];
		di2 = wa1[i__ - 2] * cc[i__ + (k + (cc_dim2 << 1)) * cc_dim1] - 
			wa1[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 1)) * 
			cc_dim1];
		dr3 = wa2[i__ - 2] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1] + 
			wa2[i__ - 1] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1];
		di3 = wa2[i__ - 2] * cc[i__ + (k + cc_dim2 * 3) * cc_dim1] - wa2[
			i__ - 1] * cc[i__ - 1 + (k + cc_dim2 * 3) * cc_dim1];
		dr4 = wa3[i__ - 2] * cc[i__ - 1 + (k + (cc_dim2 << 2)) * cc_dim1] 
			+ wa3[i__ - 1] * cc[i__ + (k + (cc_dim2 << 2)) * cc_dim1];
		di4 = wa3[i__ - 2] * cc[i__ + (k + (cc_dim2 << 2)) * cc_dim1] - 
			wa3[i__ - 1] * cc[i__ - 1 + (k + (cc_dim2 << 2)) * 
			cc_dim1];
		dr5 = wa4[i__ - 2] * cc[i__ - 1 + (k + cc_dim2 * 5) * cc_dim1] + 
			wa4[i__ - 1] * cc[i__ + (k + cc_dim2 * 5) * cc_dim1];
		di5 = wa4[i__ - 2] * cc[i__ + (k + cc_dim2 * 5) * cc_dim1] - wa4[
			i__ - 1] * cc[i__ - 1 + (k + cc_dim2 * 5) * cc_dim1];
		cr2 = dr2 + dr5;
		ci5 = dr5 - dr2;
		cr5 = di2 - di5;
		ci2 = di2 + di5;
		cr3 = dr3 + dr4;
		ci4 = dr4 - dr3;
		cr4 = di3 - di4;
		ci3 = di3 + di4;
		ch[i__ - 1 + (k * 5 + 1) * ch_dim1] = cc[i__ - 1 + (k + cc_dim2) *
			 cc_dim1] + cr2 + cr3;
		ch[i__ + (k * 5 + 1) * ch_dim1] = cc[i__ + (k + cc_dim2) * 
			cc_dim1] + ci2 + ci3;
		tr2 = cc[i__ - 1 + (k + cc_dim2) * cc_dim1] + tr11 * cr2 + tr12 * 
			cr3;
		ti2 = cc[i__ + (k + cc_dim2) * cc_dim1] + tr11 * ci2 + tr12 * ci3;
		tr3 = cc[i__ - 1 + (k + cc_dim2) * cc_dim1] + tr12 * cr2 + tr11 * 
			cr3;
		ti3 = cc[i__ + (k + cc_dim2) * cc_dim1] + tr12 * ci2 + tr11 * ci3;
		tr5 = ti11 * cr5 + ti12 * cr4;
		ti5 = ti11 * ci5 + ti12 * ci4;
		tr4 = ti12 * cr5 - ti11 * cr4;
		ti4 = ti12 * ci5 - ti11 * ci4;
		ch[i__ - 1 + (k * 5 + 3) * ch_dim1] = tr2 + tr5;
		ch[ic - 1 + (k * 5 + 2) * ch_dim1] = tr2 - tr5;
		ch[i__ + (k * 5 + 3) * ch_dim1] = ti2 + ti5;
		ch[ic + (k * 5 + 2) * ch_dim1] = ti5 - ti2;
		ch[i__ - 1 + (k * 5 + 5) * ch_dim1] = tr3 + tr4;
		ch[ic - 1 + (k * 5 + 4) * ch_dim1] = tr3 - tr4;
		ch[i__ + (k * 5 + 5) * ch_dim1] = ti3 + ti4;
		ch[ic + (k * 5 + 4) * ch_dim1] = ti4 - ti3;
//* L102: */
	}
//* L103: */
	}
	return;
} //* radf5_ */

void radfg(int32_t ido, int32_t *ip, int32_t l1, int32_t *
	idl1, double *cc, double *c1, double *c2, double *ch, 
	double *ch2, double *wa)
{
	//* Initialized data */

	static double tpi = 
		(double) 6.283185307179586476925286766559005768394338798750116419498891846;

	//* System generated locals */
	int32_t ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_offset, c1_dim1,
		 c1_dim2, c1_offset, c2_dim1, c2_offset, ch2_dim1, ch2_offset, 
		i__1, i__2, i__3;

	//* Local variables */
	int32_t i__, j, k, l, j2, ic, jc, lc, ik, is;
	double dc2, ai1, ai2, ar1, ar2, ds2;
	int32_t nbd;
	double dcp, arg, dsp, ar1h, ar2h;
	int32_t idp2, ipp2, idij, ipph;

	//* Parameter adjustments */
	ch_dim1 = ido;
	ch_dim2 = l1;
	ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
	ch -= ch_offset;
	c1_dim1 = ido;
	c1_dim2 = l1;
	c1_offset = 1 + c1_dim1 * (1 + c1_dim2);
	c1 -= c1_offset;
	cc_dim1 = ido;
	cc_dim2 = *ip;
	cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
	cc -= cc_offset;
	ch2_dim1 = *idl1;
	ch2_offset = 1 + ch2_dim1;
	ch2 -= ch2_offset;
	c2_dim1 = *idl1;
	c2_offset = 1 + c2_dim1;
	c2 -= c2_offset;
	--wa;

	//* Function Body */
	arg = tpi / (double) (*ip);
	dcp = cos(arg);
	dsp = sin(arg);
	ipph = (*ip + 1) / 2;
	ipp2 = *ip + 2;
	idp2 = ido + 2;
	nbd = (ido - 1) / 2;
	if (ido == 1) {
	goto L119;
	}
	i__1 = *idl1;
	for (ik = 1; ik <= i__1; ++ik) {
	ch2[ik + ch2_dim1] = c2[ik + c2_dim1];
//* L101: */
	}
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		ch[(k + j * ch_dim2) * ch_dim1 + 1] = c1[(k + j * c1_dim2) * 
			c1_dim1 + 1];
//* L102: */
	}
//* L103: */
	}
	if (nbd > l1) {
	goto L107;
	}
	is = -(ido);
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	is += ido;
	idij = is;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		idij += 2;
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = wa[idij - 1] * c1[
			i__ - 1 + (k + j * c1_dim2) * c1_dim1] + wa[idij] * 
			c1[i__ + (k + j * c1_dim2) * c1_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = wa[idij - 1] * c1[i__ 
			+ (k + j * c1_dim2) * c1_dim1] - wa[idij] * c1[i__ - 
			1 + (k + j * c1_dim2) * c1_dim1];
//* L104: */
		}
//* L105: */
	}
//* L106: */
	}
	goto L111;
L107:
	is = -(ido);
	i__1 = *ip;
	for (j = 2; j <= i__1; ++j) {
	is += ido;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		idij = is;
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		idij += 2;
		ch[i__ - 1 + (k + j * ch_dim2) * ch_dim1] = wa[idij - 1] * c1[
			i__ - 1 + (k + j * c1_dim2) * c1_dim1] + wa[idij] * 
			c1[i__ + (k + j * c1_dim2) * c1_dim1];
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = wa[idij - 1] * c1[i__ 
			+ (k + j * c1_dim2) * c1_dim1] - wa[idij] * c1[i__ - 
			1 + (k + j * c1_dim2) * c1_dim1];
//* L108: */
		}
//* L109: */
	}
//* L110: */
	}
L111:
	if (nbd < l1) {
	goto L115;
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = ch[i__ - 1 + (k + 
			j * ch_dim2) * ch_dim1] + ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		c1[i__ - 1 + (k + jc * c1_dim2) * c1_dim1] = ch[i__ + (k + j *
			 ch_dim2) * ch_dim1] - ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = ch[i__ + (k + j * 
			ch_dim2) * ch_dim1] + ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		c1[i__ + (k + jc * c1_dim2) * c1_dim1] = ch[i__ - 1 + (k + jc 
			* ch_dim2) * ch_dim1] - ch[i__ - 1 + (k + j * ch_dim2)
			 * ch_dim1];
//* L112: */
		}
//* L113: */
	}
//* L114: */
	}
	goto L121;
L115:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = ch[i__ - 1 + (k + 
			j * ch_dim2) * ch_dim1] + ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		c1[i__ - 1 + (k + jc * c1_dim2) * c1_dim1] = ch[i__ + (k + j *
			 ch_dim2) * ch_dim1] - ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = ch[i__ + (k + j * 
			ch_dim2) * ch_dim1] + ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		c1[i__ + (k + jc * c1_dim2) * c1_dim1] = ch[i__ - 1 + (k + jc 
			* ch_dim2) * ch_dim1] - ch[i__ - 1 + (k + j * ch_dim2)
			 * ch_dim1];
//* L116: */
		}
//* L117: */
	}
//* L118: */
	}
	goto L121;
L119:
	i__1 = *idl1;
	for (ik = 1; ik <= i__1; ++ik) {
	c2[ik + c2_dim1] = ch2[ik + ch2_dim1];
//* L120: */
	}
L121:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		c1[(k + j * c1_dim2) * c1_dim1 + 1] = ch[(k + j * ch_dim2) * 
			ch_dim1 + 1] + ch[(k + jc * ch_dim2) * ch_dim1 + 1];
		c1[(k + jc * c1_dim2) * c1_dim1 + 1] = ch[(k + jc * ch_dim2) * 
			ch_dim1 + 1] - ch[(k + j * ch_dim2) * ch_dim1 + 1];
//* L122: */
	}
//* L123: */
	}

	ar1 = (double) 1.0;
	ai1 = (double) 0.0;
	i__1 = ipph;
	for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
		ch2[ik + l * ch2_dim1] = c2[ik + c2_dim1] + ar1 * c2[ik + (
			c2_dim1 << 1)];
		ch2[ik + lc * ch2_dim1] = ai1 * c2[ik + *ip * c2_dim1];
//* L124: */
	}
	dc2 = ar1;
	ds2 = ai1;
	ar2 = ar1;
	ai2 = ai1;
	i__2 = ipph;
	for (j = 3; j <= i__2; ++j) {
		jc = ipp2 - j;
		ar2h = dc2 * ar2 - ds2 * ai2;
		ai2 = dc2 * ai2 + ds2 * ar2;
		ar2 = ar2h;
		i__3 = *idl1;
		for (ik = 1; ik <= i__3; ++ik) {
		ch2[ik + l * ch2_dim1] += ar2 * c2[ik + j * c2_dim1];
		ch2[ik + lc * ch2_dim1] += ai2 * c2[ik + jc * c2_dim1];
//* L125: */
		}
//* L126: */
	}
//* L127: */
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
		ch2[ik + ch2_dim1] += c2[ik + j * c2_dim1];
//* L128: */
	}
//* L129: */
	}

	if (ido < l1) {
	goto L132;
	}
	i__1 = l1;
	for (k = 1; k <= i__1; ++k) {
	i__2 = ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
		cc[i__ + (k * cc_dim2 + 1) * cc_dim1] = ch[i__ + (k + ch_dim2) * 
			ch_dim1];
//* L130: */
	}
//* L131: */
	}
	goto L135;
L132:
	i__1 = ido;
	for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		cc[i__ + (k * cc_dim2 + 1) * cc_dim1] = ch[i__ + (k + ch_dim2) * 
			ch_dim1];
//* L133: */
	}
//* L134: */
	}
L135:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		cc[ido + (j2 - 2 + k * cc_dim2) * cc_dim1] = ch[(k + j * ch_dim2)
			 * ch_dim1 + 1];
		cc[(j2 - 1 + k * cc_dim2) * cc_dim1 + 1] = ch[(k + jc * ch_dim2) *
			 ch_dim1 + 1];
//* L136: */
	}
//* L137: */
	}
	if (ido == 1) {
	return;
	}
	if (nbd < l1) {
	goto L141;
	}
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = l1;
	for (k = 1; k <= i__2; ++k) {
		i__3 = ido;
		for (i__ = 3; i__ <= i__3; i__ += 2) {
		ic = idp2 - i__;
		cc[i__ - 1 + (j2 - 1 + k * cc_dim2) * cc_dim1] = ch[i__ - 1 + 
			(k + j * ch_dim2) * ch_dim1] + ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		cc[ic - 1 + (j2 - 2 + k * cc_dim2) * cc_dim1] = ch[i__ - 1 + (
			k + j * ch_dim2) * ch_dim1] - ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		cc[i__ + (j2 - 1 + k * cc_dim2) * cc_dim1] = ch[i__ + (k + j *
			 ch_dim2) * ch_dim1] + ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		cc[ic + (j2 - 2 + k * cc_dim2) * cc_dim1] = ch[i__ + (k + jc *
			 ch_dim2) * ch_dim1] - ch[i__ + (k + j * ch_dim2) * 
			ch_dim1];
//* L138: */
		}
//* L139: */
	}
//* L140: */
	}
	return;
L141:
	i__1 = ipph;
	for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
		ic = idp2 - i__;
		i__3 = l1;
		for (k = 1; k <= i__3; ++k) {
		cc[i__ - 1 + (j2 - 1 + k * cc_dim2) * cc_dim1] = ch[i__ - 1 + 
			(k + j * ch_dim2) * ch_dim1] + ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		cc[ic - 1 + (j2 - 2 + k * cc_dim2) * cc_dim1] = ch[i__ - 1 + (
			k + j * ch_dim2) * ch_dim1] - ch[i__ - 1 + (k + jc * 
			ch_dim2) * ch_dim1];
		cc[i__ + (j2 - 1 + k * cc_dim2) * cc_dim1] = ch[i__ + (k + j *
			 ch_dim2) * ch_dim1] + ch[i__ + (k + jc * ch_dim2) * 
			ch_dim1];
		cc[ic + (j2 - 2 + k * cc_dim2) * cc_dim1] = ch[i__ + (k + jc *
			 ch_dim2) * ch_dim1] - ch[i__ + (k + j * ch_dim2) * 
			ch_dim1];
//* L142: */
		}
//* L143: */
	}
//* L144: */
	}
	return;
} //* radfg_ */

void rfftb1(int32_t n, double *c__, double *ch, 
	double *wa, int32_t *ifac)
{
	//* System generated locals */
	int32_t i__1;

	//* Local variables */
	int32_t i__, k1, l1, l2, na, nf, ip, iw, ix2, ix3, ix4, ido, idl1;

	//* Parameter adjustments */
	--ifac;
	--wa;
	--ch;
	--c__;

	//* Function Body */
	nf = ifac[2];
	na = 0;
	l1 = 1;
	iw = 1;
	i__1 = nf;
	for (k1 = 1; k1 <= i__1; ++k1) {
	ip = ifac[k1 + 2];
	l2 = ip * l1;
	ido = n / l2;
	idl1 = ido * l1;
	if (ip != 4) {
		goto L103;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	if (na != 0) {
		goto L101;
	}
	radb4(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3]);
	goto L102;
L101:
	radb4(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3]);
L102:
	na = 1 - na;
	goto L115;
L103:
	if (ip != 2) {
		goto L106;
	}
	if (na != 0) {
		goto L104;
	}
	radb2(ido, l1, &c__[1], &ch[1], &wa[iw]);
	goto L105;
L104:
	radb2(ido, l1, &ch[1], &c__[1], &wa[iw]);
L105:
	na = 1 - na;
	goto L115;
L106:
	if (ip != 3) {
		goto L109;
	}
	ix2 = iw + ido;
	if (na != 0) {
		goto L107;
	}
	radb3(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2]);
	goto L108;
L107:
	radb3(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2]);
L108:
	na = 1 - na;
	goto L115;
L109:
	if (ip != 5) {
		goto L112;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	ix4 = ix3 + ido;
	if (na != 0) {
		goto L110;
	}
	radb5(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3], &wa[
		ix4]);
	goto L111;
L110:
	radb5(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3], &wa[
		ix4]);
L111:
	na = 1 - na;
	goto L115;
L112:
	if (na != 0) {
		goto L113;
	}
	radbg(ido, &ip, l1, &idl1, &c__[1], &c__[1], &c__[1], &ch[1], &ch[
		1], &wa[iw]);
	goto L114;
L113:
	radbg(ido, &ip, l1, &idl1, &ch[1], &ch[1], &ch[1], &c__[1], &c__[1]
		, &wa[iw]);
L114:
	if (ido == 1) {
		na = 1 - na;
	}
L115:
	l1 = l2;
	iw += (ip - 1) * ido;
//* L116: */
	}
	if (na == 0) {
	return;
	}
	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	c__[i__] = ch[i__];
//* L117: */
	}
	return;
} //* rfftb1_ */

void rfftb(int32_t n, double *r__, double *wsave, 
	int32_t *ifac)
{
	//* Parameter adjustments */
	--ifac;
	--wsave;
	--r__;

	//* Function Body */
	if (n == 1) {
	return;
	}
	rfftb1(n, &r__[1], &wsave[1], &wsave[n + 1], &ifac[1]);
	return;
} //* rfftb_ */

void rfftf1(int32_t n, double *c__, double *ch, 
	double *wa, int32_t *ifac)
{
	//* System generated locals */
	int32_t i__1;

	//* Local variables */
	int32_t i__, k1, l1, l2, na, kh, nf, ip, iw, ix2, ix3, ix4, ido, idl1;

	//* Parameter adjustments */
	--ifac;
	--wa;
	--ch;
	--c__;

	//* Function Body */
	nf = ifac[2];
	na = 1;
	l2 = n;
	iw = n;
	i__1 = nf;
	for (k1 = 1; k1 <= i__1; ++k1)
	{
		kh = nf - k1;
		ip = ifac[kh + 3];
		l1 = l2 / ip;
		ido = n / l2;
		idl1 = ido * l1;
		iw -= (ip - 1) * ido;
		na = 1 - na;
		if (ip != 4)
			goto L102;

		ix2 = iw + ido;
		ix3 = ix2 + ido;
		if (na != 0)
			goto L101;

		radf4(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3]);
		goto L110;
L101:
		radf4(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3]);
		goto L110;
L102:
		if (ip != 2)
			goto L104;

		if (na != 0)
			goto L103;

		radf2(ido, l1, &c__[1], &ch[1], &wa[iw]);
		goto L110;
L103:
		radf2(ido, l1, &ch[1], &c__[1], &wa[iw]);
		goto L110;
L104:
		if (ip != 3)
			goto L106;

		ix2 = iw + ido;
		if (na != 0)
			goto L105;

		radf3(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2]);
		goto L110;
L105:
		radf3(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2]);
		goto L110;
L106:
		if (ip != 5)
			goto L108;

		ix2 = iw + ido;
		ix3 = ix2 + ido;
		ix4 = ix3 + ido;

		if (na != 0)
			goto L107;

		radf5(ido, l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
		goto L110;
L107:
		radf5(ido, l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
		goto L110;
L108:
		if (ido == 1)
			na = 1 - na;

		if (na != 0)
			goto L109;

		radfg(ido, &ip, l1, &idl1, &c__[1], &c__[1], &c__[1], &ch[1], &ch[1], &wa[iw]);
		na = 1;
		goto L110;
L109:
		radfg(ido, &ip, l1, &idl1, &ch[1], &ch[1], &ch[1], &c__[1], &c__[1], &wa[iw]);
		na = 0;
L110:
		l2 = l1;
//* L111: */
	}

	if (na == 1)
		return;

	i__1 = n;
	for (i__ = 1; i__ <= i__1; ++i__)
		c__[i__] = ch[i__];
//* L112: */

	return;
} //* rfftf1_ */

void rfftf(int32_t n, double *r__, double *wsave, 
	int32_t *ifac)
{
	//* Parameter adjustments */
	--ifac;
	--wsave;
	--r__;

	//* Function Body */
	if (n == 1) {
	return;
	}
	rfftf1(n, &r__[1], &wsave[1], &wsave[n + 1], &ifac[1]);
	return;
} //* rfftf_ */

void rffti1(int32_t n, double *wa, int32_t *ifac)
{
	//* Initialized data */

	static int32_t ntryh[4] = { 4,2,3,5 };

	//* System generated locals */
	int32_t i__1, i__2, i__3;

	//* Local variables */
	int32_t i__, j, k1, l1, l2, ib;
	double fi;
	int32_t ld, ii, nf, ip, nl, is, nq, nr;
	double arg;
	int32_t ido, ipm;
	double tpi;
	int32_t nfm1;
	double argh;
	int32_t ntry=0;
	double argld;

	//* Parameter adjustments */
	--ifac;
	--wa;

	//* Function Body */
	nl = n;
	nf = 0;
	j = 0;
L101:
	++j;
	if (j - 4 <= 0) {
	goto L102;
	} else {
	goto L103;
	}
L102:
	ntry = ntryh[j - 1];
	goto L104;
L103:
	ntry += 2;
L104:
	nq = nl / ntry;
	nr = nl - ntry * nq;
	if (nr != 0) {
	goto L101;
	} else {
	goto L105;
	}
L105:
	++nf;
	ifac[nf + 2] = ntry;
	nl = nq;
	if (ntry != 2) {
	goto L107;
	}
	if (nf == 1) {
	goto L107;
	}
	i__1 = nf;
	for (i__ = 2; i__ <= i__1; ++i__) {
	ib = nf - i__ + 2;
	ifac[ib + 2] = ifac[ib + 1];
//* L106: */
	}
	ifac[3] = 2;
L107:
	if (nl != 1) {
	goto L104;
	}
	ifac[1] = n;
	ifac[2] = nf;
	tpi = (double) 6.283185307179586476925286766559005768394338798750211619498891846;
	argh = tpi / (double) n;
	is = 0;
	nfm1 = nf - 1;
	l1 = 1;
	if (nfm1 == 0) {
	return;
	}
	i__1 = nfm1;
	for (k1 = 1; k1 <= i__1; ++k1) {
	ip = ifac[k1 + 2];
	ld = 0;
	l2 = l1 * ip;
	ido = n / l2;
	ipm = ip - 1;
	i__2 = ipm;
	for (j = 1; j <= i__2; ++j) {
		ld += l1;
		i__ = is;
		argld = (double) ld * argh;
		fi = (double) 0.0;
		i__3 = ido;
		for (ii = 3; ii <= i__3; ii += 2) {
		i__ += 2;
		fi += (double) 1.0;
		arg = fi * argld;
		wa[i__ - 1] = cos(arg);
		wa[i__] = sin(arg);
//* L108: */
		}
		is += ido;
//* L109: */
	}
	l1 = l2;
//* L110: */
	}
	return;
} //* rffti1_ */


void rffti(int32_t n, double *wsave, int32_t *ifac)
{
	//* Parameter adjustments */
	--ifac;
	--wsave;

	//* Function Body */
	if (n == 1)
		return;

	rffti1(n, &wsave[n + 1], &ifac[1]);
	return;
} //* rffti_ */

void fftp(double *in, double *out, int n, int method, fft_plan_t *plan)	// FFT with a fixed plan
{
	/* method :
	 * 0 = DFT
	 * 1 = IDFT
	 */

	double *out2;
	int32_t i;
	double ratio = 1.0/sqrt((double) n);
	int32_t ifac_global[64];

	if (n < 2)
	{
		fprintf_rl(stderr, "fftp(): argument n = %d\n", n);
		return ;
	}

	if (in==out)					// if in-place FFT
		out2 = calloc (n, sizeof(double));	// allocate and assign the output array
	else						// if out-of-place FFT
		out2 = out;

	if (plan->plan_init && plan->alloc_size < 2*n+15)	// if alloc_size is too small
	{
		free_fft_plan(plan);				// reallocate to fit n
		*plan = alloc_fft_plan(n, -1);
		plan->plan_init = 0;
	}

	if (plan->plan_init && plan->fft_size != n)	// reinit plan if wrong size is saved
		plan->plan_init = 0;

	if (plan->plan_init==0)
	{
		rffti(n, plan->plan, ifac_global);					// initialise the 'plan'
		memcpy(plan->plan_backup, plan->plan, (2*n+15) * sizeof(double));	// back it up
		memcpy(plan->ifacg, ifac_global, 64 * sizeof(int32_t));
		plan->plan_init = 1;
		plan->fft_size = n;
	}
	else
	{
		memcpy(plan->plan, plan->plan_backup, (2*n+15) * sizeof(double));	// copy from backup
		memcpy(ifac_global, plan->ifacg, 64 * sizeof(int32_t));
	}

	if (method==0)
	{
		rfftf(n, in, plan->plan, ifac_global);		// FFT

		out2[0] = in[0];				// DC

		for (i=0; i<(n+(n&1)-2)>>1; i++)		// all real and imaginary bins except the Nyquist component
		{						// i represents the complex bin index, i=0 being both lowest real and imaginary components
			out2[i+1] = in[(i<<1)+1];		// real
			out2[n-i-1] = in[(i<<1)+2];		// imaginary
		}

		if ((n&1)==0)					// if there's a Nyquist component
			out2[n>>1] = in[n-1];			// copy it over
	}
	if (method==1)
	{
		out2[0] = in[0];				// DC

		for (i=0; i<(n+(n&1)-2)>>1; i++)		// all real and imaginary bins except the Nyquist component
		{						// i represents the complex bin index, i=0 being both lowest real and imaginary components
			out2[(i<<1)+1] = in[i+1];		// real
			out2[(i<<1)+2] = in[n-i-1];		// imaginary
		}

		if ((n&1)==0)					// if there's a Nyquist component
			out2[n-1] = in[n>>1];			// copy it over

		rfftb(n, out2, plan->plan, ifac_global);	// IFFT
	}

	if (in==out)
		memcpy (out, out2, n * sizeof(double));

	for (i=0; i<n; i++)
		out[i] *= ratio;

	if (out2!=out)
		free(out2);
}

fft_plan_t alloc_fft_plan(int fft_size, int alloc_size)
{
	fft_plan_t plan;

	plan.fft_size = -1;
	plan.alloc_size = alloc_size;
	if (alloc_size <= 0)
		plan.alloc_size = 2*fft_size + 15;

	plan.plan = calloc (plan.alloc_size, sizeof(double));
	plan.plan_backup = calloc (plan.alloc_size, sizeof(double));
	plan.ifacg = calloc(64, sizeof(int32_t));
	plan.plan_init = 0;

	return plan;
}

void free_fft_plan(fft_plan_t *plan)
{
	free(plan->plan);
	free(plan->plan_backup);
	free(plan->ifacg);

	memset(plan, 0, sizeof(fft_plan_t));
}

#endif
