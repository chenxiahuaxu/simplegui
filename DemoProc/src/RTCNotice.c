/*************************************************************************/
/** Copyright.															**/
/** FileName: RTCNotice.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for notice box interface and refresh screen.	**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "HMI_Engine.h"
#include "SGUI_Notice.h"
#include "SGUI_Common.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_RTC_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char				s_szRTCNoticeText[NOTICE_RTC_BUFFER_SIZE+1] = {0x00};
HMI_SCREEN_ACTION		s_stDemoRTCNoticeActions =		{	NULL,
															HMI_DemoRTCNotice_Prepare,
															HMI_DemoRTCNotice_RefreshScreen,
															HMI_DemoRTCNotice_ProcessEvent,
															HMI_DemoRTCNotice_PostProcess
														};
//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_RTCNotice =			{	HMI_SCREEN_ID_DEMO_RTC_NOTICE,
															&s_stDemoRTCNoticeActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoRTCNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	RTCTimerEnable(true);
	SGUI_SystemIF_MemorySet(s_szRTCNoticeText, 0x00, sizeof(SGUI_CHAR)*(NOTICE_RTC_BUFFER_SIZE+1));
	HMI_DemoRTCNotice_RefreshScreen(pstIFObj, NULL);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_TIME				stRTCTime;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_SystemIF_GetNowTime(&stRTCTime);
	sprintf(s_szRTCNoticeText, DEMO_RTC_NOTICE_TEXT_FMT,
				stRTCTime.Year, stRTCTime.Month, stRTCTime.Day,
				stRTCTime.Hour, stRTCTime.Minute, stRTCTime.Second);
	SGUI_Notice_Repaint(pstIFObj, s_szRTCNoticeText, SGUI_FONT_SIZE_H12, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_TIME					stRTCTime;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*			pstKeyEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstEvent)
	{
		if(EVENT_TYPE_ACTION == pstEvent->iType)
		{
			if(EVENT_ID_KEY_PRESS == pstEvent->iID)
			{
				pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
				uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);
				switch(uiKeyValue)
				{
					case KEY_VALUE_ENTER:
					case KEY_VALUE_ESC:
					{
						iProcessAction = HMI_DEMO_PROC_CANCEL;
						break;
					}
				}
			}
		}
		else if(EVENT_TYPE_DATA == pstEvent->iType)
		{
			if(EVENT_ID_RTC == pstEvent->iID)
			{
				SGUI_SystemIF_GetNowTime(&stRTCTime);
				sprintf(s_szRTCNoticeText, DEMO_RTC_NOTICE_TEXT_FMT,
					stRTCTime.Year, stRTCTime.Month, stRTCTime.Day,
					stRTCTime.Hour, stRTCTime.Minute, stRTCTime.Second);
				SGUI_Notice_Repaint(pstIFObj, s_szRTCNoticeText, SGUI_FONT_SIZE_H12, 0, SGUI_ICON_INFORMATION);
			}
		}
	}
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			RTCTimerEnable(false);
			HMI_GoBack(NULL);
		}
	}

	return HMI_RET_NORMAL;
}

