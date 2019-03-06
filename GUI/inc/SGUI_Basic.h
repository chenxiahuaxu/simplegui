#ifndef __INCLUDE_GUI_BASIC__
#define __INCLUDE_GUI_BASIC__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_FlashData.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//


//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		BASIC_FONT_HEIGHT				(8)
#define		BASIC_FONT_WIDTH				(6)
#define		BASIC_FONT_CHAR_DATA_SIZE		(((BASIC_FONT_HEIGHT-1)/8)+1)*BASIC_FONT_WIDTH
#define		BASIC_FONT_DATA					(SGUI_BASIC_FONT_H8)

//Bitmap(include font) data bit operation
#define     SGUI_SET_PAGE_BIT(PAGE, Bit)	((PAGE) = (PAGE) | (0x01 << (Bit)))
#define     SGUI_CLR_PAGE_BIT(PAGE, Bit)	((PAGE) = (PAGE) & (~(0x01 << (Bit))))
#define     SGUI_GET_PAGE_BIT(PAGE, Bit)	((((PAGE) & (0x01 << (Bit)))>0)?1:0)

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern SGUI_CBYTE		SGUI_BASIC_FONT_H8[];
extern SGUI_CBYTE		SGUI_BASIC_FONT_H6[];

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void					SGUI_Basic_ClearScreen(SGUI_SCR_DEV* pstIFObj);
void					SGUI_Basic_DrawPoint(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiPosX, SGUI_UINT uiPosY, SGUI_COLOR eColor);
void					SGUI_Basic_DrawLine(SGUI_SCR_DEV* pstIFObj, SGUI_INT uiStartX, SGUI_INT uiStartY, SGUI_INT uiEndX, SGUI_INT uiEndY, SGUI_COLOR eColor);
void					SGUI_Basic_DrawRectangle(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void					SGUI_Basic_DrawCircle(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiCx, SGUI_UINT uiCy, SGUI_UINT uiRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void					SGUI_Basic_ReverseBlockColor(SGUI_SCR_DEV* pstIFObj, SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight);
void					SGUI_Basic_DrawBitMap(SGUI_SCR_DEV* pstIFObj, SGUI_RECT_AREA* pstDisplayArea, SGUI_RECT_AREA* pstDataArea, SGUI_FLASH_DATA_SOURCE eDataSource, SGUI_ROM_ADDRESS adDataStartAddr, SGUI_DRAW_MODE eDrawMode);

#endif
