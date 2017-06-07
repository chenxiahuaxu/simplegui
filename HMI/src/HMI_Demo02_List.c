/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo02_List.c											**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/** History:															**/
/**	Polarix	2017/6/1	1.0.0.0		New create.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo02_List.h"
#include "GUI_List.h"
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
static int32_t			HMI_DemoList_InternalEventEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoList_ExternalEventEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoList_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static const char*		arrszNoticeType[] =		{	"文字消息", "系统时间"};
static GUI_LIST_ITEM	arrstTestListItems[] =	{	{"简单列表项",			LIST_ITEM_NORMAL,		{0}, 					{0, 0, 0}, NULL},
													{"枚举类型列表项",		LIST_ITEM_ENUM,			{0, 0, 1},				{0, 0, 0}, arrszNoticeType},
													{"数字列表项",			LIST_ITEM_DIGIT,		{0, -50, 50},			{0, 0, 3}, NULL},
													{"带小数的数字列表项",	LIST_ITEM_DIGIT,		{1, -50, 50},			{2, 0, 5}, NULL},
													{"超长文字的简单列表项",	LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{"列表项",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{"曲线图",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
													{"编辑框",				LIST_ITEM_NORMAL,		{0, 0, 0},				{0, 0, 0}, NULL},
};
static GUI_LIST_STRUCT	stTestList =			{	{"测试列表", 8, arrstTestListItems}};
static char				szNoticeTextBuffer[NOTICE_TEXT_BUFFER_SIZE] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoListActions = {	HMI_DemoList_Initialize,
													HMI_DemoList_PreProcess,
													HMI_DemoList_RefreshScreen,
													HMI_DemoList_InternalEventEvent,
													HMI_DemoList_ExternalEventEvent,
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
	GUI_List_InitializeListData(&stTestList);
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_PreProcess(const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoList_RefreshScreen(void)
{
	GUI_List_RefreshList(&stTestList);
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_InternalEventEvent(uint32_t uiScreenID, const void* pstParameters)
{
	return HMI_RESULT_NORMAL;
}

int32_t	HMI_DemoList_ExternalEventEvent(uint32_t uiScreenID, const void* pstParameters)
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
			if((pstUserEvent->Options & KEY_OPTION_SHIFT) != 0)
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
			if((pstUserEvent->Options & KEY_OPTION_SHIFT) != 0)
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

int32_t HMI_DemoList_PostProcess(int32_t iActionResult)
{
	uint32_t			uiSelectListIndex;
	GUI_LIST_ITEM*		pstSelectedItem;
	int32_t				iListItemParameterValue;

	if(HMI_RESULT_CONFIRM == iActionResult)
	{
		uiSelectListIndex = stTestList.ControlVariable.SelectIndex;
		switch(uiSelectListIndex)
		{
			case 1:
			{
				// Show notice.
				pstSelectedItem = stTestList.Data.Items+uiSelectListIndex;
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


