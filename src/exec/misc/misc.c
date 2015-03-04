#include "exec/helper.h"

#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

make_helper(inv) {
	/* invalid opcode */

	uint8_t temp[8];
	((uint32_t *)temp)[0] = instr_fetch(eip, 4);
	((uint32_t *)temp)[1] = instr_fetch(eip + 4, 4);
	printf("invalid opcode(eip = 0x%08x): %02x %02x %02x %02x %02x %02x %02x %02x ...\n", 
			eip, temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

	printf("current register\n");
	printf("EAX %8x  ECX %8x\n", cpu.eax, cpu.ecx);
	printf("EDX %8x  EBX %8x\n", cpu.edx, cpu.ebx);
	printf("ESP %8x  EBP %8x\n", cpu.esp, cpu.ebp);
	printf("ESI %8x  EDI %8x\n", cpu.esi, cpu.edi);
	printf("EFALGS 0x%08x\n", cpu.eflags.val);
	fflush(stdout);

	assert(0);
}

make_helper(int3) {
	/* A breakpoint is hit! Do something here! */
	stop_state = BREAK;
	nemu_state = STOP;
	int index = recover_bp(eip);
	assert(index!=-1);
	printf("breakpoint %d at address 0x%x\n", index, eip);
	
	return 0;
}

make_helper(nemu_trap) {
	printf("nemu: HIT \33[1;31m%s\33[0m TRAP at eip = 0x%08x\n\n", (cpu.eax == 0 ? "GOOD" : "BAD"), cpu.eip);
	if (cpu.eax == 2) {
		char a;
		int i=0;
		while ( (a=swaddr_read(cpu.ecx+i, 1))) {
			printf("%c", a);
			i++;
		}
		fflush(stdout);
	} else 
		nemu_state = END;
		

	print_asm("nemu trap");
	return 1;
}

make_helper(escape_cmd)
{
	uint8_t op = instr_fetch(eip,1);
	if (op== 0xd9) // fidz
		return 2;
	else  if (op== 0xdd)
		return 6;
	assert(0);
	return 3; 
}
