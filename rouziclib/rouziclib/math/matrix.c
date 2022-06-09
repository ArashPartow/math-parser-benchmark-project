double matrix_determinant(double *a, int ndim, int width)
{
	double s=1., det=0., *b;
	int i, j, m, n, c;

	if (ndim == 1)
		return a[0*width+0];

	b = calloc(width*width, sizeof(double));

	for (c=0; c<ndim; c++)
	{
		m = 0;
		n = 0;

		for (i=0; i<ndim; i++)
		{
			for (j=0; j<ndim; j++)
			{
				b[i*width+j] = 0.;
				if (i != 0 && j != c)
				{
					b[m*width+n] = a[i*width+j];
					if (n < ndim-2)
						n++;
					else
					{
						n = 0;
						m++;
					}
				}
			}
		}

		det += s * (a[0*width+c] * matrix_determinant(b, ndim-1, width));
		s = -s;
	}

	free (b);

	return det;
}

void matrix_inverse(double *num, double *inverse, int ndim)
{
	double det, *b, *fac;
	int p, q, m, n, i, j;

	det = matrix_determinant(num, ndim, ndim);

	if (det==0.)
	{
		memset(inverse, 0, ndim*ndim*sizeof(double));	// can't invert matrix
		fprintf_rl(stderr, "Determinant of the matrix is 0\n");
		return ;
	}

	b = calloc(ndim*ndim, sizeof(double));
	fac = calloc(ndim*ndim, sizeof(double));

	// cofactor
	for (q=0; q<ndim; q++)
	{
		for (p=0; p<ndim; p++)
		{
			m = 0;
			n = 0;

			for (i=0; i<ndim; i++)
			{
				for (j=0; j<ndim; j++)
				{
					if (i!=q && j!=p)
					{
						b[m*ndim+n] = num[i*ndim+j];
						if (n < ndim-2)
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}

			fac[q*ndim+p] = pow(-1., q + p) * matrix_determinant(b, ndim-1, ndim);
		}
	}

	// transposition
	for (i=0; i<ndim; i++)
		for (j=0; j<ndim; j++)
			inverse[i*ndim+j] = fac[j*ndim+i] / det;

	free (fac);
	free (b);
}

void matrix_multiplication(double *a, double *b, double *c, int m, int n, int q)	// c=a*b, a dim is m*n, b dim is n*q, c dim is m*q
{
	int im, in, iq;

	memset(c, 0, m*q*sizeof(double));

	for (im=0; im<m; im++)
		for (iq=0; iq<q; iq++)
			for (in=0; in<n; in++)
				c[im*q+iq] += a[im*n+in] * b[in*q+iq];
}

#ifdef MPFR
void matrix_determinant_mpfr(real det, real *a, int ndim, int width)
{
	double s=1.;
	real d, *b;
	int i, j, m, n, c;

	if (ndim == 1)
	{
		r_set(det, a[0*width+0]);
		return ;
	}

	r_init(d);
	b = calloc(width*width, sizeof(real));
	for (i=0; i<width*width, i++)
		r_init(b[i]);

	for (c=0; c<ndim; c++)
	{
		m = 0;
		n = 0;

		for (i=0; i<ndim; i++)
		{
			for (j=0; j<ndim; j++)
			{
				r_setd(b[i*width+j], 0.);
				if (i != 0 && j != c)
				{
					r_set(b[m*width+n], a[i*width+j]);
					if (n < ndim-2)
						n++;
					else
					{
						n = 0;
						m++;
					}
				}
			}
		}

		//det += s * (a[0*width+c] * matrix_determinant(b, ndim-1, width));
		matrix_determinant_mpfr(d, b, ndim-1, width);
		r_mul(d, a[0*width+c]);
		r_muld(d, s);
		r_add(det, d);

		s = -s;
	}

	for (i=0; i<width*width, i++)
		r_free(b[i]);
	free (b);
	r_free(d);
}

void matrix_inverse_mpfr(real *num, real *inverse, int ndim)
{
	real det, *b, *fac;
	int p, q, m, n, i, j;

	r_init(det);
	matrix_determinant(det, num, ndim, ndim);

	if (mpfr_cmp_d(det, 0.)==0)		// can't invert the matrix
	{
		for (i=0; i<ndim*ndim; i++)
			r_setd(inverse[i], 0.);
		fprintf_rl(stderr, "Determinant of the matrix is 0\n");
		return ;
	}

	b = calloc(ndim*ndim, sizeof(real));
	for (i=0; i<ndim*ndim, i++)
		r_init(b[i]);

	fac = calloc(ndim*ndim, sizeof(real));
	for (i=0; i<ndim*ndim, i++)
		r_init(fac[i]);

	// cofactor
	for (q=0; q<ndim; q++)
	{
		for (p=0; p<ndim; p++)
		{
			m = 0;
			n = 0;

			for (i=0; i<ndim; i++)
			{
				for (j=0; j<ndim; j++)
				{
					if (i!=q && j!=p)
					{
						r_set(b[m*ndim+n], num[i*ndim+j]);
						if (n < ndim-2)
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}

			//fac[q*ndim+p] = pow(-1., q + p) * matrix_determinant(b, ndim-1, ndim);
			matrix_determinant_mpfr(fac[q*ndim+p], b, ndim-1, ndim);
			r_muld(fac[q*ndim+p], pow(-1., q + p));
		}
	}

	// transposition
	for (i=0; i<ndim; i++)
		for (j=0; j<ndim; j++)
			r_rdiv(inverse[i*ndim+j], fac[j*ndim+i], det);

	for (i=0; i<ndim*ndim, i++)
		r_free(fac[i]);
	free (fac);

	for (i=0; i<ndim*ndim, i++)
		r_free(b[i]);
	free (b);

	r_free(det);
}

void matrix_multiplication_mpfr(real *a, real *b, real *c, int m, int n, int q)	// c=a*b, a dim is m*n, b dim is n*q, c dim is m*q
{
	int im, in, iq;

	for (i=0; i<m*q; i++)
		r_setd(c[i], 0.);

	for (im=0; im<m; im++)
		for (iq=0; iq<q; iq++)
			for (in=0; in<n; in++)
				r_rfma(c[im*q+iq], a[im*n+in]. b[in*q+iq], c[im*q+iq]);
}
#endif
