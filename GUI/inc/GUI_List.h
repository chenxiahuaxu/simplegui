#ifndef __INCLUDE_GUI_LIST_H__
#define __INCLUDE_GUI_LIST_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Common.h"
#include "GUI_Basic.h"
#include "GUI_Text.h"
#include "GUI_ScrollBar.h"
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
#include "LCD_VirtualDeviceParameter.h"
#else
// Insert platform display device parameter info file here.
#endif //_SIMPLE_GUI_ENABLE_SIMULATOR_


//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
	LIST_ITEM_NORMAL		= 0,
	LIST_ITEM_ENUM,
	LIST_ITEM_DIGIT,
	LIST_ITEM_DATE,
	LIST_ITEM_TIME
}GUI_LIST_ITEM_TYPE;

typedef struct
{
	int32_t						Value;
	int32_t						Min;
	int32_t						Max;
	int32_t*					Bind;
}GUI_LIST_PARAMETER_VALUE;

typedef struct _st_gui_list_item_
{
	uint32_t					Sign;
	const char*					Text;
	GUI_LIST_ITEM_TYPE			Type;
	GUI_LIST_PARAMETER_VALUE	Valid;
	GUI_LIST_PARAMETER_VALUE	Decimal;
    const char**				EnumerationValues;
    uint32_t					EnumerationCount;
#if _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
	struct _st_gui_list_item_*	PrevItem;
    struct _st_gui_list_item_*	NextItem;
#endif
}GUI_LIST_ITEM;

typedef struct
{
	uint16_t					ListTitleHeight;				// Read only
	uint16_t					VisibleItemsAreaHeight;			// Read only
	uint16_t					ListItemHeight;					// Read only
	uint16_t					FirstVisibleItemPosY;			// Read only
	uint16_t					VisibleIntegralItemsNum;		// Read only
	uint16_t					VisibleItemsNum;				// Read only
	size_t						SelectIndex;					// Control
	size_t						PageStartIndex;					// Control
	uint16_t					ItemPosYOffSet;					// Control
}GUI_LIST_CONTROL;

typedef struct
{
	char*						Title;
	size_t						Count;
	GUI_LIST_ITEM*				Items;
}GUI_LIST_DATA;

typedef struct
{
	GUI_SCROLLBAR_STRUCT		ScrollBar;
}GUI_LIST_SUBELEMENT;

typedef struct
{
	GUI_LIST_DATA				Data;
	GUI_LIST_CONTROL			ControlVariable;
	GUI_LIST_SUBELEMENT			SubElement;
}GUI_LIST_STRUCT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void			GUI_List_InitializeListData(GUI_LIST_STRUCT* pstList);
void			GUI_List_RefreshList(GUI_LIST_STRUCT* pstList);
void			GUI_List_SelectUpItem(GUI_LIST_STRUCT* pstList);
void			GUI_List_SelectDownItem(GUI_LIST_STRUCT* pstList);
void			GUI_List_SetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t iSetValid, int32_t iSetDecimal);
void			GUI_List_GetListItemValue(GUI_LIST_STRUCT* pstList, size_t uiItemIndex, int32_t* piValid, int32_t* piDecimal);
GUI_LIST_ITEM*	GUI_List_GetListItemPtr(GUI_LIST_STRUCT* pstList, uint32_t uiItemIndex);
#if _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
BOOL			GUI_List_InsertItem(GUI_LIST_STRUCT* pstList, GUI_LIST_ITEM* pstNewItem, uint32_t uiNewItemIndex);
BOOL			GUI_List_RemoveItem(GUI_LIST_STRUCT* pstList, uint32_t uiNewItemIndex);
#endif // _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_

#endif // __INCLUDE_GUI_LIST_H__
