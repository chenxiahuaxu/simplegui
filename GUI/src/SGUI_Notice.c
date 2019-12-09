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
#include "SGUI_Notice.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
// User settings
#define NOTICE_BOX_EDGE_DIST								(6)
#define NOTICE_BOX_MARGIN									(2)

// Automatic calculation
#define NOTICE_BOX_WIDTH(SCR_OBJ)							(((SCR_OBJ).stSize.Width)-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT_MIN(FONT_SIZE)					(g_stFontSize[FONT_SIZE].Height*2+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_HEIGHT_MAX(SCR_OBJ)						(((SCR_OBJ).stSize.Height)-NOTICE_BOX_EDGE_DIST*2)
#define NOTICE_BOX_HEIGHT(LINES, FONT_SIZE)					(LINES*g_stFontSize[FONT_SIZE].Height+NOTICE_BOX_MARGIN*2)
#define NOTICE_BOX_POSX										(NOTICE_BOX_EDGE_DIST)
#define NOTICE_BOX_POSY(SCR_OBJ, HEIGHT)					((((SCR_OBJ).stSize.Height)-HEIGHT)/2)
#define NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)				(NOTICE_BOX_WIDTH(SCR_OBJ)-NOTICE_BOX_MARGIN*4)
#define	NOTICE_TEXT_AREA_WIDTH(SCR_OBJ)						(NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)-NOTICE_ICON_SIZE-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT(LINES, FONT_SIZE)			(NOTICE_BOX_HEIGHT(LINES, FONT_SIZE)-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_AREA_HEIGHT_MIN(FONT_SIZE)				(g_stFontSize[FONT_SIZE].Height*2)
#define NOTICE_TEXT_AREA_HEIGHT_MAX(SCR_OBJ)				(NOTICE_BOX_HEIGHT_MAX(SCR_OBJ)-NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX_NOICON								(NOTICE_BOX_POSX+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSX									(NOTICE_TEXT_POSX_NOICON+NOTICE_ICON_SIZE+NOTICE_BOX_MARGIN*2)
#define NOTICE_TEXT_POSY(SCR_OBJ, HEIGHT)					(NOTICE_BOX_POSY(SCR_OBJ, HEIGHT)+NOTICE_BOX_MARGIN)
#define	NOTICE_TEXT_LINES_MAX(SCR_OBJ, FONT_WIDTH)			(NOTICE_TEXT_AREA_WIDTH(SCR_OBJ)/FONT_WIDTH)
#define	NOTICE_TEXT_LINES_MAX_NOICON(SCR_OBJ, FONT_WIDTH)	(NOTICE_TEXT_AREA_WIDTH_NOICON(SCR_OBJ)/FONT_WIDTH)

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Notice_RefreshNotice							**/
/** Purpose:		Show a notice box.									**/
/** Params:																**/
/** Params:																**/
/**	@ pstIFObj[in]:		SimpleGUI object pointer.						**/
/**	@ pstObject[in]:	Object structure pointer.						**/
/** @ pstFontRes[in]:	Text font resource.								**/
/**	@ uiTextOffset[in]:	Text top offset.								**/
/** Return:			Remaining text height display.						**/
/** Notice:			None.												**/
/*************************************************************************/
SGUI_SIZE SGUI_Notice_Repaint(SGUI_SCR_DEV* pstIFObj, SGUI_NOTICT_BOX* pstObject, const SGUI_FONT_RES* pstFontRes, SGUI_INT uiTextOffset)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiTextLines;
	SGUI_RECT_AREA				stIconDisplayArea;
	SGUI_POINT					stIconPosition;
	SGUI_RECT_AREA				stTextDisplayArea;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObject) && (NULL != pstObject->cszNoticeText))
	{
		// Draw edge
		SGUI_Basic_DrawRectangle(pstIFObj, pstObject->stLayout.iPosX, pstObject->stLayout.iPosY, pstObject->stLayout.iWidth, pstObject->stLayout.iHeight, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);

		stTextDisplayArea.iPosY = pstObject->stLayout.iPosY+2;
		stTextDisplayArea.iHeight = pstObject->stLayout.iHeight-4;
		if(NULL == pstObject->pstIcon)
		{
			stTextDisplayArea.iPosX = pstObject->stLayout.iPosX+2;
			stTextDisplayArea.iWidth = pstObject->stLayout.iWidth-4;
		}
		else
		{
			stTextDisplayArea.iPosX = pstObject->stLayout.iPosX+pstObject->pstIcon->iWidth+4;
			stTextDisplayArea.iWidth = pstObject->stLayout.iWidth-pstObject->pstIcon->iWidth-6;

			stIconDisplayArea.iPosX = pstObject->stLayout.iPosX+2;
			stIconDisplayArea.iPosY = pstObject->stLayout.iPosY+2;
			stIconDisplayArea.iWidth = pstObject->pstIcon->iWidth;
			stIconDisplayArea.iHeight = pstObject->pstIcon->iHeight;
			stIconPosition.iPosX = 0;
			stIconPosition.iPosY = 0;
			// Paint icon.
			SGUI_Basic_DrawBitMap(pstIFObj, &stIconDisplayArea, &stIconPosition, pstObject->pstIcon, SGUI_DRAW_NORMAL);
		}
		// Draw text;
		uiTextLines = SGUI_Text_DrawMultipleLinesText(pstIFObj, pstObject->cszNoticeText, pstFontRes, &stTextDisplayArea, uiTextOffset, SGUI_DRAW_NORMAL);
	}
    return uiTextLines;
}




