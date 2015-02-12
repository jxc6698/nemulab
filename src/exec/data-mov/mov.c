#include "exec/helper.h"

#define DATA_BYTE 1
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mov-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(mov_i2r_v) {
	return (suffix == 'l' ? mov_i2r_l(eip) : mov_i2r_w(eip));
}

make_helper(mov_i2rm_v) {
	return (suffix == 'l' ? mov_i2rm_l(eip) : mov_i2rm_w(eip));
}

make_helper(mov_r2rm_v) {
	return (suffix == 'l' ? mov_r2rm_l(eip) : mov_r2rm_w(eip));
}

make_helper(mov_rm2r_v) {
	return (suffix == 'l' ? mov_rm2r_l(eip) : mov_rm2r_w(eip));
}

make_helper(mov_a2moffs_v) {
	return (suffix == 'l' ? mov_a2moffs_l(eip) : mov_a2moffs_w(eip));
}

make_helper(mov_moffs2a_v) {
	return (suffix == 'l' ? mov_moffs2a_l(eip) : mov_moffs2a_w(eip));
}

/* sign extended */
make_helper(movsx_rmb2rw) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		int16_t tmp = *(int8_t *)&reg_b(m.R_M);
		reg_w(m.reg) = *(uint16_t *)(&tmp);
		print_asm("movsx %%%s,%%%s", regsb[m.R_M], regsw[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		uint8_t tmp1 = swaddr_read(addr, 1);
		int16_t tmp = *(int8_t *)&tmp1;
		reg_w(m.reg) = *(uint16_t *)(&tmp);
		print_asm("movsx %%%s,%%%s", ModR_M_asm, regsw[m.reg]);

		return 2+len;
	}
}

/* sign extended */
make_helper(movsx_rmb2rl) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		int32_t tmp = *(int8_t *)&reg_b(m.R_M);
		reg_l(m.reg) = *(uint32_t *)(&tmp);
		print_asm("movsx %%%s,%%%s", regsb[m.R_M], regsl[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		uint8_t tmp1 = swaddr_read(addr, 1);
		int32_t tmp = *(int8_t *)&tmp1;
		reg_l(m.reg) = *(uint32_t *)(&tmp);
		print_asm("movsx %s,%%%s", ModR_M_asm, regsl[m.reg]);

		return 2+len;
	}
}

make_helper(movsx_rmb2rv) {
	return (suffix == 'l' ? movsx_rmb2rl(eip) : movsx_rmb2rw(eip));
}

/* sign extended */
make_helper(movsx_rmw2rl) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		int32_t tmp = *(int16_t *)&reg_w(m.R_M);
		reg_l(m.reg) = *(uint32_t *)(&tmp);
		print_asm("movsx %%%s,%%%s", regsw[m.R_M], regsl[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		uint16_t tmp1 = swaddr_read(addr, 2);
		int32_t tmp = *(int16_t *)&tmp1;
		reg_l(m.reg) = *(uint32_t *)(&tmp);
		print_asm("movsx %s,%%%s", ModR_M_asm, regsl[m.reg]);

		return 2+len;
	}
}

/* zero extended */
make_helper(movzx_rmb2rw) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		reg_w(m.reg) = reg_b(m.R_M);
		print_asm("movsx %%%s,%%%s", regsb[m.R_M], regsw[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		reg_w(m.reg) = swaddr_read(addr, 1);
		print_asm("movsx %%%s,%%%s", ModR_M_asm, regsw[m.reg]);

		return 2+len;
	}
}

/* zero extended */
make_helper(movzx_rmb2rl) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		reg_l(m.reg) = reg_b(m.R_M);
		print_asm("movzx %%%s,%%%s", regsb[m.R_M], regsl[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		reg_l(m.reg) = swaddr_read(addr, 1);
		print_asm("movzx %s,%%%s", ModR_M_asm, regsl[m.reg]);

		return 2+len;
	}
}

make_helper(movzx_rmb2rv) {
	return (suffix == 'l' ? movzx_rmb2rl(eip) : movzx_rmb2rw(eip));
}

/* zero extended */
make_helper(movzx_rmw2rl) {
	ModR_M m;
	m.val = instr_fetch(eip + 2, 4);
	if (m.mod == 3) {
		reg_l(m.reg) = reg_w(m.R_M);
		print_asm("movzx %%%s,%%%s", regsw[m.R_M], regsl[m.reg]);

		return 3;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+2, &addr);
		reg_l(m.reg) = swaddr_read(addr, 2);
		print_asm("movzx %s,%%%s", ModR_M_asm, regsl[m.reg]);

		return 2+len;
	}
}

