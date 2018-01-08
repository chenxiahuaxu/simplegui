#ifndef _INCLUDE_SYSTEM_SYSTICK_H_
#define _INCLUDE_SYSTEM_SYSTICK_H_
#include "stm32f10x.h"
#include "core_cm3.h"

#include "Typedefine.h"

#ifndef SYSTICK_MAXCOUNT
#define SYSTICK_MAXCOUNT  16777216
#endif

#define Systick_SetValue(T)		{SysTick->VAL = (T);}
#define Systick_SetReload(R)	{SysTick->LOAD = (R);}

#define Systick_Enable()		{SysTick->CTRL |= 0x00000001;}
#define Systick_Disable()		{Systick->CTRL &= 0xFFFFFFFE;}

#define SystickInt_Enable()		{SysTick->CTRL |= 0x00000002;}
#define SystickInt_Disable()	{Systick->CTRL &= 0xFFFFFFFD;}

#define INVAILD_TICKS(TICKS) (((TICKS) < 0) || ((TICKS) > SysTick_LOAD_RELOAD_Msk))

ErrorStatus Systick_Initialize(uint32_t ui_Ticks, bool b_EnableInterrupt);

#endif
