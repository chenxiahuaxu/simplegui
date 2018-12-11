/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Notice.c												**/
/** Author: XuYulin														**/
/** Version: 1.0.0.0													**/
/** Description: Notice box display interface.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
#include "SGUI_Notice.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
// User settings
#define NOTICE_FONT_SIZE				(SGUI_FONT_SIZE_H12)
#define NOTICE_BOX_EDGE_DIST			(6)
#define NOTICE_BOX_MARGIN				(2)

// Automatic calculation
#define NOTICE_BOX_WIDTH				(LCD_SIZE_WIDTH-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT_MIN			(g_stFontSize[NOTICE_FONT_SIZE].Height*2+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_HEIGHT_MAX			(LCD_SIZE_HEIGHT-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT(LINES)		(LINES*g_stFontSize[NOTICE_FONT_SIZE].Height+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_POSX					(NOTICE_BOX_EDGE_DIST)
#define NOTICE_BOX_POSY(HEIGHT)			((LCD_SIZE_HEIGHT-HEIGHT)/2)
#define NOTICE_TEXT_AREA_WIDTH_NOICON	(NOTICE_BOX_WIDTH-NOTICE_BOX_MARGIN*4)
#define	NOTICE_TEXT_AREA_WIDTH			(NOTICE_TEXT_AREA_WIDTH_NOICON-NOTICE_ICON_SIZE-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT(LINES)	(NOTICE_BOX_HEIGHT(LINES)-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT_MIN		(g_stFontSize[NOTICE_FONT_SIZE].Height*2)
#define NOTICE_TEXT_AREA_HEIGHT_MAX		(NOTICE_BOX_HEIGHT_MAX-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX_NOICON			(NOTICE_BOX_POSX+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX				(NOTICE_TEXT_POSX_NOICON+NOTICE_ICON_SIZE+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSY(HEIGHT)		(NOTICE_BOX_POSY(HEIGHT)+NOTICE_BOX_MARGIN)
#define	NOTICE_TEXT_LINES_MAX			(NOTICE_TEXT_AREA_WIDTH/g_stFontSize[NOTICE_FONT_SIZE].Width)
#define	NOTICE_TEXT_LINES_MAX_NOICON	(NOTICE_TEXT_AREA_WIDTH_NOICON/g_stFontSize[NOTICE_FONT_SIZE].Width)

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Notice_RefreshNotice							**/
/** Purpose:		Show a notice box.									**/
/** Params:																**/
/** Params:																**/
/**	@ pstIFObj[in]:		SimpleGUI object pointer.						**/
/**	@ szNoticeText[in]:	Notice text.									**/
/**	@ uiTextOffset[in]:	Text top offset.								**/
/**	@ eIcon[in]:		Notice icon index.								**/
/** Return:			Remaining text height display.						**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_SIZE SGUI_Notice_Refresh(SGUI_IF_OBJ* pstIFObj, SGUI_PCSZSTR szNoticeText, SGUI_INT uiTextOffset, SGUI_NOTICE_ICON eIcon)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiLineCount;
	SGUI_SIZE					uiNoticeBoxHeight;
	SGUI_SIZE					uiTextLines;
	SGUI_RECT_AREA				stTextDisplayArea;
	SGUI_RECT_AREA				stIconDisplayArea, stIconDataArea;
	SGUI_PCSZSTR				pszNoticeTextPtr;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Encode string if defined.
	pszNoticeTextPtr = szNoticeText;
	// Get max line of notice text.
	if(SGUI_ICON_NONE != eIcon)
	{
		uiLineCount = SGUI_Text_GetMultiLineTextLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX);
	}
	else
	{
		uiLineCount = SGUI_Text_GetMultiLineTextLines(pszNoticeTextPtr, NOTICE_TEXT_LINES_MAX_NOICON);
	}
	if(uiLineCount < 2)
	{
		uiLineCount = 2;
	}
	uiNoticeBoxHeight = NOTICE_BOX_HEIGHT(uiLineCount);
	if(uiNoticeBoxHeight > NOTICE_BOX_HEIGHT_MAX)
	{
		uiNoticeBoxHeight = NOTICE_BOX_HEIGHT_MAX;
	}
	// Draw edge
    SGUI_Basic_DrawRectangle(pstIFObj, NOTICE_BOX_POSX, NOTICE_BOX_POSY(uiNoticeBoxHeight), NOTICE_BOX_WIDTH, uiNoticeBoxHeight, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
    // Draw icon if exists.
    if(SGUI_ICON_NONE != eIcon)
	{
		stIconDisplayArea.PosX = NOTICE_BOX_POSX+NOTICE_BOX_MARGIN;
		stIconDisplayArea.PosY = NOTICE_BOX_POSY(uiNoticeBoxHeight)+NOTICE_BOX_MARGIN;
		stIconDisplayArea.Width = NOTICE_ICON_SIZE;
		stIconDisplayArea.Height = NOTICE_ICON_SIZE;
		stIconDataArea.PosX = 0;
		stIconDataArea.PosY = 0;
		stIconDataArea.Width = NOTICE_ICON_SIZE;
		stIconDataArea.Height = NOTICE_ICON_SIZE;
		#if NOTICE_ICON_SIZE == 16
		SGUI_Basic_DrawBitMap(pstIFObj, &stIconDisplayArea, &stIconDataArea, SGUI_NOTICE_ICON_16PIX, eIcon*(NOTICE_ICON_SIZE*(NOTICE_ICON_SIZE/8)), SGUI_DRAW_NORMAL);
		#elif NOTICE_ICON_SIZE == 24
		SGUI_Basic_DrawBitMap(&stIconDisplayArea, &stIconDataArea, SGUI_NOTICE_ICON_24PIX, eIcon*(NOTICE_ICON_SIZE*(NOTICE_ICON_SIZE/8)), SGUI_DRAW_NORMAL);
		#endif
	}
    // Draw text;
    if(SGUI_ICON_NONE != eIcon)
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH;
	}
	else
	{
		stTextDisplayArea.PosX = NOTICE_TEXT_POSX_NOICON;
		stTextDisplayArea.Width = NOTICE_TEXT_AREA_WIDTH_NOICON;;
	}
	stTextDisplayArea.PosY = NOTICE_TEXT_POSY(uiNoticeBoxHeight);
	stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT(uiLineCount);
    if(stTextDisplayArea.Height > NOTICE_TEXT_AREA_HEIGHT_MAX)
	{
		stTextDisplayArea.Height = NOTICE_TEXT_AREA_HEIGHT_MAX;
	}

    uiTextLines = SGUI_Text_DrawMultipleLinesText(pstIFObj, pszNoticeTextPtr, NOTICE_FONT_SIZE, &stTextDisplayArea, uiTextOffset, SGUI_DRAW_NORMAL);

    return uiTextLines;
}




