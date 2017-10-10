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
static HMI_ENGINE_RESULT	HMI_DemoNotice_Initialize(void);
static HMI_ENGINE_RESULT	HMI_DemoNotice_Prepare(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoNotice_RefreshScreen(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoNotice_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent);
static HMI_ENGINE_RESULT	HMI_DemoNotice_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_CHAR		m_szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE+1] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoTextNoticeActions =	{	HMI_DemoNotice_Initialize,
															HMI_DemoNotice_Prepare,
															HMI_DemoNotice_RefreshScreen,
															HMI_DemoNotice_ProcessEvent,
															HMI_DemoNotice_PostProcess,
														};
HMI_SCREEN_OBJECT       g_stHMIDemo_TextNotice =		{	HMI_SCREEN_ID_DEMO_TEXT_NOTICE,
															&stHMI_DemoTextNoticeActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoNotice_Initialize(void)
{
	SGUI_Common_MemorySet(m_szDemoNoticeText, 0x00, sizeof(SGUI_CHAR)*(NOTICE_TEXT_BUFFER_SIZE+1));
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoNotice_Prepare(const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL == pstParameters)
	{
		SGUI_Common_StringLengthCopy(m_szDemoNoticeText, "无参数。", NOTICE_TEXT_BUFFER_SIZE);
	}
	else
	{
		SGUI_Common_StringLengthCopy(m_szDemoNoticeText, (SGUI_PSZSTR)pstParameters, NOTICE_TEXT_BUFFER_SIZE);
		m_szDemoNoticeText[NOTICE_TEXT_BUFFER_SIZE] = '\0';
	}
	SGUI_Notice_RefreshNotice(m_szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoNotice_RefreshScreen(const void* pstParameters)
{
	SGUI_Notice_RefreshNotice(m_szDemoNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoNotice_ProcessEvent(HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16*				parrKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(eEventType == HMI_ENGINE_EVENT_ACTION)
	{
		if(NULL != pstEvent)
		{
			parrKeyValue = (SGUI_UINT16*)pstEvent->Data;
			if(NULL != parrKeyValue)
			{
				switch(*(parrKeyValue+1))
				{
					case KEY_VALUE_ENTER:
					case KEY_VALUE_ESC:
					{
						eProcessResult = HMI_RET_CONFIRM;
						break;
					}
				}
			}
		}
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoNotice_PostProcess(SGUI_INT iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RET_CONFIRM == iActionResult)
	{
		HMI_GoBack(NULL);
	}
	return HMI_RET_NORMAL;
}

