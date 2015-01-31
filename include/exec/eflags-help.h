#ifndef __EFLAGS_HELP_H__
#define __EFLAGS_HELP_H__
/*
* see doc in doc/exec/eflags.txt
*/

#include "common.h"
#include "nemu.h"

/* helper structure for eflags cal */
typedef union{
	uint64_t unsign64;
	int64_t sign64;
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
#define sub_ch_eflags(cpu, BITS, offset)	do {					\
	result.sign##BITS = val1.sign##BITS - val2.sign##BITS;			\
	(val1.unsign##BITS<val2.unsign##BITS)? set_cf(cpu): clear_cf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((val1.unsign##BITS&0x0f)<(val2.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);																\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((val2.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);		\
	} while(0)

/* affect of, sf, zf, af, pf, cf */
#define cmp_ch_eflags(cpu, BITS, offset) sub_ch_eflags(cpu, BITS, offset)

/* affect of, sf, zf, af, pf, cf */
#define add_ch_eflags(cpu, BITS, offset)	do {					\
	result.sign##BITS = val1.sign##BITS + val2.sign##BITS;				\
	(result.unsign##BITS<val1.unsign##BITS)? set_cf(cpu): clear_cf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((result.unsign##BITS&0x0f)<(val1.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);																\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((result.sign##BITS^val2.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);		\
	} while(0)

#define adc_ch_eflags(cpu, BITS, offset)	do {						\
	result.sign##BITS = val1.sign##BITS +val2.sign##BITS +!!test_cf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((result.unsign##BITS&0x0f)<(val1.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);															\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((result.sign##BITS^val2.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);	\
	if (test_cf(cpu)&&val1.unsign##BITS+1==0) set_cf(cpu);			\
	else if (result.unsign##BITS<val2.unsign##BITS) set_cf(cpu);	\
	else clear_cf(cpu);												\
	} while(0)


#define sbb_ch_eflags(cpu, BITS, offset)	do {					\
	uint8_t ef_tmp = test_cf(cpu);									\
	result.sign##BITS = val1.sign##BITS - val2.sign##BITS - ef_tmp;	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((val1.unsign##BITS&0x0f)<(val2.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);																\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((val2.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);		\
	if (ef_tmp && val2.unsign##BITS+1==0) set_cf(cpu);				\
	else if (val1.unsign##BITS<val2.unsign##BITS+ef_tmp) set_cf(cpu);	\
	else clear_cf(cpu);												\
	} while(0)

#define inc_ch_eflags(cpu, BITS, offset)	do {					\
	result.sign##BITS = val1.sign##BITS + 1;						\
	(result.unsign##BITS<val1.unsign##BITS)? set_cf(cpu): clear_cf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((result.unsign##BITS&0x0f)<(val1.unsign##BITS&0x0f))? set_af(cpu):clear_af(cpu);															\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((result.sign##BITS^1)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);		\
	} while(0);

#define dec_ch_eflags(cpu, BITS, offset)	do {					\
	result.sign##BITS = val1.sign##BITS - 1;						\
	(val1.unsign##BITS<1)? set_cf(cpu): clear_cf(cpu);	\
	(pf_flag[result.unsign##BITS])? set_pf(cpu):clear_pf(cpu);		\
	((val1.unsign##BITS&0x0f)<1)? set_af(cpu):clear_af(cpu);		\
	(!result.unsign##BITS)? set_zf(cpu): clear_zf(cpu);				\
	(result.sign##BITS&1<<(offset-1))? set_sf(cpu): clear_sf(cpu);	\
	((result.sign##BITS^val1.sign##BITS)&(1<<(offset-1)))&&((val1.sign##BITS^1)&(1<<(offset-1)))? set_of(cpu): clear_of(cpu);		\
	} while(0)


#define test_ch_eflags(val,cpu,offset) do {				\
		clear_cf(cpu);									\
		clear_of(cpu);									\
		pf_flag[val&0xff]?set_pf(cpu):clear_pf(cpu);	\
		(!val)?set_zf(cpu):clear_zf(cpu);				\
		(val&(1<<(offset-1)))?set_sf(cpu):clear_sf(cpu);\
	} while(0)


#define neg_ch_eflags(cpu, val, offset)  do {				\
	val = -val;												\
	(val)?set_cf(cpu):clear_cf(cpu);						\
	(pf_flag[val&0x00ff])? set_pf(cpu):clear_pf(cpu);		\
	(!val)? set_zf(cpu): clear_zf(cpu);						\
	(val==(0x1<<(offset-1)))? set_of(cpu): clear_of(cpu);	\
	} while(0)

/*  in mul imul div idiv 
	BITS = 2 * offset 
	*/

/* val1.unsign##BITS : val2.unsign##BITS  */
/* affect of/cf, other not defined */
#define mul_ch_eflags(cpu, BITS, offset)   do {		\
		val1.unsign##BITS = val1.unsign##BITS * val2.unsign##BITS;	\
		val2.unsign##BITS = val1.unsign##BITS & 0xffffffff;					\
		val1.unsign##BITS >>= offset;								\
		(val1.unsign##BITS)?set_cf(cpu)&&set_of(cpu):clear_cf(cpu)&&clear_cf(cpu);			\
	} while(0)

/* val1.unsign##BITS : val2.unsign##BITS  */
/* affect of/cf, other not defined */
#define imul_ch_eflags(cpu, BITS, offset)   do {		\
		val1.sign##BITS = val1.sign##BITS * val2.sign##BITS;	\
		val2.sign##BITS = val1.sign##offset;		\
		val1.unsign##BITS >>= offset;								\
		(val1.sign##BITS!=val2.sign##BITS)?set_cf(cpu)&&set_of(cpu):clear_cf(cpu)&&clear_cf(cpu);			\
	} while(0)

/* gcc compiler use __udivdi3  */	
/* of sf zf ar pf cf not defined */
#define div_ch_eflags(cpu, BITS, offset)   do {		\
		result.unsign##BITS = val1.unsign##BITS / val2.unsign##offset;	\
		val1.unsign##BITS = val1.unsign##BITS % val2.unsign##BITS;	\
	} while(0)

#define idiv_ch_eflags(cpu, BITS, offset)   do {		\
		result.sign##BITS = val1.sign##BITS / val2.sign##offset;		\
		val1.unsign##BITS = val1.unsign##BITS % val2.unsign##BITS;	\
	} while(0)



#endif
