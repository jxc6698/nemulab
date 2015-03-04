#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

make_helper(cld)
{
	clear_df(cpu);
	print_asm("cld");
	return 1;
}


