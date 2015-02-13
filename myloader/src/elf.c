#include <elf.h>
#include <stdint.h>
#include "trap.h"


void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *phd = (void *)elf->e_phoff;
 
	int i,j;
	for(i=0;i<elf->e_phnum;i++) {
		Elf32_Phdr *ph = phd+i;
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
 
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			unsigned char *e = (void *)ph->p_vaddr, *s = (void *)ph->p_offset;
 			for (j=0;j<ph->p_filesz;j++)
				*(e+j) = *(s+j);
 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
			e = (void *)(ph->p_vaddr + ph->p_filesz);
			for (j=0;j<ph->p_memsz-ph->p_filesz;j++)
				*(e+j) = 0;
 
		} else if (ph->p_type == PT_DYNAMIC) {
			HIT_BAD_TRAP;
		}
	}
 
	/* Here we go! */
	((void(*)(void)) elf->e_entry) ();
 
	/* When returning from the program, it is executed successfully */
	HIT_GOOD_TRAP;
}



