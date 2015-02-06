/**
*	jump if Condition is Met
*	made by jxc
*/
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"

extern char suffix;

#define NOTASSIGN
#define ADD_SUB_NAME cmp
#define ADD_SUB_CMD "cmp"

#include "exec/add_sub-template.h"

#undef ADD_SUB_CMD
#undef ADD_SUB_NAME
#undef NOTASSIGN
