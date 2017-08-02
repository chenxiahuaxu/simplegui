/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_ProcessBar.c											**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Process bar display interface.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Basic.h"
#include "SGUI_ProcessBar.h"

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	GUI_UpdateProcessBar								**/
/** Purpose:		Display or update a process bar.					**/
/** Resources:		Process bar data structure.							**/
/** Params:																**/
/**	@pProcessBarData:	Process bar data whitch will update on screen.	**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_RefreshProcessBar(SGUI_PROCBAR_STRUCT *pProcessBarData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_UINT16					uiProcessBlockStartX, uiProcessBlockStartY;
	SGUI_UINT16					uiProcessBlockWidth, uiProcessBlockHeight;
	SGUI_COLOR					eBackColor, eFillColor;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pProcessBarData)
	{
		if((pProcessBarData->Parameter.Width > 3) && (pProcessBarData->Parameter.Height > 3))
		{
			// Check value must be less then PROCBAR_VALUE_MAX.
			if(pProcessBarData->Data.Value > pProcessBarData->Parameter.MaxValue)
			{
				pProcessBarData->Data.Value = pProcessBarData->Parameter.MaxValue;
			}
			// Update process bar data.
			switch(pProcessBarData->Parameter.Direction)
			{
				case SGUI_PROCBAR_DOWN:	// Process from up to down.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= pProcessBarData->Parameter.Width - 2;
					uiProcessBlockHeight	= (pProcessBarData->Parameter.Height - 2) * (pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					eBackColor = GUI_COLOR_BKGCLR;
					eFillColor = GUI_COLOR_FRGCLR;
					break;
				}
				case SGUI_PROCBAR_LEFT:	// Process from right to left.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= (pProcessBarData->Parameter.Width - 2) * (pProcessBarData->Parameter.MaxValue - pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					uiProcessBlockHeight	= pProcessBarData->Parameter.Height - 2;
					eBackColor = GUI_COLOR_FRGCLR;
					eFillColor = GUI_COLOR_BKGCLR;
					break;
				}
				case SGUI_PROCBAR_RIGHT:	// Process from left to right.
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= (pProcessBarData->Parameter.Width - 2) * (pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					uiProcessBlockHeight	= pProcessBarData->Parameter.Height - 2;
					eBackColor = GUI_COLOR_BKGCLR;
					eFillColor = GUI_COLOR_FRGCLR;
					break;
				}
				case SGUI_PROCBAR_UP:	// Process from down to up.
				default:
				{
					uiProcessBlockStartX	= pProcessBarData->Parameter.PosX + 1;
					uiProcessBlockStartY	= pProcessBarData->Parameter.PosY + 1;
					uiProcessBlockWidth		= pProcessBarData->Parameter.Width - 2;
					uiProcessBlockHeight	= (pProcessBarData->Parameter.Height - 2) * (pProcessBarData->Parameter.MaxValue - pProcessBarData->Data.Value) / pProcessBarData->Parameter.MaxValue;
					eBackColor = GUI_COLOR_FRGCLR;
					eFillColor = GUI_COLOR_BKGCLR;
				}
			}
			// Redraw edge and clean up area.
			SGUI_Basic_DrawRectangle(pProcessBarData->Parameter.PosX, pProcessBarData->Parameter.PosY, pProcessBarData->Parameter.Width, pProcessBarData->Parameter.Height, GUI_COLOR_FRGCLR, eBackColor);
			// Draw process block.
			SGUI_Basic_DrawRectangle(uiProcessBlockStartX, uiProcessBlockStartY, uiProcessBlockWidth, uiProcessBlockHeight, eFillColor, eFillColor);
		}
	}
}
