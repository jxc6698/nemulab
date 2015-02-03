#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(call_rell)
{
	uint32_t disp = instr_fetch(eip+1, 4);
	cpu.eip = disp;	
	return 5;
}

make_helper(call_relw)
{
	uint16_t disp = instr_fetch(eip+1, 2);
	cpu.eip = disp;	
	cpu.eip &= 0x0000ffff;
	return 3;
}

make_helper(call_relv)
{
	return suffix=='l'?call_rell(eip):call_relw(eip);
}

make_helper(call_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	eflags_help_s disp;
	
	if (m.mod == 3) {
		disp.unsign16 = reg_w(m.reg);
		cpu.eip = disp.unsign16;
		cpu.eip &= 0x0000ffff;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		disp.unsign16 = instr_fetch(eip+1+len, 2);
		cpu.eip = disp.unsign16;
		cpu.eip &= 0x0000ffff;

		return 1+len;
	}
}

make_helper(call_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	eflags_help_s disp;
	
	if (m.mod == 3) {
		disp.unsign32 = reg_l(m.reg);
		cpu.eip = disp.sign32;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		disp.unsign32 = instr_fetch(eip+1+len, 4);
		cpu.eip = disp.unsign32;

		return 1+len;
	}
}

make_helper(call_rmv)
{
	return suffix=='l'?call_rml(eip):call_rmw(eip);
}
