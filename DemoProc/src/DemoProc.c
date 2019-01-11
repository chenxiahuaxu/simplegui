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
//= User Macro definition.											    =//
//=======================================================================//

//=======================================================================//
//= Static function declare											    =//
//=======================================================================//
static HMI_ENGINE_RESULT	InitializeEngine_Internal(HMI_ENGINE_OBJECT* pstHMIEngineObject);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
HMI_ENGINE_OBJECT			g_stDemoEngine;
SGUI_SCR_DEV				g_stDeviceInterface;

//=======================================================================//
//= Function define.										            =//
//=======================================================================//

/*****************************************************************************/
/** Function Name:	SimpleGUI_DemoProcess   								**/
/** Purpose:		Simple GUI HMI engine and interface demo process.       **/
/** Parameters:		None.													**/
/** Return:			None.													**/
/** Notice:			This function demonstrates how to use the interface and **/
/**                 HMI engine of Simple GUI.                               **/
/*****************************************************************************/
void InitializeEngine(void)
{
	/* Clear structure. */
	SGUI_SystemIF_MemorySet(&g_stDeviceInterface, 0x00, sizeof(SGUI_SCR_DEV));
	SGUI_SystemIF_MemorySet(&g_stDemoEngine, 0x00, sizeof(HMI_ENGINE_OBJECT));
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
	/* Initialize interface object. */
	g_stDeviceInterface.fnSetPixel = SGUI_SDK_SetPixel;
	g_stDeviceInterface.fnGetPixel = SGUI_SDK_GetPixel;
	g_stDeviceInterface.fnClearScreen = SGUI_SDK_ClearDisplay;
	g_stDeviceInterface.fnRefreshScreen = SGUI_SDK_RefreshDisplay;
#else
	g_stDeviceInterface.stActions.fnSetPixel = OLED_SetPixel;
	g_stDeviceInterface.stActions.fnGetPixel = OLED_GetPixel;
	g_stDeviceInterface.stActions.fnClearScreen = OLED_ClearDisplay;
	g_stDeviceInterface.stActions.fnRefreshScreen = OLED_RefreshScreen;
#endif
	g_stDemoEngine.Interface = &g_stDeviceInterface;

	/* Configure HMI engine. */
	InitializeEngine_Internal(&g_stDemoEngine);
}

/*****************************************************************************/
/** Function Name:	InitializeEngine										**/
/** Purpose:		Initialize HMI demo engine.								**/
/** Parameters:																**/
/** @ pstHMIEngineObject[in]: HMI engine object pointer.					**/
/** Return:			HMI_ENGINE_RESULT.										**/
/** Notice:			This function must be called when initialize.			**/
/*****************************************************************************/
HMI_ENGINE_RESULT InitializeEngine_Internal(HMI_ENGINE_OBJECT* pstHMIEngineObject)
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
    if(NULL != pstHMIEngineObject)
    {
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_PrepareEngine(pstHMIEngineObject);
        }

        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMIDemo_ScrollingText, SGUI_TRUE);
        }
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMIDemo_List, SGUI_TRUE);
        }
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMIDemo_TextNotice, SGUI_TRUE);
        }
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMIDemo_RTCNotice, SGUI_TRUE);
        }
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMIDemo_VariableBox, SGUI_TRUE);
        }
        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_AddScreen(pstHMIEngineObject, &g_stHMI_DemoRealtimeGraph, SGUI_TRUE);
        }

        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_ActiveEngine(pstHMIEngineObject, HMI_SCREEN_ID_DEMO_SCROLLING_TEXT);
        }

        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            eProcessResult = HMI_StartEngine(NULL);
        }
    }
    else
    {
        // No activated HMI engine object.
        eProcessResult = HMI_RET_INVALID_DATA;
    }

	return eProcessResult;
}

/*****************************************************************************/
/** Function Name:	EventProcess											**/
/** Purpose:		Process posted event.									**/
/** Parameters:																**/
/** @ eEventType[in]:   HMI event type.         						    **/
/** @ pstEvent[in]:     HMI event data.                                     **/
/** Return:			HMI_ENGINE_RESULT.										**/
/** Notice:			This function must be called when initialize.			**/
/*****************************************************************************/
HMI_ENGINE_RESULT EventProcess(HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent)
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

	eProcessResult = HMI_ProcessEvent(eEventType, pstEvent);
	if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
	{
		HMI_PostProcess(eProcessResult);
	}

	return eProcessResult;
}

int DemoMainProcess(void)
{
    // Start heart-beat timer.
    //SGUI_SDK_ConfigHearBeatTimer(SDK_DEFAULT_HEART_BEAT_INTERVAL_MS);
	// Start RTC timer.
    //SGUI_SDK_EnableRTCInterrupt(true);

    // Initialize Engine.
    InitializeEngine();

    while(1)
    {
        // Check and process heart-beat timer event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_TIM_EVENT))
        {
            SGUI_SDK_HeartBeatTimerTagEvent();
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_TIM_EVENT, false);
        }
        // Check and process key press event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_KEY_EVENT))
        {
            SGUI_SDK_KeyPressInterruptEvent(SGUI_SDK_GetKeyEventData());
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_KEY_EVENT, false);
        }
        // Check and process RTC event.
        if(true == SGUI_SDK_GetEventSyncFlag(ENV_FLAG_IDX_SDK_RTC_EVENT))
        {
            SGUI_SDK_RTCInterruptTagEvent();
            SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_IDX_SDK_RTC_EVENT, false);
        }
    }

	return 0;
}
