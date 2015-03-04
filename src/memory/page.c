#include "common.h"
#include "page.h"
#include "nemu.h"

extern hwaddr_t hwaddr_read(hwaddr_t, size_t);
extern void hwaddr_write(hwaddr_t, size_t, uint32_t);

union pageaddr {
	struct {
	uint32_t pd		:10;
	uint32_t pt		:10;
	uint32_t base	:12;
	};
	uint32_t val;
};

typedef struct TLB_entry {
	uint8_t valid;
	uint32_t viraddr;
	uint32_t lnaddr;
} tlb_entry;

#define TLB_NUM 32
tlb_entry tlb[TLB_NUM];

hwaddr_t page_translate(lnaddr_t addr)
{
	if (cpu.cr0.pg == 0) 
		return addr;
	
	int item = (addr>>12)&0x1f;
	if (tlb[item].valid && (tlb[item].viraddr == PAGE_START(addr)) )
		return tlb[item].lnaddr | (addr&0x0fff);

	int index;
	uint32_t val;
	pgd_t pgd;
	pte_t pte;
	index = (addr>>22)&0x03ff;
	
	val = hwaddr_read(cpu.cr3.val +4*index, 4);
	make_pgd(pgd, val);
	if (pgd.p == 0) {
		printf("cr3  0x%x\n", cpu.cr3.val);
		printf("---pgd val %x addr %x index %x\n", val, addr, index);
		int i;
		for(i=0;i<300;i++) {
			if (hwaddr_read(cpu.cr3.val +4*i, 4) &0x01)
				printf(" index %d preset\n", i);
		}
		printf("eip %x  esp %x\n", cpu.eip, cpu.esp);
		fflush(stdout);
		assert(pgd.p);
	}
	
	index = (addr>>12)&0x03ff;
	val = hwaddr_read((pgd.addr<<12) +4*index, 4);
	make_pte(pte, val);
	if (!pte.p) {
		printf("cr3  0x%x\n", cpu.cr3.val);
		printf("---pte val %x addr %x index %x\n", val, addr, index);
		fflush(stdout);
		assert(pte.p);
	}

	tlb[item].valid = 1;
	tlb[item].viraddr = PAGE_START(addr);
	tlb[item].lnaddr = (pte.addr<<12);

	return (addr&0x0fff)|(pte.addr<<12);
}

void init_tlb()
{
	int i;
	for(i=0;i<TLB_NUM;i++)
		tlb[i].valid = 0;
}
