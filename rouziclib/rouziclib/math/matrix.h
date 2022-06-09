extern double matrix_determinant(double *a, int ndim, int width);
extern void matrix_inverse(double *num, double *inverse, int ndim);
extern void matrix_multiplication(double *a, double *b, double *c, int m, int n, int q);
#ifdef MPFR
extern void matrix_determinant_mpfr(real det, real *a, int ndim, int width);
extern void matrix_inverse_mpfr(real *num, real *inverse, int ndim);
extern void matrix_multiplication_mpfr(real *a, real *b, real *c, int m, int n, int q);
#endif
