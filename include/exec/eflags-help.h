#ifndef __EFLAGS_HELP_H__
#define __EFLAGS_HELP_H__
/*
* see doc in doc/exec/eflags.txt
*/

#include "common.h"
#include "nemu.h"

/* helper structure for eflags cal */
typedef union{
	uint32_t unsign32;
	int32_t sign32;
	uint16_t unsign16;
	int16_t sign16;
	uint8_t unsign8;
	int8_t sign8;
} eflags_help_s;
/*	use cmp_help_s val1, val2:
*	val1: left operand. val2: right operand
*/

extern uint8_t pf_flag[];

/* affect of, sf, zf, af, pf, cf */
#define sub_ch_eflags(cpu, BITS, offset)						\
	result.sign##BITS = val1.sign##BITS - val2.sign##BITS;				\
	(val1.unsign##BITS<val2.unsign##BITS)? set_cf(cpu): clear_pf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((val1.unsign##BITS&0x0f)<(val2.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);																\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((val2.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);

/* affect of, sf, zf, af, pf, cf */
#define cmp_ch_eflags(cpu, BITS, offset) sub_ch_eflags(cpu, BITS, offset)

/* affect of, sf, zf, af, pf, cf */
#define add_ch_eflags(cpu, BITS, offset)						\
	result.sign##BITS = val1.sign##BITS + val2.sign##BITS;				\
	(result.unsign##BITS<val1.unsign##BITS)? set_cf(cpu): clear_pf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((result.unsign##BITS&0x0f)<(val1.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);																\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((result.sign##BITS^val2.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);


#define test_ch_eflags(val,cpu,offset) do {				\
		clear_cf(cpu);									\
		clear_of(cpu);									\
		pf_flag[val&0xff]?set_pf(cpu):clear_pf(cpu);	\
		(!val)?set_zf(cpu):clear_zf(cpu);				\
		(val&(1<<(offset-1)))?set_sf(cpu):clear_sf(cpu);\
	} while(0)



#endif
