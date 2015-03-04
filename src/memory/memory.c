#include "common.h"
#include "page.h"
#include "io/port-io.h"
#include "io/mmio.h"

uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
hwaddr_t page_translate(lnaddr_t addr);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	int16_t index = is_mmio(addr);
	if (index!=-1) {
		return mmio_read(addr, len, index);
	}
	return dram_read(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	int16_t index = is_mmio(addr);
	if (index!=-1) {
		mmio_write(addr, len, data, index);
	} else 
		dram_write(addr, len, data);
}

#define UPPER 0xffffffff
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if (addr >= UPPER ) {
		printf("addrsss is %x\n", addr);
		fflush(stdout);
		assert(0);
	} else {
		if (SAMEPAGE(addr, (addr+len-1))) {
			hwaddr_t hwaddr = page_translate(addr);
			return hwaddr_read(hwaddr, len);
		} else {
			hwaddr_t hwaddr = page_translate(addr);
			int len1 = PAGE_START(addr+len-1) - addr;
			uint32_t value =0;
			int i=0;
			for (i=0;i<len1;i++) {
				value |= (hwaddr_read(hwaddr+i, 1) << ((i)<<3));
			}
			hwaddr = page_translate( PAGE_START(addr+len-1));
			for (i=0;i<len-len1;i++) {
				value |= (hwaddr_read(hwaddr+i, 1) << ((len1+i)<<3));
			}
			return value;
		}
	}
}
 
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if (addr >= UPPER ) {
		printf("addrsss is %x\n", addr);
		fflush(stdout);
		assert(0);
	} else {
		if (SAMEPAGE(addr, (addr+len-1))) {
			hwaddr_t hwaddr = page_translate(addr);
			hwaddr_write(hwaddr, len, data);
		} else {
			hwaddr_t hwaddr = page_translate(addr);
			int len1 = PAGE_START(addr+len-1) - addr;
			int i=0;
			for (i=0;i<len1;i++) {
				hwaddr_write(hwaddr+i, 1, (data>>(i<<3)) &0xff);
			}
			hwaddr = page_translate( PAGE_START(addr+len-1));
			for (i=0;i<len-len1;i++) {
				hwaddr_write(hwaddr+i, 1, (data>>((len1+i)<<3)));
			}
		}
	}
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_write(addr, len, data);
}

static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return dram_read(addr, len);
}

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
//	hwaddr_t add = page_translate(addr);
	if (addr >= UPPER ) {
		printf("addrsss is %x\n", addr);
		fflush(stdout);
		assert(0);
	} else {
		if (SAMEPAGE(addr, (addr+len-1))) {
			hwaddr_t hwaddr = page_translate(addr);
			return hwaddr_read_instr(hwaddr, len);
		} else {
			hwaddr_t hwaddr = page_translate(addr);
			int len1 = PAGE_START(addr+len-1) - addr;
			uint32_t value =0;
			int i=0;
			for (i=0;i<len1;i++) {
				value |= (hwaddr_read_instr(hwaddr+i, 1) << ((i)<<3));
			}
			hwaddr = page_translate( PAGE_START(addr+len-1));
			for (i=0;i<len-len1;i++) {
				value |= (hwaddr_read_instr(hwaddr+i, 1) << ((len1+i)<<3));
			}
			return value;
		}
	}

//	lnaddr_t lnaddr = segment_translate(addr, len, current_sreg);
//	return hwaddr_read_instr(add, len);
}

