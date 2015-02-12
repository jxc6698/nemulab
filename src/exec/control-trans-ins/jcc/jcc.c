/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"

#include "exec/eflags-help.h"

extern char suffix;


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
	/* assume do not need jcxz_rel8, because I do 
	not know difference between jecxz_rel8 and 
	jcxz_rel8 */
	assert(suffix=='l');
	int insLen = 2;
	eflags_help_s offset;
	offset.unsign8 = instr_fetch(eip+1, 1);

	if (!reg_l(R_ECX))
		cpu.eip += offset.sign8;

	print_asm("jecxz 0x%x", cpu.eip+insLen);
	
	return insLen;
}

#define BITS 8
#define BYTESIZE 1
#define HEADAPPEND +1
#define OPSIZE 1

#include "exec/jcc-template.h"

#undef OPSIZE
#undef HEADAPPEND
#undef BYTESIZE
#undef BITS


#define BITS 16
#define BYTESIZE 2
#define HEADAPPEND +2
#define OPSIZE 2

#include "exec/jcc-template.h"

#undef OPSIZE
#undef HEADAPPEND
#undef BYTESIZE
#undef BITS


#define BITS 32
#define BYTESIZE 4
#define HEADAPPEND +2
#define OPSIZE 2

#include "exec/jcc-template.h"

#undef OPSIZE
#undef HEADAPPEND
#undef BYTESIZE
#undef BITS


make_helper(ja_relv)
{
	return suffix=='l'?ja_rel32(eip):ja_rel16(eip);
}
make_helper(jae_relv)
{
	return suffix=='l'?jae_rel32(eip):jae_rel16(eip);
}
make_helper(jb_relv)
{
	return suffix=='l'?jb_rel32(eip):jb_rel16(eip);
}
make_helper(jbe_relv)
{
	return suffix=='l'?jbe_rel32(eip):jbe_rel16(eip);
}
make_helper(jc_relv)
{
	return suffix=='l'?jc_rel32(eip):jc_rel16(eip);
}
make_helper(je_relv)
{
	return suffix=='l'?je_rel32(eip):je_rel16(eip);
}
make_helper(jg_relv)
{
	return suffix=='l'?jg_rel32(eip):jg_rel16(eip);
}
make_helper(jge_relv)
{
	return suffix=='l'?jge_rel32(eip):jge_rel16(eip);
}
make_helper(jl_relv)
{
	return suffix=='l'?jl_rel32(eip):jl_rel16(eip);
}
make_helper(jle_relv)
{
	return suffix=='l'?jle_rel32(eip):jle_rel16(eip);
}
make_helper(jne_relv)
{
	return suffix=='l'?jne_rel32(eip):jne_rel16(eip);
}
make_helper(jno_relv)
{
	return suffix=='l'?jno_rel32(eip):jno_rel16(eip);
}
make_helper(jnp_relv)
{
	return suffix=='l'?jnp_rel32(eip):jnp_rel16(eip);
}
make_helper(jns_relv)
{
	return suffix=='l'?jns_rel32(eip):jns_rel16(eip);
}
make_helper(jo_relv)
{
	return suffix=='l'?jo_rel32(eip):jo_rel16(eip);
}
make_helper(jp_relv)
{
	return suffix=='l'?jp_rel32(eip):jp_rel16(eip);
}
make_helper(js_relv)
{
	return suffix=='l'?js_rel32(eip):js_rel16(eip);
}

