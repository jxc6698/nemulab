#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

make_helper(cmova_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_cf(cpu) && !test_zf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovae_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_cf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovb_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_cf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovbe_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_cf(cpu)||test_zf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmove_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_zf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovg_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = ((!test_zf(cpu))&&(get_sf(cpu)==get_of(cpu)))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovge_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (get_sf(cpu)==get_of(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovl_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (get_sf(cpu)!=get_of(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovle_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_zf(cpu)||(get_sf(cpu)!=get_of(cpu)))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovne_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_zf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovno_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_of(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovnp_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_pf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovns_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_sf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovo_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_of(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovp_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_pf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}

make_helper(cmovs_rml)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_sf(cpu))?1:0;
	if (m.mod == 3) {
		if (val)
			reg_l(m.reg) = reg_l(m.R_M);
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		if (val)
			reg_l(m.reg) = swaddr_read(addr, 4);

		return 2+len;
	}
}



/////////////////////
make_helper(cmova_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_cf(cpu) && !test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovae_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_cf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovb_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_cf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovbe_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_cf(cpu)||test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmove_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovg_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = ((!test_zf(cpu))&&(get_sf(cpu)==get_of(cpu)))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovge_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (get_sf(cpu)==get_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}


make_helper(cmovl_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (get_sf(cpu)!=get_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovle_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_zf(cpu)||(get_sf(cpu)!=get_of(cpu)))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovne_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_zf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovno_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovnp_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_pf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovns_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (!test_sf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovo_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_of(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovp_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_pf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}

make_helper(cmovs_rmw)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	uint8_t val = (test_sf(cpu))?1:0;
	if (m.mod == 3) {
		reg_b(m.reg) = val;
		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		swaddr_write(addr, 1, val);

		return 2+len;
	}
}


#define cmovz_rml(eip) cmove_rml(eip)
#define cmovc_rml(eip) cmovb_rml(eip)
#define cmovna_rml(eip) cmovbe_rml(eip)

#define cmovnae_rml(eip) cmovb_rml(eip)

#define cmovnb_rml(eip) cmovae_rml(eip)

#define cmovnbe_rml(eip) cmova_rml(eip)

#define cmovnc_rml(eip) cmovae_rml(eip)

#define cmovng_rml(eip) cmovle_rml(eip)

#define cmovnge_rml(eip) cmovl_rml(eip)

#define cmovnl_rml(eip) cmovge_rml(eip)

#define cmovnle_rml(eip) cmovg_rml(eip)

#define cmovnz_rml(eip) cmovne_rml(eip)

#define cmovpe_rml(eip) cmovp_rml(eip)

#define cmovpo_rml(eip) cmovnp_rml(eip);
make_helper(cmova_rmv)
{
	return suffix=='l'?cmova_rml(eip):cmova_rmw(eip);
}
make_helper(cmovae_rmv)
{
	return suffix=='l'?cmovae_rml(eip):cmovae_rmw(eip);
}
make_helper(cmovb_rmv)
{
	return suffix=='l'?cmovb_rml(eip):cmovb_rmw(eip);
}
make_helper(cmovbe_rmv)
{
	return suffix=='l'?cmovbe_rml(eip):cmovbe_rmw(eip);
}
make_helper(cmove_rmv)
{
	return suffix=='l'?cmove_rml(eip):cmove_rmw(eip);
}
make_helper(cmovg_rmv)
{
	return suffix=='l'?cmovg_rml(eip):cmovg_rmw(eip);
}
make_helper(cmovge_rmv)
{
	return suffix=='l'?cmovge_rml(eip):cmovge_rmw(eip);
}
make_helper(cmovl_rmv)
{
	return suffix=='l'?cmovl_rml(eip):cmovl_rmw(eip);
}
make_helper(cmovle_rmv)
{
	return suffix=='l'?cmovle_rml(eip):cmovle_rmw(eip);
}
make_helper(cmovne_rmv)
{
	return suffix=='l'?cmovne_rml(eip):cmovne_rmw(eip);
}
make_helper(cmovno_rmv)
{
	return suffix=='l'?cmovno_rml(eip):cmovno_rmw(eip);
}
make_helper(cmovnp_rmv)
{
	return suffix=='l'?cmovnp_rml(eip):cmovnp_rmw(eip);
}
make_helper(cmovns_rmv)
{
	return suffix=='l'?cmovns_rml(eip):cmovns_rmw(eip);
}
make_helper(cmovo_rmv)
{
	return suffix=='l'?cmovo_rml(eip):cmovo_rmw(eip);
}
make_helper(cmovp_rmv)
{
	return suffix=='l'?cmovp_rml(eip):cmovp_rmw(eip);
}
make_helper(cmovs_rmv)
{
	return suffix=='l'?cmovs_rml(eip):cmovs_rmw(eip);
}

