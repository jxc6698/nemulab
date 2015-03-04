#ifndef __PAGE_H__
#define __PAGE_H__

typedef struct {
	uint32_t p		:1;
	uint32_t rw		:1;
	uint32_t us		:1;
	uint32_t reserved1	:2;
	uint32_t a		:1;
	uint32_t d		:1;
	uint32_t reserved2	:2;
	uint32_t avl	:3;
	uint32_t addr	:20;
} pgd_t;

typedef pgd_t pte_t;

#define make_pgd(name1, name)  name1 = *(pgd_t *)(&name)

#define make_pte(name1, name)  name1 = *(pte_t *)(&name)

#define PAGE_OFFSET	(12)
#define PAGE_SIZE	(1<<PAGE_OFFSET)
#define PAGE_MASK	(PAGE_SIZE-1)
#define PAGE_ADDR_MASK	(~(PAGE_MASK))
#define PAGE_START(x)	((x)&PAGE_ADDR_MASK)
#define SAMEPAGE(x,y)	(PAGE_START(x) == PAGE_START(y))

#endif
