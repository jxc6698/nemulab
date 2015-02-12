#include "cpu/reg.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

#include "exec/eflags-help.h"

extern char suffix;

#define ADD_SUB_NAME sar
#define SAL_SAR_CMD "sar"

#include "exec/sal_sar-template.h"

#undef SAL_SAR_CMD
#undef ADD_SUB_NAME
