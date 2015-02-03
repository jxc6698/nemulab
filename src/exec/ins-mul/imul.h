#ifndef __IMUL_H__
#define __IMUL_H__


make_helper(imul_rmb2al);
make_helper(imul_rmv2av);

make_helper(imul_rmv2rv);

/* thest two are the same */
make_helper(imul_rmvib2rv);
make_helper(imul_ib2rv);

/* thest two are the same */
make_helper(imul_rmviv2rv);
make_helper(imul_iv2rv);

#endif
