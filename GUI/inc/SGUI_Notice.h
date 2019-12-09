#ifndef __INCLUDE_GUI_NOTICE_H__
#define __INCLUDE_GUI_NOTICE_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct
{
    SGUI_CSZSTR			cszNoticeText;
    const SGUI_BMP_RES*	pstIcon;
    SGUI_RECT_AREA		stLayout;
}SGUI_NOTICT_BOX;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE SGUI_Notice_Repaint(SGUI_SCR_DEV* pstIFObj, SGUI_NOTICT_BOX* pstObject, const SGUI_FONT_RES* pstFontRes, SGUI_INT uiTextOffset);

#endif // __INCLUDE_GUI_NOTICE_H__
