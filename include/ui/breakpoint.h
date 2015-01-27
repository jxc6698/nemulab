#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO;
	struct breakpoint *next;

	/* TODO: Add more members if necessary */
    uint32_t addr;
    uint8_t ins_f_bit;
    /* func name */
    char func[32];

} BP;

void add_bp(uint32_t index);
void del_bp(uint32_t index);



#endif
