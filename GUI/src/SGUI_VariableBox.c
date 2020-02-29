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
/** Function Name:	SGUI_NumberVariableBox_Initialize					**/
/** Purpose:		Initialize a integer value edit box structure.		**/
/** Params:																**/
/**	@ pstObj[in]:	Number variable box object pointer.					**/
/**	@ pcstLayout[in]: Object layout.									**/
/**	@ pcstParam[in]: Initialize parameter for initialize.				**/
/** Return:			None.												**/
/** Notice:			iValue will be changed when more then max value or	**/
/**					less then minimum value.							**/
/*************************************************************************/
void SGUI_NumberVariableBox_Initialize(SGUI_NUM_VARBOX_STRUCT* pstObj, const SGUI_RECT* pcstLayout, const SGUI_NUM_VARBOX_PARAM* pcstParam)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pcstLayout))
	{
		SGUI_SystemIF_MemorySet(pstObj, 0x00, sizeof(SGUI_NUM_VARBOX_STRUCT));
		SGUI_SystemIF_MemoryCopy(&(pstObj->stLayout), (void*)pcstLayout, sizeof(SGUI_RECT));
		SGUI_SystemIF_MemoryCopy(&(pstObj->stParam), (void*)pcstParam, sizeof(SGUI_NUM_VARBOX_PARAM));
	}
}

/*************************************************************************/
/** Function Name:	SGUI_NumberVariableBox_SetValue						**/
/** Purpose:		Set a variable box structure value.					**/
/** Params:																**/
/**	@ pstObj[in]:	Number variable box object pointer.					**/
/**	@ iNewValue[in]: New value will be set.								**/
/** Return:			None.												**/
/** Notice:			For update screen display, repaint function must be **/
/**					called after this function.							**/
/*************************************************************************/
void SGUI_NumberVariableBox_SetValue(SGUI_NUM_VARBOX_STRUCT* pstObj, const SGUI_INT iNewValue)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstObj)
	{
		if((iNewValue <= pstObj->stParam.iMax) && (iNewValue >= pstObj->stParam.iMin))
		{
			pstObj->stData.iValue = iNewValue;
		}
	}
}

/*************************************************************************/
/** Function Name:	SGUI_NumberVariableBox_GetValue						**/
/** Purpose:		Get a variable box structure value.					**/
/** Params:																**/
/**	@ pstObj[in]:	Number variable box object pointer.					**/
/** Return:			Current value of the variable box.					**/
/*************************************************************************/
SGUI_INT SGUI_NumberVariableBox_GetValue(SGUI_NUM_VARBOX_STRUCT* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT				iReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iReturn =				0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstObj)
	{
		iReturn = pstObj->stData.iValue;
	}

	return iReturn;
}

/*************************************************************************/
/** Function Name:	GUI_RefreshVariableBox								**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	Device driver object pointer.					**/
/**	@ pstObj[in]:	Value structure, include max value, min value and	**/
/**					current value.										**/
/**	@ eMode[in]:	Display mode, normal or reveres.					**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_NumberVariableBox_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_NUM_VARBOX_STRUCT* pstObj, SGUI_DRAW_MODE eMode)
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
	SGUI_Basic_DrawRectangle(pstDeviceIF, pstObj->stLayout.iPosX, pstObj->stLayout.iPosY, pstObj->stLayout.iWidth, pstObj->stLayout.iHeight, eBackColor, eBackColor);

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/

	if(NULL != pstObj)
	{
		// Convert number to string
		(void)SGUI_Common_IntegerToString(pstObj->stData.iValue, szTextBuffer, 10, -1, ' ');
		SGUI_Text_GetTextExtent(szTextBuffer, pstObj->stParam.pstFontRes, &stTextExtentSize);
		switch(pstObj->stParam.eAlignment)
		{
			case SGUI_RIGHT:
			{
				stTextInnerPos.iPosX = pstObj->stLayout.iWidth - stTextExtentSize.iWidth;
				break;
			}
			case SGUI_CENTER:
			{
				stTextInnerPos.iPosX = (pstObj->stLayout.iWidth - stTextExtentSize.iWidth) / 2;
				break;
			}
			default:
			{
				stTextInnerPos.iPosX = 0;
			}
		}
		stTextInnerPos.iPosY = 0;
		SGUI_Text_DrawText(pstDeviceIF, szTextBuffer, pstObj->stParam.pstFontRes, &(pstObj->stLayout), &stTextInnerPos, eMode);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_TextVariableBox_Paint							**/
/** Purpose:		Display or refresh a integer value edit box.		**/
/** Params:																**/
/**	@ pstDeviceIF[in]:	Device driver object pointer.						**/
/** @ pstTextValue[in]:	Text value edit box pointer.					**/
/** @ cNewCharacters[in]: New character of value.						**/
/**	@ eMode[in]:			Display mode, normal or reveres.			**/
/** Return:			None.												**/
/** Notice:			Static function, call by others interface.			**/
/*************************************************************************/
void SGUI_TextVariableBox_Paint(SGUI_SCR_DEV* pstDeviceIF, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_COLOR				eBackColor;
	SGUI_POINT				stTextInnerPos;
	SGUI_RECT				stFocusArea;
	SGUI_UINT16				uiFontWidth, uiFontHeight;
	SGUI_SIZE				uiTextLength, uiFocusIndexMax;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eBackColor =				((eMode==SGUI_DRAW_NORMAL)?SGUI_COLOR_BKGCLR:SGUI_COLOR_FRGCLR);
	if(NULL != pstTextValue->szValue)
	{
		// Clear background.
		SGUI_Basic_DrawRectangle(pstDeviceIF, pstTextValue->stLayout.iPosX, pstTextValue->stLayout.iPosY, pstTextValue->stLayout.iWidth, pstTextValue->stLayout.iHeight, eBackColor, eBackColor);
		// Get font graphics size.
		uiFontWidth =		pstTextValue->pstFontRes->iHalfWidth;
		uiFontHeight =		pstTextValue->pstFontRes->iHeight;
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
		if(RECT_X_END(stFocusArea) > RECT_X_END(pstTextValue->stLayout))
		{
			stTextInnerPos.iPosX = RECT_X_END(pstTextValue->stLayout) - RECT_X_END(stFocusArea);
			stFocusArea.iPosX = stFocusArea.iPosX + stTextInnerPos.iPosX;
		}
		// Display text.
		SGUI_Text_DrawText(pstDeviceIF, pstTextValue->szValue, pstTextValue->pstFontRes, &(pstTextValue->stLayout), &stTextInnerPos, eMode);
		// Focus first character.
        SGUI_Basic_ReverseBlockColor(pstDeviceIF, stFocusArea.iPosX, stFocusArea.iPosY, stFocusArea.iWidth, stFocusArea.iHeight);
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
void SGUI_TextVariableBox_ChangeCharacter(SGUI_SCR_DEV* pstDeviceIF, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode, SGUI_UINT uiCharacterSet, SGUI_TEXT_VARBOX_OPT eOpt)
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
			SGUI_TextVariableBox_Paint(pstDeviceIF, pstTextValue, eMode);
		}
	}
}
