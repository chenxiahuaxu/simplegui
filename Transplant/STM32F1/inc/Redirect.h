#ifndef _INCLUDE_SYSTEM_IO_REDIRECT_H_
#define _INCLUDE_SYSTEM_IO_REDIRECT_H_
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "Usart.h"

struct __FILE 
{ 
	int handle; 
};

void		Initialize_StdioUart(uint32_t Baudrate);

#endif
