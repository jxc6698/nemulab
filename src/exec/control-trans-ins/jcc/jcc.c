/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"

#include "exec/eflags-help.h"

make_helper(ja_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (!test_zf(cpu) && !test_zf(cpu))
		cpu.eip += offset.sign8;

	print_asm("ja 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jae_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (!test_cf(cpu))
		cpu.eip += offset.sign8;

	print_asm("jae 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(je_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (test_zf(cpu))
		cpu.eip += offset.sign8;

	print_asm("je 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jb_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (test_cf(cpu))
		cpu.eip += offset.sign8;

	print_asm("jb 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jbe_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (test_cf(cpu)|| test_zf(cpu))
		cpu.eip += offset.sign8;

	print_asm("jbe 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jc_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (test_cf(cpu))
		cpu.eip += offset.sign8;

	print_asm("jc 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jcxz_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (!reg_w(R_CX))
		cpu.eip += offset.sign8;

	print_asm("jcxz 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jecxz_rel8)
{
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (!reg_l(R_ECX))
		cpu.eip += offset.sign8;

	print_asm("jecxz 0x%x", cpu.eip+insLen);
	
	return insLen;
}

