#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
#include "exec/eflags-help.h"

extern char suffix;



make_helper(test_ib)
{
	int insLen = 1;
	uint32_t i8 = instr_fetch(eip+1, 1);
	assert(i8<=255);

	insLen += 1;
	i8 = reg_b(R_AL) & i8;
	test_ch_eflags(i8,cpu,8);

	return insLen;
}

make_helper(test_iw)
{
	int insLen = 1;
	uint32_t i16 = instr_fetch(eip+1, 2);

	insLen += 2;
	i16 = reg_w(R_AX) & i16;
	test_ch_eflags(i16,cpu,16);

	return insLen;
}

make_helper(test_il)
{
	int insLen = 1;
	uint32_t i32 = instr_fetch(eip+1, 4);

	insLen += 4;
	i32 = reg_w(R_AX) & i32;
	test_ch_eflags(i32,cpu,32);

	return insLen;
}

make_helper(test_iv)
{
	int insLen = 1;

	insLen += (suffix=='l')?test_il(eip+1):test_iw(eip+1);

	return insLen;
}

/* reg/memory and imm8 */
make_helper(test_rmandib)
{	
	int insLen = 1;
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode == 0);
	
	if (m.mod == 3) {
		uint32_t i8 = instr_fetch(eip+1, 1);
		uint8_t val = reg_b(m.reg);

		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		insLen += (1+1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i8 = instr_fetch(eip+1+len, 1);
		uint32_t val = swaddr_read(addr, 1);

		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		insLen += (1+1+len);
	}

	return insLen;
}

make_helper(test_rmandiw)
{	
	int insLen = 1;
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 0);
	
	if (m.mod == 3) {
		uint32_t i16 = instr_fetch(eip+1, 2);
		uint16_t val = reg_w(m.reg);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		insLen += (1+2);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i16 = instr_fetch(eip+1+len, 2);
		uint32_t val = swaddr_read(addr, 2);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		insLen += (2+len);
	}

	return insLen;
}

make_helper(test_rmandil)
{	
	int insLen = 1;
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 0);
	
	if (m.mod == 3) {
		uint32_t i32 = instr_fetch(eip+1, 4);
		uint32_t val = reg_l(m.reg);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		insLen += (1+4);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i32 = instr_fetch(eip+1+len, 4);
		uint32_t val = swaddr_read(addr, 4);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		insLen += (4+len);
	}

	return insLen;
}

make_helper(test_rmandiv)
{
	return (suffix=='l')?test_rmandil(eip):test_rmandiw(eip);
}

make_helper(test_rmandrb)
{
	int insLen = 1;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		uint32_t i8 = reg_b(m.R_M);
		uint8_t val = reg_b(m.reg);

		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i8 = reg_b(m.R_M);
		uint32_t val = swaddr_read(addr, 1);

		i8 = i8 & val;
		test_ch_eflags(i8, cpu, 8);

		insLen += (len);
	}
	
	return insLen;
}

make_helper(test_rmandrw)
{
	int insLen = 1;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);

	if (m.mod == 3) {
		uint32_t i16 = reg_w(m.R_M);
		uint16_t val = reg_w(m.reg);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i16 = reg_w(m.R_M);
		uint32_t val = swaddr_read(addr, 2);

		i16 = i16 & val;
		test_ch_eflags(i16, cpu, 16);

		insLen += (len);
	}

	return insLen;

}

make_helper(test_rmandrl)
{
	int insLen = 1;
	ModR_M m;

	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 0);
	
	if (m.mod == 3) {
		uint32_t i32 = reg_l(m.R_M);
		uint32_t val = reg_l(m.reg);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip+1, &addr);
		uint32_t i32 = reg_l(m.R_M);
		uint32_t val = swaddr_read(addr, 4);

		i32 = i32 & val;
		test_ch_eflags(i32, cpu, 32);

		insLen += (len);
	}

	return insLen;
}

make_helper(test_rmandrv)
{
	return (suffix=='l')?test_rmandrl(eip):test_rmandrw(eip);
}

