#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;
uint8_t repsuffix = 0;
/*
the same as movsb movsw movsd ?
make_helper(movs_mb2mb)
{
	uint8_t u8 = swaddr_read(cpu.esi,1);
	swaddr_write(cpu.edi, 1, u8);
	
	return 1;
}

make_helper(movs_mw2mw)
{
	return 1;
}

make_helper(movs_ml2ml)
{
	return 1;
}
*/
make_helper(movsb)
{
	uint8_t u8 = swaddr_read(reg_l(R_ESI),1);
	swaddr_write(reg_l(R_EDI), 1, u8);
	int t;
	t = test_df(cpu)?-1:1;
	reg_l(R_ESI) += t;
	reg_l(R_EDI) += t;

	if (repsuffix)
		print_asm("rep movsb %%ds:[%%esi],%%es:[%%edi]");
	else
		print_asm("movsb %%ds:[%%esi],%%es:[%%edi]");

	return 1;
}

make_helper(movsw)
{
	uint16_t u16 = swaddr_read(reg_l(R_ESI),2);
	swaddr_write(reg_l(R_EDI), 2, u16);
	int t;
	t = test_df(cpu)?-2:2;
	reg_l(R_ESI) += t;
	reg_l(R_EDI) += t;
	
	if (repsuffix)
		print_asm("rep movsw %%ds:[%%esi],%%es:[%%edi]");
	else
		print_asm("movsb %%ds:[%%esi],%%es:[%%edi]");

	return 1;
}

make_helper(movsd)
{
	uint32_t u32 = swaddr_read(cpu.esi,4);
	swaddr_write(cpu.edi, 4, u32);
	int t;
	t = test_df(cpu)?-4:4;
	reg_l(R_ESI) += t;
	reg_l(R_EDI) += t;

	if (repsuffix)
		print_asm("rep movsd %%ds:[%%esi],%%es:[%%edi]");
	else
		print_asm("movsd %%ds:[%%esi],%%es:[%%edi]");

	return 1;
}

make_helper(movsv)
{
	return suffix=='l'?movsd(eip):movsw(eip);
}

typedef int (*helper_fun)(swaddr_t);
extern helper_fun opcode_table[256];
make_helper(rep)
{
	uint32_t times = reg_l(R_ECX);
	uint8_t op2 = instr_fetch(eip+1, 1);
	int len=0,i;
	repsuffix = 1;
	for(i=0;i<times;i++) {
		len = opcode_table[op2](eip+1);
	}
	repsuffix = 0;

	return 1+len;
}
