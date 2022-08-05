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

/**
@file fftpack.h
@brief Fortran API for FFTPACK 5.1
@author Paul N. Swarztrauber and Richard A. Valent


FFTPACK 5.1, traditional Fortran API converted by f2c.

Authors:  Paul N. Swarztrauber and Richard A. Valent

Converted to C and cleaned up a little: Roy Zywina

This code is in the public domain.
*/

#ifndef _FFTPACKD_H_
#define _FFTPACKD_H_

#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif


/*
This type is binary compatable with C's "double _Complex" or
C++'s "std::complex<double>" or an array of length 2*N of
double. (or float if you redefine double)
*/
typedef struct{
  double r;
  double i;
}fft_complexd_t;

/* Fortran API */

/// FFT
int cfft1b_d(int *n, int *inc, fft_complexd_t *c__, int *
   	lenc, double *wsave, int *lensav, double *work, int *lenwrk,
   	int *ier);

/// IFFT
int cfft1f_d(int *n, int *inc, fft_complexd_t *c__, int *
    lenc, double *wsave, int *lensav, double *work, int *lenwrk,
    int *ier);

/// initialize constants array for #cfft1b_ and #cfft1f_d
int cfft1i_d(int *n, double *wsave, int *lensav,int *ier);

/// 2D FFT
int cfft2b_d(int *ldim, int *l, int *m, fft_complexd_t *
	c__, double *wsave, int *lensav, double *work, int *lenwrk,
	int *ier);

/// 2D IFFT
int cfft2f_d(int *ldim, int *l, int *m, fft_complexd_t *
	c__, double *wsave, int *lensav, double *work, int *lenwrk,
	int *ier);

/// initialize constants array for #cfft2b_d and #cfft2f_d
int cfft2i_d(int *l, int *m, double *wsave, int *
  lensav, int *ier);

/// initialize DCT-I constants
int cost1i_d(int *n, double *wsave, int *lensav,
  	int *ier);

/// DCT-I
int cost1b_d(int *n, int *inc, double *x, int *lenx,
  double *wsave, int *lensav, double *work, int *lenwrk, int *ier);

/// DCT-I with scaling applied to properly invert
int cost1f_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);


/// initialize constants for DCT
int cosq1i_d(int *n, double *wsave, int *lensav,
  	int *ier);
/// DCT (DCT-III)
int cosq1f_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
/// IDCT (DCT-II)
int cosq1b_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);

// DST 2 and 3 (aka DST and IDST)

/// DST (DST-III)
int sinq1b_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
/// IDST (DST-II)
int sinq1f_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
/// initialize constants for #sinq1b_d and #sinq1f
int sinq1i_d(int *n, double *wsave, int *lensav, int *ier);

/// DST (DST-I)
int sint1b_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
/// IDST (DST-I)
int sint1f_d(int *n, int *inc, double *x, int *lenx,
    double *wsave, int *lensav, double *work, int *lenwrk, int *ier);
/// initialize constants for #sint1b_d and #sint1f
int sint1i_d(int *n, double *wsave, int *lensav, int *ier);

/// RFFT init
int rfft1i_d(int *n, double *wsave, int *lensav, int *ier);
/// RFFT
int rfft1f_d(int *n, int *inc, double *r__, int *
	lenr, double *wsave, int *lensav, double *work, int *lenwrk,
	int *ier);
/// IRFFT
int rfft1b_d(int *n, int *inc, double *r__, int *
	lenr, double *wsave, int *lensav, double *work, int *lenwrk,
	int *ier);

/// multi DCT init
int cosqmi_d(int *n, double *wsave, int *lensav,int *ier);
/// multi DCT-III
int cosqmf_d(int *lot, int *jump, int *n, int
	*inc, double *x, int *lenx, double *wsave, int *lensav, double *
	work, int *lenwrk, int *ier);
/// multi DCT-II
int cosqmb_d(int *lot, int *jump, int *n, int
	*inc, double *x, int *lenx, double *wsave, int *lensav, double *
	work, int *lenwrk, int *ier);

#ifdef __cplusplus
}; // extern"C"
#endif

#endif
