/*************************************************************************/
/** Copyright.															**/
/** FileName: DemoProc.c												**/
/** Author: Polarix														**/
/** Description: User operation interface.								**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"

#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
#include "SDKInterface.h"
#else
#include "OLED.h"
#include "DemoActions.h"
#endif

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
HMI_ENGINE_OBJECT			g_stDemoEngine;
SGUI_SCR_DEV				g_stDeviceInterface;

//=======================================================================//
//= Static function declare.								            =//
//=======================================================================//
static void					KeyPressEventProc(void);
static void					RTCEventProc(void);
static void					SysTickTimerEventProc(void);

//=======================================================================//
//= Function define.										            =//
//=======================================================================//

/*****************************************************************************/
/** Function Name:	SimpleGUI_DemoProcess   								**/
/** Purpose:		Simple GUI HMI engine and interface demo process.       **/
/** Parameters:		None.													**/
/** Return:			HMI_ENGINE_RESULT.										**/
/** Notice:			This function demonstrates how to use the interface and **/
/**                 HMI engine of Simple GUI.                               **/
/*****************************************************************************/
HMI_ENGINE_RESULT InitializeEngine(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	/* Clear structure. */
	SGUI_SystemIF_MemorySet(&g_stDeviceInterface, 0x00, sizeof(SGUI_SCR_DEV));
	SGUI_SystemIF_MemorySet(&g_stDemoEngine, 0x00, sizeof(HMI_ENGINE_OBJECT));
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
	/* Initialize display size. */
	g_stDeviceInterface.stSize.Width = 128;
	g_stDeviceInterface.stSize.Height = 64;
	/* Initialize interface object. */
	g_stDeviceInterface.fnSetPixel = SGUI_SDK_SetPixel;
	g_stDeviceInterface.fnGetPixel = SGUI_SDK_GetPixel;
	g_stDeviceInterface.fnClearScreen = SGUI_SDK_ClearDisplay;
	g_stDeviceInterface.fnRefreshScreen = SGUI_SDK_RefreshDisplay;
#else
	/* Initialize display size. */
	g_stDeviceInterface.stSize.Width = 128;
	g_stDeviceInterface.stSize.Height = 64;
	/* Initialize interface object. */
	g_stDeviceInterface.stActions.fnSetPixel = OLED_SetPixel;
	g_stDeviceInterface.stActions.fnGetPixel = OLED_GetPixel;
	g_stDeviceInterface.stActions.fnClearScreen = OLED_ClearDisplay;
	g_stDeviceInterface.stActions.fnRefreshScreen = OLED_RefreshScreen;
#endif
	g_stDemoEngine.Interface = &g_stDeviceInterface;

	/* Configure HMI engine. */
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_PrepareEngine(&g_stDemoEngine);
	}

	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMIDemo_ScrollingText, SGUI_TRUE);
	}
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMIDemo_List, SGUI_TRUE);
	}
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMIDemo_TextNotice, SGUI_TRUE);
	}
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMIDemo_RTCNotice, SGUI_TRUE);
	}
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMIDemo_VariableBox, SGUI_TRUE);
	}
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_AddScreen(&g_stDemoEngine, &g_stHMI_DemoRealtimeGraph, SGUI_TRUE);
	}

	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_ActiveEngine(&g_stDemoEngine, HMI_SCREEN_ID_DEMO_SCROLLING_TEXT);
	}

	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		eProcessResult = HMI_StartEngine(NULL);
	}

	return eProcessResult;
}

/*****************************************************************************/
/** Function Name:	EventProcess											**/
/** Purpose:		Process posted event.									**/
/** Parameters:																**/
/** @ pstEvent[in]:     HMI event data.                                     **/
/** Return:			HMI_ENGINE_RESULT.										**/
/** Notice:			This function must be called when initialize.			**/
/*****************************************************************************/
HMI_ENGINE_RESULT EventProcess(const HMI_EVENT_BASE* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	eProcessResult = HMI_ProcessEvent(pstEvent);
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		HMI_PostProcess(eProcessResult);
	}

	return eProcessResult;
}

int DemoMainProcess(void)
{
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
    // Initialize Engine.
    InitializeEngine();

    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    while(1)
    {
        // Check and process heart-beat timer event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_TIM_EVENT))
        {
        	SysTickTimerEventProc();
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_TIM_EVENT, false);
        }
        // Check and process key press event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_KEY_EVENT))
        {
            KeyPressEventProc();
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_KEY_EVENT, false);
        }
        // Check and process RTC event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_RTC_EVENT))
        {
            RTCEventProc();
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_RTC_EVENT, false);
        }
    }

	return 0;
}

void KeyPressEventProc(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	KEY_PRESS_EVENT		stEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	HMI_EVENT_INIT(stEvent);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	stEvent.Head.eType = HMI_ENGINE_EVENT_ACTION;
	stEvent.Head.iID = EVENT_ID_KEY_PRESS;
	stEvent.Data.uiKeyValue = SGUI_SDK_GetKeyEventData();
	// Post key press event.
	EventProcess((HMI_EVENT_BASE*)(&stEvent));
}

void SysTickTimerEventProc(void)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    DATA_EVENT				stEvent;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    HMI_EVENT_INIT(stEvent);

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    stEvent.Head.eType =	HMI_ENGINE_EVENT_DATA;
    stEvent.Head.iID =		EVENT_ID_TIMER;
    stEvent.Data.iValue = (rand() % 200)-100;
    // Post timer event.
    EventProcess((HMI_EVENT_BASE*)&stEvent);
}


void RTCEventProc(void)
{
    /*----------------------------------*/
    /* Variable Declaration				*/
    /*----------------------------------*/
    HMI_GENERAL_EVENT		stEvent;

    /*----------------------------------*/
    /* Initialize						*/
    /*----------------------------------*/
    HMI_EVENT_INIT(stEvent);

    /*----------------------------------*/
    /* Process							*/
    /*----------------------------------*/
    stEvent.Head.eType =	HMI_ENGINE_EVENT_DATA;
    stEvent.Head.iID =		EVENT_ID_RTC;
    // Post RTC update message to a screen.
    EventProcess((HMI_EVENT_BASE*)&stEvent);
}
