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
//#define		NOTICE_ICON_SIZE				(24)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE SGUI_Notice_Repaint(SGUI_SCR_DEV* pstIFObj, SGUI_CSZSTR szNoticeText, const SGUI_FONT_RES* pstFontRes, SGUI_INT uiTextOffset, SGUI_NOTICE_ICON_IDX eIcon);

#endif // __INCLUDE_GUI_NOTICE_H__
