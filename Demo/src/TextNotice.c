/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo03_Notice2.c										**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for notice box interface.						**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Notice.h"
#include "string.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

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
static char				szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE+1] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoTextNoticeActions =	{	HMI_DemoNotice_Initialize,
															HMI_DemoNotice_PreProcess,
															HMI_DemoNotice_RefreshScreen,
															HMI_DemoNotice_OnInternalEvent,
															HMI_DemoNotice_OnExternalEvent,
															HMI_DemoNotice_PostProcess,
														};
HMI_SCREEN_OBJECT       g_stHMI_DemoTextNotice =		{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoTextNoticeActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

SGUI_INT HMI_DemoNotice_Initialize(void)
{
	SGUI_Notice_RefreshNotice(szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_PreProcess(const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL == pstParameters)
	{
		SGUI_Common_StringCopy(szDemoNoticeText, "无参数。");
	}
	else
	{
		strncpy(szDemoNoticeText, (SGUI_PSZSTR)pstParameters, NOTICE_TEXT_BUFFER_SIZE);
		szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE] = '\0';
	}
	SGUI_Notice_RefreshNotice(szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_RefreshScreen(void)
{
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoNotice_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iProcessResult;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	iProcessResult = HMI_RET_NOACTION;
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
		iProcessResult = HMI_RET_CONFIRM;
	}
	else
	{
		iProcessResult = HMI_RET_NOACTION;
	}
	return iProcessResult;
}

SGUI_INT HMI_DemoNotice_PostProcess(SGUI_INT iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RET_CONFIRM == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return 0;
}

