/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo_02.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for notice box interface.						**/
/** History:															**/
/**	Polarix	2017/6/1	1.0.0.0		New create.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo03_Notice2.h"


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
static char				szDemoNoticeText[64] = {0x00};
static size_t			uiListIndex = 0;


//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoTextNoticeActions =	{	HMI_DemoNotice_Initialize,
															HMI_DemoNotice_PreProcess,
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
	return 0;
}

int32_t HMI_DemoNotice_PreProcess(void* pstParameters)
{
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL == pstParameters)
	{
		uiListIndex = 0;
	}
	else
	{
		uiListIndex = *((uint32_t*)pstParameters);
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	sprintf(szDemoNoticeText, "选择了列表项目%u.", uiListIndex);

	return 0;
}

int32_t HMI_DemoNotice_OnInternalEvent(uint32_t uiScreenID, void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(g_stHMI_DemoTextNotice.ScreenID == uiScreenID)
	{
		GUI_Notice_RefreshNotice(szDemoNoticeText, 0, GUI_ICON_INFORMATION);
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

