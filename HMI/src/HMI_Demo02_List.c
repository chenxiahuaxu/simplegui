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
#include "HMI_Demo02_List.h"
#include "SGUI_List.h"
#include "HMI_Process.h"
#include <stdio.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoList_Initialize(void);
static int32_t			HMI_DemoList_PreProcess(const void* pstParameters);
static int32_t			HMI_DemoList_RefreshScreen(void);
static int32_t			HMI_DemoList_InternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoList_ExternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoList_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
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


#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
static SGUI_LIST_STRUCT	stTestList =			{	{"测试列表", 8, NULL}};
#else
static SGUI_LIST_STRUCT	stTestList =			{	{"测试列表", 8, arrstTestListItems}};
#endif

static char				szNoticeTextBuffer[NOTICE_TEXT_BUFFER_SIZE] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoListActions = {	HMI_DemoList_Initialize,
													HMI_DemoList_PreProcess,
													HMI_DemoList_RefreshScreen,
													HMI_DemoList_InternalEvent,
													HMI_DemoList_ExternalEvent,
													HMI_DemoList_PostProcess
												};
HMI_SCREEN				g_stHMI_DemoList =		{	HMI_SCREEN_ID_ANY,
													&stHMI_DemoListActions
												};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
int32_t	HMI_DemoList_Initialize(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_LIST_InitializeListData(&stTestList);
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_PreProcess(const void* pstParameters)
{
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t					i;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	for(i=0; i<(sizeof(arrstTestListItems)/sizeof(SGUI_LIST_ITEM)); i++)
	{
        SGUI_LIST_InsertItem(&stTestList, &arrstTestListItems[i], stTestList.Data.Count);
	}
	SGUI_LIST_RefreshList(&stTestList);
#endif
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoList_RefreshScreen(void)
{
	SGUI_LIST_RefreshList(&stTestList);
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_InternalEvent(uint32_t uiScreenID, const void* pstParameters)
{
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_ExternalEvent(uint32_t uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	USER_ACT_KEYPRESS*			pstUserEvent;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RESULT_NORMAL;
	pstUserEvent = 				(USER_ACT_KEYPRESS*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(pstUserEvent->KeyValue[0])
	{
		case KEY_VALUE_SPACE:
		{
			break;
		}
		case KEY_VALUE_ENTER:
		{
			iProcessResult = HMI_RESULT_CONFIRM;
			break;
		}
		case KEY_VALUE_ESC:
		{
			iProcessResult = HMI_RESULT_CANCEL;
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
			if((pstUserEvent->Options & KEY_OPTION_SHIFT) != 0)
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
			if((pstUserEvent->Options & KEY_OPTION_SHIFT) != 0)
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
	return iProcessResult;
}

int32_t HMI_DemoList_PostProcess(int32_t iActionResult)
{
	uint32_t			uiSelectListIndex;
	SGUI_LIST_ITEM*		pstSelectedItem;
	int32_t				iListItemParameterValue;

	if(HMI_RESULT_CONFIRM == iActionResult)
	{
		uiSelectListIndex = stTestList.ControlVariable.SelectIndex;
		switch(SGUI_LIST_GetListItemPtr(&stTestList, uiSelectListIndex)->Sign)
		{
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
			case 6:
			{
				HMI_Action_Goto(4, NULL);
				break;
			}
			case 7:
			{
				HMI_Action_Goto(5, NULL);
				break;
			}
			default:
			{
				sprintf(szNoticeTextBuffer, "选择列表项%u.", uiSelectListIndex);
				HMI_Action_Goto(3, szNoticeTextBuffer);
				break;
			}
		}
	}
	else if(HMI_RESULT_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return 0;
}


