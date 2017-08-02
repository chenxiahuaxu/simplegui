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
#include "HMI_Demo03_Notice2.h"
#include "string.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoNotice_Initialize(void);
static int32_t			HMI_DemoNotice_PreProcess(const void* pstParameters);
static int32_t			HMI_DemoNotice_RefreshScreen(void);
static int32_t			HMI_DemoNotice_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoNotice_OnExternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoNotice_PostProcess(int32_t iActionResult);

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
HMI_SCREEN				g_stHMI_DemoTextNotice =		{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoTextNoticeActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

int32_t HMI_DemoNotice_Initialize(void)
{
	SGUI_Notice_RefreshNotice(szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoNotice_PreProcess(const void* pstParameters)
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
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoNotice_RefreshScreen(void)
{
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoNotice_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	iProcessResult = HMI_RESULT_NOACTION;
	return iProcessResult;
}

int32_t HMI_DemoNotice_OnExternalEvent(uint32_t uiScreenID, const void* pstParameters)
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
	if(KEY_VALUE_ENTER == pstUserEvent->KeyValue[0])
	{
		iProcessResult = HMI_RESULT_CONFIRM;
	}
	else
	{
		iProcessResult = HMI_RESULT_NOACTION;
	}
	return iProcessResult;
}

int32_t HMI_DemoNotice_PostProcess(int32_t iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RESULT_CONFIRM == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return 0;
}

