
make_helper(concat(ADD_SUB_NAME, _ib2al))
{
	eflags_help_s val1, val2, result;
	val1.unsign8 = instr_fetch(eip+1, 1);
	val2.unsign8 = reg_b(R_AL);

	concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
	reg_b(R_AL) = result.unsign8;

	return 2;
}

make_helper(concat(ADD_SUB_NAME, _iw2ax))
{
	eflags_help_s val1, val2, result;
	val1.unsign16 = instr_fetch(eip+1, 2);
	val2.unsign16 = reg_w(R_AX);

	concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
	reg_w(R_AX) = result.unsign16;

	return 3;
}

make_helper(concat(ADD_SUB_NAME, _il2eax))
{
	eflags_help_s val1, val2, result;
	val1.unsign32 = instr_fetch(eip+1, 4);
	val2.unsign32 = reg_l(R_EAX);

	concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
	reg_l(R_EAX) = result.unsign32;

	return 5;
}

make_helper(concat(ADD_SUB_NAME, _iv2av))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _il2eax)(eip):concat(ADD_SUB_NAME, _iw2ax)(eip);
}

make_helper(concat(ADD_SUB_NAME, _ib2rmb))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val2.unsign8 = reg_b(m.reg);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = instr_fetch(eip+len+1, 1);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len +1;
	}
}

make_helper(concat(ADD_SUB_NAME, _iw2rmw))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = instr_fetch(eip+2, 2);
		val2.unsign16 = reg_w(m.reg);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 4;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 2);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len+2;
	}
}

make_helper(concat(ADD_SUB_NAME, _il2rml))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = instr_fetch(eip+2, 4);
		val2.unsign32 = reg_l(m.reg);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 6;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 4);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len+4;
	}
}

make_helper(concat(ADD_SUB_NAME, _iv2rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _il2rml)(eip):concat(ADD_SUB_NAME, _iw2rmw)(eip);
}

make_helper(concat(ADD_SUB_NAME, _ib2rmw))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val1.sign16 = val1.sign8;
		val2.unsign16 = reg_w(m.reg);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 1);
		val1.sign16 = val1.sign8;

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len+1;
	}
}

make_helper(concat(ADD_SUB_NAME, _ib2rml))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = instr_fetch(eip+2, 1);
		val1.sign16 = val1.sign8;
		val2.unsign32 = reg_l(m.reg);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 1);
		val1.sign16 = val1.sign8;

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len+1;
	}
}

make_helper(concat(ADD_SUB_NAME, _ib2rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _ib2rmw)(eip):concat(ADD_SUB_NAME, _ib2rml)(eip);
}

make_helper(concat(ADD_SUB_NAME, _rb2rmb))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.reg);
		val2.unsign8 = reg_b(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = reg_b(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rw2rmw))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.reg);;
		val2.unsign16 = reg_w(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = reg_w(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rl2rml))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.reg);
		val2.unsign32 = reg_l(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = reg_l(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rv2rmv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _rl2rml)(eip):concat(ADD_SUB_NAME, _rw2rmw)(eip);
}

make_helper(concat(ADD_SUB_NAME, _rmb2rb))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign8 = reg_b(m.reg);
		val1.unsign8 = reg_b(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);
		val2.unsign8 = reg_b(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;

		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rmw2rw))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign16 = reg_w(m.reg);;
		val1.unsign16 = reg_w(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2.unsign16 = reg_w(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rml2rl))
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign32 = reg_l(m.reg);
		val1.unsign32 = reg_l(m.R_M);
		
		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);
		val2.unsign32 = reg_l(m.reg);

		concat(ADD_SUB_NAME, _ch_eflags)(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 1+len;
	}
}

make_helper(concat(ADD_SUB_NAME, _rmv2rv))
{
	return suffix=='l'?concat(ADD_SUB_NAME, _rml2rl)(eip):concat(ADD_SUB_NAME, _rmw2rw)(eip);
}

