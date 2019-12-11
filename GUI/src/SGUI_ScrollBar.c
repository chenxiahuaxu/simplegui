/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_ScrollBar.c											**/
/** Author: XuYulin														**/
/** Description: Create and display a scrollbar on screen.				**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_ScrollBar.h"

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_ScrollBar_RefreshScrollBar						**/
/** Purpose:		Display or update a scroll bar.						**/
/** Resources:		Scroll bar data structure.							**/
/** Params:																**/
/** @pstScrollBar[in]:	Scroll bar data pointer.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_ScrollBar_Repaint(SGUI_SCR_DEV* pstIFObj, SGUI_SCROLLBAR_STRUCT* pstScrollBar)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					uiScrollBlockPos;
	SGUI_SIZE					uiScrollBlockSize;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(SGUI_SCROLLBAR_VERTICAL == pstScrollBar->eDirection)
	{
		uiScrollBlockSize	= pstScrollBar->iWidth-2;
	}
	else
	{
		uiScrollBlockSize	= pstScrollBar->iHeight-2;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(((pstScrollBar->iHeight > 2) && (pstScrollBar->iWidth > 2)) && (pstScrollBar->iHeight != pstScrollBar->iWidth))
	{
		// Check new value must be less then max value.
		if(pstScrollBar->sIndex > pstScrollBar->sMaxIndex)
		{
			pstScrollBar->sIndex = pstScrollBar->sMaxIndex;
		}

		if(SGUI_SCROLLBAR_VERTICAL == pstScrollBar->eDirection)
		{
			// Draw scroll bar edge.
			SGUI_Basic_DrawRectangle(pstIFObj, pstScrollBar->iPosX, pstScrollBar->iPosY,
									pstScrollBar->iWidth, pstScrollBar->iHeight,
									SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
			// Value lower limit is 0, scroll blocks must be greater then 0.
			if(pstScrollBar->sMaxIndex > 0)
			{
				uiScrollBlockPos = pstScrollBar->iPosY+1+((pstScrollBar->iHeight-uiScrollBlockSize-2)*pstScrollBar->sIndex/pstScrollBar->sMaxIndex);
				// Redraw process block
				SGUI_Basic_DrawRectangle(pstIFObj, pstScrollBar->iPosX+1, uiScrollBlockPos,
										uiScrollBlockSize, uiScrollBlockSize, SGUI_COLOR_FRGCLR, SGUI_COLOR_FRGCLR);
			}
			else
			{
				SGUI_Basic_DrawRectangle(pstIFObj, pstScrollBar->iPosX+1, pstScrollBar->iPosY+1,
										uiScrollBlockSize, uiScrollBlockSize, SGUI_COLOR_FRGCLR, SGUI_COLOR_FRGCLR);
			}
		}
		else // Horizontal
		{
			// Draw scroll bar edge.
			SGUI_Basic_DrawRectangle(pstIFObj, pstScrollBar->iPosX, pstScrollBar->iPosY,
									pstScrollBar->iWidth, pstScrollBar->iHeight,
									SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
			// Value lower limit is 0, scroll blocks must be greater then 0.
			if(pstScrollBar->sMaxIndex > 0)
			{
				uiScrollBlockPos = pstScrollBar->iPosX+1+((pstScrollBar->iWidth-uiScrollBlockSize-2)*pstScrollBar->sIndex/pstScrollBar->sMaxIndex);
				// Redraw process block
				SGUI_Basic_DrawRectangle(pstIFObj, uiScrollBlockPos, pstScrollBar->iPosY+1,
										uiScrollBlockSize, uiScrollBlockSize, SGUI_COLOR_FRGCLR, SGUI_COLOR_FRGCLR);
			}
			else
			{
				SGUI_Basic_DrawRectangle(pstIFObj, pstScrollBar->iPosX+1, pstScrollBar->iPosY+1,
										uiScrollBlockSize, uiScrollBlockSize, SGUI_COLOR_FRGCLR, SGUI_COLOR_FRGCLR);
			}
		}
	}
}
