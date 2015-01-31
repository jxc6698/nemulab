#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(adc_ib2al)
{
	eflags_help_s val1, val2, result;
	val1.unsign8 = instr_fetch(eip+1, 1);
	val2.unsign8 = reg_b(R_AL);

	adc_ch_eflags(cpu, 8, 8);
	reg_b(R_AL) = result.unsign8;

	return 2;
}

make_helper(adc_iw2ax)
{
	eflags_help_s val1, val2, result;
	val1.unsign16 = instr_fetch(eip+1, 2);
	val2.unsign16 = reg_w(R_AX);

	adc_ch_eflags(cpu, 16, 16);
	reg_w(R_AX) = result.unsign16;

	return 3;
}

make_helper(adc_il2eax)
{
	eflags_help_s val1, val2, result;
	val1.unsign32 = instr_fetch(eip+1, 4);
	val2.unsign32 = reg_l(R_EAX);

	adc_ch_eflags(cpu, 32, 32);
	reg_l(R_EAX) = result.unsign32;

	return 5;
}

make_helper(adc_iv2av)
{
	return suffix=='l'?adc_il2eax(eip):adc_iw2ax(eip);
}

make_helper(adc_ib2rmb)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val2.unsign8 = reg_b(m.reg);
		
		sub_ch_eflags(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = instr_fetch(eip+len+1, 1);

		adc_ch_eflags(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len +1;
	}
}

make_helper(adc_iw2rmw)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign16 = instr_fetch(eip+2, 2);
		val2.unsign16 = reg_w(m.reg);
		
		sub_ch_eflags(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 4;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 2);

		adc_ch_eflags(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len+2;
	}
}

make_helper(adc_il2rml)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign32 = instr_fetch(eip+2, 4);
		val2.unsign32 = reg_l(m.reg);
		
		sub_ch_eflags(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 6;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 4);

		adc_ch_eflags(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len+4;
	}
}

make_helper(adc_iv2rmv)
{
	return suffix=='l'?adc_il2rml(eip):adc_iw2rmw(eip);
}

make_helper(adc_ib2rmw)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val1.sign16 = val1.sign8;
		val2.unsign16 = reg_w(m.reg);
		
		sub_ch_eflags(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 1);
		val1.sign16 = val1.sign8;

		adc_ch_eflags(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len+1;
	}
}

make_helper(adc_ib2rml)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign32 = instr_fetch(eip+2, 1);
		val1.sign16 = val1.sign8;
		val2.unsign32 = reg_l(m.reg);
		
		sub_ch_eflags(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 1);
		val1.sign16 = val1.sign8;

		adc_ch_eflags(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len+1;
	}
}

make_helper(adc_ib2rmv)
{
	return suffix=='l'?adc_ib2rmw(eip):adc_ib2rml(eip);
}

make_helper(adc_rb2rmb)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.reg);
		val2.unsign8 = reg_b(m.R_M);
		
		sub_ch_eflags(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = reg_b(m.reg);

		adc_ch_eflags(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len;
	}
}

make_helper(adc_rw2rmw)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.reg);;
		val2.unsign16 = reg_w(m.R_M);
		
		sub_ch_eflags(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = reg_w(m.reg);

		adc_ch_eflags(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len;
	}
}

make_helper(adc_rl2rml)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.reg);
		val2.unsign32 = reg_l(m.R_M);
		
		sub_ch_eflags(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = reg_l(m.reg);

		adc_ch_eflags(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len;
	}
}

make_helper(adc_rv2rmv)
{
	return suffix=='l'?adc_rl2rml(eip):adc_rw2rmw(eip);
}

make_helper(adc_rmb2rb)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val2.unsign8 = reg_b(m.reg);
		val1.unsign8 = reg_b(m.R_M);
		
		sub_ch_eflags(cpu, 8, 8);
		reg_b(m.reg) = result.unsign8;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);
		val2.unsign8 = reg_b(m.reg);

		adc_ch_eflags(cpu, 8, 8);
		swaddr_write(addr, 1, result.unsign8);

		return 1+len;
	}
}

make_helper(adc_rmw2rw)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val2.unsign16 = reg_w(m.reg);;
		val1.unsign16 = reg_w(m.R_M);
		
		sub_ch_eflags(cpu, 16, 16);
		reg_w(m.reg) = result.unsign16;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2.unsign16 = reg_w(m.reg);

		adc_ch_eflags(cpu, 16, 16);
		swaddr_write(addr, 2, result.unsign16);
		
		return 1+len;
	}
}

make_helper(adc_rml2rl)
{
	ModR_M m;
	eflags_help_s val1, val2, result;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val2.unsign32 = reg_l(m.reg);
		val1.unsign32 = reg_l(m.R_M);
		
		sub_ch_eflags(cpu, 32, 32);
		reg_l(m.reg) = result.unsign32;
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);
		val2.unsign32 = reg_l(m.reg);

		adc_ch_eflags(cpu, 32, 32);
		swaddr_write(addr, 4, result.unsign32);
		
		return 1+len;
	}
}

make_helper(adc_rmv2rv)
{
	return suffix=='l'?adc_rml2rl(eip):adc_rmw2rw(eip);
}

