#ifndef _INCLUDE_SYSTEM_USART_H_
#define _INCLUDE_SYSTEM_USART_H_
#include "stm32f10x_usart.h"
#include "Typedefine.h"

void USART_Config(USART_TypeDef* st_USARTx, uint32_t ui_Baudrate, bool b_Enable);
void USART_SendByte(USART_TypeDef* pstUSARTx, uint16_t uiByte);

#endif
