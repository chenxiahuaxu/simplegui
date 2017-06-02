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
	pstCurrentScreen->Actions->RefreshScreen(HMI_SCREEN_START, NULL);
}

/*****************************************************************************/
/** Function Name:	HMI_Action_UserActions									**/
/** Purpose:		User action process interface.							**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/**	@uiOptions:			User option value, usually the control key code of	**/
/**						Flags.												**/
/**	@uiActions:			User action value, usually the common key code or 	**/
/**						key code array.										**/
/** Return:			Process result.											**/
/** Notice:			None.													**/
/*****************************************************************************/
int32_t HMI_Action_UserActions(uint16_t uiOptions, uint16_t* uiActions)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	HMI_SCREEN*					pstCurrentScreen;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult				= HMI_RESULT_NORMAL;
	// Get the active screen.
	pstCurrentScreen			= HMI_ScreenData_GetCurrentScreen();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstCurrentScreen)
	{
		if(NULL != pstCurrentScreen->Actions->UserActionCallBack)
		{
			// Call the user action process function.
			iProcessResult = pstCurrentScreen->Actions->UserActionCallBack(uiOptions, uiActions);
			// Call the post-process function when existed.
			iProcessResult = pstCurrentScreen->Actions->PostProcess(iProcessResult);
		}
	}
	else
	{
		iProcessResult = HMI_RESULT_INVALID_DATA;
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
int32_t HMI_Action_RefreshScreen(uint32_t uiScreenID, void* pstData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	HMI_SCREEN*					pstCurrentScreen;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult				= HMI_RESULT_NORMAL;
	pstCurrentScreen			= HMI_ScreenData_GetCurrentScreen();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstCurrentScreen)
	{
		if((uiScreenID == pstCurrentScreen->ScreenID) && (NULL != pstCurrentScreen->Actions->RefreshScreen))
		{
			iProcessResult = pstCurrentScreen->Actions->RefreshScreen(uiScreenID, pstData);
		}
	}
	else
	{
		iProcessResult = HMI_RESULT_INVALID_DATA;
	}

    return iProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_Action_GotoScreen									**/
/** Purpose:		Turn to a screen with screen index.						**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/**	@pstPreProcessData:	Update screen data.									**/
/** Return:			None.													**/
/** Notice:			Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
void HMI_Action_GotoScreen(uint32_t uiCurrentScreenID, uint32_t uiDestScreenID, void* pstPreProcessData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_SCREEN*				pstScreen;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	HMI_ScreenData_SetCurrentScreen(uiDestScreenID);
	pstScreen = HMI_ScreenData_GetCurrentScreen();

	if(NULL != pstScreen)
	{
		HMI_ScreenData_AddToHistory(uiCurrentScreenID);
		if(NULL != pstScreen->Actions->Initialize)
		{
			pstScreen->Actions->Initialize();
		}
		if(NULL != pstScreen->Actions->PreProcess)
		{
			pstScreen->Actions->PreProcess(pstPreProcessData);
		}
		pstScreen->Actions->RefreshScreen(uiDestScreenID, pstPreProcessData);
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
	uiLastScreenID =		HMI_ScreenData_GetLastHistory();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	HMI_ScreenData_SetCurrentScreen(uiLastScreenID);
	pstScreen = HMI_ScreenData_GetCurrentScreen();

	if(NULL != pstScreen)
	{
		pstScreen->Actions->RefreshScreen(uiLastScreenID, NULL);
	}
}
