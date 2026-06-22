#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

void Key_Init(void);

uint8_t Key_Feed(void);
uint8_t Key_Play(void);
uint8_t Key_Medical(void);

#endif
