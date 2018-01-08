/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "Typedefine.h"
#include "usart_io.h"
#include "Initialize.h"
#include "stm32f10x_gpio.h"
#include "Systick.h"
#include "Delay.h"

#include "GPIO.h"
#include "RTC.h"
#include "ExternalInterrupt.h"
#include "SSD1306_SPI.h"

#include "SGUI_Basic.h"
#include "SGUI_Text.h"

char		szOutputBuffer[64] = {0x00};

void UpdateRTC(void);

int main(void)
{
    SGUI_RECT_AREA      stDisplayArea, stDataArea;

	HSEClocks_Initialize(RCC_PLLMul_9);
	NVIC_Initialize(NVIC_PriorityGroup_2);
	DebugPort_Initialize(DEBUG_SWD);
	DebugSerialPort_Initialize(115200);
	printf("Debug output Initialized.\r\n");

	RTC_Initialize();
	printf("RTC Initialized.\r\n");

	Systick_Initialize(72, TRUE);
	printf("Systick interrupt Initialized.\r\n");

	GPIO_Initialize(astGPIOInitData, 2);
	printf("General GPIO Initialized.\r\n");

	DelayMs(500);
	SSD1306_SPI_Initialize();
	printf("LCD controller Initialized.\r\n");

    //UpdateRTC();

    printf("System Initialize finished.\r\n");


    SGUI_Basic_DrawRectangle(0, 0, 128, 64, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);

    stDisplayArea.PosX = 5;
    stDisplayArea.PosY = 5;
    stDisplayArea.Width = 120;
    stDisplayArea.Height = 12;

    stDataArea.PosX=0;
    stDataArea.PosY=0;

	while(1)
	{
		if(g_eRTCRefreshedFlag == RTC_REFRESHED)
		{
			printf("%04u-%02u-%02u %02u:%02u:%02u.\r\n", g_stCleandar.tm_year, g_stCleandar.tm_mon, g_stCleandar.tm_mday, g_stCleandar.tm_hour, g_stCleandar.tm_min, g_stCleandar.tm_sec);
			sprintf(szOutputBuffer, "%04u-%02u-%02u %02u:%02u:%02u.", g_stCleandar.tm_year, g_stCleandar.tm_mon, g_stCleandar.tm_mday, g_stCleandar.tm_hour, g_stCleandar.tm_min, g_stCleandar.tm_sec);
			//SSD1306_SPI_6x8Str(0, 2, szOutputBuffer);
			SGUI_Text_DrawSingleLineText(szOutputBuffer, SGUI_FONT_SIZE_H12, &stDisplayArea, &stDataArea, SGUI_DRAW_NORMAL);
			SGUI_Basic_RefreshDisplay();
			g_eRTCRefreshedFlag = RTC_HOLD;
			if(GPIO_STATE_LOW == GPIO_ReadPin(astGPIOInitData, 1))
            {
                GPIO_SetPinHigh(astGPIOInitData, 1);
            }
            else
            {
                GPIO_SetPinLow(astGPIOInitData, 1);
            }
		}
	}
}

void UpdateRTC(void)
{
    RTC_CALENDAR_STRUCT stCleandarData = {};

    stCleandarData.tm_year = 2018;
	stCleandarData.tm_mon = 1;
	stCleandarData.tm_mday = 8;
	stCleandarData.tm_hour = 21;
	stCleandarData.tm_min = 52;
	stCleandarData.tm_sec = 30;

	RTC_UpdateCalendar(&stCleandarData);
}

#ifdef  USE_FULL_ASSERT
/*****************************************************************************/
/** Function Name:	assert_failed.										    **/
/** Purpose:		Reports the name of the source file and the source	    **/
/**					line number where the assert_param error has		    **/
/**					occurred.											    **/
/** Params:																    **/
/**	@szFile:			Pointer to the source file name.				    **/
/**	@uiLine:			assert_param error line source number.			    **/
/** Return:			None.												    **/
/** Notice:         Need macro definition USE_FULL_ASSERT support in	    **/
/**					stm32f10x_conf.h.									    **/
/*****************************************************************************/
void assert_failed(uint8_t* szFile, uint32_t uiLine)
{
	// Output error information to the serial port.
	printf("Wrong parameters value: file %s on line %d\r\n", szFile, uiLine);
	// Infinite loop.
	while(1);
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
