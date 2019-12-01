/*************************************************************************/
/** Copyright.															**/
/** FileName: List.c													**/
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

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoList_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoList_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoList_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoList_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_CSZSTR		s_szListTitle = 			    NULL;//DEMO_LIST_TITLE;
static SGUI_CSZSTR		s_arrszNoticeType[] =		{	DEMO_LIST_ITEM_NOTICE_TEXT, DEMO_LIST_ITEM_NOTICE_TIME};
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
static SGUI_CSZSTR		s_arrszEnumedValue[] =		{	DEMO_LIST_ITEM_ENUM_VALUE1, DEMO_LIST_ITEM_ENUM_VALUE2, DEMO_LIST_ITEM_ENUM_VALUE3};
#endif
static SGUI_List_ITEM	s_arrstTestListItems[] =	{	DEMO_LIST_ITEM_0,
														DEMO_LIST_ITEM_1,
														DEMO_LIST_ITEM_2,
														DEMO_LIST_ITEM_3,
														DEMO_LIST_ITEM_4,
														DEMO_LIST_ITEM_5,
														DEMO_LIST_ITEM_6,
													};

#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
static SGUI_List_ITEM	s_arrstAppendListItems[] =	{	DEMO_LIST_ITEM_7,
														DEMO_LIST_ITEM_8,
														DEMO_LIST_ITEM_9
													};
#endif

HMI_SCREEN_ACTION		s_stDemoListActions =		{	HMI_DemoList_Initialize,
														HMI_DemoList_Prepare,
														HMI_DemoList_RefreshScreen,
														HMI_DemoList_ProcessEvent,
														HMI_DemoList_PostProcess
													};

static SGUI_List_STRUCT	s_stDemoListObject;

static char				s_szNoticeTextBuffer[NOTICE_TEXT_BUFFER_SIZE] = {0x00};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_List =			{	HMI_SCREEN_ID_DEMO_LIST,
														&s_stDemoListActions
													};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoList_Initialize(SGUI_SCR_DEV* pstIFObj)
{
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t					i;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_SystemIF_MemorySet(&s_stDemoListObject, 0x00, sizeof(SGUI_List_STRUCT));
    // Title and font size must set before initialize list object.
    s_stDemoListObject.Data.Rect.PosX = 5;
    s_stDemoListObject.Data.Rect.PosY = 5;
    s_stDemoListObject.Data.Rect.Width = 96;//RECT_WIDTH(pstIFObj->stSize);
    s_stDemoListObject.Data.Rect.Height = 48; //RECT_HEIGHT(pstIFObj->stSize);
    s_stDemoListObject.Data.Title = s_szListTitle;
    s_stDemoListObject.FontRes = &SGUI_DEFAULT_FONT;
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
    s_stDemoListObject.Data.Items = NULL;
    s_stDemoListObject.Data.Count = 0;
    // Insert list item.
    for(i=0; i<(sizeof(s_arrstTestListItems)/sizeof(SGUI_List_ITEM)); i++)
	{
        SGUI_List_InsertItem(&s_stDemoListObject, &s_arrstTestListItems[i], s_stDemoListObject.Data.Count);
	}
#else
    s_stDemoListObject.Data.Items = s_arrstTestListItems;
    s_stDemoListObject.Data.Count = sizeof(s_arrstTestListItems)/sizeof(SGUI_List_ITEM);
#endif

     //Initialize list object.
	SGUI_List_Initialize(&s_stDemoListObject);

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_Prepare (SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoList_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16					uiKeyCode;
	SGUI_UINT16					uiKeyValue;
	SGUI_UINT16					uiOptionCode;
	KEY_PRESS_EVENT*			pstKeyEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	pstKeyEvent =				(KEY_PRESS_EVENT*)pstEvent;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(pstEvent->iType == EVENT_TYPE_ACTION)
	{
		// Check event is valid.
		if(SGUI_FALSE == HMI_EVENT_SIZE_CHK(*pstKeyEvent, KEY_PRESS_EVENT))
		{
			// Event data is invalid.
			eProcessResult = HMI_RET_INVALID_DATA;
		}
		else if(EVENT_ID_KEY_PRESS == pstEvent->iID)
		{
			uiKeyCode = pstKeyEvent->Data.uiKeyValue;
			uiKeyValue = KEY_CODE_VALUE(uiKeyCode);
			uiOptionCode = KEY_CODE_OPT(uiKeyCode);
			switch(uiKeyValue)
			{
				case KEY_VALUE_ENTER:
				{
					iProcessAction = HMI_DEMO_PROC_CONFIRM;
					break;
				}
				case KEY_VALUE_ESC:
				{
					iProcessAction = HMI_DEMO_PROC_CANCEL;
					break;
				}
				case KEY_VALUE_UP:
				{
					SGUI_List_SelectUpItem(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_DOWN:
				{
					SGUI_List_SelectDownItem(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_RIGHT:
				{
					if((uiOptionCode & KEY_OPTION_SHIFT) != 0)
					{
						SGUI_List_SetListItemValue(pstIFObj, &s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value-1);
					}
					else
					{
						SGUI_List_SetListItemValue(pstIFObj, &s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value+1, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value);
					}
					break;
				}
				case KEY_VALUE_LEFT:
				{
					if((uiOptionCode & KEY_OPTION_SHIFT) != 0)
					{
						SGUI_List_SetListItemValue(pstIFObj, &s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value+1);
					}
					else
					{
						SGUI_List_SetListItemValue(pstIFObj, &s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Valid.Value-1, SGUI_List_GetListItemPtr(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex)->Decimal.Value);
					}
					break;
				}
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
				case KEY_VALUE_F8:
				{
					SGUI_List_RemoveItem(&s_stDemoListObject, s_stDemoListObject.ControlVariable.SelectIndex);
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_F9:	// Insert to head.
				{
					SGUI_List_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[0], 0);
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_F10:	// Insert to intermediate.
				{
					SGUI_List_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[1], 5);
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
					break;
				}
				case KEY_VALUE_F11:	// Insert to end.
				{
					SGUI_List_InsertItem(&s_stDemoListObject, &s_arrstAppendListItems[2], s_stDemoListObject.Data.Count);
					SGUI_List_Repaint(pstIFObj, &s_stDemoListObject);
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
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

HMI_ENGINE_RESULT HMI_DemoList_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	uint32_t			uiSelectListIndex;
	SGUI_List_ITEM*		pstSelectedItem;
	int32_t				iListItemParameterValue;

	if(HMI_DEMO_PROC_CONFIRM == iActionID)
	{
		uiSelectListIndex = s_stDemoListObject.ControlVariable.SelectIndex;
		switch(SGUI_List_GetListItemPtr(&s_stDemoListObject, uiSelectListIndex)->ItemID)
		{
			case 1:
			{
				// Show notice.
				pstSelectedItem = SGUI_List_GetListItemPtr(&s_stDemoListObject, uiSelectListIndex);
				iListItemParameterValue = pstSelectedItem->Valid.Value;
				if(0 == iListItemParameterValue)
				{
					sprintf(s_szNoticeTextBuffer, DEMO_LIST_NOTICE_TEXT_FMT, uiSelectListIndex);
					HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_TEXT_NOTICE, s_szNoticeTextBuffer);
				}
				else
				{
					HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_RTC_NOTICE, NULL);
				}
				break;
			}
			case 5:
			{
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_VARIABLE_BOX, NULL);
				break;
			}
			case 6:
			{
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH, NULL);
				break;
			}
			default:
			{
				sprintf(s_szNoticeTextBuffer, DEMO_LIST_NOTICE_TEXT_FMT, uiSelectListIndex);
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_TEXT_NOTICE, s_szNoticeTextBuffer);
				break;
			}
		}
	}
	else if(HMI_DEMO_PROC_CANCEL == iActionID)
	{
		HMI_GoBack(NULL);
	}

	return HMI_RET_NORMAL;
}

