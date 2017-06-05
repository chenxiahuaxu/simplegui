/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo03_Notice1.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for notice box interface.						**/
/** History:															**/
/**	Polarix	2017/6/1	1.0.0.0		New create.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo03_Notice1.h"
#include "HMI_Data.h"
#include "HMI_Process.h"
#include "GUI_Notice.h"
#include <stdio.h>

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoNotice_Initialize(void);
static int32_t			HMI_DemoNotice_PreProcess(void* pstParameters);
static int32_t			HMI_DemoNotice_OnInternalEvent(uint32_t uiScreenID, void* pstParameters);
static int32_t			HMI_DemoNotice_OnExternalEvent(uint32_t uiScreenID, void* pstParameters);
static int32_t			HMI_DemoNotice_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char				szRTCNoticeText[64] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoRTCNoticeActions =	{	HMI_DemoNotice_Initialize,
															HMI_DemoNotice_PreProcess,
															HMI_DemoNotice_OnInternalEvent,
															HMI_DemoNotice_OnExternalEvent,
															HMI_DemoNotice_PostProcess,
														};
HMI_SCREEN				g_stHMI_DemoRTCNotice =			{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoRTCNoticeActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

int32_t HMI_DemoNotice_Initialize(void)
{
	return 0;
}

int32_t HMI_DemoNotice_PreProcess(void* pstParameters)
{
	return 0;
}

int32_t HMI_DemoNotice_OnInternalEvent(uint32_t uiScreenID, void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	HMI_RTC_TIME*				pstRTCTime;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	pstRTCTime = (HMI_RTC_TIME*)pstParameters;
	if(NULL != pstRTCTime)
	{
        sprintf(szRTCNoticeText, "系统时间\n%04u-%02u-%02u\n%02u:%02u:%02u",
				pstRTCTime->Year, pstRTCTime->Month+1, pstRTCTime->Day,
				pstRTCTime->Hour, pstRTCTime->Minute, pstRTCTime->Second);
		GUI_Notice_RefreshNotice(szRTCNoticeText, 0, GUI_ICON_INFORMATION);
		iProcessResult = HMI_RESULT_NORMAL;
	}
	else
	{
		iProcessResult = HMI_RESULT_NOACTION;
	}

	return iProcessResult;
}

int32_t HMI_DemoNotice_OnExternalEvent(uint32_t uiScreenID, void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	USER_ACT_KEYPRESS*			pstUserEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RESULT_NORMAL;
	pstUserEvent =				(USER_ACT_KEYPRESS*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(KEY_VALUE_SPACE == pstUserEvent->KeyValue[0])
	{
		iProcessResult = HMI_RESULT_CANCEL;
	}
	else
	{
		iProcessResult = HMI_RESULT_NORMAL;
	}
	return iProcessResult;
}

int32_t HMI_DemoNotice_PostProcess(int32_t iActionResult)
{
	if(HMI_RESULT_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}

	return HMI_RESULT_NORMAL;
}

