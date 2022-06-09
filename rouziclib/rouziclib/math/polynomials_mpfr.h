#ifdef RL_MPFR

extern void eval_polynomial_mpfr(real_t y, real_t x, real_t *c, int degree);
extern void eval_chebyshev_polynomial_mpfr(real_t y, real_t x, real_t *cm, int degree);
extern double get_polynomial_error_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree, int errmode);

extern void polynomial_addition_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c);
extern void polynomial_subtraction_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c);
extern void polynomial_scalar_mul_mpfr(real_t *a, int adeg, real_t m, real_t *c);
extern int polynomial_multiplication_mpfr(real_t *a, int adeg, real_t *b, int bdeg, real_t *c, int cdeg);
extern real_t *polynomial_power_mpfr(real_t *a, int adeg, int n, int *maxdegp);
extern void polynomial_x_substitution_mpfr(real_t *a, int adeg, real_t *xs, int xsdeg, real_t *c);

extern real_t *chebyshev_coefs_mpfr(int degree);
extern void chebyshev_node_mpfr(real_t v, double degree, double node);

extern void polynomial_fit_on_points_mpfr(real_t *x, real_t *y, real_t *c, int degree);
extern void polynomial_fit_on_function_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree);
extern void chebyshev_multiplier_by_dct_mpfr(real_t v, real_t *y, int p_count, int id);
extern void polynomial_fit_on_points_by_dct_mpfr(real_t *y, int p_count, real_t start, real_t end, real_t *c, int degree);
extern real_t *polynomial_function_to_points_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, int p_count);
extern void polynomial_fit_on_function_by_dct_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *c, int degree);
extern void chebyshev_analysis_on_function_mpfr(void (*f)(real_t,real_t), real_t start, real_t end, real_t *cm, int degree, int p_count);
extern double reduce_digits_mpfr(void (*f)(real_t,real_t), real_t segstart, real_t segend, real_t *c, const int degree, int errmode, double added_error_thresh, double digits);

#endif
