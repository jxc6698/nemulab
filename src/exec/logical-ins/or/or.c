#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

#define ADD_SUB_NAME or
#define ADD_SUB_CMD "or"

#include "exec/add_sub-template.h"

#undef ADD_SUB_CMD
#undef ADD_SUB_NAME
