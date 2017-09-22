#ifndef __INCLUDE_GUI_BASIC__
#define __INCLUDE_GUI_BASIC__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Config.h"
#include "SGUI_Common.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
	GUI_COLOR_BKGCLR = 0,
	GUI_COLOR_FRGCLR = 1,
	GUI_COLOR_TRANS	 = 2,
}SGUI_COLOR;

typedef enum
{
	GUI_DRAW_NORMAL = 0,
	GUI_DRAW_REVERSE = 1,
}SGUI_DRAW_MODE;

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		BASIC_FONT_HEIGHT				(8)
#define		BASIC_FONT_WIDTH				(6)
#define		BASIC_FONT_CHAR_DATA_SIZE		(((BASIC_FONT_HEIGHT-1)/8)+1)*BASIC_FONT_WIDTH
#define		BASIC_FONT_DATA					(SGUI_BASIC_FONT_H8)

#define		GET_BIT(PAGE, Bit)		((((PAGE) & (0x01 << (Bit)))>0)?1:0)

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern SGUI_CBYTE		SGUI_BASIC_FONT_H8[];
extern SGUI_CBYTE		SGUI_BASIC_FONT_H6[];

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void					SGUI_Basic_ClearScreen(void);
void					SGUI_Basic_DrawPoint(SGUI_UINT uiPosX, SGUI_UINT uiPosY, SGUI_COLOR eColor);
void					SGUI_Basic_DrawLine(SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiEndX, SGUI_UINT uiEndY, SGUI_COLOR eColor);
void					SGUI_Basic_DrawRectangle(SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void					SGUI_Basic_DrawCircle(SGUI_UINT uiCx, SGUI_UINT uiCy, SGUI_UINT uiRadius, SGUI_COLOR eEdgeColor, SGUI_COLOR eFillColor);
void					SGUI_Basic_ReverseBlockColor(SGUI_UINT uiStartX, SGUI_UINT uiStartY, SGUI_UINT uiWidth, SGUI_UINT uiHeight);
void					SGUI_Basic_DrawBitMap(SGUI_RECT_AREA* pstDisplayArea, SGUI_RECT_AREA* pstDataArea, SGUI_BYTE* pDataBuffer, SGUI_DRAW_MODE eDrawMode);

#endif
