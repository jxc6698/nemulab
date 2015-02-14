#include "cpu/reg.h"
#include "exec/helper.h"

extern char suffix;

make_helper(leave_w)
{
	print_asm("leavew");
	reg_w(R_SP) = reg_w(R_BP);

	/* UNFIXED esp -> [ss:esp]*/	
	reg_w(R_BP) = swaddr_read(cpu.esp, 2);
	cpu.esp += 2; 
	
	return 1;
}

make_helper(leave_l)
{
	print_asm("leavew");
	reg_w(R_ESP) = reg_w(R_EBP);

	/* UNFIXED esp -> [ss:esp]*/	
	reg_w(R_EBP) = swaddr_read(cpu.esp, 4);
	cpu.esp += 4; 
	
	return 1;
}

make_helper(leave)
{
	return suffix=='l'?leave_l(eip):leave_w(eip);
}
