#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(lea_m2rw)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	swaddr_t addr = read_ModR_M(eip+1, &addr);
	print_asm("leaw %s, %%%s", ModR_M_asm, regsw[m.reg]);
	reg_w(m.reg) = addr;

	return 2;
}

make_helper(lea_m2rl)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	swaddr_t addr = read_ModR_M(eip+1, &addr);
	print_asm("leal %s, %%%s", ModR_M_asm, regsl[m.reg]);
	reg_l(m.reg) = addr;

	return 2;
}

make_helper(lea_m2rv)
{
	return suffix=='l'?lea_m2rl(eip):lea_m2rw(eip);
}
