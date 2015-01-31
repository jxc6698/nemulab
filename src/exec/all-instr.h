#include "prefix/prefix.h"
#include "cpu/modrm.h"

#include "data-mov/mov.h"
#include "ins-push/push.h"
#include "ins-test/test.h"
#include "ins-jump/jmpcon.h"
#include "ins-cmp/cmp.h"
#include "ins-xchg/xchg.h"
#include "ins-pop/pop.h"
#include "ins-leave/leave.h"

#include "ins-add/add.h"
#include "ins-add/adc.h"

#include "ins-inc/inc.h"
#include "ins-dec/dec.h"

#include "ins-sub/sub.h"
#include "ins-sub/sbb.h"

#include "ins-neg/neg.h"

#include "ins-mul/mul.h"
#include "ins-mul/imul.h"

#include "ins-div/div.h"
#include "ins-div/idiv.h"

/* for 0f 
*/
static make_helper(handle_0f)
{
	uint8_t op = instr_fetch(eip, 1);
	switch (op) {
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
		default:
			assert(0);
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
			return add_ib2rmb(eip);
		case 1:
			return 0;
		case 2:
			return adc_ib2rmb(eip);
		case 3:
			return sbb_ib2rmb(eip);
		case 4:
			return 0;
		case 5:
			return sub_ib2rmb(eip);
		case 6:
			return 0;
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
			return add_iv2rmv(eip);
		case 1:
			return 0;
		case 2:
			return adc_iv2rmv(eip);
		case 3:
			return sbb_iv2rmv(eip);
		case 4:
			return 0;
		case 5:
			return sub_iv2rmv(eip);;
		case 6:
			return 0;
		case 7:
			return cmp_rmv2ib(eip);
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
			return add_ib2rmv(eip);
		case 1:
			return 0;
		case 2:
			return adc_ib2rmv(eip);
		case 3:
			return sbb_ib2rmv(eip);;
		case 4:
			return 0;
		case 5:
			return sub_ib2rmv(eip);;
		case 6:
			return 0;
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
			return test_rmandib(eip);
		case 1:
			return 0;
		case 2:
			return 0;
		case 3:
			return neg_rmb(eip);
		case 4:
			return mul_rmb2al(eip);
		case 5:
			return 0;
		case 6:
			return div_rmb2al(eip);
		case 7:
			return 0;
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
			return test_rmandiv(eip);
		case 1:
			return 0;
		case 2:
			return 0;
		case 3:
			return neg_rmv(eip);
		case 4:
			return mul_rmv2av(eip);
		case 5:
			return 0;
		case 6:
			return div_rmv2av(eip);
		case 7:
			return 0;
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
			return inc_rv(eip);
		case 1:
			return dec_rv(eip);
		case 2:
			return 0;
		case 3:
			return 0;
		case 4:
			return 0;
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
