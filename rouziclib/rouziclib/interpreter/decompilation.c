const char *rlip_get_op_name(enum opcode op)
{
	// To update copy the enum and apply this regex:
	// s/\t\([^, ]*\).*$/\t\tcase \1:    \treturn "\1";
	switch (op)
	{
		case op_1word_ops:    	return "op_1word_ops";
		case op_end:    	return "op_end";

		case op_2word_ops:    	return "op_2word_ops";
		case op_ret_d:    	return "op_ret_d";
		case op_ret_r:    	return "op_ret_r";
		case op_jmp:    	return "op_jmp";
		case nop_jmp:    	return "nop_jmp";
		case op_set0_d:    	return "op_set0_d";
		case op_set0_i:    	return "op_set0_i";
		case op_inc1_d:    	return "op_inc1_d";
		case op_inc1_i:    	return "op_inc1_i";

		case op_3word_ops:    	return "op_3word_ops";
		case op_ret_dd:    	return "op_ret_dd";
		case op_ret_rr:    	return "op_ret_rr";
		case op_load_d:    	return "op_load_d";
		case op_load_i:    	return "op_load_i";
		case op_load_r:    	return "op_load_r";
		case op_set_d:    	return "op_set_d";
		case op_set_i:    	return "op_set_i";
		case op_set_r:    	return "op_set_r";
		case op_cvt_i_d:    	return "op_cvt_i_d";
		case op_cvt_d_i:    	return "op_cvt_d_i";
		case op_cvt_r_d:    	return "op_cvt_r_d";
		case op_cvt_d_r:    	return "op_cvt_d_r";
		case op_cvt_r_i:    	return "op_cvt_r_i";
		case op_cvt_i_r:    	return "op_cvt_i_r";
		case op_sq_d:    	return "op_sq_d";
		case op_sqrt_d:    	return "op_sqrt_d";

		case op_jmp_cond:    	return "op_jmp_cond";
		case nop_jmp_cond:    	return "nop_jmp_cond";
		case op_func0_d:    	return "op_func0_d";
		case op_func0_r:    	return "op_func0_r";

		case op_4word_ops:    	return "op_4word_ops";
		case op_ret_ddd:    	return "op_ret_ddd";
		case op_ret_rrr:    	return "op_ret_rrr";
		case op_add_dd:    	return "op_add_dd";
		case op_add_ii:    	return "op_add_ii";
		case op_sub_dd:    	return "op_sub_dd";
		case op_sub_ii:    	return "op_sub_ii";
		case op_mul_dd:    	return "op_mul_dd";
		case op_mul_ii:    	return "op_mul_ii";
		case op_div_dd:    	return "op_div_dd";
		case op_div_ii:    	return "op_div_ii";
		case op_mod_ii:    	return "op_mod_ii";
		case op_mod_dd:    	return "op_mod_dd";
		case op_sqadd_dd:    	return "op_sqadd_dd";
		case op_sqsub_dd:    	return "op_sqsub_dd";
		case op_diff_dd:    	return "op_diff_dd";

		case op_and_ii:    	return "op_and_ii";
		case op_or_ii:    	return "op_or_ii";

		case op_cmp_dd_eq:    	return "op_cmp_dd_eq";
		case op_cmp_ii_eq:    	return "op_cmp_ii_eq";
		case op_cmp_rr_eq:    	return "op_cmp_rr_eq";
		case op_cmp_dd_ne:    	return "op_cmp_dd_ne";
		case op_cmp_ii_ne:    	return "op_cmp_ii_ne";
		case op_cmp_rr_ne:    	return "op_cmp_rr_ne";
		case op_cmp_dd_lt:    	return "op_cmp_dd_lt";
		case op_cmp_ii_lt:    	return "op_cmp_ii_lt";
		case op_cmp_rr_lt:    	return "op_cmp_rr_lt";
		case op_cmp_dd_le:    	return "op_cmp_dd_le";
		case op_cmp_ii_le:    	return "op_cmp_ii_le";
		case op_cmp_rr_le:    	return "op_cmp_rr_le";
		case op_cmp_dd_gt:    	return "op_cmp_dd_gt";
		case op_cmp_ii_gt:    	return "op_cmp_ii_gt";
		case op_cmp_rr_gt:    	return "op_cmp_rr_gt";
		case op_cmp_dd_ge:    	return "op_cmp_dd_ge";
		case op_cmp_ii_ge:    	return "op_cmp_ii_ge";
		case op_cmp_rr_ge:    	return "op_cmp_rr_ge";
		case op_func1_dd:    	return "op_func1_dd";
		case op_func1_di:    	return "op_func1_di";
		case op_func1_ii:    	return "op_func1_ii";
		case op_func1_rr:    	return "op_func1_rr";

		case op_5word_ops:    	return "op_5word_ops";
		case op_ret_dddd:    	return "op_ret_dddd";
		case op_ret_rrrr:    	return "op_ret_rrrr";
		case op_aad_ddd:    	return "op_aad_ddd";
		case op_mmul_ddd:    	return "op_mmul_ddd";
		case op_mad_ddd:    	return "op_mad_ddd";
		case op_adm_ddd:    	return "op_adm_ddd";
		case op_func2_ddd:    	return "op_func2_ddd";
		case op_func2_rrr:    	return "op_func2_rrr";

		case op_6word_ops:    	return "op_6word_ops";
		case op_func3_dddd:    	return "op_func3_dddd";
		case op_func3_dddi:    	return "op_func3_dddi";
		case op_func3_rrrr:    	return "op_func3_rrrr";

		case op_7word_ops:    	return "op_7word_ops";
		case op_8word_ops:    	return "op_8word_ops";
	}

	return "Unknown op";
}

buffer_t rlip_decompile(rlip_t *d)
{
	int i;
	buffer_t buffer={0}, *b=&buffer;
	opint_t *op = d->op;
	const char *opname;

	while (1)
	{
		// Get op name
		opname = rlip_get_op_name(op[0]);
		bufprintf(b, "%s\t", opname);

		if (strcmp(opname, "Unknown op")==0)
			return buffer;

		// Print arguments
		for (i=1; i < op[0] >> 10; i++)
			bufprintf(b, "%6d\t", op[i]);
		bufprintf(b, "\n");

		if (op[0] == op_end)
			return buffer;

		op = &op[op[0] >> 10];
	}

	return buffer;
}
