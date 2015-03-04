#include "common.h"
#include "memory.h"
#include <string.h>

#include <elf.h>

#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();
void setusepde(uint32_t addr, uint32_t len);

uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif

	/* Load each program segment */
#ifdef HAS_DEVICE
	Elf32_Phdr *phd = (void *)(elf->e_phoff+buf);;
#else
	Elf32_Phdr *phd = (void *)elf->e_phoff;
#endif

 
	int i,j;
	for(i=0;i<elf->e_phnum;i++) {
		ph = phd+i;
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
 
			mm_malloc(ph->p_vaddr, ph->p_memsz);
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
#ifdef HAS_DEVICE
			unsigned char *e = (void *)ph->p_vaddr;
			unsigned char s[4096];
 			for (j=0;j<ph->p_filesz;j+=4096) {
				int tlen;
				if (ph->p_filesz-j>=4096)
					tlen = 4096;
				else 
					tlen = ph->p_filesz-j;
				ide_read(s, ELF_OFFSET_IN_DISK+ph->p_offset+j, tlen);
//				*(e+j) = s;
				memcpy(e+j, s, tlen);
			}
#else
			unsigned char *e = (void *)ph->p_vaddr, *s = (void *)ph->p_offset;
 			for (j=0;j<ph->p_filesz;j++)
				*(e+j) = *(s+j);
#endif
 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
			e = (void *)(ph->p_vaddr + ph->p_filesz);
			for (j=0;j<ph->p_memsz-ph->p_filesz;j++)
				*(e+j) = 0;

 
			/* Record the prgram break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }

		} else if (ph->p_type == PT_DYNAMIC) {
			HIT_BAD_TRAP;
		}
	}

	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
