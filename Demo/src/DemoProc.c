/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Data.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: User operation interface.								**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//

//=======================================================================//
//= Static function declare											    =//
//=======================================================================//


//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
HMI_ENGINE_OBJECT       g_stDemoEngine;
//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//

/*****************************************************************************/
/** Function Name:	SimpleGUI_DemoProcess   								**/
/** Purpose:		Simple GUI HMI engine and interface demo process.       **/
/** Parameters:		None.													**/
/** Return:			None.													**/
/** Notice:			This function demonstrates how to use the interface and **/
/**                 HMI engine of Simple GUI.
								**/
/*****************************************************************************/
void SimpleGUI_DemoProcess(void)
{

}

/*****************************************************************************/
/** Function Name:	HMI_ActionMap_Initialize								**/
/** Purpose:		Initialize screen follow-up data.						**/
/** Resources:		Screen data array and count variable.					**/
/** Parameters:		None.													**/
/** Return:			None.													**/
/** Notice:			This function must be called in action map initialize	**/
/**					process.												**/
/*****************************************************************************/
HMI_ENGINE_RESULT InitializeEngine(HMI_ENGINE_OBJECT* pstHMIEngineObject)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	HMI_SCREEN_OBJECT*          pstCurrentScreen;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	pstCurrentScreen =          NULL;

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
            //eProcessResult = HMI_AddScreen(HMI_ENGINE_OBJECT* pstHMIEngineObject, HMI_SCREEN_OBJECT* pstScreenObject)
        }

        if(HMI_PROCESS_SUCCESSFUL(eProcessResult))
        {
            //eProcessResult = HMI_ENGINE_RESULT HMI_ActiveEngine(pstHMIEngineObject, iScreenID);
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


