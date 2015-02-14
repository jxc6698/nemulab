#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(neg_rmb)
{
	uint8_t val;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod==3) {
		val = reg_b(m.reg);
		neg_ch_eflags(cpu, val, 8);
		reg_b(m.reg) = val;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val = swaddr_read(addr, 1);
		neg_ch_eflags(cpu, val, 8);
		swaddr_write(addr, 1, val);

		return len +1;
	}
}

make_helper(neg_rmw)
{
	uint16_t val;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod==3) {
		val = reg_w(m.reg);
		neg_ch_eflags(cpu, val, 16);
		reg_w(m.reg) = val;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val = swaddr_read(addr, 2);
		neg_ch_eflags(cpu, val, 16);
		swaddr_write(addr, 2, val);

		return len +1;
	}
}

make_helper(neg_rml)
{
	uint32_t val;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod==3) {
		val = reg_l(m.reg);
		neg_ch_eflags(cpu, val, 32);
		reg_l(m.reg) = val;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		val = swaddr_read(addr, 4);
		neg_ch_eflags(cpu, val, 32);
		swaddr_write(addr, 4, val);

		return len +1;
	}
}

make_helper(neg_rmv)
{
	return suffix=='l'?neg_rml(eip):neg_rmw(eip);
}
