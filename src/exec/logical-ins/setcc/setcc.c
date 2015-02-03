#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(seta_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_cf(cpu) && !test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setae_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_cf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setb_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_cf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setbe_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_cf(cpu)||test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setc_rmb(eip) setb_rmb(eip)

make_helper(sete_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setg_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = ((!test_zf(cpu))&&(get_sf(cpu)==get_of(cpu)))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setge_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (get_sf(cpu)==get_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}


make_helper(setl_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (get_sf(cpu)!=get_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setle_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_zf(cpu)||(get_sf(cpu)!=get_of(cpu)))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setna_rmb(eip) setbe_rmb(eip)

#define setnae_rmb(eip) setb_rmb(eip)

#define setnb_rmb(eip) setae_rmb(eip)

#define setnbe_rmb(eip) seta_rmb(eip)

#define setnc_rmb(eip) setae_rmb(eip)

make_helper(setne_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setng_rmb(eip) setle_rmb(eip)

#define setnge_rmb(eip) setl_rmb(eip)

#define setnl_rmb(eip) setge_rmb(eip)

#define setnle_rmb(eip) setg_rmb(eip)

make_helper(setno_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setnp_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_pf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setns_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (!test_sf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setnz_rmb(eip) setne_rmb(eip)

make_helper(seto_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

make_helper(setp_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_pf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setpe_rmb(eip) setp_rmb(eip)

#define setpo_rmb(eip) setnp_rmb(eip);

make_helper(sets_rmb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	uint8_t val = (test_sf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 1, val);

		return 1+len;
	}
}

#define setz_rmb(eip) sete_rmb(eip)

