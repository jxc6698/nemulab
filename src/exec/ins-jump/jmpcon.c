/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"


make_helper(ja_rel8)
{
	int insLen = 2;
	uint8_t offset = instr_fetch(eip+1, 1);

	if (!test_zf(cpu) && !test_zf(cpu))
		cpu.eip += offset;

	print_asm("ja 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(jae_rel8)
{
	int insLen = 2;
	uint8_t offset = instr_fetch(eip+1, 1);

	if (!test_cf(cpu))
		cpu.eip += offset;

	print_asm("jae 0x%x", cpu.eip+insLen);
	
	return insLen;
}


make_helper(je_rel8)
{
	int insLen = 2;
	uint8_t offset = instr_fetch(eip+1, 1);

	if (test_zf(cpu))
		cpu.eip += offset;

	print_asm("je 0x%x", cpu.eip+insLen);
	
	return insLen;
}
