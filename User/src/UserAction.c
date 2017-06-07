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
#include "UserAction.h"
#include "LCD_OperationIF.h"


#include "HMI_Data.h"
#include "HMI_Process.h"

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
	HMI_Action_Initialize();
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
	uint16_t				uiOptionKeyFlags;
	USER_ACT_KEYPRESS		stUserKeyEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiOptionKeyFlags = KEY_OPTION_NONE;
	if(true == bShift)
	{
		uiOptionKeyFlags |= KEY_OPTION_SHIFT;
	}
	if(true == bCtrl)
	{
		uiOptionKeyFlags |= KEY_OPTION_CTRL;
	}
	if(true == bAlt)
	{
		uiOptionKeyFlags |= KEY_OPTION_ALT;
	}
	stUserKeyEvent.Options = uiOptionKeyFlags;
	stUserKeyEvent.KeyValue[0] = uiKeyCode;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	HMI_Action_ExternalEventProcess(HMI_SCREEN_ID_ANY, &stUserKeyEvent);
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
	/* Process							*/
	/*----------------------------------*/
	// Post timer event.
	HMI_Action_InternalEventProcess(0, NULL);
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
	HMI_RTC_TIME		stRTCTime;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stRTCTime.Year = uiYear;
	stRTCTime.Month = uiMonth;
	stRTCTime.Day = uiDay;
	stRTCTime.Hour = uiHour;
	stRTCTime.Minute = uiMinute;
	stRTCTime.Second = uiSecond;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Post RTC update message to a screen.
	HMI_Action_InternalEventProcess(2, &stRTCTime);
}
