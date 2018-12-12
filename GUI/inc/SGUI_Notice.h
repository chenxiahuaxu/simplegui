#ifndef __INCLUDE_GUI_NOTICE_H__
#define __INCLUDE_GUI_NOTICE_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
//#define		NOTICE_ICON_SIZE				(24)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
	SGUI_ICON_ERROR =			0,
	SGUI_ICON_INFORMATION,
	SGUI_ICON_QUESTION,
	SGUI_ICON_WARNING,
	SGUI_ICON_NONE,
}SGUI_NOTICE_ICON;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE SGUI_Notice_Refresh(SGUI_IF_OBJ* pstIFObj, SGUI_CSZSTR szNoticeText, SGUI_INT uiTextOffset, SGUI_NOTICE_ICON eIcon);

#endif // __INCLUDE_GUI_NOTICE_H__
