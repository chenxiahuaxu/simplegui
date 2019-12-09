#ifndef __INCLUDE_SGUI_List_H__
#define __INCLUDE_SGUI_List_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
#include "SGUI_ScrollBar.h"
#include "SGUI_ItemsBase.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//

typedef struct
{
	SGUI_RECT_AREA				stLayout;
	SGUI_ITEMS_BASE				stItems;
	SGUI_CSZSTR					szTitle;
	SGUI_SCROLLBAR_STRUCT*		pstScrollBar;
	const SGUI_FONT_RES*        pstFontRes;
}SGUI_LIST_CONTROL;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			SGUI_List_Initialize(SGUI_LIST_CONTROL* pstObj, const SGUI_FONT_RES* pstFontRes);
void			SGUI_List_BindItemsData(SGUI_LIST_CONTROL* pstObj, SGUI_ITEMS_ITEM* pstItemsData, SGUI_INT iItemsCount);
void			SGUI_List_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_LIST_CONTROL* pstObj);

#endif // __INCLUDE_SGUI_List_H__
