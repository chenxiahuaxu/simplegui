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
#include "HMI_Demo04_Graph.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoGraph_Initialize(void);
static int32_t			HMI_DemoGraph_PreProcess(const void* pstParameters);
static int32_t			HMI_DemoGraph_RefreshScreen(void);
static int32_t			HMI_DemoGraph_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoGraph_OnExternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoGraph_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
GUI_GRAPH_POINT			arrPoint[] =			{	{-50, 90},
													{-40, 10},
													{-20, 0},
													{0, 60},
													{20, 40},
													{50  , 80}
												};
GUI_GRAPH_DATA			stGraphData =			{0x00};
GUI_GRAPH_CONTROL		stGraphControl =		{{-50, 50}, {0, 100}, 1};
GUI_GRAPH_INIT_DATA		stGraphInitializeData =	{6 , 0, arrPoint};
GUI_GRAPH				stGraph =				{&stGraphData, &stGraphControl};

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
HMI_SCREEN				g_stHMI_DemoGraph =			{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoGraphActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
int32_t HMI_DemoGraph_Initialize(void)
{
	GUI_Graph_InitializeGraphData(&stGraph, &stGraphInitializeData);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoGraph_PreProcess(const void* pstParameters)
{
	GUI_Graph_Refresh(&stGraph);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoGraph_RefreshScreen(void)
{
	GUI_Graph_Refresh(&stGraph);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoGraph_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters)
{
	return HMI_RESULT_NOACTION;
}

int32_t HMI_DemoGraph_OnExternalEvent(uint32_t uiScreenID, const void* pstParameters)
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
	if(KEY_VALUE_ESC == pstUserEvent->KeyValue[0])
	{
		iProcessResult = HMI_RESULT_CANCEL;
	}
	else
	{
		iProcessResult = HMI_RESULT_NOACTION;
	}
	return iProcessResult;
}

int32_t HMI_DemoGraph_PostProcess(int32_t iActionResult)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_RESULT_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return HMI_RESULT_NORMAL;
}
