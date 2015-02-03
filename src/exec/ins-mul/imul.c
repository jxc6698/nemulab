#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(imul_rmb2al)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(R_AL);
		val2.unsign8 = reg_b(m.R_M);
		imul_ch_eflags(cpu, 16, 8);
		reg_b(R_AH) = val1.unsign8;
		reg_b(R_AL) = val2.unsign8;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = reg_b(R_AL);
		imul_ch_eflags(cpu, 16, 8);
		reg_b(R_AH) = val1.unsign8;
		reg_b(R_AL) = val2.unsign8;

		return 1+len;
	}
}

make_helper(imul_rmw2ax)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(R_AX);
		val2.unsign16 = reg_w(m.R_M);
		imul_ch_eflags(cpu, 32, 16);
		reg_w(R_DX) = val1.unsign16;
		reg_w(R_AX) = val2.unsign16;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = reg_w(R_AX);
		imul_ch_eflags(cpu, 32, 16);
		reg_w(R_DX) = val1.unsign16;
		reg_w(R_AX) = val2.unsign16;

		return 1+len;
	}
}

make_helper(imul_rml2eax)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(R_EAX);
		val2.unsign32 = reg_l(m.R_M);
		imul_ch_eflags(cpu, 64, 32);
		reg_l(R_EDX) = val1.unsign32;
		reg_l(R_EAX) = val2.unsign32;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = reg_l(R_EAX);
		imul_ch_eflags(cpu, 64, 32);
		reg_l(R_EDX) = val1.unsign32;
		reg_l(R_EAX) = val2.unsign32;

		return 1+len;
	}
}

make_helper(imul_rmv2av)
{
	return suffix=='l'?imul_rml2eax(eip):imul_rmw2ax(eip);
}

make_helper(imul_rmw2rw)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+2, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val2.unsign16 = reg_w(m.reg);;
		val1.unsign16 = reg_w(m.R_M);
		
		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2.unsign16 = reg_w(m.reg);

		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;
		
		return 2+len;
	}
}

make_helper(imul_rml2rl)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+2, 1);
	assert(m.opcode == 0);
	if (m.mod == 3) {
		val2.unsign32 = reg_l(m.reg);
		val1.unsign32 = reg_l(m.R_M);
		
		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		val1.unsign32 = swaddr_read(addr, 4);
		val2.unsign32 = reg_l(m.reg);

		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;
		
		return 2+len;
	}
}

make_helper(imul_rmv2rv)
{
	return suffix=='l'?imul_rml2rl(eip):imul_rmw2rw(eip);
}


make_helper(imul_rmwib2rw)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val1.sign16 = val1.sign8;
		val2.unsign16 = reg_w(m.R_M);
		
		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 1);
		val1.sign16 = val1.sign8;

		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;

		return 1+len +1;
	}
}

make_helper(imul_rmlib2rl)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = instr_fetch(eip+2, 1);
		val1.sign32 = val1.sign8;
		val2.unsign32 = reg_l(m.R_M);
		
		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;
		
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 1);
		val1.sign32 = val1.sign8;

		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;

		return 1+len +1;
	}
}

make_helper(imul_rmvib2rv)
{
	return suffix=='l'?imul_rmlib2rl(eip):imul_rmwib2rw(eip);
}

make_helper(imul_ib2rw)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	val1.unsign8 = instr_fetch(eip+2, 1);
	val2.unsign16 = reg_w(m.reg);
	val1.sign16 = val1.sign8;
	
	imul_ch_eflags(cpu, 32, 16);
	reg_w(m.reg) = val2.unsign16;
	
	return 3;
}

make_helper(imul_ib2rl)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	val1.unsign8 = instr_fetch(eip+2, 1);
	val2.unsign32 = reg_l(m.reg);
	val1.sign32 = val1.sign8;
	
	imul_ch_eflags(cpu, 64, 32);
	reg_l(m.reg) = val2.unsign32;
	
	return 3;
}

make_helper(imul_ib2rv)
{
	return suffix=='l'?imul_ib2rl(eip):imul_ib2rw(eip);
}

make_helper(imul_rmwiw2rw)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = instr_fetch(eip+2, 2);
		val2.unsign16 = reg_w(m.R_M);
		
		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;
		
		return 4;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = instr_fetch(eip+len+1, 2);

		imul_ch_eflags(cpu, 32, 16);
		reg_w(m.reg) = val2.unsign16;

		return 1+len +2;
	}
}

make_helper(imul_rmlil2rl)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = instr_fetch(eip+2, 4);
		val2.unsign32 = reg_l(m.R_M);
		
		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;
		
		return 6;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = instr_fetch(eip+len+1, 4);

		imul_ch_eflags(cpu, 64, 32);
		reg_l(m.reg) = val2.unsign32;

		return 1+len +4;
	}
}

make_helper(imul_rmviv2rv)
{
	return suffix=='l'?imul_rmlil2rl(eip):imul_rmwiw2rw(eip);
}

make_helper(imul_iw2rw)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	val1.unsign16 = instr_fetch(eip+2, 2);
	val2.unsign16 = reg_w(m.reg);
	
	imul_ch_eflags(cpu, 32, 16);
	reg_w(m.reg) = val2.unsign16;
	
	return 4;
}

make_helper(imul_il2rl)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	val1.unsign32 = instr_fetch(eip+2, 4);
	val2.unsign32 = reg_l(m.reg);
	
	imul_ch_eflags(cpu, 64, 32);
	reg_l(m.reg) = val2.unsign32;
	
	return 6;
}

make_helper(imul_iv2rv)
{
	return suffix=='l'?imul_il2rl(eip):imul_iw2rw(eip);
}

