int find_res_taken(int *res_taken, int count)
{
	// Pick result ID
	for (int i=0; i < count; i++)
		if (res_taken[i] == 0)
		{
			res_taken[i] = 1;
			return i;
		}

	return -1;	// won't happen
}

void sym_move(symbol_data_t *sym, size_t *sym_count, int dst, int src)
{
	memmove(&sym[dst], &sym[src], (*sym_count - src) * sizeof(symbol_data_t));
	*sym_count -= src - dst;

	// Update match IDs
	for (int is=0; is < *sym_count; is++)
		if (sym[is].match >= dst)
			sym[is].match -= src - dst;
}

void print_any_var(buffer_t *prog, symbol_data_t *sym)
{
	// Print value or variable as it was written
	if (sym->type == sym_value || sym->type == sym_variable)
		bufprintf(prog, " %.*s", sym->p_len, sym->p);

	// Print result variable
	else if (sym->type == sym_result_real || sym->type == sym_result_int)
		bufprintf(prog, " %c%d", sym->type == sym_result_real ? 'v' : 'i', sym->result_id);
}

symbol_data_t *expression_to_symbol_list(const char *expression, buffer_t *comp_log, int verbose, int *max_depth, size_t *sym_count, size_t *sym_as)
{
	int i, is, n=0, cant_be_operator=1, depth=0;
	symbol_data_t *sym=NULL;
	char *endptr, name[33], red_str[8], grey_str[8];
	size_t len = strlen(expression);
	const char *p = expression, *end = &expression[len];

	sprint_unicode(red_str, sc_red);
	sprint_unicode(grey_str, sc_grey);

	// Map the string as symbols
	while (1)
	{
loop_start:
		p = skip_whitespace(&p[n]);
		if (p == end)
			break;

		// Prepare new symbol
		is = *sym_count;
		alloc_enough(&sym, *sym_count+=1, sym_as, sizeof(symbol_data_t), 2.);
		sym[is].p = p;
		sym[is].match = -1;
		sym[is].result_id = -1;
		sym[is].depth = depth;
		*max_depth = MAXN(*max_depth, depth);

		// Try to read operators
		if (isalnum(p[0]) == 0)
		{
			n = 0;
			sscanf(p, "%32[-+*/%%%^=<>!]%n", name, &n);

			if (cant_be_operator==0)
			{
				if (n)
				{
					if (verbose) bufprintf(comp_log, "Operator %s, %d chars\n", name, n);
					sym[is].type = sym_operator;

					switch (p[0])
					{
						case '^':	// covers both ^ and ^-
							sym[is].operator_priority = 5;
							n = 1;
							if (p[1] == '-')
								n = 2;
							break;
						case '*':
						case '/':
						case '%':
							sym[is].operator_priority = 3;
							n = 1;
							break;
						case '+':
						case '-':
							sym[is].operator_priority = 2;
							n = 1;
							break;
						case '=':
						case '<':
						case '>':
						case '!':
							sym[is].operator_priority = 1;
							break;
					}
					sym[is].p = p;
					sym[is].p_len = n;

					cant_be_operator = 1;
					goto loop_start;
				}
				else if (p[0] == ',')
				{
					n = 1;
					if (verbose) bufprintf(comp_log, "Comma\n");
					sym[is].type = sym_comma;
					cant_be_operator = 1;
					goto loop_start;
				}
			}
			else
			{
				// Try to read number
				strtod(p, &endptr);
				n = endptr - p;

				// Handle negation by turning it into subtraction
				if (p[0] == '-' && n == 0)	// if there's a '-' not part of a value
				{
					// Handle negation by inserting a 0 value symbol
					sym[is].type = sym_value;
					sym[is].p = "0";
					sym[is].p_len = 1;

					// Add '-' operator
					is = *sym_count;
					alloc_enough(&sym, *sym_count+=1, sym_as, sizeof(symbol_data_t), 2.);
					sym[is].type = sym_operator;
					sym[is].p = p;
					sym[is].p_len = 1;
					sym[is].depth = depth;
					sym[is].operator_priority = 4;
					cant_be_operator = 1;
					n = 1;
					goto loop_start;
				}
			}
		}

		// Try to read number		
		strtod(p, &endptr);	// sscanf("0.5erf", "%*g%n", &n) fails
		n = endptr - p;
		if (n)
		{
			intmax_t doz_frac = 12;
			buffer_t doz_conv={0};

			// Convert dozenal numbers to fractions
			while (p[n] == ';')
			{
				// Avoid skipping whitespace to find the next number
				if (isspace(p[n+1]))
					break;

				// Find next number
				int n2=0;
				strtod(&p[n+1], &endptr);
				n2 = endptr - &p[n+1];

				// Process element
				if (n2)
				{
					// Start fractional expression
					if (doz_conv.buf == NULL)
						bufprintf(&doz_conv, "%.*s", n, p);

					// Continue fraction
					bufprintf(&doz_conv, "+%.*s/%" PRIdMAX, n2, &p[n+1], doz_frac);

					doz_frac *= 12;
					n += n2+1;
				}
				else
					break;
			}

			if (verbose) bufprintf(comp_log, "Value, %d chars\n", n);
			sym[is].type = sym_value;
			sym[is].p = p;
			sym[is].p_len = n;
			sym[is].can_imply_mul_with_prev = 1;
			sym[is].can_imply_mul_with_next = 1;
			cant_be_operator = 0;

			// Finish and register dozenal fraction
			if (doz_conv.buf)
			{
				sym[is].p = doz_conv.buf;
				sym[is].p_len = doz_conv.len;
				sym[is].p_to_free = 1;
			}

			goto loop_start;
		}

		// Try to read variable/function name
		if (isalpha(p[0]))
		{
			n = 0;
			sscanf(p, "%32[a-zA-Z0-9_.]%n", name, &n);
			if (n)
			{
				if (verbose) bufprintf(comp_log, "%s named '%s', %d chars\n", p[n]=='(' ? "Function" : "Variable", name, n);
				sym[is].type = p[n]=='(' ? sym_function : sym_variable;
				sym[is].p = p;
				sym[is].p_len = n;
				sym[is].can_imply_mul_with_prev = 1;
				sym[is].can_imply_mul_with_next = (sym[is].type == sym_variable);
				cant_be_operator = 0;
				goto loop_start;
			}
		}

		// Try to read brackets
		if (p[0] == '(')
		{
			n = 1;
			sym[is].type = sym_bracket_open;
			if (is > 0)
				if (sym[is-1].type == sym_function)
					sym[is].type = sym_arg_open;
			if (verbose) bufprintf(comp_log, "%s\n", sym[is].type==sym_arg_open ? "Function bracket open" : "Bracket open");
			sym[is].can_imply_mul_with_prev = (sym[is].type == sym_bracket_open);
			cant_be_operator = 1;
			depth++;
			goto loop_start;
		}

		if (p[0] == ')')
		{
			n = 1;
			sym[is].type = sym_bracket_close;
			sym[is].can_imply_mul_with_next = 1;

			// Match brackets by finding the first preceding unmatched '('
			for (i=is-1; i >= 0; i--)
			{
				if ((sym[i].type == sym_bracket_open || sym[i].type == sym_arg_open) && sym[i].match == -1)
				{
					sym[i].match = is;
					sym[is].match = i;

					// If the brackets are part of a function call
					if (sym[i].type == sym_arg_open)
					{
						sym[is].type = sym_arg_close;
						sym[i-1].match = is;			// indicate where the function call ends
					}

					break;
				}
			}

			if (verbose) bufprintf(comp_log, sym[is].type == sym_bracket_close ? "Bracket close\n" : "Function bracket close\n");

			// If the ')' remains unmatched
			if (sym[is].match == -1)
			{
				bufprintf(comp_log, "%sUnmatched ')' at position %d%s\n", red_str, is, grey_str);
				*sym_count = 0;
				free_null(&sym);
				return NULL;
			}

			cant_be_operator = 0;
			depth--;
			goto loop_start;
		}

		// Unidentified character
		if (p[0] > 0)
			bufprintf(comp_log, "%sCharacter '%c' (0x%x) unidentified%s\n", red_str, p[0], p[0], grey_str);
		else
			bufprintf(comp_log, "%sCharacter 0x%x unidentified%s\n", red_str, p[0], grey_str);
		n = 1;
		*sym_count = 0;
		free_null(&sym);
		return NULL;
	}

	// Check for unmatched brackets
	for (is=0; is < *sym_count; is++)
		if ((sym[is].type == sym_bracket_open || sym[is].type == sym_arg_open) && sym[is].match == -1)
		{
			bufprintf(comp_log, "%sUnmatched '(' at position %d%s\n", red_str, is, grey_str);
			*sym_count = 0;
			free_null(&sym);
			return NULL;
		}

	// Turned implied multiplications into operators
	for (is=1; is < *sym_count; is++)
	{
		if (sym[is-1].can_imply_mul_with_next && sym[is].can_imply_mul_with_prev)
		{
			// Move everything one place to make room for the operator
			alloc_enough(&sym, *sym_count+1, sym_as, sizeof(symbol_data_t), 2.);
			sym_move(sym, sym_count, is+1, is);

			// Add operator
			if (verbose) bufprintf(comp_log, "Implied '*' operator added\n");
			sym[is].type = sym_operator;
			sym[is].p = "*";
			sym[is].p_len = 1;
			sym[is].operator_priority = 3;
			sym[is].can_imply_mul_with_prev = 0;
			sym[is].can_imply_mul_with_next = 0;
		}
	}

	return sym;
}

buffer_t expression_to_rlip_listing(const char *expression, const char *cmd_suffix, int use_real, buffer_t *comp_log, int verbose)
{
	buffer_t prog_s={0}, *prog=&prog_s;
	int i, is, max_depth=0;
	symbol_data_t *sym=NULL;
	size_t sym_count=0, sym_as=0;
	char red_str[8], grey_str[8];
	int *res_taken_r=NULL, *res_taken_i=NULL;
	char var_decl = use_real ? 'r' : 'd';

	sprint_unicode(red_str, sc_red);
	sprint_unicode(grey_str, sc_grey);

	// Map the string as symbols
	sym = expression_to_symbol_list(expression, comp_log, verbose, &max_depth, &sym_count, &sym_as);
	if (sym == NULL)
		goto invalid_expr;

	int id, max_prio, max_prio_pos, result_id;
	size_t res_taken_count = sym_count;
	res_taken_r = calloc(res_taken_count, sizeof(int));		// result ID taken (0 or 1)
	res_taken_i = calloc(res_taken_count, sizeof(int));

	// Go through every depth
	for (id = max_depth; id >= 0; id--)
	{
		for (is = sym_count-1; is >= 0; is--)
		{
			// Process function calls
			if (sym[is].depth == id && sym[is].type == sym_function)
			{
				// Free result IDs that are about to be consumed
				for (i = is+1; i <= sym[is].match; i++)
				{
					if (sym[i].type == sym_result_real)
						res_taken_r[sym[i].result_id] = 0;

					if (sym[i].type == sym_result_int)
						res_taken_i[sym[i].result_id] = 0;
				}

				// Pick result ID
				result_id = find_res_taken(res_taken_r, res_taken_count);

				// Print start of command
				bufprintf(prog, "%c v%d = %.*s%s", var_decl, result_id, sym[is].p_len, sym[is].p, cmd_suffix);

				// Go through all arguments and print them
				for (i = is+1; i <= sym[is].match; i++)
					print_any_var(prog, &sym[i]);
				bufprintf(prog, "\n");

				// Remove everything that was just used from the sym array
				sym_move(sym, &sym_count, is+1, sym[is].match+1);

				// Turn command call into result
				sym[is].type = sym_result_real;
				sym[is].result_id = result_id;
			}

			// Process brackets that contain no operator (therefore contain only one symbol)
			if (sym[is].depth == id && sym[is].type == sym_bracket_open)
			{
				// Check that it contains only one symbol
				if (sym[is].match != is + 2)
				{
					bufprintf(comp_log, "%sBracket '%.*s' doesn't reduce to one symbol, an operator must be missing.%s\n", red_str, sym[sym[is].match].p_len + sym[sym[is].match].p - sym[is].p, sym[is].p, grey_str);
					goto invalid_expr;
				}

				// Move symbol to the position and depth of the bracket
				sym[is].type = sym[is+1].type;
				sym[is].result_id = sym[is+1].result_id;
				sym[is].p = sym[is+1].p;
				sym[is].p_len = sym[is+1].p_len;

				// Remove the two symbols
				sym_move(sym, &sym_count, is+1, is+3);
			}
		}

prio_loop_start:
		max_prio = 0;

		// Find the highest priority operator level
		for (is=0; is < sym_count; is++)
			if (sym[is].depth == id && sym[is].type == sym_operator && sym[is].operator_priority > max_prio)
				max_prio = sym[is].operator_priority;

		// Find the first top priority operator to process
		for (is=0; is < sym_count; is++)
			if (sym[is].depth == id && sym[is].type == sym_operator)
				if (sym[is].operator_priority == max_prio)
				{
					max_prio_pos = is;

					// Stop at the first operator if operator isn't ^ or ^-
					if (max_prio < 5)
						break;
				}

		// Process an operator
		if (max_prio > 0)
		{
			is = max_prio_pos;

			// Identify operator
			int is_comparison = 0;
			const char *identified_op=NULL, *identified_cmd=NULL;
			const char *op[] =  {  "==",   "<",    ">",    "<=",   ">=",   "!=",   "+",   "-",   "*",   "/",  "%",   "^",   "^-" };
			const char *cmd[] = { "cmpr", "cmpr", "cmpr", "cmpr", "cmpr", "cmpr", "add", "sub", "mul", "div", "mod", "pow", "pow" };
			for (i=0; i < sizeof(op)/sizeof(*op); i++)
				if (compare_varlen_word_to_fixlen_word(sym[is].p, sym[is].p_len, op[i]))
				{
					identified_op = op[i];
					identified_cmd = cmd[i];
					is_comparison = (strcmp(identified_cmd, "cmpr") == 0);
					break;
				}

			// Make sure operator isn't the final symbol
			if (is == sym_count-1)
			{
				bufprintf(comp_log, "%sOperator '%.*s' is the final symbol.%s\n", red_str, sym[is].p_len, sym[is].p, grey_str);
				goto invalid_expr;
			}

			// Free result IDs that are about to be consumed
			for (i = is-1; i <= is+1; i+=2)
			{
				if (sym[i].type == sym_result_real)
					res_taken_r[sym[i].result_id] = 0;

				if (sym[i].type == sym_result_int)
					res_taken_i[sym[i].result_id] = 0;
			}

			// Pick result ID
			result_id = find_res_taken(is_comparison ? res_taken_i : res_taken_r, res_taken_count);

			// Handle ^- exception (negative exponent) by inserting extra command
			if (compare_varlen_word_to_fixlen_word(sym[is].p, sym[is].p_len, "^-"))
			{
				int result_id2 = find_res_taken(res_taken_r, res_taken_count);

				// Print neg command
				bufprintf(prog, "%c v%d = sub%s 0", var_decl, result_id2, cmd_suffix);
				i = is+1;
				print_any_var(prog, &sym[i]);
				bufprintf(prog, "\n");

				// Replace input with result
				sym[i].type = sym_result_real;
				sym[i].result_id = result_id2;

				res_taken_r[result_id2] = 0;
			}

			// Print start of command
			if (is_comparison)
				bufprintf(prog, "i i%d = %s", result_id, identified_cmd);
			else
				bufprintf(prog, "%c v%d = %s%s", var_decl, result_id, identified_cmd, cmd_suffix);

			// Go through all two arguments and print them
			for (i = is-1; i <= is+1; i+=2)
			{
				print_any_var(prog, &sym[i]);

				// Print comparison operator
				if (is_comparison && i == is-1)
					bufprintf(prog, " %s", identified_op);
			}
			bufprintf(prog, "\n");

			// Replace the 3 symbols with 1 result symbol
			sym_move(sym, &sym_count, is, is+2);
			sym[is-1].type = is_comparison ? sym_result_int : sym_result_real;
			sym[is-1].result_id = result_id;
			sym[is-1].can_imply_mul_with_prev = 1;
			sym[is-1].can_imply_mul_with_next = 1;

			goto prio_loop_start;
		}
	}

	// Check that only one symbol remains
	if (sym_count != 1)
	{
		bufprintf(comp_log, "%s%d symbols remain instead of the expected 1.%s\n", red_str, sym_count, grey_str);
		goto invalid_expr;
	}

	// Print return value
	bufprintf(prog, "%s", use_real ? "return_real" : "return");
	print_any_var(prog, &sym[0]);
	bufprintf(prog, "\n");

	if (0)
	{
invalid_expr:
		free_buf(prog);
	}

	free(res_taken_r);
	free(res_taken_i);
	for (is=0; is < sym_count; is++)
		if (sym[is].p_to_free)
			free((char *) sym[is].p);
	free(sym);

	return prog_s;
}

rlip_t rlip_expression_compile(const char *expression, rlip_inputs_t *inputs, int input_count, int real, buffer_t *comp_log)
{
	buffer_t listing;
	rlip_t prog={0};

	// Expression to listing
	if (real)
		listing = expression_to_rlip_listing(expression, "_", 1, comp_log, 0);
	else
		listing = expression_to_rlip_listing(expression, "", 0, comp_log, 0);

	// Listing to opcodes
	if (listing.len)
		prog = rlip_compile(listing.buf, inputs, input_count, 1, comp_log);
	free_buf(&listing);

	return prog;
}

double rlip_expression_interp_double(const char *expression, buffer_t *comp_log)
{
	// Expression to listing
	buffer_t listing = expression_to_rlip_listing(expression, "", 0, comp_log, 0);
	if (listing.len == 0)
	{
		free_buf(&listing);
		return NAN;
	}

	// Listing to opcodes
	rlip_inputs_t inputs[] = { RLIP_FUNC };
	rlip_t prog = rlip_compile(listing.buf, inputs, sizeof(inputs)/sizeof(*inputs), 1, comp_log);
	free_buf(&listing);

	// Execute opcodes
	volatile int exec_on = 1;
	prog.exec_on = &exec_on;
	rlip_execute_opcode(&prog);

	if (prog.valid_prog == 0)
	{
		free_rlip(&prog);
		return NAN;
	}

	// Return value
	double v = prog.return_value[0];
	free_rlip(&prog);

	return v;
}

int rlip_expression_interp_real(uint8_t *result, const char *expression, rlip_inputs_t *inputs, int input_count, buffer_t *comp_log)
{
	const rlip_real_functions_t *func=NULL;

	// Find functions
	for (int i=0; i < input_count; i++)
		if (strcmp(inputs[i].name, "rlip_real_functions")==0)
		{
			func = inputs[i].ptr;
			break;
		}

	if (func==NULL)
		return 0;

	// Expression to listing
	buffer_t listing = expression_to_rlip_listing(expression, "_", 1, comp_log, 0);
	if (listing.len == 0)
	{
		free_buf(&listing);
		return 0;
	}

	// Listing to opcodes
	rlip_t prog = rlip_compile(listing.buf, inputs, input_count, 1, comp_log);
	free_buf(&listing);

	if (prog.valid_prog == 0)
	{
		free_rlip(&prog);
		func->set_nan(result);
		return 0;
	}

	// Execute opcodes
	volatile int exec_on = 1;
	prog.exec_on = &exec_on;
	rlip_execute_opcode(&prog);

	// Set return value
	func->set(result, &prog.return_real[0]);

	free_rlip(&prog);

	return 1;
}

#ifdef RLIP_REAL_DOUBLEDOUBLE
ddouble_t rlip_expression_interp_ddouble(const char *expression, buffer_t *comp_log)
{
	ddouble_t result={0};
	rlip_inputs_t inputs[] = { RLIP_REAL_DOUBLEDOUBLE };

	rlip_expression_interp_real((uint8_t *) &result, expression, inputs, sizeof(inputs)/sizeof(*inputs), comp_log);

	return result;
}
#endif

#ifdef RLIP_REAL_MPFR
int rlip_expression_interp_mpfr(mpfr_t *result, const char *expression, buffer_t *comp_log)
{
	rlip_inputs_t inputs[] = { RLIP_REAL_MPFR };

	return rlip_expression_interp_real(result, expression, inputs, sizeof(inputs)/sizeof(*inputs), comp_log);
}
#endif
