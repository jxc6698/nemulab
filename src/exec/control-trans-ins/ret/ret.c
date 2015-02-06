#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

static make_helper(ret_near_w)
{
	eflags_help_s addr;
	addr.unsign16 = swaddr_read(cpu.eip, 2);
	cpu.esp +=2;
	cpu.eip = addr.sign16;
	print_asm("ret");

	return 1;
}

static make_helper(ret_near_l)
{
	eflags_help_s addr;
	addr.unsign32 = swaddr_read(cpu.eip, 4);
	cpu.esp +=4;
	cpu.eip += addr.sign32;
	print_asm("ret");

	return 1;
}

make_helper(ret_near_v)
{
	return suffix=='l'?ret_near_l(eip):ret_near_w(eip);
}

/* need it ?? */
static make_helper(ret_neariw_w)
{
	eflags_help_s val;
	val.unsign16 = instr_fetch(eip+1, 2);
	uint32_t addr = swaddr_read(cpu.eip, 2);
	cpu.esp +=2;
	cpu.eip = addr;
/* suppose val to be unsigned16 */
	cpu.esp += val.unsign16;
	print_asm("ret 0x%x", val.unsign16);

	return 3;
}

static make_helper(ret_neariw_l)
{
	eflags_help_s val;
	val.unsign16 = instr_fetch(eip+1, 2);
	uint32_t addr = swaddr_read(cpu.eip, 4);
	cpu.esp +=4;
	cpu.eip = addr;
/* suppose val to be unsigned16 */
	cpu.esp += val.unsign16;
	print_asm("ret 0x%x", val.unsign16);
	
	return 3;
}

make_helper(ret_neariw_v)
{
	return suffix=='l'?ret_neariw_l(eip):ret_neariw_w(eip);
}
