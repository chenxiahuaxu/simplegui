#ifndef _INCLUDE_SYSTEM_GPIO_H_
#define _INCLUDE_SYSTEM_GPIO_H_
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

typedef enum
{
    GPIO_STATE_LOW,
    GPIO_STATE_HIGH,
}GPIO_STATE;

// Data type define.
typedef struct
{
	uint32_t			PortRCC;
	GPIO_TypeDef*		Port;
	uint16_t			Pin;
	GPIOMode_TypeDef	Mode;
	GPIOSpeed_TypeDef	Speed;
	GPIO_STATE          InitState;
}GPIO_OBJECT_STRUCT;

// Function declare
void		GPIO_Initialize(const GPIO_OBJECT_STRUCT* pstGPIODataList, uint16_t uiArrayListLength);
GPIO_STATE  GPIO_ReadPin(const GPIO_OBJECT_STRUCT* astPinList, uint8_t uiIndex);
void		GPIO_SetPinHigh(const GPIO_OBJECT_STRUCT* astPinList, uint8_t uiIndex);
void		GPIO_SetPinLow(const GPIO_OBJECT_STRUCT* astPinList, uint8_t uiIndex);

extern GPIO_OBJECT_STRUCT	astGPIOInitData[];

#endif
