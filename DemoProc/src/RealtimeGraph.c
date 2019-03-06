/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo04_Graph.c										**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for graph interface.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Text.h"
#include "SGUI_RealtimeGraph.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
SGUI_RTGRAPH_CONTROL		s_stRealtimeGraphControl =	{50, -50, SGUI_TRUE, 3, 0};
SGUI_RTGRAPH_DATA			s_stRealtimeGraphData =		{{1, 9, 126, 46}, {0}, {0}, {0}, 0, 0};
SGUI_RTGRAPH				s_stRealtimeGraph =			{&s_stRealtimeGraphData, &s_stRealtimeGraphControl};
//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
static HMI_SCREEN_ACTION	s_stDemoRealtimeGraphActions =	{	HMI_DemoRealGraph_Initialize,
														HMI_DemoRealGraph_Prepare,
														HMI_DemoRealGraph_RefreshScreen,
														HMI_DemoRealGraph_ProcessEvent,
														HMI_DemoRealGraph_PostProcess,
														};
HMI_SCREEN_OBJECT			g_stHMI_DemoRealtimeGraph =		{	HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH,
                                                        &s_stDemoRealtimeGraphActions
                                                    };

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoRealGraph_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	//SGUI_RealtimeGraph_Initialize(&s_stRealtimeGraph);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	// Reinitialize data.
	SGUI_RealtimeGraph_Initialize(&s_stRealtimeGraph);
	// Paint frame.
	SGUI_Basic_DrawRectangle(pstIFObj, 0, 0, RECT_WIDTH(pstIFObj->stSize), RECT_HEIGHT(pstIFObj->stSize), SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
	// Update screen display.
	SGUI_RealtimeGraph_Refresh(pstIFObj, &s_stRealtimeGraph);
	// Start dummy heart-beat timer.
	SGUI_SDK_ConfigHearBeatTimer(SDK_DEFAULT_HEART_BEAT_INTERVAL_MS);

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	SGUI_CHAR			szTextBuffer[16];
	SGUI_RECT_AREA		stTextDisplayArea;
	SGUI_RECT_AREA		stTextDataArea;

	// Paint frame.
	SGUI_Basic_DrawRectangle(pstIFObj, 0, 0, RECT_WIDTH(pstIFObj->stSize), RECT_HEIGHT(pstIFObj->stSize), SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
	// Paint title
	stTextDisplayArea.PosX = 1;
	stTextDisplayArea.PosY = 1;
	stTextDisplayArea.Width = RECT_WIDTH(pstIFObj->stSize)-2;
	stTextDisplayArea.Height = 8;
	stTextDataArea.PosX = 0;
	stTextDataArea.PosY = 0;
	SGUI_Text_DrawSingleLineText(pstIFObj, "Real-time graph", SGUI_FONT_SIZE_H8, &stTextDisplayArea, &stTextDataArea, SGUI_DRAW_NORMAL);
	// Paint value.
	SGUI_Common_IntegerToString(s_stRealtimeGraph.Data->ValueArray[s_stRealtimeGraph.Data->ValueCount-1], szTextBuffer, 10, -15, ' ');
	stTextDisplayArea.PosX = 1;
	stTextDisplayArea.PosY = RECT_HEIGHT(pstIFObj->stSize)-9;
	stTextDisplayArea.Width = RECT_WIDTH(pstIFObj->stSize)-2;
	stTextDisplayArea.Height = 8;
	stTextDataArea.PosX = 0;
	stTextDataArea.PosY = 0;
	SGUI_Text_DrawSingleLineText(pstIFObj, szTextBuffer, SGUI_FONT_SIZE_H8, &stTextDisplayArea, &stTextDataArea, SGUI_DRAW_NORMAL);
	SGUI_RealtimeGraph_Refresh(pstIFObj, &s_stRealtimeGraph);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_INT					iNewValue;
	SGUI_UINT16					uiKeyCode;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*			pstKeyEvent;
	DATA_EVENT*					pstDataEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(pstEvent->iID)
	{
		case EVENT_ID_KEY_PRESS:
		{
			pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
			if(SGUI_FALSE == HMI_EVENT_SIZE_CHK(*pstKeyEvent, KEY_PRESS_EVENT))
			{
				// Event data is invalid.
				eProcessResult = HMI_RET_INVALID_DATA;
			}
			else
			{
				uiKeyCode = pstKeyEvent->Data.uiKeyValue;
				uiKeyValue = KEY_CODE_VALUE(uiKeyCode);

				if(KEY_VALUE_ESC == uiKeyValue)
				{
					iProcessAction = HMI_DEMO_PROC_CANCEL;
				}
			}
			break;
		}
		case EVENT_ID_TIMER:
		{
			pstDataEvent = (DATA_EVENT*)pstEvent;
			if(SGUI_FALSE == HMI_EVENT_SIZE_CHK(*pstDataEvent, DATA_EVENT))
			{
				// Event data is invalid.
				eProcessResult = HMI_RET_INVALID_DATA;
			}
			else
			{
				iNewValue = pstDataEvent->Data.iValue;
				SGUI_RealtimeGraph_AppendValue(pstIFObj, &s_stRealtimeGraph, iNewValue);
				HMI_DemoRealGraph_RefreshScreen(pstIFObj, NULL);
			}
			break;
		}
		default:
		{
			/* No process. */
			break;
		}
	}

	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			// Stop heart-beat timer.
			SGUI_SDK_ConfigHearBeatTimer(0);
			// Go back to last screen.
			HMI_GoBack(NULL);
		}
	}

	return HMI_RET_NORMAL;
}
