int rlip_execute_opcode(rlip_t *d)
{
	opint_t *op = d->op, *op_next;
	double *vd = d->vd;
	int64_t *vi = d->vi;
	uint8_t *vr = d->vr;

	if (d->valid_prog == 0)
	{
		if (d->return_value)
			d->return_value[0] = NAN;
		return -1;
	}

	while (*d->exec_on)
	{
		// Point to next op
		op_next = &op[op[0] >> 10];

		// Execute op
		switch (op[0])
		{
			// 1 word ops
			case op_end:	return 1;

			// 2 word ops
			break;	case op_ret_d:		d->return_value[0] = vd[op[1]];					// return <var/ptr/expr>
			break;	case op_ret_r:		d->rf.set(&d->return_real[0], &vr[op[1]]);
			break;	case op_jmp:		op_next = &op[(ptrdiff_t) op[1]];				// unused for now
			break;	case op_set0_d:		vd[op[1]] = 0.;							// set0 <var>
			break;	case op_set0_i:		vi[op[1]] = 0;
			break;	case op_inc1_d:		vd[op[1]] += 1.;						// inc1 <var>
			break;	case op_inc1_i:		vi[op[1]] += 1;

			// 3 word ops
			break;	case op_ret_dd:		d->return_value[0] = vd[op[1]];					// return <var/ptr/expr> <var/ptr/expr>
							d->return_value[1] = vd[op[2]];
			break;	case op_ret_rr:		d->rf.set(&d->return_real[0], &vr[op[1]]);
							d->rf.set(&d->return_real[1], &vr[op[2]]);
			break;	case op_load_d:		vd[op[1]] = *(double *) d->ptr[op[2]];				// compiler-only
			break;	case op_load_i:		vi[op[1]] = *(int64_t *) d->ptr[op[2]];
			break;	case op_load_r:		d->rf.set(&vr[op[1]], d->ptr[op[2]]);
			break;	case op_set_d:		vd[op[1]] = vd[op[2]];						// <var> = <var/ptr/expr>
			break;	case op_set_i:		vi[op[1]] = vi[op[2]];
			break;	case op_set_r:		d->rf.set(&vr[op[1]], &vr[op[2]]);
			break;	case op_cvt_i_d:	vd[op[1]] = (double) vi[op[2]];					// <var> = <var/ptr/expr>
			break;	case op_cvt_d_i:	vi[op[1]] = (int64_t) vd[op[2]];
			break;	case op_cvt_r_d:	vd[op[1]] = d->rf.cvt_r_d(&vr[op[2]]);
			break;	case op_cvt_d_r:	d->rf.cvt_d_r(&vr[op[1]], vd[op[2]]);
			break;	case op_cvt_r_i:	vi[op[1]] = d->rf.cvt_r_i(&vr[op[2]]);
			break;	case op_cvt_i_r:	d->rf.cvt_i_r(&vr[op[1]], vi[op[2]]);

			break;	case op_sq_d:		vd[op[1]] = sq(vd[op[2]]);					// <var> = sq <var/ptr/expr>
			break;	case op_sqrt_d:		vd[op[1]] = sqrt(vd[op[2]]);					// <var> = sqrt <var/ptr/expr>

			break;	case op_jmp_cond:	if (vi[op[1]]) { op_next = &op[(ptrdiff_t) op[2]]; }		// if <var> goto <loc>
			break;	case op_func0_d:	vd[op[1]] = ((double (*)(void)) d->ptr[op[2]])();
			break;	case op_func0_r:	((void (*)(uint8_t *)) d->ptr[op[2]])(&vr[op[1]]);

			// 4 word ops
			break;	case op_ret_ddd:	d->return_value[0] = vd[op[1]];					// return <var/ptr/expr> x3
							d->return_value[1] = vd[op[2]];
							d->return_value[2] = vd[op[3]];
			break;	case op_ret_rrr:	d->rf.set(&d->return_real[0], &vr[op[1]]);
							d->rf.set(&d->return_real[1], &vr[op[2]]);
							d->rf.set(&d->return_real[2], &vr[op[3]]);
			break;	case op_add_dd:		vd[op[1]] = vd[op[2]] + vd[op[3]];				// <var> = add <var/ptr/expr> <var/ptr/expr>
			break;	case op_add_ii:		vi[op[1]] = vi[op[2]] + vi[op[3]];				// <var> = addi <var/ptr/expr> <var/ptr/expr>
			break;	case op_sub_dd:		vd[op[1]] = vd[op[2]] - vd[op[3]];				// sub
			break;	case op_sub_ii:		vi[op[1]] = vi[op[2]] - vi[op[3]];				// subi
			break;	case op_mul_dd:		vd[op[1]] = vd[op[2]] * vd[op[3]];				// mul
			break;	case op_mul_ii:		vi[op[1]] = vi[op[2]] * vi[op[3]];				// muli
			break;	case op_div_dd:		vd[op[1]] = vd[op[2]] / vd[op[3]];				// div
			break;	case op_div_ii:		vi[op[1]] = vi[op[3]]==0 ? 0 : vi[op[2]] / vi[op[3]];		// divi
			break;	case op_mod_ii:		vi[op[1]] = vi[op[3]]==0 ? 0 : vi[op[2]] % vi[op[3]];		// modi
			break;	case op_mod_dd:		vd[op[1]] = fmod(vd[op[2]], vd[op[3]]);				// mod
			break;	case op_sqadd_dd:	vd[op[1]] = sq(vd[op[2]]) + sq(vd[op[3]]);			// sqadd (the sum of squares)
			break;	case op_sqsub_dd:	vd[op[1]] = sq(vd[op[2]]) - sq(vd[op[3]]);			// sqsub (the difference of squares)
			break;	case op_diff_dd:	vd[op[1]] = fabs(vd[op[2]] - vd[op[3]]);			// diff (abs of sub)
			
			break;	case op_and_ii:		vi[op[1]] = vi[op[2]] & vi[op[3]];				// and (binary &)
			break;	case op_or_ii:		vi[op[1]] = vi[op[2]] | vi[op[3]];				// or (binary &)

			break;	case op_cmp_dd_eq:	vi[op[1]] = (vd[op[2]] == vd[op[3]]);				// <var> = cmp <var/ptr/expr> == <var/ptr/expr>
			break;	case op_cmp_ii_eq:	vi[op[1]] = (vi[op[2]] == vi[op[3]]);				// <var> = cmpi <var/ptr/expr> == <var/ptr/expr>
			break;	case op_cmp_rr_eq:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) == 0;		// <var> = cmpr <var/ptr/expr> == <var/ptr/expr>
			break;	case op_cmp_dd_ne:	vi[op[1]] = (vd[op[2]] != vd[op[3]]);
			break;	case op_cmp_ii_ne:	vi[op[1]] = (vi[op[2]] != vi[op[3]]);
			break;	case op_cmp_rr_ne:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) != 0;
			break;	case op_cmp_dd_lt:	vi[op[1]] = (vd[op[2]] <  vd[op[3]]);
			break;	case op_cmp_ii_lt:	vi[op[1]] = (vi[op[2]] <  vi[op[3]]);
			break;	case op_cmp_rr_lt:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) < 0;
			break;	case op_cmp_dd_le:	vi[op[1]] = (vd[op[2]] <= vd[op[3]]);
			break;	case op_cmp_ii_le:	vi[op[1]] = (vi[op[2]] <= vi[op[3]]);
			break;	case op_cmp_rr_le:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) <= 0;
			break;	case op_cmp_dd_gt:	vi[op[1]] = (vd[op[2]] >  vd[op[3]]);
			break;	case op_cmp_ii_gt:	vi[op[1]] = (vi[op[2]] >  vi[op[3]]);
			break;	case op_cmp_rr_gt:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) > 0;
			break;	case op_cmp_dd_ge:	vi[op[1]] = (vd[op[2]] >= vd[op[3]]);
			break;	case op_cmp_ii_ge:	vi[op[1]] = (vi[op[2]] >= vi[op[3]]);
			break;	case op_cmp_rr_ge:	vi[op[1]] = d->rf.cmp(&vr[op[2]], &vr[op[3]]) >= 0;
			break;	case op_func1_dd:	vd[op[1]] = ((double (*)(double)) d->ptr[op[2]])(vd[op[3]]);	// <var> = <func> <var/ptr/expr>
			break;	case op_func1_di:	vd[op[1]] = ((double (*)(int64_t)) d->ptr[op[2]])(vi[op[3]]);
			break;	case op_func1_ii:	vi[op[1]] = ((int64_t (*)(int64_t)) d->ptr[op[2]])(vi[op[3]]);
			break;	case op_func1_rr:	((void (*)(uint8_t *,uint8_t *)) d->ptr[op[2]])(&vr[op[1]], &vr[op[3]]);

			// 5 word ops
			break;	case op_ret_dddd:	d->return_value[0] = vd[op[1]];					// return <var/ptr/expr> x4
							d->return_value[1] = vd[op[2]];
							d->return_value[2] = vd[op[3]];
							d->return_value[3] = vd[op[4]];
			break;	case op_ret_rrrr:	d->rf.set(&d->return_real[0], &vr[op[1]]);
							d->rf.set(&d->return_real[1], &vr[op[2]]);
							d->rf.set(&d->return_real[2], &vr[op[3]]);
							d->rf.set(&d->return_real[3], &vr[op[4]]);
			break;	case op_aad_ddd:	vd[op[1]] = vd[op[2]] + vd[op[3]] + vd[op[4]];			// <var> = aad <var/ptr/expr> <var/ptr/expr> <var/ptr/expr>
			break;	case op_mmul_ddd:	vd[op[1]] = vd[op[2]] * vd[op[3]] * vd[op[4]];			// mmul (two multiplications)
			break;	case op_mad_ddd:	vd[op[1]] = vd[op[2]] * vd[op[3]] + vd[op[4]];			// mad (multiply-add)
			break;	case op_adm_ddd:	vd[op[1]] = (vd[op[2]] + vd[op[3]]) * vd[op[4]];		// adm (multiplication of sum)
			break;	case op_func2_ddd:	vd[op[1]] = ((double (*)(double,double)) d->ptr[op[2]])(vd[op[3]], vd[op[4]]);
			break;	case op_func2_rrr:	((void (*)(uint8_t *,uint8_t *,uint8_t *)) d->ptr[op[2]])(&vr[op[1]], &vr[op[3]], &vr[op[4]]);

			// 6 word ops
			break;	case op_func3_dddd:	vd[op[1]] = ((double (*)(double,double,double)) d->ptr[op[2]])(vd[op[3]], vd[op[4]], vd[op[5]]);
			break;	case op_func3_dddi:	vd[op[1]] = ((double (*)(double,double,int)) d->ptr[op[2]])(vd[op[3]], vd[op[4]], vi[op[5]]);
			break;	case op_func3_rrrr:	((void (*)(uint8_t *,uint8_t *,uint8_t *,uint8_t *)) d->ptr[op[2]])(&vr[op[1]], &vr[op[3]], &vr[op[4]], &vr[op[5]]);
			break;

			default:
				fprintf_rl(stderr, "Invalid opcode '%d' at op[%zu]\n", op[0], (op - d->op) / sizeof(opint_t));
				return -2;
		}

		// Increment to next op
		op = op_next;
	}

	return 0;
}
