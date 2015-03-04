#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include "device/i8259.h"
#include "cpu/interrupt.h"

#include <setjmp.h>

#define LOADER_START 0x100000

int exec(swaddr_t);
void load_prog();
void init_dram();
void init_tlb();
void sdl_clear_event_queue();

char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */
bool nextintr=false;

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
//	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
    cpu.eflags.val = 0x02;
	cpu.esp = 0x100000;
	cpu.ebp = 0;
	cpu.cr0.val = 0;

	sdl_clear_event_queue();

	init_dram();
	init_tlb();
}

#define SKIP_INT  0//4000000
volatile int countint =0;
static void print_bin_instr(swaddr_t eip, int len) {
	static int lastpg =0;
	int i;
	int t=cpu.cr0.pg;
	cpu.cr0.pg = lastpg;

	countint ++;
	if (countint > SKIP_INT) {

	printf("%8x:   ", eip);
	/* if change cr0:pg for get opcode correctly */

	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
	}

	cpu.cr0.pg = t;
	lastpg = cpu.cr0.pg;
}

void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);

		switch(stop_state) {
		case NOBREAK:
			break;
		case BREAK: 
			stop_state = BREAK1;
//			cpu.breakpointAddr = cpu.eip;
			return;
		case BREAK1:
			stop_state = NOBREAK;
//			reset_bp(cpu.breakpointAddr);
			reset_bp(cpu.eip);
			break;
		default :
			assert(0);
		}

		cpu.eip += instr_len;

		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);

	if (countint > SKIP_INT) {
			puts(assembly);
	}
		}

		if(cpu.INTR & cpu.eflags.If & nextintr) {
			uint32_t intr_no = i8259_query_intr();
			i8259_ack_intr();
			raise_intr(intr_no);
		}
		nextintr = cpu.eflags.If;

		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { return; }
		else if (nemu_state == STOP) return;
	}
}
