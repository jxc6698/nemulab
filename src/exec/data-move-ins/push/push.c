#include "exec/helper.h"
#include "cpu/modrm.h"


extern char suffix;

make_helper(push_mw)
{
	swaddr_t addr;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode==6);

	int len = read_ModR_M(eip+1, &addr); 
	print_asm("pushw %s", ModR_M_asm);
	cpu.esp -= 2;
	swaddr_write(cpu.esp, 2, swaddr_read(addr, 2));

	return len+1;
}

make_helper(push_ml)
{
	swaddr_t addr;
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	assert(m.opcode==6);

	int len = read_ModR_M(eip+1, &addr); 
	print_asm("pushl %s", ModR_M_asm);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, swaddr_read(addr, 4));

	return len+1;
}

make_helper(push_mv)
{
	return suffix == 'l'?push_mw(eip):push_ml(eip);
}

make_helper(push_r)
{
	int insLen = 1;
	uint32_t i32;
	uint16_t i16;

	int reg_code = instr_fetch(eip, 1) & 0x07;
	if (suffix == 'l') {
		i32 = reg_l(reg_code);
		print_asm("pushl %%%s", regsl[reg_code]);
		cpu.esp -= 4;
		/* UNFIXED: address should be [ss:esp] */
		swaddr_write(cpu.esp, 4, i32);
	} else { /* 'w' */
		i16 = reg_w(reg_code);
		print_asm("pushw %%%s", regsw[reg_code]);
		cpu.esp -= 2;
		/* UNFIXED: address should be [ss:esp] */
		swaddr_write(cpu.esp, 2, i16);
	}

	return insLen;
}

make_helper(push_ib)
{
	uint8_t i8 = instr_fetch(eip+1, 1);
	print_asm("pushb 0x%2x", i8);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, i8);

	return 2;
}

/* push im16 or im32 */
make_helper(push_iv)
{
	int32_t i32;
	int16_t i16;

	if (suffix == 'l') {
		i32 = instr_fetch(eip+1, 4);
		print_asm("pushl 0x%2x", i32);
		cpu.esp -= 4;
		/* UNFIXED: address should be [ss:esp] */
		swaddr_write(cpu.esp, 4, i32);
		
		return 5;
	} else { /* 'w' */
		i16 = instr_fetch(eip+1, 2);
		print_asm("pushw 0x%2x", i16);
		cpu.esp -= 2;
		/* UNFIXED: address should be [ss:esp] */
		swaddr_write(cpu.esp, 2, i16);

		return 3;
	}
}

make_helper(push_cs)
{
	assert(0);
	return 1;
}

make_helper(push_ss)
{
	assert(0);
	return 1;
}

make_helper(push_ds)
{
	assert(0);
	return 1;
}

make_helper(push_es)
{
	assert(0);
	return 1;
}

make_helper(push_fs)
{
	assert(0);
	uint8_t op = instr_fetch(eip+1, 1);
	if (op==0xa0) {
		;
	} else 
		assert(0);
	return 2;
}

make_helper(push_gs)
{
	assert(0);
	uint8_t op = instr_fetch(eip+1, 1);
	if ( op == 0xa8 ) {
		;
	} else
		assert(0);
	return 2;
}

make_helper(push_a)
{
	/* UNFIXED: address should be [ss:esp] */
	int i;
	for (i=0;i<8;i++) {
		cpu.esp -= 2;
		swaddr_write(cpu.esp, 2, reg_w(i));
	}
	print_asm("pusha");

	return 1;
}

make_helper(push_ad)
{
	int i;
	for (i=0;i<8;i++) {
		cpu.esp -= 4;
		swaddr_write(cpu.esp, 4, reg_l(i));
	}
	print_asm("pushad");
	return 1;
}

make_helper(push_av)
{
	return suffix=='l'?push_ad(eip):push_a(eip);
}

make_helper(push_f)
{
	cpu.esp -= 2;
	swaddr_write(cpu.esp, 2, get_flags(cpu));
	return 1;
}

make_helper(push_fd)
{
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, get_eflags(cpu));
	return 1;
}

make_helper(push_fv)
{
	return suffix=='l'?push_fd(eip):push_f(eip);
}


