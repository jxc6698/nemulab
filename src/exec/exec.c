#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_rb2rmb, add_rv2rmv, add_rmb2rb, add_rmv2rv, 
/* 0x04 */	add_ib2al, add_iv2av, push_es, pop_es, 
/* 0x08 */	or_rb2rmb, or_rv2rmv, or_rmb2rb, or_rmv2rv, 
/* 0x0c */	or_ib2al, or_iv2av, push_cs, handle_0f, 
/* 0x10 */	adc_rb2rmb, adc_rv2rmv, adc_rmb2rb, adc_rmv2rv, 
/* 0x14 */	adc_ib2al, adc_iv2av, push_ss, pop_ss, 
/* 0x18 */	sbb_rb2rmb, sbb_rv2rmv, sbb_rmb2rb, sbb_rmv2rv, 
/* 0x1c */	sbb_ib2al, sbb_iv2av, push_ds, pop_ds, 
/* 0x20 */	and_rb2rmb, and_rv2rmv, and_rmb2rb, and_rmv2rv, 
/* 0x24 */	and_ib2al, and_iv2av, inv, inv,
/* 0x28 */	sub_rb2rmb, sub_rv2rmv, sub_rmb2rb, sub_rmv2rv, 
/* 0x2c */	sub_ib2al, sub_iv2av, inv, inv, 
/* 0x30 */	xor_rb2rmb, xor_rv2rmv, xor_rmb2rb, xor_rmv2rv, 
/* 0x34 */	xor_ib2al, xor_iv2av, inv, inv,
/* 0x38 */	cmp_rb2rmb, cmp_rv2rmv, cmp_rmb2rb, cmp_rmv2rv, 
/* 0x3c */	cmp_ib2al, cmp_iv2av, inv, inv, 
/* 0x40 */	inc_rv, inc_rv, inc_rv, inc_rv, 
/* 0x44 */	inc_rv, inc_rv, inc_rv, inc_rv,
/* 0x48 */	dec_rv, dec_rv, dec_rv, dec_rv, 
/* 0x4c */	dec_rv, dec_rv, dec_rv, dec_rv, 
/* 0x50 */	push_r, push_r, push_r, push_r, 
/* 0x54 */	push_r, push_r, push_r, push_r,
/* 0x58 */	pop_rv, inv, inv, inv, 
/* 0x5c */	inv, inv, inv, inv, 
/* 0x60 */	push_av, pop_av, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_iv, imul_rmviv2rv, push_ib, imul_rmvib2rv, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, jae_rel8,
/* 0x74 */	je_rel8, inv, inv, ja_rel8,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	inv, inv, inv, inv, 
/* 0x80 */	handle_80_opcode, handle_81_opcode, nemu_trap, handle_83_opcode, 
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
/* 0xc0 */	handle_c0_opcode, handle_c1_opcode, ret_neariw_v, ret_near_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave, inv, inv,
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	handle_d0_opcode, handle_d1_opcode, handle_d2_opcode, handle_d3_opcode,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_relv, jmp_relv, inv, jmp_relb,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, inv,
/* 0xf4 */	inv, inv, handle_f6_opcode, handle_f7_opcode,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, handle_fe_opcode, handle_ff_opcode
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
