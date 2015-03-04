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

make_helper(mov_cr2rl)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	switch(m.reg) {
		case 0:
			reg_l(m.R_M) = cpu.cr0.val;
			break;
		case 3:
			reg_l(m.R_M) = cpu.cr3.val;
			break;
		default:
			printf("mov crx to reg \n");
			assert(0);
	}
	print_asm("mov %%cr%d, %%%s", m.reg, regsl[m.R_M]);
	return 3;
}

uint32_t hwaddr_read(hwaddr_t, uint32_t);
void testcr3() 
{
	int i=0;
	uint32_t val;
	for (i=0;i<128;i++) {
		val = hwaddr_read(cpu.cr3.val+ 4*i, 4);
		if (val&0x01)
			printf("index %d present\n", i);
	}
}

make_helper(mov_rl2cr)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	switch(m.reg) {
		case 0:
			cpu.cr0.val = reg_l(m.R_M);
			break;
		case 3:
			cpu.cr3.val = reg_l(m.R_M);
//			testcr3();
			break;
		default:
			printf("mov crx to reg \n");
			assert(0);
	}
	print_asm("mov %%%s, %%cr%d", regsl[m.R_M], m.reg);
	return 3;
}

make_helper(mov_rm2sg)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		cpu.sg[m.reg] = reg_l(m.R_M);
		print_asm("mov %%%s,%%%s", regsl[m.R_M], regss[m.reg]);
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		cpu.sg[m.reg] = swaddr_read(addr, 1);
		print_asm("mov %%%s,%%%s", ModR_M_asm, regss[m.reg]);

		return 1+len;
	}

}

make_helper(mov_sg2rm)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		reg_l(m.R_M) = cpu.sg[m.reg];
		print_asm("mov %%%s,%%%s", regsl[m.R_M], regss[m.reg]);
		
		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		swaddr_write(addr, 4, cpu.sg[m.reg]);

		print_asm("mov %%%s,%%%s", ModR_M_asm, regss[m.reg]);

		return 1+len;
	}

}
