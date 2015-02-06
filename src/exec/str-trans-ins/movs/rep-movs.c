#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

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

make_helper(movsb)
{
	return 1;
}

make_helper(movsw)
{
	return 1;
}

make_helper(movsd)
{
	return 1;
}


make_helper(rep)
{
	return 1;
}
