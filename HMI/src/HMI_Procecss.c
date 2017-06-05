/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Process.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: This file provides ActionMap interface function.		**/
/** History:															**/
/**	Polarix		2017/6/1	2.0.0.0		New create.						**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Process.h"
#include "HMI_Data.h"

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static bool							bInProcess;

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	HMI_Action_Initialize.									**/
/** Purpose:		Initialize screen data and action control.				**/
/** Resources:		Screen data definition.									**/
/** Params:			None.													**/
/** Return:			None.													**/
/** Notice:			This function must be called when system initialized.	**/
/*****************************************************************************/
void HMI_Action_Initialize(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_SCREEN*					pstCurrentScreen;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	HMI_ScreenData_Initialize();
	HMI_ScreenData_SetCurrentScreen(HMI_SCREEN_START);
	pstCurrentScreen = HMI_ScreenData_GetCurrentScreen();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Add initialize process for the first screen here.
	pstCurrentScreen->Actions->PreProcess(NULL);
	pstCurrentScreen->Actions->InternalEventProcess(HMI_SCREEN_START, NULL);
	bInProcess = false;
}

/*****************************************************************************/
/** Function Name:	HMI_Action_OnUserEvent									**/
/** Purpose:		User action process interface.							**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/** @uiScreenID:		Matched screen ID.									**/
/**	@pstData:			User action data pointer.							**/
/**						key code array.										**/
/** Return:			Process result.											**/
/** Notice:			None.													**/
/*****************************************************************************/
int32_t HMI_Action_OnExternalEvent(uint32_t uiScreenID, void* pstData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	HMI_SCREEN*					pstCurrentScreen;
	USER_ACT_KEYPRESS*			pstUserEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RESULT_NORMAL;
	// Get the active screen.
	pstCurrentScreen =			HMI_ScreenData_GetCurrentScreen();
	pstUserEvent =				pstData;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(true == bInProcess)
	{
		// GUI screen is in process, ignore user action.
		iProcessResult =HMI_RESULT_INPROCESS;
	}
	else if(NULL == pstCurrentScreen)
	{
		// Screen data is invalid.
		iProcessResult = HMI_RESULT_INVALID_DATA;
	}
	else
	{
		bInProcess = true;
		// Call user action callback function if existed.
		if(NULL != pstCurrentScreen->Actions->ExternalEventProcess)
		{
			iProcessResult = pstCurrentScreen->Actions->ExternalEventProcess(HMI_SCREEN_ID_ANY, pstUserEvent);
		}
		// Call post process function if existed.
		if(NULL != pstCurrentScreen->Actions->PostProcess)
		{
			iProcessResult = pstCurrentScreen->Actions->PostProcess(iProcessResult);
		}
		else
		{
			// Post process is must be existed.
			iProcessResult = HMI_RESULT_INVALID_DATA;
		}
		bInProcess = false;
	}
	return iProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_Action_UpdateScreen									**/
/** Purpose:		Refresh screen or update screen with new data.			**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/** @uiScreenID:		Matched screen ID.									**/
/**	@pstPreProcessData:	Update screen data.									**/
/** Return:			None.													**/
/** Notice:			Screen update action will only process when screen id	**/
/**					is actived.												**/
/**					Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
int32_t HMI_Action_OnInternalEvent(uint32_t uiScreenID, void* pstData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	HMI_SCREEN*					pstCurrentScreen;
	USER_ACT_KEYPRESS*			pstUserEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RESULT_NORMAL;
	pstCurrentScreen =			HMI_ScreenData_GetCurrentScreen();
	pstUserEvent =				pstData;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(true == bInProcess)
	{
		// GUI screen is in process, ignore user action.
		iProcessResult =HMI_RESULT_INPROCESS;
	}
	else if(NULL == pstCurrentScreen)
	{
		// Screen data is invalid.
		iProcessResult = HMI_RESULT_INVALID_DATA;
	}
	else
	{
		if((uiScreenID == pstCurrentScreen->ScreenID) && (NULL != pstCurrentScreen->Actions->InternalEventProcess))
		{
			iProcessResult = pstCurrentScreen->Actions->InternalEventProcess(uiScreenID, pstUserEvent);
		}
		// Call post process function if existed.
		if(NULL != pstCurrentScreen->Actions->PostProcess)
		{
			iProcessResult = pstCurrentScreen->Actions->PostProcess(iProcessResult);
		}
		else
		{
			// Post process is must be existed.
			iProcessResult = HMI_RESULT_INVALID_DATA;
		}
	}

    return iProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_Action_Goto											**/
/** Purpose:		Turn to a screen with screen index.						**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/**	@uiDestScreenID:	Screen ID witch will be going to.					**/
/**	@pstPreProcessData:	New screen initialize data.							**/
/** Return:			None.													**/
/** Notice:			Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
void HMI_Action_Goto(uint32_t uiDestScreenID, void* pstPreProcessData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_SCREEN*				pstScreen;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Add current screen ID to history stack.
	if(true == HMI_ScreenData_PushHistory())
	{
		// Set destination screen.
		HMI_ScreenData_SetCurrentScreen(uiDestScreenID);
		pstScreen = HMI_ScreenData_GetCurrentScreen();
		if(NULL != pstScreen->Actions->Initialize)
		{
			pstScreen->Actions->Initialize();
		}
		if(NULL != pstScreen->Actions->PreProcess)
		{
			pstScreen->Actions->PreProcess(pstPreProcessData);
		}
		pstScreen->Actions->InternalEventProcess(uiDestScreenID, pstPreProcessData);
	}
	else
	{
        // Stack is full, push history failed.
	}
}

/*****************************************************************************/
/** Function Name:	HMI_Action_GoBack.										**/
/** Purpose:		Go back to previous screen in actions history.			**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/**	@pstPreProcessData:	Update screen data.									**/
/** Return:			None.													**/
/** Notice:			Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
void HMI_Action_GoBack(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_SCREEN*				pstScreen;
	uint32_t				uiLastScreenID;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiLastScreenID =		HMI_ScreenData_PopHistory();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	HMI_ScreenData_SetCurrentScreen(uiLastScreenID);
	pstScreen = HMI_ScreenData_GetCurrentScreen();

	if(NULL != pstScreen)
	{
		pstScreen->Actions->InternalEventProcess(uiLastScreenID, NULL);
	}
}
