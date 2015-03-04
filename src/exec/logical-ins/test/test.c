#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
#include "exec/eflags-help.h"

extern char suffix;

make_helper(test_ib)
{
	uint32_t i8 = instr_fetch(eip+1, 1);

	print_asm("testb %%al,$0x%x", i8);
	i8 = reg_b(R_AL) & i8;
	test_ch_eflags(i8,cpu,8);

	return 2;
}

make_helper(test_iw)
{
	uint32_t i16 = instr_fetch(eip+1, 2);

	print_asm("testw %%ax,$0x%x", i16);
	i16 = reg_w(R_AX) & i16;
	test_ch_eflags(i16,cpu,16);

	return 3;
}

make_helper(test_il)
{
	uint32_t i32 = instr_fetch(eip+1, 4);

	print_asm("testl %%eax,$0x%x", i32);
	i32 = reg_w(R_AX) & i32;
	test_ch_eflags(i32,cpu,32);

	return 5;
}

make_helper(test_iv)
{
	return (suffix=='l')?test_il(eip+1):test_iw(eip+1);
}

/* reg/memory 2 imm8 */
make_helper(test_rm2ib)
{	
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	
	if (m.mod == 3) {
		uint32_t i8 = instr_fetch(eip+2, 1);
		uint8_t val = reg_b(m.reg);

		print_asm("testb %%%s,$0x%x", regsb[m.reg], i8);
		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		return 1+1+1;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i8 = instr_fetch(eip+1+len, 1);
		uint32_t val = swaddr_read(addr, 1);

		print_asm("testb %s,$0x%x", ModR_M_asm, i8);
		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		return 1+len+1;
	}
}

make_helper(test_rm2iw)
{	
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	
	if (m.mod == 3) {
		uint32_t i16 = instr_fetch(eip+2, 2);
		uint16_t val = reg_w(m.reg);

		print_asm("testw %%%s,$0x%x", regsl[m.reg], i16);
		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		return 1+1+2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i16 = instr_fetch(eip+1+len, 2);
		uint32_t val = swaddr_read(addr, 2);

		print_asm("testw %s,$0x%x", ModR_M_asm, i16);
		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		return 1+len+2;
	}
}

make_helper(test_rm2il)
{	
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	
	if (m.mod == 3) {
		uint32_t i32 = instr_fetch(eip+2, 4);
		uint32_t val = reg_l(m.reg);

		print_asm("testl %%%s,$0x%x", regsl[m.reg], i32);
		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		return 1+1+4;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i32 = instr_fetch(eip+1+len, 4);
		uint32_t val = swaddr_read(addr, 4);
		print_asm("testl %s,$0x%x", ModR_M_asm, i32);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		return 1+len+4;
	}
}

make_helper(test_rm2iv)
{
	return (suffix=='l')?test_rm2il(eip):test_rm2iw(eip);
}

make_helper(test_rm2rb)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		uint32_t i8 = reg_b(m.R_M);
		uint8_t val = reg_b(m.reg);

		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);
		print_asm("testb %%%s,%%%s", regsb[m.reg], regsb[m.R_M]);

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i8 = reg_b(m.R_M);
		uint32_t val = swaddr_read(addr, 1);

		print_asm("testb %%%s,%s", regsb[m.reg], ModR_M_asm);
		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		return 1+len;
	}
}

make_helper(test_rm2rw)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		uint32_t i16 = reg_w(m.R_M);
		uint16_t val = reg_w(m.reg);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);
		print_asm("testw %%%s,%%%s", regsw[m.reg], regsw[m.R_M]);

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i16 = reg_w(m.R_M);
		uint32_t val = swaddr_read(addr, 2);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);
		print_asm("testw %%%s,%s", regsw[m.reg], ModR_M_asm);

		return 1+len;
	}
}

make_helper(test_rm2rl)
{
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	
	if (m.mod == 3) {
		uint32_t i32 = reg_l(m.R_M);
		uint32_t val = reg_l(m.reg);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);
		print_asm("testl %%%s,%%%s", regsl[m.reg], regsl[m.R_M]);

		return 2;
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i32 = reg_l(m.R_M);
		uint32_t val = swaddr_read(addr, 4);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);
		print_asm("testl %%%s,%s", regsl[m.reg], ModR_M_asm);

		return 1+len;
	}
}

make_helper(test_rm2rv)
{
	return (suffix=='l')?test_rm2rl(eip):test_rm2rw(eip);
}

