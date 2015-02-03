#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

#define ADD_SUB_NAME and

#include "exec/add_sub-template.h"

#undef ADD_SUB_NAME
