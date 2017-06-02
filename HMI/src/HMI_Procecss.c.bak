/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Process.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI process interface.									**/
/** History:															**/
/**	Polarix		2017/6/1	2.0.0.0		New create.						**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Process.h"
#include "HMI_Data.h"

//=======================================================================//
//= Global variable declaration.									    =//
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
	HMI_ScreenData_Initialize();
	HMI_ScreenData_SetCurrentScreen(0);
	HMI_ScreenData_GetCurrentScreen()->UpdateScreen(NULL);
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
	pstCurrentScreen			= HMI_ScreenData_GetCurrentScreen();

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstCurrentScreen)
	{
		if(NULL != pstCurrentScreen->UserActionCallBack)
		{
			iProcessResult = pstCurrentScreen->UserActionCallBack(uiOptions, uiActions);
			if(NULL != pstCurrentScreen->PostProcess)
			{
				iProcessResult = pstCurrentScreen->PostProcess(iProcessResult);
			}
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
/**	@pstPreProcessData:	Update screen data.									**/
/** Return:			None.													**/
/** Notice:			Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
int32_t HMI_Action_UpdateScreen(void* pstPreProcessData)
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
		if(NULL != pstCurrentScreen->UpdateScreen)
		{
			iProcessResult = pstCurrentScreen->UpdateScreen(pstPreProcessData);
			if(NULL != pstCurrentScreen->PostProcess)
			{
				iProcessResult = pstCurrentScreen->PostProcess(iProcessResult);
			}
		}
	}
	else
	{
		iProcessResult = HMI_RESULT_INVALID_DATA;
	}

    return iProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_Action_FollowUp										**/
/** Purpose:		Turn to a screen with screen index.						**/
/** Resources:		Screen data structure and action process function.		**/
/** Params:																	**/
/**	@pstPreProcessData:	Update screen data.									**/
/** Return:			None.													**/
/** Notice:			Screen will only refresh when pstPreProcessData is NULL	**/
/*****************************************************************************/
void HMI_Action_FollowUp(size_t uiScreenIndex, void* pstPreProcessData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_SCREEN*				pstScreen;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	HMI_ScreenData_SetCurrentScreen(uiScreenIndex);
	pstScreen = HMI_ScreenData_GetCurrentScreen();

	if(NULL != pstScreen)
	{
		if(NULL != pstScreen->Initialize)
		{
			pstScreen->Initialize();
		}
		if(NULL != pstScreen->PreProcess)
		{
			pstScreen->PreProcess(pstPreProcessData);
		}
		pstScreen->UpdateScreen(NULL);
	}
}
