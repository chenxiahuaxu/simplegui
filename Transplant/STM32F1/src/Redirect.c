#include <stdio.h>
#include "Redirect.h"
#include "Usart.h"
#include "GPIO.h"

#define PRINT_USART		USART1

GPIO_OBJECT_STRUCT	astUSART1GPIO[] =
{
	{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
};

#pragma import(__use_no_semihosting)

FILE __stdout;
FILE __stdin;

void _sys_exit(int return_code)
{
	while(1)
	{
		/* Blank loop */
	}
}

int ferror(FILE *f) 
{
	/* Your implementation of ferror */
	return EOF;
}

void _ttywrch(int c) 
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(PRINT_USART, (uint8_t) c);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(PRINT_USART, USART_FLAG_TC) == RESET)
    {
		/* Blank loop */
    }
}

/*******************************************************************************
* Function Name  : int fputc(int ch, FILE *f)
* Description    : Retargets the C library printf function to the USART.printf
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int fputc(int ch, FILE *f)
{      
	while(USART_GetFlagStatus(PRINT_USART,USART_FLAG_TC)==RESET)
	{
		/* Blank loop */
	}
    USART_SendData(PRINT_USART,(uint8_t)ch);   
	return ch;
}

/*******************************************************************************
* Function Name  : int fgetc(FILE *f)
* Description    : Retargets the C library printf function to the USART.fgetc
* Input          : None
* Output         : None
* Return         : Read char
*******************************************************************************/
int fgetc(FILE *f)
{
	uint16_t uiRtnValue;
	/* Loop until received a char */
	while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET))
	{
		/* Blank loop */
	}
	uiRtnValue = USART_ReceiveData(USART1); 
	
	//USART_SendData(PRINT_USART,(uint8_t)uiRtnValue);
	
	/* Read a character from the USART and RETURN */
	return (uiRtnValue);
}

void Initialize_StdioUart(uint32_t Baudrate)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure Usart1 interrupt. */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Configure USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_Config(USART1, Baudrate);
	
	/* Configure USART1 GPIO */
	GPIO_Initialize(astUSART1GPIO, 2);
}

