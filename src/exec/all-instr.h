#include "prefix/prefix.h"
#include "cpu/modrm.h"

#include "data-mov/mov.h"

#include "ins-cwd/cwd.h"

#include "data-move-ins/data-move-ins.h"

#include "binary-arit-ins/binary-arit-ins.h"

#include "logical-ins/logical_ins.h"

#include "control-trans-ins/control-trans-ins.h"

#include "str-trans-ins/str-trans-ins.h"

#include "flag-control-ins/flag-control-ins.h"

#include "miscellaneous-ins/miscellaneous-ins.h"

#include "system-ins/system-ins.h"

/* for 0f 
*/
static make_helper(handle_0f)
{
	uint8_t op = instr_fetch(eip+1, 1);
	switch (op) {
		case 0x01:
			return lgdtidt(eip);
		case 0x20:
			return mov_cr2rl(eip);
		case 0x22:
			return mov_rl2cr(eip);
		case 0x40:
			return cmovo_rmv(eip);
		case 0x41:
			return cmovno_rmv(eip);
		case 0x42:
			return cmovb_rmv(eip);
		case 0x43:
			return cmovae_rmv(eip);
		case 0x44:
			return cmove_rmv(eip);
		case 0x45:
			return cmovne_rmv(eip);
		case 0x46:
			return cmovbe_rmv(eip);
		case 0x47:
			return cmova_rmv(eip);
		case 0x48:
			return cmovs_rmv(eip);
		case 0x49:
			return cmovns_rmv(eip);
		case 0x4a:
			return cmovp_rmv(eip);
		case 0x4b:
			return cmovnp_rmv(eip);
		case 0x4c:
			return cmovl_rmv(eip);
		case 0x4d:
			return cmovge_rmv(eip);
		case 0x4e:
			return cmovle_rmv(eip);
		case 0x4f:
			return cmovg_rmv(eip);
		case 0x80:
			return jo_relv(eip);
		case 0x81:
			return jno_relv(eip);
		case 0x82:
			return jb_relv(eip);
		case 0x83:
			return jae_relv(eip);
		case 0x84:
			return je_relv(eip);
		case 0x85:
			return jne_relv(eip);
		case 0x86:
			return jbe_relv(eip);
		case 0x87:
			return ja_relv(eip);
		case 0x88:
			return js_relv(eip);
		case 0x89:
			return jns_relv(eip);
		case 0x8a:
			return jp_relv(eip);
		case 0x8b:
			return jnp_relv(eip);
		case 0x8c:
			return jl_relv(eip);
		case 0x8d:
			return jge_relv(eip);
		case 0x8e:
			return jle_relv(eip);
		case 0x8f:
			return jg_relv(eip);
		case 0x90:
			return seto_rmb(eip);
		case 0x91:
			return setno_rmb(eip);
		case 0x92:
			return setb_rmb(eip);
		case 0x93:
			return setae_rmb(eip);
		case 0x94:
			return sete_rmb(eip);
		case 0x95:
			return setne_rmb(eip);
		case 0x96:
			return setbe_rmb(eip);
		case 0x97:
			return seta_rmb(eip);
		case 0x98:
			return sets_rmb(eip);
		case 0x99:
			return setns_rmb(eip);
		case 0x9a:
			return setp_rmb(eip);
		case 0x9b:
			return setnp_rmb(eip);
		case 0x9c:
			return setl_rmb(eip);
		case 0x9d:
			return setge_rmb(eip);
		case 0x9e:
			return setle_rmb(eip);
		case 0x9f:
			return setg_rmb(eip);
		case 0xa0:
			return push_fs(eip);
		case 0xa1:
			return pop_fs(eip);
		case 0xa8:
			return push_gs(eip);
		case 0xa9:
			return pop_gs(eip);
		case 0xb6:
			return movzx_rmb2rv(eip);
		case 0xb7:
			return movzx_rmw2rl(eip);
		case 0xbe:
			return movsx_rmb2rv(eip);
		case 0xbf:
			return movsx_rmw2rl(eip);
		case 0xaf:
			return imul_rmv2rv(eip);
		default:
			assert(0);
	}
	return 0;
}


/* for c0 opcode
*/
static make_helper(handle_c0_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_ib2rmb(eip);
	case 5:
		return shr_ib2rmb(eip);
	case 6:
		assert(0);
	case 7:
		return sar_ib2rmb(eip);
	}
	return 0;
}


/* for c1 opcode
*/
static make_helper(handle_c1_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_ib2rmv(eip);
	case 5:
		return shr_ib2rmv(eip);
	case 6:
		assert(0);
	case 7:
		return sar_ib2rmv(eip);
	}
	return 0;
}


/* for d0 opcode
*/
static make_helper(handle_d0_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_12rmb(eip);
	case 5:
		return shr_12rmb(eip);
	case 6:
		assert(0);
	case 7:
		return sar_12rmb(eip);
	}
	return 0;
}


/* for d1 opcode
*/
static make_helper(handle_d1_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_12rmv(eip);
	case 5:
		return shr_12rmv(eip);
	case 6:
		assert(0);
	case 7:
		return sar_12rmv(eip);
	}
	return 0;
}

/* for d2 opcode
*/
static make_helper(handle_d2_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_cl2rmb(eip);
	case 5:
		return shr_cl2rmb(eip);
	case 6:
		assert(0);
	case 7:
		return sar_cl2rmb(eip);
	}
	return 0;
}

/* for d3 opcode
*/
static make_helper(handle_d3_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
	case 0:
		assert(0);
	case 1:
		assert(0);
	case 2:
		assert(0);
	case 3:
		assert(0);
	case 4:
		return sal_cl2rmv(eip);
	case 5:
		return shr_cl2rmv(eip);;
	case 6:
		assert(0);
	case 7:
		return sar_cl2rmv(eip);
	}
	return 0;
}


/* for 80 opcode
*/
static make_helper(handle_80_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return add_rmb2ib(eip);
		case 1:
			return or_rmb2ib(eip);;
		case 2:
			return adc_rmb2ib(eip);
		case 3:
			return sbb_rmb2ib(eip);
		case 4:
			return and_rmb2ib(eip);
		case 5:
			return sub_rmb2ib(eip);
		case 6:
			return xor_rmb2ib(eip);
		case 7:
			return cmp_rmb2ib(eip);
		default:
			assert(0);
	}
	return 0;
}

/* for 81 opcode
*/
static make_helper(handle_81_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return add_rmv2iv(eip);
		case 1:
			return or_rmv2iv(eip);
		case 2:
			return adc_rmv2iv(eip);
		case 3:
			return sbb_rmv2iv(eip);
		case 4:
			return and_rmv2iv(eip);
		case 5:
			return sub_rmv2iv(eip);;
		case 6:
			return xor_rmv2iv(eip);
		case 7:
			return cmp_rmv2iv(eip);
		default:
			assert(0);
	}
	return 0;
}

/* for 83 opcode
*/
static make_helper(handle_83_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return add_rmv2ib(eip);
		case 1:
			return or_rmv2ib(eip);;
		case 2:
			return adc_rmv2ib(eip);
		case 3:
			return sbb_rmv2ib(eip);
		case 4:
			return and_rmv2ib(eip);
		case 5:
			return sub_rmv2ib(eip);
		case 6:
			return xor_rmv2ib(eip);
		case 7:
			return cmp_rmv2ib(eip);
		default:
			assert(0);
	}
	return 0;
}

/* for f6 opcode
*/
static make_helper(handle_f6_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return test_rm2ib(eip);
		case 1:
			assert(0);
			return 0;
		case 2:
			return not_rmb(eip);
		case 3:
			return neg_rmb(eip);
		case 4:
			return mul_rmb2al(eip);
		case 5:
			return imul_rmb2al(eip);
		case 6:
			return div_rmb2al(eip);
		case 7:
			return idiv_rmb2al(eip);
		default:
			assert(0);
	}
	return 0;
}

/* for f7 opcode
*/
static make_helper(handle_f7_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return test_rm2iv(eip);
		case 1:
			assert(0);
			return 0;
		case 2:
			return not_rmv(eip);;
		case 3:
			return neg_rmv(eip);
		case 4:
			return mul_rmv2av(eip);
		case 5:
			return imul_rmv2av(eip);;
		case 6:
			return div_rmv2av(eip);
		case 7:
			return idiv_rmv2av(eip);
		default:
			assert(0);
	}
	return 0;
}

/* for fe opcode
*/
static make_helper(handle_fe_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return inc_rmb(eip);
		case 1:
			return dec_rmb(eip);
		case 2:
			return 0;
		case 3:
			return 0;
		case 4:
			return 0;
		case 5:
			return 0;
		case 6:
			return 0;
		case 7:
			return 0;
		default:
			assert(0);
	}
	return 0;
}

/* for ff opcode
*/
static make_helper(handle_ff_opcode)
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	switch (m.opcode) {
		case 0:
			return inc_rmv(eip);
		case 1:
			return dec_rmv(eip);
		case 2:
			return call_rmv(eip);;
		case 3:
			return 0;
		case 4:
			return jmp_rmv(eip);
		case 5:
			return 0;
		case 6:
			return push_mv(eip);
		case 7:
			return 0;
		default:
			assert(0);
	}
	return 0;
}

#include "misc/misc.h"
