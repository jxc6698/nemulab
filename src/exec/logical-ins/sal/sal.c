#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

#define ADD_SUB_NAME sal
#define SAL_SAR_CMD "sal"

#include "exec/sal_sar-template.h"

#undef SAL_SAR_CMD
#undef ADD_SUB_NAME
