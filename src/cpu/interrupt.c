#include "cpu/interrupt.h"
#include "cpu/reg.h"
#include "nemu.h"
#include "common.h"

#include <setjmp.h>
extern jmp_buf jbuf;
 
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eflags.val);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.cs.val);
	cpu.esp -= 4;
	swaddr_write(cpu.esp, 4, cpu.eip);

	uint32_t f0_3,f4_7;
	f0_3 = swaddr_read(cpu.idtr.base+NO*8, 4);
	f4_7 = swaddr_read(cpu.idtr.base+NO*8 +4, 4);
	swaddr_t addr = (f0_3 &0x00ffff ) | (f4_7&0xffff0000);
 	cpu.eip = addr;
	cpu.cs.val = (f0_3&0xffff0000) >> 16;

	if ((f4_7&0x000f00) == 0x0e00) {
		clear_if(cpu);
	}
 
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}

void set_interrupt(int num)
{
	return;
}
