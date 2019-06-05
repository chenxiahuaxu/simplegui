#ifndef _INCLUDE_SYSTEM_USART_H_
#define _INCLUDE_SYSTEM_USART_H_
#include <stdbool.h>
#include <stddef.h>
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

void	USART_Config(USART_TypeDef* USARTx, uint32_t Baudrate);
void    USART_SendByte(USART_TypeDef* pstUSARTx, uint16_t uiByte);
size_t	GetReveivedByte(uint8_t* pReadBuffer, size_t sBufferSize);
void    ResetReveivedByte(void);
bool	IsNewTarget(void);

#endif
