/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_VariableBox.c										**/
/** Author: XuYulin														**/
/** Description: Show and change variable box.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_VariableBox.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	GUI_RefreshVariableBox								**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstIFObj[in]:	Device driver object pointer.						**/
/**	@ pstValue[in]:	Value structure, include max value, min value and	**/
/**					current value.										**/
/**	@ eAlignment[in]: Alignment mode, might be right, center or left.	**/
/**	@ eMode[in]:	Display mode, normal or reveres.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_NumberVariableBox_Paint(SGUI_SCR_DEV* pstIFObj, SGUI_NUM_VARBOX_STRUCT* pstValue, SGUI_ALIG_MODE eAlignment, SGUI_DRAW_MODE eMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_AREA_SIZE				stTextExtentSize;
	SGUI_POINT					stTextInnerPos;
	SGUI_COLOR					eBackColor;
	SGUI_CHAR					szTextBuffer[VARBOX_TEXT_BUFFER_SIZE];

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	SGUI_SystemIF_MemorySet(szTextBuffer, 0x00, VARBOX_TEXT_BUFFER_SIZE);
	eBackColor =				((eMode==SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR);
	// Draw edge
	SGUI_Basic_DrawRectangle(pstIFObj, pstValue->stLayout.iPosX, pstValue->stLayout.iPosY, pstValue->stLayout.iWidth, pstValue->stLayout.iHeight, eBackColor, eBackColor);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if(NULL != pstValue)
	{
		// Check value limited.
		if(pstValue->Value > pstValue->Max)
		{
			pstValue->Value = pstValue->Max;
		}
		if(pstValue->Value < pstValue->Min)
		{
			pstValue->Value = pstValue->Min;
		}
		// Convert number to string
		(void)SGUI_Common_IntegerToString(pstValue->Value, szTextBuffer, 10, -1, ' ');
		SGUI_Text_GetTextExtent(szTextBuffer, pstValue->pstFontRes, &stTextExtentSize);
		switch(eAlignment)
		{
			case SGUI_RIGHT:
			{
				stTextInnerPos.iPosX = pstValue->stLayout.iWidth - stTextExtentSize.iWidth;
				break;
			}
			case SGUI_CENTER:
			{
				stTextInnerPos.iPosX = (pstValue->stLayout.iWidth - stTextExtentSize.iWidth) / 2;
				break;
			}
			default:
			{
				stTextInnerPos.iPosX = 0;
			}
		}
		stTextInnerPos.iPosY = 0;
		SGUI_Text_DrawText(pstIFObj, szTextBuffer, pstValue->pstFontRes, &(pstValue->stLayout), &stTextInnerPos, eMode);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_TextVariableBox_Paint							**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstIFObj[in]:	Device driver object pointer.						**/
/** @ pstTextValue[in]:	Text value edit box pointer.					**/
/** @ cNewCharacters[in]: New character of value.						**/
/**	@ eMode[in]:			Display mode, normal or reveres.			**/
/** Return:			None.												**/
/** Notice:			Static function, call by others interface.			**/
/*************************************************************************/
void SGUI_TextVariableBox_Paint(SGUI_SCR_DEV* pstIFObj, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_COLOR					eBackColor;
	SGUI_POINT					stTextInnerPos;
	SGUI_RECT_AREA				stFocusArea;
	SGUI_UINT16					uiFontWidth, uiFontHeight;
	SGUI_SIZE					uiTextLength, uiFocusIndexMax;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eBackColor =				((eMode==SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR);
	if(NULL != pstTextValue->szValue)
	{
		// Clear background.
		SGUI_Basic_DrawRectangle(pstIFObj, pstTextValue->stLayout.iPosX, pstTextValue->stLayout.iPosY, pstTextValue->stLayout.iWidth, pstTextValue->stLayout.iHeight, eBackColor, eBackColor);
		// Get font graphics size.
		uiFontWidth =				pstTextValue->pstFontRes->iHalfWidth;
		uiFontHeight =				pstTextValue->pstFontRes->iHeight;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstTextValue) && (NULL != pstTextValue->szValue))
	{
		// Get max text length and graphics width.
		uiFocusIndexMax = pstTextValue->sMaxTextLength-1;
		// Ignore too long text string.
		uiTextLength = SGUI_SystemIF_StringLength(pstTextValue->szValue);
		if(uiTextLength > pstTextValue->sMaxTextLength)
		{
			uiTextLength = pstTextValue->sMaxTextLength;
			*(pstTextValue->szValue+uiTextLength) = '\0';
            // Point at to last character position if index is more then string length.
			if(pstTextValue->sFocusIndex > uiFocusIndexMax)
			{
				pstTextValue->sFocusIndex = uiFocusIndexMax;
			}
		}
		// Set text display area.
		stTextInnerPos.iPosX = 0;
		stTextInnerPos.iPosY = 0;
		// Set focus character area.
		stFocusArea.iPosX = pstTextValue->stLayout.iPosX+pstTextValue->sFocusIndex*uiFontWidth;
		stFocusArea.iPosY = pstTextValue->stLayout.iPosY;
		stFocusArea.iWidth = uiFontWidth;
		stFocusArea.iHeight = uiFontHeight;
		if(RECT_X_END(stFocusArea, stFocusArea) > RECT_X_END(pstTextValue->stLayout, pstTextValue->stLayout))
		{
			stTextInnerPos.iPosX = RECT_X_END(pstTextValue->stLayout, pstTextValue->stLayout) - RECT_X_END(stFocusArea, stFocusArea);
			stFocusArea.iPosX = stFocusArea.iPosX + stTextInnerPos.iPosX;
		}
		// Display text.
		SGUI_Text_DrawText(pstIFObj, pstTextValue->szValue, pstTextValue->pstFontRes, &(pstTextValue->stLayout), &stTextInnerPos, eMode);
		// Focus first character.
        SGUI_Basic_ReverseBlockColor(pstIFObj, stFocusArea.iPosX, stFocusArea.iPosY, stFocusArea.iWidth, stFocusArea.iHeight);
	}
}

/*************************************************************************/
/** Function Name:	GUI_TextVariableBox_PrevCharacter					**/
/** Purpose:		Select previous character at current index.			**/
/** Params:																**/
/** @pstTextValue[in]:	Text value edit box pointer.					**/
/**	@eMode[in]:			Display mode, normal or reveres.				**/
/**	@uiCharacterSet[in]: Mask of characters set.						**/
/** @eOpt[in]:			Operation.										**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_TextVariableBox_ChangeCharacter(SGUI_SCR_DEV* pstIFObj, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode, SGUI_UINT uiCharacterSet, SGUI_TEXT_VARBOX_OPT eOpt)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_CHAR					cCurChar;
	SGUI_BOOL					bUpdated;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	cCurChar					= '\0';
	bUpdated					= SGUI_FALSE;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstTextValue)
	{
		if(NULL != pstTextValue->szValue)
		{
			cCurChar = *(pstTextValue->szValue+pstTextValue->sFocusIndex);
			while(SGUI_FALSE == bUpdated)
			{
				cCurChar += (SGUI_INT)eOpt;
				if(cCurChar > 0x7E)
				{
					cCurChar = 0x20;
				}
				if(cCurChar < 0x20)
				{
					cCurChar = 0x7E;
				}
				if(SGUI_ISDIGIT(cCurChar) || ('.' == cCurChar) || ('-' == cCurChar))
				{
					if(uiCharacterSet & SGUI_TEXT_NUMBER)
					{
						bUpdated = SGUI_TRUE;
					}
				}
				if(SGUI_ISALPHA(cCurChar))
				{
					if(uiCharacterSet & SGUI_TEXT_ALPHA)
					{
						bUpdated = SGUI_TRUE;
					}
				}
				if((!SGUI_ISDIGIT(cCurChar)) && (!(SGUI_ISALPHA(cCurChar))))
				{
					if(uiCharacterSet & SGUI_TEXT_PUNCTUATION)
					{
						bUpdated = SGUI_TRUE;
					}
				}
			}
			pstTextValue->szValue[pstTextValue->sFocusIndex] = cCurChar;
			SGUI_TextVariableBox_Paint(pstIFObj, pstTextValue, eMode);
		}
	}
}
