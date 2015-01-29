/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"

extern char suffix;

make_helper(cmp_al2ib)
{
	eflags_help_s val1, val2, result;
	val1.unsign8 = reg_b(R_AL);
	val2.unsign8 = instr_fetch(eip+1, 1);
	result.sign8 = val1.sign8 - val2.sign8;
	cmp_ch_eflags(cpu, 8, 8);

	return 2;
}

make_helper(cmp_ax2iw)
{
	eflags_help_s val1, val2, result;
	val1.unsign16 = reg_w(R_AX);
	val2.unsign16 = instr_fetch(eip+1, 2);
	result.sign16 = val1.sign16 - val2.sign16;
	cmp_ch_eflags(cpu, 16, 16);

	return 3;
}

make_helper(cmp_eax2il)
{
	eflags_help_s val1, val2, result;
	val1.unsign32 = reg_l(R_EAX);
	val2.unsign32 = instr_fetch(eip+1, 4);
	result.sign32 = val1.sign32 - val2.sign32;
	cmp_ch_eflags(cpu, 32, 32);

	return 5;
}

make_helper(cmp_av2iv)
{
	return suffix=='l'?cmp_eax2il(eip):cmp_ax2iw(eip);
}

make_helper(cmp_rmb2ib)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 7);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.R_M);
		val2.unsign8 = instr_fetch(eip+2, 1);	
		print_asm("cmpb  0x%x, 0x%x", val1.sign8, val2.sign8); 
		insLen += 2;
	} else {
		swaddr_t addr;                                                      
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign8 = swaddr_read(addr, 1);
		val2.unsign8 = instr_fetch(eip+1+insLen, 1);	
		print_asm("cmpb  0x%x,%s", val1.sign8, ModR_M_asm); 
		insLen += len+1;
	}
	
	result.sign8 = val1.sign8 - val2.sign8;
	cmp_ch_eflags(cpu, 8, 8);

	return insLen;
}

make_helper(cmp_rmw2iw)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 7);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.R_M);
		val2.unsign16 = instr_fetch(eip+2, 2);
		print_asm("cmpw  0x%x, 0x%x", val1.sign16, val2.sign16); 
		insLen += (1+2);
	} else {
		swaddr_t addr;                            
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2.unsign8 = instr_fetch(eip+1+insLen, 2);	
		print_asm("cmpw  0x%x,%s", val1.sign16, ModR_M_asm); 
		val2.sign16 = val2.sign8;
		insLen += len+2;
	}
	
	result.sign16 = val1.sign16 - val2.sign16;
	cmp_ch_eflags(cpu, 16, 16);

	return insLen;
}

make_helper(cmp_rml2il)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 7);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.R_M);
		val2.unsign32 = instr_fetch(eip+2, 4);
		print_asm("cmpw  0x%x, 0x%x", val1.sign32, val2.sign32); 
		insLen += (1+4);
	} else {
		swaddr_t addr;                                                      
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign16 = swaddr_read(addr, 4);
		val2.unsign8 = instr_fetch(eip+1+insLen, 4);	
		print_asm("cmpw  0x%x,%s", val1.sign32, ModR_M_asm); 
		insLen += len+4;
	}
	
	result.sign32 = val1.sign32 - val2.sign32;
	cmp_ch_eflags(cpu, 32, 32);

	return insLen;
}

make_helper(cmp_rmv2iv)
{
	return (suffix=='l')?cmp_rml2il(eip):cmp_rmw2iw(eip);
}

make_helper(cmp_rmw2ib)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 7);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.R_M);
		val2.unsign8 = instr_fetch(eip+2, 1);
		print_asm("cmpw  0x%x, 0x%x", val1.sign16, val2.sign8); 
		val2.sign16 = val2.sign8;
		insLen += (1+1);
	} else {
		swaddr_t addr;                                                      
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign16 = swaddr_read(addr, 2);
		val2.unsign8 = instr_fetch(eip+1+insLen, 1);	
		print_asm("cmpw  0x%x,%s", val1.sign16, ModR_M_asm); 
		val2.sign16 = val2.sign8;
		insLen += len+1;
	}
	
	result.sign16 = val1.sign16 - val2.sign16;
	cmp_ch_eflags(cpu, 16, 16);

	return insLen;
}

make_helper(cmp_rml2ib)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	assert(m.reg == 7);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.R_M);
		val2.unsign8 = instr_fetch(eip+2, 1);
		print_asm("cmpl  0x%x, 0x%x", val1.sign32, val2.sign8); 
		val2.sign32 = val2.sign8;
		insLen += 2;
	} else {
		swaddr_t addr;                                                      
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign32 = swaddr_read(addr, 4);
		val2.unsign8 = instr_fetch(eip+1+insLen, 1);	
		print_asm("cmpl  0x%x,%s", val1.sign32, ModR_M_asm); 
		val2.sign32 = val2.sign8;
		insLen += len+1;
	}
	
	result.sign32 = val1.sign32 - val2.sign32;
	cmp_ch_eflags(cpu, 32, 32);

	return insLen;
}

make_helper(cmp_rmv2ib)
{
	return (suffix=='l')?cmp_rml2ib(eip):cmp_rmw2ib(eip);
}

make_helper(cmp_rmb2rb)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign8 = reg_b(m.reg);
		val1.unsign8 = reg_b(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsb[m.reg], regsb[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;                       
		int len = read_ModR_M(eip + 1, &addr);
		val2.unsign8 = reg_w(m.reg);
		val1.unsign8 = swaddr_read(addr, 1);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsb[m.reg]); 
		insLen += len;
	}
	
	result.sign8 = val1.sign8 - val2.sign8;
	cmp_ch_eflags(cpu, 8, 8);

	return insLen;
}

make_helper(cmp_rmw2rw)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign16 = reg_w(m.reg);
		val1.unsign16 = reg_w(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsw[m.reg], regsw[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		val2.unsign16 = reg_w(m.reg);
		val1.unsign16 = swaddr_read(addr, 2);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsw[m.reg]); 
		insLen += len;
	}
	
	result.sign16 = val1.sign16 - val2.sign16;
	cmp_ch_eflags(cpu, 16, 16);

	return insLen;
}

make_helper(cmp_rml2rl)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val2.unsign32 = reg_l(m.reg);
		val1.unsign32 = reg_l(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsl[m.reg], regsl[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		val2.unsign32 = reg_w(m.reg);
		val1.unsign32 = swaddr_read(addr, 4);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsl[m.reg]); 
		insLen += len;
	}
	
	result.sign32 = val1.sign32 - val2.sign32;
	cmp_ch_eflags(cpu, 32, 32);

	return insLen;
}

make_helper(cmp_rmv2rv)
{
	return suffix=='l'?cmp_rml2rl(eip):cmp_rmw2rw(eip);
}

make_helper(cmp_rb2rmb)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign8 = reg_b(m.reg);
		val2.unsign8 = reg_b(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsb[m.reg], regsb[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;                       
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign8 = reg_w(m.reg);
		val2.unsign8 = swaddr_read(addr, 1);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsb[m.reg]); 
		insLen += len;
	}
	
	result.sign8 = val1.sign8 - val2.sign8;
	cmp_ch_eflags(cpu, 8, 8);

	return insLen;
}

make_helper(cmp_rw2rmw)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign16 = reg_w(m.reg);
		val2.unsign16 = reg_w(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsw[m.reg], regsw[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign16 = reg_w(m.reg);
		val2.unsign16 = swaddr_read(addr, 2);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsw[m.reg]); 
		insLen += len;
	}
	
	result.sign16 = val1.sign16 - val2.sign16;
	cmp_ch_eflags(cpu, 16, 16);

	return insLen;
}

make_helper(cmp_rl2rml)
{
	int insLen = 1;
	ModR_M m;
	eflags_help_s val1, val2, result;
	
	m.val = instr_fetch(eip+1, 1);
	if (m.mod == 3) {
		val1.unsign32 = reg_l(m.reg);
		val2.unsign32 = reg_l(m.R_M);
		print_asm("cmpw  %%%s, %%%s", regsl[m.reg], regsl[m.R_M]); 
		insLen += (1);
	} else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		val1.unsign32 = reg_w(m.reg);
		val2.unsign32 = swaddr_read(addr, 4);
		print_asm("cmpw  %s, %%%s", ModR_M_asm, regsl[m.reg]); 
		insLen += len;
	}
	
	result.sign32 = val1.sign32 - val2.sign32;
	cmp_ch_eflags(cpu, 32, 32);

	return insLen;
}

make_helper(cmp_rv2rmv)
{
	return suffix=='l'?cmp_rl2rml(eip):cmp_rw2rmw(eip);
}
