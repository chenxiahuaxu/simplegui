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
#include "Redirect.h"
#include "OLED.h"
#include "Timer.h"
#include "GPIO.h"
#include "RTC.h"
#include "DemoProc.h"

void InitSysForSGUIDemo(void);
void InitializeRTC(void);

int main(void)
{
	InitSysForSGUIDemo();
	puts("System initialized.\r\n");
	InitializeRTC();
	
	OLED_Initialize();
	
	(void)DemoMainProcess();
}

void InitSysForSGUIDemo(void)
{
	//Config usart1 for input/output.
	Initialize_StdioUart(115200);
	
	//Initialize Timer3 for Simple-GUI Demo Heartbeat-Timer.
	//TIMBase_Int_Init(TIM3, 4999, 7199);
	TIMBase_Int_Init(TIM3, 499, 7199);
	
	//Initialize RTC and interrupt.
	RTC_Initialize();
}

void InitializeRTC(void)
{
	RTC_CALENDAR_STRUCT			stTime;
	
	stTime.tm_year = 2019;
	stTime.tm_mon = 5;
	stTime.tm_mday = 4;
	stTime.tm_hour = 12;
	stTime.tm_min = 37;
	stTime.tm_sec = 30;
	
	RTC_UpdateCalendar(&stTime);
}

