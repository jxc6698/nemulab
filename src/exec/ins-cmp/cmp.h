#ifndef __CMP_H_
#define __CMP_H_

/*
3C  ib          CMP AL,imm8        2        Compare immediate byte to AL
3D  iw          CMP AX,imm16       2        Compare immediate word to AX
3D  id          CMP EAX,imm32      2        Compare immediate dword to EAX
*/
make_helper(cmp_ib2al);
make_helper(cmp_iv2av);
/*
80  /7 ib       CMP r/m8,imm8      2/5      Compare immediate byte to r/m byte
81  /7 iw       CMP r/m16,imm16    2/5      Compare immediate word to r/m word
81  /7 id       CMP r/m32,imm32    2/5      Compare immediate dword to r/m dword
83  /7 ib       CMP r/m16,imm8     2/5      Compare sign extended immediate byte to r/m word
83  /7 ib       CMP r/m32,imm8     2/5      Compare sign extended immediate byte to r/m dword
*/
make_helper(cmp_ib2rmb);
make_helper(cmp_iv2rmv);
make_helper(cmp_ib2rmv);
/*
38  /r          CMP r/m8,r8        2/5      Compare byte register to r/m byte
39  /r          CMP r/m16,r16      2/5      Compare word register to r/m word
39  /r          CMP r/m32,r32      2/5      Compare dword register to r/m dword
*/
make_helper(cmp_rb2rmb);
make_helper(cmp_rv2rmv);

/*
/r          CMP r8,r/m8        2/6      Compare r/m byte to byte register
3B  /r          CMP r16,r/m16      2/6      Compare r/m word to word register
3B  /r          CMP r32,r/m32      2/6      Compare r/m dword to dword register  /r          CMP r8,r/m8        2/6      Compare r/m byte to byte register
3B  /r          CMP r16,r/m16      2/6      Compare r/m word to word register
3B  /r          CMP r32,r/m32      2/6      Compare r/m dword to dword register  /r          CMP r8,r/m8        2/6      Compare r/m byte to byte register
3B  /r          CMP r16,r/m16      2/6      Compare r/m word to word register
3B  /r          CMP r32,r/m32      2/6      Compare r/m dword to dword register
*/
make_helper(cmp_rmb2rb);
make_helper(cmp_rmv2rv);

#endif
