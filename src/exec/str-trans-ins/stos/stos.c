#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;
extern uint8_t repsuffix;

make_helper(stosb)
{
	swaddr_write(reg_l(R_EDI), 1, reg_b(R_AL));
	reg_l(R_EDI) ++;
	if (repsuffix)
		print_asm("rep stosb %%al,%%es:[%%di]");
	else
		print_asm("stosb %%al,%%es:[%%di]");

	return 1;
}

make_helper(stosl)
{	
	swaddr_write(reg_l(R_EDI), 4, reg_l(R_EAX));
	reg_l(R_EDI) +=4;
	if (repsuffix)
		print_asm("rep stosl %%eax,%%es:[%%di]");
	else
		print_asm("stosl %%eax,%%es:[%%di]");

	return 1;
}

make_helper(stosw)
{
	swaddr_write(reg_l(R_EDI), 2, reg_w(R_AX));
	reg_l(R_EDI) +=2;
	if (repsuffix)
		print_asm("rep stosw %%ax,%%es:[%%edi]");
	else
		print_asm("stosw %%ax,%%es:[%%edi]");

	return 1;
}

make_helper(stosv)
{
	return suffix=='l'?stosl(eip):stosw(eip);
}
