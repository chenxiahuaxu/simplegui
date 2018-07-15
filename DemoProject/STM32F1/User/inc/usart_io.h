#ifndef _INCLUDE_USART_IO_H_
#define _INCLUDE_USART_IO_H_
#include <stdbool.h>
#include "stm32f10x_usart.h"
#include "GPIO.h"

/* Debug IO serial */
#define DEBUG_IO_DEVICE			USART1
#define DEBUG_IO_DEVICE_CLOCK	RCC_APB2Periph_USART1

void    USART_Config(USART_TypeDef* st_USARTx, uint32_t ui_Baudrate, bool b_Enable);
void    DebugSerialPort_Initialize(uint32_t Baudrate);
int     USART_Putc(int iChar);

#endif //_INCLUDE_USART_IO_H_
