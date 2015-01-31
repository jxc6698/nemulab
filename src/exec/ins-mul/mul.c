#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(mul_rmb2al)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(R_AL);
		val2.unsign8 = reg_b(m.R_M);
		mul_ch_eflags(cpu, 16, 8);
		reg_b(R_AH) = val1.unsign8;
		reg_b(R_AL) = val2.unsign8;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign8 = swaddr_read(addr, 1);
		val1.unsign8 = reg_b(R_AL);
		mul_ch_eflags(cpu, 16, 8);
		reg_b(R_AH) = val1.unsign8;
		reg_b(R_AL) = val2.unsign8;

		return 1+len;
	}
}

make_helper(mul_rmw2ax)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(R_AX);
		val2.unsign16 = reg_w(m.R_M);
		mul_ch_eflags(cpu, 32, 16);
		reg_w(R_DX) = val1.unsign16;
		reg_w(R_AX) = val2.unsign16;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign16 = swaddr_read(addr, 2);
		val1.unsign16 = reg_w(R_AX);
		mul_ch_eflags(cpu, 32, 16);
		reg_w(R_DX) = val1.unsign16;
		reg_w(R_AX) = val2.unsign16;

		return 1+len;
	}
}

make_helper(mul_rml2eax)
{
	ModR_M m;
	eflags_help_s val1, val2;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(R_EAX);
		val2.unsign32 = reg_l(m.R_M);
		mul_ch_eflags(cpu, 64, 32);
		reg_l(R_EDX) = val1.unsign32;
		reg_l(R_EAX) = val2.unsign32;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val2.unsign32 = swaddr_read(addr, 4);
		val1.unsign32 = reg_l(R_EAX);
		mul_ch_eflags(cpu, 64, 32);
		reg_l(R_EDX) = val1.unsign32;
		reg_l(R_EAX) = val2.unsign32;

		return 1+len;
	}
}

make_helper(mul_rmv2av)
{
	return suffix=='l'?mul_rml2eax(eip):mul_rmw2ax(eip);
}
