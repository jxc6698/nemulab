#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "ins-push/push.h"
#include "ins-test/test.h"
#include "ins-jump/jmpcon.h"
#include "ins-cmp/cmp.h"
#include "ins-xchg/xchg.h"
#include "ins-pop/pop.h"
#include "ins-leave/leave.h"

#include "ins-add/add.h"



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


#include "misc/misc.h"
