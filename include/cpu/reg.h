#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"



typedef union {
	struct {
		uint16_t rpl	:2;
		uint16_t ti		:1;
		uint16_t index	:13;
	};
	uint16_t val;
} segment;

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */

typedef struct {
    union {
        struct {
            union {
                uint32_t _32;
                uint16_t _16;
                uint8_t _8[2];
            };
        } gpr[8];

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */
        struct {
            uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
        };
    };
	union {
		struct {
			segment es, cs, ss, ds, fs, gs;
		};
		uint16_t sg[6];
	};
	/* cs, ss ,ds , es, fs, gs base addr
	 * should be 8 byte of segment selector value
	 * now is base addr
	 */
	swaddr_t csValue, ssValue, dsValue, esValue, fsValue, gsValue;

	union {
		struct {
			uint8_t Cf		:1;
			uint8_t unused1 :1;
			uint8_t Pf		:1;
			uint8_t unused2	:1;
			uint8_t Af		:1;
			uint8_t unused3	:1;
			uint8_t Zf		:1;
			uint8_t Sf		:1;
			uint8_t Tf		:1;
			uint8_t If		:1;
			uint8_t Df		:1;
			uint8_t Of		:1;
			uint8_t Iopl	:2;
			uint8_t NT		:1;
			uint8_t unused4	:1;
			uint8_t Rf		:1;
			uint8_t Vm		:1;
			uint32_t unused5:13;
		};
		uint32_t val;
		uint16_t flags;
	} eflags;

	swaddr_t eip;

	/*   */
	swaddr_t breakpointAddr;

	union {
		struct {
			uint32_t base	:32;
			uint32_t limit	:16;
		};
	} gdt;
	
	union {
		uint32_t val;
	} cr0;

} CPU_state;

extern CPU_state cpu;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };
enum { R_ES, R_CS, R_SS, R_DS, R_FS, R_GS };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];
extern const char* regss[];

#define set_eflags(cpu, value) (cpu.eflags.val = value);
#define set_flags(cpu, value) (cpu.eflags.flags = value)

#define get_eflags(cpu) (cpu.eflags.val)
#define get_flags(cpu) (cpu.eflags.flags)

#define test_cf(cpu) (cpu.eflags.Cf)
#define test_pf(cpu) (cpu.eflags.Pf)
#define test_zf(cpu) (cpu.eflags.Zf)
#define test_sf(cpu) (cpu.eflags.Sf)
#define test_if(cpu) (cpu.eflags.If)
#define test_df(cpu) (cpu.eflags.Df)
#define test_of(cpu) (cpu.eflags.Of)

/* no used in current NEMU*/
#define test_af(cpu) (cpu.eflags.Af)

#define set_cf(cpu) (cpu.eflags.Cf = 1)
#define set_pf(cpu) (cpu.eflags.Pf = 1)
#define set_zf(cpu) (cpu.eflags.Zf = 1)
#define set_sf(cpu) (cpu.eflags.Sf = 1)
#define set_if(cpu) (cpu.eflags.If = 1)
#define set_df(cpu) (cpu.eflags.Df = 1)
#define set_of(cpu) (cpu.eflags.Of = 1)

/* no used in current NEMU*/
#define set_af(cpu) (cpu.eflags.Af = 1)

#define clear_cf(cpu) (cpu.eflags.Cf = 0)
#define clear_pf(cpu) (cpu.eflags.Pf = 0)
#define clear_zf(cpu) (cpu.eflags.Zf = 0)
#define clear_sf(cpu) (cpu.eflags.Sf = 0)
#define clear_if(cpu) (cpu.eflags.If = 0)
#define clear_df(cpu) (cpu.eflags.Df = 0)
#define clear_of(cpu) (cpu.eflags.Of = 0)

/* no used in current NEMU*/
#define clear_af(cpu) (cpu.eflags.Af = 0)

#define get_cf(cpu) (cpu.eflags.Cf)
#define get_pf(cpu) (cpu.eflags.Pf)
#define get_zf(cpu) (cpu.eflags.Zf)
#define get_sf(cpu) (cpu.eflags.Sf)
#define get_if(cpu) (cpu.eflags.If)
#define get_df(cpu) (cpu.eflags.Df)
#define get_of(cpu) (cpu.eflags.Of)

/* no used in current NEMU*/
#define get_af(cpu) (cpu.eflags.Af)


#endif
