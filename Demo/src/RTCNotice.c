/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo03_Notice1.c										**/
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
#include <stdio.h>

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static SGUI_INT			HMI_DemoNotice_Initialize(void);
static SGUI_INT			HMI_DemoNotice_PreProcess(const void* pstParameters);
static SGUI_INT			HMI_DemoNotice_RefreshScreen(void);
static SGUI_INT			HMI_DemoNotice_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoNotice_OnExternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoNotice_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char				szRTCNoticeText[64] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoRTCNoticeActions =	{	HMI_DemoNotice_Initialize,
															HMI_DemoNotice_PreProcess,
															HMI_DemoNotice_RefreshScreen,
															HMI_DemoNotice_OnInternalEvent,
															HMI_DemoNotice_OnExternalEvent,
															HMI_DemoNotice_PostProcess,
														};
HMI_SCREEN_OBJECT       g_stHMI_DemoRTCNotice =			{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoRTCNoticeActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

SGUI_INT HMI_DemoNotice_Initialize(void)
{
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_PreProcess(const void* pstParameters)
{
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_RefreshScreen(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_TIME				stRTCTime;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_Common_GetNowTime(&stRTCTime);
	sprintf(szRTCNoticeText, "系统时间\n%04u-%02u-%02u\n%02u:%02u:%02u",
				stRTCTime.Year, stRTCTime.Month, stRTCTime.Day,
				stRTCTime.Hour, stRTCTime.Minute, stRTCTime.Second);
	SGUI_Notice_RefreshNotice(szRTCNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iProcessResult;
	SGUI_TIME*				pstRTCTime;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	pstRTCTime = (SGUI_TIME*)pstParameters;
	if(NULL != pstRTCTime)
	{
        sprintf(szRTCNoticeText, "系统时间\n%04u-%02u-%02u\n%02u:%02u:%02u",
				pstRTCTime->Year, pstRTCTime->Month+1, pstRTCTime->Day,
				pstRTCTime->Hour, pstRTCTime->Minute, pstRTCTime->Second);
		SGUI_Notice_RefreshNotice(szRTCNoticeText, 0, SGUI_ICON_INFORMATION);
		iProcessResult = HMI_RET_NORMAL;
	}
	else
	{
		iProcessResult = HMI_RET_NOACTION;
	}

	return iProcessResult;
}

SGUI_INT HMI_DemoNotice_OnExternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iProcessResult;
	USER_ACT_KEYPRESS*			pstUserEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RET_NORMAL;
	pstUserEvent =				(USER_ACT_KEYPRESS*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(KEY_VALUE_ENTER == pstUserEvent->KeyValue[0])
	{
		iProcessResult = HMI_RET_CANCEL;
	}
	else
	{
		iProcessResult = HMI_RET_NORMAL;
	}
	return iProcessResult;
}

SGUI_INT HMI_DemoNotice_PostProcess(SGUI_INT iActionResult)
{
	if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}

	return HMI_RET_NORMAL;
}

