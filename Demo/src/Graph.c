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
#include "SGUI_Graph.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static SGUI_INT			HMI_DemoGraph_Initialize(void);
static SGUI_INT			HMI_DemoGraph_PreProcess(const void* pstParameters);
static SGUI_INT			HMI_DemoGraph_RefreshScreen(void);
static SGUI_INT			HMI_DemoGraph_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoGraph_OnExternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoGraph_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
SGUI_GRAPH_POINT		arrPoint[] =			{	{-50, 90},
													{-40, 10},
													{-20, 0},
													{0, 60},
													{20, 40},
													{50  , 80}
												};
SGUI_GRAPH_DATA			stGraphData =			{0x00};
SGUI_GRAPH_CONTROL		stGraphControl =		{{-50, 50}, {0, 100}, 1};
SGUI_GRAPH_INIT_DATA	stGraphInitializeData =	{6 , 0, arrPoint};
SGUI_GRAPH				stGraph =				{&stGraphData, &stGraphControl};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoGraphActions =	{	HMI_DemoGraph_Initialize,
														HMI_DemoGraph_PreProcess,
														HMI_DemoGraph_RefreshScreen,
														HMI_DemoGraph_OnInternalEvent,
														HMI_DemoGraph_OnExternalEvent,
														HMI_DemoGraph_PostProcess,
														};
HMI_SCREEN_OBJECT				g_stHMI_DemoGraph =			{	HMI_SCREEN_ID_ANY,
                                                        &stHMI_DemoGraphActions
                                                    };

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
SGUI_INT HMI_DemoGraph_Initialize(void)
{
	SGUI_Graph_InitializeGraphData(&stGraph, &stGraphInitializeData);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoGraph_PreProcess(const void* pstParameters)
{
	SGUI_Graph_Refresh(&stGraph);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoGraph_RefreshScreen(void)
{
	SGUI_Graph_Refresh(&stGraph);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoGraph_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
{
	return HMI_RET_NOACTION;
}

SGUI_INT HMI_DemoGraph_OnExternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
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
	if(KEY_VALUE_ESC == pstUserEvent->KeyValue[0])
	{
		iProcessResult = HMI_RET_CANCEL;
	}
	else
	{
		iProcessResult = HMI_RET_NOACTION;
	}
	return iProcessResult;
}

SGUI_INT HMI_DemoGraph_PostProcess(SGUI_INT iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return HMI_RET_NORMAL;
}
