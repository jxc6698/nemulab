#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(not_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		reg_b(m.R_M) = ~reg_b(m.R_M);
		print_asm("notb %%%s", regsw[m.R_M]);
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, ~swaddr_read(addr, 1));
		print_asm("notb %s", ModR_M_asm);

		return 1+len;
	}
}

make_helper(not_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		reg_w(m.R_M) = ~reg_w(m.R_M);
		print_asm("notw %%%s", regsw[m.R_M]);
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 2, ~swaddr_read(addr, 2));
		print_asm("notw %s", ModR_M_asm);

		return 1+len;
	}
}


make_helper(not_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		reg_l(m.R_M) = ~reg_l(m.R_M);
		print_asm("notl %%%s", regsl[m.R_M]);
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 4, ~swaddr_read(addr, 4));
		print_asm("notl %s", ModR_M_asm);

		return 1+len;
	}
}

make_helper(not_rmv)
{
	return suffix=='l'?not_rml(eip):not_rmw(eip);
}
