#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	inv, inv, inv, inv, 
/* 0x04 */	add_al2ib, add_av2iv, push_es, pop_es, 
/* 0x08 */	inv, inv, inv, inv, 
/* 0x0c */	inv, inv, push_cs, handle_0f, 
/* 0x10 */	inv, inv, inv, inv, 
/* 0x14 */	inv, inv, inv, pop_ss, 
/* 0x18 */	inv, push_ss, inv, inv, 
/* 0x1c */	inv, inv, push_ds, pop_ds, 
/* 0x20 */	inv, inv, inv, inv, 
/* 0x24 */	inv, inv, inv, inv,
/* 0x28 */	inv, inv, inv, inv, 
/* 0x2c */	inv, inv, inv, inv, 
/* 0x30 */	inv, inv, inv, inv, 
/* 0x34 */	inv, inv, inv, inv,
/* 0x38 */	cmp_rmb2rb, cmp_rmv2rv, cmp_rb2rmb, cmp_rv2rmv, 
/* 0x3c */	cmp_al2ib, cmp_av2iv, inv, inv, 
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	inv, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	push_r, push_r, push_r, push_r, 
/* 0x54 */	push_r, push_r, push_r, push_r,
/* 0x58 */	pop_rv, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	push_av, pop_av, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	inv, inv, push_ib, push_iv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, jae_rel8,
/* 0x74 */	je_rel8, inv, inv, ja_rel8,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, inv, inv, 
/* 0x80 */	cmp_rmb2ib, cmp_rmv2iv, nemu_trap, cmp_rmv2ib, 
/* 0x84 */	test_rmandrb, test_rmandrv, xchg_rmb2rb, xchg_rmv2rv, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, inv, inv, pop_mv, 
/* 0x90 */	xchg_av2rv, inv, inv, inv,
/* 0x94 */	inv, inv, inv, inv,
/* 0x98 */	inv, inv, inv, inv, 
/* 0x9c */	push_fv, pop_fv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	inv, inv, inv, inv,
/* 0xa8 */	test_ib, test_iv, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	inv, inv, inv, inv,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	inv, inv, inv, inv,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, test_rmandib, test_rmandiv,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, inv, push_mv
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
