/*
C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
C     *                                                               *
C     *                  copyright (c) 2011 by UCAR                   *
C     *                                                               *
C     *       University Corporation for Atmospheric Research         *
C     *                                                               *
C     *                      all rights reserved                      *
C     *                                                               *
C     *                     FFTPACK  version 5.1                      *
C     *                                                               *
C     *                 A Fortran Package of Fast Fourier             *
C     *                                                               *
C     *                Subroutines and Example Programs               *
C     *                                                               *
C     *                             by                                *
C     *                                                               *
C     *               Paul Swarztrauber and Dick Valent               *
C     *                                                               *
C     *                             of                                *
C     *                                                               *
C     *         the National Center for Atmospheric Research          *
C     *                                                               *
C     *                Boulder, Colorado  (80307)  U.S.A.             *
C     *                                                               *
C     *                   which is sponsored by                       *
C     *                                                               *
C     *              the National Science Foundation                  *
C     *                                                               *
C     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/* fftpack5.1.0 -- translated by f2c (version 20160102).
		http://www.netlib.org/f2c/libf2c.zip
*/

// silence compiler specific warnings
#ifdef __clang__
#pragma clang diagnostic ignored "-Wshift-op-parentheses"
#endif
#ifdef _MSC_VER
#pragma warning (disable: 4244 4554)
#endif

#include "fftpack_double.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

// Prototypes for all the functions
extern int xercon_d(int *inc, int *jump, int *n, int *lot);
extern int c1f2kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f2kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f3kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f3kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f4kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f4kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f5kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1f5kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa);
extern int c1fgkb_d(int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *in1, double *ch, double *ch1, int *in2, double *wa);
extern int c1fgkf_d(int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *in1, double *ch, double *ch1, int *in2, double *wa);
extern int c1fm1b_d(int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac);
extern int c1fm1f_d(int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac);
extern int cfft1b_d(int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfft1f_d(int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfft1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int cfft2b_d(int *ldim, int *l, int *m, fft_complexd_t *c__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfft2f_d(int *ldim, int *l, int *m, fft_complexd_t *c__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfft2i_d(int *l, int *m, double *wsave, int *lensav, int *ier);
extern int cfftmb_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfftmf_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cfftmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int cmf2kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf2kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf3kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf3kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf4kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf4kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf5kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmf5kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa);
extern int cmfgkb_d(int *lot, int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *im1, int *in1, double *ch, double *ch1, int *im2, int *in2, double *wa);
extern int cmfgkf_d(int *lot, int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *im1, int *in1, double *ch, double *ch1, int *im2, int *in2, double *wa);
extern int cmfm1b_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac);
extern int cmfm1f_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac);
extern int cosq1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cosq1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cosq1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int cosqb1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int cosqf1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int cosqmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cosqmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cosqmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int cost1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cost1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int cost1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int costb1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int costf1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int costmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int costmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int costmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int factor_d(int *n, int *nf, double *fac);
extern int mcfti1_d(int *n, double *wa, double *fnf, double *fac);
extern int mcsqb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int mcsqf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *work, int *ier);
extern int mcstb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *work, int *ier);
extern int mcstf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *work, int *ier);
extern int mradb2_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1);
extern int mradb3_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2);
extern int mradb4_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3);
extern int mradb5_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3, double *wa4);
extern int mradbg_d(int *m, int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *im1, int *in1, double *ch, double *ch2, int *im2, int *in2, double *wa);
extern int mradf2_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1);
extern int mradf3_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2);
extern int mradf4_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3);
extern int mradf5_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3, double *wa4);
extern int mradfg_d(int *m, int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *im1, int *in1, double *ch, double *ch2, int *im2, int *in2, double *wa);
extern int mrftb1_d(int *m, int *im, int *n, int *in, double *c__, double *ch, double *wa, double *fac);
extern int mrftf1_d(int *m, int *im, int *n, int *in, double *c__, double *ch, double *wa, double *fac);
extern int mrfti1_d(int *n, double *wa, double *fac);
extern int msntb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *xh, double *work, int *ier);
extern int msntf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *xh, double *work, int *ier);
extern int r1f2kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1);
extern int r1f2kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1);
extern int r1f3kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2);
extern int r1f3kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2);
extern int r1f4kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3);
extern int r1f4kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3);
extern int r1f5kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3, double *wa4);
extern int r1f5kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3, double *wa4);
extern int r1fgkb_d(int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *in1, double *ch, double *ch2, int *in2, double *wa);
extern int r1fgkf_d(int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *in1, double *ch, double *ch2, int *in2, double *wa);
extern int r2w_d(int *ldr, int *ldw, int *l, int *m, double *r__, double *w);
extern int rfft1b_d(int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfft1f_d(int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfft1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int rfft2b_d(int *ldim, int *l, int *m, double *r__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfft2f_d(int *ldim, int *l, int *m, double *r__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfft2i_d(int *l, int *m, double *wsave, int *lensav, int *ier);
extern int rfftb1_d(int *n, int *in, double *c__, double *ch, double *wa, double *fac);
extern int rfftf1_d(int *n, int *in, double *c__, double *ch, double *wa, double *fac);
extern int rffti1_d(int *n, double *wa, double *fac);
extern int rfftmb_d(int *lot, int *jump, int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfftmf_d(int *lot, int *jump, int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int rfftmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int sinq1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sinq1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sinq1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int sinqmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sinqmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sinqmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int sint1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sint1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sint1i_d(int *n, double *wsave, int *lensav, int *ier);
extern int sintb1_d(int *n, int *inc, double *x, double *wsave, double *xh, double *work, int *ier);
extern int sintf1_d(int *n, int *inc, double *x, double *wsave, double *xh, double *work, int *ier);
extern int sintmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sintmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
extern int sintmi_d(int *n, double *wsave, int *lensav, int *ier);
extern int tables_d(int *ido, int *ip, double *wa);
extern int w2r_d(int *ldr, int *ldw, int *l, int *m, double *r__, double *w);

/* unused function, errors to be handled by return code */
int xerfft_d(char *a, int *b, int c){
  return 0;
}

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f2kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double ti2, tr2, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 1);
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 3);
    ch -= ch_offset;

    /* Function Body */
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	chold1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1];
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = cc[(k + (
		cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((cc_dim3 <<
		1) + 1) * cc_dim2) * cc_dim1 + 1];
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = chold1;
	chold2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2];
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = cc[(k + (
		cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((cc_dim3 <<
		1) + 1) * cc_dim2) * cc_dim1 + 2];
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = chold2;
/* L101: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 1] + cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) *
		cc_dim1 + 1];
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 2] + cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) *
		cc_dim1 + 2];
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 2];
/* L103: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[(k + ((i__ << 1) + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__
		    + cc_dim3) * cc_dim2) * cc_dim1 + 1] + cc[(k + (i__ + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] - cc[(k +
		    (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + ((i__ << 1) + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__
		    + cc_dim3) * cc_dim2) * cc_dim1 + 2] + cc[(k + (i__ + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] - cc[(k +
		    (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2];
	    ch[(k + ((i__ << 1) + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 1)] * ti2 + wa[i__ + wa_dim1 * 3] * tr2;
	    ch[(k + ((i__ << 1) + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 1)] * tr2 - wa[i__ + wa_dim1 * 3] * ti2;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f2kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f2kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double sn, ti2, tr2, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 1);
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 3);
    ch -= ch_offset;

    /* Function Body */
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 << 1);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	chold1 = sn * (cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(
		k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]);
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cc[(k
		+ (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((cc_dim3
		<< 1) + 1) * cc_dim2) * cc_dim1 + 1]);
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = chold1;
	chold2 = sn * (cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(
		k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]);
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (cc[(k
		+ (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((cc_dim3
		<< 1) + 1) * cc_dim2) * cc_dim1 + 2]);
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = chold2;
/* L101: */
    }
    return 0;
L106:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = sn * (cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] + cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 1]);
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = sn * (cc[(k + (cc_dim3 + 1) *
		 cc_dim2) * cc_dim1 + 1] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 1]);
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = sn * (cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] + cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 2]);
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = sn * (cc[(k + (cc_dim3 + 1) *
		 cc_dim2) * cc_dim1 + 2] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 2]);
/* L107: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 1] + cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) *
		cc_dim1 + 1];
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 2] + cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) *
		cc_dim1 + 2];
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] - cc[(k + ((cc_dim3 << 1) + 1) *
		cc_dim2) * cc_dim1 + 2];
/* L103: */
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[(k + ((i__ << 1) + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__
		    + cc_dim3) * cc_dim2) * cc_dim1 + 1] + cc[(k + (i__ + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] - cc[(k +
		    (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + ((i__ << 1) + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__
		    + cc_dim3) * cc_dim2) * cc_dim1 + 2] + cc[(k + (i__ + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] - cc[(k +
		    (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2];
	    ch[(k + ((i__ << 1) + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 1)] * ti2 - wa[i__ + wa_dim1 * 3] * tr2;
	    ch[(k + ((i__ << 1) + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 1)] * tr2 + wa[i__ + wa_dim1 * 3] * ti2;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f2kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f3kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* Initialized data */

     double taur = -.5;
     double taui = .866025403784439;

    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double ci2, ci3, di2, di3, cr2, cr3, dr2, dr3, ti2, tr2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 3;
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + (ch_dim2 << 2));
    ch -= ch_offset;

    /* Function Body */

    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + taur * tr2;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] += tr2;
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + taur * ti2;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] += ti2;
	cr3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1]);
	ci3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2]);
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = cr2 - ci3;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = cr2 + ci3;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = ci2 + cr3;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = ci2 - cr3;
/* L101: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + taur * tr2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] + tr2;
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + taur * ti2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] + ti2;
	cr3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1]);
	ci3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2]);
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = cr2 - ci3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = cr2 + ci3;
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = ci2 + cr3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = ci2 - cr3;
/* L103: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    tr2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    cr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + taur *
		    tr2;
	    ch[(k + (i__ * 3 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr2;
	    ti2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ci2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + taur *
		    ti2;
	    ch[(k + (i__ * 3 + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 2] + ti2;
	    cr3 = taui * (cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] - cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    1]);
	    ci3 = taui * (cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 2] - cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    2]);
	    dr2 = cr2 - ci3;
	    dr3 = cr2 + ci3;
	    di2 = ci2 + cr3;
	    di3 = ci2 - cr3;
	    ch[(k + (i__ * 3 + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 3] * di2 + wa[i__ + wa_dim1 * 5] * dr2;
	    ch[(k + (i__ * 3 + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 3] * dr2 - wa[i__ + wa_dim1 * 5] * di2;
	    ch[(k + (i__ * 3 + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 2)] * di3 + wa[i__ + wa_dim1 * 6] * dr3;
	    ch[(k + (i__ * 3 + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 2)] * dr3 - wa[i__ + wa_dim1 * 6] * di3;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f3kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f3kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* Initialized data */

     double taur = -.5;
     double taui = -.866025403784439;

    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double sn, ci2, ci3, di2, di3, cr2, cr3, dr2, dr3, ti2, tr2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 3;
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + (ch_dim2 << 2));
    ch -= ch_offset;

    /* Function Body */

    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 * 3);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + taur * tr2;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cc[(k + (
		cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr2);
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + taur * ti2;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (cc[(k + (
		cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + ti2);
	cr3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1]);
	ci3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2]);
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr2 -
		ci3);
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr2 + ci3)
		;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci2 +
		cr3);
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci2 - cr3)
		;
/* L101: */
    }
    return 0;
L106:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + taur * tr2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = sn * (cc[(k + (cc_dim3 + 1) *
		 cc_dim2) * cc_dim1 + 1] + tr2);
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + taur * ti2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = sn * (cc[(k + (cc_dim3 + 1) *
		 cc_dim2) * cc_dim1 + 2] + ti2);
	cr3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1]);
	ci3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2]);
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = sn * (cr2 - ci3);
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = sn * (cr2 + ci3);
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = sn * (ci2 + cr3);
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = sn * (ci2 - cr3);
/* L107: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + taur * tr2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] + tr2;
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + taur * ti2;
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] + ti2;
	cr3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1]);
	ci3 = taui * (cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2]
		- cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2]);
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = cr2 - ci3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = cr2 + ci3;
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = ci2 + cr3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = ci2 - cr3;
/* L103: */
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    tr2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    cr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + taur *
		    tr2;
	    ch[(k + (i__ * 3 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr2;
	    ti2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ci2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + taur *
		    ti2;
	    ch[(k + (i__ * 3 + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 2] + ti2;
	    cr3 = taui * (cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] - cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    1]);
	    ci3 = taui * (cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 2] - cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    2]);
	    dr2 = cr2 - ci3;
	    dr3 = cr2 + ci3;
	    di2 = ci2 + cr3;
	    di3 = ci2 - cr3;
	    ch[(k + (i__ * 3 + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 3] * di2 - wa[i__ + wa_dim1 * 5] * dr2;
	    ch[(k + (i__ * 3 + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 3] * dr2 + wa[i__ + wa_dim1 * 5] * di2;
	    ch[(k + (i__ * 3 + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 2)] * di3 - wa[i__ + wa_dim1 * 6] * dr3;
	    ch[(k + (i__ * 3 + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 2)] * dr3 + wa[i__ + wa_dim1 * 6] * di3;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f3kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f4kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double ci2, ci3, ci4, cr2, cr3, cr4, ti1, ti2, ti3, ti4, tr1, tr2,
	    tr3, tr4;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 2);
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 5);
    ch -= ch_offset;

    /* Function Body */
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	tr4 = cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	ti4 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = tr2 + tr3;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = tr2 - tr3;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = ti2 + ti3;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = ti2 - ti3;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = tr1 + tr4;
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] = tr1 - tr4;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = ti1 + ti4;
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] = ti1 - ti4;
/* L101: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	tr4 = cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	ti4 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = tr2 + tr3;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = tr2 - tr3;
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = ti2 + ti3;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = ti2 - ti3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = tr1 + tr4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = tr1 - tr4;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = ti1 + ti4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = ti1 - ti4;
/* L103: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ti1 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] - cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ti3 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    tr4 = cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2] -
		    cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2];
	    tr1 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] - cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    ti4 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    tr3 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + ((i__ << 2) + 1) * ch_dim2) * ch_dim1 + 1] = tr2 + tr3;
	    cr3 = tr2 - tr3;
	    ch[(k + ((i__ << 2) + 1) * ch_dim2) * ch_dim1 + 2] = ti2 + ti3;
	    ci3 = ti2 - ti3;
	    cr2 = tr1 + tr4;
	    cr4 = tr1 - tr4;
	    ci2 = ti1 + ti4;
	    ci4 = ti1 - ti4;
	    ch[(k + ((i__ << 2) + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 2)] * cr2 - wa[i__ + wa_dim1 * 7] * ci2;
	    ch[(k + ((i__ << 2) + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 2)] * ci2 + wa[i__ + wa_dim1 * 7] * cr2;
	    ch[(k + ((i__ << 2) + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 5] * cr3 - wa[i__ + (wa_dim1 << 3)] * ci3;
	    ch[(k + ((i__ << 2) + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 5] * ci3 + wa[i__ + (wa_dim1 << 3)] * cr3;
	    ch[(k + ((i__ << 2) + 4) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 6] * cr4 - wa[i__ + wa_dim1 * 9] * ci4;
	    ch[(k + ((i__ << 2) + 4) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 6] * ci4 + wa[i__ + wa_dim1 * 9] * cr4;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f4kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f4kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double sn, ci2, ci3, ci4, cr2, cr3, cr4, ti1, ti2, ti3, ti4, tr1,
	    tr2, tr3, tr4;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 2);
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 5);
    ch -= ch_offset;

    /* Function Body */
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 << 2);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	tr4 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	ti4 = cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (tr2 + tr3);
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (tr2 - tr3)
		;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ti2 + ti3);
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ti2 - ti3)
		;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (tr1 +
		tr4);
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (tr1 -
		tr4);
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ti1 +
		ti4);
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ti1 -
		ti4);
/* L101: */
    }
    return 0;
L106:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	tr4 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	ti4 = cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = sn * (tr2 + tr3);
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = sn * (tr2 - tr3);
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = sn * (ti2 + ti3);
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = sn * (ti2 - ti3);
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = sn * (tr1 + tr4);
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = sn * (tr1 - tr4);
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = sn * (ti1 + ti4);
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = sn * (ti1 - ti4);
/* L107: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2];
	tr4 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + (
		cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1];
	ti4 = cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = tr2 + tr3;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = tr2 - tr3;
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = ti2 + ti3;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = ti2 - ti3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = tr1 + tr4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = tr1 - tr4;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = ti1 + ti4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = ti1 - ti4;
/* L103: */
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ti1 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] - cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2];
	    ti3 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    tr4 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] -
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    tr1 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] - cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + cc[(k +
		    (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	    ti4 = cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] -
		    cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	    tr3 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + ((i__ << 2) + 1) * ch_dim2) * ch_dim1 + 1] = tr2 + tr3;
	    cr3 = tr2 - tr3;
	    ch[(k + ((i__ << 2) + 1) * ch_dim2) * ch_dim1 + 2] = ti2 + ti3;
	    ci3 = ti2 - ti3;
	    cr2 = tr1 + tr4;
	    cr4 = tr1 - tr4;
	    ci2 = ti1 + ti4;
	    ci4 = ti1 - ti4;
	    ch[(k + ((i__ << 2) + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 2)] * cr2 + wa[i__ + wa_dim1 * 7] * ci2;
	    ch[(k + ((i__ << 2) + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 2)] * ci2 - wa[i__ + wa_dim1 * 7] * cr2;
	    ch[(k + ((i__ << 2) + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 5] * cr3 + wa[i__ + (wa_dim1 << 3)] * ci3;
	    ch[(k + ((i__ << 2) + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 5] * ci3 - wa[i__ + (wa_dim1 << 3)] * cr3;
	    ch[(k + ((i__ << 2) + 4) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 6] * cr4 + wa[i__ + wa_dim1 * 9] * ci4;
	    ch[(k + ((i__ << 2) + 4) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 6] * ci4 - wa[i__ + wa_dim1 * 9] * cr4;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f4kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f5kb_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* Initialized data */

     double tr11 = .3090169943749474;
     double ti11 = .9510565162951536;
     double tr12 = -.8090169943749474;
     double ti12 = .5877852522924731;

    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double ci2, ci3, ci4, ci5, di3, di4, di5, di2, cr2, cr3, cr5, cr4,
	    dr3, dr4, ti2, ti3, ti4, ti5, dr5, dr2, tr2, tr3, tr4, tr5,
	    chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 5;
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 6);
    ch -= ch_offset;

    /* Function Body */

/* FFTPACK 5.1 auxiliary routine */

    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	chold1 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr2 + tr3;
	chold2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + ti2 + ti3;
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr11 * tr2 +
		tr12 * tr3;
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr11 * ti2 +
		tr12 * ti3;
	cr3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr12 * tr2 +
		tr11 * tr3;
	ci3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr12 * ti2 +
		tr11 * ti3;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = chold1;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = chold2;
	cr5 = ti11 * tr5 + ti12 * tr4;
	ci5 = ti11 * ti5 + ti12 * ti4;
	cr4 = ti12 * tr5 - ti11 * tr4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = cr2 - ci5;
	cc[(k + (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1] = cr2 + ci5;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = ci2 + cr5;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = ci3 + cr4;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = cr3 - ci4;
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] = cr3 + ci4;
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] = ci3 - cr4;
	cc[(k + (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2] = ci2 - cr5;
/* L101: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 1] + tr2 + tr3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 2] + ti2 + ti3;
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr11 * tr2 +
		tr12 * tr3;
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr11 * ti2 +
		tr12 * ti3;
	cr3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr12 * tr2 +
		tr11 * tr3;
	ci3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr12 * ti2 +
		tr11 * ti3;
	cr5 = ti11 * tr5 + ti12 * tr4;
	ci5 = ti11 * ti5 + ti12 * ti4;
	cr4 = ti12 * tr5 - ti11 * tr4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = cr2 - ci5;
	ch[(k + ch_dim2 * 10) * ch_dim1 + 1] = cr2 + ci5;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = ci2 + cr5;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = ci3 + cr4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = cr3 - ci4;
	ch[(k + ch_dim2 * 9) * ch_dim1 + 1] = cr3 + ci4;
	ch[(k + ch_dim2 * 9) * ch_dim1 + 2] = ci3 - cr4;
	ch[(k + ch_dim2 * 10) * ch_dim1 + 2] = ci2 - cr5;
/* L103: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ti5 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] -
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 2];
	    ti4 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2] - cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    ti3 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2] + cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    tr5 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1];
	    tr4 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    tr3 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + (i__ * 5 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr2 + tr3;
	    ch[(k + (i__ * 5 + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 2] + ti2 + ti3;
	    cr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 *
		    tr2 + tr12 * tr3;
	    ci2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + tr11 *
		    ti2 + tr12 * ti3;
	    cr3 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 *
		    tr2 + tr11 * tr3;
	    ci3 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + tr12 *
		    ti2 + tr11 * ti3;
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
	    ch[(k + (i__ * 5 + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 5] * dr2 - wa[i__ + wa_dim1 * 9] * di2;
	    ch[(k + (i__ * 5 + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 5] * di2 + wa[i__ + wa_dim1 * 9] * dr2;
	    ch[(k + (i__ * 5 + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 6] * dr3 - wa[i__ + wa_dim1 * 10] * di3;
	    ch[(k + (i__ * 5 + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 6] * di3 + wa[i__ + wa_dim1 * 10] * dr3;
	    ch[(k + (i__ * 5 + 4) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 7] * dr4 - wa[i__ + wa_dim1 * 11] * di4;
	    ch[(k + (i__ * 5 + 4) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 7] * di4 + wa[i__ + wa_dim1 * 11] * dr4;
	    ch[(k + (i__ * 5 + 5) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 3)] * dr5 - wa[i__ + wa_dim1 * 12] * di5;
	    ch[(k + (i__ * 5 + 5) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 3)] * di5 + wa[i__ + wa_dim1 * 12] * dr5;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f5kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1f5kf_d(int *ido, int *l1, int *na, double *cc, int *in1, double *ch, int *in2, double *wa)
{
    /* Initialized data */

     double tr11 = .3090169943749474;
     double ti11 = -.9510565162951536;
     double tr12 = -.8090169943749474;
     double ti12 = -.5877852522924731;

    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2;

    /* Local variables */
     int i__, k;
     double sn, ci2, ci3, ci4, ci5, di3, di4, di5, di2, cr2, cr3, cr5,
	    cr4, dr3, dr4, ti2, ti3, ti4, ti5, dr5, dr2, tr2, tr3, tr4, tr5,
	    chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 5;
    wa -= wa_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 6);
    ch -= ch_offset;

    /* Function Body */

/* FFTPACK 5.1 auxiliary routine */

    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 * 5);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	chold1 = sn * (cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr2
		+ tr3);
	chold2 = sn * (cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + ti2
		+ ti3);
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr11 * tr2 +
		tr12 * tr3;
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr11 * ti2 +
		tr12 * ti3;
	cr3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr12 * tr2 +
		tr11 * tr3;
	ci3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr12 * ti2 +
		tr11 * ti3;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = chold1;
	cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = chold2;
	cr5 = ti11 * tr5 + ti12 * tr4;
	ci5 = ti11 * ti5 + ti12 * ti4;
	cr4 = ti12 * tr5 - ti11 * tr4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr2 -
		ci5);
	cc[(k + (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr2 + ci5)
		;
	cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci2 +
		cr5);
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci3 + cr4)
		;
	cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr3 - ci4)
		;
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1] = sn * (cr3 +
		ci4);
	cc[(k + ((cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci3 -
		cr4);
	cc[(k + (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2] = sn * (ci2 - cr5)
		;
/* L101: */
    }
    return 0;
L106:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = sn * (cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 1] + tr2 + tr3);
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = sn * (cc[(k + (cc_dim3 + 1) *
		cc_dim2) * cc_dim1 + 2] + ti2 + ti3);
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr11 * tr2 +
		tr12 * tr3;
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr11 * ti2 +
		tr12 * ti3;
	cr3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr12 * tr2 +
		tr11 * tr3;
	ci3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr12 * ti2 +
		tr11 * ti3;
	cr5 = ti11 * tr5 + ti12 * tr4;
	ci5 = ti11 * ti5 + ti12 * ti4;
	cr4 = ti12 * tr5 - ti11 * tr4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = sn * (cr2 - ci5);
	ch[(k + ch_dim2 * 10) * ch_dim1 + 1] = sn * (cr2 + ci5);
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = sn * (ci2 + cr5);
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = sn * (ci3 + cr4);
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = sn * (cr3 - ci4);
	ch[(k + ch_dim2 * 9) * ch_dim1 + 1] = sn * (cr3 + ci4);
	ch[(k + ch_dim2 * 9) * ch_dim1 + 2] = sn * (ci3 - cr4);
	ch[(k + ch_dim2 * 10) * ch_dim1 + 2] = sn * (ci2 - cr5);
/* L107: */
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ti5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 2];
	ti4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	ti3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 2] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 2];
	tr5 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr2 = cc[(k + ((cc_dim3 << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k
		+ (cc_dim3 * 5 + 1) * cc_dim2) * cc_dim1 + 1];
	tr4 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] - cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	tr3 = cc[(k + (cc_dim3 * 3 + 1) * cc_dim2) * cc_dim1 + 1] + cc[(k + ((
		cc_dim3 << 2) + 1) * cc_dim2) * cc_dim1 + 1];
	ch[(k + ch_dim2 * 6) * ch_dim1 + 1] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 1] + tr2 + tr3;
	ch[(k + ch_dim2 * 6) * ch_dim1 + 2] = cc[(k + (cc_dim3 + 1) * cc_dim2)
		 * cc_dim1 + 2] + ti2 + ti3;
	cr2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr11 * tr2 +
		tr12 * tr3;
	ci2 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr11 * ti2 +
		tr12 * ti3;
	cr3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] + tr12 * tr2 +
		tr11 * tr3;
	ci3 = cc[(k + (cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] + tr12 * ti2 +
		tr11 * ti3;
	cr5 = ti11 * tr5 + ti12 * tr4;
	ci5 = ti11 * ti5 + ti12 * ti4;
	cr4 = ti12 * tr5 - ti11 * tr4;
	ci4 = ti12 * ti5 - ti11 * ti4;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 1] = cr2 - ci5;
	ch[(k + ch_dim2 * 10) * ch_dim1 + 1] = cr2 + ci5;
	ch[(k + ch_dim2 * 7) * ch_dim1 + 2] = ci2 + cr5;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 2] = ci3 + cr4;
	ch[(k + (ch_dim2 << 3)) * ch_dim1 + 1] = cr3 - ci4;
	ch[(k + ch_dim2 * 9) * ch_dim1 + 1] = cr3 + ci4;
	ch[(k + ch_dim2 * 9) * ch_dim1 + 2] = ci3 - cr4;
	ch[(k + ch_dim2 * 10) * ch_dim1 + 2] = ci2 - cr5;
/* L103: */
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ti5 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] -
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 2];
	    ti2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 2] +
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 2];
	    ti4 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2] - cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    ti3 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 2] + cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 2];
	    tr5 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1];
	    tr2 = cc[(k + (i__ + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] +
		    cc[(k + (i__ + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1];
	    tr4 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    tr3 = cc[(k + (i__ + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + cc[(
		    k + (i__ + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1];
	    ch[(k + (i__ * 5 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr2 + tr3;
	    ch[(k + (i__ * 5 + 1) * ch_dim2) * ch_dim1 + 2] = cc[(k + (i__ +
		    cc_dim3) * cc_dim2) * cc_dim1 + 2] + ti2 + ti3;
	    cr2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 *
		    tr2 + tr12 * tr3;
	    ci2 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + tr11 *
		    ti2 + tr12 * ti3;
	    cr3 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 *
		    tr2 + tr11 * tr3;
	    ci3 = cc[(k + (i__ + cc_dim3) * cc_dim2) * cc_dim1 + 2] + tr12 *
		    ti2 + tr11 * ti3;
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
	    ch[(k + (i__ * 5 + 2) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 5] * dr2 + wa[i__ + wa_dim1 * 9] * di2;
	    ch[(k + (i__ * 5 + 2) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 5] * di2 - wa[i__ + wa_dim1 * 9] * dr2;
	    ch[(k + (i__ * 5 + 3) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 6] * dr3 + wa[i__ + wa_dim1 * 10] * di3;
	    ch[(k + (i__ * 5 + 3) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 6] * di3 - wa[i__ + wa_dim1 * 10] * dr3;
	    ch[(k + (i__ * 5 + 4) * ch_dim2) * ch_dim1 + 1] = wa[i__ +
		    wa_dim1 * 7] * dr4 + wa[i__ + wa_dim1 * 11] * di4;
	    ch[(k + (i__ * 5 + 4) * ch_dim2) * ch_dim1 + 2] = wa[i__ +
		    wa_dim1 * 7] * di4 - wa[i__ + wa_dim1 * 11] * dr4;
	    ch[(k + (i__ * 5 + 5) * ch_dim2) * ch_dim1 + 1] = wa[i__ + (
		    wa_dim1 << 3)] * dr5 + wa[i__ + wa_dim1 * 12] * di5;
	    ch[(k + (i__ * 5 + 5) * ch_dim2) * ch_dim1 + 2] = wa[i__ + (
		    wa_dim1 << 3)] * di5 - wa[i__ + wa_dim1 * 12] * dr5;
/* L104: */
	}
/* L105: */
    }
    return 0;
} /* c1f5kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1fgkb_d(int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *in1, double *ch, double *ch1, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, cc1_dim1, cc1_dim2, cc1_offset, ch1_dim1, ch1_dim2,
	    ch1_offset, wa_dim1, wa_dim2, wa_offset, i__1, i__2, i__3;

    /* Local variables */
     int i__, j, k, l, jc, lc, ki;
     double wai, war;
     int ipp2, idlj, ipph;
     double chold1, chold2;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_dim2 = *ip - 1;
    wa_offset = 1 + wa_dim1 * (1 + wa_dim2);
    wa -= wa_offset;
    cc1_dim1 = *in1;
    cc1_dim2 = *lid;
    cc1_offset = 1 + cc1_dim1 * (1 + cc1_dim2);
    cc1 -= cc1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch1_dim1 = *in2;
    ch1_dim2 = *lid;
    ch1_offset = 1 + ch1_dim1 * (1 + ch1_dim2);
    ch1 -= ch1_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_dim3 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	ch1[(ki + ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 1];
	ch1[(ki + ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 2];
/* L110: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 1] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 1] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    1];
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    2];
/* L112: */
	}
/* L111: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    cc1[(ki + cc1_dim2) * cc1_dim1 + 1] += ch1[(ki + j * ch1_dim2) *
		    ch1_dim1 + 1];
	    cc1[(ki + cc1_dim2) * cc1_dim1 + 2] += ch1[(ki + j * ch1_dim2) *
		    ch1_dim1 + 2];
/* L117: */
	}
/* L118: */
    }
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    cc1[(ki + l * cc1_dim2) * cc1_dim1 + 1] = ch1[(ki + ch1_dim2) *
		    ch1_dim1 + 1] + wa[(l - 1 + wa_dim2) * wa_dim1 + 1] * ch1[
		    (ki + (ch1_dim2 << 1)) * ch1_dim1 + 1];
	    cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 1] = wa[(l - 1 + (wa_dim2 <<
		     1)) * wa_dim1 + 1] * ch1[(ki + *ip * ch1_dim2) *
		    ch1_dim1 + 1];
	    cc1[(ki + l * cc1_dim2) * cc1_dim1 + 2] = ch1[(ki + ch1_dim2) *
		    ch1_dim1 + 2] + wa[(l - 1 + wa_dim2) * wa_dim1 + 1] * ch1[
		    (ki + (ch1_dim2 << 1)) * ch1_dim1 + 2];
	    cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 2] = wa[(l - 1 + (wa_dim2 <<
		     1)) * wa_dim1 + 1] * ch1[(ki + *ip * ch1_dim2) *
		    ch1_dim1 + 2];
/* L113: */
	}
	i__2 = ipph;
	for (j = 3; j <= i__2; ++j) {
	    jc = ipp2 - j;
	    idlj = (l - 1) * (j - 1) % *ip;
	    war = wa[(idlj + wa_dim2) * wa_dim1 + 1];
	    wai = wa[(idlj + (wa_dim2 << 1)) * wa_dim1 + 1];
	    i__3 = *lid;
	    for (ki = 1; ki <= i__3; ++ki) {
		cc1[(ki + l * cc1_dim2) * cc1_dim1 + 1] += war * ch1[(ki + j *
			 ch1_dim2) * ch1_dim1 + 1];
		cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 1] += wai * ch1[(ki +
			jc * ch1_dim2) * ch1_dim1 + 1];
		cc1[(ki + l * cc1_dim2) * cc1_dim1 + 2] += war * ch1[(ki + j *
			 ch1_dim2) * ch1_dim1 + 2];
		cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 2] += wai * ch1[(ki +
			jc * ch1_dim2) * ch1_dim1 + 2];
/* L114: */
	    }
/* L115: */
	}
/* L116: */
    }
    if (*ido > 1 || *na == 1) {
	goto L136;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    chold1 = cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] - cc1[(ki + jc *
		    cc1_dim2) * cc1_dim1 + 2];
	    chold2 = cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] + cc1[(ki + jc *
		    cc1_dim2) * cc1_dim1 + 2];
	    cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] = chold1;
	    cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    1];
	    cc1[(ki + j * cc1_dim2) * cc1_dim1 + 2] += cc1[(ki + jc *
		    cc1_dim2) * cc1_dim1 + 1];
	    cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1] = chold2;
/* L119: */
	}
/* L120: */
    }
    return 0;
L136:
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	ch1[(ki + ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 1];
	ch1[(ki + ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 2];
/* L137: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 1] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 1] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    2];
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    1];
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1]
		    ;
/* L134: */
	}
/* L135: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(k + (i__ * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = ch[(k + (
		    i__ + ch_dim3) * ch_dim2) * ch_dim1 + 1];
	    cc[(k + (i__ * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = ch[(k + (
		    i__ + ch_dim3) * ch_dim2) * ch_dim1 + 2];
/* L130: */
	}
/* L131: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(k + (j + cc_dim3) * cc_dim2) * cc_dim1 + 1] = ch[(k + (j *
		    ch_dim3 + 1) * ch_dim2) * ch_dim1 + 1];
	    cc[(k + (j + cc_dim3) * cc_dim2) * cc_dim1 + 2] = ch[(k + (j *
		    ch_dim3 + 1) * ch_dim2) * ch_dim1 + 2];
/* L122: */
	}
/* L123: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *ido;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		cc[(k + (j + i__ * cc_dim3) * cc_dim2) * cc_dim1 + 1] = wa[
			i__ + (j - 1 + wa_dim2) * wa_dim1] * ch[(k + (i__ + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 1] - wa[i__ + (j -
			1 + (wa_dim2 << 1)) * wa_dim1] * ch[(k + (i__ + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 2];
		cc[(k + (j + i__ * cc_dim3) * cc_dim2) * cc_dim1 + 2] = wa[
			i__ + (j - 1 + wa_dim2) * wa_dim1] * ch[(k + (i__ + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 2] + wa[i__ + (j -
			1 + (wa_dim2 << 1)) * wa_dim1] * ch[(k + (i__ + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L124: */
	    }
/* L125: */
	}
/* L126: */
    }
    return 0;
} /* c1fgkb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1fgkf_d(int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *in1, double *ch, double *ch1, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, cc1_dim1, cc1_dim2, cc1_offset, ch1_dim1, ch1_dim2,
	    ch1_offset, wa_dim1, wa_dim2, wa_offset, i__1, i__2, i__3;

    /* Local variables */
     int i__, j, k, l, jc, lc, ki;
     double sn, wai, war;
     int ipp2, idlj, ipph;
     double chold1, chold2;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_dim2 = *ip - 1;
    wa_offset = 1 + wa_dim1 * (1 + wa_dim2);
    wa -= wa_offset;
    cc1_dim1 = *in1;
    cc1_dim2 = *lid;
    cc1_offset = 1 + cc1_dim1 * (1 + cc1_dim2);
    cc1 -= cc1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *l1;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch1_dim1 = *in2;
    ch1_dim2 = *lid;
    ch1_offset = 1 + ch1_dim1 * (1 + ch1_dim2);
    ch1 -= ch1_offset;
    ch_dim1 = *in2;
    ch_dim2 = *l1;
    ch_dim3 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	ch1[(ki + ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 1];
	ch1[(ki + ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 2];
/* L110: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 1] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 1] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    1];
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    2];
/* L112: */
	}
/* L111: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    cc1[(ki + cc1_dim2) * cc1_dim1 + 1] += ch1[(ki + j * ch1_dim2) *
		    ch1_dim1 + 1];
	    cc1[(ki + cc1_dim2) * cc1_dim1 + 2] += ch1[(ki + j * ch1_dim2) *
		    ch1_dim1 + 2];
/* L117: */
	}
/* L118: */
    }
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    cc1[(ki + l * cc1_dim2) * cc1_dim1 + 1] = ch1[(ki + ch1_dim2) *
		    ch1_dim1 + 1] + wa[(l - 1 + wa_dim2) * wa_dim1 + 1] * ch1[
		    (ki + (ch1_dim2 << 1)) * ch1_dim1 + 1];
	    cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 1] = -wa[(l - 1 + (wa_dim2
		    << 1)) * wa_dim1 + 1] * ch1[(ki + *ip * ch1_dim2) *
		    ch1_dim1 + 1];
	    cc1[(ki + l * cc1_dim2) * cc1_dim1 + 2] = ch1[(ki + ch1_dim2) *
		    ch1_dim1 + 2] + wa[(l - 1 + wa_dim2) * wa_dim1 + 1] * ch1[
		    (ki + (ch1_dim2 << 1)) * ch1_dim1 + 2];
	    cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 2] = -wa[(l - 1 + (wa_dim2
		    << 1)) * wa_dim1 + 1] * ch1[(ki + *ip * ch1_dim2) *
		    ch1_dim1 + 2];
/* L113: */
	}
	i__2 = ipph;
	for (j = 3; j <= i__2; ++j) {
	    jc = ipp2 - j;
	    idlj = (l - 1) * (j - 1) % *ip;
	    war = wa[(idlj + wa_dim2) * wa_dim1 + 1];
	    wai = -wa[(idlj + (wa_dim2 << 1)) * wa_dim1 + 1];
	    i__3 = *lid;
	    for (ki = 1; ki <= i__3; ++ki) {
		cc1[(ki + l * cc1_dim2) * cc1_dim1 + 1] += war * ch1[(ki + j *
			 ch1_dim2) * ch1_dim1 + 1];
		cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 1] += wai * ch1[(ki +
			jc * ch1_dim2) * ch1_dim1 + 1];
		cc1[(ki + l * cc1_dim2) * cc1_dim1 + 2] += war * ch1[(ki + j *
			 ch1_dim2) * ch1_dim1 + 2];
		cc1[(ki + lc * cc1_dim2) * cc1_dim1 + 2] += wai * ch1[(ki +
			jc * ch1_dim2) * ch1_dim1 + 2];
/* L114: */
	    }
/* L115: */
	}
/* L116: */
    }
    if (*ido > 1) {
	goto L136;
    }
    sn = 1.0 / (double) (*ip * *l1);
    if (*na == 1) {
	goto L146;
    }
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	cc1[(ki + cc1_dim2) * cc1_dim1 + 1] = sn * cc1[(ki + cc1_dim2) *
		cc1_dim1 + 1];
	cc1[(ki + cc1_dim2) * cc1_dim1 + 2] = sn * cc1[(ki + cc1_dim2) *
		cc1_dim1 + 2];
/* L149: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    chold1 = sn * (cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] - cc1[(ki
		    + jc * cc1_dim2) * cc1_dim1 + 2]);
	    chold2 = sn * (cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] + cc1[(ki
		    + jc * cc1_dim2) * cc1_dim1 + 2]);
	    cc1[(ki + j * cc1_dim2) * cc1_dim1 + 1] = chold1;
	    cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 1]);
	    cc1[(ki + j * cc1_dim2) * cc1_dim1 + 2] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 1]);
	    cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1] = chold2;
/* L119: */
	}
/* L120: */
    }
    return 0;
L146:
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	ch1[(ki + ch1_dim2) * ch1_dim1 + 1] = sn * cc1[(ki + cc1_dim2) *
		cc1_dim1 + 1];
	ch1[(ki + ch1_dim2) * ch1_dim1 + 2] = sn * cc1[(ki + cc1_dim2) *
		cc1_dim1 + 2];
/* L147: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 1] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 1] - cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 2]);
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 2] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 1]);
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 1] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 1] + cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 2]);
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 2] = sn * (cc1[(ki + j *
		    cc1_dim2) * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) *
		    cc1_dim1 + 1]);
/* L144: */
	}
/* L145: */
    }
    return 0;
L136:
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	ch1[(ki + ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 1];
	ch1[(ki + ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + cc1_dim2) * cc1_dim1
		+ 2];
/* L137: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 1] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 2]
		    ;
	    ch1[(ki + j * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		    * cc1_dim1 + 2] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 + 1]
		    ;
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 1] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 1] + cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    2];
	    ch1[(ki + jc * ch1_dim2) * ch1_dim1 + 2] = cc1[(ki + j * cc1_dim2)
		     * cc1_dim1 + 2] - cc1[(ki + jc * cc1_dim2) * cc1_dim1 +
		    1];
/* L134: */
	}
/* L135: */
    }
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(k + (i__ * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = ch[(k + (
		    i__ + ch_dim3) * ch_dim2) * ch_dim1 + 1];
	    cc[(k + (i__ * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 2] = ch[(k + (
		    i__ + ch_dim3) * ch_dim2) * ch_dim1 + 2];
/* L130: */
	}
/* L131: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(k + (j + cc_dim3) * cc_dim2) * cc_dim1 + 1] = ch[(k + (j *
		    ch_dim3 + 1) * ch_dim2) * ch_dim1 + 1];
	    cc[(k + (j + cc_dim3) * cc_dim2) * cc_dim1 + 2] = ch[(k + (j *
		    ch_dim3 + 1) * ch_dim2) * ch_dim1 + 2];
/* L122: */
	}
/* L123: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *ido;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		cc[(k + (j + i__ * cc_dim3) * cc_dim2) * cc_dim1 + 1] = wa[
			i__ + (j - 1 + wa_dim2) * wa_dim1] * ch[(k + (i__ + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 1] + wa[i__ + (j -
			1 + (wa_dim2 << 1)) * wa_dim1] * ch[(k + (i__ + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 2];
		cc[(k + (j + i__ * cc_dim3) * cc_dim2) * cc_dim1 + 2] = wa[
			i__ + (j - 1 + wa_dim2) * wa_dim1] * ch[(k + (i__ + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 2] - wa[i__ + (j -
			1 + (wa_dim2 << 1)) * wa_dim1] * ch[(k + (i__ + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L124: */
	    }
/* L125: */
	}
/* L126: */
    }
    return 0;
} /* c1fgkf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1fm1b_d(int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac)
{
    /* System generated locals */
    int i__1, i__2;
    int c__2 = 2;

    /* Local variables */
     int k1, l1, l2, na, nf, ip, iw, lid, ido, nbr, inc2;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    --fac;
    --wa;
    --ch;
    --c__;

    /* Function Body */
    inc2 = *inc + *inc;
    nf = *fnf;
    na = 0;
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1];
	l2 = ip * l1;
	ido = *n / l2;
	lid = l1 * ido;
/* Computing MIN */
	i__2 = ip - 2;
	nbr = na + 1 + (min(i__2,4) << 1);
	switch (nbr) {
	    case 1:  goto L52;
	    case 2:  goto L62;
	    case 3:  goto L53;
	    case 4:  goto L63;
	    case 5:  goto L54;
	    case 6:  goto L64;
	    case 7:  goto L55;
	    case 8:  goto L65;
	    case 9:  goto L56;
	    case 10:  goto L66;
	}
L52:
	c1f2kb_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L62:
	c1f2kb_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L53:
	c1f3kb_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L63:
	c1f3kb_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L54:
	c1f4kb_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L64:
	c1f4kb_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L55:
	c1f5kb_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L65:
	c1f5kb_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L56:
	c1fgkb_d(&ido, &ip, &l1, &lid, &na, (double*)&c__[1], (double*)&c__[1], &
		inc2, &ch[1], &ch[1], &c__2, &wa[iw]);
	goto L120;
L66:
	c1fgkb_d(&ido, &ip, &l1, &lid, &na, &ch[1], &ch[1], &c__2, (double*)&c__[
		1], (double*)&c__[1], &inc2, &wa[iw]);
L120:
	l1 = l2;
	iw += (ip - 1) * (ido + ido);
	if (ip <= 5) {
	    na = 1 - na;
	}
/* L125: */
    }
    return 0;
} /* c1fm1b_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int c1fm1f_d(int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac)
{
    /* System generated locals */
    int i__1, i__2;
    int c__2 = 2;

    /* Local variables */
     int k1, l1, l2, na, nf, ip, iw, lid, ido, nbr, inc2;

/* FFTPACK 5.1 auxiliary routine */

    /* Parameter adjustments */
    --fac;
    --wa;
    --ch;
    --c__;

    /* Function Body */
    inc2 = *inc + *inc;
    nf = *fnf;
    na = 0;
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1];
	l2 = ip * l1;
	ido = *n / l2;
	lid = l1 * ido;
/* Computing MIN */
	i__2 = ip - 2;
	nbr = na + 1 + (min(i__2,4) << 1);
	switch (nbr) {
	    case 1:  goto L52;
	    case 2:  goto L62;
	    case 3:  goto L53;
	    case 4:  goto L63;
	    case 5:  goto L54;
	    case 6:  goto L64;
	    case 7:  goto L55;
	    case 8:  goto L65;
	    case 9:  goto L56;
	    case 10:  goto L66;
	}
L52:
	c1f2kf_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L62:
	c1f2kf_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L53:
	c1f3kf_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L63:
	c1f3kf_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L54:
	c1f4kf_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L64:
	c1f4kf_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L55:
	c1f5kf_d(&ido, &l1, &na, (double*)&c__[1], &inc2, &ch[1], &c__2, &wa[iw])
		;
	goto L120;
L65:
	c1f5kf_d(&ido, &l1, &na, &ch[1], &c__2, (double*)&c__[1], &inc2, &wa[iw])
		;
	goto L120;
L56:
	c1fgkf_d(&ido, &ip, &l1, &lid, &na, (double*)&c__[1], (double*)&c__[1], &
		inc2, &ch[1], &ch[1], &c__2, &wa[iw]);
	goto L120;
L66:
	c1fgkf_d(&ido, &ip, &l1, &lid, &na, &ch[1], &ch[1], &c__2, (double*)&c__[
		1], (double*)&c__[1], &inc2, &wa[iw]);
L120:
	l1 = l2;
	iw += (ip - 1) * (ido + ido);
	if (ip <= 5) {
	    na = 1 - na;
	}
/* L125: */
    }
    return 0;
} /* c1fm1f_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft1b_d(int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --c__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenc < *inc * (*n - 1) + 1) {
	*ier = 1;
	////xerfft_d("CFFT1B ", &c__4, (int)7);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	////xerfft_d("CFFT1B ", &c__6, (int)7);
    } else if (*lenwrk < *n << 1) {
	*ier = 3;
	////xerfft_d("CFFT1B ", &c__8, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    c1fm1b_d(n, inc, &c__[1], &work[1], &wsave[1], &wsave[iw1], &wsave[iw1 + 1]
	    );
    return 0;
} /* cfft1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft1f_d(int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --c__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenc < *inc * (*n - 1) + 1) {
	*ier = 1;
	////xerfft_d("CFFT1F ", &c__4, (int)7);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	////xerfft_d("CFFT1F ", &c__6, (int)7);
    } else if (*lenwrk < *n << 1) {
	*ier = 3;
	////xerfft_d("CFFT1F ", &c__8, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    c1fm1f_d(n, inc, &c__[1], &work[1], &wsave[1], &wsave[iw1], &wsave[iw1 + 1]
	    );
    return 0;
} /* cfft1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft1i_d(int *n, double *wsave, int *lensav, int *ier)
{

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	////xerfft_d("CFFTMI ", &c__3, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    mcfti1_d(n, &wsave[1], &wsave[iw1], &wsave[iw1 + 1]);

    return 0;
} /* cfft1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft2b_d(int *ldim, int *l, int *m, fft_complexd_t *c__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int c_dim1, c_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Local variables */
     int iw, ier1;

/* Initialize error return */

    /* Parameter adjustments */
    c_dim1 = *ldim;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*l > *ldim) {
	*ier = 5;
	////xerfft_d("CFFT2B", &c_n2, (int)6);
	goto L100;
    } else if (*lensav < (*l << 1) + (int) (log((double) (*l)) / log(2.0))
	    + (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 8) {
	*ier = 2;
	////xerfft_d("CFFT2B", &c__6, (int)6);
	goto L100;
    } else if (*lenwrk < (*l << 1) * *m) {
	*ier = 3;
	////xerfft_d("CFFT2B", &c__8, (int)6);
	goto L100;
    }

/* Transform X lines of C array */
    iw = (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 3;
    i__1 = *l - 1 + *ldim * (*m - 1) + 1;
    i__2 = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    i__3 = (*l << 1) * *m;
    cfftmb_d(l, &c__1, m, ldim, &c__[c_offset], &i__1, &wsave[iw], &i__2, &
	    work[1], &i__3, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	////xerfft_d("CFFT2B", &c_n5, (int)6);
	goto L100;
    }

/* Transform Y lines of C array */
    iw = 1;
    i__1 = (*m - 1) * *ldim + *l;
    i__2 = (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 4;
    i__3 = (*m << 1) * *l;
    cfftmb_d(m, ldim, l, &c__1, &c__[c_offset], &i__1, &wsave[iw], &i__2, &
	    work[1], &i__3, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	////xerfft_d("CFFT2B", &c_n5, (int)6);
    }

L100:
    return 0;
} /* cfft2b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft2f_d(int *ldim, int *l, int *m, fft_complexd_t *c__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int c_dim1, c_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int iw, ier1;

/* Initialize error return */

    /* Parameter adjustments */
    c_dim1 = *ldim;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*l > *ldim) {
	*ier = 5;
	//xerfft_d("CFFT2F", &c_n2, (int)6);
	goto L100;
    } else if (*lensav < (*l << 1) + (int) (log((double) (*l)) / log(2.0))
	    + (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 8) {
	*ier = 2;
	//xerfft_d("CFFT2F", &c__6, (int)6);
	goto L100;
    } else if (*lenwrk < (*l << 1) * *m) {
	*ier = 3;
	//xerfft_d("CFFT2F", &c__8, (int)6);
	goto L100;
    }

/* Transform X lines of C array */
    iw = (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 3;
    i__1 = *l - 1 + *ldim * (*m - 1) + 1;
    i__2 = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    i__3 = (*l << 1) * *m;
    cfftmf_d(l, &c__1, m, ldim, &c__[c_offset], &i__1, &wsave[iw], &i__2, &
	    work[1], &i__3, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("CFFT2F", &c_n5, (int)6);
	goto L100;
    }

/* Transform Y lines of C array */
    iw = 1;
    i__1 = (*m - 1) * *ldim + *l;
    i__2 = (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 4;
    i__3 = (*m << 1) * *l;
    cfftmf_d(m, ldim, l, &c__1, &c__[c_offset], &i__1, &wsave[iw], &i__2, &
	    work[1], &i__3, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("CFFT2F", &c_n5, (int)6);
    }

L100:
    return 0;
} /* cfft2f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfft2i_d(int *l, int *m, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int ier1;

/* Initialize error return */

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + (*m <<
	     1) + (int) (log((double) (*m)) / log(2.0)) + 8) {
	*ier = 2;
	//xerfft_d("CFFT2I", &c__4, (int)6);
	goto L100;
    }

    i__1 = (*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 4;
    cfftmi_d(l, &wsave[1], &i__1, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("CFFT2I", &c_n5, (int)6);
	goto L100;
    }
    i__1 = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    cfftmi_d(m, &wsave[(*l << 1) + (int) (log((double) (*l)) / log(2.0)) + 3]
	    , &i__1, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("CFFT2I", &c_n5, (int)6);
    }

L100:
    return 0;
} /* cfft2i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfftmb_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --c__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenc < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("CFFTMB ", &c__6, (int)7);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("CFFTMB ", &c__8, (int)7);
    } else if (*lenwrk < (*lot << 1) * *n) {
	*ier = 3;
	//xerfft_d("CFFTMB ", &c__10, (int)7);
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("CFFTMB ", &c_n1, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    cmfm1b_d(lot, jump, n, inc, &c__[1], &work[1], &wsave[1], &wsave[iw1], &
	    wsave[iw1 + 1]);
    return 0;
} /* cfftmb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfftmf_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, int *lenc, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --c__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenc < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("CFFTMF ", &c__6, (int)7);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("CFFTMF ", &c__8, (int)7);
    } else if (*lenwrk < (*lot << 1) * *n) {
	*ier = 3;
	//xerfft_d("CFFTMF ", &c__10, (int)7);
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("CFFTMF ", &c_n1, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    cmfm1f_d(lot, jump, n, inc, &c__[1], &work[1], &wsave[1], &wsave[iw1], &
	    wsave[iw1 + 1]);
    return 0;
} /* cfftmf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cfftmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int iw1;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("CFFTMI ", &c__3, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    iw1 = *n + *n + 1;
    mcfti1_d(n, &wsave[1], &wsave[iw1], &wsave[iw1 + 1]);
    return 0;
} /* cfftmi_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf2kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2, m1d;
     double ti2;
     int m2s;
     double tr2, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 1);
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    chold1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) +
		    1] + cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    chold1;
	    chold2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) +
		    2] + cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    chold2;
/* L101: */
	}
    }
    return 0;
L102:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 1] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + cc[(m1 + (
		    k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1];
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] - cc[(m1
		    + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) +
		    1];
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 2] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + cc[(m1 + (
		    k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2];
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] - cc[(m1
		    + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) +
		    2];
/* L103: */
	}
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ch[(m2 + (k + ((i__ << 1) + 1) * ch_dim3) * ch_dim2 << 1) + 1]
			 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2
			<< 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] - cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + ((i__ << 1) + 1) * ch_dim3) * ch_dim2 << 1) + 2]
			 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2
			<< 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] - cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ch[(m2 + (k + ((i__ << 1) + 2) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + (wa_dim1 << 1)] * ti2 + wa[i__ + wa_dim1 *
			 3] * tr2;
		ch[(m2 + (k + ((i__ << 1) + 2) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + (wa_dim1 << 1)] * tr2 - wa[i__ + wa_dim1 *
			 3] * ti2;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf2kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf2kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double sn;
     int m1d;
     double ti2;
     int m2s;
     double tr2, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 1);
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 << 1);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    chold1 = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 <<
		     1) + 1] + cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		     cc_dim2 << 1) + 1]);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2
		    << 1) + 1] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3)
		     * cc_dim2 << 1) + 1]);
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    chold1;
	    chold2 = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 <<
		     1) + 2] + cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		     cc_dim2 << 1) + 2]);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2
		    << 1) + 2] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3)
		     * cc_dim2 << 1) + 2]);
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    chold2;
/* L101: */
	}
    }
    return 0;
L106:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 1] = sn * (cc[(m1 + (
		    k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + cc[(
		    m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1]);
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = sn * (cc[(m1
		    + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] - cc[
		    (m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1)
		     + 1]);
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 2] = sn * (cc[(m1 + (
		    k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + cc[(
		    m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2]);
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = sn * (cc[(m1
		    + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] - cc[
		    (m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1)
		     + 2]);
/* L107: */
	}
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 1] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + cc[(m1 + (
		    k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1];
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] - cc[(m1
		    + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) +
		    1];
	    ch[(m2 + (k + ch_dim3 * 3) * ch_dim2 << 1) + 2] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + cc[(m1 + (
		    k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2];
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] - cc[(m1
		    + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) +
		    2];
/* L103: */
	}
    }
    i__3 = *ido;
    for (i__ = 2; i__ <= i__3; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		ch[(m2 + (k + ((i__ << 1) + 1) * ch_dim3) * ch_dim2 << 1) + 1]
			 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2
			<< 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] - cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + ((i__ << 1) + 1) * ch_dim3) * ch_dim2 << 1) + 2]
			 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2
			<< 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] - cc[(m1 + (k + (i__ + (cc_dim4 << 1)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ch[(m2 + (k + ((i__ << 1) + 2) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + (wa_dim1 << 1)] * ti2 - wa[i__ + wa_dim1 *
			 3] * tr2;
		ch[(m2 + (k + ((i__ << 1) + 2) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + (wa_dim1 << 1)] * tr2 + wa[i__ + wa_dim1 *
			 3] * ti2;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf2kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf3kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* Initialized data */

     double taur = -.5;
     double taui = .866025403784439;

    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double ci2, ci3, di2, di3;
     int m1d;
     double cr2, cr3, dr2, dr3, ti2;
     int m2s;
     double tr2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 3;
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + (ch_dim3 << 2)));
    ch -= ch_offset;

    /* Function Body */

    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + taur * tr2;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] +=
		    tr2;
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + taur * ti2;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] +=
		    ti2;
	    cr3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 1]);
	    ci3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 2]);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = cr2 - ci3;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    cr2 + ci3;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = ci2 + cr3;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    ci2 - cr3;
/* L101: */
	}
    }
    return 0;
L102:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + taur * tr2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + tr2;
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + taur * ti2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + ti2;
	    cr3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 1]);
	    ci3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 2]);
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = cr2 - ci3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = cr2 + ci3;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = ci2 + cr3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = ci2 - cr3;
/* L103: */
	}
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		tr2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 3)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		cr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + taur * tr2;
		ch[(m2 + (k + (i__ * 3 + 1) * ch_dim3) * ch_dim2 << 1) + 1] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 1] + tr2;
		ti2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 3)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ci2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + taur * ti2;
		ch[(m2 + (k + (i__ * 3 + 1) * ch_dim3) * ch_dim2 << 1) + 2] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 2] + ti2;
		cr3 = taui * (cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3)
			* cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + cc_dim4 *
			3) * cc_dim3) * cc_dim2 << 1) + 1]);
		ci3 = taui * (cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3)
			* cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + cc_dim4 *
			3) * cc_dim3) * cc_dim2 << 1) + 2]);
		dr2 = cr2 - ci3;
		dr3 = cr2 + ci3;
		di2 = ci2 + cr3;
		di3 = ci2 - cr3;
		ch[(m2 + (k + (i__ * 3 + 2) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 3] * di2 + wa[i__ + wa_dim1 * 5] *
			dr2;
		ch[(m2 + (k + (i__ * 3 + 2) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 3] * dr2 - wa[i__ + wa_dim1 * 5] *
			di2;
		ch[(m2 + (k + (i__ * 3 + 3) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + (wa_dim1 << 2)] * di3 + wa[i__ + wa_dim1 * 6]
			 * dr3;
		ch[(m2 + (k + (i__ * 3 + 3) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + (wa_dim1 << 2)] * dr3 - wa[i__ + wa_dim1 * 6]
			 * di3;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf3kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf3kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* Initialized data */

     double taur = -.5;
     double taui = -.866025403784439;

    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double sn, ci2, ci3, di2, di3;
     int m1d;
     double cr2, cr3, dr2, dr3, ti2;
     int m2s;
     double tr2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 3;
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + (ch_dim3 << 2)));
    ch -= ch_offset;

    /* Function Body */

    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 * 3);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + taur * tr2;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] = sn *
		     (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + tr2);
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + taur * ti2;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] = sn *
		     (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + ti2);
	    cr3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 1]);
	    ci3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 2]);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (cr2 - ci3);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    sn * (cr2 + ci3);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (ci2 + cr3);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    sn * (ci2 - cr3);
/* L101: */
	}
    }
    return 0;
L106:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + taur * tr2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = sn * (cc[(m1
		    + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] +
		    tr2);
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + taur * ti2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = sn * (cc[(m1
		    + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] +
		    ti2);
	    cr3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 1]);
	    ci3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 2]);
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = sn * (cr2 - ci3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = sn * (cr2 + ci3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = sn * (ci2 + cr3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = sn * (ci2 - cr3)
		    ;
/* L107: */
	}
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + taur * tr2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 1] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + tr2;
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + taur * ti2;
	    ch[(m2 + (k + (ch_dim3 << 2)) * ch_dim2 << 1) + 2] = cc[(m1 + (k
		    + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + ti2;
	    cr3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 1]);
	    ci3 = taui * (cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2] - cc[(m1 + (k + (cc_dim4 * 3 + 1) *
		    cc_dim3) * cc_dim2 << 1) + 2]);
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = cr2 - ci3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = cr2 + ci3;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = ci2 + cr3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = ci2 - cr3;
/* L103: */
	}
    }
    i__3 = *ido;
    for (i__ = 2; i__ <= i__3; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		tr2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 3)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		cr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + taur * tr2;
		ch[(m2 + (k + (i__ * 3 + 1) * ch_dim3) * ch_dim2 << 1) + 1] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 1] + tr2;
		ti2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 3)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ci2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + taur * ti2;
		ch[(m2 + (k + (i__ * 3 + 1) * ch_dim3) * ch_dim2 << 1) + 2] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 2] + ti2;
		cr3 = taui * (cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3)
			* cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + cc_dim4 *
			3) * cc_dim3) * cc_dim2 << 1) + 1]);
		ci3 = taui * (cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3)
			* cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + cc_dim4 *
			3) * cc_dim3) * cc_dim2 << 1) + 2]);
		dr2 = cr2 - ci3;
		dr3 = cr2 + ci3;
		di2 = ci2 + cr3;
		di3 = ci2 - cr3;
		ch[(m2 + (k + (i__ * 3 + 2) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 3] * di2 - wa[i__ + wa_dim1 * 5] *
			dr2;
		ch[(m2 + (k + (i__ * 3 + 2) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 3] * dr2 + wa[i__ + wa_dim1 * 5] *
			di2;
		ch[(m2 + (k + (i__ * 3 + 3) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + (wa_dim1 << 2)] * di3 - wa[i__ + wa_dim1 * 6]
			 * dr3;
		ch[(m2 + (k + (i__ * 3 + 3) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + (wa_dim1 << 2)] * dr3 + wa[i__ + wa_dim1 * 6]
			 * di3;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf3kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf4kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double ci2, ci3, ci4;
     int m1d;
     double cr3, cr2, cr4, ti1, ti2, ti3, ti4;
     int m2s;
     double tr1, tr2, tr3, tr4;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 2);
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 5));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    ti1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    ti2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    tr4 = cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    tr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    ti4 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] = tr2
		    + tr3;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    tr2 - tr3;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] = ti2
		    + ti3;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    ti2 - ti3;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = tr1 + tr4;
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = tr1 - tr4;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = ti1 + ti4;
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = ti1 - ti4;
/* L101: */
	}
    }
    return 0;
L102:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ti1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    ti2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    tr4 = cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    tr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    ti4 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = tr2 + tr3;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = tr2 - tr3;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = ti2 + ti3;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = ti2 - ti3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = tr1 + tr4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = tr1 - tr4;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = ti1 + ti4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = ti1 - ti4;
/* L103: */
	}
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ti1 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] - cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 2];
		ti3 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 2];
		tr4 = cc[(m1 + (k + (i__ + (cc_dim4 << 2)) * cc_dim3) *
			cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + (cc_dim4 <<
			1)) * cc_dim3) * cc_dim2 << 1) + 2];
		tr1 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] - cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 1];
		ti4 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 1];
		tr3 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + ((i__ << 2) + 1) * ch_dim3) * ch_dim2 << 1) + 1]
			 = tr2 + tr3;
		cr3 = tr2 - tr3;
		ch[(m2 + (k + ((i__ << 2) + 1) * ch_dim3) * ch_dim2 << 1) + 2]
			 = ti2 + ti3;
		ci3 = ti2 - ti3;
		cr2 = tr1 + tr4;
		cr4 = tr1 - tr4;
		ci2 = ti1 + ti4;
		ci4 = ti1 - ti4;
		ch[(m2 + (k + ((i__ << 2) + 2) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + (wa_dim1 << 2)] * cr2 - wa[i__ + wa_dim1 *
			 7] * ci2;
		ch[(m2 + (k + ((i__ << 2) + 2) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + (wa_dim1 << 2)] * ci2 + wa[i__ + wa_dim1 *
			 7] * cr2;
		ch[(m2 + (k + ((i__ << 2) + 3) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + wa_dim1 * 5] * cr3 - wa[i__ + (wa_dim1 <<
			3)] * ci3;
		ch[(m2 + (k + ((i__ << 2) + 3) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + wa_dim1 * 5] * ci3 + wa[i__ + (wa_dim1 <<
			3)] * cr3;
		ch[(m2 + (k + ((i__ << 2) + 4) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + wa_dim1 * 6] * cr4 - wa[i__ + wa_dim1 * 9]
			 * ci4;
		ch[(m2 + (k + ((i__ << 2) + 4) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + wa_dim1 * 6] * ci4 + wa[i__ + wa_dim1 * 9]
			 * cr4;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf4kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf4kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double sn, ci2, ci3, ci4;
     int m1d;
     double cr3, cr2, cr4, ti1, ti2, ti3, ti4;
     int m2s;
     double tr1, tr2, tr3, tr4;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + (wa_dim1 << 2);
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 5));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 << 2);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    ti1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    ti2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    tr4 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    tr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    ti4 = cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] = sn *
		     (tr2 + tr3);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    sn * (tr2 - tr3);
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] = sn *
		     (ti2 + ti3);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    sn * (ti2 - ti3);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (tr1 + tr4);
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (tr1 - tr4);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (ti1 + ti4);
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (ti1 - ti4);
/* L101: */
	}
    }
    return 0;
L106:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ti1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    ti2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    tr4 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    tr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    ti4 = cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = sn * (tr2 + tr3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = sn * (tr2 - tr3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = sn * (ti2 + ti3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = sn * (ti2 - ti3)
		    ;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = sn * (tr1 + tr4)
		    ;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = sn * (tr1 -
		    tr4);
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = sn * (ti1 + ti4)
		    ;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = sn * (ti1 -
		    ti4);
/* L107: */
	}
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ti1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    ti2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2];
	    tr4 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    - cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    tr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1];
	    ti4 = cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 1] = tr2 + tr3;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = tr2 - tr3;
	    ch[(m2 + (k + ch_dim3 * 5) * ch_dim2 << 1) + 2] = ti2 + ti3;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = ti2 - ti3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = tr1 + tr4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = tr1 - tr4;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = ti1 + ti4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = ti1 - ti4;
/* L103: */
	}
    }
    i__3 = *ido;
    for (i__ = 2; i__ <= i__3; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		ti1 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] - cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 2];
		ti3 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 2];
		tr4 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 2];
		tr1 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] - cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) *
			 cc_dim2 << 1) + 1];
		ti4 = cc[(m1 + (k + (i__ + (cc_dim4 << 2)) * cc_dim3) *
			cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + (cc_dim4 <<
			1)) * cc_dim3) * cc_dim2 << 1) + 1];
		tr3 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 <<
			2)) * cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + ((i__ << 2) + 1) * ch_dim3) * ch_dim2 << 1) + 1]
			 = tr2 + tr3;
		cr3 = tr2 - tr3;
		ch[(m2 + (k + ((i__ << 2) + 1) * ch_dim3) * ch_dim2 << 1) + 2]
			 = ti2 + ti3;
		ci3 = ti2 - ti3;
		cr2 = tr1 + tr4;
		cr4 = tr1 - tr4;
		ci2 = ti1 + ti4;
		ci4 = ti1 - ti4;
		ch[(m2 + (k + ((i__ << 2) + 2) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + (wa_dim1 << 2)] * cr2 + wa[i__ + wa_dim1 *
			 7] * ci2;
		ch[(m2 + (k + ((i__ << 2) + 2) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + (wa_dim1 << 2)] * ci2 - wa[i__ + wa_dim1 *
			 7] * cr2;
		ch[(m2 + (k + ((i__ << 2) + 3) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + wa_dim1 * 5] * cr3 + wa[i__ + (wa_dim1 <<
			3)] * ci3;
		ch[(m2 + (k + ((i__ << 2) + 3) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + wa_dim1 * 5] * ci3 - wa[i__ + (wa_dim1 <<
			3)] * cr3;
		ch[(m2 + (k + ((i__ << 2) + 4) * ch_dim3) * ch_dim2 << 1) + 1]
			 = wa[i__ + wa_dim1 * 6] * cr4 + wa[i__ + wa_dim1 * 9]
			 * ci4;
		ch[(m2 + (k + ((i__ << 2) + 4) * ch_dim3) * ch_dim2 << 1) + 2]
			 = wa[i__ + wa_dim1 * 6] * ci4 - wa[i__ + wa_dim1 * 9]
			 * cr4;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf4kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmf5kb_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* Initialized data */

     double tr11 = .3090169943749474;
     double ti11 = .9510565162951536;
     double tr12 = -.8090169943749474;
     double ti12 = .5877852522924731;

    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double ci2, ci3, ci4, ci5;
     int m1d;
     double di3, di4, di5, di2, cr2, cr3, cr5, cr4, ti2, ti3, ti4;
     int m2s;
     double ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 5;
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 6));
    ch -= ch_offset;

    /* Function Body */

/* FFTPACK 5.0 auxiliary routine */

    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1 || *na == 1) {
	goto L102;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    ti5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    chold1 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) +
		    1] + tr2 + tr3;
	    chold2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) +
		    2] + ti2 + ti3;
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr11 * tr2 + tr12 * tr3;
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr11 * ti2 + tr12 * ti3;
	    cr3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr12 * tr2 + tr11 * tr3;
	    ci3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr12 * ti2 + tr11 * ti3;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    chold1;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    chold2;
	    cr5 = ti11 * tr5 + ti12 * tr4;
	    ci5 = ti11 * ti5 + ti12 * ti4;
	    cr4 = ti12 * tr5 - ti11 * tr4;
	    ci4 = ti12 * ti5 - ti11 * ti4;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = cr2 - ci5;
	    cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    cr2 + ci5;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = ci2 + cr5;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    ci3 + cr4;
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    cr3 - ci4;
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = cr3 + ci4;
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = ci3 - cr4;
	    cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    ci2 - cr5;
/* L101: */
	}
    }
    return 0;
L102:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ti5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + tr2 + tr3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + ti2 + ti3;
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr11 * tr2 + tr12 * tr3;
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr11 * ti2 + tr12 * ti3;
	    cr3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr12 * tr2 + tr11 * tr3;
	    ci3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr12 * ti2 + tr11 * ti3;
	    cr5 = ti11 * tr5 + ti12 * tr4;
	    ci5 = ti11 * ti5 + ti12 * ti4;
	    cr4 = ti12 * tr5 - ti11 * tr4;
	    ci4 = ti12 * ti5 - ti11 * ti4;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = cr2 - ci5;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 1] = cr2 + ci5;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = ci2 + cr5;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = ci3 + cr4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = cr3 - ci4;
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 1] = cr3 + ci4;
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 2] = ci3 - cr4;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 2] = ci2 - cr5;
/* L103: */
	}
    }
    if (*ido == 1) {
	return 0;
    }
    i__1 = *ido;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ti5 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ti4 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 2] - cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ti3 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		tr5 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		tr4 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 1] - cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		tr3 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + (i__ * 5 + 1) * ch_dim3) * ch_dim2 << 1) + 1] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 1] + tr2 + tr3;
		ch[(m2 + (k + (i__ * 5 + 1) * ch_dim3) * ch_dim2 << 1) + 2] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 2] + ti2 + ti3;
		cr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + tr11 * tr2 + tr12 * tr3;
		ci2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + tr11 * ti2 + tr12 * ti3;
		cr3 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + tr12 * tr2 + tr11 * tr3;
		ci3 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + tr12 * ti2 + tr11 * ti3;
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
		ch[(m2 + (k + (i__ * 5 + 2) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 5] * dr2 - wa[i__ + wa_dim1 * 9] *
			di2;
		ch[(m2 + (k + (i__ * 5 + 2) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 5] * di2 + wa[i__ + wa_dim1 * 9] *
			dr2;
		ch[(m2 + (k + (i__ * 5 + 3) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 6] * dr3 - wa[i__ + wa_dim1 * 10] *
			 di3;
		ch[(m2 + (k + (i__ * 5 + 3) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 6] * di3 + wa[i__ + wa_dim1 * 10] *
			 dr3;
		ch[(m2 + (k + (i__ * 5 + 4) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 7] * dr4 - wa[i__ + wa_dim1 * 11] *
			 di4;
		ch[(m2 + (k + (i__ * 5 + 4) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 7] * di4 + wa[i__ + wa_dim1 * 11] *
			 dr4;
		ch[(m2 + (k + (i__ * 5 + 5) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + (wa_dim1 << 3)] * dr5 - wa[i__ + wa_dim1 *
			12] * di5;
		ch[(m2 + (k + (i__ * 5 + 5) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + (wa_dim1 << 3)] * di5 + wa[i__ + wa_dim1 *
			12] * dr5;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf5kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/* Subroutine */ int cmf5kf_d(int *lot, int *ido, int *l1, int *na, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa)
{
    /* Initialized data */

     double tr11 = .3090169943749474;
     double ti11 = -.9510565162951536;
     double tr12 = -.8090169943749474;
     double ti12 = -.5877852522924731;

    /* System generated locals */
    int cc_dim2, cc_dim3, cc_dim4, cc_offset, ch_dim2, ch_dim3, ch_offset,
	     wa_dim1, wa_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2;
     double sn, ci2, ci3, ci4, ci5;
     int m1d;
     double di3, di4, di5, di2, cr2, cr3, cr5, cr4, ti2, ti3, ti4;
     int m2s;
     double ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5, chold1, chold2;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_offset = 1 + wa_dim1 * 5;
    wa -= wa_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ido;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * 6));
    ch -= ch_offset;

    /* Function Body */

/* FFTPACK 5.0 auxiliary routine */

    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    if (*ido > 1) {
	goto L102;
    }
    sn = 1.0 / (double) (*l1 * 5);
    if (*na == 1) {
	goto L106;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    ti5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    chold1 = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 <<
		     1) + 1] + tr2 + tr3);
	    chold2 = sn * (cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 <<
		     1) + 2] + ti2 + ti3);
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr11 * tr2 + tr12 * tr3;
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr11 * ti2 + tr12 * ti3;
	    cr3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr12 * tr2 + tr11 * tr3;
	    ci3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr12 * ti2 + tr11 * ti3;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    chold1;
	    cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    chold2;
	    cr5 = ti11 * tr5 + ti12 * tr4;
	    ci5 = ti11 * ti5 + ti12 * ti4;
	    cr4 = ti12 * tr5 - ti11 * tr4;
	    ci4 = ti12 * ti5 - ti11 * ti4;
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (cr2 - ci5);
	    cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    sn * (cr2 + ci5);
	    cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (ci2 + cr5);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    sn * (ci3 + cr4);
	    cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1) + 1] =
		    sn * (cr3 - ci4);
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		     = sn * (cr3 + ci4);
	    cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		     = sn * (ci3 - cr4);
	    cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) * cc_dim2 << 1) + 2] =
		    sn * (ci2 - cr5);
/* L101: */
	}
    }
    return 0;
L106:
    i__3 = *l1;
    for (k = 1; k <= i__3; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__1 = *im1;
	for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
	    m2 += *im2;
	    ti5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = sn * (cc[(m1 + (
		    k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + tr2 +
		    tr3);
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = sn * (cc[(m1 + (
		    k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + ti2 +
		    ti3);
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr11 * tr2 + tr12 * tr3;
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr11 * ti2 + tr12 * ti3;
	    cr3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr12 * tr2 + tr11 * tr3;
	    ci3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr12 * ti2 + tr11 * ti3;
	    cr5 = ti11 * tr5 + ti12 * tr4;
	    ci5 = ti11 * ti5 + ti12 * ti4;
	    cr4 = ti12 * tr5 - ti11 * tr4;
	    ci4 = ti12 * ti5 - ti11 * ti4;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = sn * (cr2 - ci5)
		    ;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 1] = sn * (cr2 +
		    ci5);
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = sn * (ci2 + cr5)
		    ;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = sn * (ci3 +
		    cr4);
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = sn * (cr3 -
		    ci4);
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 1] = sn * (cr3 + ci4)
		    ;
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 2] = sn * (ci3 - cr4)
		    ;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 2] = sn * (ci2 -
		    cr5);
/* L107: */
	}
    }
    return 0;
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ti5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 2] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    ti3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 2] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 2];
	    tr5 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] - cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr2 = cc[(m1 + (k + ((cc_dim4 << 1) + 1) * cc_dim3) * cc_dim2 <<
		    1) + 1] + cc[(m1 + (k + (cc_dim4 * 5 + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr4 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] - cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    tr3 = cc[(m1 + (k + (cc_dim4 * 3 + 1) * cc_dim3) * cc_dim2 << 1)
		    + 1] + cc[(m1 + (k + ((cc_dim4 << 2) + 1) * cc_dim3) *
		    cc_dim2 << 1) + 1];
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 1] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1] + tr2 + tr3;
	    ch[(m2 + (k + ch_dim3 * 6) * ch_dim2 << 1) + 2] = cc[(m1 + (k + (
		    cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2] + ti2 + ti3;
	    cr2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr11 * tr2 + tr12 * tr3;
	    ci2 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr11 * ti2 + tr12 * ti3;
	    cr3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 1]
		    + tr12 * tr2 + tr11 * tr3;
	    ci3 = cc[(m1 + (k + (cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1) + 2]
		    + tr12 * ti2 + tr11 * ti3;
	    cr5 = ti11 * tr5 + ti12 * tr4;
	    ci5 = ti11 * ti5 + ti12 * ti4;
	    cr4 = ti12 * tr5 - ti11 * tr4;
	    ci4 = ti12 * ti5 - ti11 * ti4;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 1] = cr2 - ci5;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 1] = cr2 + ci5;
	    ch[(m2 + (k + ch_dim3 * 7) * ch_dim2 << 1) + 2] = ci2 + cr5;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 2] = ci3 + cr4;
	    ch[(m2 + (k + (ch_dim3 << 3)) * ch_dim2 << 1) + 1] = cr3 - ci4;
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 1] = cr3 + ci4;
	    ch[(m2 + (k + ch_dim3 * 9) * ch_dim2 << 1) + 2] = ci3 - cr4;
	    ch[(m2 + (k + ch_dim3 * 10) * ch_dim2 << 1) + 2] = ci2 - cr5;
/* L103: */
	}
    }
    i__3 = *ido;
    for (i__ = 2; i__ <= i__3; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		ti5 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] - cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ti2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 2] + cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 2];
		ti4 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 2] - cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		ti3 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 2] + cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 2];
		tr5 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] - cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		tr2 = cc[(m1 + (k + (i__ + (cc_dim4 << 1)) * cc_dim3) *
			cc_dim2 << 1) + 1] + cc[(m1 + (k + (i__ + cc_dim4 * 5)
			 * cc_dim3) * cc_dim2 << 1) + 1];
		tr4 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 1] - cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		tr3 = cc[(m1 + (k + (i__ + cc_dim4 * 3) * cc_dim3) * cc_dim2
			<< 1) + 1] + cc[(m1 + (k + (i__ + (cc_dim4 << 2)) *
			cc_dim3) * cc_dim2 << 1) + 1];
		ch[(m2 + (k + (i__ * 5 + 1) * ch_dim3) * ch_dim2 << 1) + 1] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 1] + tr2 + tr3;
		ch[(m2 + (k + (i__ * 5 + 1) * ch_dim3) * ch_dim2 << 1) + 2] =
			cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 <<
			1) + 2] + ti2 + ti3;
		cr2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + tr11 * tr2 + tr12 * tr3;
		ci2 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + tr11 * ti2 + tr12 * ti3;
		cr3 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 1] + tr12 * tr2 + tr11 * tr3;
		ci3 = cc[(m1 + (k + (i__ + cc_dim4) * cc_dim3) * cc_dim2 << 1)
			 + 2] + tr12 * ti2 + tr11 * ti3;
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
		ch[(m2 + (k + (i__ * 5 + 2) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 5] * dr2 + wa[i__ + wa_dim1 * 9] *
			di2;
		ch[(m2 + (k + (i__ * 5 + 2) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 5] * di2 - wa[i__ + wa_dim1 * 9] *
			dr2;
		ch[(m2 + (k + (i__ * 5 + 3) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 6] * dr3 + wa[i__ + wa_dim1 * 10] *
			 di3;
		ch[(m2 + (k + (i__ * 5 + 3) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 6] * di3 - wa[i__ + wa_dim1 * 10] *
			 dr3;
		ch[(m2 + (k + (i__ * 5 + 4) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + wa_dim1 * 7] * dr4 + wa[i__ + wa_dim1 * 11] *
			 di4;
		ch[(m2 + (k + (i__ * 5 + 4) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + wa_dim1 * 7] * di4 - wa[i__ + wa_dim1 * 11] *
			 dr4;
		ch[(m2 + (k + (i__ * 5 + 5) * ch_dim3) * ch_dim2 << 1) + 1] =
			wa[i__ + (wa_dim1 << 3)] * dr5 + wa[i__ + wa_dim1 *
			12] * di5;
		ch[(m2 + (k + (i__ * 5 + 5) * ch_dim3) * ch_dim2 << 1) + 2] =
			wa[i__ + (wa_dim1 << 3)] * di5 - wa[i__ + wa_dim1 *
			12] * dr5;
/* L104: */
	    }
	}
/* L105: */
    }
    return 0;
} /* cmf5kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmfgkb_d(int *lot, int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *im1, int *in1, double *ch, double *ch1, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim2, ch_dim3, ch_dim4, ch_offset, cc_dim2, cc_dim3, cc_dim4,
	    cc_offset, cc1_dim2, cc1_dim3, cc1_offset, ch1_dim2, ch1_dim3,
	    ch1_offset, wa_dim1, wa_dim2, wa_offset, i__1, i__2, i__3, i__4,
	    i__5;

    /* Local variables */
     int i__, j, k, l, m1, m2, jc, lc, ki, m1d, m2s;
     double wai, war;
     int ipp2, idlj, ipph;
     double chold1, chold2;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_dim2 = *ip - 1;
    wa_offset = 1 + wa_dim1 * (1 + wa_dim2);
    wa -= wa_offset;
    cc1_dim2 = *in1;
    cc1_dim3 = *lid;
    cc1_offset = 1 + 2 * (1 + cc1_dim2 * (1 + cc1_dim3));
    cc1 -= cc1_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ip;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch1_dim2 = *in2;
    ch1_dim3 = *lid;
    ch1_offset = 1 + 2 * (1 + ch1_dim2 * (1 + ch1_dim3));
    ch1 -= ch1_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_dim4 = *ido;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * (1 + ch_dim4)));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 1];
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 2];
/* L110: */
	}
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
/* L112: */
	    }
	}
/* L111: */
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	i__4 = *lid;
	for (ki = 1; ki <= i__4; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__2) {
		m2 += *im2;
		cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 1] += ch1[(m2 + (
			ki + j * ch1_dim3) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 2] += ch1[(m2 + (
			ki + j * ch1_dim3) * ch1_dim2 << 1) + 2];
/* L117: */
	    }
	}
/* L118: */
    }
    i__3 = ipph;
    for (l = 2; l <= i__3; ++l) {
	lc = ipp2 - l;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 1] = ch1[(m2
			+ (ki + ch1_dim3) * ch1_dim2 << 1) + 1] + wa[(l - 1 +
			wa_dim2) * wa_dim1 + 1] * ch1[(m2 + (ki + (ch1_dim3 <<
			 1)) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 1] = wa[(l
			- 1 + (wa_dim2 << 1)) * wa_dim1 + 1] * ch1[(m2 + (ki
			+ *ip * ch1_dim3) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 2] = ch1[(m2
			+ (ki + ch1_dim3) * ch1_dim2 << 1) + 2] + wa[(l - 1 +
			wa_dim2) * wa_dim1 + 1] * ch1[(m2 + (ki + (ch1_dim3 <<
			 1)) * ch1_dim2 << 1) + 2];
		cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 2] = wa[(l
			- 1 + (wa_dim2 << 1)) * wa_dim1 + 1] * ch1[(m2 + (ki
			+ *ip * ch1_dim3) * ch1_dim2 << 1) + 2];
/* L113: */
	    }
	}
	i__4 = ipph;
	for (j = 3; j <= i__4; ++j) {
	    jc = ipp2 - j;
	    idlj = (l - 1) * (j - 1) % *ip;
	    war = wa[(idlj + wa_dim2) * wa_dim1 + 1];
	    wai = wa[(idlj + (wa_dim2 << 1)) * wa_dim1 + 1];
	    i__1 = *lid;
	    for (ki = 1; ki <= i__1; ++ki) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 1] +=
			    war * ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 <<
			    1) + 1];
		    cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 1] +=
			    wai * ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 <<
			     1) + 1];
		    cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 2] +=
			    war * ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 <<
			    1) + 2];
		    cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 2] +=
			    wai * ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 <<
			     1) + 2];
/* L114: */
		}
	    }
/* L115: */
	}
/* L116: */
    }
    if (*ido > 1 || *na == 1) {
	goto L136;
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	jc = ipp2 - j;
	i__4 = *lid;
	for (ki = 1; ki <= i__4; ++ki) {
	    i__5 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__2) {
		chold1 = cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1]
			- cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2]
			;
		chold2 = cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1]
			+ cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2]
			;
		cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] = chold1;
		cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] += cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1] = chold2;
/* L119: */
	    }
	}
/* L120: */
    }
    return 0;
L136:
    i__3 = *lid;
    for (ki = 1; ki <= i__3; ++ki) {
	m2 = m2s;
	i__2 = m1d;
	i__5 = *im1;
	for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
	    m2 += *im2;
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 1];
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 2];
/* L137: */
	}
    }
    i__5 = ipph;
    for (j = 2; j <= i__5; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] - cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] + cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
/* L134: */
	    }
	}
/* L135: */
    }
    if (*ido == 1) {
	return 0;
    }
    i__5 = *ido;
    for (i__ = 1; i__ <= i__5; ++i__) {
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__2) {
		m2 += *im2;
		cc[(m1 + (k + (i__ * cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
			+ 1] = ch[(m2 + (k + (i__ + ch_dim4) * ch_dim3) *
			ch_dim2 << 1) + 1];
		cc[(m1 + (k + (i__ * cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
			+ 2] = ch[(m2 + (k + (i__ + ch_dim4) * ch_dim3) *
			ch_dim2 << 1) + 2];
/* L130: */
	    }
	}
/* L131: */
    }
    i__5 = *ip;
    for (j = 2; j <= i__5; ++j) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		cc[(m1 + (k + (j + cc_dim4) * cc_dim3) * cc_dim2 << 1) + 1] =
			ch[(m2 + (k + (j * ch_dim4 + 1) * ch_dim3) * ch_dim2
			<< 1) + 1];
		cc[(m1 + (k + (j + cc_dim4) * cc_dim3) * cc_dim2 << 1) + 2] =
			ch[(m2 + (k + (j * ch_dim4 + 1) * ch_dim3) * ch_dim2
			<< 1) + 2];
/* L122: */
	    }
	}
/* L123: */
    }
    i__5 = *ip;
    for (j = 2; j <= i__5; ++j) {
	i__4 = *ido;
	for (i__ = 2; i__ <= i__4; ++i__) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		m2 = m2s;
		i__2 = m1d;
		i__1 = *im1;
		for (m1 = 1; i__1 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__1) {
		    m2 += *im2;
		    cc[(m1 + (k + (j + i__ * cc_dim4) * cc_dim3) * cc_dim2 <<
			    1) + 1] = wa[i__ + (j - 1 + wa_dim2) * wa_dim1] *
			    ch[(m2 + (k + (i__ + j * ch_dim4) * ch_dim3) *
			    ch_dim2 << 1) + 1] - wa[i__ + (j - 1 + (wa_dim2 <<
			     1)) * wa_dim1] * ch[(m2 + (k + (i__ + j *
			    ch_dim4) * ch_dim3) * ch_dim2 << 1) + 2];
		    cc[(m1 + (k + (j + i__ * cc_dim4) * cc_dim3) * cc_dim2 <<
			    1) + 2] = wa[i__ + (j - 1 + wa_dim2) * wa_dim1] *
			    ch[(m2 + (k + (i__ + j * ch_dim4) * ch_dim3) *
			    ch_dim2 << 1) + 2] + wa[i__ + (j - 1 + (wa_dim2 <<
			     1)) * wa_dim1] * ch[(m2 + (k + (i__ + j *
			    ch_dim4) * ch_dim3) * ch_dim2 << 1) + 1];
/* L124: */
		}
	    }
/* L125: */
	}
/* L126: */
    }
    return 0;
} /* cmfgkb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmfgkf_d(int *lot, int *ido, int *ip, int *l1, int *lid, int *na, double *cc, double *cc1, int *im1, int *in1, double *ch, double *ch1, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim2, ch_dim3, ch_dim4, ch_offset, cc_dim2, cc_dim3, cc_dim4,
	    cc_offset, cc1_dim2, cc1_dim3, cc1_offset, ch1_dim2, ch1_dim3,
	    ch1_offset, wa_dim1, wa_dim2, wa_offset, i__1, i__2, i__3, i__4,
	    i__5;

    /* Local variables */
     int i__, j, k, l, m1, m2, jc, lc, ki;
     double sn;
     int m1d, m2s;
     double wai, war;
     int ipp2, idlj, ipph;
     double chold1, chold2;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_dim2 = *ip - 1;
    wa_offset = 1 + wa_dim1 * (1 + wa_dim2);
    wa -= wa_offset;
    cc1_dim2 = *in1;
    cc1_dim3 = *lid;
    cc1_offset = 1 + 2 * (1 + cc1_dim2 * (1 + cc1_dim3));
    cc1 -= cc1_offset;
    cc_dim2 = *in1;
    cc_dim3 = *l1;
    cc_dim4 = *ip;
    cc_offset = 1 + 2 * (1 + cc_dim2 * (1 + cc_dim3 * (1 + cc_dim4)));
    cc -= cc_offset;
    ch1_dim2 = *in2;
    ch1_dim3 = *lid;
    ch1_offset = 1 + 2 * (1 + ch1_dim2 * (1 + ch1_dim3));
    ch1 -= ch1_offset;
    ch_dim2 = *in2;
    ch_dim3 = *l1;
    ch_dim4 = *ido;
    ch_offset = 1 + 2 * (1 + ch_dim2 * (1 + ch_dim3 * (1 + ch_dim4)));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*lot - 1) * *im1 + 1;
    m2s = 1 - *im2;
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    i__1 = *lid;
    for (ki = 1; ki <= i__1; ++ki) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 1];
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 2];
/* L110: */
	}
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
/* L112: */
	    }
	}
/* L111: */
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	i__4 = *lid;
	for (ki = 1; ki <= i__4; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__2) {
		m2 += *im2;
		cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 1] += ch1[(m2 + (
			ki + j * ch1_dim3) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 2] += ch1[(m2 + (
			ki + j * ch1_dim3) * ch1_dim2 << 1) + 2];
/* L117: */
	    }
	}
/* L118: */
    }
    i__3 = ipph;
    for (l = 2; l <= i__3; ++l) {
	lc = ipp2 - l;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__1 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__1 : m1 <= i__1; m1 += i__4) {
		m2 += *im2;
		cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 1] = ch1[(m2
			+ (ki + ch1_dim3) * ch1_dim2 << 1) + 1] + wa[(l - 1 +
			wa_dim2) * wa_dim1 + 1] * ch1[(m2 + (ki + (ch1_dim3 <<
			 1)) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 1] = -wa[(l
			- 1 + (wa_dim2 << 1)) * wa_dim1 + 1] * ch1[(m2 + (ki
			+ *ip * ch1_dim3) * ch1_dim2 << 1) + 1];
		cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 2] = ch1[(m2
			+ (ki + ch1_dim3) * ch1_dim2 << 1) + 2] + wa[(l - 1 +
			wa_dim2) * wa_dim1 + 1] * ch1[(m2 + (ki + (ch1_dim3 <<
			 1)) * ch1_dim2 << 1) + 2];
		cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 2] = -wa[(l
			- 1 + (wa_dim2 << 1)) * wa_dim1 + 1] * ch1[(m2 + (ki
			+ *ip * ch1_dim3) * ch1_dim2 << 1) + 2];
/* L113: */
	    }
	}
	i__4 = ipph;
	for (j = 3; j <= i__4; ++j) {
	    jc = ipp2 - j;
	    idlj = (l - 1) * (j - 1) % *ip;
	    war = wa[(idlj + wa_dim2) * wa_dim1 + 1];
	    wai = -wa[(idlj + (wa_dim2 << 1)) * wa_dim1 + 1];
	    i__1 = *lid;
	    for (ki = 1; ki <= i__1; ++ki) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 1] +=
			    war * ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 <<
			    1) + 1];
		    cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 1] +=
			    wai * ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 <<
			     1) + 1];
		    cc1[(m1 + (ki + l * cc1_dim3) * cc1_dim2 << 1) + 2] +=
			    war * ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 <<
			    1) + 2];
		    cc1[(m1 + (ki + lc * cc1_dim3) * cc1_dim2 << 1) + 2] +=
			    wai * ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 <<
			     1) + 2];
/* L114: */
		}
	    }
/* L115: */
	}
/* L116: */
    }
    if (*ido > 1) {
	goto L136;
    }
    sn = 1.0 / (double) (*ip * *l1);
    if (*na == 1) {
	goto L146;
    }
    i__3 = *lid;
    for (ki = 1; ki <= i__3; ++ki) {
	m2 = m2s;
	i__4 = m1d;
	i__5 = *im1;
	for (m1 = 1; i__5 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__5) {
	    m2 += *im2;
	    cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 1] = sn * cc1[(m1 + (
		    ki + cc1_dim3) * cc1_dim2 << 1) + 1];
	    cc1[(m1 + (ki + cc1_dim3) * cc1_dim2 << 1) + 2] = sn * cc1[(m1 + (
		    ki + cc1_dim3) * cc1_dim2 << 1) + 2];
/* L149: */
	}
    }
    i__5 = ipph;
    for (j = 2; j <= i__5; ++j) {
	jc = ipp2 - j;
	i__4 = *lid;
	for (ki = 1; ki <= i__4; ++ki) {
	    i__3 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__2) {
		chold1 = sn * (cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1)
			+ 1] - cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1)
			 + 2]);
		chold2 = sn * (cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1)
			+ 1] + cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1)
			 + 2]);
		cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] = chold1;
		cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] -
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1]);
		cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] +
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1]);
		cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1] = chold2;
/* L119: */
	    }
	}
/* L120: */
    }
    return 0;
L146:
    i__5 = *lid;
    for (ki = 1; ki <= i__5; ++ki) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 1] = sn * cc1[(m1 + (
		    ki + cc1_dim3) * cc1_dim2 << 1) + 1];
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 2] = sn * cc1[(m1 + (
		    ki + cc1_dim3) * cc1_dim2 << 1) + 2];
/* L147: */
	}
    }
    i__3 = ipph;
    for (j = 2; j <= i__3; ++j) {
	jc = ipp2 - j;
	i__2 = *lid;
	for (ki = 1; ki <= i__2; ++ki) {
	    m2 = m2s;
	    i__5 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__4) {
		m2 += *im2;
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 1] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] -
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2]);
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 2] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] +
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1]);
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 1] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] +
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2]);
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 2] = sn * (
			cc1[(m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] -
			cc1[(m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1]);
/* L144: */
	    }
	}
/* L145: */
    }
    return 0;
L136:
    i__3 = *lid;
    for (ki = 1; ki <= i__3; ++ki) {
	m2 = m2s;
	i__4 = m1d;
	i__5 = *im1;
	for (m1 = 1; i__5 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__5) {
	    m2 += *im2;
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 1];
	    ch1[(m2 + (ki + ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1 + (ki +
		    cc1_dim3) * cc1_dim2 << 1) + 2];
/* L137: */
	}
    }
    i__5 = ipph;
    for (j = 2; j <= i__5; ++j) {
	jc = ipp2 - j;
	i__4 = *lid;
	for (ki = 1; ki <= i__4; ++ki) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__2) {
		m2 += *im2;
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] - cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + j * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(m1
			+ (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] + cc1[(m1
			+ (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 1] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 1] + cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 2];
		ch1[(m2 + (ki + jc * ch1_dim3) * ch1_dim2 << 1) + 2] = cc1[(
			m1 + (ki + j * cc1_dim3) * cc1_dim2 << 1) + 2] - cc1[(
			m1 + (ki + jc * cc1_dim3) * cc1_dim2 << 1) + 1];
/* L134: */
	    }
	}
/* L135: */
    }
    i__5 = *ido;
    for (i__ = 1; i__ <= i__5; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		cc[(m1 + (k + (i__ * cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
			+ 1] = ch[(m2 + (k + (i__ + ch_dim4) * ch_dim3) *
			ch_dim2 << 1) + 1];
		cc[(m1 + (k + (i__ * cc_dim4 + 1) * cc_dim3) * cc_dim2 << 1)
			+ 2] = ch[(m2 + (k + (i__ + ch_dim4) * ch_dim3) *
			ch_dim2 << 1) + 2];
/* L130: */
	    }
	}
/* L131: */
    }
    i__5 = *ip;
    for (j = 2; j <= i__5; ++j) {
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__2) {
		m2 += *im2;
		cc[(m1 + (k + (j + cc_dim4) * cc_dim3) * cc_dim2 << 1) + 1] =
			ch[(m2 + (k + (j * ch_dim4 + 1) * ch_dim3) * ch_dim2
			<< 1) + 1];
		cc[(m1 + (k + (j + cc_dim4) * cc_dim3) * cc_dim2 << 1) + 2] =
			ch[(m2 + (k + (j * ch_dim4 + 1) * ch_dim3) * ch_dim2
			<< 1) + 2];
/* L122: */
	    }
	}
/* L123: */
    }
    i__5 = *ip;
    for (j = 2; j <= i__5; ++j) {
	i__2 = *ido;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		m2 = m2s;
		i__4 = m1d;
		i__1 = *im1;
		for (m1 = 1; i__1 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__1) {
		    m2 += *im2;
		    cc[(m1 + (k + (j + i__ * cc_dim4) * cc_dim3) * cc_dim2 <<
			    1) + 1] = wa[i__ + (j - 1 + wa_dim2) * wa_dim1] *
			    ch[(m2 + (k + (i__ + j * ch_dim4) * ch_dim3) *
			    ch_dim2 << 1) + 1] + wa[i__ + (j - 1 + (wa_dim2 <<
			     1)) * wa_dim1] * ch[(m2 + (k + (i__ + j *
			    ch_dim4) * ch_dim3) * ch_dim2 << 1) + 2];
		    cc[(m1 + (k + (j + i__ * cc_dim4) * cc_dim3) * cc_dim2 <<
			    1) + 2] = wa[i__ + (j - 1 + wa_dim2) * wa_dim1] *
			    ch[(m2 + (k + (i__ + j * ch_dim4) * ch_dim3) *
			    ch_dim2 << 1) + 2] - wa[i__ + (j - 1 + (wa_dim2 <<
			     1)) * wa_dim1] * ch[(m2 + (k + (i__ + j *
			    ch_dim4) * ch_dim3) * ch_dim2 << 1) + 1];
/* L124: */
		}
	    }
/* L125: */
	}
/* L126: */
    }
    return 0;
} /* cmfgkf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmfm1b_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac)
{
    /* System generated locals */
    int i__1, i__2;
    int c__1 = 1;

    /* Local variables */
     int k1, l1, l2, na, nf, ip, iw, lid, ido, nbr;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    --fac;
    --wa;
    --ch;
    --c__;

    /* Function Body */
    nf = *fnf;
    na = 0;
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1];
	l2 = ip * l1;
	ido = *n / l2;
	lid = l1 * ido;
/* Computing MIN */
	i__2 = ip - 2;
	nbr = na + 1 + (min(i__2,4) << 1);
	switch (nbr) {
	    case 1:  goto L52;
	    case 2:  goto L62;
	    case 3:  goto L53;
	    case 4:  goto L63;
	    case 5:  goto L54;
	    case 6:  goto L64;
	    case 7:  goto L55;
	    case 8:  goto L65;
	    case 9:  goto L56;
	    case 10:  goto L66;
	}
L52:
	cmf2kb_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L62:
	cmf2kb_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L53:
	cmf3kb_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L63:
	cmf3kb_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L54:
	cmf4kb_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L64:
	cmf4kb_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L55:
	cmf5kb_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L65:
	cmf5kb_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L56:
	cmfgkb_d(lot, &ido, &ip, &l1, &lid, &na, (double*)&c__[1], (double*)&c__[1]
		, jump, inc, &ch[1], &ch[1], &c__1, lot, &wa[iw]);
	goto L120;
L66:
	cmfgkb_d(lot, &ido, &ip, &l1, &lid, &na, &ch[1], &ch[1], &c__1, lot, (
		double*)&c__[1], (double*)&c__[1], jump, inc, &wa[iw]);
L120:
	l1 = l2;
	iw += (ip - 1) * (ido + ido);
	if (ip <= 5) {
	    na = 1 - na;
	}
/* L125: */
    }
    return 0;
} /* cmfm1b_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cmfm1f_d(int *lot, int *jump, int *n, int *inc, fft_complexd_t *c__, double *ch, double *wa, double *fnf, double *fac)
{
    /* System generated locals */
    int i__1, i__2;
    int c__1 = 1;

    /* Local variables */
     int k1, l1, l2, na, nf, ip, iw, lid, ido, nbr;

/* FFTPACK 5.0 auxiliary routine */

    /* Parameter adjustments */
    --fac;
    --wa;
    --ch;
    --c__;

    /* Function Body */
    nf = *fnf;
    na = 0;
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1];
	l2 = ip * l1;
	ido = *n / l2;
	lid = l1 * ido;
/* Computing MIN */
	i__2 = ip - 2;
	nbr = na + 1 + (min(i__2,4) << 1);
	switch (nbr) {
	    case 1:  goto L52;
	    case 2:  goto L62;
	    case 3:  goto L53;
	    case 4:  goto L63;
	    case 5:  goto L54;
	    case 6:  goto L64;
	    case 7:  goto L55;
	    case 8:  goto L65;
	    case 9:  goto L56;
	    case 10:  goto L66;
	}
L52:
	cmf2kf_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L62:
	cmf2kf_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L53:
	cmf3kf_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L63:
	cmf3kf_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L54:
	cmf4kf_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L64:
	cmf4kf_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L55:
	cmf5kf_d(lot, &ido, &l1, &na, (double*)&c__[1], jump, inc, &ch[1], &c__1,
		 lot, &wa[iw]);
	goto L120;
L65:
	cmf5kf_d(lot, &ido, &l1, &na, &ch[1], &c__1, lot, (double*)&c__[1], jump,
		 inc, &wa[iw]);
	goto L120;
L56:
	cmfgkf_d(lot, &ido, &ip, &l1, &lid, &na, (double*)&c__[1], (double*)&c__[1]
		, jump, inc, &ch[1], &ch[1], &c__1, lot, &wa[iw]);
	goto L120;
L66:
	cmfgkf_d(lot, &ido, &ip, &l1, &lid, &na, &ch[1], &ch[1], &c__1, lot, (
		double*)&c__[1], (double*)&c__[1], jump, inc, &wa[iw]);
L120:
	l1 = l2;
	iw += (ip - 1) * (ido + ido);
	if (ip <= 5) {
	    na = 1 - na;
	}
/* L125: */
    }
    return 0;
} /* cmfm1f_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosq1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     double x1;
     int ier1;
     double ssqrt2;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSQ1B", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSQ1B", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("COSQ1B", &c__10, (int)6);
	goto L300;
    }

    if ((i__1 = *n - 2) < 0) {
	goto L300;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L102:
    ssqrt2 = 1.0 / sqrt(2.0);
    x1 = x[x_dim1 + 1] + x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = ssqrt2 * (x[x_dim1 + 1] - x[(x_dim1 << 1) + 1]);
    x[x_dim1 + 1] = x1;
    return 0;
L103:
    cosqb1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQ1B", &c_n5, (int)6);
    }

L300:
    return 0;
} /* cosq1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosq1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int ier1;
     double tsqx;
     double ssqrt2;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSQ1F", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSQ1F", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("COSQ1F", &c__10, (int)6);
	goto L300;
    }

    if ((i__1 = *n - 2) < 0) {
	goto L102;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L103;
    }
L101:
    ssqrt2 = 1.0 / sqrt(2.0);
    tsqx = ssqrt2 * x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = x[x_dim1 + 1] * .5 - tsqx;
    x[x_dim1 + 1] = x[x_dim1 + 1] * .5 + tsqx;
L102:
    return 0;
L103:
    cosqf1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQ1F", &c_n5, (int)6);
    }

L300:
    return 0;
} /* cosq1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosq1i_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k;
     double fk, dt, pih;
     int ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;
    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("COSQ1I", &c__3, (int)6);
	goto L300;
    }

    pih = atan(1.0) * 2.0;
    dt = pih / (double) (*n);
    fk = 0.0;
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	fk += 1.0;
	wsave[k] = cos(fk * dt);
/* L101: */
    }
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    rfft1i_d(n, &wsave[*n + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQ1I", &c_n5, (int)6);
    }
L300:
    return 0;
} /* cosq1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosqb1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int i__, k, kc, np2, ns2, ier1;
     double xim1;
     int modn, lenx, lnwk, lnsv;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;
    ns2 = (*n + 1) / 2;
    np2 = *n + 2;
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	xim1 = x[(i__ - 1) * x_dim1 + 1] + x[i__ * x_dim1 + 1];
	x[i__ * x_dim1 + 1] = (x[(i__ - 1) * x_dim1 + 1] - x[i__ * x_dim1 + 1]
		) * .5;
	x[(i__ - 1) * x_dim1 + 1] = xim1 * .5;
/* L101: */
    }
    x[x_dim1 + 1] *= .5;
    modn = *n % 2;
    if (modn != 0) {
	goto L302;
    }
    x[*n * x_dim1 + 1] *= .5;
L302:
    lenx = *inc * (*n - 1) + 1;
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    lnwk = *n;

    rfft1b_d(n, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, &work[1], &
	    lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQB1", &c_n5, (int)6);
	goto L400;
    }

    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	work[k] = wsave[k - 1] * x[kc * x_dim1 + 1] + wsave[kc - 1] * x[k *
		x_dim1 + 1];
	work[kc] = wsave[k - 1] * x[k * x_dim1 + 1] - wsave[kc - 1] * x[kc *
		x_dim1 + 1];
/* L102: */
    }
    if (modn != 0) {
	goto L305;
    }
    x[(ns2 + 1) * x_dim1 + 1] = wsave[ns2] * (x[(ns2 + 1) * x_dim1 + 1] + x[(
	    ns2 + 1) * x_dim1 + 1]);
L305:
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	x[k * x_dim1 + 1] = work[k] + work[kc];
	x[kc * x_dim1 + 1] = work[k] - work[kc];
/* L103: */
    }
    x[x_dim1 + 1] += x[x_dim1 + 1];
L400:
    return 0;
} /* cosqb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosqf1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int i__, k, kc, np2, ns2, ier1;
     double xim1;
     int modn, lenx, lnwk, lnsv;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;
    ns2 = (*n + 1) / 2;
    np2 = *n + 2;
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	work[k] = x[k * x_dim1 + 1] + x[kc * x_dim1 + 1];
	work[kc] = x[k * x_dim1 + 1] - x[kc * x_dim1 + 1];
/* L101: */
    }
    modn = *n % 2;
    if (modn != 0) {
	goto L301;
    }
    work[ns2 + 1] = x[(ns2 + 1) * x_dim1 + 1] + x[(ns2 + 1) * x_dim1 + 1];
L301:
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	x[k * x_dim1 + 1] = wsave[k - 1] * work[kc] + wsave[kc - 1] * work[k];
	x[kc * x_dim1 + 1] = wsave[k - 1] * work[k] - wsave[kc - 1] * work[kc]
		;
/* L102: */
    }
    if (modn != 0) {
	goto L303;
    }
    x[(ns2 + 1) * x_dim1 + 1] = wsave[ns2] * work[ns2 + 1];
L303:
    lenx = *inc * (*n - 1) + 1;
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    lnwk = *n;

    rfft1f_d(n, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, &work[1], &
	    lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQF1", &c_n5, (int)6);
	goto L400;
    }

    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	xim1 = (x[(i__ - 1) * x_dim1 + 1] + x[i__ * x_dim1 + 1]) * .5;
	x[i__ * x_dim1 + 1] = (x[(i__ - 1) * x_dim1 + 1] - x[i__ * x_dim1 + 1]
		) * .5;
	x[(i__ - 1) * x_dim1 + 1] = xim1;
/* L103: */
    }
L400:
    return 0;
} /* cosqf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosqmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int m;
     double x1;
     int lj, ier1;
     double ssqrt2;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSQMB", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSQMB", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("COSQMB", &c__10, (int)6);
	goto L300;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("COSQMB", &c_n1, (int)6);
	goto L300;
    }

    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L101;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L101:
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x[m + x_dim1] = x[m + x_dim1];
/* L201: */
    }
    return 0;
L102:
    ssqrt2 = 1.0 / sqrt(2.0);
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	x1 = x[m + x_dim1] + x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = ssqrt2 * (x[m + x_dim1] - x[m + (x_dim1 << 1)])
		;
	x[m + x_dim1] = x1;
/* L202: */
    }
    return 0;
L103:
    mcsqb1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQMB", &c_n5, (int)6);
    }

L300:
    return 0;
} /* cosqmb_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosqmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int m, lj, ier1;
     double tsqx;
     double ssqrt2;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSQMF", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSQMF", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("COSQMF", &c__10, (int)6);
	goto L300;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("COSQMF", &c_n1, (int)6);
	goto L300;
    }

    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L102;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L103;
    }
L101:
    ssqrt2 = 1.0 / sqrt(2.0);
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	tsqx = ssqrt2 * x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = x[m + x_dim1] * .5 - tsqx;
	x[m + x_dim1] = x[m + x_dim1] * .5 + tsqx;
/* L201: */
    }
L102:
    return 0;
L103:
    mcsqf1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQMF", &c_n5, (int)6);
    }

L300:
    return 0;
} /* cosqmf_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cosqmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k;
     double fk, dt, pih;
     int ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("COSQMI", &c__3, (int)6);
	goto L300;
    }

    pih = atan(1.0) * 2.0;
    dt = pih / (double) (*n);
    fk = 0.0;
    i__1 = *n;
    for (k = 1; k <= i__1; ++k) {
	fk += 1.0;
	wsave[k] = cos(fk * dt);
/* L101: */
    }
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    rfftmi_d(n, &wsave[*n + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSQMI", &c_n5, (int)6);
    }
L300:
    return 0;
} /* cosqmi_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cost1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;
    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COST1B", &c__6, (int)6);
	goto L100;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COST1B", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *n - 1) {
	*ier = 3;
	//xerfft_d("COST1B", &c__10, (int)6);
	goto L100;
    }

    if (*n == 1) {
	return 0;
    }

    costb1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COST1B", &c_n5, (int)6);
    }

L100:
    return 0;
} /* cost1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cost1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;
    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COST1F", &c__6, (int)6);
	goto L100;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COST1F", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *n - 1) {
	*ier = 3;
	//xerfft_d("COST1F", &c__10, (int)6);
	goto L100;
    }

    if (*n == 1) {
	return 0;
    }

    costf1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COST1F", &c_n5, (int)6);
    }

L100:
    return 0;
} /* cost1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int cost1i_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k, kc;
     double fk, dt;
     int nm1, np1, ns2, ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("COST1I", &c__3, (int)6);
	goto L300;
    }

    if (*n <= 3) {
	return 0;
    }
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    dt = 3.14159265358979323846 / (double) nm1;
    fk = 0.0;
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np1 - k;
	fk += 1.0;
	wsave[k] = sin(fk * dt) * 2.0;
	wsave[kc] = cos(fk * dt) * 2.0;
/* L101: */
    }
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    rfft1i_d(&nm1, &wsave[*n + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COST1I", &c_n5, (int)6);
    }
L300:
    return 0;
} /* cost1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int costb1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int i__, k;
     double t1, t2, x2;
     int kc;
     double xi;
     int nm1, np1;
     double x1h;
     int ns2;
     double x1p3;
     int ier1, modn, lenx;
     double dsum;
     int lnwk, lnsv;
     double fnm1s2, fnm1s4;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;

    /* Function Body */
    *ier = 0;
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    if ((i__1 = *n - 2) < 0) {
	goto L106;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L102;
    }
L101:
    x1h = x[x_dim1 + 1] + x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = x[x_dim1 + 1] - x[(x_dim1 << 1) + 1];
    x[x_dim1 + 1] = x1h;
    return 0;
L102:
    if (*n > 3) {
	goto L103;
    }
    x1p3 = x[x_dim1 + 1] + x[x_dim1 * 3 + 1];
    x2 = x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = x[x_dim1 + 1] - x[x_dim1 * 3 + 1];
    x[x_dim1 + 1] = x1p3 + x2;
    x[x_dim1 * 3 + 1] = x1p3 - x2;
    return 0;
L103:
    x[x_dim1 + 1] += x[x_dim1 + 1];
    x[*n * x_dim1 + 1] += x[*n * x_dim1 + 1];
    dsum = x[x_dim1 + 1] - x[*n * x_dim1 + 1];
    x[x_dim1 + 1] += x[*n * x_dim1 + 1];
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np1 - k;
	t1 = x[k * x_dim1 + 1] + x[kc * x_dim1 + 1];
	t2 = x[k * x_dim1 + 1] - x[kc * x_dim1 + 1];
	dsum += wsave[kc] * t2;
	t2 = wsave[k] * t2;
	x[k * x_dim1 + 1] = t1 - t2;
	x[kc * x_dim1 + 1] = t1 + t2;
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    x[(ns2 + 1) * x_dim1 + 1] += x[(ns2 + 1) * x_dim1 + 1];
L124:
    lenx = *inc * (nm1 - 1) + 1;
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    lnwk = nm1;

    rfft1f_d(&nm1, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, work, &
	    lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSTB1", &c_n5, (int)6);
	return 0;
    }

    fnm1s2 = (double) nm1 / 2.0;
    dsum *= .5;
    x[x_dim1 + 1] = fnm1s2 * x[x_dim1 + 1];
    if (nm1 % 2 != 0) {
	goto L30;
    }
    x[nm1 * x_dim1 + 1] += x[nm1 * x_dim1 + 1];
L30:
    fnm1s4 = (double) nm1 / 4.0;
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	xi = fnm1s4 * x[i__ * x_dim1 + 1];
	x[i__ * x_dim1 + 1] = fnm1s4 * x[(i__ - 1) * x_dim1 + 1];
	x[(i__ - 1) * x_dim1 + 1] = dsum;
	dsum += xi;
/* L105: */
    }
    if (modn != 0) {
	return 0;
    }
    x[*n * x_dim1 + 1] = dsum;
L106:
    return 0;
} /* costb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int costf1_d(int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int i__, k;
     double t1, t2;
     int kc;
     double xi;
     int nm1, np1;
     double x1h;
     int ns2;
     double tx2, x1p3;
     int ier1;
     double snm1;
     int modn, lenx;
     double dsum;
     int lnwk, lnsv;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;

    /* Function Body */
    *ier = 0;
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    if ((i__1 = *n - 2) < 0) {
	goto L200;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L102;
    }
L101:
    x1h = x[x_dim1 + 1] + x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = (x[x_dim1 + 1] - x[(x_dim1 << 1) + 1]) * .5;
    x[x_dim1 + 1] = x1h * .5;
    goto L200;
L102:
    if (*n > 3) {
	goto L103;
    }
    x1p3 = x[x_dim1 + 1] + x[x_dim1 * 3 + 1];
    tx2 = x[(x_dim1 << 1) + 1] + x[(x_dim1 << 1) + 1];
    x[(x_dim1 << 1) + 1] = (x[x_dim1 + 1] - x[x_dim1 * 3 + 1]) * .5;
    x[x_dim1 + 1] = (x1p3 + tx2) * .25;
    x[x_dim1 * 3 + 1] = (x1p3 - tx2) * .25;
    goto L200;
L103:
    dsum = x[x_dim1 + 1] - x[*n * x_dim1 + 1];
    x[x_dim1 + 1] += x[*n * x_dim1 + 1];
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np1 - k;
	t1 = x[k * x_dim1 + 1] + x[kc * x_dim1 + 1];
	t2 = x[k * x_dim1 + 1] - x[kc * x_dim1 + 1];
	dsum += wsave[kc] * t2;
	t2 = wsave[k] * t2;
	x[k * x_dim1 + 1] = t1 - t2;
	x[kc * x_dim1 + 1] = t1 + t2;
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    x[(ns2 + 1) * x_dim1 + 1] += x[(ns2 + 1) * x_dim1 + 1];
L124:
    lenx = *inc * (nm1 - 1) + 1;
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    lnwk = nm1;

    rfft1f_d(&nm1, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, work, &
	    lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSTF1", &c_n5, (int)6);
	goto L200;
    }

    snm1 = 1.0 / (double) nm1;
    dsum = snm1 * dsum;
    if (nm1 % 2 != 0) {
	goto L30;
    }
    x[nm1 * x_dim1 + 1] += x[nm1 * x_dim1 + 1];
L30:
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	xi = x[i__ * x_dim1 + 1] * .5;
	x[i__ * x_dim1 + 1] = x[(i__ - 1) * x_dim1 + 1] * .5;
	x[(i__ - 1) * x_dim1 + 1] = dsum;
	dsum += xi;
/* L105: */
    }
    if (modn != 0) {
	goto L117;
    }
    x[*n * x_dim1 + 1] = dsum;
L117:
    x[x_dim1 + 1] *= .5;
    x[*n * x_dim1 + 1] *= .5;
L200:
    return 0;
} /* costf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int costmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int iw1, ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSTMB", &c__6, (int)6);
	goto L100;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSTMB", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *lot * (*n + 1)) {
	*ier = 3;
	//xerfft_d("COSTMB", &c__10, (int)6);
	goto L100;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("COSTMB", &c_n1, (int)6);
	goto L100;
    }

    iw1 = *lot + *lot + 1;
    mcstb1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], &work[1], &work[iw1],
	    &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSTMB", &c_n5, (int)6);
    }

L100:
    return 0;
} /* costmb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int costmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int iw1, ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("COSTMF", &c__6, (int)6);
	goto L100;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("COSTMF", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *lot * (*n + 1)) {
	*ier = 3;
	//xerfft_d("COSTMF", &c__10, (int)6);
	goto L100;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("COSTMF", &c_n1, (int)6);
	goto L100;
    }

    iw1 = *lot + *lot + 1;
    mcstf1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], &work[1], &work[iw1],
	    &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSTMF", &c_n5, (int)6);
    }

L100:
    return 0;
} /* costmf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int costmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k, kc;
     double fk, dt;
     int nm1, np1, ns2, ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("COSTMI", &c__3, (int)6);
	goto L300;
    }

    if (*n <= 3) {
	return 0;
    }
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    dt = 3.14159265358979323846 / (double) nm1;
    fk = 0.0;
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np1 - k;
	fk += 1.0;
	wsave[k] = sin(fk * dt) * 2.0;
	wsave[kc] = cos(fk * dt) * 2.0;
/* L101: */
    }
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    rfftmi_d(&nm1, &wsave[*n + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("COSTMI", &c_n5, (int)6);
    }
L300:
    return 0;
} /* costmi_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int factor_d(int *n, int *nf, double *fac)
{
    /* Initialized data */

     int ntryh[4] = { 4,2,3,5 };

     int j, nl, nq, nr, ntry;

    /* Parameter adjustments */
    --fac;

    /* Function Body */

    nl = *n;
    *nf = 0;
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
    ++(*nf);
    fac[*nf] = (double) ntry;
    nl = nq;
    if (nl != 1) {
	goto L104;
    }
    return 0;
} /* factor_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mcfti1_d(int *n, double *wa, double *fnf, double *fac)
{
    /* System generated locals */
    int i__1;

    /* Local variables */
     int k1, l1, l2, nf, ip, iw, ido;

    /* Parameter adjustments */
    --fac;
    --wa;

    /* Function Body */
    factor_d(n, &nf, &fac[1]);
    *fnf = (double) nf;
    iw = 1;
    l1 = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1];
	l2 = l1 * ip;
	ido = *n / l2;
	tables_d(&ido, &ip, &wa[iw]);
	iw += (ip - 1) * (ido + ido);
	l1 = l2;
/* L110: */
    }
    return 0;
} /* mcfti1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mcsqb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, work_dim1, work_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1, kc, lj, np2, ns2, ier1;
     double xim1;
     int modn, lenx, lnwk, lnsv;

    /* Parameter adjustments */
    work_dim1 = *lot;
    work_offset = 1 + work_dim1;
    work -= work_offset;
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;

    /* Function Body */
    *ier = 0;
    lj = (*lot - 1) * *jump + 1;
    ns2 = (*n + 1) / 2;
    np2 = *n + 2;
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	i__2 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	    xim1 = x[m + (i__ - 1) * x_dim1] + x[m + i__ * x_dim1];
	    x[m + i__ * x_dim1] = (x[m + (i__ - 1) * x_dim1] - x[m + i__ *
		    x_dim1]) * .5;
	    x[m + (i__ - 1) * x_dim1] = xim1 * .5;
/* L201: */
	}
/* L101: */
    }
    i__1 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	x[m + x_dim1] *= .5;
/* L301: */
    }
    modn = *n % 2;
    if (modn != 0) {
	goto L302;
    }
    i__3 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	x[m + *n * x_dim1] *= .5;
/* L303: */
    }
L302:
    lenx = (*lot - 1) * *jump + *inc * (*n - 1) + 1;
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    lnwk = *lot * *n;

    rfftmb_d(lot, jump, n, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, &
	    work[work_offset], &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MCSQB1", &c_n5, (int)6);
	goto L400;
    }

    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	m1 = 0;
	i__3 = lj;
	i__2 = *jump;
	for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	    ++m1;
	    work[m1 + k * work_dim1] = wsave[k - 1] * x[m + kc * x_dim1] +
		    wsave[kc - 1] * x[m + k * x_dim1];
	    work[m1 + kc * work_dim1] = wsave[k - 1] * x[m + k * x_dim1] -
		    wsave[kc - 1] * x[m + kc * x_dim1];
/* L202: */
	}
/* L102: */
    }
    if (modn != 0) {
	goto L305;
    }
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x[m + (ns2 + 1) * x_dim1] = wsave[ns2] * (x[m + (ns2 + 1) * x_dim1] +
		x[m + (ns2 + 1) * x_dim1]);
/* L304: */
    }
L305:
    i__2 = ns2;
    for (k = 2; k <= i__2; ++k) {
	kc = np2 - k;
	m1 = 0;
	i__1 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	    ++m1;
	    x[m + k * x_dim1] = work[m1 + k * work_dim1] + work[m1 + kc *
		    work_dim1];
	    x[m + kc * x_dim1] = work[m1 + k * work_dim1] - work[m1 + kc *
		    work_dim1];
/* L203: */
	}
/* L103: */
    }
    i__2 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	x[m + x_dim1] += x[m + x_dim1];
/* L104: */
    }
L400:
    return 0;
} /* mcsqb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mcsqf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, work_dim1, work_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1, kc, lj, np2, ns2, ier1;
     double xim1;
     int modn, lenx, lnwk, lnsv;

    /* Parameter adjustments */
    work_dim1 = *lot;
    work_offset = 1 + work_dim1;
    work -= work_offset;
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;

    /* Function Body */
    *ier = 0;
    lj = (*lot - 1) * *jump + 1;
    ns2 = (*n + 1) / 2;
    np2 = *n + 2;
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	kc = np2 - k;
	m1 = 0;
	i__2 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	    ++m1;
	    work[m1 + k * work_dim1] = x[m + k * x_dim1] + x[m + kc * x_dim1];
	    work[m1 + kc * work_dim1] = x[m + k * x_dim1] - x[m + kc * x_dim1]
		    ;
/* L201: */
	}
/* L101: */
    }
    modn = *n % 2;
    if (modn != 0) {
	goto L301;
    }
    m1 = 0;
    i__1 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	++m1;
	work[m1 + (ns2 + 1) * work_dim1] = x[m + (ns2 + 1) * x_dim1] + x[m + (
		ns2 + 1) * x_dim1];
/* L202: */
    }
L301:
    i__3 = ns2;
    for (k = 2; k <= i__3; ++k) {
	kc = np2 - k;
	m1 = 0;
	i__1 = lj;
	i__2 = *jump;
	for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	    ++m1;
	    x[m + k * x_dim1] = wsave[k - 1] * work[m1 + kc * work_dim1] +
		    wsave[kc - 1] * work[m1 + k * work_dim1];
	    x[m + kc * x_dim1] = wsave[k - 1] * work[m1 + k * work_dim1] -
		    wsave[kc - 1] * work[m1 + kc * work_dim1];
/* L302: */
	}
/* L102: */
    }
    if (modn != 0) {
	goto L303;
    }
    m1 = 0;
    i__3 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	++m1;
	x[m + (ns2 + 1) * x_dim1] = wsave[ns2] * work[m1 + (ns2 + 1) *
		work_dim1];
/* L304: */
    }
L303:
    lenx = (*lot - 1) * *jump + *inc * (*n - 1) + 1;
    lnsv = *n + (int) (log((double) (*n)) / log(2.0)) + 4;
    lnwk = *lot * *n;

    rfftmf_d(lot, jump, n, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv, &
	    work[work_offset], &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MCSQF1", &c_n5, (int)6);
	goto L400;
    }

    i__2 = *n;
    for (i__ = 3; i__ <= i__2; i__ += 2) {
	i__3 = lj;
	i__1 = *jump;
	for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	    xim1 = (x[m + (i__ - 1) * x_dim1] + x[m + i__ * x_dim1]) * .5;
	    x[m + i__ * x_dim1] = (x[m + (i__ - 1) * x_dim1] - x[m + i__ *
		    x_dim1]) * .5;
	    x[m + (i__ - 1) * x_dim1] = xim1;
/* L203: */
	}
/* L103: */
    }
L400:
    return 0;
} /* mcsqf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mcstb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1;
     double t1, t2, x2;
     int kc, lj;
     double xi;
     int nm1, np1;
     double x1h;
     int ns2;
     double x1p3;
     int ier1, modn, lenx, lnwk, lnsv;
     double fnm1s2, fnm1s4;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --dsum;

    /* Function Body */
    *ier = 0;
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L106;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L102;
    }
L101:
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x1h = x[m + x_dim1] + x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = x[m + x_dim1] - x[m + (x_dim1 << 1)];
	x[m + x_dim1] = x1h;
/* L111: */
    }
    return 0;
L102:
    if (*n > 3) {
	goto L103;
    }
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	x1p3 = x[m + x_dim1] + x[m + x_dim1 * 3];
	x2 = x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = x[m + x_dim1] - x[m + x_dim1 * 3];
	x[m + x_dim1] = x1p3 + x2;
	x[m + x_dim1 * 3] = x1p3 - x2;
/* L112: */
    }
    return 0;
L103:
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x[m + x_dim1] += x[m + x_dim1];
	x[m + *n * x_dim1] += x[m + *n * x_dim1];
/* L118: */
    }
    m1 = 0;
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	++m1;
	dsum[m1] = x[m + x_dim1] - x[m + *n * x_dim1];
	x[m + x_dim1] += x[m + *n * x_dim1];
/* L113: */
    }
    i__1 = ns2;
    for (k = 2; k <= i__1; ++k) {
	m1 = 0;
	i__2 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	    ++m1;
	    kc = np1 - k;
	    t1 = x[m + k * x_dim1] + x[m + kc * x_dim1];
	    t2 = x[m + k * x_dim1] - x[m + kc * x_dim1];
	    dsum[m1] += wsave[kc] * t2;
	    t2 = wsave[k] * t2;
	    x[m + k * x_dim1] = t1 - t2;
	    x[m + kc * x_dim1] = t1 + t2;
/* L114: */
	}
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    i__1 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	x[m + (ns2 + 1) * x_dim1] += x[m + (ns2 + 1) * x_dim1];
/* L123: */
    }
L124:
    lenx = (*lot - 1) * *jump + *inc * (nm1 - 1) + 1;
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    lnwk = *lot * nm1;

    rfftmf_d(lot, jump, &nm1, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv,
	    work, &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MCSTB1", &c_n5, (int)6);
	goto L106;
    }

    fnm1s2 = (double) nm1 / 2.0;
    m1 = 0;
    i__3 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	++m1;
	dsum[m1] *= .5;
	x[m + x_dim1] = fnm1s2 * x[m + x_dim1];
/* L10: */
    }
    if (nm1 % 2 != 0) {
	goto L30;
    }
    i__1 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	x[m + nm1 * x_dim1] += x[m + nm1 * x_dim1];
/* L20: */
    }
L30:
    fnm1s4 = (double) nm1 / 4.0;
    i__3 = *n;
    for (i__ = 3; i__ <= i__3; i__ += 2) {
	m1 = 0;
	i__1 = lj;
	i__2 = *jump;
	for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	    ++m1;
	    xi = fnm1s4 * x[m + i__ * x_dim1];
	    x[m + i__ * x_dim1] = fnm1s4 * x[m + (i__ - 1) * x_dim1];
	    x[m + (i__ - 1) * x_dim1] = dsum[m1];
	    dsum[m1] += xi;
/* L115: */
	}
/* L105: */
    }
    if (modn != 0) {
	return 0;
    }
    m1 = 0;
    i__3 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	++m1;
	x[m + *n * x_dim1] = dsum[m1];
/* L116: */
    }
L106:
    return 0;
} /* mcstb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mcstf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1;
     double t1, t2;
     int kc, lj;
     double xi;
     int nm1, np1;
     double x1h;
     int ns2;
     double tx2, x1p3;
     int ier1;
     double snm1;
     int modn, lenx, lnwk, lnsv;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --dsum;

    /* Function Body */
    *ier = 0;
    nm1 = *n - 1;
    np1 = *n + 1;
    ns2 = *n / 2;
    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L200;
    } else if (i__1 == 0) {
	goto L101;
    } else {
	goto L102;
    }
L101:
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x1h = x[m + x_dim1] + x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = (x[m + x_dim1] - x[m + (x_dim1 << 1)]) * .5;
	x[m + x_dim1] = x1h * .5;
/* L111: */
    }
    goto L200;
L102:
    if (*n > 3) {
	goto L103;
    }
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	x1p3 = x[m + x_dim1] + x[m + x_dim1 * 3];
	tx2 = x[m + (x_dim1 << 1)] + x[m + (x_dim1 << 1)];
	x[m + (x_dim1 << 1)] = (x[m + x_dim1] - x[m + x_dim1 * 3]) * .5;
	x[m + x_dim1] = (x1p3 + tx2) * .5;
	x[m + x_dim1 * 3] = (x1p3 - tx2) * .5;
/* L112: */
    }
    goto L200;
L103:
    m1 = 0;
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	++m1;
	dsum[m1] = x[m + x_dim1] - x[m + *n * x_dim1];
	x[m + x_dim1] += x[m + *n * x_dim1];
/* L113: */
    }
    i__2 = ns2;
    for (k = 2; k <= i__2; ++k) {
	m1 = 0;
	i__1 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	    ++m1;
	    kc = np1 - k;
	    t1 = x[m + k * x_dim1] + x[m + kc * x_dim1];
	    t2 = x[m + k * x_dim1] - x[m + kc * x_dim1];
	    dsum[m1] += wsave[kc] * t2;
	    t2 = wsave[k] * t2;
	    x[m + k * x_dim1] = t1 - t2;
	    x[m + kc * x_dim1] = t1 + t2;
/* L114: */
	}
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    i__2 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	x[m + (ns2 + 1) * x_dim1] += x[m + (ns2 + 1) * x_dim1];
/* L123: */
    }
L124:
    lenx = (*lot - 1) * *jump + *inc * (nm1 - 1) + 1;
    lnsv = nm1 + (int) (log((double) nm1) / log(2.0)) + 4;
    lnwk = *lot * nm1;

    rfftmf_d(lot, jump, &nm1, inc, &x[x_offset], &lenx, &wsave[*n + 1], &lnsv,
	    work, &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MCSTF1", &c_n5, (int)6);
	goto L200;
    }

    snm1 = 1.0 / (double) nm1;
    i__3 = *lot;
    for (m = 1; m <= i__3; ++m) {
	dsum[m] = snm1 * dsum[m];
/* L10: */
    }
    if (nm1 % 2 != 0) {
	goto L30;
    }
    i__3 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	x[m + nm1 * x_dim1] += x[m + nm1 * x_dim1];
/* L20: */
    }
L30:
    i__2 = *n;
    for (i__ = 3; i__ <= i__2; i__ += 2) {
	m1 = 0;
	i__3 = lj;
	i__1 = *jump;
	for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	    ++m1;
	    xi = x[m + i__ * x_dim1] * .5;
	    x[m + i__ * x_dim1] = x[m + (i__ - 1) * x_dim1] * .5;
	    x[m + (i__ - 1) * x_dim1] = dsum[m1];
	    dsum[m1] += xi;
/* L115: */
	}
/* L105: */
    }
    if (modn != 0) {
	goto L117;
    }
    m1 = 0;
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	++m1;
	x[m + *n * x_dim1] = dsum[m1];
/* L116: */
    }
L117:
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x[m + x_dim1] *= .5;
	x[m + *n * x_dim1] *= .5;
/* L118: */
    }

L200:
    return 0;
} /* mcstf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradb2_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s, idp2;

    /* Parameter adjustments */
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 3);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k + ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + (((k <<
		     1) + 1) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (*ido + ((k
		    << 1) + 2) * cc_dim2) * cc_dim1];
	    ch[m2 + ((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    (((k << 1) + 1) * cc_dim2 + 1) * cc_dim1] - cc[m1 + (*ido
		    + ((k << 1) + 2) * cc_dim2) * cc_dim1];
/* L1001: */
	}
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + ((k << 1) + 1) * cc_dim2) * cc_dim1]
			+ cc[m1 + (ic - 1 + ((k << 1) + 2) * cc_dim2) *
			cc_dim1];
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + ((k << 1) + 1) * cc_dim2) * cc_dim1] - cc[m1 + (
			ic + ((k << 1) + 2) * cc_dim2) * cc_dim1];
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1]
			= wa1[i__ - 2] * (cc[m1 + (i__ - 1 + ((k << 1) + 1) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + ((k << 1) + 2)
			 * cc_dim2) * cc_dim1]) - wa1[i__ - 1] * (cc[m1 + (
			i__ + ((k << 1) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + ((k << 1) + 2) * cc_dim2) * cc_dim1]);
		ch[m2 + (i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] =
			wa1[i__ - 2] * (cc[m1 + (i__ + ((k << 1) + 1) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic + ((k << 1) + 2) *
			cc_dim2) * cc_dim1]) + wa1[i__ - 1] * (cc[m1 + (i__ -
			1 + ((k << 1) + 1) * cc_dim2) * cc_dim1] - cc[m1 + (
			ic - 1 + ((k << 1) + 2) * cc_dim2) * cc_dim1]);
/* L1002: */
	    }
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__3 = m1d;
	i__4 = *im1;
	for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
	    m2 += *im2;
	    ch[m2 + (*ido + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (*
		    ido + ((k << 1) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (*
		    ido + ((k << 1) + 1) * cc_dim2) * cc_dim1];
	    ch[m2 + (*ido + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] = -(cc[
		    m1 + (((k << 1) + 2) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (
		    ((k << 1) + 2) * cc_dim2 + 1) * cc_dim1]);
/* L1003: */
	}
/* L106: */
    }
L107:
    return 0;
} /* mradb2_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradb3_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s;
     double arg;
     int idp2;
     double taui, taur;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + (cc_dim2 << 2));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    arg = atan(1.0) * 8.0 / 3.0;
    taur = cos(arg);
    taui = sin(arg);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k + ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k *
		    3 + 1) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (*ido + (k * 3
		    + 2) * cc_dim2) * cc_dim1] * 2.0;
	    ch[m2 + ((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    ((k * 3 + 1) * cc_dim2 + 1) * cc_dim1] + taur * 2.0 * cc[
		    m1 + (*ido + (k * 3 + 2) * cc_dim2) * cc_dim1] - taui *
		    2.0 * cc[m1 + ((k * 3 + 3) * cc_dim2 + 1) * cc_dim1];
	    ch[m2 + ((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((
		    k * 3 + 1) * cc_dim2 + 1) * cc_dim1] + taur * 2.0 * cc[m1
		    + (*ido + (k * 3 + 2) * cc_dim2) * cc_dim1] + taui * 2.0 *
		     cc[m1 + ((k * 3 + 3) * cc_dim2 + 1) * cc_dim1];
/* L1001: */
	}
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k * 3 + 1) * cc_dim2) * cc_dim1] + (
			cc[m1 + (i__ - 1 + (k * 3 + 3) * cc_dim2) * cc_dim1]
			+ cc[m1 + (ic - 1 + (k * 3 + 2) * cc_dim2) * cc_dim1])
			;
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k * 3 + 1) * cc_dim2) * cc_dim1] + (cc[m1 + (
			i__ + (k * 3 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic
			+ (k * 3 + 2) * cc_dim2) * cc_dim1]);
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1]
			= wa1[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 3 + 1) *
			cc_dim2) * cc_dim1] + taur * (cc[m1 + (i__ - 1 + (k *
			3 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			3 + 2) * cc_dim2) * cc_dim1]) - taui * (cc[m1 + (i__
			+ (k * 3 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic + (
			k * 3 + 2) * cc_dim2) * cc_dim1])) - wa1[i__ - 1] * (
			cc[m1 + (i__ + (k * 3 + 1) * cc_dim2) * cc_dim1] +
			taur * (cc[m1 + (i__ + (k * 3 + 3) * cc_dim2) *
			cc_dim1] - cc[m1 + (ic + (k * 3 + 2) * cc_dim2) *
			cc_dim1]) + taui * (cc[m1 + (i__ - 1 + (k * 3 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + (k * 3 + 2) *
			cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] =
			wa1[i__ - 2] * (cc[m1 + (i__ + (k * 3 + 1) * cc_dim2)
			* cc_dim1] + taur * (cc[m1 + (i__ + (k * 3 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 3 + 2) *
			cc_dim2) * cc_dim1]) + taui * (cc[m1 + (i__ - 1 + (k *
			 3 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + (k *
			 3 + 2) * cc_dim2) * cc_dim1])) + wa1[i__ - 1] * (cc[
			m1 + (i__ - 1 + (k * 3 + 1) * cc_dim2) * cc_dim1] +
			taur * (cc[m1 + (i__ - 1 + (k * 3 + 3) * cc_dim2) *
			cc_dim1] + cc[m1 + (ic - 1 + (k * 3 + 2) * cc_dim2) *
			cc_dim1]) - taui * (cc[m1 + (i__ + (k * 3 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic + (k * 3 + 2) *
			cc_dim2) * cc_dim1]));
		ch[m2 + (i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] =
			wa2[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 3 + 1) *
			cc_dim2) * cc_dim1] + taur * (cc[m1 + (i__ - 1 + (k *
			3 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			3 + 2) * cc_dim2) * cc_dim1]) + taui * (cc[m1 + (i__
			+ (k * 3 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic + (
			k * 3 + 2) * cc_dim2) * cc_dim1])) - wa2[i__ - 1] * (
			cc[m1 + (i__ + (k * 3 + 1) * cc_dim2) * cc_dim1] +
			taur * (cc[m1 + (i__ + (k * 3 + 3) * cc_dim2) *
			cc_dim1] - cc[m1 + (ic + (k * 3 + 2) * cc_dim2) *
			cc_dim1]) - taui * (cc[m1 + (i__ - 1 + (k * 3 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + (k * 3 + 2) *
			cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] = wa2[
			i__ - 2] * (cc[m1 + (i__ + (k * 3 + 1) * cc_dim2) *
			cc_dim1] + taur * (cc[m1 + (i__ + (k * 3 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 3 + 2) *
			cc_dim2) * cc_dim1]) - taui * (cc[m1 + (i__ - 1 + (k *
			 3 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + (k *
			 3 + 2) * cc_dim2) * cc_dim1])) + wa2[i__ - 1] * (cc[
			m1 + (i__ - 1 + (k * 3 + 1) * cc_dim2) * cc_dim1] +
			taur * (cc[m1 + (i__ - 1 + (k * 3 + 3) * cc_dim2) *
			cc_dim1] + cc[m1 + (ic - 1 + (k * 3 + 2) * cc_dim2) *
			cc_dim1]) + taui * (cc[m1 + (i__ + (k * 3 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic + (k * 3 + 2) *
			cc_dim2) * cc_dim1]));
/* L1002: */
	    }
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* mradb3_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradb4_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s, idp2;
     double sqrt2;

    /* Parameter adjustments */
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 5);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    sqrt2 = sqrt(2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + (((
		    k << 2) + 1) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (*ido + (
		    (k << 2) + 4) * cc_dim2) * cc_dim1] - (cc[m1 + (*ido + ((
		    k << 2) + 2) * cc_dim2) * cc_dim1] + cc[m1 + (*ido + ((k
		    << 2) + 2) * cc_dim2) * cc_dim1]);
	    ch[m2 + ((k + ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + (((k <<
		     2) + 1) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (*ido + ((k
		    << 2) + 4) * cc_dim2) * cc_dim1] + (cc[m1 + (*ido + ((k <<
		     2) + 2) * cc_dim2) * cc_dim1] + cc[m1 + (*ido + ((k << 2)
		     + 2) * cc_dim2) * cc_dim1]);
	    ch[m2 + ((k + (ch_dim3 << 2)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    (((k << 2) + 1) * cc_dim2 + 1) * cc_dim1] - cc[m1 + (*ido
		    + ((k << 2) + 4) * cc_dim2) * cc_dim1] + (cc[m1 + (((k <<
		    2) + 3) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (((k << 2) +
		    3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + ((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    (((k << 2) + 1) * cc_dim2 + 1) * cc_dim1] - cc[m1 + (*ido
		    + ((k << 2) + 4) * cc_dim2) * cc_dim1] - (cc[m1 + (((k <<
		    2) + 3) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (((k << 2) +
		    3) * cc_dim2 + 1) * cc_dim1]);
/* L1001: */
	}
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + ((k << 2) + 1) * cc_dim2) * cc_dim1]
			+ cc[m1 + (ic - 1 + ((k << 2) + 4) * cc_dim2) *
			cc_dim1] + (cc[m1 + (i__ - 1 + ((k << 2) + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((k << 2) + 2)
			 * cc_dim2) * cc_dim1]);
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1] - cc[m1 + (
			ic + ((k << 2) + 4) * cc_dim2) * cc_dim1] + (cc[m1 + (
			i__ + ((k << 2) + 3) * cc_dim2) * cc_dim1] - cc[m1 + (
			ic + ((k << 2) + 2) * cc_dim2) * cc_dim1]);
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1]
			= wa1[i__ - 2] * (cc[m1 + (i__ - 1 + ((k << 2) + 1) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + ((k << 2) + 4)
			 * cc_dim2) * cc_dim1] - (cc[m1 + (i__ + ((k << 2) +
			3) * cc_dim2) * cc_dim1] + cc[m1 + (ic + ((k << 2) +
			2) * cc_dim2) * cc_dim1])) - wa1[i__ - 1] * (cc[m1 + (
			i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + ((k << 2) + 4) * cc_dim2) * cc_dim1] + (cc[m1 + (
			i__ - 1 + ((k << 2) + 3) * cc_dim2) * cc_dim1] - cc[
			m1 + (ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] =
			wa1[i__ - 2] * (cc[m1 + (i__ + ((k << 2) + 1) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic + ((k << 2) + 4) *
			cc_dim2) * cc_dim1] + (cc[m1 + (i__ - 1 + ((k << 2) +
			3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + ((k << 2)
			 + 2) * cc_dim2) * cc_dim1])) + wa1[i__ - 1] * (cc[m1
			+ (i__ - 1 + ((k << 2) + 1) * cc_dim2) * cc_dim1] -
			cc[m1 + (ic - 1 + ((k << 2) + 4) * cc_dim2) * cc_dim1]
			 - (cc[m1 + (i__ + ((k << 2) + 3) * cc_dim2) *
			cc_dim1] + cc[m1 + (ic + ((k << 2) + 2) * cc_dim2) *
			cc_dim1]));
		ch[m2 + (i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] =
			wa2[i__ - 2] * (cc[m1 + (i__ - 1 + ((k << 2) + 1) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((k << 2) + 4)
			 * cc_dim2) * cc_dim1] - (cc[m1 + (i__ - 1 + ((k << 2)
			 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((k <<
			 2) + 2) * cc_dim2) * cc_dim1])) - wa2[i__ - 1] * (cc[
			m1 + (i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1] - cc[
			m1 + (ic + ((k << 2) + 4) * cc_dim2) * cc_dim1] - (cc[
			m1 + (i__ + ((k << 2) + 3) * cc_dim2) * cc_dim1] - cc[
			m1 + (ic + ((k << 2) + 2) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] = wa2[
			i__ - 2] * (cc[m1 + (i__ + ((k << 2) + 1) * cc_dim2) *
			 cc_dim1] - cc[m1 + (ic + ((k << 2) + 4) * cc_dim2) *
			cc_dim1] - (cc[m1 + (i__ + ((k << 2) + 3) * cc_dim2) *
			 cc_dim1] - cc[m1 + (ic + ((k << 2) + 2) * cc_dim2) *
			cc_dim1])) + wa2[i__ - 1] * (cc[m1 + (i__ - 1 + ((k <<
			 2) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((
			k << 2) + 4) * cc_dim2) * cc_dim1] - (cc[m1 + (i__ -
			1 + ((k << 2) + 3) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1]
			= wa3[i__ - 2] * (cc[m1 + (i__ - 1 + ((k << 2) + 1) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + ((k << 2) + 4)
			 * cc_dim2) * cc_dim1] + (cc[m1 + (i__ + ((k << 2) +
			3) * cc_dim2) * cc_dim1] + cc[m1 + (ic + ((k << 2) +
			2) * cc_dim2) * cc_dim1])) - wa3[i__ - 1] * (cc[m1 + (
			i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + ((k << 2) + 4) * cc_dim2) * cc_dim1] - (cc[m1 + (
			i__ - 1 + ((k << 2) + 3) * cc_dim2) * cc_dim1] - cc[
			m1 + (ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1] =
			wa3[i__ - 2] * (cc[m1 + (i__ + ((k << 2) + 1) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic + ((k << 2) + 4) *
			cc_dim2) * cc_dim1] - (cc[m1 + (i__ - 1 + ((k << 2) +
			3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 + ((k << 2)
			 + 2) * cc_dim2) * cc_dim1])) + wa3[i__ - 1] * (cc[m1
			+ (i__ - 1 + ((k << 2) + 1) * cc_dim2) * cc_dim1] -
			cc[m1 + (ic - 1 + ((k << 2) + 4) * cc_dim2) * cc_dim1]
			 + (cc[m1 + (i__ + ((k << 2) + 3) * cc_dim2) *
			cc_dim1] + cc[m1 + (ic + ((k << 2) + 2) * cc_dim2) *
			cc_dim1]));
/* L1002: */
	    }
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__3 = m1d;
	i__4 = *im1;
	for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
	    m2 += *im2;
	    ch[m2 + (*ido + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (*
		    ido + ((k << 2) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (*
		    ido + ((k << 2) + 3) * cc_dim2) * cc_dim1] + (cc[m1 + (*
		    ido + ((k << 2) + 1) * cc_dim2) * cc_dim1] + cc[m1 + (*
		    ido + ((k << 2) + 3) * cc_dim2) * cc_dim1]);
	    ch[m2 + (*ido + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] =
		    sqrt2 * (cc[m1 + (*ido + ((k << 2) + 1) * cc_dim2) *
		    cc_dim1] - cc[m1 + (*ido + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1] - (cc[m1 + (((k << 2) + 2) * cc_dim2 + 1) *
		    cc_dim1] + cc[m1 + (((k << 2) + 4) * cc_dim2 + 1) *
		    cc_dim1]));
	    ch[m2 + (*ido + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] = cc[m1 +
		    (((k << 2) + 4) * cc_dim2 + 1) * cc_dim1] - cc[m1 + (((k
		    << 2) + 2) * cc_dim2 + 1) * cc_dim1] + (cc[m1 + (((k << 2)
		     + 4) * cc_dim2 + 1) * cc_dim1] - cc[m1 + (((k << 2) + 2)
		    * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1] =
		    -sqrt2 * (cc[m1 + (*ido + ((k << 2) + 1) * cc_dim2) *
		    cc_dim1] - cc[m1 + (*ido + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1] + (cc[m1 + (((k << 2) + 2) * cc_dim2 + 1) *
		    cc_dim1] + cc[m1 + (((k << 2) + 4) * cc_dim2 + 1) *
		    cc_dim1]));
/* L1003: */
	}
/* L106: */
    }
L107:
    return 0;
} /* mradb4_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradb5_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3, double *wa4)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s;
     double arg, ti11, ti12, tr11, tr12;
     int idp2;

    /* Parameter adjustments */
    --wa4;
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 6);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    arg = atan(1.0) * 8.0 / 5.0;
    tr11 = cos(arg);
    ti11 = sin(arg);
    tr12 = cos(arg * 2.0);
    ti12 = sin(arg * 2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k + ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k *
		    5 + 1) * cc_dim2 + 1) * cc_dim1] + cc[m1 + (*ido + (k * 5
		    + 2) * cc_dim2) * cc_dim1] * 2.0 + cc[m1 + (*ido + (k * 5
		    + 4) * cc_dim2) * cc_dim1] * 2.0;
	    ch[m2 + ((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    ((k * 5 + 1) * cc_dim2 + 1) * cc_dim1] + tr11 * 2.0 * cc[
		    m1 + (*ido + (k * 5 + 2) * cc_dim2) * cc_dim1] + tr12 *
		    2.0 * cc[m1 + (*ido + (k * 5 + 4) * cc_dim2) * cc_dim1] -
		    (ti11 * 2.0 * cc[m1 + ((k * 5 + 3) * cc_dim2 + 1) *
		    cc_dim1] + ti12 * 2.0 * cc[m1 + ((k * 5 + 5) * cc_dim2 +
		    1) * cc_dim1]);
	    ch[m2 + ((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((
		    k * 5 + 1) * cc_dim2 + 1) * cc_dim1] + tr12 * 2.0 * cc[m1
		    + (*ido + (k * 5 + 2) * cc_dim2) * cc_dim1] + tr11 * 2.0 *
		     cc[m1 + (*ido + (k * 5 + 4) * cc_dim2) * cc_dim1] - (
		    ti12 * 2.0 * cc[m1 + ((k * 5 + 3) * cc_dim2 + 1) *
		    cc_dim1] - ti11 * 2.0 * cc[m1 + ((k * 5 + 5) * cc_dim2 +
		    1) * cc_dim1]);
	    ch[m2 + ((k + (ch_dim3 << 2)) * ch_dim2 + 1) * ch_dim1] = cc[m1 +
		    ((k * 5 + 1) * cc_dim2 + 1) * cc_dim1] + tr12 * 2.0 * cc[
		    m1 + (*ido + (k * 5 + 2) * cc_dim2) * cc_dim1] + tr11 *
		    2.0 * cc[m1 + (*ido + (k * 5 + 4) * cc_dim2) * cc_dim1] +
		    (ti12 * 2.0 * cc[m1 + ((k * 5 + 3) * cc_dim2 + 1) *
		    cc_dim1] - ti11 * 2.0 * cc[m1 + ((k * 5 + 5) * cc_dim2 +
		    1) * cc_dim1]);
	    ch[m2 + ((k + ch_dim3 * 5) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((
		    k * 5 + 1) * cc_dim2 + 1) * cc_dim1] + tr11 * 2.0 * cc[m1
		    + (*ido + (k * 5 + 2) * cc_dim2) * cc_dim1] + tr12 * 2.0 *
		     cc[m1 + (*ido + (k * 5 + 4) * cc_dim2) * cc_dim1] + (
		    ti11 * 2.0 * cc[m1 + ((k * 5 + 3) * cc_dim2 + 1) *
		    cc_dim1] + ti12 * 2.0 * cc[m1 + ((k * 5 + 5) * cc_dim2 +
		    1) * cc_dim1]);
/* L1001: */
	}
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k * 5 + 1) * cc_dim2) * cc_dim1] + (
			cc[m1 + (i__ - 1 + (k * 5 + 3) * cc_dim2) * cc_dim1]
			+ cc[m1 + (ic - 1 + (k * 5 + 2) * cc_dim2) * cc_dim1])
			 + (cc[m1 + (i__ - 1 + (k * 5 + 5) * cc_dim2) *
			cc_dim1] + cc[m1 + (ic - 1 + (k * 5 + 4) * cc_dim2) *
			cc_dim1]);
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k * 5 + 1) * cc_dim2) * cc_dim1] + (cc[m1 + (
			i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic
			+ (k * 5 + 2) * cc_dim2) * cc_dim1]) + (cc[m1 + (i__
			+ (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (
			k * 5 + 4) * cc_dim2) * cc_dim1]);
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1]
			= wa1[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 5 + 1) *
			cc_dim2) * cc_dim1] + tr11 * (cc[m1 + (i__ - 1 + (k *
			5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			5 + 2) * cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__
			- 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			- 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]) - (ti11 * (
			cc[m1 + (i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[
			m1 + (ic + (k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 *
			 (cc[m1 + (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] +
			cc[m1 + (ic + (k * 5 + 4) * cc_dim2) * cc_dim1]))) -
			wa1[i__ - 1] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr11 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) + (ti11 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1] =
			wa1[i__ - 2] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr11 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) + (ti11 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]))) + wa1[
			i__ - 1] * (cc[m1 + (i__ - 1 + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr11 * (cc[m1 + (i__ - 1 + (k * 5 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ - 1 + (k *
			 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			 5 + 4) * cc_dim2) * cc_dim1]) - (ti11 * (cc[m1 + (
			i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			+ (k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1
			+ (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] =
			wa2[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 5 + 1) *
			cc_dim2) * cc_dim1] + tr12 * (cc[m1 + (i__ - 1 + (k *
			5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			5 + 2) * cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__
			- 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			- 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]) - (ti12 * (
			cc[m1 + (i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[
			m1 + (ic + (k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 *
			 (cc[m1 + (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] +
			cc[m1 + (ic + (k * 5 + 4) * cc_dim2) * cc_dim1]))) -
			wa2[i__ - 1] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr12 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) + (ti12 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1] = wa2[
			i__ - 2] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2) *
			cc_dim1] + tr12 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) + (ti12 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]))) + wa2[
			i__ - 1] * (cc[m1 + (i__ - 1 + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr12 * (cc[m1 + (i__ - 1 + (k * 5 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ - 1 + (k *
			 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			 5 + 4) * cc_dim2) * cc_dim1]) - (ti12 * (cc[m1 + (
			i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			+ (k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1
			+ (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ - 1 + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1]
			= wa3[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 5 + 1) *
			cc_dim2) * cc_dim1] + tr12 * (cc[m1 + (i__ - 1 + (k *
			5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			5 + 2) * cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__
			- 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			- 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]) + (ti12 * (
			cc[m1 + (i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[
			m1 + (ic + (k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 *
			 (cc[m1 + (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] +
			cc[m1 + (ic + (k * 5 + 4) * cc_dim2) * cc_dim1]))) -
			wa3[i__ - 1] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr12 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) - (ti12 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1] =
			wa3[i__ - 2] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr12 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) - (ti12 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]))) + wa3[
			i__ - 1] * (cc[m1 + (i__ - 1 + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr12 * (cc[m1 + (i__ - 1 + (k * 5 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr11 * (cc[m1 + (i__ - 1 + (k *
			 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			 5 + 4) * cc_dim2) * cc_dim1]) + (ti12 * (cc[m1 + (
			i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			+ (k * 5 + 2) * cc_dim2) * cc_dim1]) - ti11 * (cc[m1
			+ (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ - 1 + (k + ch_dim3 * 5) * ch_dim2) * ch_dim1] =
			wa4[i__ - 2] * (cc[m1 + (i__ - 1 + (k * 5 + 1) *
			cc_dim2) * cc_dim1] + tr11 * (cc[m1 + (i__ - 1 + (k *
			5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			5 + 2) * cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__
			- 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			- 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]) + (ti11 * (
			cc[m1 + (i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[
			m1 + (ic + (k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 *
			 (cc[m1 + (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] +
			cc[m1 + (ic + (k * 5 + 4) * cc_dim2) * cc_dim1]))) -
			wa4[i__ - 1] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr11 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) - (ti11 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k + ch_dim3 * 5) * ch_dim2) * ch_dim1] = wa4[
			i__ - 2] * (cc[m1 + (i__ + (k * 5 + 1) * cc_dim2) *
			cc_dim1] + tr11 * (cc[m1 + (i__ + (k * 5 + 3) *
			cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ + (k * 5
			+ 5) * cc_dim2) * cc_dim1] - cc[m1 + (ic + (k * 5 + 4)
			 * cc_dim2) * cc_dim1]) - (ti11 * (cc[m1 + (i__ - 1 +
			(k * 5 + 3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1 +
			(k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1 + (
			i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1] - cc[m1 +
			(ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1]))) + wa4[
			i__ - 1] * (cc[m1 + (i__ - 1 + (k * 5 + 1) * cc_dim2)
			* cc_dim1] + tr11 * (cc[m1 + (i__ - 1 + (k * 5 + 3) *
			cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k * 5 + 2) *
			cc_dim2) * cc_dim1]) + tr12 * (cc[m1 + (i__ - 1 + (k *
			 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + (k *
			 5 + 4) * cc_dim2) * cc_dim1]) + (ti11 * (cc[m1 + (
			i__ + (k * 5 + 3) * cc_dim2) * cc_dim1] + cc[m1 + (ic
			+ (k * 5 + 2) * cc_dim2) * cc_dim1]) + ti12 * (cc[m1
			+ (i__ + (k * 5 + 5) * cc_dim2) * cc_dim1] + cc[m1 + (
			ic + (k * 5 + 4) * cc_dim2) * cc_dim1])));
/* L1002: */
	    }
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* mradb5_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradbg_d(int *m, int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *im1, int *in1, double *ch, double *ch2, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, c1_dim1, c1_dim2, c1_dim3, c1_offset, c2_dim1, c2_dim2,
	     c2_offset, ch2_dim1, ch2_dim2, ch2_offset, i__1, i__2, i__3,
	    i__4, i__5;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k, l, j2, m1, m2, ic, jc, lc, ik, is;
     double dc2, ai1, ai2;
     int m1d;
     double ar1, ar2, ds2;
     int m2s, nbd;
     double dcp, arg, dsp, tpi, ar1h, ar2h;
     int idp2, ipp2, idij, ipph;

    /* Parameter adjustments */
    --wa;
    c2_dim1 = *in1;
    c2_dim2 = *idl1;
    c2_offset = 1 + c2_dim1 * (1 + c2_dim2);
    c2 -= c2_offset;
    c1_dim1 = *in1;
    c1_dim2 = *ido;
    c1_dim3 = *l1;
    c1_offset = 1 + c1_dim1 * (1 + c1_dim2 * (1 + c1_dim3));
    c1 -= c1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch2_dim1 = *in2;
    ch2_dim2 = *idl1;
    ch2_offset = 1 + ch2_dim1 * (1 + ch2_dim2);
    ch2 -= ch2_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    tpi = atan(1.0) * 8.0;
    arg = tpi / (double) (*ip);
    dcp = cos(arg);
    dsp = sin(arg);
    idp2 = *ido + 2;
    nbd = (*ido - 1) / 2;
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    if (*ido < *l1) {
	goto L103;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1];
/* L1001: */
	    }
/* L101: */
	}
/* L102: */
    }
    goto L106;
L103:
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__4 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__3) {
		m2 += *im2;
		ch[m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1];
/* L1004: */
	    }
/* L104: */
	}
/* L105: */
    }
L106:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
		m2 += *im2;
		ch[m2 + ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1
			+ (*ido + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1]
			 + cc[m1 + (*ido + (j2 - 2 + k * cc_dim3) * cc_dim2) *
			 cc_dim1];
		ch[m2 + ((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1] = cc[m1
			+ ((j2 - 1 + k * cc_dim3) * cc_dim2 + 1) * cc_dim1] +
			cc[m1 + ((j2 - 1 + k * cc_dim3) * cc_dim2 + 1) *
			cc_dim1];
/* L1007: */
	    }
/* L107: */
	}
/* L108: */
    }
    if (*ido == 1) {
	goto L116;
    }
    if (nbd < *l1) {
	goto L112;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__4 = *ido;
	    for (i__ = 3; i__ <= i__4; i__ += 2) {
		ic = idp2 - i__;
		m2 = m2s;
		i__3 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__5) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = cc[m1 + (i__ - 1 + ((j << 1) - 1 + k * cc_dim3)
			     * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((j <<
			    1) - 2 + k * cc_dim3) * cc_dim2) * cc_dim1];
		    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] = cc[m1 + (i__ - 1 + ((j << 1) - 1 + k *
			    cc_dim3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1
			    + ((j << 1) - 2 + k * cc_dim3) * cc_dim2) *
			    cc_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    cc[m1 + (i__ + ((j << 1) - 1 + k * cc_dim3) *
			    cc_dim2) * cc_dim1] - cc[m1 + (ic + ((j << 1) - 2
			    + k * cc_dim3) * cc_dim2) * cc_dim1];
		    ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1] =
			    cc[m1 + (i__ + ((j << 1) - 1 + k * cc_dim3) *
			    cc_dim2) * cc_dim1] + cc[m1 + (ic + ((j << 1) - 2
			    + k * cc_dim3) * cc_dim2) * cc_dim1];
/* L1009: */
		}
/* L109: */
	    }
/* L110: */
	}
/* L111: */
    }
    goto L116;
L112:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    i__4 = *l1;
	    for (k = 1; k <= i__4; ++k) {
		m2 = m2s;
		i__5 = m1d;
		i__3 = *im1;
		for (m1 = 1; i__3 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__3) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = cc[m1 + (i__ - 1 + ((j << 1) - 1 + k * cc_dim3)
			     * cc_dim2) * cc_dim1] + cc[m1 + (ic - 1 + ((j <<
			    1) - 2 + k * cc_dim3) * cc_dim2) * cc_dim1];
		    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] = cc[m1 + (i__ - 1 + ((j << 1) - 1 + k *
			    cc_dim3) * cc_dim2) * cc_dim1] - cc[m1 + (ic - 1
			    + ((j << 1) - 2 + k * cc_dim3) * cc_dim2) *
			    cc_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    cc[m1 + (i__ + ((j << 1) - 1 + k * cc_dim3) *
			    cc_dim2) * cc_dim1] - cc[m1 + (ic + ((j << 1) - 2
			    + k * cc_dim3) * cc_dim2) * cc_dim1];
		    ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1] =
			    cc[m1 + (i__ + ((j << 1) - 1 + k * cc_dim3) *
			    cc_dim2) * cc_dim1] + cc[m1 + (ic + ((j << 1) - 2
			    + k * cc_dim3) * cc_dim2) * cc_dim1];
/* L1013: */
		}
/* L113: */
	    }
/* L114: */
	}
/* L115: */
    }
L116:
    ar1 = 1.0;
    ai1 = 0.0;
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    m2 = m2s;
	    i__4 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__3) {
		m2 += *im2;
		c2[m1 + (ik + l * c2_dim2) * c2_dim1] = ch2[m2 + (ik +
			ch2_dim2) * ch2_dim1] + ar1 * ch2[m2 + (ik + (
			ch2_dim2 << 1)) * ch2_dim1];
		c2[m1 + (ik + lc * c2_dim2) * c2_dim1] = ai1 * ch2[m2 + (ik +
			*ip * ch2_dim2) * ch2_dim1];
/* L1017: */
	    }
/* L117: */
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
		m2 = m2s;
		i__4 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__5) {
		    m2 += *im2;
		    c2[m1 + (ik + l * c2_dim2) * c2_dim1] += ar2 * ch2[m2 + (
			    ik + j * ch2_dim2) * ch2_dim1];
		    c2[m1 + (ik + lc * c2_dim2) * c2_dim1] += ai2 * ch2[m2 + (
			    ik + jc * ch2_dim2) * ch2_dim1];
/* L1018: */
		}
/* L118: */
	    }
/* L119: */
	}
/* L120: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__5 = *im1;
	    for (m1 = 1; i__5 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__5) {
		m2 += *im2;
		ch2[m2 + (ik + ch2_dim2) * ch2_dim1] += ch2[m2 + (ik + j *
			ch2_dim2) * ch2_dim1];
/* L1021: */
	    }
/* L121: */
	}
/* L122: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    m2 = m2s;
	    i__5 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__3) {
		m2 += *im2;
		ch[m2 + ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1] = c1[m1
			+ ((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1] - c1[
			m1 + ((k + jc * c1_dim3) * c1_dim2 + 1) * c1_dim1];
		ch[m2 + ((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1] = c1[m1
			+ ((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1] + c1[
			m1 + ((k + jc * c1_dim3) * c1_dim2 + 1) * c1_dim1];
/* L1023: */
	    }
/* L123: */
	}
/* L124: */
    }
    if (*ido == 1) {
	goto L132;
    }
    if (nbd < *l1) {
	goto L128;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		m2 = m2s;
		i__5 = m1d;
		i__4 = *im1;
		for (m1 = 1; i__4 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__4) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2)
			     * c1_dim1] - c1[m1 + (i__ + (k + jc * c1_dim3) *
			    c1_dim2) * c1_dim1];
		    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] = c1[m1 + (i__ - 1 + (k + j * c1_dim3) *
			    c1_dim2) * c1_dim1] + c1[m1 + (i__ + (k + jc *
			    c1_dim3) * c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) *
			    c1_dim1] + c1[m1 + (i__ - 1 + (k + jc * c1_dim3) *
			     c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1] =
			    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) *
			    c1_dim1] - c1[m1 + (i__ - 1 + (k + jc * c1_dim3) *
			     c1_dim2) * c1_dim1];
/* L1025: */
		}
/* L125: */
	    }
/* L126: */
	}
/* L127: */
    }
    goto L132;
L128:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		m2 = m2s;
		i__4 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__5) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2)
			     * c1_dim1] - c1[m1 + (i__ + (k + jc * c1_dim3) *
			    c1_dim2) * c1_dim1];
		    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] = c1[m1 + (i__ - 1 + (k + j * c1_dim3) *
			    c1_dim2) * c1_dim1] + c1[m1 + (i__ + (k + jc *
			    c1_dim3) * c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) *
			    c1_dim1] + c1[m1 + (i__ - 1 + (k + jc * c1_dim3) *
			     c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1] =
			    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) *
			    c1_dim1] - c1[m1 + (i__ - 1 + (k + jc * c1_dim3) *
			     c1_dim2) * c1_dim1];
/* L1029: */
		}
/* L129: */
	    }
/* L130: */
	}
/* L131: */
    }
L132:
    if (*ido == 1) {
	return 0;
    }
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    c2[m1 + (ik + c2_dim2) * c2_dim1] = ch2[m2 + (ik + ch2_dim2) *
		    ch2_dim1];
/* L1033: */
	}
/* L133: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__3 = *l1;
	for (k = 1; k <= i__3; ++k) {
	    m2 = m2s;
	    i__2 = m1d;
	    i__5 = *im1;
	    for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		m2 += *im2;
		c1[m1 + ((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1] = ch[m2
			+ ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1];
/* L1034: */
	    }
/* L134: */
	}
/* L135: */
    }
    if (nbd > *l1) {
	goto L139;
    }
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	idij = is;
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    idij += 2;
	    i__5 = *l1;
	    for (k = 1; k <= i__5; ++k) {
		m2 = m2s;
		i__2 = m1d;
		i__4 = *im1;
		for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		    m2 += *im2;
		    c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1]
			     = wa[idij - 1] * ch[m2 + (i__ - 1 + (k + j *
			    ch_dim3) * ch_dim2) * ch_dim1] - wa[idij] * ch[m2
			    + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1] =
			    wa[idij - 1] * ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + wa[idij] * ch[m2 + (i__ - 1
			    + (k + j * ch_dim3) * ch_dim2) * ch_dim1];
/* L1036: */
		}
/* L136: */
	    }
/* L137: */
	}
/* L138: */
    }
    goto L143;
L139:
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	i__3 = *l1;
	for (k = 1; k <= i__3; ++k) {
	    idij = is;
	    i__5 = *ido;
	    for (i__ = 3; i__ <= i__5; i__ += 2) {
		idij += 2;
		m2 = m2s;
		i__4 = m1d;
		i__2 = *im1;
		for (m1 = 1; i__2 < 0 ? m1 >= i__4 : m1 <= i__4; m1 += i__2) {
		    m2 += *im2;
		    c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1]
			     = wa[idij - 1] * ch[m2 + (i__ - 1 + (k + j *
			    ch_dim3) * ch_dim2) * ch_dim1] - wa[idij] * ch[m2
			    + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1] =
			    wa[idij - 1] * ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + wa[idij] * ch[m2 + (i__ - 1
			    + (k + j * ch_dim3) * ch_dim2) * ch_dim1];
/* L1040: */
		}
/* L140: */
	    }
/* L141: */
	}
/* L142: */
    }
L143:
    return 0;
} /* mradbg_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradf2_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_dim3, cc_offset,
	     i__1, i__2, i__3, i__4;

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s, idp2;

    /* Parameter adjustments */
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 3);
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + (((k << 1) + 1) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1];
	    ch[m2 + (*ido + ((k << 1) + 2) * ch_dim2) * ch_dim1] = cc[m1 + ((
		    k + cc_dim3) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1];
/* L1001: */
	}
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ + ((k << 1) + 1) * ch_dim2) * ch_dim1] = cc[m1 +
			(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1]);
		ch[m2 + (ic + ((k << 1) + 2) * ch_dim2) * ch_dim1] = wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] - cc[m1 + (i__ +
			(k + cc_dim3) * cc_dim2) * cc_dim1];
		ch[m2 + (i__ - 1 + ((k << 1) + 1) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] +
			(wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)
			) * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]);
		ch[m2 + (ic - 1 + ((k << 1) + 2) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] -
			(wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)
			) * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]);
/* L1003: */
	    }
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__3 = m1d;
	i__4 = *im1;
	for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
	    m2 += *im2;
	    ch[m2 + (((k << 1) + 2) * ch_dim2 + 1) * ch_dim1] = -cc[m1 + (*
		    ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1];
	    ch[m2 + (*ido + ((k << 1) + 1) * ch_dim2) * ch_dim1] = cc[m1 + (*
		    ido + (k + cc_dim3) * cc_dim2) * cc_dim1];
/* L1006: */
	}
/* L106: */
    }
L107:
    return 0;
} /* mradf2_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradf3_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_dim3, cc_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s;
     double arg;
     int idp2;
     double taui, taur;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + (ch_dim2 << 2));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    arg = atan(1.0) * 8.0 / 3.0;
    taur = cos(arg);
    taui = sin(arg);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k * 3 + 1) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + (cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k +
		    cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + ((k * 3 + 3) * ch_dim2 + 1) * ch_dim1] = taui * (cc[m1 + (
		    (k + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k
		    + (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + (k * 3 + 2) * ch_dim2) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + taur * (cc[m1 + ((k
		    + (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k
		    + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
/* L1001: */
	}
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k * 3 + 1) * ch_dim2) * ch_dim1] = cc[m1
			+ (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + (
			wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1))
			 * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa2[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k * 3 + 1) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa2[i__ - 2] *
			 cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ - 1 + (k * 3 + 3) * ch_dim2) * ch_dim1] = cc[m1
			+ (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] +
			taur * (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] *
			cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
			cc_dim1] + (wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + wa2[i__ - 1] *
			cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1]
			)) + taui * (wa1[i__ - 2] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] - wa1[i__ - 1] *
			cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
			cc_dim1] - (wa2[i__ - 2] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] - wa2[i__ - 1] *
			cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1]));
		ch[m2 + (ic - 1 + (k * 3 + 2) * ch_dim2) * ch_dim1] = cc[m1 +
			(i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + taur
			* (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 <<
			1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (
			i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (
			wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1])) - taui * (
			wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] - (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k * 3 + 3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + taur * (
			wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])) + taui * (wa2[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic + (k * 3 + 2) * ch_dim2) * ch_dim1] = taui * (wa2[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1])) - (cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + taur * (
			wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])));
/* L1002: */
	    }
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* mradf3_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradf4_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s, idp2;
     double hsqt2;

    /* Parameter adjustments */
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 5);
    ch -= ch_offset;

    /* Function Body */
    hsqt2 = sqrt(2.0) / 2.0;
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + (((k << 2) + 1) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k +
		    (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k +
		    (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] + (cc[m1 + ((k
		    + cc_dim3) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k +
		    cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + ((k << 2) + 4) * ch_dim2) * ch_dim1] = cc[m1 + ((
		    k + cc_dim3) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k +
		    cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1] - (cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k + (
		    cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + ((k << 2) + 2) * ch_dim2) * ch_dim1] = cc[m1 + ((
		    k + cc_dim3) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k +
		    cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1];
	    ch[m2 + (((k << 2) + 3) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k +
		    (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k +
		    (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1];
/* L1001: */
	}
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + ((k << 2) + 1) * ch_dim2) * ch_dim1] = wa1[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa3[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]) + (cc[m1 +
			(i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa2[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic - 1 + ((k << 2) + 4) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] +
			(wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			 cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1]) - (wa1[i__ -
			2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa3[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + ((k << 2) + 1) * ch_dim2) * ch_dim1] = wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			 cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]) + (cc[m1 + (i__
			+ (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa2[i__ - 2]
			* cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic + ((k << 2) + 4) * ch_dim2) * ch_dim1] = wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			 cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]) - (cc[m1 + (i__
			+ (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa2[i__ - 2]
			* cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ - 1 + ((k << 2) + 3) * ch_dim2) * ch_dim1] = wa1[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] - (wa3[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]) + (cc[
			m1 + (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] -
			(wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			 cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic - 1 + ((k << 2) + 2) * ch_dim2) * ch_dim1] = cc[
			m1 + (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] -
			(wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			 cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1]) - (wa1[i__ -
			2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
			cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] - (wa3[i__ - 2] *
			 cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + ((k << 2) + 3) * ch_dim2) * ch_dim1] = wa3[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa1[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]) + (cc[m1 +
			(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic + ((k << 2) + 2) * ch_dim2) * ch_dim1] = wa3[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa1[i__
			- 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]) - (cc[m1 +
			(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1]));
/* L1003: */
	    }
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__3 = m1d;
	i__4 = *im1;
	for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
	    m2 += *im2;
	    ch[m2 + (*ido + ((k << 2) + 1) * ch_dim2) * ch_dim1] = hsqt2 * (
		    cc[m1 + (*ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]
		     - cc[m1 + (*ido + (k + (cc_dim3 << 2)) * cc_dim2) *
		    cc_dim1]) + cc[m1 + (*ido + (k + cc_dim3) * cc_dim2) *
		    cc_dim1];
	    ch[m2 + (*ido + ((k << 2) + 3) * ch_dim2) * ch_dim1] = cc[m1 + (*
		    ido + (k + cc_dim3) * cc_dim2) * cc_dim1] - hsqt2 * (cc[
		    m1 + (*ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] -
		    cc[m1 + (*ido + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]
		    );
	    ch[m2 + (((k << 2) + 2) * ch_dim2 + 1) * ch_dim1] = -hsqt2 * (cc[
		    m1 + (*ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] +
		    cc[m1 + (*ido + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]
		    ) - cc[m1 + (*ido + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1];
	    ch[m2 + (((k << 2) + 4) * ch_dim2 + 1) * ch_dim1] = -hsqt2 * (cc[
		    m1 + (*ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] +
		    cc[m1 + (*ido + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]
		    ) + cc[m1 + (*ido + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1];
/* L1006: */
	}
/* L106: */
    }
L107:
    return 0;
} /* mradf4_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradf5_d(int *m, int *ido, int *l1, double *cc, int *im1, int *in1, double *ch, int *im2, int *in2, double *wa1, double *wa2, double *wa3, double *wa4)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     i__1, i__2, i__3, i__4;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m1, m2, ic, m1d, m2s;
     double arg, ti11, ti12, tr11, tr12;
     int idp2;

    /* Parameter adjustments */
    --wa4;
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 6);
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    arg = atan(1.0) * 8.0 / 5.0;
    tr11 = cos(arg);
    ti11 = sin(arg);
    tr12 = cos(arg * 2.0);
    ti12 = sin(arg * 2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch[m2 + ((k * 5 + 1) * ch_dim2 + 1) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + (cc[m1 + ((k +
		    cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]) + (cc[m1 + ((k
		    + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k
		    + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + (k * 5 + 2) * ch_dim2) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + tr11 * (cc[m1 + ((k
		    + cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]) + tr12 * (cc[m1
		    + ((k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] + cc[m1
		    + ((k + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + ((k * 5 + 3) * ch_dim2 + 1) * ch_dim1] = ti11 * (cc[m1 + (
		    (k + cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k
		    + (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]) + ti12 * (cc[
		    m1 + ((k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] - cc[
		    m1 + ((k + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + (*ido + (k * 5 + 4) * ch_dim2) * ch_dim1] = cc[m1 + ((k +
		    cc_dim3) * cc_dim2 + 1) * cc_dim1] + tr12 * (cc[m1 + ((k
		    + cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1] + cc[m1 + ((k + (
		    cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]) + tr11 * (cc[m1
		    + ((k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] + cc[m1
		    + ((k + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
	    ch[m2 + ((k * 5 + 5) * ch_dim2 + 1) * ch_dim1] = ti12 * (cc[m1 + (
		    (k + cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1] - cc[m1 + ((k
		    + (cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1]) - ti11 * (cc[
		    m1 + ((k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1] - cc[
		    m1 + ((k + cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1]);
/* L1001: */
	}
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    ic = idp2 - i__;
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + (i__ - 1 + (k * 5 + 1) * ch_dim2) * ch_dim1] = cc[m1
			+ (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + (
			wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1))
			 * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1])) + (wa2[i__ -
			2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) *
			 cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ + (k * 5 + 1) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + (wa1[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[i__ - 2] *
			 cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2) *
			cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + (wa2[i__ - 2] *
			 cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) *
			cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]));
		ch[m2 + (i__ - 1 + (k * 5 + 3) * ch_dim2) * ch_dim1] = cc[m1
			+ (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] +
			tr11 * (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] *
			cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
			cc_dim1] + wa4[i__ - 2] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1] + wa4[i__ - 1] *
			cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1]
			) + tr12 * (wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + wa2[i__ - 1] *
			cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1]
			 + wa3[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 <<
			2)) * cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (
			i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1]) +
			ti11 * (wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 <<
			 1)) * cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (
			i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]
			- (wa4[i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + cc_dim3 * 5) * cc_dim2) * cc_dim1])) + ti12 * (
			wa2[i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa3[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2)
			* cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]));
		ch[m2 + (ic - 1 + (k * 5 + 2) * ch_dim2) * ch_dim1] = cc[m1 +
			(i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + tr11
			* (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 <<
			1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (
			i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] +
			wa4[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1]) + tr12 * (wa2[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1] + wa3[i__ - 2]
			* cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) *
			 cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1]) - (ti11 * (wa1[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] - (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + ti12 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k * 5 + 3) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + tr11 * (
			wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + tr12 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])) + (ti11 * (wa4[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1])) + ti12 * (wa3[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])));
		ch[m2 + (ic + (k * 5 + 2) * ch_dim2) * ch_dim1] = ti11 * (wa4[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1])) + ti12 * (wa3[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])) - (cc[m1 + (i__
			+ (k + cc_dim3) * cc_dim2) * cc_dim1] + tr11 * (wa1[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + tr12 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ - 1 + (k * 5 + 5) * ch_dim2) * ch_dim1] = cc[m1
			+ (i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] +
			tr12 * (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] *
			cc[m1 + (i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
			cc_dim1] + (wa4[i__ - 2] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1] + wa4[i__ - 1] *
			cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1]
			)) + tr11 * (wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + wa2[i__ - 1] *
			cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1]
			 + (wa3[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 <<
			 2)) * cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (
			i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1])) + (
			ti12 * (wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 <<
			 1)) * cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (
			i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1]
			- (wa4[i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + cc_dim3 * 5) * cc_dim2) * cc_dim1])) - ti11 * (
			wa2[i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa3[i__
			- 2] * cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2)
			* cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])));
		ch[m2 + (ic - 1 + (k * 5 + 4) * ch_dim2) * ch_dim1] = cc[m1 +
			(i__ - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1] + tr12
			* (wa1[i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 <<
			1)) * cc_dim2) * cc_dim1] + wa1[i__ - 1] * cc[m1 + (
			i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (
			wa4[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1])) + tr11 * (
			wa2[i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) *
			cc_dim2) * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2)
			* cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])) - (ti12 * (wa1[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] - (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) - ti11 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] - (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])));
		ch[m2 + (i__ + (k * 5 + 5) * ch_dim2) * ch_dim1] = cc[m1 + (
			i__ + (k + cc_dim3) * cc_dim2) * cc_dim1] + tr12 * (
			wa1[i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + tr11 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])) + (ti12 * (wa4[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1])) - ti11 * (wa3[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])));
		ch[m2 + (ic + (k * 5 + 4) * ch_dim2) * ch_dim1] = ti12 * (wa4[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 5) *
			cc_dim2) * cc_dim1] + wa4[i__ - 1] * cc[m1 + (i__ + (
			k + cc_dim3 * 5) * cc_dim2) * cc_dim1] - (wa1[i__ - 2]
			 * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2)
			* cc_dim1] + wa1[i__ - 1] * cc[m1 + (i__ + (k + (
			cc_dim3 << 1)) * cc_dim2) * cc_dim1])) - ti11 * (wa3[
			i__ - 2] * cc[m1 + (i__ - 1 + (k + (cc_dim3 << 2)) *
			cc_dim2) * cc_dim1] + wa3[i__ - 1] * cc[m1 + (i__ + (
			k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1] - (wa2[i__
			- 2] * cc[m1 + (i__ - 1 + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] + wa2[i__ - 1] * cc[m1 + (i__ + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1])) - (cc[m1 + (i__
			+ (k + cc_dim3) * cc_dim2) * cc_dim1] + tr12 * (wa1[
			i__ - 2] * cc[m1 + (i__ + (k + (cc_dim3 << 1)) *
			cc_dim2) * cc_dim1] - wa1[i__ - 1] * cc[m1 + (i__ - 1
			+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1] + (wa4[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 5) * cc_dim2)
			 * cc_dim1] - wa4[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 5) * cc_dim2) * cc_dim1])) + tr11 * (wa2[
			i__ - 2] * cc[m1 + (i__ + (k + cc_dim3 * 3) * cc_dim2)
			 * cc_dim1] - wa2[i__ - 1] * cc[m1 + (i__ - 1 + (k +
			cc_dim3 * 3) * cc_dim2) * cc_dim1] + (wa3[i__ - 2] *
			cc[m1 + (i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
			cc_dim1] - wa3[i__ - 1] * cc[m1 + (i__ - 1 + (k + (
			cc_dim3 << 2)) * cc_dim2) * cc_dim1])));
/* L1002: */
	    }
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* mradf5_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mradfg_d(int *m, int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *im1, int *in1, double *ch, double *ch2, int *im2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, c1_dim1, c1_dim2, c1_dim3, c1_offset, c2_dim1, c2_dim2,
	     c2_offset, ch2_dim1, ch2_dim2, ch2_offset, i__1, i__2, i__3,
	    i__4, i__5;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k, l, j2, m1, m2, ic, jc, lc, ik, is;
     double dc2, ai1, ai2;
     int m1d;
     double ar1, ar2, ds2;
     int m2s, nbd;
     double dcp, arg, dsp, tpi, ar1h, ar2h;
     int idp2, ipp2, idij, ipph;

    /* Parameter adjustments */
    --wa;
    c2_dim1 = *in1;
    c2_dim2 = *idl1;
    c2_offset = 1 + c2_dim1 * (1 + c2_dim2);
    c2 -= c2_offset;
    c1_dim1 = *in1;
    c1_dim2 = *ido;
    c1_dim3 = *l1;
    c1_offset = 1 + c1_dim1 * (1 + c1_dim2 * (1 + c1_dim3));
    c1 -= c1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch2_dim1 = *in2;
    ch2_dim2 = *idl1;
    ch2_offset = 1 + ch2_dim1 * (1 + ch2_dim2);
    ch2 -= ch2_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    m1d = (*m - 1) * *im1 + 1;
    m2s = 1 - *im2;
    tpi = atan(1.0) * 8.0;
    arg = tpi / (double) (*ip);
    dcp = cos(arg);
    dsp = sin(arg);
    ipph = (*ip + 1) / 2;
    ipp2 = *ip + 2;
    idp2 = *ido + 2;
    nbd = (*ido - 1) / 2;
    if (*ido == 1) {
	goto L119;
    }
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	m2 = m2s;
	i__2 = m1d;
	i__3 = *im1;
	for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
	    m2 += *im2;
	    ch2[m2 + (ik + ch2_dim2) * ch2_dim1] = c2[m1 + (ik + c2_dim2) *
		    c2_dim1];
/* L1001: */
	}
/* L101: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__3 = *l1;
	for (k = 1; k <= i__3; ++k) {
	    m2 = m2s;
	    i__2 = m1d;
	    i__4 = *im1;
	    for (m1 = 1; i__4 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__4) {
		m2 += *im2;
		ch[m2 + ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1] = c1[m1
			+ ((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1];
/* L1002: */
	    }
/* L102: */
	}
/* L103: */
    }
    if (nbd > *l1) {
	goto L107;
    }
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	idij = is;
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    idij += 2;
	    i__4 = *l1;
	    for (k = 1; k <= i__4; ++k) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = wa[idij - 1] * c1[m1 + (i__ - 1 + (k + j *
			    c1_dim3) * c1_dim2) * c1_dim1] + wa[idij] * c1[m1
			    + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    wa[idij - 1] * c1[m1 + (i__ + (k + j * c1_dim3) *
			    c1_dim2) * c1_dim1] - wa[idij] * c1[m1 + (i__ - 1
			    + (k + j * c1_dim3) * c1_dim2) * c1_dim1];
/* L1004: */
		}
/* L104: */
	    }
/* L105: */
	}
/* L106: */
    }
    goto L111;
L107:
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	i__3 = *l1;
	for (k = 1; k <= i__3; ++k) {
	    idij = is;
	    i__4 = *ido;
	    for (i__ = 3; i__ <= i__4; i__ += 2) {
		idij += 2;
		m2 = m2s;
		i__5 = m1d;
		i__2 = *im1;
		for (m1 = 1; i__2 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__2) {
		    m2 += *im2;
		    ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1]
			     = wa[idij - 1] * c1[m1 + (i__ - 1 + (k + j *
			    c1_dim3) * c1_dim2) * c1_dim1] + wa[idij] * c1[m1
			    + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1];
		    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1] =
			    wa[idij - 1] * c1[m1 + (i__ + (k + j * c1_dim3) *
			    c1_dim2) * c1_dim1] - wa[idij] * c1[m1 + (i__ - 1
			    + (k + j * c1_dim3) * c1_dim2) * c1_dim1];
/* L1008: */
		}
/* L108: */
	    }
/* L109: */
	}
/* L110: */
    }
L111:
    if (nbd < *l1) {
	goto L115;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__3 = *l1;
	for (k = 1; k <= i__3; ++k) {
	    i__4 = *ido;
	    for (i__ = 3; i__ <= i__4; i__ += 2) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1]
			     = ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2)
			     * ch_dim1] + ch[m2 + (i__ - 1 + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ - 1 + (k + jc * c1_dim3) * c1_dim2) *
			    c1_dim1] = ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] - ch[m2 + (i__ + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1] =
			    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) *
			    ch_dim1] + ch[m2 + (i__ + (k + jc * ch_dim3) *
			    ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + jc * c1_dim3) * c1_dim2) * c1_dim1] =
			    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			     ch_dim1] - ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			     ch_dim2) * ch_dim1];
/* L1012: */
		}
/* L112: */
	    }
/* L113: */
	}
/* L114: */
    }
    goto L121;
L115:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__3 = *ido;
	for (i__ = 3; i__ <= i__3; i__ += 2) {
	    i__4 = *l1;
	    for (k = 1; k <= i__4; ++k) {
		m2 = m2s;
		i__5 = m1d;
		i__2 = *im1;
		for (m1 = 1; i__2 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__2) {
		    m2 += *im2;
		    c1[m1 + (i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1]
			     = ch[m2 + (i__ - 1 + (k + j * ch_dim3) * ch_dim2)
			     * ch_dim1] + ch[m2 + (i__ - 1 + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ - 1 + (k + jc * c1_dim3) * c1_dim2) *
			    c1_dim1] = ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] - ch[m2 + (i__ + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1] =
			    ch[m2 + (i__ + (k + j * ch_dim3) * ch_dim2) *
			    ch_dim1] + ch[m2 + (i__ + (k + jc * ch_dim3) *
			    ch_dim2) * ch_dim1];
		    c1[m1 + (i__ + (k + jc * c1_dim3) * c1_dim2) * c1_dim1] =
			    ch[m2 + (i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			     ch_dim1] - ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			     ch_dim2) * ch_dim1];
/* L1016: */
		}
/* L116: */
	    }
/* L117: */
	}
/* L118: */
    }
    goto L121;
L119:
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	m2 = m2s;
	i__3 = m1d;
	i__4 = *im1;
	for (m1 = 1; i__4 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__4) {
	    m2 += *im2;
	    c2[m1 + (ik + c2_dim2) * c2_dim1] = ch2[m2 + (ik + ch2_dim2) *
		    ch2_dim1];
/* L1020: */
	}
/* L120: */
    }
L121:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__2 = *im1;
	    for (m1 = 1; i__2 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__2) {
		m2 += *im2;
		c1[m1 + ((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1] = ch[m2
			+ ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1] + ch[
			m2 + ((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1];
		c1[m1 + ((k + jc * c1_dim3) * c1_dim2 + 1) * c1_dim1] = ch[m2
			+ ((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1] - ch[
			m2 + ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1];
/* L1022: */
	    }
/* L122: */
	}
/* L123: */
    }

    ar1 = 1.0;
    ai1 = 0.0;
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__4 = *idl1;
	for (ik = 1; ik <= i__4; ++ik) {
	    m2 = m2s;
	    i__2 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__3) {
		m2 += *im2;
		ch2[m2 + (ik + l * ch2_dim2) * ch2_dim1] = c2[m1 + (ik +
			c2_dim2) * c2_dim1] + ar1 * c2[m1 + (ik + (c2_dim2 <<
			1)) * c2_dim1];
		ch2[m2 + (ik + lc * ch2_dim2) * ch2_dim1] = ai1 * c2[m1 + (ik
			+ *ip * c2_dim2) * c2_dim1];
/* L1024: */
	    }
/* L124: */
	}
	dc2 = ar1;
	ds2 = ai1;
	ar2 = ar1;
	ai2 = ai1;
	i__4 = ipph;
	for (j = 3; j <= i__4; ++j) {
	    jc = ipp2 - j;
	    ar2h = dc2 * ar2 - ds2 * ai2;
	    ai2 = dc2 * ai2 + ds2 * ar2;
	    ar2 = ar2h;
	    i__3 = *idl1;
	    for (ik = 1; ik <= i__3; ++ik) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    ch2[m2 + (ik + l * ch2_dim2) * ch2_dim1] += ar2 * c2[m1 +
			    (ik + j * c2_dim2) * c2_dim1];
		    ch2[m2 + (ik + lc * ch2_dim2) * ch2_dim1] += ai2 * c2[m1
			    + (ik + jc * c2_dim2) * c2_dim1];
/* L1025: */
		}
/* L125: */
	    }
/* L126: */
	}
/* L127: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__4 = *idl1;
	for (ik = 1; ik <= i__4; ++ik) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__5 = *im1;
	    for (m1 = 1; i__5 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__5) {
		m2 += *im2;
		ch2[m2 + (ik + ch2_dim2) * ch2_dim1] += c2[m1 + (ik + j *
			c2_dim2) * c2_dim1];
/* L1028: */
	    }
/* L128: */
	}
/* L129: */
    }

    if (*ido < *l1) {
	goto L132;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__4 = *ido;
	for (i__ = 1; i__ <= i__4; ++i__) {
	    m2 = m2s;
	    i__5 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__3) {
		m2 += *im2;
		cc[m1 + (i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1] = ch[
			m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1];
/* L1030: */
	    }
/* L130: */
	}
/* L131: */
    }
    goto L135;
L132:
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    m2 = m2s;
	    i__3 = m1d;
	    i__5 = *im1;
	    for (m1 = 1; i__5 < 0 ? m1 >= i__3 : m1 <= i__3; m1 += i__5) {
		m2 += *im2;
		cc[m1 + (i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1] = ch[
			m2 + (i__ + (k + ch_dim3) * ch_dim2) * ch_dim1];
/* L1033: */
	    }
/* L133: */
	}
/* L134: */
    }
L135:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    m2 = m2s;
	    i__5 = m1d;
	    i__3 = *im1;
	    for (m1 = 1; i__3 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__3) {
		m2 += *im2;
		cc[m1 + (*ido + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1] =
			 ch[m2 + ((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1];
		cc[m1 + ((j2 - 1 + k * cc_dim3) * cc_dim2 + 1) * cc_dim1] =
			ch[m2 + ((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1];
/* L1036: */
	    }
/* L136: */
	}
/* L137: */
    }
    if (*ido == 1) {
	return 0;
    }
    if (nbd < *l1) {
	goto L141;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__4 = *l1;
	for (k = 1; k <= i__4; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		ic = idp2 - i__;
		m2 = m2s;
		i__5 = m1d;
		i__2 = *im1;
		for (m1 = 1; i__2 < 0 ? m1 >= i__5 : m1 <= i__5; m1 += i__2) {
		    m2 += *im2;
		    cc[m1 + (i__ - 1 + (j2 - 1 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + ch[m2 + (i__ - 1 + (k + jc *
			     ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (ic - 1 + (j2 - 2 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] - ch[m2 + (i__ - 1 + (k + jc *
			     ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (i__ + (j2 - 1 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + ch[m2 + (i__ + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (ic + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1]
			     = ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] - ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1];
/* L1038: */
		}
/* L138: */
	    }
/* L139: */
	}
/* L140: */
    }
    return 0;
L141:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__4 = *ido;
	for (i__ = 3; i__ <= i__4; i__ += 2) {
	    ic = idp2 - i__;
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		m2 = m2s;
		i__2 = m1d;
		i__5 = *im1;
		for (m1 = 1; i__5 < 0 ? m1 >= i__2 : m1 <= i__2; m1 += i__5) {
		    m2 += *im2;
		    cc[m1 + (i__ - 1 + (j2 - 1 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + ch[m2 + (i__ - 1 + (k + jc *
			     ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (ic - 1 + (j2 - 2 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ - 1 + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] - ch[m2 + (i__ - 1 + (k + jc *
			     ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (i__ + (j2 - 1 + k * cc_dim3) * cc_dim2) *
			    cc_dim1] = ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1] + ch[m2 + (i__ + (k + jc *
			    ch_dim3) * ch_dim2) * ch_dim1];
		    cc[m1 + (ic + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1]
			     = ch[m2 + (i__ + (k + jc * ch_dim3) * ch_dim2) *
			    ch_dim1] - ch[m2 + (i__ + (k + j * ch_dim3) *
			    ch_dim2) * ch_dim1];
/* L1042: */
		}
/* L142: */
	    }
/* L143: */
	}
/* L144: */
    }
    return 0;
} /* mradfg_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mrftb1_d(int *m, int *im, int *n, int *in, double *c__, double *ch, double *wa, double *fac)
{
    /* System generated locals */
    int ch_dim1, ch_offset, c_dim1, c_offset, i__1, i__2;
    int c__1 = 1;

    /* Local variables */
     int i__, j, k1, l1, l2, m2, na, nf, ip, nl, iw, ix2, ix3, ix4,
	    ido, idl1;
     double half;
     int modn;
     double halfm;

    /* Parameter adjustments */
    ch_dim1 = *m;
    ch_offset = 1 + ch_dim1;
    ch -= ch_offset;
    --wa;
    c_dim1 = *in;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --fac;

    /* Function Body */
    nf = fac[2];
    na = 0;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	na = 1 - na;
	if (ip <= 5) {
	    goto L10;
	}
	if (k1 == nf) {
	    goto L10;
	}
	na = 1 - na;
L10:
	;
    }
    half = .5;
    halfm = -.5;
    modn = *n % 2;
    nl = *n - 2;
    if (modn != 0) {
	nl = *n - 1;
    }
    if (na == 0) {
	goto L120;
    }
    m2 = 1 - *im;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	m2 += *im;
	ch[i__ + ch_dim1] = c__[m2 + c_dim1];
	ch[i__ + *n * ch_dim1] = c__[m2 + *n * c_dim1];
/* L117: */
    }
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	m2 = 1 - *im;
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    m2 += *im;
	    ch[i__ + j * ch_dim1] = half * c__[m2 + j * c_dim1];
	    ch[i__ + (j + 1) * ch_dim1] = halfm * c__[m2 + (j + 1) * c_dim1];
/* L118: */
	}
    }
    goto L124;
L120:
    i__2 = nl;
    for (j = 2; j <= i__2; j += 2) {
	m2 = 1 - *im;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    m2 += *im;
	    c__[m2 + j * c_dim1] = half * c__[m2 + j * c_dim1];
	    c__[m2 + (j + 1) * c_dim1] = halfm * c__[m2 + (j + 1) * c_dim1];
/* L122: */
	}
    }
L124:
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	l2 = ip * l1;
	ido = *n / l2;
	idl1 = ido * l1;
	if (ip != 4) {
	    goto L103;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	if (na != 0) {
	    goto L101;
	}
	mradb4_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2], &wa[ix3]);
	goto L102;
L101:
	mradb4_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2], &wa[ix3]);
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
	mradb2_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw]);
	goto L105;
L104:
	mradb2_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw]);
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
	mradb3_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2]);
	goto L108;
L107:
	mradb3_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2]);
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
	mradb5_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
	goto L111;
L110:
	mradb5_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
L111:
	na = 1 - na;
	goto L115;
L112:
	if (na != 0) {
	    goto L113;
	}
	mradbg_d(m, &ido, &ip, &l1, &idl1, &c__[c_offset], &c__[c_offset], &
		c__[c_offset], im, in, &ch[ch_offset], &ch[ch_offset], &c__1,
		m, &wa[iw]);
	goto L114;
L113:
	mradbg_d(m, &ido, &ip, &l1, &idl1, &ch[ch_offset], &ch[ch_offset], &ch[
		ch_offset], &c__1, m, &c__[c_offset], &c__[c_offset], im, in,
		&wa[iw]);
L114:
	if (ido == 1) {
	    na = 1 - na;
	}
L115:
	l1 = l2;
	iw += (ip - 1) * ido;
/* L116: */
    }
    return 0;
} /* mrftb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mrftf1_d(int *m, int *im, int *n, int *in, double *c__, double *ch, double *wa, double *fac)
{
    /* System generated locals */
    int ch_dim1, ch_offset, c_dim1, c_offset, i__1, i__2;
    int c__1 = 1;

    /* Local variables */
     int i__, j, k1, l1, l2, m2, na, kh, nf, ip, nl, iw;
     double sn;
     int ix2, ix3, ix4, ido;
     double tsn;
     int idl1, modn;
     double tsnm;

    /* Parameter adjustments */
    ch_dim1 = *m;
    ch_offset = 1 + ch_dim1;
    ch -= ch_offset;
    --wa;
    c_dim1 = *in;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --fac;

    /* Function Body */
    nf = fac[2];
    na = 1;
    l2 = *n;
    iw = *n;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	kh = nf - k1;
	ip = fac[kh + 3];
	l1 = l2 / ip;
	ido = *n / l2;
	idl1 = ido * l1;
	iw -= (ip - 1) * ido;
	na = 1 - na;
	if (ip != 4) {
	    goto L102;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	if (na != 0) {
	    goto L101;
	}
	mradf4_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2], &wa[ix3]);
	goto L110;
L101:
	mradf4_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2], &wa[ix3]);
	goto L110;
L102:
	if (ip != 2) {
	    goto L104;
	}
	if (na != 0) {
	    goto L103;
	}
	mradf2_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw]);
	goto L110;
L103:
	mradf2_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw]);
	goto L110;
L104:
	if (ip != 3) {
	    goto L106;
	}
	ix2 = iw + ido;
	if (na != 0) {
	    goto L105;
	}
	mradf3_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2]);
	goto L110;
L105:
	mradf3_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2]);
	goto L110;
L106:
	if (ip != 5) {
	    goto L108;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	ix4 = ix3 + ido;
	if (na != 0) {
	    goto L107;
	}
	mradf5_d(m, &ido, &l1, &c__[c_offset], im, in, &ch[ch_offset], &c__1,
		m, &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
	goto L110;
L107:
	mradf5_d(m, &ido, &l1, &ch[ch_offset], &c__1, m, &c__[c_offset], im,
		in, &wa[iw], &wa[ix2], &wa[ix3], &wa[ix4]);
	goto L110;
L108:
	if (ido == 1) {
	    na = 1 - na;
	}
	if (na != 0) {
	    goto L109;
	}
	mradfg_d(m, &ido, &ip, &l1, &idl1, &c__[c_offset], &c__[c_offset], &
		c__[c_offset], im, in, &ch[ch_offset], &ch[ch_offset], &c__1,
		m, &wa[iw]);
	na = 1;
	goto L110;
L109:
	mradfg_d(m, &ido, &ip, &l1, &idl1, &ch[ch_offset], &ch[ch_offset], &ch[
		ch_offset], &c__1, m, &c__[c_offset], &c__[c_offset], im, in,
		&wa[iw]);
	na = 0;
L110:
	l2 = l1;
/* L111: */
    }
    sn = 1.0 / *n;
    tsn = 2.0 / *n;
    tsnm = -tsn;
    modn = *n % 2;
    nl = *n - 2;
    if (modn != 0) {
	nl = *n - 1;
    }
    if (na != 0) {
	goto L120;
    }
    m2 = 1 - *im;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	m2 += *im;
	c__[m2 + c_dim1] = sn * ch[i__ + ch_dim1];
/* L117: */
    }
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	m2 = 1 - *im;
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    m2 += *im;
	    c__[m2 + j * c_dim1] = tsn * ch[i__ + j * ch_dim1];
	    c__[m2 + (j + 1) * c_dim1] = tsnm * ch[i__ + (j + 1) * ch_dim1];
/* L118: */
	}
    }
    if (modn != 0) {
	return 0;
    }
    m2 = 1 - *im;
    i__2 = *m;
    for (i__ = 1; i__ <= i__2; ++i__) {
	m2 += *im;
	c__[m2 + *n * c_dim1] = sn * ch[i__ + *n * ch_dim1];
/* L119: */
    }
    return 0;
L120:
    m2 = 1 - *im;
    i__2 = *m;
    for (i__ = 1; i__ <= i__2; ++i__) {
	m2 += *im;
	c__[m2 + c_dim1] = sn * c__[m2 + c_dim1];
/* L121: */
    }
    i__2 = nl;
    for (j = 2; j <= i__2; j += 2) {
	m2 = 1 - *im;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    m2 += *im;
	    c__[m2 + j * c_dim1] = tsn * c__[m2 + j * c_dim1];
	    c__[m2 + (j + 1) * c_dim1] = tsnm * c__[m2 + (j + 1) * c_dim1];
/* L122: */
	}
    }
    if (modn != 0) {
	return 0;
    }
    m2 = 1 - *im;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	m2 += *im;
	c__[m2 + *n * c_dim1] = sn * c__[m2 + *n * c_dim1];
/* L123: */
    }
    return 0;
} /* mrftf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int mrfti1_d(int *n, double *wa, double *fac)
{
    /* Initialized data */

     int ntryh[4] = { 4,2,3,5 };

    /* System generated locals */
    int i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k1, l1, l2, ib;
     double fi;
     int ld, ii, nf, ip, nl, is, nq, nr;
     double arg;
     int ido, ipm;
     double tpi;
     int nfm1;
     double argh;
     int ntry;
     double argld;

    /* Parameter adjustments */
    --wa;
    --fac;

    /* Function Body */

    nl = *n;
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
    fac[nf + 2] = (double) ntry;
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
	fac[ib + 2] = fac[ib + 1];
/* L106: */
    }
    fac[3] = 2.0;
L107:
    if (nl != 1) {
	goto L104;
    }
    fac[1] = (double) (*n);
    fac[2] = (double) nf;
    tpi = atan(1.) * 8.;
    argh = tpi / (double) (*n);
    is = 0;
    nfm1 = nf - 1;
    l1 = 1;
    if (nfm1 == 0) {
	return 0;
    }
    i__1 = nfm1;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	ld = 0;
	l2 = l1 * ip;
	ido = *n / l2;
	ipm = ip - 1;
	i__2 = ipm;
	for (j = 1; j <= i__2; ++j) {
	    ld += l1;
	    i__ = is;
	    argld = (double) ld * argh;
	    fi = 0.0;
	    i__3 = ido;
	    for (ii = 3; ii <= i__3; ii += 2) {
		i__ += 2;
		fi += 1.0;
		arg = fi * argld;
		wa[i__ - 1] = cos(arg);
		wa[i__] = sin(arg);
/* L108: */
	    }
	    is += ido;
/* L109: */
	}
	l1 = l2;
/* L110: */
    }
    return 0;
} /* mrfti1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int msntb1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *xh, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, xh_dim1, xh_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1;
     double t1, t2;
     int kc, lj, np1, ns2, ier1, modn, lnxh, lnwk, lnsv;
     double fnp1s4, xhold, srt3s2;

    /* Parameter adjustments */
    xh_dim1 = *lot;
    xh_offset = 1 + xh_dim1;
    xh -= xh_offset;
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --dsum;

    /* Function Body */
    *ier = 0;
    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L200;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L102:
    srt3s2 = sqrt(3.0) / 2.0;
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	xhold = srt3s2 * (x[m + x_dim1] + x[m + (x_dim1 << 1)]);
	x[m + (x_dim1 << 1)] = srt3s2 * (x[m + x_dim1] - x[m + (x_dim1 << 1)])
		;
	x[m + x_dim1] = xhold;
/* L112: */
    }
    goto L200;
L103:
    np1 = *n + 1;
    ns2 = *n / 2;
    i__2 = ns2;
    for (k = 1; k <= i__2; ++k) {
	kc = np1 - k;
	m1 = 0;
	i__1 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	    ++m1;
	    t1 = x[m + k * x_dim1] - x[m + kc * x_dim1];
	    t2 = wsave[k] * (x[m + k * x_dim1] + x[m + kc * x_dim1]);
	    xh[m1 + (k + 1) * xh_dim1] = t1 + t2;
	    xh[m1 + (kc + 1) * xh_dim1] = t2 - t1;
/* L114: */
	}
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    m1 = 0;
    i__2 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	++m1;
	xh[m1 + (ns2 + 2) * xh_dim1] = x[m + (ns2 + 1) * x_dim1] * 4.0;
/* L123: */
    }
L124:
    i__3 = *lot;
    for (m = 1; m <= i__3; ++m) {
	xh[m + xh_dim1] = 0.0;
/* L127: */
    }
    lnxh = *lot - 1 + *lot * (np1 - 1) + 1;
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    lnwk = *lot * np1;

    rfftmf_d(lot, &c__1, &np1, lot, &xh[xh_offset], &lnxh, &wsave[ns2 + 1], &
	    lnsv, work, &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MSNTB1", &c_n5, (int)6);
	goto L200;
    }

    if (np1 % 2 != 0) {
	goto L30;
    }
    i__3 = *lot;
    for (m = 1; m <= i__3; ++m) {
	xh[m + np1 * xh_dim1] += xh[m + np1 * xh_dim1];
/* L20: */
    }
L30:
    fnp1s4 = (double) np1 / 4.0;
    m1 = 0;
    i__3 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	++m1;
	x[m + x_dim1] = fnp1s4 * xh[m1 + xh_dim1];
	dsum[m1] = x[m + x_dim1];
/* L125: */
    }
    i__2 = *n;
    for (i__ = 3; i__ <= i__2; i__ += 2) {
	m1 = 0;
	i__3 = lj;
	i__1 = *jump;
	for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	    ++m1;
	    x[m + (i__ - 1) * x_dim1] = fnp1s4 * xh[m1 + i__ * xh_dim1];
	    dsum[m1] += fnp1s4 * xh[m1 + (i__ - 1) * xh_dim1];
	    x[m + i__ * x_dim1] = dsum[m1];
/* L115: */
	}
/* L105: */
    }
    if (modn != 0) {
	goto L200;
    }
    m1 = 0;
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	++m1;
	x[m + *n * x_dim1] = fnp1s4 * xh[m1 + (*n + 1) * xh_dim1];
/* L116: */
    }

L200:
    return 0;
} /* msntb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int msntf1_d(int *lot, int *jump, int *n, int *inc, double *x, double *wsave, double *dsum, double *xh, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, xh_dim1, xh_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, k, m, m1;
     double t1, t2;
     int kc, lj, np1, ns2, ier1, modn, lnxh, lnwk, lnsv;
     double sfnp1, xhold, ssqrt3;

    /* Parameter adjustments */
    xh_dim1 = *lot;
    xh_offset = 1 + xh_dim1;
    xh -= xh_offset;
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --dsum;

    /* Function Body */
    *ier = 0;
    lj = (*lot - 1) * *jump + 1;
    if ((i__1 = *n - 2) < 0) {
	goto L101;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L102:
    ssqrt3 = 1.0 / sqrt(3.0);
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	xhold = ssqrt3 * (x[m + x_dim1] + x[m + (x_dim1 << 1)]);
	x[m + (x_dim1 << 1)] = ssqrt3 * (x[m + x_dim1] - x[m + (x_dim1 << 1)])
		;
	x[m + x_dim1] = xhold;
/* L112: */
    }
L101:
    goto L200;
L103:
    np1 = *n + 1;
    ns2 = *n / 2;
    i__2 = ns2;
    for (k = 1; k <= i__2; ++k) {
	kc = np1 - k;
	m1 = 0;
	i__1 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	    ++m1;
	    t1 = x[m + k * x_dim1] - x[m + kc * x_dim1];
	    t2 = wsave[k] * (x[m + k * x_dim1] + x[m + kc * x_dim1]);
	    xh[m1 + (k + 1) * xh_dim1] = t1 + t2;
	    xh[m1 + (kc + 1) * xh_dim1] = t2 - t1;
/* L114: */
	}
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    m1 = 0;
    i__2 = lj;
    i__3 = *jump;
    for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	++m1;
	xh[m1 + (ns2 + 2) * xh_dim1] = x[m + (ns2 + 1) * x_dim1] * 4.0;
/* L123: */
    }
L124:
    i__3 = *lot;
    for (m = 1; m <= i__3; ++m) {
	xh[m + xh_dim1] = 0.0;
/* L127: */
    }
    lnxh = *lot - 1 + *lot * (np1 - 1) + 1;
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    lnwk = *lot * np1;

    rfftmf_d(lot, &c__1, &np1, lot, &xh[xh_offset], &lnxh, &wsave[ns2 + 1], &
	    lnsv, work, &lnwk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("MSNTF1", &c_n5, (int)6);
	goto L200;
    }

    if (np1 % 2 != 0) {
	goto L30;
    }
    i__3 = *lot;
    for (m = 1; m <= i__3; ++m) {
	xh[m + np1 * xh_dim1] += xh[m + np1 * xh_dim1];
/* L20: */
    }
L30:
    sfnp1 = 1.0 / (double) np1;
    m1 = 0;
    i__3 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	++m1;
	x[m + x_dim1] = xh[m1 + xh_dim1] * .5;
	dsum[m1] = x[m + x_dim1];
/* L125: */
    }
    i__2 = *n;
    for (i__ = 3; i__ <= i__2; i__ += 2) {
	m1 = 0;
	i__3 = lj;
	i__1 = *jump;
	for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	    ++m1;
	    x[m + (i__ - 1) * x_dim1] = xh[m1 + i__ * xh_dim1] * .5;
	    dsum[m1] += xh[m1 + (i__ - 1) * xh_dim1] * .5;
	    x[m + i__ * x_dim1] = dsum[m1];
/* L115: */
	}
/* L105: */
    }
    if (modn != 0) {
	goto L200;
    }
    m1 = 0;
    i__2 = lj;
    i__1 = *jump;
    for (m = 1; i__1 < 0 ? m >= i__2 : m <= i__2; m += i__1) {
	++m1;
	x[m + *n * x_dim1] = xh[m1 + (*n + 1) * xh_dim1] * .5;
/* L116: */
    }
L200:
    return 0;
} /* msntf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f2kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2;

    /* Local variables */
     int i__, k, ic, idp2;

    /* Parameter adjustments */
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 3);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k + ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 1) + 1) *
		 cc_dim2 + 1) * cc_dim1 + 1] + cc[(*ido + ((k << 1) + 2) *
		cc_dim2) * cc_dim1 + 1];
	ch[((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 1)
		 + 1) * cc_dim2 + 1) * cc_dim1 + 1] - cc[(*ido + ((k << 1) +
		2) * cc_dim2) * cc_dim1 + 1];
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + ((k << 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1
		    + ((k << 1) + 2) * cc_dim2) * cc_dim1 + 1];
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + ((k
		    << 1) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(ic + ((k << 1)
		    + 2) * cc_dim2) * cc_dim1 + 1];
	    ch[(i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] =
		    wa1[i__ - 2] * (cc[(i__ - 1 + ((k << 1) + 1) * cc_dim2) *
		    cc_dim1 + 1] - cc[(ic - 1 + ((k << 1) + 2) * cc_dim2) *
		    cc_dim1 + 1]) - wa1[i__ - 1] * (cc[(i__ + ((k << 1) + 1) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + ((k << 1) + 2) *
		    cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = wa1[
		    i__ - 2] * (cc[(i__ + ((k << 1) + 1) * cc_dim2) * cc_dim1
		    + 1] + cc[(ic + ((k << 1) + 2) * cc_dim2) * cc_dim1 + 1])
		    + wa1[i__ - 1] * (cc[(i__ - 1 + ((k << 1) + 1) * cc_dim2)
		    * cc_dim1 + 1] - cc[(ic - 1 + ((k << 1) + 2) * cc_dim2) *
		    cc_dim1 + 1]);
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(*ido + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(*ido + ((k <<
		 1) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(*ido + ((k << 1) + 1)
		 * cc_dim2) * cc_dim1 + 1];
	ch[(*ido + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = -(cc[(((k
		<< 1) + 2) * cc_dim2 + 1) * cc_dim1 + 1] + cc[(((k << 1) + 2)
		* cc_dim2 + 1) * cc_dim1 + 1]);
/* L106: */
    }
L107:
    return 0;
} /* r1f2kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f2kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_dim3, cc_offset,
	     i__1, i__2;

    /* Local variables */
     int i__, k, ic, idp2;

    /* Parameter adjustments */
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 3);
    ch -= ch_offset;

    /* Function Body */
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(((k << 1) + 1) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		 cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1];
	ch[(*ido + ((k << 1) + 2) * ch_dim2) * ch_dim1 + 1] = cc[((k +
		cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + (cc_dim3 <<
		1)) * cc_dim2 + 1) * cc_dim1 + 1];
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ + ((k << 1) + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k
		    + cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__ - 2] * cc[
		    (i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1]);
	    ch[(ic + ((k << 1) + 2) * ch_dim2) * ch_dim1 + 1] = wa1[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		    - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] - cc[(i__ + (k + cc_dim3) *
		    cc_dim2) * cc_dim1 + 1];
	    ch[(i__ - 1 + ((k << 1) + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__
		    - 1 + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__
		    - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1]);
	    ch[(ic - 1 + ((k << 1) + 2) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] - (wa1[i__ -
		    2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1]);
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(((k << 1) + 2) * ch_dim2 + 1) * ch_dim1 + 1] = -cc[(*ido + (k + (
		cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1];
	ch[(*ido + ((k << 1) + 1) * ch_dim2) * ch_dim1 + 1] = cc[(*ido + (k +
		cc_dim3) * cc_dim2) * cc_dim1 + 1];
/* L106: */
    }
L107:
    return 0;
} /* r1f2kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f3kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic;
     double arg;
     int idp2;
     double taui, taur;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + (cc_dim2 << 2));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    arg = atan(1.0) * 8.0 / 3.0;
    taur = cos(arg);
    taui = sin(arg);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k + ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 3 + 1) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[(*ido + (k * 3 + 2) *
		cc_dim2) * cc_dim1 + 1] * 2.0;
	ch[((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 3 +
		1) * cc_dim2 + 1) * cc_dim1 + 1] + taur * 2.0 * cc[(*ido + (k
		* 3 + 2) * cc_dim2) * cc_dim1 + 1] - taui * 2.0 * cc[((k * 3
		+ 3) * cc_dim2 + 1) * cc_dim1 + 1];
	ch[((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 3 + 1)
		* cc_dim2 + 1) * cc_dim1 + 1] + taur * 2.0 * cc[(*ido + (k *
		3 + 2) * cc_dim2) * cc_dim1 + 1] + taui * 2.0 * cc[((k * 3 +
		3) * cc_dim2 + 1) * cc_dim1 + 1];
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + (k * 3 + 1) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ - 1
		    + (k * 3 + 3) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k
		    * 3 + 2) * cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k *
		     3 + 1) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ + (k * 3 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] =
		    wa1[i__ - 2] * (cc[(i__ - 1 + (k * 3 + 1) * cc_dim2) *
		    cc_dim1 + 1] + taur * (cc[(i__ - 1 + (k * 3 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - taui * (cc[(i__ + (k * 3 + 3) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 3 + 2) * cc_dim2)
		     * cc_dim1 + 1])) - wa1[i__ - 1] * (cc[(i__ + (k * 3 + 1)
		    * cc_dim2) * cc_dim1 + 1] + taur * (cc[(i__ + (k * 3 + 3)
		    * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + taui * (cc[(i__ - 1 + (k * 3 +
		    3) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = wa1[
		    i__ - 2] * (cc[(i__ + (k * 3 + 1) * cc_dim2) * cc_dim1 +
		    1] + taur * (cc[(i__ + (k * 3 + 3) * cc_dim2) * cc_dim1 +
		    1] - cc[(ic + (k * 3 + 2) * cc_dim2) * cc_dim1 + 1]) +
		    taui * (cc[(i__ - 1 + (k * 3 + 3) * cc_dim2) * cc_dim1 +
		    1] - cc[(ic - 1 + (k * 3 + 2) * cc_dim2) * cc_dim1 + 1]))
		    + wa1[i__ - 1] * (cc[(i__ - 1 + (k * 3 + 1) * cc_dim2) *
		    cc_dim1 + 1] + taur * (cc[(i__ - 1 + (k * 3 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - taui * (cc[(i__ + (k * 3 + 3) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 3 + 2) * cc_dim2)
		     * cc_dim1 + 1]));
	    ch[(i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[
		    i__ - 2] * (cc[(i__ - 1 + (k * 3 + 1) * cc_dim2) *
		    cc_dim1 + 1] + taur * (cc[(i__ - 1 + (k * 3 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + taui * (cc[(i__ + (k * 3 + 3) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 3 + 2) * cc_dim2)
		     * cc_dim1 + 1])) - wa2[i__ - 1] * (cc[(i__ + (k * 3 + 1)
		    * cc_dim2) * cc_dim1 + 1] + taur * (cc[(i__ + (k * 3 + 3)
		    * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - taui * (cc[(i__ - 1 + (k * 3 +
		    3) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[i__ -
		    2] * (cc[(i__ + (k * 3 + 1) * cc_dim2) * cc_dim1 + 1] +
		    taur * (cc[(i__ + (k * 3 + 3) * cc_dim2) * cc_dim1 + 1] -
		    cc[(ic + (k * 3 + 2) * cc_dim2) * cc_dim1 + 1]) - taui * (
		    cc[(i__ - 1 + (k * 3 + 3) * cc_dim2) * cc_dim1 + 1] - cc[(
		    ic - 1 + (k * 3 + 2) * cc_dim2) * cc_dim1 + 1])) + wa2[
		    i__ - 1] * (cc[(i__ - 1 + (k * 3 + 1) * cc_dim2) *
		    cc_dim1 + 1] + taur * (cc[(i__ - 1 + (k * 3 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 3 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + taui * (cc[(i__ + (k * 3 + 3) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 3 + 2) * cc_dim2)
		     * cc_dim1 + 1]));
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* r1f3kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f3kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_dim3, cc_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic;
     double arg;
     int idp2;
     double taui, taur;

    /* Parameter adjustments */
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + (ch_dim2 << 2));
    ch -= ch_offset;

    /* Function Body */
    arg = atan(1.0) * 8.0 / 3.0;
    taur = cos(arg);
    taui = sin(arg);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k * 3 + 1) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		cc_dim2 + 1) * cc_dim1 + 1] + (cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) * cc_dim2
		+ 1) * cc_dim1 + 1]);
	ch[((k * 3 + 3) * ch_dim2 + 1) * ch_dim1 + 1] = taui * (cc[((k +
		cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + (
		cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1 + 1]);
	ch[(*ido + (k * 3 + 2) * ch_dim2) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		 cc_dim2 + 1) * cc_dim1 + 1] + taur * (cc[((k + (cc_dim3 << 1)
		) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) *
		cc_dim2 + 1) * cc_dim1 + 1]);
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k * 3 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__ - 2]
		    * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ - 1 + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1]
		    * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k * 3 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__ - 2] * cc[(
		    i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1])
		    );
	    ch[(i__ - 1 + (k * 3 + 3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + taur * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa2[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    1])) + taui * (wa1[i__ - 2] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] - wa1[i__ - 1] * cc[(i__ -
		    1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - (wa2[
		    i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k + cc_dim3 *
		     3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(ic - 1 + (k * 3 + 2) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + taur * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa2[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 +
		    1])) - taui * (wa1[i__ - 2] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] - wa1[i__ - 1] * cc[(i__ -
		    1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - (wa2[
		    i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k + cc_dim3 *
		     3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k * 3 + 3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + taur * (wa1[i__ - 2]
		    * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		     - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1])
		    ) + taui * (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3)
		     * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] *
		     cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(ic + (k * 3 + 2) * ch_dim2) * ch_dim1 + 1] = taui * (wa2[i__
		    - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k + cc_dim3 * 3)
		    * cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 +
		    (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__
		    - 1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1])) - (cc[(i__ + (k + cc_dim3) * cc_dim2) *
		    cc_dim1 + 1] + taur * (wa1[i__ - 2] * cc[(i__ + (k + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - wa1[i__ - 1] *
		    cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 +
		    1] + (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1])));
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* r1f3kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f4kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic, idp2;
     double sqrt2;

    /* Parameter adjustments */
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 5);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    sqrt2 = sqrt(2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 2) +
		1) * cc_dim2 + 1) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 4) *
		 cc_dim2) * cc_dim1 + 1] - (cc[(*ido + ((k << 2) + 2) *
		cc_dim2) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 2) * cc_dim2)
		 * cc_dim1 + 1]);
	ch[((k + ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 2) + 1) *
		 cc_dim2 + 1) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 4) *
		cc_dim2) * cc_dim1 + 1] + (cc[(*ido + ((k << 2) + 2) *
		cc_dim2) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 2) * cc_dim2)
		 * cc_dim1 + 1]);
	ch[((k + (ch_dim3 << 2)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 2)
		 + 1) * cc_dim2 + 1) * cc_dim1 + 1] - cc[(*ido + ((k << 2) +
		4) * cc_dim2) * cc_dim1 + 1] + (cc[(((k << 2) + 3) * cc_dim2
		+ 1) * cc_dim1 + 1] + cc[(((k << 2) + 3) * cc_dim2 + 1) *
		cc_dim1 + 1]);
	ch[((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(((k << 2)
		 + 1) * cc_dim2 + 1) * cc_dim1 + 1] - cc[(*ido + ((k << 2) +
		4) * cc_dim2) * cc_dim1 + 1] - (cc[(((k << 2) + 3) * cc_dim2
		+ 1) * cc_dim1 + 1] + cc[(((k << 2) + 3) * cc_dim2 + 1) *
		cc_dim1 + 1]);
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + ((k << 2) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1
		    + ((k << 2) + 4) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ - 1
		    + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 +
		    ((k << 2) + 2) * cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + ((k
		    << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(ic + ((k << 2)
		    + 4) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ + ((k << 2) + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + ((k << 2) + 2) *
		    cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] =
		    wa1[i__ - 2] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2) *
		    cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) *
		    cc_dim1 + 1] - (cc[(i__ + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic + ((k << 2) + 2) * cc_dim2) *
		    cc_dim1 + 1])) - wa1[i__ - 1] * (cc[(i__ + ((k << 2) + 1)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + ((k << 2) + 4) *
		    cc_dim2) * cc_dim1 + 1] + (cc[(i__ - 1 + ((k << 2) + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 2) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = wa1[
		    i__ - 2] * (cc[(i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1
		    + 1] + cc[(ic + ((k << 2) + 4) * cc_dim2) * cc_dim1 + 1]
		    + (cc[(i__ - 1 + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1]
		    - cc[(ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1 + 1]))
		    + wa1[i__ - 1] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2)
		    * cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) *
		    cc_dim1 + 1] - (cc[(i__ + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic + ((k << 2) + 2) * cc_dim2) *
		    cc_dim1 + 1]));
	    ch[(i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[
		    i__ - 2] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) *
		    cc_dim1 + 1] - (cc[(i__ - 1 + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic - 1 + ((k << 2) + 2) * cc_dim2) *
		    cc_dim1 + 1])) - wa2[i__ - 1] * (cc[(i__ + ((k << 2) + 1)
		    * cc_dim2) * cc_dim1 + 1] - cc[(ic + ((k << 2) + 4) *
		    cc_dim2) * cc_dim1 + 1] - (cc[(i__ + ((k << 2) + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic + ((k << 2) + 2) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[i__ -
		    2] * (cc[(i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1 + 1]
		    - cc[(ic + ((k << 2) + 4) * cc_dim2) * cc_dim1 + 1] - (cc[
		    (i__ + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    + ((k << 2) + 2) * cc_dim2) * cc_dim1 + 1])) + wa2[i__ -
		    1] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2) * cc_dim1 +
		    1] + cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) * cc_dim1 + 1]
		     - (cc[(i__ - 1 + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1]
		     + cc[(ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1 + 1]))
		    ;
	    ch[(i__ - 1 + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1 + 1] =
		    wa3[i__ - 2] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2) *
		    cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) *
		    cc_dim1 + 1] + (cc[(i__ + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic + ((k << 2) + 2) * cc_dim2) *
		    cc_dim1 + 1])) - wa3[i__ - 1] * (cc[(i__ + ((k << 2) + 1)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + ((k << 2) + 4) *
		    cc_dim2) * cc_dim1 + 1] - (cc[(i__ - 1 + ((k << 2) + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 2) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1 + 1] = wa3[
		    i__ - 2] * (cc[(i__ + ((k << 2) + 1) * cc_dim2) * cc_dim1
		    + 1] + cc[(ic + ((k << 2) + 4) * cc_dim2) * cc_dim1 + 1]
		    - (cc[(i__ - 1 + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1]
		    - cc[(ic - 1 + ((k << 2) + 2) * cc_dim2) * cc_dim1 + 1]))
		    + wa3[i__ - 1] * (cc[(i__ - 1 + ((k << 2) + 1) * cc_dim2)
		    * cc_dim1 + 1] - cc[(ic - 1 + ((k << 2) + 4) * cc_dim2) *
		    cc_dim1 + 1] + (cc[(i__ + ((k << 2) + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic + ((k << 2) + 2) * cc_dim2) *
		    cc_dim1 + 1]));
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(*ido + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(*ido + ((k <<
		 2) + 1) * cc_dim2) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 3)
		 * cc_dim2) * cc_dim1 + 1] + (cc[(*ido + ((k << 2) + 1) *
		cc_dim2) * cc_dim1 + 1] + cc[(*ido + ((k << 2) + 3) * cc_dim2)
		 * cc_dim1 + 1]);
	ch[(*ido + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = sqrt2 * (
		cc[(*ido + ((k << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(*
		ido + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1] - (cc[(((k <<
		2) + 2) * cc_dim2 + 1) * cc_dim1 + 1] + cc[(((k << 2) + 4) *
		cc_dim2 + 1) * cc_dim1 + 1]));
	ch[(*ido + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = cc[(((k << 2)
		 + 4) * cc_dim2 + 1) * cc_dim1 + 1] - cc[(((k << 2) + 2) *
		cc_dim2 + 1) * cc_dim1 + 1] + (cc[(((k << 2) + 4) * cc_dim2 +
		1) * cc_dim1 + 1] - cc[(((k << 2) + 2) * cc_dim2 + 1) *
		cc_dim1 + 1]);
	ch[(*ido + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1 + 1] = -sqrt2 * (
		cc[(*ido + ((k << 2) + 1) * cc_dim2) * cc_dim1 + 1] - cc[(*
		ido + ((k << 2) + 3) * cc_dim2) * cc_dim1 + 1] + (cc[(((k <<
		2) + 2) * cc_dim2 + 1) * cc_dim1 + 1] + cc[(((k << 2) + 4) *
		cc_dim2 + 1) * cc_dim1 + 1]));
/* L106: */
    }
L107:
    return 0;
} /* r1f4kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f4kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic, idp2;
     double hsqt2;

    /* Parameter adjustments */
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 5);
    ch -= ch_offset;

    /* Function Body */
    hsqt2 = sqrt(2.0) / 2.0;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(((k << 2) + 1) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k + (cc_dim3
		<< 1)) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 2)
		) * cc_dim2 + 1) * cc_dim1 + 1] + (cc[((k + cc_dim3) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) * cc_dim2
		+ 1) * cc_dim1 + 1]);
	ch[(*ido + ((k << 2) + 4) * ch_dim2) * ch_dim1 + 1] = cc[((k +
		cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3)
		 * cc_dim2 + 1) * cc_dim1 + 1] - (cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 2)) *
		cc_dim2 + 1) * cc_dim1 + 1]);
	ch[(*ido + ((k << 2) + 2) * ch_dim2) * ch_dim1 + 1] = cc[((k +
		cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + cc_dim3 * 3)
		 * cc_dim2 + 1) * cc_dim1 + 1];
	ch[(((k << 2) + 3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k + (cc_dim3
		<< 2)) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + (cc_dim3 << 1)
		) * cc_dim2 + 1) * cc_dim1 + 1];
/* L101: */
    }
    if ((i__1 = *ido - 2) < 0) {
	goto L107;
    } else if (i__1 == 0) {
	goto L105;
    } else {
	goto L102;
    }
L102:
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + ((k << 2) + 1) * ch_dim2) * ch_dim1 + 1] = wa1[i__
		    - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] * cc[(i__ -
		    1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] + wa3[
		    i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) *
		    cc_dim1 + 1]) + (cc[(i__ - 1 + (k + cc_dim3) * cc_dim2) *
		    cc_dim1 + 1] + (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3
		    * 3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ +
		    (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(ic - 1 + ((k << 2) + 4) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa2[i__ -
		    2] * cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1
		    + 1] + wa2[i__ - 1] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1]) - (wa1[i__ - 2] * cc[(i__ - 1 + (
		    k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__ -
		    1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] + (wa3[i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 2))
		    * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 1] * cc[(i__ + (k +
		    (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + ((k << 2) + 1) * ch_dim2) * ch_dim1 + 1] = wa1[i__ - 2]
		    * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		     - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] * cc[(i__ + (k + (
		    cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] - wa3[i__ - 1] *
		    cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 +
		    1]) + (cc[(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1]
		    + (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) *
		     cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k + cc_dim3
		    * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(ic + ((k << 2) + 4) * ch_dim2) * ch_dim1 + 1] = wa1[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		    - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] * cc[(i__ + (k + (
		    cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] - wa3[i__ - 1] *
		    cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 +
		    1]) - (cc[(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1]
		    + (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) *
		     cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k + cc_dim3
		    * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ - 1 + ((k << 2) + 3) * ch_dim2) * ch_dim1 + 1] = wa1[i__
		    - 2] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1] - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3
		    << 1)) * cc_dim2) * cc_dim1 + 1] - (wa3[i__ - 2] * cc[(
		    i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] -
		    wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1]) + (cc[(i__ - 1 + (k + cc_dim3) *
		    cc_dim2) * cc_dim1 + 1] - (wa2[i__ - 2] * cc[(i__ - 1 + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1]
		    * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(ic - 1 + ((k << 2) + 2) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] - (wa2[i__ -
		    2] * cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) * cc_dim1
		    + 1] + wa2[i__ - 1] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1]) - (wa1[i__ - 2] * cc[(i__ + (k +
		    (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - wa1[i__ - 1] *
		     cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] - (wa3[i__ - 2] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1] - wa3[i__ - 1] * cc[(i__ - 1 + (k
		    + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + ((k << 2) + 3) * ch_dim2) * ch_dim1 + 1] = wa3[i__ - 2]
		    * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1
		    + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 + (
		    k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__ -
		    1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1]) + (cc[(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1]
		     - (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2)
		    * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1]));
	    ch[(ic + ((k << 2) + 2) * ch_dim2) * ch_dim1 + 1] = wa3[i__ - 2] *
		     cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1
		    + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 + (
		    k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__ -
		    1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1]) - (cc[(i__ + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1]
		     - (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2)
		    * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1]));
/* L103: */
	}
/* L104: */
    }
    if (*ido % 2 == 1) {
	return 0;
    }
L105:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[(*ido + ((k << 2) + 1) * ch_dim2) * ch_dim1 + 1] = hsqt2 * (cc[(*
		ido + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - cc[(*
		ido + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]) + cc[(*
		ido + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1];
	ch[(*ido + ((k << 2) + 3) * ch_dim2) * ch_dim1 + 1] = cc[(*ido + (k +
		cc_dim3) * cc_dim2) * cc_dim1 + 1] - hsqt2 * (cc[(*ido + (k +
		(cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - cc[(*ido + (k + (
		cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]);
	ch[(((k << 2) + 2) * ch_dim2 + 1) * ch_dim1 + 1] = -hsqt2 * (cc[(*ido
		+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + cc[(*ido +
		(k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]) - cc[(*ido + (
		k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
	ch[(((k << 2) + 4) * ch_dim2 + 1) * ch_dim1 + 1] = -hsqt2 * (cc[(*ido
		+ (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + cc[(*ido +
		(k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]) + cc[(*ido + (
		k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1];
/* L106: */
    }
L107:
    return 0;
} /* r1f4kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f5kb_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3, double *wa4)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_offset, ch_dim1, ch_dim2, ch_dim3, ch_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic;
     double arg, ti11, ti12, tr11, tr12;
     int idp2;

    /* Parameter adjustments */
    --wa4;
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * 6);
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    arg = atan(1.0) * 8.0 / 5.0;
    tr11 = cos(arg);
    ti11 = sin(arg);
    tr12 = cos(arg * 2.0);
    ti12 = sin(arg * 2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k + ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 5 + 1) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[(*ido + (k * 5 + 2) *
		cc_dim2) * cc_dim1 + 1] * 2.0 + cc[(*ido + (k * 5 + 4) *
		cc_dim2) * cc_dim1 + 1] * 2.0;
	ch[((k + (ch_dim3 << 1)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 5 +
		1) * cc_dim2 + 1) * cc_dim1 + 1] + tr11 * 2.0 * cc[(*ido + (k
		* 5 + 2) * cc_dim2) * cc_dim1 + 1] + tr12 * 2.0 * cc[(*ido + (
		k * 5 + 4) * cc_dim2) * cc_dim1 + 1] - (ti11 * 2.0 * cc[((k *
		5 + 3) * cc_dim2 + 1) * cc_dim1 + 1] + ti12 * 2.0 * cc[((k *
		5 + 5) * cc_dim2 + 1) * cc_dim1 + 1]);
	ch[((k + ch_dim3 * 3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 5 + 1)
		* cc_dim2 + 1) * cc_dim1 + 1] + tr12 * 2.0 * cc[(*ido + (k *
		5 + 2) * cc_dim2) * cc_dim1 + 1] + tr11 * 2.0 * cc[(*ido + (k
		* 5 + 4) * cc_dim2) * cc_dim1 + 1] - (ti12 * 2.0 * cc[((k * 5
		+ 3) * cc_dim2 + 1) * cc_dim1 + 1] - ti11 * 2.0 * cc[((k * 5
		+ 5) * cc_dim2 + 1) * cc_dim1 + 1]);
	ch[((k + (ch_dim3 << 2)) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 5 +
		1) * cc_dim2 + 1) * cc_dim1 + 1] + tr12 * 2.0 * cc[(*ido + (k
		* 5 + 2) * cc_dim2) * cc_dim1 + 1] + tr11 * 2.0 * cc[(*ido + (
		k * 5 + 4) * cc_dim2) * cc_dim1 + 1] + (ti12 * 2.0 * cc[((k *
		5 + 3) * cc_dim2 + 1) * cc_dim1 + 1] - ti11 * 2.0 * cc[((k *
		5 + 5) * cc_dim2 + 1) * cc_dim1 + 1]);
	ch[((k + ch_dim3 * 5) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k * 5 + 1)
		* cc_dim2 + 1) * cc_dim1 + 1] + tr11 * 2.0 * cc[(*ido + (k *
		5 + 2) * cc_dim2) * cc_dim1 + 1] + tr12 * 2.0 * cc[(*ido + (k
		* 5 + 4) * cc_dim2) * cc_dim1 + 1] + (ti11 * 2.0 * cc[((k * 5
		+ 3) * cc_dim2 + 1) * cc_dim1 + 1] + ti12 * 2.0 * cc[((k * 5
		+ 5) * cc_dim2 + 1) * cc_dim1 + 1]);
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ -
		    1 + (k * 5 + 1) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ - 1
		    + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k
		    * 5 + 2) * cc_dim2) * cc_dim1 + 1]) + (cc[(i__ - 1 + (k *
		    5 + 5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 +
		    4) * cc_dim2) * cc_dim1 + 1]);
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k *
		     5 + 1) * cc_dim2) * cc_dim1 + 1] + (cc[(i__ + (k * 5 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + (cc[(i__ + (k * 5 + 5) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 4) * cc_dim2)
		    * cc_dim1 + 1]);
	    ch[(i__ - 1 + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] =
		    wa1[i__ - 2] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr11 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr12 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) - (ti11 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]))) - wa1[i__ - 1] * (cc[(i__ + (k * 5 + 1)
		     * cc_dim2) * cc_dim1 + 1] + tr11 * (cc[(i__ + (k * 5 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]) + (ti11 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k + (ch_dim3 << 1)) * ch_dim2) * ch_dim1 + 1] = wa1[
		    i__ - 2] * (cc[(i__ + (k * 5 + 1) * cc_dim2) * cc_dim1 +
		    1] + tr11 * (cc[(i__ + (k * 5 + 3) * cc_dim2) * cc_dim1 +
		    1] - cc[(ic + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) +
		    tr12 * (cc[(i__ + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] -
		    cc[(ic + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]) + (ti11 *
		    (cc[(i__ - 1 + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] - cc[
		    (ic - 1 + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) + ti12 *
		    (cc[(i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[
		    (ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]))) + wa1[
		    i__ - 1] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr11 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr12 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) - (ti11 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1])));
	    ch[(i__ - 1 + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[
		    i__ - 2] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr12 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr11 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) - (ti12 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]))) - wa2[i__ - 1] * (cc[(i__ + (k * 5 + 1)
		     * cc_dim2) * cc_dim1 + 1] + tr12 * (cc[(i__ + (k * 5 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]) + (ti12 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k + ch_dim3 * 3) * ch_dim2) * ch_dim1 + 1] = wa2[i__ -
		    2] * (cc[(i__ + (k * 5 + 1) * cc_dim2) * cc_dim1 + 1] +
		    tr12 * (cc[(i__ + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] -
		    cc[(ic + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) + tr11 * (
		    cc[(i__ + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]) + (ti12 * (cc[(
		    i__ - 1 + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    - 1 + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[
		    (i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]))) + wa2[i__
		    - 1] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) * cc_dim1 +
		    1] + tr12 * (cc[(i__ - 1 + (k * 5 + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) * cc_dim2) *
		    cc_dim1 + 1]) + tr11 * (cc[(i__ - 1 + (k * 5 + 5) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) - (ti12 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1])));
	    ch[(i__ - 1 + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1 + 1] =
		    wa3[i__ - 2] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr12 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr11 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) + (ti12 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]))) - wa3[i__ - 1] * (cc[(i__ + (k * 5 + 1)
		     * cc_dim2) * cc_dim1 + 1] + tr12 * (cc[(i__ + (k * 5 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]) - (ti12 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k + (ch_dim3 << 2)) * ch_dim2) * ch_dim1 + 1] = wa3[
		    i__ - 2] * (cc[(i__ + (k * 5 + 1) * cc_dim2) * cc_dim1 +
		    1] + tr12 * (cc[(i__ + (k * 5 + 3) * cc_dim2) * cc_dim1 +
		    1] - cc[(ic + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) +
		    tr11 * (cc[(i__ + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] -
		    cc[(ic + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]) - (ti12 *
		    (cc[(i__ - 1 + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] - cc[
		    (ic - 1 + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) - ti11 *
		    (cc[(i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[
		    (ic - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]))) + wa3[
		    i__ - 1] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr12 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr11 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) + (ti12 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) - ti11 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1])));
	    ch[(i__ - 1 + (k + ch_dim3 * 5) * ch_dim2) * ch_dim1 + 1] = wa4[
		    i__ - 2] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) *
		    cc_dim1 + 1] + tr11 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr12 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) + (ti11 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]))) - wa4[i__ - 1] * (cc[(i__ + (k * 5 + 1)
		     * cc_dim2) * cc_dim1 + 1] + tr11 * (cc[(i__ + (k * 5 + 3)
		     * cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + tr12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] - cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1]) - (ti11 * (cc[(i__ - 1 + (k * 5 + 3) *
		    cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ - 1 + (k * 5 +
		    5) * cc_dim2) * cc_dim1 + 1] - cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k + ch_dim3 * 5) * ch_dim2) * ch_dim1 + 1] = wa4[i__ -
		    2] * (cc[(i__ + (k * 5 + 1) * cc_dim2) * cc_dim1 + 1] +
		    tr11 * (cc[(i__ + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] -
		    cc[(ic + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) + tr12 * (
		    cc[(i__ + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]) - (ti11 * (cc[(
		    i__ - 1 + (k * 5 + 3) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    - 1 + (k * 5 + 2) * cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[
		    (i__ - 1 + (k * 5 + 5) * cc_dim2) * cc_dim1 + 1] - cc[(ic
		    - 1 + (k * 5 + 4) * cc_dim2) * cc_dim1 + 1]))) + wa4[i__
		    - 1] * (cc[(i__ - 1 + (k * 5 + 1) * cc_dim2) * cc_dim1 +
		    1] + tr11 * (cc[(i__ - 1 + (k * 5 + 3) * cc_dim2) *
		    cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 2) * cc_dim2) *
		    cc_dim1 + 1]) + tr12 * (cc[(i__ - 1 + (k * 5 + 5) *
		    cc_dim2) * cc_dim1 + 1] + cc[(ic - 1 + (k * 5 + 4) *
		    cc_dim2) * cc_dim1 + 1]) + (ti11 * (cc[(i__ + (k * 5 + 3)
		    * cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 2) *
		    cc_dim2) * cc_dim1 + 1]) + ti12 * (cc[(i__ + (k * 5 + 5) *
		     cc_dim2) * cc_dim1 + 1] + cc[(ic + (k * 5 + 4) * cc_dim2)
		     * cc_dim1 + 1])));
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* r1f5kb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1f5kf_d(int *ido, int *l1, double *cc, int *in1, double *ch, int *in2, double *wa1, double *wa2, double *wa3, double *wa4)
{
    /* System generated locals */
    int cc_dim1, cc_dim2, cc_dim3, cc_offset, ch_dim1, ch_dim2, ch_offset,
	     i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, k, ic;
     double arg, ti11, ti12, tr11, tr12;
     int idp2;

    /* Parameter adjustments */
    --wa4;
    --wa3;
    --wa2;
    --wa1;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *l1;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * 6);
    ch -= ch_offset;

    /* Function Body */
    arg = atan(1.0) * 8.0 / 5.0;
    tr11 = cos(arg);
    ti11 = sin(arg);
    tr12 = cos(arg * 2.0);
    ti12 = sin(arg * 2.0);
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	ch[((k * 5 + 1) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		cc_dim2 + 1) * cc_dim1 + 1] + (cc[((k + cc_dim3 * 5) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1]) + (cc[((k + (cc_dim3 << 2)) *
		cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) * cc_dim2
		+ 1) * cc_dim1 + 1]);
	ch[(*ido + (k * 5 + 2) * ch_dim2) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		 cc_dim2 + 1) * cc_dim1 + 1] + tr11 * (cc[((k + cc_dim3 * 5) *
		 cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1]) + tr12 * (cc[((k + (cc_dim3 << 2)
		) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) *
		cc_dim2 + 1) * cc_dim1 + 1]);
	ch[((k * 5 + 3) * ch_dim2 + 1) * ch_dim1 + 1] = ti11 * (cc[((k +
		cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + (
		cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1 + 1]) + ti12 * (cc[((
		k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k +
		cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1 + 1]);
	ch[(*ido + (k * 5 + 4) * ch_dim2) * ch_dim1 + 1] = cc[((k + cc_dim3) *
		 cc_dim2 + 1) * cc_dim1 + 1] + tr12 * (cc[((k + cc_dim3 * 5) *
		 cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + (cc_dim3 << 1)) *
		cc_dim2 + 1) * cc_dim1 + 1]) + tr11 * (cc[((k + (cc_dim3 << 2)
		) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((k + cc_dim3 * 3) *
		cc_dim2 + 1) * cc_dim1 + 1]);
	ch[((k * 5 + 5) * ch_dim2 + 1) * ch_dim1 + 1] = ti12 * (cc[((k +
		cc_dim3 * 5) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k + (
		cc_dim3 << 1)) * cc_dim2 + 1) * cc_dim1 + 1]) - ti11 * (cc[((
		k + (cc_dim3 << 2)) * cc_dim2 + 1) * cc_dim1 + 1] - cc[((k +
		cc_dim3 * 3) * cc_dim2 + 1) * cc_dim1 + 1]);
/* L101: */
    }
    if (*ido == 1) {
	return 0;
    }
    idp2 = *ido + 2;
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    ch[(i__ - 1 + (k * 5 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__ - 2]
		    * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ - 1 + (
		    k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] + wa4[i__ - 1]
		    * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1]))
		    + (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		    cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 +
		    1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ + (k * 5 + 1) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + (wa1[i__ - 2] * cc[(
		    i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2)
		     * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		    cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1]));
	    ch[(i__ - 1 + (k * 5 + 3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + wa4[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] + wa4[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 +
		    1]) + tr12 * (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 *
		    3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 2]
		    * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1
		    + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1]) + ti11 * (wa1[i__ - 2] * cc[(i__
		    + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] - wa1[
		    i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] - (wa4[i__ - 2] * cc[(i__ + (k + cc_dim3 *
		    5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] * cc[(i__ - 1
		    + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])) + ti12 * (
		    wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k + cc_dim3 *
		     3) * cc_dim2) * cc_dim1 + 1] - (wa3[i__ - 2] * cc[(i__ +
		    (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] - wa3[i__
		    - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) *
		    cc_dim1 + 1]));
	    ch[(ic - 1 + (k * 5 + 2) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + wa4[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] + wa4[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 +
		    1]) + tr12 * (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 *
		    3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 2]
		    * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1
		    + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1]) - (ti11 * (wa1[i__ - 2] * cc[(
		    i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] -
		    wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] - (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + ti12 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k * 5 + 3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 * (wa1[i__ - 2]
		    * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		     - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + tr12 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])) + (ti11 * (wa4[i__ - 2] * cc[(
		    i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] +
		    wa4[i__ - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) *
		    cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 + (k + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__ - 1] *
		    cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]))
		     + ti12 * (wa3[i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 <<
		    2)) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 1] * cc[(i__ + (
		    k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] - (wa2[i__
		    - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k + cc_dim3 * 3)
		    * cc_dim2) * cc_dim1 + 1])));
	    ch[(ic + (k * 5 + 2) * ch_dim2) * ch_dim1 + 1] = ti11 * (wa4[i__
		    - 2] * cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) *
		    cc_dim1 + 1] + wa4[i__ - 1] * cc[(i__ + (k + cc_dim3 * 5)
		    * cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 +
		    (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__
		    - 1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1])) + ti12 * (wa3[i__ - 2] * cc[(i__ - 1 + (k
		    + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 1]
		     * cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 +
		    1] - (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1])) - (cc[(i__ + (k
		    + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr11 * (wa1[i__ -
		    2] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		     cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + tr12 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ - 1 + (k * 5 + 5) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] + wa4[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 +
		    1])) + tr11 * (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 *
		     3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2]
		     * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) *
		    cc_dim1 + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    2)) * cc_dim2) * cc_dim1 + 1])) + (ti12 * (wa1[i__ - 2] *
		    cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		    - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] - (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) - ti11 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(ic - 1 + (k * 5 + 4) * ch_dim2) * ch_dim1 + 1] = cc[(i__ - 1
		    + (k + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 * (wa1[
		    i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) * cc_dim2) *
		     cc_dim1 + 1] + wa1[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    1)) * cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ -
		    1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] + wa4[i__
		    - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 +
		    1])) + tr11 * (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 *
		     3) * cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (
		    k + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2]
		     * cc[(i__ - 1 + (k + (cc_dim3 << 2)) * cc_dim2) *
		    cc_dim1 + 1] + wa3[i__ - 1] * cc[(i__ + (k + (cc_dim3 <<
		    2)) * cc_dim2) * cc_dim1 + 1])) - (ti12 * (wa1[i__ - 2] *
		    cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		    - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] - (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) - ti11 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] - (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])));
	    ch[(i__ + (k * 5 + 5) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k +
		    cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 * (wa1[i__ - 2]
		    * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]
		     - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		    cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + tr11 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])) + (ti12 * (wa4[i__ - 2] * cc[(
		    i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] +
		    wa4[i__ - 1] * cc[(i__ + (k + cc_dim3 * 5) * cc_dim2) *
		    cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 + (k + (
		    cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__ - 1] *
		    cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1]))
		     - ti11 * (wa3[i__ - 2] * cc[(i__ - 1 + (k + (cc_dim3 <<
		    2)) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 1] * cc[(i__ + (
		    k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] - (wa2[i__
		    - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) * cc_dim2) *
		    cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k + cc_dim3 * 3)
		    * cc_dim2) * cc_dim1 + 1])));
	    ch[(ic + (k * 5 + 4) * ch_dim2) * ch_dim1 + 1] = ti12 * (wa4[i__
		    - 2] * cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) *
		    cc_dim1 + 1] + wa4[i__ - 1] * cc[(i__ + (k + cc_dim3 * 5)
		    * cc_dim2) * cc_dim1 + 1] - (wa1[i__ - 2] * cc[(i__ - 1 +
		    (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1 + 1] + wa1[i__
		    - 1] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) *
		    cc_dim1 + 1])) - ti11 * (wa3[i__ - 2] * cc[(i__ - 1 + (k
		    + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1] + wa3[i__ - 1]
		     * cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 +
		    1] - (wa2[i__ - 2] * cc[(i__ - 1 + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] + wa2[i__ - 1] * cc[(i__ + (k +
		    cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1])) - (cc[(i__ + (k
		    + cc_dim3) * cc_dim2) * cc_dim1 + 1] + tr12 * (wa1[i__ -
		    2] * cc[(i__ + (k + (cc_dim3 << 1)) * cc_dim2) * cc_dim1
		    + 1] - wa1[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 1)) *
		     cc_dim2) * cc_dim1 + 1] + (wa4[i__ - 2] * cc[(i__ + (k +
		    cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1] - wa4[i__ - 1] *
		    cc[(i__ - 1 + (k + cc_dim3 * 5) * cc_dim2) * cc_dim1 + 1])
		    ) + tr11 * (wa2[i__ - 2] * cc[(i__ + (k + cc_dim3 * 3) *
		    cc_dim2) * cc_dim1 + 1] - wa2[i__ - 1] * cc[(i__ - 1 + (k
		    + cc_dim3 * 3) * cc_dim2) * cc_dim1 + 1] + (wa3[i__ - 2] *
		     cc[(i__ + (k + (cc_dim3 << 2)) * cc_dim2) * cc_dim1 + 1]
		    - wa3[i__ - 1] * cc[(i__ - 1 + (k + (cc_dim3 << 2)) *
		    cc_dim2) * cc_dim1 + 1])));
/* L102: */
	}
/* L103: */
    }
    return 0;
} /* r1f5kf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1fgkb_d(int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *in1, double *ch, double *ch2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, c1_dim1, c1_dim2, c1_dim3, c1_offset, c2_dim1, c2_dim2,
	     c2_offset, ch2_dim1, ch2_dim2, ch2_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k, l, j2, ic, jc, lc, ik, is;
     double dc2, ai1, ai2, ar1, ar2, ds2;
     int nbd;
     double dcp, arg, dsp, tpi, ar1h, ar2h;
     int idp2, ipp2, idij, ipph;

    /* Parameter adjustments */
    --wa;
    c2_dim1 = *in1;
    c2_dim2 = *idl1;
    c2_offset = 1 + c2_dim1 * (1 + c2_dim2);
    c2 -= c2_offset;
    c1_dim1 = *in1;
    c1_dim2 = *ido;
    c1_dim3 = *l1;
    c1_offset = 1 + c1_dim1 * (1 + c1_dim2 * (1 + c1_dim3));
    c1 -= c1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch2_dim1 = *in2;
    ch2_dim2 = *idl1;
    ch2_offset = 1 + ch2_dim1 * (1 + ch2_dim2);
    ch2 -= ch2_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    tpi = atan(1.0) * 8.0;
    arg = tpi / (double) (*ip);
    dcp = cos(arg);
    dsp = sin(arg);
    idp2 = *ido + 2;
    nbd = (*ido - 1) / 2;
    ipp2 = *ip + 2;
    ipph = (*ip + 1) / 2;
    if (*ido < *l1) {
	goto L103;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k *
		     cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1];
/* L101: */
	}
/* L102: */
    }
    goto L106;
L103:
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[(i__ + (k + ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(i__ + (k *
		     cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1];
/* L104: */
	}
/* L105: */
    }
L106:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[(*ido + (
		    j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] + cc[(*
		    ido + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1];
	    ch[((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = cc[((j2 -
		    1 + k * cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1] + cc[((j2
		    - 1 + k * cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1];
/* L1007: */
/* L107: */
	}
/* L108: */
    }
    if (*ido == 1) {
	goto L116;
    }
    if (nbd < *l1) {
	goto L112;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		ic = idp2 - i__;
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			cc[(i__ - 1 + ((j << 1) - 1 + k * cc_dim3) * cc_dim2)
			* cc_dim1 + 1] + cc[(ic - 1 + ((j << 1) - 2 + k *
			cc_dim3) * cc_dim2) * cc_dim1 + 1];
		ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			cc[(i__ - 1 + ((j << 1) - 1 + k * cc_dim3) * cc_dim2)
			* cc_dim1 + 1] - cc[(ic - 1 + ((j << 1) - 2 + k *
			cc_dim3) * cc_dim2) * cc_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(
			i__ + ((j << 1) - 1 + k * cc_dim3) * cc_dim2) *
			cc_dim1 + 1] - cc[(ic + ((j << 1) - 2 + k * cc_dim3) *
			 cc_dim2) * cc_dim1 + 1];
		ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(
			i__ + ((j << 1) - 1 + k * cc_dim3) * cc_dim2) *
			cc_dim1 + 1] + cc[(ic + ((j << 1) - 2 + k * cc_dim3) *
			 cc_dim2) * cc_dim1 + 1];
/* L109: */
	    }
/* L110: */
	}
/* L111: */
    }
    goto L116;
L112:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			cc[(i__ - 1 + ((j << 1) - 1 + k * cc_dim3) * cc_dim2)
			* cc_dim1 + 1] + cc[(ic - 1 + ((j << 1) - 2 + k *
			cc_dim3) * cc_dim2) * cc_dim1 + 1];
		ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			cc[(i__ - 1 + ((j << 1) - 1 + k * cc_dim3) * cc_dim2)
			* cc_dim1 + 1] - cc[(ic - 1 + ((j << 1) - 2 + k *
			cc_dim3) * cc_dim2) * cc_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(
			i__ + ((j << 1) - 1 + k * cc_dim3) * cc_dim2) *
			cc_dim1 + 1] - cc[(ic + ((j << 1) - 2 + k * cc_dim3) *
			 cc_dim2) * cc_dim1 + 1];
		ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] = cc[(
			i__ + ((j << 1) - 1 + k * cc_dim3) * cc_dim2) *
			cc_dim1 + 1] + cc[(ic + ((j << 1) - 2 + k * cc_dim3) *
			 cc_dim2) * cc_dim1 + 1];
/* L113: */
	    }
/* L114: */
	}
/* L115: */
    }
L116:
    ar1 = 1.0;
    ai1 = 0.0;
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    c2[(ik + l * c2_dim2) * c2_dim1 + 1] = ch2[(ik + ch2_dim2) *
		    ch2_dim1 + 1] + ar1 * ch2[(ik + (ch2_dim2 << 1)) *
		    ch2_dim1 + 1];
	    c2[(ik + lc * c2_dim2) * c2_dim1 + 1] = ai1 * ch2[(ik + *ip *
		    ch2_dim2) * ch2_dim1 + 1];
/* L117: */
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
		c2[(ik + l * c2_dim2) * c2_dim1 + 1] += ar2 * ch2[(ik + j *
			ch2_dim2) * ch2_dim1 + 1];
		c2[(ik + lc * c2_dim2) * c2_dim1 + 1] += ai2 * ch2[(ik + jc *
			ch2_dim2) * ch2_dim1 + 1];
/* L118: */
	    }
/* L119: */
	}
/* L120: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    ch2[(ik + ch2_dim2) * ch2_dim1 + 1] += ch2[(ik + j * ch2_dim2) *
		    ch2_dim1 + 1];
/* L121: */
	}
/* L122: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = c1[((k + j *
		     c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1] - c1[((k + jc *
		    c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1];
	    ch[((k + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = c1[((k + j
		    * c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1] + c1[((k + jc *
		    c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1];
/* L123: */
	}
/* L124: */
    }
    if (*ido == 1) {
	goto L132;
    }
    if (nbd < *l1) {
	goto L128;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1
			+ 1] - c1[(i__ + (k + jc * c1_dim3) * c1_dim2) *
			c1_dim1 + 1];
		ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1
			+ 1] + c1[(i__ + (k + jc * c1_dim3) * c1_dim2) *
			c1_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = c1[(
			i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] +
			c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1
			+ 1];
		ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] = c1[(
			i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] -
			c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1
			+ 1];
/* L125: */
	    }
/* L126: */
	}
/* L127: */
    }
    goto L132;
L128:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1
			+ 1] - c1[(i__ + (k + jc * c1_dim3) * c1_dim2) *
			c1_dim1 + 1];
		ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1
			+ 1] + c1[(i__ + (k + jc * c1_dim3) * c1_dim2) *
			c1_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = c1[(
			i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] +
			c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1
			+ 1];
		ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1] = c1[(
			i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] -
			c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1
			+ 1];
/* L129: */
	    }
/* L130: */
	}
/* L131: */
    }
L132:
    if (*ido == 1) {
	return 0;
    }
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	c2[(ik + c2_dim2) * c2_dim1 + 1] = ch2[(ik + ch2_dim2) * ch2_dim1 + 1]
		;
/* L133: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    c1[((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1] = ch[((k + j *
		     ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1];
/* L134: */
	}
/* L135: */
    }
    if (nbd > *l1) {
	goto L139;
    }
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	idij = is;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    idij += 2;
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			wa[idij - 1] * ch[(i__ - 1 + (k + j * ch_dim3) *
			ch_dim2) * ch_dim1 + 1] - wa[idij] * ch[(i__ + (k + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 1];
		c1[(i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] = wa[
			idij - 1] * ch[(i__ + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] + wa[idij] * ch[(i__ - 1 + (k + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L136: */
	    }
/* L137: */
	}
/* L138: */
    }
    goto L143;
L139:
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    idij = is;
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		idij += 2;
		c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			wa[idij - 1] * ch[(i__ - 1 + (k + j * ch_dim3) *
			ch_dim2) * ch_dim1 + 1] - wa[idij] * ch[(i__ + (k + j
			* ch_dim3) * ch_dim2) * ch_dim1 + 1];
		c1[(i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] = wa[
			idij - 1] * ch[(i__ + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] + wa[idij] * ch[(i__ - 1 + (k + j *
			ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L140: */
	    }
/* L141: */
	}
/* L142: */
    }
L143:
    return 0;
} /* r1fgkb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r1fgkf_d(int *ido, int *ip, int *l1, int *idl1, double *cc, double *c1, double *c2, int *in1, double *ch, double *ch2, int *in2, double *wa)
{
    /* System generated locals */
    int ch_dim1, ch_dim2, ch_dim3, ch_offset, cc_dim1, cc_dim2, cc_dim3,
	    cc_offset, c1_dim1, c1_dim2, c1_dim3, c1_offset, c2_dim1, c2_dim2,
	     c2_offset, ch2_dim1, ch2_dim2, ch2_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k, l, j2, ic, jc, lc, ik, is;
     double dc2, ai1, ai2, ar1, ar2, ds2;
     int nbd;
     double dcp, arg, dsp, tpi, ar1h, ar2h;
     int idp2, ipp2, idij, ipph;

    /* Parameter adjustments */
    --wa;
    c2_dim1 = *in1;
    c2_dim2 = *idl1;
    c2_offset = 1 + c2_dim1 * (1 + c2_dim2);
    c2 -= c2_offset;
    c1_dim1 = *in1;
    c1_dim2 = *ido;
    c1_dim3 = *l1;
    c1_offset = 1 + c1_dim1 * (1 + c1_dim2 * (1 + c1_dim3));
    c1 -= c1_offset;
    cc_dim1 = *in1;
    cc_dim2 = *ido;
    cc_dim3 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2 * (1 + cc_dim3));
    cc -= cc_offset;
    ch2_dim1 = *in2;
    ch2_dim2 = *idl1;
    ch2_offset = 1 + ch2_dim1 * (1 + ch2_dim2);
    ch2 -= ch2_offset;
    ch_dim1 = *in2;
    ch_dim2 = *ido;
    ch_dim3 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2 * (1 + ch_dim3));
    ch -= ch_offset;

    /* Function Body */
    tpi = atan(1.0) * 8.0;
    arg = tpi / (double) (*ip);
    dcp = cos(arg);
    dsp = sin(arg);
    ipph = (*ip + 1) / 2;
    ipp2 = *ip + 2;
    idp2 = *ido + 2;
    nbd = (*ido - 1) / 2;
    if (*ido == 1) {
	goto L119;
    }
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	ch2[(ik + ch2_dim2) * ch2_dim1 + 1] = c2[(ik + c2_dim2) * c2_dim1 + 1]
		;
/* L101: */
    }
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    ch[((k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] = c1[((k + j *
		     c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1];
/* L102: */
	}
/* L103: */
    }
    if (nbd > *l1) {
	goto L107;
    }
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	idij = is;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    idij += 2;
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			wa[idij - 1] * c1[(i__ - 1 + (k + j * c1_dim3) *
			c1_dim2) * c1_dim1 + 1] + wa[idij] * c1[(i__ + (k + j
			* c1_dim3) * c1_dim2) * c1_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = wa[
			idij - 1] * c1[(i__ + (k + j * c1_dim3) * c1_dim2) *
			c1_dim1 + 1] - wa[idij] * c1[(i__ - 1 + (k + j *
			c1_dim3) * c1_dim2) * c1_dim1 + 1];
/* L104: */
	    }
/* L105: */
	}
/* L106: */
    }
    goto L111;
L107:
    is = -(*ido);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	is += *ido;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    idij = is;
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		idij += 2;
		ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] =
			wa[idij - 1] * c1[(i__ - 1 + (k + j * c1_dim3) *
			c1_dim2) * c1_dim1 + 1] + wa[idij] * c1[(i__ + (k + j
			* c1_dim3) * c1_dim2) * c1_dim1 + 1];
		ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] = wa[
			idij - 1] * c1[(i__ + (k + j * c1_dim3) * c1_dim2) *
			c1_dim1 + 1] - wa[idij] * c1[(i__ - 1 + (k + j *
			c1_dim3) * c1_dim2) * c1_dim1 + 1];
/* L108: */
	    }
/* L109: */
	}
/* L110: */
    }
L111:
    if (nbd < *l1) {
	goto L115;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1
			+ 1] + ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			ch_dim1 + 1];
		c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			- ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
		c1[(i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] = ch[(
			i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] +
			ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			;
		c1[(i__ + (k + jc * c1_dim3) * c1_dim2) * c1_dim1 + 1] = ch[(
			i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			 - ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1];
/* L112: */
	    }
/* L113: */
	}
/* L114: */
    }
    goto L121;
L115:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		c1[(i__ - 1 + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) * ch_dim1
			+ 1] + ch[(i__ - 1 + (k + jc * ch_dim3) * ch_dim2) *
			ch_dim1 + 1];
		c1[(i__ - 1 + (k + jc * c1_dim3) * c1_dim2) * c1_dim1 + 1] =
			ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			- ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
		c1[(i__ + (k + j * c1_dim3) * c1_dim2) * c1_dim1 + 1] = ch[(
			i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1] +
			ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			;
		c1[(i__ + (k + jc * c1_dim3) * c1_dim2) * c1_dim1 + 1] = ch[(
			i__ - 1 + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			 - ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1];
/* L116: */
	    }
/* L117: */
	}
/* L118: */
    }
    goto L121;
L119:
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
	c2[(ik + c2_dim2) * c2_dim1 + 1] = ch2[(ik + ch2_dim2) * ch2_dim1 + 1]
		;
/* L120: */
    }
L121:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    c1[((k + j * c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1] = ch[((k + j *
		     ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] + ch[((k + jc *
		    ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1];
	    c1[((k + jc * c1_dim3) * c1_dim2 + 1) * c1_dim1 + 1] = ch[((k +
		    jc * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1] - ch[((k + j *
		     ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1];
/* L122: */
	}
/* L123: */
    }

    ar1 = 1.0;
    ai1 = 0.0;
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
	lc = ipp2 - l;
	ar1h = dcp * ar1 - dsp * ai1;
	ai1 = dcp * ai1 + dsp * ar1;
	ar1 = ar1h;
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    ch2[(ik + l * ch2_dim2) * ch2_dim1 + 1] = c2[(ik + c2_dim2) *
		    c2_dim1 + 1] + ar1 * c2[(ik + (c2_dim2 << 1)) * c2_dim1 +
		    1];
	    ch2[(ik + lc * ch2_dim2) * ch2_dim1 + 1] = ai1 * c2[(ik + *ip *
		    c2_dim2) * c2_dim1 + 1];
/* L124: */
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
		ch2[(ik + l * ch2_dim2) * ch2_dim1 + 1] += ar2 * c2[(ik + j *
			c2_dim2) * c2_dim1 + 1];
		ch2[(ik + lc * ch2_dim2) * ch2_dim1 + 1] += ai2 * c2[(ik + jc
			* c2_dim2) * c2_dim1 + 1];
/* L125: */
	    }
/* L126: */
	}
/* L127: */
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
	    ch2[(ik + ch2_dim2) * ch2_dim1 + 1] += c2[(ik + j * c2_dim2) *
		    c2_dim1 + 1];
/* L128: */
	}
/* L129: */
    }

    if (*ido < *l1) {
	goto L132;
    }
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    cc[(i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = ch[(i__ +
		    (k + ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L130: */
	}
/* L131: */
    }
    goto L135;
L132:
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(i__ + (k * cc_dim3 + 1) * cc_dim2) * cc_dim1 + 1] = ch[(i__ +
		    (k + ch_dim3) * ch_dim2) * ch_dim1 + 1];
/* L133: */
	}
/* L134: */
    }
L135:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    cc[(*ido + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] = ch[(
		    (k + j * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1];
	    cc[((j2 - 1 + k * cc_dim3) * cc_dim2 + 1) * cc_dim1 + 1] = ch[((k
		    + jc * ch_dim3) * ch_dim2 + 1) * ch_dim1 + 1];
/* L136: */
	}
/* L137: */
    }
    if (*ido == 1) {
	return 0;
    }
    if (nbd < *l1) {
	goto L141;
    }
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = *ido;
	    for (i__ = 3; i__ <= i__3; i__ += 2) {
		ic = idp2 - i__;
		cc[(i__ - 1 + (j2 - 1 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1]
			 = ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] + ch[(i__ - 1 + (k + jc * ch_dim3) *
			ch_dim2) * ch_dim1 + 1];
		cc[(ic - 1 + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1]
			= ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] - ch[(i__ - 1 + (k + jc * ch_dim3) *
			ch_dim2) * ch_dim1 + 1];
		cc[(i__ + (j2 - 1 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] =
			ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			+ ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
		cc[(ic + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] =
			ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			 - ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
/* L138: */
	    }
/* L139: */
	}
/* L140: */
    }
    return 0;
L141:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
	jc = ipp2 - j;
	j2 = j + j;
	i__2 = *ido;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    ic = idp2 - i__;
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
		cc[(i__ - 1 + (j2 - 1 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1]
			 = ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] + ch[(i__ - 1 + (k + jc * ch_dim3) *
			ch_dim2) * ch_dim1 + 1];
		cc[(ic - 1 + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1]
			= ch[(i__ - 1 + (k + j * ch_dim3) * ch_dim2) *
			ch_dim1 + 1] - ch[(i__ - 1 + (k + jc * ch_dim3) *
			ch_dim2) * ch_dim1 + 1];
		cc[(i__ + (j2 - 1 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] =
			ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			+ ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
		cc[(ic + (j2 - 2 + k * cc_dim3) * cc_dim2) * cc_dim1 + 1] =
			ch[(i__ + (k + jc * ch_dim3) * ch_dim2) * ch_dim1 + 1]
			 - ch[(i__ + (k + j * ch_dim3) * ch_dim2) * ch_dim1 +
			1];
/* L142: */
	    }
/* L143: */
	}
/* L144: */
    }
    return 0;
} /* r1fgkf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   AUTHORS:  PAUL N. SWARZTRAUBER AND RICHARD A. VALENT */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int r2w_d(int *ldr, int *ldw, int *l, int *m, double *r__, double *w)
{
    /* System generated locals */
    int r_dim1, r_offset, w_dim1, w_offset, i__1, i__2;

    /* Local variables */
     int i__, j;

    /* Parameter adjustments */
    r_dim1 = *ldr;
    r_offset = 1 + r_dim1;
    r__ -= r_offset;
    w_dim1 = *ldw;
    w_offset = 1 + w_dim1;
    w -= w_offset;

    /* Function Body */
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *l;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    w[i__ + j * w_dim1] = r__[i__ + j * r_dim1];
	}
    }
    return 0;
} /* r2w_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft1b_d(int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --r__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenr < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("RFFT1B ", &c__6, (int)7);
    } else if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFT1B ", &c__8, (int)7);
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("RFFT1B ", &c__10, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    rfftb1_d(n, inc, &r__[1], &work[1], &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfft1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft1f_d(int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --r__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenr < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("RFFT1F ", &c__6, (int)7);
    } else if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFT1F ", &c__8, (int)7);
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("RFFT1F ", &c__10, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    rfftf1_d(n, inc, &r__[1], &work[1], &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfft1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft1i_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFT1I ", &c__3, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    rffti1_d(n, &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfft1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   AUTHORS:  PAUL N. SWARZTRAUBER AND RICHARD A. VALENT */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft2b_d(int *ldim, int *l, int *m, double *r__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int r_dim1, r_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, j;
     int ldh, ldw, ldx, ier1, modl, modm, mmsav, lwsav, mwsav;

/* INITIALIZE IER */

    /* Parameter adjustments */
    r_dim1 = *ldim;
    r_offset = 1 + r_dim1;
    r__ -= r_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

/* VERIFY LENSAV */

    lwsav = *l + (int) (log((double) (*l)) / log(2.0)) + 4;
    mwsav = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    mmsav = *m + (int) (log((double) (*m)) / log(2.0)) + 4;
    modl = *l % 2;
    modm = *m % 2;

    if (*lensav < lwsav + mwsav + mmsav) {
	*ier = 2;
	//xerfft_d("RFFT2F", &c__6, (int)6);
	goto L100;
    }

/* VERIFY LENWRK */

    if (*lenwrk < (*l + 1) * *m) {
	*ier = 3;
	//xerfft_d("RFFT2F", &c__8, (int)6);
	goto L100;
    }

/* VERIFY LDIM IS AS BIG AS L */

    if (*ldim < *l) {
	*ier = 5;
	//xerfft_d("RFFT2F", &c_n6, (int)6);
	goto L100;
    }

/* TRANSFORM SECOND DIMENSION OF ARRAY */

    i__1 = ((*m + 1) / 2 << 1) - 1;
    for (j = 2; j <= i__1; ++j) {
	r__[j * r_dim1 + 1] += r__[j * r_dim1 + 1];
    }
    i__1 = *m;
    for (j = 3; j <= i__1; j += 2) {
	r__[j * r_dim1 + 1] = -r__[j * r_dim1 + 1];
    }
    i__1 = *m * *ldim;
    rfftmb_d(&c__1, &c__1, m, ldim, &r__[r_offset], &i__1, &wsave[lwsav +
	    mwsav + 1], &mmsav, &work[1], lenwrk, &ier1);
    ldh = (*l + 1) / 2;
    if (ldh > 1) {
	ldw = ldh + ldh;

/*     R AND WORK ARE SWITCHED BECAUSE THE THE FIRST DIMENSION */
/*     OF THE INPUT TO COMPLEX CFFTMF MUST BE EVEN. */

	r2w_d(ldim, &ldw, l, m, &r__[r_offset], &work[1]);
	i__1 = ldh - 1;
	i__2 = ldh * *m;
	i__3 = *l * *m;
	cfftmb_d(&i__1, &c__1, m, &ldh, (fft_complexd_t*)&work[2], &i__2, &wsave[lwsav + 1], &
		mwsav, &r__[r_offset], &i__3, &ier1);
	if (ier1 != 0) {
	    *ier = 20;
	    //xerfft_d("RFFT2B", &c_n5, (int)6);
	    goto L100;
	}
	w2r_d(ldim, &ldw, l, m, &r__[r_offset], &work[1]);
    }

    if (modl == 0) {
	i__1 = ((*m + 1) / 2 << 1) - 1;
	for (j = 2; j <= i__1; ++j) {
	    r__[*l + j * r_dim1] += r__[*l + j * r_dim1];
	}
	i__1 = *m;
	for (j = 3; j <= i__1; j += 2) {
	    r__[*l + j * r_dim1] = -r__[*l + j * r_dim1];
	}
	i__1 = *m * *ldim;
	rfftmb_d(&c__1, &c__1, m, ldim, &r__[*l + r_dim1], &i__1, &wsave[lwsav
		+ mwsav + 1], &mmsav, &work[1], lenwrk, &ier1);
    }

/*     PRINT*, 'BACKWARD TRANSFORM IN THE J DIRECTION' */
/*     DO I=1,L */
/*       PRINT*, (R(I,J),J=1,M) */
/*     END DO */

/* TRANSFORM FIRST DIMENSION OF ARRAY */

    ldx = ((*l + 1) / 2 << 1) - 1;
    i__1 = ldx;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    r__[i__ + j * r_dim1] += r__[i__ + j * r_dim1];
	}
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ldx;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    r__[i__ + j * r_dim1] = -r__[i__ + j * r_dim1];
	}
    }
    i__1 = *m * *ldim;
    i__2 = *l + (int) (log((double) (*l)) / log(2.0)) + 4;
    rfftmb_d(m, ldim, l, &c__1, &r__[r_offset], &i__1, &wsave[1], &i__2, &work[
	    1], lenwrk, &ier1);

/*     PRINT*, 'BACKWARD TRANSFORM IN THE I DIRECTION' */
/*     DO I=1,L */
/*       PRINT*, (R(I,J),J=1,M) */
/*     END DO */

    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2F", &c_n5, (int)6);
	goto L100;
    }

    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2F", &c_n5, (int)6);
	goto L100;
    }

L100:

    return 0;
} /* rfft2b_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   AUTHORS:  PAUL N. SWARZTRAUBER AND RICHARD A. VALENT */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft2f_d(int *ldim, int *l, int *m, double *r__, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int r_dim1, r_offset, i__1, i__2, i__3;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, j;
     int ldh, ldw, ldx, ier1, modl, modm, mmsav, lwsav, mwsav;

/* INITIALIZE IER */

    /* Parameter adjustments */
    r_dim1 = *ldim;
    r_offset = 1 + r_dim1;
    r__ -= r_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

/* VERIFY LENSAV */

    lwsav = *l + (int) (log((double) (*l)) / log(2.0)) + 4;
    mwsav = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    mmsav = *m + (int) (log((double) (*m)) / log(2.0)) + 4;

    if (*lensav < lwsav + mwsav + mmsav) {
	*ier = 2;
	//xerfft_d("RFFT2F", &c__6, (int)6);
	goto L100;
    }

/* VERIFY LENWRK */

    if (*lenwrk < (*l + 1) * *m) {
	*ier = 3;
	//xerfft_d("RFFT2F", &c__8, (int)6);
	goto L100;
    }

/* VERIFY LDIM IS AS BIG AS L */

    if (*ldim < *l) {
	*ier = 5;
	//xerfft_d("RFFT2F", &c_n6, (int)6);
	goto L100;
    }

/* TRANSFORM FIRST DIMENSION OF ARRAY */

    i__1 = *m * *ldim;
    i__2 = *l + (int) (log((double) (*l)) / log(2.0)) + 4;
    rfftmf_d(m, ldim, l, &c__1, &r__[r_offset], &i__1, &wsave[1], &i__2, &work[
	    1], lenwrk, &ier1);

    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2F", &c_n5, (int)6);
	goto L100;
    }

    ldx = ((*l + 1) / 2 << 1) - 1;
    i__1 = ldx;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    r__[i__ + j * r_dim1] *= .5;
	}
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = ldx;
	for (i__ = 3; i__ <= i__2; i__ += 2) {
	    r__[i__ + j * r_dim1] = -r__[i__ + j * r_dim1];
	}
    }

/*     PRINT*, 'FORWARD TRANSFORM IN THE I DIRECTION' */
/*     DO I=1,L */
/*       PRINT*, (R(I,J),J=1,M) */
/*     END DO */

/* RESHUFFLE TO ADD IN NYQUIST IMAGINARY COMPONENTS */

    modl = *l % 2;
    modm = *m % 2;

/* TRANSFORM SECOND DIMENSION OF ARRAY */

    i__1 = *m * *ldim;
    rfftmf_d(&c__1, &c__1, m, ldim, &r__[r_offset], &i__1, &wsave[lwsav +
	    mwsav + 1], &mmsav, &work[1], lenwrk, &ier1);
    i__1 = ((*m + 1) / 2 << 1) - 1;
    for (j = 2; j <= i__1; ++j) {
	r__[j * r_dim1 + 1] *= .5;
    }
    i__1 = *m;
    for (j = 3; j <= i__1; j += 2) {
	r__[j * r_dim1 + 1] = -r__[j * r_dim1 + 1];
    }
    ldh = (*l + 1) / 2;
    if (ldh > 1) {
	ldw = ldh + ldh;

/*     R AND WORK ARE SWITCHED BECAUSE THE THE FIRST DIMENSION */
/*     OF THE INPUT TO COMPLEX CFFTMF MUST BE EVEN. */

	r2w_d(ldim, &ldw, l, m, &r__[r_offset], &work[1]);
	i__1 = ldh - 1;
	i__2 = ldh * *m;
	i__3 = *l * *m;
	cfftmf_d(&i__1, &c__1, m, &ldh, (fft_complexd_t*)&work[2], &i__2, &wsave[lwsav + 1], &
		mwsav, &r__[r_offset], &i__3, &ier1);
	if (ier1 != 0) {
	    *ier = 20;
	    //xerfft_d("RFFT2F", &c_n5, (int)6);
	    goto L100;
	}
	w2r_d(ldim, &ldw, l, m, &r__[r_offset], &work[1]);
    }

    if (modl == 0) {
	i__1 = *m * *ldim;
	rfftmf_d(&c__1, &c__1, m, ldim, &r__[*l + r_dim1], &i__1, &wsave[lwsav
		+ mwsav + 1], &mmsav, &work[1], lenwrk, &ier1);
	i__1 = ((*m + 1) / 2 << 1) - 1;
	for (j = 2; j <= i__1; ++j) {
	    r__[*l + j * r_dim1] *= .5;
	}
	i__1 = *m;
	for (j = 3; j <= i__1; j += 2) {
	    r__[*l + j * r_dim1] = -r__[*l + j * r_dim1];
	}
    }

/*     PRINT*, 'FORWARD TRANSFORM IN THE J DIRECTION' */
/*     DO I=1,L */
/*       PRINT*, (R(I,J),J=1,M) */
/*     END DO */

    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2F", &c_n5, (int)6);
	goto L100;
    }

L100:
    return 0;
} /* rfft2f_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   AUTHORS:  PAUL N. SWARZTRAUBER AND RICHARD A. VALENT */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfft2i_d(int *l, int *m, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int ier1, mmsav, lwsav, mwsav;

/* INITIALIZE IER */

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

/* VERIFY LENSAV */

    lwsav = *l + (int) (log((double) (*l)) / log(2.0)) + 4;
    mwsav = (*m << 1) + (int) (log((double) (*m)) / log(2.0)) + 4;
    mmsav = *m + (int) (log((double) (*m)) / log(2.0)) + 4;
    if (*lensav < lwsav + mwsav + mmsav) {
	*ier = 2;
	//xerfft_d("RFFT2I", &c__4, (int)6);
	goto L100;
    }

    rfftmi_d(l, &wsave[1], &lwsav, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2I", &c_n5, (int)6);
	goto L100;
    }
    cfftmi_d(m, &wsave[lwsav + 1], &mwsav, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2I", &c_n5, (int)6);
	goto L100;
    }

    rfftmi_d(m, &wsave[lwsav + mwsav + 1], &mmsav, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("RFFT2I", &c_n5, (int)6);
	goto L100;
    }

L100:
    return 0;
} /* rfft2i_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfftb1_d(int *n, int *in, double *c__, double *ch, double *wa, double *fac)
{
    /* System generated locals */
    int c_dim1, c_offset, i__1;
    int c__1 = 1;

    /* Local variables */
     int j, k1, l1, l2, na, nf, ip, nl, iw, ix2, ix3, ix4, ido,
	    idl1;
     double half;
     int modn;
     double halfm;

    /* Parameter adjustments */
    --wa;
    c_dim1 = *in;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --ch;
    --fac;

    /* Function Body */
    nf = fac[2];
    na = 0;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	na = 1 - na;
	if (ip <= 5) {
	    goto L10;
	}
	if (k1 == nf) {
	    goto L10;
	}
	na = 1 - na;
L10:
	;
    }
    half = .5;
    halfm = -.5;
    modn = *n % 2;
    nl = *n - 2;
    if (modn != 0) {
	nl = *n - 1;
    }
    if (na == 0) {
	goto L120;
    }
    ch[1] = c__[c_dim1 + 1];
    ch[*n] = c__[*n * c_dim1 + 1];
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	ch[j] = half * c__[j * c_dim1 + 1];
	ch[j + 1] = halfm * c__[(j + 1) * c_dim1 + 1];
/* L118: */
    }
    goto L124;
L120:
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	c__[j * c_dim1 + 1] = half * c__[j * c_dim1 + 1];
	c__[(j + 1) * c_dim1 + 1] = halfm * c__[(j + 1) * c_dim1 + 1];
/* L122: */
    }
L124:
    l1 = 1;
    iw = 1;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	l2 = ip * l1;
	ido = *n / l2;
	idl1 = ido * l1;
	if (ip != 4) {
	    goto L103;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	if (na != 0) {
	    goto L101;
	}
	r1f4kb_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2], &wa[ix3]);
	goto L102;
L101:
	r1f4kb_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2], &wa[ix3]);
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
	r1f2kb_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw]);
	goto L105;
L104:
	r1f2kb_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw]);
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
	r1f3kb_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2]);
	goto L108;
L107:
	r1f3kb_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2]);
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
	r1f5kb_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2], &wa[ix3], &wa[ix4]);
	goto L111;
L110:
	r1f5kb_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2], &wa[ix3], &wa[ix4]);
L111:
	na = 1 - na;
	goto L115;
L112:
	if (na != 0) {
	    goto L113;
	}
	r1fgkb_d(&ido, &ip, &l1, &idl1, &c__[c_offset], &c__[c_offset], &c__[
		c_offset], in, &ch[1], &ch[1], &c__1, &wa[iw]);
	goto L114;
L113:
	r1fgkb_d(&ido, &ip, &l1, &idl1, &ch[1], &ch[1], &ch[1], &c__1, &c__[
		c_offset], &c__[c_offset], in, &wa[iw]);
L114:
	if (ido == 1) {
	    na = 1 - na;
	}
L115:
	l1 = l2;
	iw += (ip - 1) * ido;
/* L116: */
    }
    return 0;
} /* rfftb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfftf1_d(int *n, int *in, double *c__, double *ch, double *wa, double *fac)
{
    /* System generated locals */
    int c_dim1, c_offset, i__1;
    int c__1 = 1;

    /* Local variables */
     int j, k1, l1, l2, na, kh, nf, ip, nl, iw;
     double sn;
     int ix2, ix3, ix4, ido;
     double tsn;
     int idl1, modn;
     double tsnm;

    /* Parameter adjustments */
    --wa;
    c_dim1 = *in;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --ch;
    --fac;

    /* Function Body */
    nf = fac[2];
    na = 1;
    l2 = *n;
    iw = *n;
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
	kh = nf - k1;
	ip = fac[kh + 3];
	l1 = l2 / ip;
	ido = *n / l2;
	idl1 = ido * l1;
	iw -= (ip - 1) * ido;
	na = 1 - na;
	if (ip != 4) {
	    goto L102;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	if (na != 0) {
	    goto L101;
	}
	r1f4kf_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2], &wa[ix3]);
	goto L110;
L101:
	r1f4kf_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2], &wa[ix3]);
	goto L110;
L102:
	if (ip != 2) {
	    goto L104;
	}
	if (na != 0) {
	    goto L103;
	}
	r1f2kf_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw]);
	goto L110;
L103:
	r1f2kf_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw]);
	goto L110;
L104:
	if (ip != 3) {
	    goto L106;
	}
	ix2 = iw + ido;
	if (na != 0) {
	    goto L105;
	}
	r1f3kf_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2]);
	goto L110;
L105:
	r1f3kf_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2]);
	goto L110;
L106:
	if (ip != 5) {
	    goto L108;
	}
	ix2 = iw + ido;
	ix3 = ix2 + ido;
	ix4 = ix3 + ido;
	if (na != 0) {
	    goto L107;
	}
	r1f5kf_d(&ido, &l1, &c__[c_offset], in, &ch[1], &c__1, &wa[iw], &wa[
		ix2], &wa[ix3], &wa[ix4]);
	goto L110;
L107:
	r1f5kf_d(&ido, &l1, &ch[1], &c__1, &c__[c_offset], in, &wa[iw], &wa[
		ix2], &wa[ix3], &wa[ix4]);
	goto L110;
L108:
	if (ido == 1) {
	    na = 1 - na;
	}
	if (na != 0) {
	    goto L109;
	}
	r1fgkf_d(&ido, &ip, &l1, &idl1, &c__[c_offset], &c__[c_offset], &c__[
		c_offset], in, &ch[1], &ch[1], &c__1, &wa[iw]);
	na = 1;
	goto L110;
L109:
	r1fgkf_d(&ido, &ip, &l1, &idl1, &ch[1], &ch[1], &ch[1], &c__1, &c__[
		c_offset], &c__[c_offset], in, &wa[iw]);
	na = 0;
L110:
	l2 = l1;
/* L111: */
    }
    sn = 1.0 / *n;
    tsn = 2.0 / *n;
    tsnm = -tsn;
    modn = *n % 2;
    nl = *n - 2;
    if (modn != 0) {
	nl = *n - 1;
    }
    if (na != 0) {
	goto L120;
    }
    c__[c_dim1 + 1] = sn * ch[1];
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	c__[j * c_dim1 + 1] = tsn * ch[j];
	c__[(j + 1) * c_dim1 + 1] = tsnm * ch[j + 1];
/* L118: */
    }
    if (modn != 0) {
	return 0;
    }
    c__[*n * c_dim1 + 1] = sn * ch[*n];
    return 0;
L120:
    c__[c_dim1 + 1] = sn * c__[c_dim1 + 1];
    i__1 = nl;
    for (j = 2; j <= i__1; j += 2) {
	c__[j * c_dim1 + 1] = tsn * c__[j * c_dim1 + 1];
	c__[(j + 1) * c_dim1 + 1] = tsnm * c__[(j + 1) * c_dim1 + 1];
/* L122: */
    }
    if (modn != 0) {
	return 0;
    }
    c__[*n * c_dim1 + 1] = sn * c__[*n * c_dim1 + 1];
    return 0;
} /* rfftf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rffti1_d(int *n, double *wa, double *fac)
{
    /* Initialized data */

     int ntryh[4] = { 4,2,3,5 };

    /* System generated locals */
    int i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int i__, j, k1, l1, l2, ib;
     double fi;
     int ld, ii, nf, ip, nl, is, nq, nr;
     double arg;
     int ido, ipm;
     double tpi;
     int nfm1;
     double argh;
     int ntry;
     double argld;

    /* Parameter adjustments */
    --wa;
    --fac;

    /* Function Body */

    nl = *n;
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
    fac[nf + 2] = (double) ntry;
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
	fac[ib + 2] = fac[ib + 1];
/* L106: */
    }
    fac[3] = 2.0;
L107:
    if (nl != 1) {
	goto L104;
    }
    fac[1] = (double) (*n);
    fac[2] = (double) nf;
    tpi = atan(1.) * 8.;
    argh = tpi / (double) (*n);
    is = 0;
    nfm1 = nf - 1;
    l1 = 1;
    if (nfm1 == 0) {
	return 0;
    }
    i__1 = nfm1;
    for (k1 = 1; k1 <= i__1; ++k1) {
	ip = fac[k1 + 2];
	ld = 0;
	l2 = l1 * ip;
	ido = *n / l2;
	ipm = ip - 1;
	i__2 = ipm;
	for (j = 1; j <= i__2; ++j) {
	    ld += l1;
	    i__ = is;
	    argld = (double) ld * argh;
	    fi = 0.0;
	    i__3 = ido;
	    for (ii = 3; ii <= i__3; ii += 2) {
		i__ += 2;
		fi += 1.0;
		arg = fi * argld;
		wa[i__ - 1] = cos(arg);
		wa[i__] = sin(arg);
/* L108: */
	    }
	    is += ido;
/* L109: */
	}
	l1 = l2;
/* L110: */
    }
    return 0;
} /* rffti1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfftmb_d(int *lot, int *jump, int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --r__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenr < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("RFFTMB ", &c__6, (int)7);
    } else if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFTMB ", &c__8, (int)7);
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("RFFTMB ", &c__10, (int)7);
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("RFFTMB ", &c_n1, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    mrftb1_d(lot, jump, n, inc, &r__[1], &work[1], &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfftmb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfftmf_d(int *lot, int *jump, int *n, int *inc, double *r__, int *lenr, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --r__;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenr < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("RFFTMF ", &c__6, (int)7);
    } else if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFTMF ", &c__8, (int)7);
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("RFFTMF ", &c__10, (int)7);
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("RFFTMF ", &c_n1, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    mrftf1_d(lot, jump, n, inc, &r__[1], &work[1], &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfftmf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rfftmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("RFFTMI ", &c__3, (int)7);
    }

    if (*n == 1) {
	return 0;
    }

    mrfti1_d(n, &wsave[1], &wsave[*n + 1]);
    return 0;
} /* rfftmi_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinq1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int k, kc, ns2, ier1;
     double xhold;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINQ1B", &c__6, (int)6);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("SINQ1B", &c__8, (int)6);
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("SINQ1B", &c__10, (int)6);
    }

    if (*n > 1) {
	goto L101;
    }
/*     X(1,1) = 4.*X(1,1) line disabled by Dick Valent 08/26/2010 */
    return 0;
L101:
    ns2 = *n / 2;
    i__1 = *n;
    for (k = 2; k <= i__1; k += 2) {
	x[k * x_dim1 + 1] = -x[k * x_dim1 + 1];
/* L102: */
    }
    cosq1b_d(n, inc, &x[x_offset], lenx, &wsave[1], lensav, &work[1], lenwrk, &
	    ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQ1B", &c_n5, (int)6);
	goto L300;
    }
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	kc = *n - k;
	xhold = x[k * x_dim1 + 1];
	x[k * x_dim1 + 1] = x[(kc + 1) * x_dim1 + 1];
	x[(kc + 1) * x_dim1 + 1] = xhold;
/* L103: */
    }
L300:
    return 0;
} /* sinq1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinq1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;

    /* Builtin functions */

    /* Local variables */
     int k, kc, ns2, ier1;
     double xhold;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINQ1F", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("SINQ1F", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *n) {
	*ier = 3;
	//xerfft_d("SINQ1F", &c__10, (int)6);
	goto L300;
    }

    if (*n == 1) {
	return 0;
    }
    ns2 = *n / 2;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	kc = *n - k;
	xhold = x[k * x_dim1 + 1];
	x[k * x_dim1 + 1] = x[(kc + 1) * x_dim1 + 1];
	x[(kc + 1) * x_dim1 + 1] = xhold;
/* L101: */
    }
    cosq1f_d(n, inc, &x[x_offset], lenx, &wsave[1], lensav, &work[1], lenwrk, &
	    ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQ1F", &c_n5, (int)6);
	goto L300;
    }
    i__1 = *n;
    for (k = 2; k <= i__1; k += 2) {
	x[k * x_dim1 + 1] = -x[k * x_dim1 + 1];
/* L102: */
    }
L300:
    return 0;
} /* sinq1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinq1i_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("SINQ1I", &c__3, (int)6);
	goto L300;
    }

    cosq1i_d(n, &wsave[1], lensav, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQ1I", &c_n5, (int)6);
    }
L300:
    return 0;
} /* sinq1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinqmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int k, m, kc, lj, ns2, ier1;
     double xhold;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINQMB", &c__6, (int)6);
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("SINQMB", &c__8, (int)6);
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("SINQMB", &c__10, (int)6);
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("SINQMB", &c_n1, (int)6);
    }

    lj = (*lot - 1) * *jump + 1;
    if (*n > 1) {
	goto L101;
    }
    i__1 = lj;
    i__2 = *jump;
    for (m = 1; i__2 < 0 ? m >= i__1 : m <= i__1; m += i__2) {
	x[m + x_dim1] *= 4.0;
/* L201: */
    }
    return 0;
L101:
    ns2 = *n / 2;
    i__2 = *n;
    for (k = 2; k <= i__2; k += 2) {
	i__1 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__1 : m <= i__1; m += i__3) {
	    x[m + k * x_dim1] = -x[m + k * x_dim1];
/* L202: */
	}
/* L102: */
    }
    cosqmb_d(lot, jump, n, inc, &x[x_offset], lenx, &wsave[1], lensav, &work[1]
	    , lenwrk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQMB", &c_n5, (int)6);
	goto L300;
    }
    i__2 = ns2;
    for (k = 1; k <= i__2; ++k) {
	kc = *n - k;
	i__3 = lj;
	i__1 = *jump;
	for (m = 1; i__1 < 0 ? m >= i__3 : m <= i__3; m += i__1) {
	    xhold = x[m + k * x_dim1];
	    x[m + k * x_dim1] = x[m + (kc + 1) * x_dim1];
	    x[m + (kc + 1) * x_dim1] = xhold;
/* L203: */
	}
/* L103: */
    }
L300:
    return 0;
} /* sinqmb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinqmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1, i__2, i__3;

    /* Builtin functions */

    /* Local variables */
     int k, m, kc, lj, ns2, ier1;
     double xhold;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINQMF", &c__6, (int)6);
	goto L300;
    } else if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0))
	    + 4) {
	*ier = 2;
	//xerfft_d("SINQMF", &c__8, (int)6);
	goto L300;
    } else if (*lenwrk < *lot * *n) {
	*ier = 3;
	//xerfft_d("SINQMF", &c__10, (int)6);
	goto L300;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("SINQMF", &c_n1, (int)6);
	goto L300;
    }

    if (*n == 1) {
	return 0;
    }
    ns2 = *n / 2;
    lj = (*lot - 1) * *jump + 1;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	kc = *n - k;
	i__2 = lj;
	i__3 = *jump;
	for (m = 1; i__3 < 0 ? m >= i__2 : m <= i__2; m += i__3) {
	    xhold = x[m + k * x_dim1];
	    x[m + k * x_dim1] = x[m + (kc + 1) * x_dim1];
	    x[m + (kc + 1) * x_dim1] = xhold;
/* L201: */
	}
/* L101: */
    }
    cosqmf_d(lot, jump, n, inc, &x[x_offset], lenx, &wsave[1], lensav, &work[1]
	    , lenwrk, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQMF", &c_n5, (int)6);
	goto L300;
    }
    i__1 = *n;
    for (k = 2; k <= i__1; k += 2) {
	i__3 = lj;
	i__2 = *jump;
	for (m = 1; i__2 < 0 ? m >= i__3 : m <= i__3; m += i__2) {
	    x[m + k * x_dim1] = -x[m + k * x_dim1];
/* L202: */
	}
/* L102: */
    }
L300:
    return 0;
} /* sinqmf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sinqmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < (*n << 1) + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("SINQMI", &c__3, (int)6);
	goto L300;
    }

    cosqmi_d(n, &wsave[1], lensav, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINQMI", &c_n5, (int)6);
    }
L300:
    return 0;
} /* sinqmi_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sint1b_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINT1B", &c__6, (int)6);
	goto L100;
    } else if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0))
	     + 4) {
	*ier = 2;
	//xerfft_d("SINT1B", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < (*n << 1) + 2) {
	*ier = 3;
	//xerfft_d("SINT1B", &c__10, (int)6);
	goto L100;
    }

    sintb1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &work[*n + 2], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINT1B", &c_n5, (int)6);
    }

L100:
    return 0;
} /* sint1b_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sint1f_d(int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;
    if (*lenx < *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINT1F", &c__6, (int)6);
	goto L100;
    } else if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0))
	     + 4) {
	*ier = 2;
	//xerfft_d("SINT1F", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < (*n << 1) + 2) {
	*ier = 3;
	//xerfft_d("SINT1F", &c__10, (int)6);
	goto L100;
    }

    sintf1_d(n, inc, &x[x_offset], &wsave[1], &work[1], &work[*n + 2], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINT1F", &c_n5, (int)6);
    }
L100:
    return 0;
} /* sint1f_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sint1i_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k;
     double dt;
     int np1, ns2, ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("SINT1I", &c__3, (int)6);
	goto L300;
    }

    if (*n <= 1) {
	return 0;
    }
    ns2 = *n / 2;
    np1 = *n + 1;
    dt = 3.14159265358979323846 / (double) np1;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	wsave[k] = sin(k * dt) * 2.0;
/* L101: */
    }
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    rfft1i_d(&np1, &wsave[ns2 + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINT1I", &c_n5, (int)6);
    }

L300:
    return 0;
} /* sint1i_d */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sintb1_d(int *n, int *inc, double *x, double *wsave, double *xh, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, k;
     double t1, t2;
     int kc, np1, ns2, ier1, modn;
     double dsum;
     int lnxh, lnwk, lnsv;
     double fnp1s4, xhold, srt3s2;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --xh;

    /* Function Body */
    *ier = 0;
    if ((i__1 = *n - 2) < 0) {
	goto L200;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L102:
    srt3s2 = sqrt(3.0) / 2.0;
    xhold = srt3s2 * (x[x_dim1 + 1] + x[(x_dim1 << 1) + 1]);
    x[(x_dim1 << 1) + 1] = srt3s2 * (x[x_dim1 + 1] - x[(x_dim1 << 1) + 1]);
    x[x_dim1 + 1] = xhold;
    goto L200;
L103:
    np1 = *n + 1;
    ns2 = *n / 2;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	kc = np1 - k;
	t1 = x[k * x_dim1 + 1] - x[kc * x_dim1 + 1];
	t2 = wsave[k] * (x[k * x_dim1 + 1] + x[kc * x_dim1 + 1]);
	xh[k + 1] = t1 + t2;
	xh[kc + 1] = t2 - t1;
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    xh[ns2 + 2] = x[(ns2 + 1) * x_dim1 + 1] * 4.0;
L124:
    xh[1] = 0.0;
    lnxh = np1;
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    lnwk = np1;

    rfft1f_d(&np1, &c__1, &xh[1], &lnxh, &wsave[ns2 + 1], &lnsv, work, &lnwk, &
	    ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINTB1", &c_n5, (int)6);
	goto L200;
    }

    if (np1 % 2 != 0) {
	goto L30;
    }
    xh[np1] += xh[np1];
L30:
    fnp1s4 = (double) np1 / 4.0;
    x[x_dim1 + 1] = fnp1s4 * xh[1];
    dsum = x[x_dim1 + 1];
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	x[(i__ - 1) * x_dim1 + 1] = fnp1s4 * xh[i__];
	dsum += fnp1s4 * xh[i__ - 1];
	x[i__ * x_dim1 + 1] = dsum;
/* L105: */
    }
    if (modn != 0) {
	goto L200;
    }
    x[*n * x_dim1 + 1] = fnp1s4 * xh[*n + 1];

L200:
    return 0;
} /* sintb1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sintf1_d(int *n, int *inc, double *x, double *wsave, double *xh, double *work, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset, i__1;
    int c__1 = 1;

    /* Builtin functions */

    /* Local variables */
     int i__, k;
     double t1, t2;
     int kc, np1, ns2, ier1, modn;
     double dsum;
     int lnxh, lnwk, lnsv;
     double sfnp1, xhold;
     double ssqrt3;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --xh;

    /* Function Body */
    *ier = 0;
    if ((i__1 = *n - 2) < 0) {
	goto L200;
    } else if (i__1 == 0) {
	goto L102;
    } else {
	goto L103;
    }
L102:
    ssqrt3 = 1.0 / sqrt(3.0);
    xhold = ssqrt3 * (x[x_dim1 + 1] + x[(x_dim1 << 1) + 1]);
    x[(x_dim1 << 1) + 1] = ssqrt3 * (x[x_dim1 + 1] - x[(x_dim1 << 1) + 1]);
    x[x_dim1 + 1] = xhold;
    goto L200;
L103:
    np1 = *n + 1;
    ns2 = *n / 2;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	kc = np1 - k;
	t1 = x[k * x_dim1 + 1] - x[kc * x_dim1 + 1];
	t2 = wsave[k] * (x[k * x_dim1 + 1] + x[kc * x_dim1 + 1]);
	xh[k + 1] = t1 + t2;
	xh[kc + 1] = t2 - t1;
/* L104: */
    }
    modn = *n % 2;
    if (modn == 0) {
	goto L124;
    }
    xh[ns2 + 2] = x[(ns2 + 1) * x_dim1 + 1] * 4.0;
L124:
    xh[1] = 0.0;
    lnxh = np1;
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    lnwk = np1;

    rfft1f_d(&np1, &c__1, &xh[1], &lnxh, &wsave[ns2 + 1], &lnsv, work, &lnwk, &
	    ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINTF1", &c_n5, (int)6);
	goto L200;
    }

    if (np1 % 2 != 0) {
	goto L30;
    }
    xh[np1] += xh[np1];
L30:
    sfnp1 = 1.0 / (double) np1;
    x[x_dim1 + 1] = xh[1] * .5;
    dsum = x[x_dim1 + 1];
    i__1 = *n;
    for (i__ = 3; i__ <= i__1; i__ += 2) {
	x[(i__ - 1) * x_dim1 + 1] = xh[i__] * .5;
	dsum += xh[i__ - 1] * .5;
	x[i__ * x_dim1 + 1] = dsum;
/* L105: */
    }
    if (modn != 0) {
	goto L200;
    }
    x[*n * x_dim1 + 1] = xh[*n + 1] * .5;
L200:
    return 0;
} /* sintf1_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sintmb_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int iw1, iw2, ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINTMB", &c__6, (int)6);
	goto L100;
    } else if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0))
	     + 4) {
	*ier = 2;
	//xerfft_d("SINTMB", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *lot * ((*n << 1) + 4)) {
	*ier = 3;
	//xerfft_d("SINTMB", &c__10, (int)6);
	goto L100;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("SINTMB", &c_n1, (int)6);
	goto L100;
    }

    iw1 = *lot + *lot + 1;
    iw2 = iw1 + *lot * (*n + 1);
    msntb1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], (double*)&work[1],
	     &work[iw1], &work[iw2], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINTMB", &c_n5, (int)6);
    }

L100:
    return 0;
} /* sintmb_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sintmf_d(int *lot, int *jump, int *n, int *inc, double *x, int *lenx, double *wsave, int *lensav, double *work, int *lenwrk, int *ier)
{
    /* System generated locals */
    int x_dim1, x_offset;

    /* Builtin functions */

    /* Local variables */
     int iw1, iw2, ier1;

    /* Parameter adjustments */
    x_dim1 = *inc;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    --wsave;
    --work;

    /* Function Body */
    *ier = 0;

    if (*lenx < (*lot - 1) * *jump + *inc * (*n - 1) + 1) {
	*ier = 1;
	//xerfft_d("SINTMF", &c__6, (int)6);
	goto L100;
    } else if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0))
	     + 4) {
	*ier = 2;
	//xerfft_d("SINTMF", &c__8, (int)6);
	goto L100;
    } else if (*lenwrk < *lot * ((*n << 1) + 4)) {
	*ier = 3;
	//xerfft_d("SINTMF", &c__10, (int)6);
	goto L100;
    } else if (! xercon_d(inc, jump, n, lot)) {
	*ier = 4;
	//xerfft_d("SINTMF", &c_n1, (int)6);
	goto L100;
    }

    iw1 = *lot + *lot + 1;
    iw2 = iw1 + *lot * (*n + 1);
    msntf1_d(lot, jump, n, inc, &x[x_offset], &wsave[1], (double*)&work[1],
	     &work[iw1], &work[iw2], &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINTMF", &c_n5, (int)6);
    }
L100:
    return 0;
} /* sintmf_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sintmi_d(int *n, double *wsave, int *lensav, int *ier)
{
    /* System generated locals */
    int i__1;

    /* Builtin functions */

    /* Local variables */
     int k;
     double dt;
     int np1, ns2, ier1, lnsv;

    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    *ier = 0;

    if (*lensav < *n / 2 + *n + (int) (log((double) (*n)) / log(2.0)) + 4) {
	*ier = 2;
	//xerfft_d("SINTMI", &c__3, (int)6);
	goto L300;
    }

    if (*n <= 1) {
	return 0;
    }
    ns2 = *n / 2;
    np1 = *n + 1;
    dt = 3.14159265358979323846 / (double) np1;
    i__1 = ns2;
    for (k = 1; k <= i__1; ++k) {
	wsave[k] = sin(k * dt) * 2.0;
/* L101: */
    }
    lnsv = np1 + (int) (log((double) np1) / log(2.0)) + 4;
    rfftmi_d(&np1, &wsave[ns2 + 1], &lnsv, &ier1);
    if (ier1 != 0) {
	*ier = 20;
	//xerfft_d("SINTMI", &c_n5, (int)6);
    }

L300:
    return 0;
} /* sintmi_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int tables_d(int *ido, int *ip, double *wa)
{
    /* System generated locals */
    int wa_dim1, wa_dim2, wa_offset, i__1, i__2;

    /* Builtin functions */

    /* Local variables */
     int i__, j;
     double tpi, arg1, arg2, arg3, arg4, argz;

    /* Parameter adjustments */
    wa_dim1 = *ido;
    wa_dim2 = *ip - 1;
    wa_offset = 1 + wa_dim1 * (1 + wa_dim2);
    wa -= wa_offset;

    /* Function Body */
    tpi = atan(1.0) * 8.0;
    argz = tpi / (double) (*ip);
    arg1 = tpi / (double) (*ido * *ip);
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
	arg2 = (double) (j - 1) * arg1;
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    arg3 = (double) (i__ - 1) * arg2;
	    wa[i__ + (j - 1 + wa_dim2) * wa_dim1] = cos(arg3);
	    wa[i__ + (j - 1 + (wa_dim2 << 1)) * wa_dim1] = sin(arg3);
/* L100: */
	}
	if (*ip <= 5) {
	    goto L110;
	}
	arg4 = (double) (j - 1) * argz;
	wa[(j - 1 + wa_dim2) * wa_dim1 + 1] = cos(arg4);
	wa[(j - 1 + (wa_dim2 << 1)) * wa_dim1 + 1] = sin(arg4);
L110:
	;
    }
    return 0;
} /* tables_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   AUTHORS:  PAUL N. SWARZTRAUBER AND RICHARD A. VALENT */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int w2r_d(int *ldr, int *ldw, int *l, int *m, double *r__, double *w)
{
    /* System generated locals */
    int r_dim1, r_offset, w_dim1, w_offset, i__1, i__2;

    /* Local variables */
     int i__, j;

    /* Parameter adjustments */
    r_dim1 = *ldr;
    r_offset = 1 + r_dim1;
    r__ -= r_offset;
    w_dim1 = *ldw;
    w_offset = 1 + w_dim1;
    w -= w_offset;

    /* Function Body */
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *l;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    r__[i__ + j * r_dim1] = w[i__ + j * w_dim1];
	}
    }
    return 0;
} /* w2r_ */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*   FFTPACK 5.1 */

/*   Authors:  Paul N. Swarztrauber and Richard A. Valent */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
int xercon_d(int *inc, int *jump, int *n, int *lot)
{
    /* System generated locals */
    int ret_val;

    /* Local variables */
     int i__, j, lcm, jnew;

/*     Definition: positive ints INC, JUMP, N and LOT are consistent */
/*                                                            ---------- */
/*     if I1*INC + J1*JUMP = I2*INC + J2*JUMP for I1,I2 < N and J1,J2 */
/*     < LOT implies I1=I2 and J1=J2. */

/*     For multiple FFTs to execute correctly, input parameters INC, */
/*     JUMP, N and LOT must be consistent ... otherwise at least one */
/*     array element mistakenly is transformed more than once. */

/*     XERCON = .TRUE. if and only if INC, JUMP, N and LOT are */
/*     consistent. */

/*     ------------------------------------------------------------------ */

/*     Compute I = greatest common divisor (INC, JUMP) */

    i__ = *inc;
    j = *jump;
L10:
    if (j != 0) {
	jnew = i__ % j;
	i__ = j;
	j = jnew;
	goto L10;
    }

/* Compute LCM = least common multiple (INC, JUMP) */

    lcm = *inc * *jump / i__;

/* Check consistency of INC, JUMP, N, LOT */

    if (lcm <= (*n - 1) * *inc && lcm <= (*lot - 1) * *jump) {
	ret_val = 0;
    } else {
	ret_val = 1;
    }

    return ret_val;
} /* xercon_ */
