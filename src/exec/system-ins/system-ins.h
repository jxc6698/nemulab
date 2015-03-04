#ifndef __SYSTEM_INS_H__
#define __SYSTEM_INS_H__

make_helper(lgdtidt);
make_helper(cli);
make_helper(sti);

make_helper(hlt);

make_helper(intc);
make_helper(iret);

make_helper(in_ib);
make_helper(in_iv);
make_helper(in_dxb);
make_helper(in_dxv);

make_helper(out_ib);
make_helper(out_iv);
make_helper(out_dxb);
make_helper(out_dxv);



#endif
