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
#include "SGUI_RealtimeGraph.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_Initialize(SGUI_IF_OBJ* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_Prepare(SGUI_IF_OBJ* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_RefreshScreen(SGUI_IF_OBJ* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_ProcessEvent(SGUI_IF_OBJ* pstIFObj, HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent);
static HMI_ENGINE_RESULT	HMI_DemoRealGraph_PostProcess(SGUI_IF_OBJ* pstIFObj, SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
SGUI_RTGRAPH_CONTROL	s_stRealtimeGraphControl = {50, -50, SGUI_TRUE, 3, 0};
SGUI_RTGRAPH_DATA		s_stRealtimeGraphData = {{0}, {0}, {0}, 0, 0};
SGUI_RTGRAPH			s_stRealtimeGraph =			{&s_stRealtimeGraphData, &s_stRealtimeGraphControl};
//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		s_stDemoRealtimeGraphActions =	{	HMI_DemoRealGraph_Initialize,
														HMI_DemoRealGraph_Prepare,
														HMI_DemoRealGraph_RefreshScreen,
														HMI_DemoRealGraph_ProcessEvent,
														HMI_DemoRealGraph_PostProcess,
														};
HMI_SCREEN_OBJECT				g_stHMI_DemoRealtimeGraph =		{	HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH,
                                                        &s_stDemoRealtimeGraphActions
                                                    };

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoRealGraph_Initialize(SGUI_IF_OBJ* pstIFObj)
{
	//SGUI_RealtimeGraph_Initialize(&s_stRealtimeGraph);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_Prepare(SGUI_IF_OBJ* pstIFObj, const void* pstParameters)
{
	SGUI_RealtimeGraph_Initialize(&s_stRealtimeGraph);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_RefreshScreen(SGUI_IF_OBJ* pstIFObj, const void* pstParameters)
{
	SGUI_CHAR			szTextBuffer[16];
	SGUI_Common_IntegerToString(s_stRealtimeGraph.Data->ValueArray[s_stRealtimeGraph.Data->ValueCount-1], szTextBuffer, 10, -15, ' ');
	SGUI_RealtimeGraph_Refresh(pstIFObj, &s_stRealtimeGraph, szTextBuffer, "Real-time graph.");
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_ProcessEvent(SGUI_IF_OBJ* pstIFObj, HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_INT					iNewValue;
	SGUI_UINT16					uiKeyCode;
	SGUI_UINT16					uiKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_ENGINE_EVENT_ACTION == eEventType)
	{
		switch(pstEvent->Action)
		{
			case HMI_ENGINE_ACTION_KEY_PRESS:
			{
				uiKeyCode = *((SGUI_UINT16*)pstEvent->Data);
				uiKeyValue = KEY_CODE_VALUE(uiKeyCode);

				if(KEY_VALUE_ESC == uiKeyValue)
				{
					eProcessResult = HMI_RET_CANCEL;
				}
				else
				{
					eProcessResult = HMI_RET_NOACTION;
				}
				break;
			}
			case HMI_ENGINE_ACTION_ON_TIMER:
			{
				iNewValue = *((SGUI_INT*)pstEvent->Data);
				SGUI_RealtimeGraph_AppendValue(&s_stRealtimeGraph, iNewValue);
				HMI_DemoRealGraph_RefreshScreen(pstIFObj, NULL);
				break;
			}
			default:
			{
				eProcessResult = HMI_RET_NOACTION;
				break;
			}
		}
	}
	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoRealGraph_PostProcess(SGUI_IF_OBJ* pstIFObj, SGUI_INT iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_GoBack(NULL);
	}
	return HMI_RET_NORMAL;
}
