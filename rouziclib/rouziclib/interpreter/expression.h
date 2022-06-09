enum symbol_type
{
	sym_none,
	sym_value,
	sym_operator,
	sym_variable,
	sym_function,
	sym_bracket_open,
	sym_bracket_close,
	sym_arg_open,
	sym_arg_close,
	sym_comma,
	sym_result_real,
	sym_result_int,
};

typedef struct
{
	enum symbol_type type;
	int depth, match;
	int operator_priority;
	int result_id;
	int can_imply_mul_with_prev, can_imply_mul_with_next;
	const char *p;
	int p_len, p_to_free;
} symbol_data_t;

extern symbol_data_t *expression_to_symbol_list(const char *expression, buffer_t *comp_log, int verbose, int *max_depth, size_t *sym_count, size_t *sym_as);
extern buffer_t expression_to_rlip_listing(const char *expression, const char *cmd_suffix, int use_real, buffer_t *comp_log, int verbose);
extern rlip_t rlip_expression_compile(const char *expression, rlip_inputs_t *inputs, int input_count, int real, buffer_t *comp_log);
extern double rlip_expression_interp_double(const char *expression, buffer_t *comp_log);
extern int rlip_expression_interp_real(uint8_t *result, const char *expression, rlip_inputs_t *inputs, int input_count, buffer_t *comp_log);
#ifdef RLIP_REAL_DOUBLEDOUBLE
extern ddouble_t rlip_expression_interp_ddouble(const char *expression, buffer_t *comp_log);
#endif
#ifdef RLIP_REAL_MPFR
extern int rlip_expression_interp_mpfr(mpfr_t *result, const char *expression, buffer_t *comp_log);
#endif

#define etof(expr) rlip_expression_interp_double(expr, NULL)
