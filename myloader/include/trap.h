#ifndef __TRAP_H__
#define __TRAP_H__

#define concat(x,y) x ## y

#ifndef __ASSEMBLER__

#define HIT_GOOD_TRAP  		\
	asm volatile(".byte 0x82" : : "a"(0))

#define HIT_BAD_TRAP		\
	asm volatile(".byte 0x82" : : "a"(1))

#define nemu_assert(condition) 		\
	do {							\
		if (!(condition)) HIT_BAD_TRAP;	\
	} while(0)						

#else

#define HIT_GOOD_TRAP	\
	movl $0x0, %eax;		\
	.byte 0x82

#define HIT_BAD_TRAP	\
	movl $0x1, %eax		\
	.byte 0x82

#define nemu_assert(reg, val)	\
	cmp $val, %reg				\
	je concat(lable, __LINE__); \
	HIT_BAD_TRAP;				\
	concat(lable, __LINE__):

#endif

/* __TRAP_H__ */
#endif
