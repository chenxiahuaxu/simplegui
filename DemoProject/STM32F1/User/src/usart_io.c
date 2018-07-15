#include "stm32f10x.h"
#include "usart_io.h"

GPIO_OBJECT_STRUCT	astDebugSerialPortGPIO[] =
{
	{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
};

/*****************************************************************************/
/** Function Name:	Initialize_DebugSerialPort							    **/
/** Purpose:		Initialize debugging usart device and GPIO.		        **/
/** Resources:		Usart1 controler, GPIOA9, GPIOA10.					    **/
/** Params:																    **/
/**	@Baudrate		Serial baud rate.    								    **/
/** Return:			None												    **/
/** Limitation:		None												    **/
/*****************************************************************************/
void DebugSerialPort_Initialize(uint32_t Baudrate)
{
	/* Configure USART1 GPIO */
	GPIO_Initialize(astDebugSerialPortGPIO, 2);

	/* Configure USART1 controller */
	RCC_APB2PeriphClockCmd(DEBUG_IO_DEVICE_CLOCK, ENABLE);	//Enable USART device clock.
	USART_Config(DEBUG_IO_DEVICE, Baudrate, false);         //Initialize USART and disable USART interrupt.
}

/*****************************************************************************/
/** Function Name:	USART_Putc							                    **/
/** Purpose:		Send a byte by usart.                     		        **/
/** Params:																    **/
/**	@iChar          Send byte.                                               **/
/** Return:			Number of written bytes.							    **/
/*****************************************************************************/
int USART_Putc(int iChar)
{
    USART_SendByte(DEBUG_IO_DEVICE, iChar);
    return iChar;
}
