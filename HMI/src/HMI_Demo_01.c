/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo_01.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/** History:															**/
/**	Polarix	2017/6/1	1.0.0.0		New create.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo_01.h"
#include "GUI_List.h"
#include "HMI_Process.h"
#include <stdio.h>

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoList_Initialize(void);
static int32_t			HMI_DemoList_UpdateScreen(void* pstParameters);
static int32_t			HMI_DemoList_UserActions(uint16_t uiOptions, uint16_t* puiActions);
static int32_t			HMI_DemoList_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static const char*		arrszOptionGp1[] =		{	"选项1", "选项2", "选项3"};
static const char*		arrszOptionGp2[] =		{	"组2 选项A", "组2 选项B", "组2 选项C", "组2 选项D"};
static GUI_LIST_ITEM	arrstTestListItems[] =	{	{"列表项0 - 超长列表项",	LIST_ITEM_NORMAL,	{0}, 					{0, 0, 0}, NULL},
													{"列表项1 - 枚举",		LIST_ITEM_ENUM,			{2, 0, 2},				{0, 0, 2}, arrszOptionGp1},
													{"列表项2 - 枚举",		LIST_ITEM_ENUM,			{1, 0, 3},				{0, 0, 3}, arrszOptionGp2},
													{"列表项3 - 数字",		LIST_ITEM_DIGIT,		{9, 1, 9},				{0, 0, 0}, NULL},
													{"列表项4 - 数字",		LIST_ITEM_DIGIT,		{10, 5, 15},			{0, 0, 0}, NULL},
													{"列表项5 - 数字",		LIST_ITEM_DIGIT,		{100, 50, 100},			{0, 0, 0}, NULL},
													{"列表项6 - 数字",		LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 0}, NULL},
													{"列表项7 - 小数",		LIST_ITEM_DIGIT,		{12345, 0, 99999},		{2, 0, 2}, NULL},
													{"列表项8 - 小数",		LIST_ITEM_DIGIT,		{66, 66, 66},			{4, 0, 5}, NULL},
													{"列表项9 - 数字",		LIST_ITEM_DIGIT,		{-100, -100, 0},		{0, 0, 0}, NULL},
													{"列表项A - 小数",		LIST_ITEM_DIGIT,		{-123, -123, -123},		{1, 0, 1}, NULL},
													{"列表项B - 小数",		LIST_ITEM_DIGIT,		{-456, -500, -50},		{5, 0, 5}, NULL},
													{"列表项C",				LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
													{"列表项D",				LIST_ITEM_NORMAL,		{0},					{0, 0, 0}, NULL},
													{"列表项E",				LIST_ITEM_NORMAL,		{0},					{0, 0, 0}, NULL},
													{"列表项F - 超长列表项",	LIST_ITEM_NORMAL,	{0},					{0, 0, 0}, NULL},
};
static GUI_LIST_STRUCT	stTestList =			{	{"测试列表", 16, arrstTestListItems}};
//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN				g_stHMI_DemoList =		{	HMI_DemoList_Initialize,
																NULL,
																HMI_DemoList_UserActions,
                                                                HMI_DemoList_UpdateScreen,
                                                                HMI_DemoList_PostProcess
															};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	HMI_DemoList_Initialize									**/
/** Purpose:		Initialize list data.									**/
/** Resources:		List data structure and bind data if existed.			**/
/** Params:			None.													**/
/** Return:			Initialize process result.								**/
/** Limitation:		None.													**/
/*****************************************************************************/
int32_t	HMI_DemoList_Initialize(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	GUI_List_InitializeListData(&stTestList);
	return HMI_RESULT_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_UpdateScreen								**/
/** Purpose:		Update data and refresh screen display.					**/
/** Resources:		List data structure and bind data if existed.			**/
/** Params:																	**/
/** @[in]pstParameters: Screen update data pointer.							**/
/** Return:			Initialize process result.								**/
/** Limitation:		Parameter pointer is a void type, convert to the 		**/
/**					appropriate type before use.							**/
/*****************************************************************************/
int32_t	HMI_DemoList_UpdateScreen(void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	GUI_List_RefreshList(&stTestList);
	return HMI_RESULT_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_UpdateScreen								**/
/** Purpose:		Update data and refresh screen display.					**/
/** Resources:		List data structure and bind data if existed.			**/
/** Params:																	**/
/** @[in]pstParameters: Screen update data pointer.							**/
/** Return:			Initialize process result.								**/
/** Limitation:		Parameter pointer is a void type, convert to the 		**/
/**					appropriate type before use.							**/
/*****************************************************************************/
int32_t	HMI_DemoList_UserActions(uint16_t uiOptions, uint16_t* puiActions)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult				= HMI_RESULT_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(*puiActions)
	{
		case KEY_VALUE_SPACE:
		{
			break;
		}
		case KEY_VALUE_ENTER:
		{
			iProcessResult =HMI_RESULT_CONFIRM;
			break;
		}
		case KEY_VALUE_ESC:
		{
			break;
		}
		case KEY_VALUE_UP:
		{
			GUI_List_SelectUpItem(&stTestList);
			break;
		}
		case KEY_VALUE_DOWN:
		{
			GUI_List_SelectDownItem(&stTestList);
			break;
		}
		case KEY_VALUE_RIGHT:
		{
			if((uiOptions & KEY_OPTION_SHIFT) != 0)
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value-1);
			}
			else
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value+1, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value);
			}
			break;
		}
		case KEY_VALUE_LEFT:
		{
			if((uiOptions & KEY_OPTION_SHIFT) != 0)
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value+1);
			}
			else
			{
				GUI_List_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Valid.Value-1, stTestList.Data.Items[stTestList.ControlVariable.SelectIndex].Decimal.Value);
			}
			break;
		}
		default:
		{
			break;
		}
	}
	return iProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_PostProcess								**/
/** Purpose:		Do something after user action or update screen.		**/
/** Resources:		List data structure and bind data if existed.			**/
/** Params:																	**/
/** @[in]iActionResult: User action or screen update process result.		**/
/** Return:			Process result.											**/
/** Limitation:		None.													**/
/*****************************************************************************/
int32_t HMI_DemoList_PostProcess(int32_t iActionResult)
{
	uint32_t			uiSelectListIndex;

	if(HMI_RESULT_CONFIRM == iActionResult)
	{
		uiSelectListIndex = stTestList.ControlVariable.SelectIndex;
		HMI_Action_FollowUp(1, &uiSelectListIndex);
	}
	return 0;
}


