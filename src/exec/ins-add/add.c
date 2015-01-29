#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;



make_helper(add_al2ib)
{
	eflags_help_s val1, val2, result;
	val1.unsign8 = instr_fetch(eip+1, 1);
	val2.unsign8 = reg_b(R_AL);

	add_ch_eflags(cpu, 8, 8);
	reg_b(R_AL) = result.unsign8;

	return 2;
}

make_helper(add_ax2iw)
{
	eflags_help_s val1, val2, result;
	val1.unsign16 = instr_fetch(eip+1, 2);
	val2.unsign16 = reg_w(R_AX);

	add_ch_eflags(cpu, 16, 16);
	reg_w(R_AX) = result.unsign16;

	return 3;
}

make_helper(add_eax2il)
{
	eflags_help_s val1, val2, result;
	val1.unsign32 = instr_fetch(eip+1, 4);
	val2.unsign32 = reg_l(R_EAX);

	add_ch_eflags(cpu, 32, 32);
	reg_l(R_EAX) = result.unsign32;

	return 5;
}

make_helper(add_av2iv)
{
	return suffix=='l'?add_ax2iw(eip):add_eax2il(eip);
}
