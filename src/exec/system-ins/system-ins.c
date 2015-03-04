#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"
#include "io/port-io.h"
#include "io/mmio.h"

extern char suffix;

make_helper(lgdtl)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	if (m.R_M ==5) {
		swaddr_t addr = instr_fetch(eip+3, 4);
		cpu.gdtr.base = swaddr_read(addr+2, 4);
		cpu.gdtr.limit = swaddr_read(addr, 2);
		print_asm("lgdtl 0x%x base %x limit %4x", addr, cpu.gdtr.base, cpu.gdtr.limit);
		return 3+4;
	} else if (m.R_M==0) {
		swaddr_t addr = reg_l(R_EAX);
		cpu.gdtr.base = swaddr_read(addr+2, 4);
		cpu.gdtr.limit = swaddr_read(addr, 2);
		print_asm("lgdtl (%%eax)");
		return 3;
	} else {
		assert(0);
		return 3;
	}
}

make_helper(lgdtw)
{
	assert(0);
	swaddr_t addr = instr_fetch(eip+3, 4);
	cpu.gdtr.base = swaddr_read(addr+2, 3);
	cpu.gdtr.limit = swaddr_read(addr, 2);
	return 3+4;
}

make_helper(lidtl)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	if (m.R_M ==5) {
		swaddr_t addr = instr_fetch(eip+3, 4);
		cpu.idtr.base = swaddr_read(addr+2, 4);
		cpu.idtr.limit = swaddr_read(addr, 2);
		print_asm("lidtl 0x%x base %x limit %4x", addr, cpu.idtr.base, cpu.idtr.limit);

		return 3+4;
	} else if (m.R_M==0) {
		swaddr_t addr = reg_l(R_EAX);
		cpu.idtr.base = swaddr_read(addr+2, 4);
		cpu.idtr.limit = swaddr_read(addr, 2);
		print_asm("lidtl (%%EAX)");

		return 3;
	} else {
		assert(0);
		return 3;
	}
}

make_helper(lidtw)
{
	assert(0);
	swaddr_t addr = instr_fetch(eip+3, 4);
	cpu.idtr.base = swaddr_read(addr+2, 3);
	cpu.idtr.limit = swaddr_read(addr, 2);
	print_asm("lidtw 0x%x base %x limit %4x", addr, cpu.idtr.base, cpu.idtr.limit);

	return 3+4;
}


make_helper(lgdtidt)
{
	ModR_M m;
	m.val = instr_fetch(eip+2, 1);
	if (m.opcode ==2)
		return suffix=='l'?lgdtl(eip):lgdtw(eip);
	else if (m.opcode ==3)/* lidt */
		return suffix=='l'?lidtl(eip):lgdtw(eip);
	else 
		assert(0);
}

make_helper(cli)
{
	clear_if(cpu);
	print_asm("cli");
	return 1;
}

make_helper(sti)
{
	set_if(cpu);
	print_asm("sti");
	return 1;
}

make_helper(hlt)
{
// not pass
	if (cpu.eflags.If==0) {
		printf("eip %x\n", cpu.eip);
		fflush(stdout);
		assert(0);
	}
	/* do nothing 
	*	wait for NMI interrupt 
	*/
	while (1) {
		if (cpu.INTR)
			break;
	}
	print_asm("hlt");
	return 1;
}

void raise_intr(uint8_t);

make_helper(intc)
{
	uint8_t instr = instr_fetch(eip+1,1);
/*	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eflags.val);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.cs.val);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip);
*/
	cpu.eip += 2;
	raise_intr(instr);

	print_asm("int $0x%2x", instr);

	return 2;
}

make_helper(iret)
{
	cpu.eip = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	cpu.cs.val = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	cpu.eflags.val = swaddr_read(cpu.esp, 4);
	cpu.esp += 4;
	cpu.eip += (-1);

	print_asm("iret");
	return 1;
}

make_helper(in_ib)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	reg_b(R_AL) = pio_read(u8, 1);
	print_asm("inb %%%s,$%2x", regsb[R_AL], u8); 

	return 2;
}

make_helper(in_iw)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	reg_w(R_AX) = pio_read(u8, 2);
	print_asm("inw %%%s,$%2x", regsw[R_AX], u8);

	return 2;
}

make_helper(in_il)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	reg_l(R_EAX) = pio_read(u8, 4);
	print_asm("inl %%%s,$%2x", regsl[R_EAX], u8);

	return 2;
}

make_helper(in_iv)
{
	return suffix=='l'?in_il(eip):in_iw(eip);
}

make_helper(in_dxb)
{
	uint16_t u16 = reg_w(R_DX);
	reg_b(R_AL) = pio_read(u16, 1);
	print_asm("inb %%%s,%%%s", regsb[R_AL], regsw[R_DX]);

	return 1;
}

make_helper(in_dxw)
{
	uint16_t u16 = reg_w(R_DX);
	reg_w(R_AX) = pio_read(u16, 2);
	print_asm("inw %%%s,%%%s", regsw[R_AX], regsw[R_DX]);

	return 1;
}

make_helper(in_dxl)
{
	uint16_t u16 = reg_w(R_DX);
	reg_l(R_EAX) = pio_read(u16, 4);
	print_asm("inl %%%s,%%%s", regsl[R_EAX], regsw[R_DX]);

	return 1;
}

make_helper(in_dxv)
{
	return suffix=='l'?in_dxl(eip):in_dxw(eip);
}




make_helper(out_ib)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	pio_write(u8, 1, reg_b(R_AL));
	print_asm("outb %%%s,$%2x", regsb[R_AL], u8);

	return 2;
}

make_helper(out_iw)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	pio_write(u8, 2, reg_w(R_AX));
	print_asm("outw %%%s,$%2x", regsw[R_AX], u8);

	return 2;
}

make_helper(out_il)
{
	uint8_t u8 = instr_fetch(eip+1, 1);
	pio_write(u8, 4, reg_l(R_EAX));
	print_asm("outl %%%s,$%2x", regsl[R_EAX], u8);

	return 2;
}

make_helper(out_iv)
{
	return suffix=='l'?out_il(eip):out_iw(eip);
}

make_helper(out_dxb)
{
	uint16_t u16 = reg_w(R_DX);
	pio_write(u16, 1, reg_b(R_AL));
	print_asm("outb %%%s,%%%s", regsb[R_AL], regsw[R_DX]);

	return 1;
}

make_helper(out_dxw)
{
	uint16_t u16 = reg_w(R_DX);
	pio_write(u16, 2, reg_w(R_AX));
	print_asm("outw %%%s,%%%s", regsw[R_AX], regsw[R_DX]);

	return 1;
}

make_helper(out_dxl)
{
	uint16_t u16 = reg_w(R_DX);
	pio_write(u16, 4, reg_l(R_EAX));
	print_asm("outl %%%s,%%%s", regsl[R_EAX], regsw[R_DX]);

	return 1;
}

make_helper(out_dxv)
{
	return suffix=='l'?out_dxl(eip):out_dxw(eip);
}


