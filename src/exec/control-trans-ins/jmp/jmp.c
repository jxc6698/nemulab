#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(jmp_relb)
{
	eflags_help_s disp;
	disp.unsign8 = instr_fetch(eip+1, 1);
	cpu.eip += disp.sign8;	
	print_asm("jmp %x", cpu.eip+2);
	return 2;
}

make_helper(jmp_relw)
{
	eflags_help_s disp;
	disp.unsign16 = instr_fetch(eip+1, 2);
	cpu.eip += disp.sign16;
	cpu.eip &= 0x0000ffff;
	print_asm("jmp %x", cpu.eip+3);
	return 3;
}

make_helper(jmp_rell)
{
	eflags_help_s disp;
	disp.unsign32 = instr_fetch(eip+1, 4);
	cpu.eip += disp.sign32;
	print_asm("jmp %x", cpu.eip+5);
	return 5;
}

make_helper(jmp_relv)
{
	return suffix=='l'?jmp_rell(eip):jmp_relw(eip);
}

make_helper(jmp_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	eflags_help_s disp;
	
	if (m.mod == 3) {
		disp.unsign16 = reg_w(m.R_M);
		cpu.eip = disp.sign16;
		cpu.eip &= 0x0000ffff;
		print_asm("jmp %x", cpu.eip);
		cpu.eip -= 2;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		disp.unsign16 = swaddr_read(addr, 2);
		cpu.eip = disp.sign16;
		cpu.eip &= 0x0000ffff;
		print_asm("jmp %x", cpu.eip);
		cpu.eip -= (1+len);

		return 1+len;
	}
}

make_helper(jmp_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	eflags_help_s disp;
	
	if (m.mod == 3) {
		disp.unsign32 = reg_l(m.R_M);
		cpu.eip = disp.unsign32;
		print_asm("jmp %x", cpu.eip);
		cpu.eip -= 2;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		disp.unsign32 = swaddr_read(addr, 4);
		cpu.eip = disp.unsign32;
		print_asm("jmp %x", cpu.eip);
		cpu.eip -= (1+len);

		return 1+len;
	}
}

make_helper(jmp_rmv)
{
	return suffix=='l'?jmp_rml(eip):jmp_rmw(eip);
}

