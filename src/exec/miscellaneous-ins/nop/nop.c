#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

make_helper(nop)
{
	print_asm("nop");
	return 1;
}
