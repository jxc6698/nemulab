#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(cbw)
{
	reg_w(R_AX) = (int8_t)reg_b(R_AL);
	print_asm("cbw");

	return 1;
}

make_helper(cwde)
{
	reg_l(R_EAX) = (int16_t)reg_w(R_AX);
	print_asm("cwde");

	return 1;
}

make_helper(convert_bw)
{
	return suffix=='l'?cwde(eip):cbw(eip);
}

make_helper(cwd)
{
	reg_w(R_DX) = (reg_w(R_AX)>>15)?0xffff:0x0000;
	print_asm("cwd");

	return 1;
}

make_helper(cdq)
{
	reg_l(R_EDX) = (reg_l(R_EAX)>>31)?0xffffffff:0x00000000;
	print_asm("cdq");

	return 1;
}

make_helper(convert_wd)
{
	return suffix=='l'?cdq(eip):cwd(eip);
}
