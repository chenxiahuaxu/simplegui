/*************************************************************************/
/** Copyright.															**/
/** FileName: UserAction.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: User operation interface.								**/
/** History:															**/
/**	XuyYulin	2017/2/27	2.0.0.0		New create.						**/
/** XuYulin 2017/2/27 1.0 build this moudle								**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "VirtualDeviceInterface.h"
#include "LCD_OperationIF.h"
#include "DemoProc.h"
#include "HMI_Engine.h"
#include "SGUI_Common.h"

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	USR_ACT_OnInitialize								**/
/** Purpose:		Process with application startup.					**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnInitialize(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SimpleGUI_DemoProcess();
}

/*************************************************************************/
/** Function Name:	USR_ACT_OnKeyPress									**/
/** Purpose:		Recive and process keyboard event.					**/
/** Resources:		None.												**/
/** Params:																**/
/** @uiKeyCode:			Key code.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnKeyPress(bool bShift, bool bCtrl, bool bAlt, uint16_t uiKeyCode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_UINT16				arruiPressedKey[HMI_EVENT_KEY_VALUE_LENGTH_MAX];
	HMI_EVENT				stEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	arruiPressedKey[0] = KEY_OPTION_NONE;
	stEvent.Action = HMI_ENGINE_ACTION_KEY_PRESS;
	if(true == bShift)
	{
		arruiPressedKey[0] |= KEY_OPTION_SHIFT;
	}
	if(true == bCtrl)
	{
		arruiPressedKey[0] |= KEY_OPTION_CTRL;
	}
	if(true == bAlt)
	{
		arruiPressedKey[0] |= KEY_OPTION_ALT;
	}
	arruiPressedKey[1] = uiKeyCode;
	stEvent.Data = (void*)arruiPressedKey;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Call demo process.
	EventProcess(HMI_ENGINE_EVENT_ACTION, (void*)(&stEvent));
}

/*************************************************************************/
/** Function Name:	USR_ACT_OnTimerEventProcess							**/
/** Purpose:		Timer event process.								**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnTimerEventProcess(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_EVENT				stEvent;
	SGUI_INT				iRandomNumber;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stEvent.Action =		HMI_ENGINE_ACTION_ON_TIMER;
	stEvent.Data =			NULL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	iRandomNumber = rand();

	iRandomNumber = (iRandomNumber % 200)-100;
	stEvent.Data = (void*)(&iRandomNumber);
	// Post timer event.
	HMI_ProcessEvent(HMI_ENGINE_EVENT_ACTION, &stEvent);
}

/*************************************************************************/
/** Function Name:	USR_ACT_OnRTCUpdateEventProcess						**/
/** Purpose:		RTC timer event process.							**/
/** Resources:		None.												**/
/** Params:			None.												**/
/**@uiYear				:Year.											**/
/**@uiMonth				:Month.											**/
/**@uiDay				:Day.											**/
/**@uiHour				:Hour.											**/
/**@uiMinute			:Minute.										**/
/**@uiSecond			:Second.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void USR_ACT_OnRTCUpdateEventProcess(uint16_t uiYear, uint16_t uiMonth, uint16_t uiDay, uint16_t uiHour, uint16_t uiMinute, uint16_t uiSecond)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_TIME				stRTCTime;
	HMI_EVENT				stEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stRTCTime.Year =		uiYear;
	stRTCTime.Month =		uiMonth;
	stRTCTime.Day =			uiDay;
	stRTCTime.Hour =		uiHour;
	stRTCTime.Minute =		uiMinute;
	stRTCTime.Second =		uiSecond;
	stEvent.Action =		HMI_ENGINE_ACTION_ON_TIMER_RTC;
	stEvent.Data = 			(void*)(&stRTCTime);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Post RTC update message to a screen.
	HMI_ProcessEvent(HMI_ENGINE_EVENT_DATA, &stEvent);
}
