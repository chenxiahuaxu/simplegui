#ifndef __INCLUDE_SGUI_List_H__
#define __INCLUDE_SGUI_List_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"
#include "SGUI_Text.h"
#include "SGUI_ScrollBar.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
	LIST_ITEM_NORMAL =			0,
	LIST_ITEM_ENUM,
	LIST_ITEM_DIGIT,
	LIST_ITEM_DATE,
	LIST_ITEM_TIME
}SGUI_List_ITEM_TYPE;

typedef struct
{
	SGUI_INT32					Value;
	SGUI_INT32					Min;
	SGUI_INT32					Max;
	SGUI_INT32					*Bind;
}SGUI_List_PARAMETER_VALUE;

typedef struct _st_sgui_list_item_
{
	SGUI_SIZE					Sign;
	SGUI_CSZSTR				Text;
	SGUI_List_ITEM_TYPE			Type;
	SGUI_List_PARAMETER_VALUE	Valid;
	SGUI_List_PARAMETER_VALUE	Decimal;
    SGUI_CSZSTR*				EnumerationValues;
    SGUI_SIZE					EnumerationCount;
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
	struct _st_sgui_list_item_	*PrevItem;
    struct _st_sgui_list_item_	*NextItem;
#endif
}SGUI_List_ITEM;

typedef struct
{
	SGUI_UINT16					ListTitleHeight;				// Read only
	SGUI_UINT16					VisibleItemsAreaHeight;			// Read only
	SGUI_UINT16					ListItemHeight;					// Read only
	SGUI_UINT16					FirstVisibleItemPosY;			// Read only
	SGUI_UINT16					VisibleIntegralItemsNum;		// Read only
	SGUI_UINT16					VisibleItemsNum;				// Read only
	SGUI_SIZE					SelectIndex;					// Control
	SGUI_SIZE					PageStartIndex;					// Control
	SGUI_UINT16					ItemPosYOffSet;					// Control
}SGUI_List_CONTROL;

typedef struct
{
	SGUI_CSZSTR				Title;
	SGUI_SIZE					Count;
	SGUI_List_ITEM*				Items;
}SGUI_List_DATA;

typedef struct
{
	SGUI_SCROLLBAR_STRUCT		ScrollBar;
}SGUI_List_SUBELEMENT;

typedef struct
{
	SGUI_List_DATA				Data;
	SGUI_List_CONTROL			ControlVariable;
	SGUI_List_SUBELEMENT		SubElement;
	SGUI_FONT_SIZE	            FontSize;
}SGUI_List_STRUCT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			SGUI_List_InitializeListData(SGUI_List_STRUCT* pstList);
void			SGUI_List_Refresh(SGUI_SCR_DEV* pstIFObj, SGUI_List_STRUCT* pstList);
void			SGUI_List_SelectUpItem(SGUI_SCR_DEV* pstIFObj, SGUI_List_STRUCT* pstList);
void			SGUI_List_SelectDownItem(SGUI_SCR_DEV* pstIFObj, SGUI_List_STRUCT* pstList);
void			SGUI_List_SetListItemValue(SGUI_SCR_DEV* pstIFObj, SGUI_List_STRUCT* pstList, SGUI_INDEX iItemIndex, SGUI_INT32 iSetValid, SGUI_INT32 iSetDecimal);
void			SGUI_List_GetListItemValue(SGUI_List_STRUCT* pstList, SGUI_INDEX iItemIndex, SGUI_INT32 *piValid, SGUI_INT32 *piDecimal);
SGUI_List_ITEM*	SGUI_List_GetListItemPtr(SGUI_List_STRUCT* pstList, SGUI_INDEX iItemIndex);
void			SGUI_List_BindData(SGUI_List_STRUCT* pstList, SGUI_INDEX iItemIndex, SGUI_INT32* piValid, SGUI_INT32* piDecimal);
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
SGUI_BOOL		SGUI_List_InsertItem(SGUI_List_STRUCT* pstList, SGUI_List_ITEM* pstNewItem, SGUI_INDEX iNewItemIndex);
SGUI_BOOL		SGUI_List_RemoveItem(SGUI_List_STRUCT* pstList, SGUI_INDEX iItemIndex);
#endif

#endif // __INCLUDE_SGUI_List_H__
