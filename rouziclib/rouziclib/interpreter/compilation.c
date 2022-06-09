enum opcode_table
{
	table_none=0,
	table_vd,
	table_vi,
	table_vr,
	table_ptr,
	table_loc,
};

typedef struct 
{
	char *name;
	uint64_t hash;
	char *type;
	enum opcode_table table;	// table is 0 for not in a table (like function pointers), 1 for vd, 2 for vi, 3 for ptr
	size_t index;			// index is the index in the given table
} rlip_reg_t;

typedef struct 
{
	rlip_t *d;
	opint_t *op;
	rlip_reg_t *reg;
	int *loc;
	size_t op_count, op_as, vd_count, vd_as, vi_count, vi_as, vr_count, vr_as, ptr_count, ptr_as, loc_count, loc_as, reg_count, reg_as;
	int valid_reals, abort_compilation;
	int rd[8], ri[8], rr[8];	// generic registers
	buffer_t *comp_log;
	rlip_inputs_t *inputs;
	int input_count;
} rlip_data_t;

int rlip_find_value(const char *name, rlip_data_t *ed)
{
	int i;
	uint64_t hash;

	if (name==NULL)
		return -1;

	hash = get_string_hash(name);

	// Look for existing instance of the value
	for (i=0; i < ed->reg_count; i++)
		if (hash == ed->reg[i].hash)
			if (strcmp(name, ed->reg[i].name)==0)
				return i;			// return reg index

	return -1;
}

void rlip_add_value_at_reg_index(int ir, const char *name, const void *ptr, const char *type, rlip_data_t *ed)
{
	ed->reg[ir].name = make_string_copy(name);	// name can be NULL in which case this is a nameless variable only usable by the compiler
	if (name)
		ed->reg[ir].hash = get_string_hash(name);
	ed->reg[ir].type = make_string_copy(type);

	if (strcmp(type, "d")==0)			// add to vd table
	{
		ed->reg[ir].table = table_vd;
		ed->reg[ir].index = ed->vd_count;
		alloc_enough(&ed->d->vd, ed->vd_count+=1, &ed->vd_as, sizeof(double), 1.5);
		if (ptr)
			ed->d->vd[ed->reg[ir].index] = *(double *) ptr;
	}

	else if (strcmp(type, "i")==0)			// add to vi table
	{
		ed->reg[ir].table = table_vi;
		ed->reg[ir].index = ed->vi_count;
		alloc_enough(&ed->d->vi, ed->vi_count+=1, &ed->vi_as, sizeof(int64_t), 1.5);
		if (ptr)
			ed->d->vi[ed->reg[ir].index] = *(int64_t *) ptr;
	}

	if (strcmp(type, "r")==0 && ed->valid_reals)	// add to vr table
	{
		ed->reg[ir].table = table_vr;
		ed->reg[ir].index = ed->vr_count * ed->d->rf.size_of_real;
		alloc_enough(&ed->d->vr, ed->vr_count+=1, &ed->vr_as, ed->d->rf.size_of_real, 1.5);
		if (ptr)
			memcpy(&ed->d->vr[ed->reg[ir].index], ptr, ed->d->rf.size_of_real);
		else if (ed->d->rf.var_init)
			ed->d->rf.var_init(&ed->d->vr[ed->reg[ir].index]);
	}

	else if (type[0] == 'p' || type[0] == 'f')	// add to ptr table
	{
		ed->reg[ir].table = table_ptr;
		ed->reg[ir].index = ed->ptr_count;
		alloc_enough((void **) &ed->d->ptr, ed->ptr_count+=1, &ed->ptr_as, sizeof(void *), 1.5);
		ed->d->ptr[ed->reg[ir].index] = (void *) ptr;
	}

	else if (strcmp(type, "l")==0)			// add to loc table
	{
		ed->reg[ir].table = table_loc;
		ed->reg[ir].index = ed->loc_count;
		alloc_enough((void **) &ed->loc, ed->loc_count+=1, &ed->loc_as, sizeof(void *), 1.5);
		ed->loc[ed->reg[ir].index] = -1;
		if (ptr)
			ed->loc[ed->reg[ir].index] = *(int *) ptr;	// the ptr is missing if this is being called when adding a goto command to a forward location
	}
}

int rlip_add_value(const char *name, const void *ptr, const char *type, rlip_data_t *ed)
{
	int ir;

	if (name==NULL)
		return -1;

	// Special case when the "value" is the rlip_real_functions_t structure
	if (strcmp(name, "rlip_real_functions")==0 && ptr)
	{
		const rlip_real_functions_t *rf = ptr;
		if (rf->size_of_real && rf->set && rf->cvt_r_d && rf->cvt_d_r && rf->cvt_r_i && rf->cvt_i_r && rf->cmp && rf->ator && rf->get_pi && rf->get_e && rf->set_nan)
		{
			ed->d->rf = *rf;
			ed->valid_reals = 1;
		}
		return -1;
	}

	// Look for existing instance of the value
	ir = rlip_find_value(name, ed);
	if (ir > -1)
		return ir;

	// Add new registry entry
	ir = ed->reg_count;
	alloc_enough(&ed->reg, ed->reg_count+=1, &ed->reg_as, sizeof(rlip_reg_t), 1.5);

	rlip_add_value_at_reg_index(ir, name, ptr, type, ed);

	return ir;
}

size_t alloc_opcode(rlip_data_t *ed, size_t add_count)
{
	size_t index = ed->op_count;
	alloc_enough(&ed->op, ed->op_count+=add_count, &ed->op_as, sizeof(opint_t), 1.5);
	return index;
}

void prepend_opcode(rlip_data_t *ed, size_t add_count)
{
	size_t i, move_count = alloc_opcode(ed, add_count);			// make room for the ops to prepend
	memmove(&ed->op[add_count], ed->op, move_count * sizeof(ed->op[0]));	// move all ops to make room for the new ones at the beginning

	// Shift all registered locations
	for (i=0; i < ed->loc_count; i++)
		if (ed->loc[i] > -1)
			ed->loc[i] += add_count;
}

void convert_pointer_to_variable(int ir, rlip_data_t *ed)
{
	// Convert a pointer to a variable forever
	if (ed->reg[ir].type[0] == 'p' && (ed->reg[ir].type[1] == 'd' || ed->reg[ir].type[1] == 'i' || ed->reg[ir].type[1] == 'r') && ed->reg[ir].type[2] == '\0')
	{
		// Prepend load opcode
		prepend_opcode(ed, 3);
		switch (ed->reg[ir].type[1])
		{
			case 'd': ed->op[0] = op_load_d; break;
			case 'i': ed->op[0] = op_load_i; break;
			case 'r':
				  ed->op[0] = op_load_r;
				  if (ed->valid_reals == 0)
				  {
					  
					  bufprintf(ed->comp_log, "Real-type conversion without valid functions (rlip_real_functions_t) provided in rlip_compile()'s inputs\n");
					  ed->abort_compilation = 1;
				  }
				  break;
		}
		ed->op[2] = ed->reg[ir].index;

		// Convert reg entry from pointer to variable
		rlip_reg_t old_entry = ed->reg[ir];
		rlip_add_value_at_reg_index(ir, old_entry.name, NULL, &old_entry.type[1], ed);
		free(old_entry.name);
		free(old_entry.type);

		// Set destination
		ed->op[1] = ed->reg[ir].index;
	}
}

int convert_expression_to_variable(const char *name, rlip_data_t *ed)
{
	int ir = -1;
	//vd = te_interp(name, NULL);			// interpret name as an expression

	if (ed->valid_reals)
	{
		// Allocate real value first
		ir = rlip_add_value(name, NULL, "r", ed);
		uint8_t *vr = &ed->d->vr[ed->reg[ir].index];

		if (strcmp(name, "pi") == 0)
			ed->d->rf.get_pi(vr);
		else if (strcmp(name, "e") == 0)
			ed->d->rf.get_e(vr);
		else
		{
			// Read expression like a number
			char *endptr=NULL;
			ed->d->rf.ator(vr, name, &endptr);

			// If ator didn't parse the whole string then it's not just one number
			if (endptr[0])
			{
				// Check if it's only an unknown symbol
				int max_depth=0;
				size_t sym_count=0, sym_as=0;
				symbol_data_t *sym = expression_to_symbol_list(name, ed->comp_log, 0, &max_depth, &sym_count, &sym_as);
				if (sym_count == 0 || (sym_count == 1 && sym[0].type == sym_variable))
				{
					if (sym_count == 1)
						bufprintf(ed->comp_log, "Symbol '%.*s' unknown\n", sym[0].p_len, sym[0].p);
					else
						bufprintf(ed->comp_log, "Expression '%s' couldn't be interpreted\n", name);
					free_null(&sym);
					ed->abort_compilation = 1;
					return -1;
				}
				free_null(&sym);

				// Make copy of inputs without the variable pointers
				rlip_inputs_t *inputs_copy = copy_alloc(ed->inputs, ed->input_count*sizeof(rlip_inputs_t));

				for (int i=0; i < ed->input_count; i++)
					if (inputs_copy[i].type)
						if (inputs_copy[i].type[0] == 'p')
							memset(&inputs_copy[i], 0, sizeof(rlip_inputs_t));

				// Interpret expression
				if (rlip_expression_interp_real(vr, name, inputs_copy, ed->input_count, ed->comp_log) == 0)
				{
			      		bufprintf(ed->comp_log, "Expression '%s' couldn't be interpreted\n", name);
					ed->abort_compilation = 1;
				}

				free(inputs_copy);
			}
		}
	}
	else
	{
		double vd;

		if (strcmp(name, "pi") == 0)
			vd = pi;
		else if (strcmp(name, "e") == 0)
			vd = 2.7182818284590451;
		else
		{
			// Read expression like a number
			char *endptr=NULL;
			vd = strtod(name, &endptr);

			// If strtod didn't parse the whole string then it's not just one number
			if (endptr[0])
			{
				// Check if it's only an unknown symbol
				int max_depth=0;
				size_t sym_count=0, sym_as=0;
				symbol_data_t *sym = expression_to_symbol_list(name, ed->comp_log, 0, &max_depth, &sym_count, &sym_as);
				if (sym_count == 0 || (sym_count == 1 && sym[0].type == sym_variable))
				{
					if (sym_count == 1)
						bufprintf(ed->comp_log, "Symbol '%.*s' unknown\n", sym[0].p_len, sym[0].p);
					else
						bufprintf(ed->comp_log, "Expression '%s' couldn't be interpreted\n", name);
					free_null(&sym);
					ed->abort_compilation = 1;
					return -1;
				}
				free_null(&sym);

				// Interpret expression
				vd = rlip_expression_interp_double(name, ed->comp_log);
			}
		}

		if (isnan(vd)==0)					// if it's a valid expression
			ir = rlip_add_value(name, &vd, "d", ed);		// add the value as a variable with the original expression as its name
		else
		{
			bufprintf(ed->comp_log, "Invalid expression '%s'\n", name);
			ed->abort_compilation = 1;
		}
	}

	return ir;
}

int rlip_find_convert_value(const char *name, rlip_data_t *ed)
{
	int ir;

	ir = rlip_find_value(name, ed);

	// If it's an expression/value, make it a variable
	if (ir == -1)
		ir = convert_expression_to_variable(name, ed);

	if (ir > -1)
		// It might be a pointer, in which case make it a variable permanently
		convert_pointer_to_variable(ir, ed);

	return ir;
}

enum opcode rlip_find_cvt_opcode(char src_type, char dst_type)
{
	if (src_type == 'i' && dst_type == 'd') return op_cvt_i_d;
	if (src_type == 'd' && dst_type == 'i') return op_cvt_d_i;
	if (src_type == 'r' && dst_type == 'd') return op_cvt_r_d;
	if (src_type == 'd' && dst_type == 'r') return op_cvt_d_r;
	if (src_type == 'r' && dst_type == 'i') return op_cvt_r_i;
	if (src_type == 'i' && dst_type == 'r') return op_cvt_i_r;

	if (src_type == 'd' && dst_type == 'd') return op_set_d;
	if (src_type == 'i' && dst_type == 'i') return op_set_i;
	if (src_type == 'r' && dst_type == 'r') return op_set_r;

	return op_end;
}

void rlip_convert_mismatched_var_to_register(int *ir, char expected_type, int i, rlip_data_t *ed)
{
	int io;
	char var_type = ed->reg[*ir].type[0];

	// Convert the variable to a generic register if the type doesn't match the one expected
	if (var_type != expected_type)
	{
		// Check real conversion
		if (ed->valid_reals == 0 && (var_type == 'r' || expected_type == 'r'))
		{

			bufprintf(ed->comp_log, "Real type used without valid functions (rlip_real_functions_t) provided in rlip_compile()'s inputs\n");
			ed->abort_compilation = 1;
		}

		io = alloc_opcode(ed, 3);		// add conversion opcode
		ed->op[io+2] = ed->reg[*ir].index;	// source index

		// Opcode
		ed->op[io] = rlip_find_cvt_opcode(var_type, expected_type);

		// Destination index
		switch (expected_type)
		{
			case 'd': *ir = ed->rd[1+i];	break;
			case 'i': *ir = ed->ri[1+i];	break;
			case 'r': *ir = ed->rr[1+i];	break;
		}

		ed->op[io+1] = ed->reg[*ir].index;	// the ir for this argument is now the generic register
	}
}

int rlip_get_arguments(char *p, char *cmd_arg_type, int *arg_ir, rlip_data_t *ed, int il, char **line)
{
	int i, n=0, ret;
	char s1[32];

	for (i=0; cmd_arg_type[i]; i++)
	{
		p = &p[n];
		n = 0;
		ret = sscanf(p, "%30s %n", s1, &n);

		if (ret == 1)
		{
			arg_ir[i] = rlip_find_convert_value(s1, ed);

			if (arg_ir[i] == -1)
			{
				bufprintf(ed->comp_log, "Argument '%s' unidentified in line %d: '%s'\n", s1, il, line[il]);
				return -1;
			}

			// Convert the variable to a generic register if the type doesn't match the one expected
			if (cmd_arg_type[i] != 'f')
				rlip_convert_mismatched_var_to_register(&arg_ir[i], cmd_arg_type[i], i, ed);
		}
		else
		{
			bufprintf(ed->comp_log, "Argument missing (%d arguments expected) in line %d: '%s'\n", strlen(cmd_arg_type)-(cmd_arg_type[0]=='f'), il, line[il]);
			return -1;
		}
	}

	return 0;
}

rlip_t rlip_compile(const char *source, rlip_inputs_t *inputs, int input_count, int ret_count, buffer_t *comp_log)
{
	int i, io, ir, il, ret, linecount, n, add_var_type, dest_ir, ret_cmd_done=0, cmd_found, fwd_jumps=0;
	char **line = arrayise_text(make_string_copy(source), &linecount);
	rlip_t data={0};
	rlip_data_t extra_data={0}, *ed=&extra_data;
	char *p, s0[32], s1[32], s2[32], s3[32], cmd_arg_type[16];
	int arg_ir[16];
	uint64_t hash;
	enum opcode new_opcode;

	ed->d = &data;
	ed->comp_log = comp_log;

	// Add generic registers
	for (i=0; i < sizeof(ed->rd)/sizeof(*ed->rd); i++)
		ed->rd[i] = rlip_add_value(sprintf_ret(s0, "rd%d", i), NULL, "d", ed);

	for (i=0; i < sizeof(ed->ri)/sizeof(*ed->ri); i++)
		ed->ri[i] = rlip_add_value(sprintf_ret(s0, "ri%d", i), NULL, "i", ed);

	// Add inputs to structure
	for (i=0; i < input_count; i++)
		rlip_add_value(inputs[i].name, inputs[i].ptr, inputs[i].type, ed);
	ed->inputs = inputs;
	ed->input_count = input_count;

	// Add generic real registers
	if (ed->valid_reals)
		for (i=0; i < sizeof(ed->rr)/sizeof(*ed->rr); i++)
			ed->rr[i] = rlip_add_value(sprintf_ret(s0, "rr%d", i), NULL, "r", ed);

	// Alloc and init return value arrays
	ed->d->return_value = calloc(ret_count, sizeof(double));
	if (ed->valid_reals)
	{
		ed->d->return_real = calloc(ret_count, ed->d->rf.size_of_real);
		if (ed->d->rf.var_init)
			for (i=0; i < ret_count; i++)
				ed->d->rf.var_init(&ed->d->return_real[i]);
	}

	// Parse lines and compile them into opcodes
	for (il=0; il < linecount; il++)
	{
		if (ed->abort_compilation)
			goto invalid_prog;

		add_var_type = 0;
		p = line[il];

line_proc_start:
		s0[0] = '\0';
		s1[0] = '\0';
		s2[0] = '\0';
		s3[0] = '\0';
		n = 0;
		sscanf(p, "%30s %*s = %n", s0, &n);

		// Declaring a new variable by its type
		if (n && (strcmp(s0, "d")==0 || strcmp(s0, "i")==0 || strcmp(s0, "r")==0))
		{
			// Set flag for creation of variable
			if (s0[0]=='d')
				add_var_type = table_vd;
			else if (s0[0]=='i')
				add_var_type = table_vi;
			else
			{
				add_var_type = table_vr;

				if (ed->valid_reals == 0)
				{

					bufprintf(ed->comp_log, "Real-type variable declaration without valid functions (rlip_real_functions_t) provided in rlip_compile()'s inputs\n");
					goto invalid_prog;
				}
			}

			// Jump back to end up at the processing of "<var> = ..."
			sscanf(p, "%*s%n", &n);
			p = &p[n];

			goto line_proc_start;
		}

		n = 0;
		sscanf(p, "%30s = %n", s0, &n);

		// Declaring a location
		if (s0[strlen(s0)-1] == ':')
		{
			s0[strlen(s0)-1] = '\0';	// remove : to make location name

			// Check for previous declaration
			ir = rlip_find_value(s0, ed);
			if (ir > -1)	// this most likely is the result of a forward jump meaning we must go through previous opcodes to add in the correct offsets
			{
				ed->loc[ed->reg[ir].index] = ed->op_count;	// add the correct current location

				// Go through all previous opcodes to look for forward jumps to this location
				for (io=0; io < ed->op_count;)
				{
					if (ed->op[io] == nop_jmp)
						if (ed->op[io+1] == ir)
						{
							ed->op[io] = op_jmp;
							ed->op[io+1] = ed->op_count - io;
							fwd_jumps--;
						}

					if (ed->op[io] == nop_jmp_cond)
						if (ed->op[io+2] == ir)
						{
							ed->op[io] = op_jmp_cond;
							ed->op[io+2] = ed->op_count - io;
							fwd_jumps--;
						}

					if ((ed->op[io] >> 10) < 1)
					{
						bufprintf(comp_log, "op[%d] is %d\n", io, ed->op[io]);
						goto invalid_prog;
					}

					io += ed->op[io] >> 10;
				}
			}
			else
			{
				// Add location in table
				ir = rlip_add_value(s0, &ed->op_count, "l", ed);
			}
		}

		// When doing "<var> = ..."
		else if (n)
		{
			p = &p[n];

			// Add or find destination var
			if (add_var_type)
				dest_ir = rlip_add_value(s0, NULL, add_var_type==table_vd ? "d" : add_var_type==table_vi ? "i" : "r", ed);
			else
				dest_ir = rlip_find_value(s0, ed);
			
			if (dest_ir == -1)
			{
				bufprintf(comp_log, "Undeclared variable '%s' used in line %d: '%s'\n", s0, il, line[il]);
				goto invalid_prog;
			}

			if (ed->reg[dest_ir].type[0]!='d' && ed->reg[dest_ir].type[0]!='i' && ed->reg[dest_ir].type[0]!='r')
			{
				bufprintf(comp_log, "Assignment to variable '%s' of invalid type '%s' used in line %d: '%s'\n", s0, ed->reg[dest_ir].type, il, line[il]);
				goto invalid_prog;
			}

			// Read command
			n = 0;
			ret = sscanf(p, "%30s %n", s0, &n);
			cmd_found = 0;

			if (ret == 1)
			{
				int cmd_arg_count = 0;

				// Identify the command and find its argument count
				if (	strcmp(s0, "sq")==0 ||
					strcmp(s0, "sqrt")==0 )
				{
					cmd_arg_count = 1;
					sprintf(cmd_arg_type, "dd");
					cmd_found = 1;
				}

				else if ( strcmp(s0, "add")==0 ||
					strcmp(s0, "sub")==0 ||
					strcmp(s0, "mul")==0 ||
					strcmp(s0, "div")==0 ||
					strcmp(s0, "mod")==0 ||
					strcmp(s0, "sqadd")==0 ||
					strcmp(s0, "sqsub")==0 ||
					strcmp(s0, "diff")==0 )
				{
					cmd_arg_count = 2;
					sprintf(cmd_arg_type, "ddd");
					cmd_found = 1;
				}

				else if ( strcmp(s0, "addi")==0 ||
					strcmp(s0, "subi")==0 ||
					strcmp(s0, "muli")==0 ||
					strcmp(s0, "divi")==0 ||
					strcmp(s0, "modi")==0 ||
					strcmp(s0, "and")==0 ||
					strcmp(s0, "or")==0 )
				{
					cmd_arg_count = 2;
					sprintf(cmd_arg_type, "iii");
					cmd_found = 1;
				}

				else if ( strcmp(s0, "aad")==0 ||
					strcmp(s0, "mmul")==0 ||
					strcmp(s0, "mad")==0 ||
					strcmp(s0, "adm")==0 )
				{
					cmd_arg_count = 3;
					sprintf(cmd_arg_type, "dddd");
					cmd_found = 1;
				}

				// Add command
				if (cmd_found == 1)
				{
					new_opcode = 0;

					if (strcmp(s0, "sq")==0)		new_opcode = op_sq_d;
					else if (strcmp(s0, "sqrt")==0)		new_opcode = op_sqrt_d;
					else if (strcmp(s0, "add")==0)		new_opcode = op_add_dd;
					else if (strcmp(s0, "addi")==0)		new_opcode = op_add_ii;
					else if (strcmp(s0, "sub")==0)		new_opcode = op_sub_dd;
					else if (strcmp(s0, "subi")==0)		new_opcode = op_sub_ii;
					else if (strcmp(s0, "mul")==0)		new_opcode = op_mul_dd;
					else if (strcmp(s0, "muli")==0)		new_opcode = op_mul_ii;
					else if (strcmp(s0, "div")==0)		new_opcode = op_div_dd;
					else if (strcmp(s0, "divi")==0)		new_opcode = op_div_ii;
					else if (strcmp(s0, "mod")==0)		new_opcode = op_mod_dd;
					else if (strcmp(s0, "modi")==0)		new_opcode = op_mod_ii;
					else if (strcmp(s0, "sqadd")==0)	new_opcode = op_sqadd_dd;
					else if (strcmp(s0, "sqsub")==0)	new_opcode = op_sqsub_dd;
					else if (strcmp(s0, "diff")==0)		new_opcode = op_diff_dd;
					else if (strcmp(s0, "and")==0)		new_opcode = op_and_ii;
					else if (strcmp(s0, "or")==0)		new_opcode = op_or_ii;
					else if (strcmp(s0, "aad")==0)		new_opcode = op_aad_ddd;
					else if (strcmp(s0, "mmul")==0)		new_opcode = op_mmul_ddd;
					else if (strcmp(s0, "mad")==0)		new_opcode = op_mad_ddd;
					else if (strcmp(s0, "adm")==0)		new_opcode = op_adm_ddd;
add_command:
					// Go through arguments to convert them and determine their types
					if (rlip_get_arguments(&p[n], &cmd_arg_type[1], arg_ir, ed, il, line))
						goto invalid_prog;

					// Add opcode
					io = alloc_opcode(ed, 2+cmd_arg_count);
					ed->op[io] = new_opcode;

					// Add arguments to opcode
					for (i=0; i < cmd_arg_count; i++)
						ed->op[io+2+i] = ed->reg[arg_ir[i]].index;

					// Destination (assuming same type)
					ed->op[io+1] = ed->reg[dest_ir].index;

					// Convert result to destination type
					if (ed->reg[dest_ir].type[0] != cmd_arg_type[0])
					{
						// Output to generic register
						ed->op[io+1] = cmd_arg_type[0]=='d' ? ed->reg[ed->rd[0]].index : cmd_arg_type[0]=='i' ? ed->reg[ed->ri[0]].index : ed->reg[ed->rr[0]].index;

						// Convert from generic register to destination
						io = alloc_opcode(ed, 3);	// add conversion opcode
						ed->op[io+1] = ed->reg[dest_ir].index;	// destination index

						ed->op[io] = rlip_find_cvt_opcode(cmd_arg_type[0], ed->reg[dest_ir].type[0]);

						// Source index
						switch (cmd_arg_type[0])
						{
							case 'd': ed->op[io+2] = ed->reg[ed->rd[0]].index;	break;
							case 'i': ed->op[io+2] = ed->reg[ed->ri[0]].index;	break;
							case 'r': ed->op[io+2] = ed->reg[ed->rr[0]].index;	break;
						}
					}
				}

				// Commands with less typical needs
				if (cmd_found == 0)
				{
					if (strcmp(s0, "cmp")==0 || strcmp(s0, "cmpi")==0 || strcmp(s0, "cmpr")==0)
					{
						cmd_found = 1;
						if (strcmp(s0, "cmp")==0)
							sprintf(cmd_arg_type, "idd");
						else if (strcmp(s0, "cmpi")==0)
							sprintf(cmd_arg_type, "iii");
						else
							sprintf(cmd_arg_type, "irr");

						n = 0;
						ret = sscanf(p, "%*s %30s %30s %30s %n", s1, s2, s3, &n);
						
						if (ret == 3)
						{
							// Find / convert variables
							for (i=0; i < 2; i++)
							{
								arg_ir[i] = rlip_find_convert_value(i==0 ? s1 : s3, ed);

								if (arg_ir[i] == -1)
								{
									bufprintf(comp_log, "Argument '%s' unidentified in line %d: '%s'\n", i==0 ? s1 : s3, il, line[il]);
									goto invalid_prog;
								}

								// Convert the variable to a generic register if the type doesn't match the one expected
								rlip_convert_mismatched_var_to_register(&arg_ir[i], cmd_arg_type[1+i], i, ed);
							}

							// Add cmp opcode
							io = alloc_opcode(ed, 4);

							// Select correct opcode
							if (strcmp(s2, "==")==0)	ed->op[io] = op_cmp_dd_eq;
							if (strcmp(s2, "!=")==0)	ed->op[io] = op_cmp_dd_ne;
							if (strcmp(s2, "<")==0) 	ed->op[io] = op_cmp_dd_lt;
							if (strcmp(s2, "<=")==0)	ed->op[io] = op_cmp_dd_le;
							if (strcmp(s2, ">")==0) 	ed->op[io] = op_cmp_dd_gt;
							if (strcmp(s2, ">=")==0)	ed->op[io] = op_cmp_dd_ge;

							if (cmd_arg_type[1]=='i')
								ed->op[io] += 1;

							if (cmd_arg_type[1]=='r')
								ed->op[io] += 2;

							if (ed->op[io] == 0)	// if comparison hasn't been found
							{
								bufprintf(comp_log, "Comparator invalid in line %d: '%s'\n", il, line[il]);
								goto invalid_prog;
							}

							ed->op[io+1] = ed->reg[dest_ir].index;
							ed->op[io+2] = ed->reg[arg_ir[0]].index;
							ed->op[io+3] = ed->reg[arg_ir[1]].index;
							
							// Convert integer result to double or real if needed
							if (ed->reg[dest_ir].type[0] == 'd' || ed->reg[dest_ir].type[0] == 'r')
							{
								// Output to generic register
								ed->op[io+1] = ed->reg[ed->ri[0]].index;

								// Convert from generic register to destination
								io = alloc_opcode(ed, 3);			// add conversion opcode
								ed->op[io] = rlip_find_cvt_opcode('i', ed->reg[dest_ir].type[0]);
								ed->op[io+1] = ed->reg[dest_ir].index;		// destination index
								ed->op[io+2] = ed->reg[ed->ri[0]].index;	// source index
							}
						}
						else
						{
							bufprintf(comp_log, "Argument missing (2 arguments expected) in line %d: '%s'\n", il, line[il]);
							goto invalid_prog;
						}
					}
				}

				// Check if it's a variable, pointer, expression or function pointer rather than a command making "=" a set, cvt or func command
				if (cmd_found == 0)
				{
					ir = rlip_find_convert_value(s0, ed);	// converts pointers and expressions to variables
					if (ir > -1)
					{
						// Variable
						if (strcmp(ed->reg[ir].type, "d")==0 || strcmp(ed->reg[ir].type, "i")==0 || strcmp(ed->reg[ir].type, "r")==0)
						{
							io = alloc_opcode(ed, 3);

							// Copy (set) or convert
							ed->op[io] = rlip_find_cvt_opcode(ed->reg[ir].type[0], ed->reg[dest_ir].type[0]);

							ed->op[io+1] = ed->reg[dest_ir].index;
							ed->op[io+2] = ed->reg[ir].index;
							cmd_found = 2;
						}

						// Provided function pointer
						if (ed->reg[ir].type[0]=='f')
						{
							cmd_arg_count = strlen(ed->reg[ir].type) - 1;
							sprintf(cmd_arg_type, "%s", ed->reg[ir].type);
							swap_char(&cmd_arg_type[0], &cmd_arg_type[1]);
							cmd_found = 3;

							// Set opcode
							new_opcode = 0;
							switch (cmd_arg_count)
							{
								case 1:
									if (strcmp(ed->reg[ir].type, "fd")==0)		new_opcode = op_func0_d;
									else if (strcmp(ed->reg[ir].type, "fr")==0)	new_opcode = op_func0_r;
									break;
								case 2:
									if (strcmp(ed->reg[ir].type, "fdd")==0)		new_opcode = op_func1_dd;
									else if (strcmp(ed->reg[ir].type, "fdi")==0)	new_opcode = op_func1_di;
									else if (strcmp(ed->reg[ir].type, "fii")==0)	new_opcode = op_func1_ii;
									else if (strcmp(ed->reg[ir].type, "frr")==0)	new_opcode = op_func1_rr;
									break;
								case 3:
									if (strcmp(ed->reg[ir].type, "fddd")==0)	new_opcode = op_func2_ddd;
									else if (strcmp(ed->reg[ir].type, "frrr")==0)	new_opcode = op_func2_rrr;
									break;
								case 4:
									if (strcmp(ed->reg[ir].type, "fdddd")==0)	new_opcode = op_func3_dddd;
									else if (strcmp(ed->reg[ir].type, "fdddi")==0)	new_opcode = op_func3_dddi;
									else if (strcmp(ed->reg[ir].type, "frrrr")==0)	new_opcode = op_func3_rrrr;
									break;
							}

							if (new_opcode == 0)
							{
								bufprintf(comp_log, "Function type '%s' not implemented in line %d: '%s'\n", ed->reg[ir].type, il, line[il]);
								goto invalid_prog;
							}

							n = 0;			// makes the parsing keep the name of the function as an argument
							goto add_command;
						}
					}
				}

				if (cmd_found == 0)
				{
					bufprintf(comp_log, "Unidentified '%s' in line %d: '%s'\n", s0, il, line[il]);
					goto invalid_prog;
				}
			}
		}

		// Commands starting with the command name
		else
		{
			// Return (double or real values)
			if (strcmp(s0, "return")==0 || strcmp(s0, "return_real")==0)
			{
				enum opcode *ret_op;
				char **ret_arg_type;
				enum opcode ret_op_d[] = { 0, op_ret_d, op_ret_dd, op_ret_ddd, op_ret_dddd };
				char *ret_arg_type_d[] = { "", "d", "dd", "ddd", "dddd" };
				enum opcode ret_op_r[] = { 0, op_ret_r, op_ret_rr, op_ret_rrr, op_ret_rrrr };
				char *ret_arg_type_r[] = { "", "r", "rr", "rrr", "rrrr" };

				if (strcmp(s0, "return")==0)
				{
					ret_op = ret_op_d;
					ret_arg_type = ret_arg_type_d;
				}
				else
				{
					ret_op = ret_op_r;
					ret_arg_type = ret_arg_type_r;
				}

				n = 0;
				sscanf(p, "%*s %n", &n);

				// Get/convert arguments
				if (rlip_get_arguments(&p[n], ret_arg_type[ret_count], arg_ir, ed, il, line))
					goto invalid_prog;

				// Add return opcode
				io = alloc_opcode(ed, 1 + ret_count);
				ed->op[io] = ret_op[ret_count];

				// Add arguments
				for (i=0; i < ret_count; i++)
					ed->op[io+1+i] = ed->reg[arg_ir[i]].index;

				ret_cmd_done = 1;
			}

			// If <condition result> goto <location>
			if (strcmp(s0, "if")==0)
			{
				ret = sscanf(p, "%*s %30s goto %30s", s1, s2);

				if (ret == 2)
				{
					arg_ir[0] = rlip_find_value(s1, ed);
					//arg_ir[1] = rlip_find_value(s2, ed);
					arg_ir[1] = rlip_add_value(s2, NULL, "l", ed);

					for (i=0; i < 2; i++)
					{
						if (arg_ir[i] == -1)
						{
							bufprintf(comp_log, "Variable '%s' not found in line %d: '%s'\n", i==0 ? s1 : s2, il, line[il]);
							goto invalid_prog;
						}
					}

					if (strcmp(ed->reg[arg_ir[0]].type, "i") != 0)	// s1 must be an integer variable
					{
						bufprintf(comp_log, "Not an integer variable '%s' in line %d: '%s'\n", s1, il, line[il]);
						goto invalid_prog;
					}

					if (strcmp(ed->reg[arg_ir[1]].type, "l") != 0)	// s2 must be a location
					{
						bufprintf(comp_log, "Not a location '%s' in line %d: '%s'\n", s2, il, line[il]);
						goto invalid_prog;
					}

					io = alloc_opcode(ed, 3);
					ed->op[io] = op_jmp_cond;
					ed->op[io+1] = ed->reg[arg_ir[0]].index;					// integer variable
					if (ed->loc[ed->reg[arg_ir[1]].index] > -1)
						ed->op[io+2] = (opint_t) ed->loc[ed->reg[arg_ir[1]].index] - io;	// signed backward jump offset
					else
					{
						ed->op[io] = nop_jmp_cond;	// this indicates that the forward jump must be edited later
						ed->op[io+2] = arg_ir[1];	// in case of a forward jump the jump offset will have to be specified later
						fwd_jumps++;
					}
				}
				else
				{
					bufprintf(comp_log, "Incorrect 'if <integer variable> goto <loc>' command in line %d: '%s'\n", il, line[il]);
					goto invalid_prog;
				}
			}

			if (strcmp(s0, "set0")==0)
			{
				sscanf(p, "%*s %30s", s1);
				ir = rlip_find_value(s1, ed);

				// Add opcode
				if (ir > -1)
				{
					if (strcmp(ed->reg[ir].type, "d")==0 || strcmp(ed->reg[ir].type, "i")==0)
					{
						io = alloc_opcode(ed, 2);
						ed->op[io] = ed->reg[ir].type[0]=='d' ? op_set0_d : op_set0_i;
						ed->op[io+1] = ed->reg[ir].index;
					}
					else
					{
						bufprintf(comp_log, "Command 'set0' can't use type '%s' in line %d: '%s'\n", ed->reg[ir].type, il, line[il]);
						goto invalid_prog;
					}
				}
				else
				{
					bufprintf(comp_log, "Value not found for command 'set0' in line %d: '%s'\n", il, line[il]);
					goto invalid_prog;
				}
			}

			if (strcmp(s0, "inc1")==0)
			{
				sscanf(p, "%*s %30s", s1);
				ir = rlip_find_value(s1, ed);

				// Add opcode
				if (ir > -1)
				{
					if (strcmp(ed->reg[ir].type, "d")==0 || strcmp(ed->reg[ir].type, "i")==0)
					{
						io = alloc_opcode(ed, 2);
						ed->op[io] = ed->reg[ir].type[0]=='d' ? op_inc1_d : op_inc1_i;
						ed->op[io+1] = ed->reg[ir].index;
					}
					else
					{
						bufprintf(comp_log, "Command 'inc1' can't use type '%s' in line %d: '%s'\n", ed->reg[ir].type, il, line[il]);
						goto invalid_prog;
					}
				}
				else
				{
					bufprintf(comp_log, "Value not found for command 'inc1' in line %d: '%s'\n", il, line[il]);
					goto invalid_prog;
				}
			}
		}
	}

	data.valid_prog = 1;

	// free_rlip() needs these values
	ed->d->vr_count = ed->vr_count;
	ed->d->ret_count = ret_count;

	// If not all forward jumps were resolved
	if (fwd_jumps != 0)
	{
		bufprintf(comp_log, "There are %d unresolved forward jumps\n", fwd_jumps);
		data.valid_prog = 0;
	}

	// If the return command is missing
	if (ret_cmd_done==0)
	{
		bufprintf(comp_log, "The 'return' command is missing or invalid\n");
invalid_prog:
		data.valid_prog = 0;
	}

	// Add end opcode
	io = alloc_opcode(ed, 1);
	ed->op[io] = op_end;

	// Free stuff
	free_2d(line, 1);

	for (i=0; i < ed->reg_count; i++)
	{
		free(ed->reg[i].name);
		free(ed->reg[i].type);
	}
	free(ed->loc);
	free(ed->reg);

	data.op = ed->op;
	return data;
}
