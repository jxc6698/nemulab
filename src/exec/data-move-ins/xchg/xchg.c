#include "exec/helper.h"
#include "cpu/reg.h"
#include "cpu/modrm.h"

extern char suffix;

make_helper(xchg_ax2rw)
{
	uint16_t tmp = reg_w(R_AX);
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_w(R_AX) = reg_w(reg);
	reg_w(reg) = tmp;

	return 1;
}
/*
the same as xchg_ax2rw
make_helper(xchg_rw2ax)
{
	uint16_t tmp = reg_w(R_AX);
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_w(R_AX) = reg_w(reg);
	reg_w(reg) = tmp;

	return 1;
}
*/
make_helper(xchg_eax2rl)
{
	uint32_t tmp = reg_w(R_EAX);
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_l(R_EAX) = reg_l(reg);
	reg_l(reg) = tmp;

	return 1;
}
/*
make_helper(xchg_rl2eax)
{
	uint32_t tmp = reg_l(R_EAX);
	int reg = instr_fetch(eip, 1) & 0x07;
	reg_l(R_EAX) = reg_l(reg);
	reg_l(reg) = tmp;

	return 1;
}
*/

make_helper(xchg_av2rv)
{
	return suffix=='l'?xchg_ax2rw(eip):xchg_eax2rl(eip);
}

make_helper(xchg_rmb2rb)
{
	ModR_M m;
	uint8_t tmp;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		tmp = reg_b(m.R_M);
		reg_b(m.R_M) = reg_b(m.reg);
		reg_b(m.R_M) = tmp;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		tmp = swaddr_read(addr, 1);
		swaddr_write(addr, 1, tmp);
		reg_b(m.reg) = tmp;

		return 1+len;
	}
}

make_helper(xchg_rmw2rw)
{
	ModR_M m;
	uint16_t tmp;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		tmp = reg_w(m.R_M);
		reg_w(m.R_M) = reg_w(m.reg);
		reg_w(m.R_M) = tmp;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		tmp = swaddr_read(addr, 2);
		swaddr_write(addr, 2, tmp);
		reg_w(m.reg) = tmp;

		return 1+len;
	}
}

make_helper(xchg_rml2rl)
{
	ModR_M m;
	uint32_t tmp;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		tmp = reg_l(m.R_M);
		reg_l(m.R_M) = reg_l(m.reg);
		reg_l(m.R_M) = tmp;

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		tmp = swaddr_read(addr, 4);
		swaddr_write(addr, 4, tmp);
		reg_l(m.reg) = tmp;

		return 1+len;
	}
}

make_helper(xchg_rmv2rv)
{
	return suffix=='l'?xchg_rml2rl(eip):xchg_rmw2rw(eip);
}
