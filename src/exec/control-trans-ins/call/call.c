#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(call_rell)
{
	eflags_help_s disp;
	disp.unsign32 = instr_fetch(eip+1, 4);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip+5);
	cpu.eip += disp.sign32;
	print_asm("call 0x%x", cpu.eip);
	return 5;
}

make_helper(call_relw)
{
	eflags_help_s disp;
	disp.unsign16 = instr_fetch(eip+1, 2);
	cpu.esp -= 2;
	swaddr_write(cpu.esp, 2, cpu.eip+3);
	cpu.eip += disp.sign16;
	cpu.eip &= 0x0000ffff;
	print_asm("call 0x%x", cpu.eip);
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
		cpu.esp -= 2;
		swaddr_write(cpu.esp, 2, cpu.eip+2);
		disp.unsign16 = reg_w(m.reg);
		cpu.eip += disp.sign16;
		cpu.eip &= 0x0000ffff;
		print_asm("call 0x%x", cpu.eip);

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		cpu.esp -= 2;
		swaddr_write(cpu.esp, 2, cpu.eip+1+len);
		disp.unsign16 = instr_fetch(eip+1+len, 2);
		cpu.eip += disp.sign16;
		cpu.eip &= 0x0000ffff;
		print_asm("call 0x%x", cpu.eip);

		return 1+len;
	}
}

make_helper(call_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	eflags_help_s disp;
	
	if (m.mod == 3) {
		cpu.esp -= 4;
		swaddr_write(cpu.esp, 4, cpu.eip+2);
		disp.unsign32 = reg_l(m.reg);
		cpu.eip += disp.sign32;
		print_asm("call 0x%x", cpu.eip);

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		cpu.esp -= 4;
		swaddr_write(cpu.esp, 4, cpu.eip+1+len);
		disp.unsign32 = instr_fetch(eip+1+len, 4);
		cpu.eip += disp.sign32;
		print_asm("call 0x%x", cpu.eip);

		return 1+len;
	}
}

make_helper(call_rmv)
{
	return suffix=='l'?call_rml(eip):call_rmw(eip);
}
