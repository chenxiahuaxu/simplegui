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
#include "SGUI_ItemsBase.h"
#include "SGUI_FontResource.h"
#include "HMI_Engine.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define					NOTICE_TEXT_BUFFER_SIZE				(64)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoItemsBase_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoItemsBase_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoItemsBase_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoItemsBase_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoItemsBase_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_ITEMS_ITEM		s_arrstTestItems[] =		{	{"Variable box", NULL},
															{"Item2 text", NULL},
															{"Item3 text", NULL},
															{"Item4 text", NULL},
															{"Item5 text", NULL},
															{"Item6 text", NULL},
															{"Item7 text", NULL},
														};

HMI_SCREEN_ACTION			s_stDemoItemsBaseActions =	{	HMI_DemoItemsBase_Initialize,
															HMI_DemoItemsBase_Prepare,
															HMI_DemoItemsBase_RefreshScreen,
															HMI_DemoItemsBase_ProcessEvent,
															HMI_DemoItemsBase_PostProcess
														};

static SGUI_ITEMS_BASE		s_stDemoItemsBaseObject;

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_ItemsBase =			{	HMI_SCREEN_ID_DEMO_ITEMS_BASE,
															&s_stDemoItemsBaseActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoItemsBase_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_SystemIF_MemorySet(&s_stDemoItemsBaseObject, 0x00, sizeof(SGUI_ITEMS_BASE));
    // Title and font size must set before initialize list object.
    s_stDemoItemsBaseObject.stLayout.iPosX = 5;
    s_stDemoItemsBaseObject.stLayout.iPosY = 5;
    s_stDemoItemsBaseObject.stLayout.iWidth = 118;
    s_stDemoItemsBaseObject.stLayout.iHeight = 54;
     //Initialize list object.
	SGUI_ItemsBase_Initialize(&s_stDemoItemsBaseObject, &SGUI_DEFAULT_FONT_8);
	SGUI_ItemsBase_BindItemsData(&s_stDemoItemsBaseObject, s_arrstTestItems, sizeof(s_arrstTestItems)/sizeof(SGUI_ITEMS_ITEM));

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoItemsBase_Prepare (SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_Basic_DrawRectangle(pstIFObj, 4, 4, 120, 56, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
	SGUI_ItemsBase_Repaint(pstIFObj, &s_stDemoItemsBaseObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoItemsBase_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_Basic_DrawRectangle(pstIFObj, 4, 4, 62, 22, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
	SGUI_ItemsBase_Repaint(pstIFObj, &s_stDemoItemsBaseObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoItemsBase_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16					uiKeyCode;
	SGUI_UINT16					uiKeyValue;
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
					if(s_stDemoItemsBaseObject.iSelection > 0)
					{
						s_stDemoItemsBaseObject.iSelection -= 1;
					}
					SGUI_ItemsBase_Repaint(pstIFObj, &s_stDemoItemsBaseObject);
					break;
				}
				case KEY_VALUE_DOWN:
				{
					if(s_stDemoItemsBaseObject.iSelection < s_stDemoItemsBaseObject.iCount-1)
					{
						s_stDemoItemsBaseObject.iSelection += 1;
					}
					SGUI_ItemsBase_Repaint(pstIFObj, &s_stDemoItemsBaseObject);
					break;
				}
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

HMI_ENGINE_RESULT HMI_DemoItemsBase_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_DEMO_PROC_CONFIRM == iActionID)
	{
        switch(s_stDemoItemsBaseObject.iSelection)
        {
			case 0:
			{
				HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_VARIABLE_BOX, NULL);
				break;
			}
			default:
			{

				/* do nothing. */
			}
        }
	}
	else if(HMI_DEMO_PROC_CANCEL == iActionID)
	{
		HMI_GoBack(NULL);
	}

	return HMI_RET_NORMAL;
}

