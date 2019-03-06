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
static HMI_ENGINE_RESULT	HMI_DemoTextNotice_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoTextNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoTextNotice_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoTextNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoTextNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_CHAR		s_szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE+1] = {0x00};

HMI_SCREEN_ACTION		s_stDemoTextNoticeActions =		{	HMI_DemoTextNotice_Initialize,
															HMI_DemoTextNotice_Prepare,
															HMI_DemoTextNotice_RefreshScreen,
															HMI_DemoTextNotice_ProcessEvent,
															HMI_DemoTextNotice_PostProcess,
														};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_TextNotice =		{	HMI_SCREEN_ID_DEMO_TEXT_NOTICE,
															&s_stDemoTextNoticeActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoTextNotice_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	SGUI_SystemIF_MemorySet(s_szDemoNoticeText, 0x00, sizeof(SGUI_CHAR)*(NOTICE_TEXT_BUFFER_SIZE+1));
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoTextNotice_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL == pstParameters)
	{
		SGUI_SystemIF_StringLengthCopy(s_szDemoNoticeText, "No Parameter.", NOTICE_TEXT_BUFFER_SIZE);
	}
	else
	{
		SGUI_SystemIF_StringLengthCopy(s_szDemoNoticeText, (SGUI_SZSTR)pstParameters, NOTICE_TEXT_BUFFER_SIZE);
		s_szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE] = '\0';
	}
	SGUI_Notice_Refresh(pstIFObj, s_szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoTextNotice_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	SGUI_Notice_Refresh(pstIFObj, s_szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoTextNotice_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
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
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoTextNotice_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			HMI_GoBack(NULL);
		}
	}
	return HMI_RET_NORMAL;
}

