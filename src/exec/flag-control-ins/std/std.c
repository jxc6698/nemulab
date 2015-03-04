#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

make_helper(std)
{
	set_df(cpu);
	print_asm("std");
	return 1;
}
