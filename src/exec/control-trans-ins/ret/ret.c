#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

static make_helper(ret_near_w)
{
	uint16_t addr = swaddr_read(cpu.eip, 2);
	cpu.esp +=2;
	cpu.eip = addr;
	return 1;
}

static make_helper(ret_near_l)
{
	uint32_t addr = swaddr_read(cpu.eip, 4);
	cpu.esp +=4;
	cpu.eip = addr;
	return 1;
}

make_helper(ret_near_v)
{
	return suffix=='l'?ret_near_l(eip):ret_near_w(eip);
}

static make_helper(ret_neariw_w)
{
	eflags_help_s val;
	val.unsign16 = instr_fetch(eip+1, 2);
	uint32_t addr = swaddr_read(cpu.eip, 2);
	cpu.esp +=2;
	cpu.eip = addr;
/* suppose val to be unsigned16 */
	cpu.esp += val.unsign16;
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
	return 3;
}

make_helper(ret_neariw_v)
{
	return suffix=='l'?ret_neariw_l(eip):ret_neariw_w(eip);
}
