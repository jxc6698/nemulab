/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"

extern char suffix;

make_helper(pop_mw)
{
	swaddr_t addr;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode==0);

	int len = read_ModR_M(eip+1, &addr); 
	swaddr_write(addr, 2, swaddr_read(cpu.esp, 2));
	cpu.esp += 2;
	print_asm("popw %s", ModR_M_asm);

	return len+1;
}

make_helper(pop_ml)
{
	swaddr_t addr;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode==0);

	int len = read_ModR_M(eip+1, &addr); 
	swaddr_write(addr, 4, swaddr_read(cpu.esp, 4));
	cpu.esp += 4;
	print_asm("popl %s", ModR_M_asm);

	return len+1;
}

make_helper(pop_mv)
{
	return suffix == 'l'?pop_ml(eip):pop_mw(eip);
}

make_helper(pop_rw)
{
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_w(reg) = swaddr_read(cpu.esp, 2);
	cpu.esp += 2;
	print_asm("popw %%%s", regsw[reg]);

	return 1;
}

make_helper(pop_rl)
{
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_l(reg) = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	print_asm("popw %%%s", regsl[reg]);

	return 1;
}

make_helper(pop_rv)
{
	return suffix == 'l'?pop_rl(eip):pop_rw(eip);
}

make_helper(pop_ds)
{
	assert(0);
	return 1;
}

make_helper(pop_es)
{
	assert(0);
	return 1;
}

make_helper(pop_ss)
{
	assert(0);
	return 1;
}

make_helper(pop_fs)
{
	assert(0);
	return 2;
}

make_helper(pop_gs)
{
	assert(0);
	return 2;
}

make_helper(pop_a)
{
	int i;
	for (i=7;i>=0;i--) {
		reg_w(i) = swaddr_read(cpu.esp, 2);
		cpu.esp -= 2;
	}
	return 1;

	return 1;
}

make_helper(pop_ad)
{
	int i;
	for (i=7;i>=0;i--) {
		reg_l(i) = swaddr_read(cpu.esp, 4);
		cpu.esp -= 4;
	}
	return 1;
}

make_helper(pop_av)
{
	return (suffix=='l')?pop_ad(eip):pop_a(eip);
}

make_helper(pop_f)
{
	set_flags(cpu, swaddr_read(cpu.esp, 2));
	cpu.esp -= 2;
	return 1;
}

make_helper(pop_fd)
{
	set_eflags(cpu, swaddr_read(cpu.esp, 4));
	cpu.esp -= 4;
	return 1;
}

make_helper(pop_fv)
{
	return suffix=='l'?pop_fd(eip):pop_f(eip);
}

