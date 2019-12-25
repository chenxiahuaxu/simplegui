/*************************************************************************/
/** Copyright.															**/
/** FileName: Menu.c													**/
/** Author: Polarix														**/
/** Description: HMI demo for menu control interface.					**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Menu.h"
#include "SGUI_FontResource.h"
#include "HMI_Engine.h"
#include "Resource.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT	HMI_DemoMenu_Initialize(SGUI_SCR_DEV* pstDeviceIF);
static HMI_ENGINE_RESULT	HMI_DemoMenu_Prepare(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoMenu_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoMenu_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoMenu_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_ITEMS_ITEM		s_arrstMenuItems[] =		{	{"Item 1", NULL},
															{"Item 2", NULL},
															{"Item 3", NULL},
															{"Item 4", NULL},
															{"Item 5", NULL},
															{"Item 6", NULL},
															{"Item 7", NULL},
															{"Item 8", NULL},
														};

static SGUI_ITEMS_ITEM		s_arrstSubMenuItems[] =		{	{"Sub 1", NULL},
															{"Sub 2", NULL},
															{"Sub 3", NULL}
														};

static SGUI_MENU_STRUCT		s_stDemoMenuObject = 		{0x00};
static SGUI_MENU_STRUCT		s_stDemoSubMenuObject =		{0x00};

static SGUI_MENU_STRUCT*	s_pstActivedMenu =			&s_stDemoMenuObject;

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		s_stDemoMenuActions =			{	HMI_DemoMenu_Initialize,
															HMI_DemoMenu_Prepare,
															HMI_DemoMenu_RefreshScreen,
															HMI_DemoMenu_ProcessEvent,
															HMI_DemoMenu_PostProcess
														};
HMI_SCREEN_OBJECT       g_stHMIDemo_Menu =				{	HMI_SCREEN_ID_DEMO_MENU,
															&s_stDemoMenuActions
														};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoMenu_Initialize(SGUI_SCR_DEV* pstDeviceIF)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    // Initialize list data.
    SGUI_SystemIF_MemorySet(&s_stDemoMenuObject, 0x00, sizeof(SGUI_MENU_STRUCT));
    // Title and font size must set before initialize list object.
    s_stDemoMenuObject.stLayout.iPosX = 0;
    s_stDemoMenuObject.stLayout.iPosY = 0;
    s_stDemoMenuObject.stLayout.iWidth = 48;
    s_stDemoMenuObject.stLayout.iHeight = 60;
     //Initialize list object.
	SGUI_Menu_Initialize(&s_stDemoMenuObject, &SGUI_DEFAULT_FONT_8, s_arrstMenuItems, sizeof(s_arrstMenuItems)/sizeof(SGUI_ITEMS_ITEM));
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoMenu_Prepare(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_Basic_DrawRectangle(pstDeviceIF, 0, 0, pstDeviceIF->stSize.iWidth, pstDeviceIF->stSize.iHeight, SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
	SGUI_Menu_Repaint(pstDeviceIF, &s_stDemoMenuObject);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoMenu_RefreshScreen(SGUI_SCR_DEV* pstDeviceIF, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SGUI_Menu_Repaint(pstDeviceIF, s_pstActivedMenu);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoMenu_ProcessEvent(SGUI_SCR_DEV* pstDeviceIF, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT		eProcessResult;
	SGUI_UINT16				uiKeyCode;
	SGUI_UINT16				uiKeyValue;
	KEY_PRESS_EVENT*		pstKeyEvent;
	SGUI_INT				iProcessAction;
	SGUI_RECT				stItemArea;

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
					if(&s_stDemoMenuObject == s_pstActivedMenu)
					{
						SGUI_ItemsBase_GetItemExtent(&(s_pstActivedMenu->stItems), s_pstActivedMenu->stItems.iSelection, &stItemArea);
						s_stDemoSubMenuObject.stLayout.iPosX = RECT_X_END(s_pstActivedMenu->stLayout);
						if(stItemArea.iPosY > (pstDeviceIF->stSize.iHeight/2))
						{
							s_stDemoSubMenuObject.stLayout.iPosY = 0;
							s_stDemoSubMenuObject.stLayout.iHeight = stItemArea.iPosY+stItemArea.iHeight;
						}
						else
						{
							s_stDemoSubMenuObject.stLayout.iPosY = stItemArea.iPosY;
							s_stDemoSubMenuObject.stLayout.iHeight = pstDeviceIF->stSize.iHeight-stItemArea.iPosY;

						}
						s_stDemoSubMenuObject.stLayout.iWidth = stItemArea.iWidth;
						s_pstActivedMenu = &s_stDemoSubMenuObject;
						SGUI_Menu_Initialize(&s_stDemoSubMenuObject, &SGUI_DEFAULT_FONT_8, s_arrstSubMenuItems, sizeof(s_arrstSubMenuItems)/sizeof(SGUI_ITEMS_ITEM));
						SGUI_Menu_Repaint(pstDeviceIF, s_pstActivedMenu);
					}
					iProcessAction = HMI_DEMO_PROC_CONFIRM;
					break;
				}
				case KEY_VALUE_ESC:
				{
					if(&s_stDemoMenuObject == s_pstActivedMenu)
					{
						iProcessAction = HMI_DEMO_PROC_CANCEL;
					}
					else
					{
						if(s_pstActivedMenu->stLayout.iWidth > 0)
						{
							/* Cleanup sub-menu display. */
							SGUI_Basic_DrawRectangle(pstDeviceIF, s_pstActivedMenu->stLayout.iPosX, s_pstActivedMenu->stLayout.iPosY, s_pstActivedMenu->stLayout.iWidth, s_pstActivedMenu->stLayout.iHeight, SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
							s_pstActivedMenu->stLayout.iWidth = 0;
							s_pstActivedMenu = &s_stDemoMenuObject;
						}
						SGUI_Menu_Repaint(pstDeviceIF, s_pstActivedMenu);
					}

					break;
				}
				case KEY_VALUE_UP:
				{
					if(s_pstActivedMenu->stItems.iSelection > 0)
					{
						s_pstActivedMenu->stItems.iSelection-=1;
						SGUI_Menu_Repaint(pstDeviceIF, s_pstActivedMenu);
					}
					break;
				}
				case KEY_VALUE_DOWN:
				{
					if(s_pstActivedMenu->stItems.iSelection < s_pstActivedMenu->stItems.iCount-1)
					{
						s_pstActivedMenu->stItems.iSelection+=1;
						SGUI_Menu_Repaint(pstDeviceIF, s_pstActivedMenu);
					}
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

HMI_ENGINE_RESULT HMI_DemoMenu_PostProcess(SGUI_SCR_DEV* pstDeviceIF, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_DEMO_PROC_CANCEL == iActionID)
	{
		HMI_GoBack(NULL);
	}

	return HMI_RET_NORMAL;
}
