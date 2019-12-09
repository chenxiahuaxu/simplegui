#ifndef __INCLUDE_GUI_VARIABLEBOX_H__
#define __INCLUDE_GUI_VARIABLEBOX_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct
{
	SGUI_RECT_AREA			stLayout;
	const SGUI_FONT_RES*	pstFontRes;
	SGUI_INT				Min;
	SGUI_INT				Max;
	SGUI_INT				Value;
}SGUI_NUM_VARBOX_STRUCT;

typedef struct
{
	SGUI_RECT_AREA			stLayout;
	const SGUI_FONT_RES*	pstFontRes;
	SGUI_SIZE				sFocusIndex;
	SGUI_SIZE				sMaxTextLength;
	SGUI_SZSTR				szValue;
}SGUI_TEXT_VARBOX_STRUCT;

enum
{
	SGUI_TEXT_NUMBER		= 0x0100,
	SGUI_TEXT_ALPHA			= 0x0200,
	SGUI_TEXT_PUNCTUATION	= 0x0400,
	SGUI_TEXT_DATE			= 0x0800,
	SGUI_TEXT_TIME			= 0x1000,
};

typedef enum
{
    SGUI_TXT_VARBOX_OPT_PREV = -1,
    SGUI_TXT_VARBOX_OPT_NONE = 0,
    SGUI_TXT_VARBOX_OPT_NEXT = 1,
}SGUI_TEXT_VARBOX_OPT;

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define VARBOX_WIDTH(FONT_SIZE, L)		(L*(g_stFontSize[FONT_SIZE].Width)-4)
#define VARBOX_HEIGHT(FONT_SIZE)		(g_stFontSize[FONT_SIZE].Height+2)
#define VARBOX_TEXT_AREA_WIDTH(W)		((W>2)?(W-2):0)
#define VARBOX_TEXT_AREA_HEIGHT(FONT_SIZE) (g_stFontSize[FONT_SIZE].Height)

#define VARBOX_TEXT_LENGTH_MAX			(11)
#define VARBOX_TEXT_BUFFER_SIZE			(VARBOX_TEXT_LENGTH_MAX+1)
#define VARBOX_TEXT_WIDTH(FONT_SIZE, L)	(L*(g_stFontSize[FONT_SIZE].Width))

#define SGUI_TEXT_ASCII					(SGUI_TEXT_NUMBER|SGUI_TEXT_ALPHA|SGUI_TEXT_PUNCTUATION)

#define GUI_TEXT_ISLOWER(C)				((C>='a' && C<='z')?true:false)
#define GUI_TEXT_ISALPHA(C)				(SGUI_IS_UPPER(C) || GUI_TEXT_ISLOWER(C))
#define GUI_TEXT_ISASCII(C)				((C>=0x20 && C<=0x7E)?true:false)

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			SGUI_NumberVariableBox_Paint(SGUI_SCR_DEV* pstIFObj, SGUI_NUM_VARBOX_STRUCT* pstValue, SGUI_ALIG_MODE eAlignment, SGUI_DRAW_MODE eMode);
void			SGUI_TextVariableBox_Paint(SGUI_SCR_DEV* pstIFObj, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode);
void			SGUI_TextVariableBox_ChangeCharacter(SGUI_SCR_DEV* pstIFObj, SGUI_TEXT_VARBOX_STRUCT* pstTextValue, SGUI_DRAW_MODE eMode, SGUI_UINT uiCharacterSet, SGUI_TEXT_VARBOX_OPT eOpt);



#endif // __INCLUDE_GUI_VARIABLEBOX_H__
