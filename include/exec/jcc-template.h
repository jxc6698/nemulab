make_helper(concat(ja_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if ((!test_zf(cpu)) && (!test_cf(cpu)))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("ja 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jae_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_cf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jae 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jb_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_cf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jb 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jbe_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_cf(cpu)|| test_zf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jbe 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jc_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_cf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jc 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(je_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_zf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("je 0x%x", cpu.eip+insLen);
	
	return insLen;
}

#define jz_rel8 je_rel8

make_helper(concat(jg_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_zf(cpu)&&(get_sf(cpu)==get_of(cpu)))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jg 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jge_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (get_sf(cpu)==get_of(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jge 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jl_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (get_sf(cpu)!=get_of(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jl 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jle_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_zf(cpu)||(get_sf(cpu)!=get_of(cpu)))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jle 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jne_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_zf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jne 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jno_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_of(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jno 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jnp_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_pf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jnp 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jns_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (!test_sf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jns 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jo_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_of(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jo 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(jp_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_pf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("jp 0x%x", cpu.eip+insLen);
	
	return insLen;
}

make_helper(concat(js_rel, BITS))
{
	int insLen = OPSIZE+BYTESIZE;
	eflags_help_s offset;
	concat(offset.unsign, BITS) = instr_fetch(eip HEADAPPEND , BYTESIZE);

	if (test_sf(cpu))
		cpu.eip += concat(offset.sign, BITS);

	print_asm("js 0x%x", cpu.eip+insLen);
	
	return insLen;
}

