#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

#include <stdint.h>
#include <stddef.h>
#include "stm32f10x_tim.h"

void TIM3_Int_Init(TIM_TypeDef* pstTimerBase, uint16_t uiReloadValue, uint16_t uiPrescaler);

#endif /* __INCLUDE_TIMER_H__ */
