
make_helper(concat(ADD_SUB_NAME, _12rmb))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =1;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.R_M);
		
		print_asm(SAL_SAR_CMD " 0x1,%%%s", regsb[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.R_M) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);

		print_asm(SAL_SAR_CMD " 0x1,%s", ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _cl2rmb))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =reg_b(R_CL)&0x1f;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.R_M);
		
		print_asm(SAL_SAR_CMD " %%%s,%%%s", regsb[R_CL], regsb[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.R_M) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);

		print_asm(SAL_SAR_CMD " %%%s,%s", regsb[R_CL], ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _ib2rmb))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.R_M);
		val2 = instr_fetch(eip+2, 1)&0x1f;
		
		print_asm(SAL_SAR_CMD " 0x%2x,%%%s", val2, regsb[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.R_M) = result.unsign8;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);
		val2 = instr_fetch(eip+1+len, 1)&0x1f;

		print_asm(SAL_SAR_CMD " 0x%2x,%s", val2, ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len+1;
	}
}

make_helper(concat(ADD_SUB_NAME, _12rmw))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =1;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.R_M);
		
		print_asm(SAL_SAR_CMD " 0x1,%%%s", regsw[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.R_M) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);

		print_asm(SAL_SAR_CMD " 0x1,%s", ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _12rml))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =1;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.R_M);
		
		print_asm(SAL_SAR_CMD " 0x1,%%%s", regsl[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.R_M) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);

		print_asm(SAL_SAR_CMD " 0x1,%s", ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _12rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _12rml(eip)):concat(ADD_SUB_NAME, _12rmw(eip));
}

make_helper(concat(ADD_SUB_NAME, _cl2rmw))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =reg_b(R_CL)&0x1f;
	m.val = instr_fetch(eip+1, 1);
	val2 = reg_b(R_CL);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.R_M);
		
		print_asm(SAL_SAR_CMD " %%%s,%%%s", regsb[R_CL], regsw[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.R_M) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);

		print_asm(SAL_SAR_CMD " %%%s,%s", regsb[R_CL], ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _cl2rml))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =reg_b(R_CL)&0x1f;
	m.val = instr_fetch(eip+1, 1);
	val2 = reg_b(R_CL);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.R_M);
		
		print_asm(SAL_SAR_CMD " %%%s,%%%s", regsb[R_CL], regsl[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.R_M) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);

		print_asm(SAL_SAR_CMD " %%%s,%s", regsb[R_CL], ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _cl2rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _cl2rml(eip)):concat(ADD_SUB_NAME, _cl2rmw(eip));
}

make_helper(concat(ADD_SUB_NAME, _ib2rmw))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =1;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.R_M);
		val2 = instr_fetch(eip+2, 1);
		
		print_asm(SAL_SAR_CMD " 0x%2x,%%%s", val2, regsw[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.R_M) = result.unsign16;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2 = instr_fetch(eip+1+len, 1);

		print_asm(SAL_SAR_CMD " 0x%2x,%s", val2, ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);

		return 1+len+1;
	}
}

make_helper(concat(ADD_SUB_NAME, _ib2rml))
{
	ModR_M m;
	eflags_help_s val1, result;
	uint8_t val2 =1;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.R_M);
		val2 = instr_fetch(eip+2, 1);
		
		print_asm(SAL_SAR_CMD " 0x%2x,%%%s", val2, regsl[m.R_M]);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.R_M) = result.unsign32;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);
		val2 = instr_fetch(eip+1+len, 1);

		print_asm(SAL_SAR_CMD " 0x%2x,%s", val2, ModR_M_asm);
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);

		return 1+len+1;
	}
}

make_helper(concat(ADD_SUB_NAME, _ib2rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _ib2rml(eip)):concat(ADD_SUB_NAME, _ib2rmw(eip));
}

