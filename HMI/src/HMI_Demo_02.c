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
#include "HMI_Demo_01.h"
#include "GUI_Notice.h"
#include "HMI_Process.h"
#include <stdio.h>

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t							HMI_DemoNotice_Initialize(void);
static int32_t							HMI_DemoNotice_PreProcess(void* pstParameters);
static int32_t							HMI_DemoNotice_UpdateScreen(void* pstParameters);
static int32_t							HMI_DemoNotice_UserActions(uint16_t uiOptions, uint16_t* puiActions);
static int32_t							HMI_DemoNotice_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static char								szDemoNoticeText[64] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN								g_stHMI_DemoNotice = {	HMI_DemoNotice_Initialize,
																HMI_DemoNotice_PreProcess,
																HMI_DemoNotice_UserActions,
                                                                HMI_DemoNotice_UpdateScreen,
                                                                HMI_DemoNotice_PostProcess,
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
	/* Variable Declaration				*/
	/*----------------------------------*/
	size_t						uiListIndex;

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

int32_t HMI_DemoNotice_UpdateScreen(void* pstParameters)
{
	GUI_Notice_RefreshNotice(szDemoNoticeText, 0, GUI_ICON_INFORMATION);
	return 0;
}

int32_t HMI_DemoNotice_UserActions(uint16_t uiOptions, uint16_t* puiActions)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult				= HMI_RESULT_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	iProcessResult = HMI_RESULT_CANCEL;
	return iProcessResult;
}

int32_t HMI_DemoNotice_PostProcess(int32_t iActionResult)
{
	HMI_Action_FollowUp(0, NULL);
	return 0;
}

