#ifndef __JMPCON_H__
#define __JMPCON_H__

make_helper(ja_rel8);
make_helper(jae_rel8);

make_helper(jb_rel8);
make_helper(jbe_rel8);

#define jc_rel8 jb_rel8
make_helper(jcxz_rel8);
make_helper(jecxz_rel8);

make_helper(je_rel8);
#define jz_rel8 je_rel8
make_helper(jg_rel8);
make_helper(jge_rel8);
make_helper(jl_rel8);
make_helper(jle_rel8);

#define jna_rel8 jbe_rel8
#define jnae_rel8 jb_rel8
#define jnb_rel8 jae_rel8
#define jnbe_rel8 ja_rel8
#define jnc_rel8 jae_rel8
make_helper(jne_rel8);

#define jng_rel8 jle_rel8
#define jnge_rel8 jl_rel8
#define jnl_rel8 jge_rel8
#define jnle_rel8 jg_rel8
make_helper(jno_rel8);
make_helper(jnp_rel8);
make_helper(jns_rel8);
#define jnz_rel8 jne_rel8
make_helper(jo_rel8);

make_helper(jp_rel8);
#define jpe_rel8 jp_rel8
#define jpo_rel8 jnp_rel8
make_helper(js_rel8);
#define jz_rel8 je_rel8

/* jcc rel16/rel32 */
make_helper(ja_relv);
make_helper(jae_relv);

make_helper(jb_relv);
make_helper(jbe_relv);

#define jc_relv jb_relv

make_helper(je_relv);
#define jz_relv je_relv
make_helper(jg_relv);
make_helper(jge_relv);
make_helper(jl_relv);
make_helper(jle_relv);

#define jna_relv jbe_relv
#define jnae_relv jb_relv
#define jnb_relv jae_relv
#define jnbe_relv ja_relv
#define jnc_relv jae_relv
make_helper(jne_relv);

#define jng_relv jle_relv
#define jnge_relv jl_relv
#define jnl_relv jge_relv
#define jnle_relv jg_relv
make_helper(jno_relv);
make_helper(jnp_relv);
make_helper(jns_relv);
#define jnz_relv jne_relv
make_helper(jo_relv);

make_helper(jp_relv);
#define jpe_relv jp_relv
#define jpo_relv jnp_relv
make_helper(js_relv);
#define jz_relv je_relv



#endif
