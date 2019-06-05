#include "stm32f10x_usart.h"
#include "Usart.h"

#define RECEIVE_BUFF_SIZE				(512)

typedef struct
{
	uint8_t				arrReceiveBuffer[RECEIVE_BUFF_SIZE];
	size_t				sWriteIndex;
}USART_REV_BUFF;

static USART_REV_BUFF	s_stReceiveBuffer;
static bool				s_bNewReceived = false;

void USART_Config(USART_TypeDef* USARTx, uint32_t Baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USARTx, USART_IT_IDLE, ENABLE);

	USART_Cmd(USARTx, ENABLE);
	USART_ClearFlag(USARTx, USART_FLAG_TXE);
	
	s_stReceiveBuffer.sWriteIndex = 0;
}

void USART_SendByte(USART_TypeDef* pstUSARTx, uint16_t uiByte)
{
    USART_ClearFlag(pstUSARTx,USART_FLAG_TC);
    // Send data.
    USART_SendData(pstUSARTx, uiByte);
    // Wait for send complete.
    //while(USART_GetFlagStatus(pstUSARTx, USART_FLAG_TXE) == RESET);
    while(USART_GetFlagStatus(pstUSARTx, USART_FLAG_TC) != SET);
}

/* USART-1 receive interrupt function. */
void USART1_IRQHandler(void)
{
	uint8_t uiReg;

	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
	{
		USART_Cmd(USART1, DISABLE);
		
		s_bNewReceived = true;
		
		uiReg = USART1->SR;
		uiReg = USART1->DR;
		(void)uiReg;
	}
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
		s_stReceiveBuffer.arrReceiveBuffer[s_stReceiveBuffer.sWriteIndex++] = USART_ReceiveData(USART1);
		
		if(s_stReceiveBuffer.sWriteIndex >= RECEIVE_BUFF_SIZE)
		{
			USART_Cmd(USART1, DISABLE);
			s_bNewReceived = true;
		}
    }
	
}

size_t GetReveivedByte(uint8_t* pReadBuffer, size_t sBufferSize)
{
	size_t		sCopySize;
	size_t		sCopyIndex;
	
	sCopySize = (sBufferSize>s_stReceiveBuffer.sWriteIndex)?s_stReceiveBuffer.sWriteIndex:sBufferSize;
	
	for(sCopyIndex=0; sCopyIndex<sCopySize; sCopyIndex++)
	{
		*(pReadBuffer+sCopyIndex) = s_stReceiveBuffer.arrReceiveBuffer[sCopyIndex];
	}
	
    return sCopySize;
}

bool IsNewTarget(void)
{
	return s_bNewReceived;
}

void ResetReveivedByte(void)
{
    s_stReceiveBuffer.sWriteIndex = 0;
	s_bNewReceived = false;
	USART_Cmd(USART1, ENABLE);
}
