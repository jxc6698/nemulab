#include "common.h"
#include "memory.h"
#include <string.h>

static PDE updir[NR_PDE] align_to_page;
static CR3 ucr3;

inline PDE* get_updir() { return updir; }
inline uint32_t get_ucr3() { return ucr3.val; }

inline PDE* get_kpdir();

uint32_t brk = 0;

/* The brk() system call handler. */
void mm_brk(uint32_t new_brk) {
//	assert(brk <= new_brk);
//	mm_malloc(brk, new_brk - brk);
	if(new_brk > brk) {
		mm_malloc(brk, new_brk - brk);
	}
	brk = new_brk;
}

void init_mm() {
	PDE *kpdir = get_kpdir();

	/* make all PDE invalid */
	memset(updir, 0, NR_PDE * sizeof(PDE));

	/* create the same mapping above 0xc0000000 as the kernel mapping does */
	memcpy(&updir[KOFFSET / PT_SIZE], &kpdir[KOFFSET / PT_SIZE], 
			(PHY_MEM / PT_SIZE) * sizeof(PDE));

	ucr3.val = (uint32_t)va_to_pa((uint32_t)updir) & ~0x3ff;
}

/*
*	0x8000000   32 - 5
*	0xbc00000  768 - 4
*   0x1000000
*   0x0c00000    3 - 3
*	0x0800000    2 - 2
*	0x0400000    1 - 1
*	0x0          0 - 0
*/
#define PDE_OFFSET 27
void setusepde(uint32_t addr, uint32_t len)
{
	PDE *kpdir = get_kpdir();//(PDE *)va_to_pa(get_kpdir());
	PDE *up = updir;//(PDE *)va_to_pa((uint32_t)updir);
	uint32_t base= addr&0xffc00000, end=(addr+len)&0xffc00000;
	base >>= 22;
	end >>= 22;
	if (base == 0x2ff) {
		if (!(up[base].val &0x1))
			memcpy(&up[base], &kpdir[4], sizeof(PDE));
		if (!(kpdir[base].val &0x1))
			memcpy(&kpdir[base], &kpdir[4], sizeof(PDE));
	} else {
		for (; base<=end; base++) {
			if (!(up[base].val &0x1))
				memcpy(&up[base], &kpdir[base-PDE_OFFSET], sizeof(PDE));
			if (!(kpdir[base].val &0x1))
				memcpy(&kpdir[base], &kpdir[base-PDE_OFFSET], sizeof(PDE));
		}
	}
}
