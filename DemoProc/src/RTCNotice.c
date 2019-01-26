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
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent);
static HMI_ENGINE_RESULT	HMI_DemoRTCNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char				s_szRTCNoticeText[NOTICE_RTC_BUFFER_SIZE+1] = {0x00};
HMI_SCREEN_ACTION		s_stDemoRTCNoticeActions =		{	HMI_DemoRTCNotice_Initialize,
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
HMI_ENGINE_RESULT HMI_DemoRTCNotice_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	SGUI_SystemIF_MemorySet(s_szRTCNoticeText, 0x00, sizeof(SGUI_CHAR)*(NOTICE_RTC_BUFFER_SIZE+1));
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	SGUI_SDK_EnableRTCInterrupt(true);
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
	SGUI_Notice_Refresh(pstIFObj, s_szRTCNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_TIME					stRTCTime;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*					pstKeyEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstEvent)
	{
		if(HMI_ENGINE_EVENT_ACTION == pstEvent->eType)
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
						eProcessResult = HMI_RET_CANCEL;
						break;
					}
				}
			}
		}
		else if(HMI_ENGINE_EVENT_DATA == pstEvent->eType)
		{
			if(EVENT_ID_RTC == pstEvent->iID)
			{
				SGUI_SystemIF_GetNowTime(&stRTCTime);
				sprintf(s_szRTCNoticeText, DEMO_RTC_NOTICE_TEXT_FMT,
					stRTCTime.Year, stRTCTime.Month, stRTCTime.Day,
					stRTCTime.Hour, stRTCTime.Minute, stRTCTime.Second);
				SGUI_Notice_Refresh(pstIFObj, s_szRTCNoticeText, 0, SGUI_ICON_INFORMATION);
				eProcessResult = HMI_RET_NOACTION;

			}
		}
	}
	else
	{
		eProcessResult = HMI_RET_NOACTION;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoRTCNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, SGUI_INT iActionResult)
{
	if(HMI_RET_CANCEL == iActionResult)
	{
		SGUI_SDK_EnableRTCInterrupt(false);
		HMI_GoBack(NULL);
	}
	return HMI_RET_NORMAL;
}

