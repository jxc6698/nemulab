#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "common.h"

void raise_intr(uint8_t NO);
void set_interrupt(int num);

#endif
