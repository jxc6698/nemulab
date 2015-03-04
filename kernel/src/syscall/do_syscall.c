#include "x86.h"

#include <sys/syscall.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);
void serial_printc(char);

static void sys_brk(TrapFrame *tf) {
#ifdef IA32_PAGE
	mm_brk(tf->ebx);
#endif
	tf->eax = 0;
}

void do_syscall(TrapFrame *tf) {
	switch(tf->eax) {
		/* The ``add_irq_handle'' system call is artificial. We use it to 
		 * let user program register its interrupt handlers. But this is 
		 * very dangerous in a real operating system. Therefore such a 
		 * system call never exists in GNU/Linux.
		 */
		case 0: add_irq_handle(tf->ebx, (void*)tf->ecx); break;

		case SYS_write: 
			if (tf->ebx == 1|| tf->ebx == 1) {
				char *buf = (char *)tf->ecx;
				int len = tf->edx;
				asm volatile (".byte 0x82" : : "a"(2), "c"(buf), "d"(len));

				int i=0;
				while (buf[i]) {
					serial_printc(buf[i]);
					i++;
				}
				tf->eax = len;
			} else 
				;
		break;

		case SYS_lseek:
			if (tf->ebx == 1|| tf->ebx == 1) {
				;
			}

		break;

		case SYS_brk: sys_brk(tf); break;

		/* TODO: Add more system calls. */

		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}

