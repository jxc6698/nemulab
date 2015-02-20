#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(lgdtl)
{
	swaddr_t addr = instr_fetch(eip+3, 4);
	cpu.gdt.base = swaddr_read(addr+2, 4);
	cpu.gdt.limit = swaddr_read(addr, 2);
	print_asm("lgdtl 0x%x base %x limit %4x", addr, cpu.gdt.base, cpu.gdt.limit);

	return 3+4;
}

make_helper(lgdtw)
{
	swaddr_t addr = instr_fetch(eip+3, 4);
	cpu.gdt.base = swaddr_read(addr+2, 3);
	cpu.gdt.limit = swaddr_read(addr, 2);
	return 3+4;
}


make_helper(lgdt)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	if (m.opcode ==2)
		return suffix=='l'?lgdtl(eip):lgdtw(eip);
	else /* lidt */
		assert(0);
}
