/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo02_List.c											**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_List.h"
#include "HMI_Engine.h"
#include <stdio.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoList_Initialize(void);
static HMI_ENGINE_RESULT	HMI_DemoList_Prepare(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_RefreshScreen(const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent);
static HMI_ENGINE_RESULT	HMI_DemoList_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_PCSZSTR     szListTitle =           "测试列表";
static SGUI_PCSZSTR		arrszNoticeType[] =		{	"文字消息", "系统时间"};
static SGUI_LIST_ITEM	arrstTestListItems[] =	{	{0, "简单列表项",			LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
													{1, "枚举类型列表项",		LIST_ITEM_ENUM,			{0, 0, 1},				{0, 0, 0}, arrszNoticeType},
													{2, "数字列表项",			LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 3}, NULL},
													{3, "带小数的数字列表项",	LIST_ITEM_DIGIT,		{1, -50, 50},			{2, 0, 5}, NULL},
													{4, "超长文字的简单列表项",	LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{5, "列表项",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{6, "曲线图",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{7, "编辑框",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
};

#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
static SGUI_LIST_ITEM	arrstAppendListItems[] = {	{8, "添加项1",				LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
													{9, "添加项2",				LIST_ITEM_ENUM,			{0, 0, 1},				{0, 0, 0}, arrszNoticeType},
													{10, "添加项3",				LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 3}, NULL},
};
#endif

static SGUI_LIST_STRUCT	stTestList;

static char				szNoticeTextBuffer[NOTICE_TEXT_BUFFER_SIZE] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoListActions = {	HMI_DemoList_Initialize,
													HMI_DemoList_Prepare,
													HMI_DemoList_RefreshScreen,
													HMI_DemoList_ProcessEvent,
													HMI_DemoList_PostProcess
												};
HMI_SCREEN_OBJECT       g_stHMIDemo_List =		{	HMI_SCREEN_ID_DEMO_LIST,
													&stHMI_DemoListActions
												};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoList_Initialize(void)
{
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t					i;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_Common_MemorySet(&stTestList, 0x00, sizeof(SGUI_LIST_STRUCT));
    stTestList.Data.Title = szListTitle;
    stTestList.FontSize = SGUI_FONT_SIZE_H12;
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
    stTestList.Data.Items = NULL;
    stTestList.Data.Count = 0;
#else
    stTestList.Data.Items = arrstTestListItems;
    stTestList.Data.Count = sizeof(arrstTestListItems)/sizeof(SGUI_LIST_ITEM);
#endif

    // Initialize logical.
	SGUI_LIST_InitializeListData(&stTestList);
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
    // Insert list item.
    for(i=0; i<(sizeof(arrstTestListItems)/sizeof(SGUI_LIST_ITEM)); i++)
	{
        SGUI_LIST_InsertItem(&stTestList, &arrstTestListItems[i], stTestList.Data.Count);
	}
#endif
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_Prepare (const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_LIST_RefreshList(&stTestList);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_RefreshScreen(const void* pstParameters)
{
	SGUI_LIST_RefreshList(&stTestList);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16*				parrKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(eEvent == HMI_ENGINE_EVENT_ACTION)
	{
		if(NULL != pstEvent)
		{
			parrKeyValue = (SGUI_UINT16*)pstEvent->Data;
			if(NULL != parrKeyValue)
			{
				switch(*(parrKeyValue+1))
				{
					case KEY_VALUE_ENTER:
					{
						eProcessResult = HMI_RET_CONFIRM;
						break;
					}
					case KEY_VALUE_ESC:
					{
						eProcessResult = HMI_RET_CANCEL;
						break;
					}
					case KEY_VALUE_UP:
					{
						SGUI_LIST_SelectUpItem(&stTestList);
						break;
					}
					case KEY_VALUE_DOWN:
					{
						SGUI_LIST_SelectDownItem(&stTestList);
						break;
					}
					case KEY_VALUE_RIGHT:
					{
						if((*(parrKeyValue+0) & KEY_OPTION_SHIFT) != 0)
						{
							SGUI_LIST_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Valid.Value, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Decimal.Value-1);
						}
						else
						{
							SGUI_LIST_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Valid.Value+1, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Decimal.Value);
						}
						break;
					}
					case KEY_VALUE_LEFT:
					{
						if((*(parrKeyValue+0) & KEY_OPTION_SHIFT) != 0)
						{
							SGUI_LIST_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Valid.Value, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Decimal.Value+1);
						}
						else
						{
							SGUI_LIST_SetListItemValue(&stTestList, stTestList.ControlVariable.SelectIndex, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Valid.Value-1, SGUI_LIST_GetListItemPtr(&stTestList, stTestList.ControlVariable.SelectIndex)->Decimal.Value);
						}
						break;
					}
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
					case KEY_VALUE_F8:
					{
						SGUI_LIST_RemoveItem(&stTestList, stTestList.ControlVariable.SelectIndex);
						SGUI_LIST_RefreshList(&stTestList);
						break;
					}
					case KEY_VALUE_F9:	// Insert to head.
					{
						SGUI_LIST_InsertItem(&stTestList, &arrstAppendListItems[0], 0);
						SGUI_LIST_RefreshList(&stTestList);
						break;
					}
					case KEY_VALUE_F10:	// Insert to intermediate.
					{
						SGUI_LIST_InsertItem(&stTestList, &arrstAppendListItems[1], 5);
						SGUI_LIST_RefreshList(&stTestList);
						break;
					}
					case KEY_VALUE_F11:	// Insert to end.
					{
						SGUI_LIST_InsertItem(&stTestList, &arrstAppendListItems[2], stTestList.Data.Count);
						SGUI_LIST_RefreshList(&stTestList);
						break;
					}
#endif
					default:
					{
						break;
					}
				}
			}
		}
	}
	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoList_PostProcess(SGUI_INT iActionResult)
{
	uint32_t			uiSelectListIndex;
	SGUI_LIST_ITEM*		pstSelectedItem;
	int32_t				iListItemParameterValue;

	if(HMI_RET_CONFIRM == iActionResult)
	{
		uiSelectListIndex = stTestList.ControlVariable.SelectIndex;
		switch(SGUI_LIST_GetListItemPtr(&stTestList, uiSelectListIndex)->Sign)
		{
			/*
			case 1:
			{
				// Show notice.
				pstSelectedItem = SGUI_LIST_GetListItemPtr(&stTestList, uiSelectListIndex);
				iListItemParameterValue = pstSelectedItem->Valid.Value;
				if(0 == iListItemParameterValue)
				{
					sprintf(szNoticeTextBuffer, "选择列表项%u.", uiSelectListIndex);
					HMI_Action_Goto(3, szNoticeTextBuffer);
				}
				else
				{
					HMI_Action_Goto(2, NULL);
				}
				break;
			}
			*/
			case 6:
			{
				//HMI_Action_Goto(4, NULL);
				break;
			}
			case 7:
			{
				HMI_Goto(HMI_SCREEN_ID_DEMO_VARIABLE_BOX, NULL);
				break;
			}
			default:
			{
				sprintf(szNoticeTextBuffer, "选择列表项%u.", uiSelectListIndex);
				HMI_Goto(HMI_SCREEN_ID_DEMO_TEXT_NOTICE, szNoticeTextBuffer);
				break;
			}
		}
	}
	else if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_GoBack(NULL);
	}
	return HMI_RET_NORMAL;
}


