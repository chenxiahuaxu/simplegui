/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo04_Graph.c										**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for graph interface.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Notice.h"
#include "SGUI_VariableBox.h"
#include "SGUI_Resource.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define						TEXT_VARIABLE_LENGTH				(20)

#define						VARIABLE_BOX_WIDTH					(100)
#define						VARIABLE_NUMBER_BOX_HEIGHT			(8)
#define						VARIABLE_TEXT_BOX_HEIGHT			(12)
#define						VARIABLE_BOX_POSX					(10)
#define						VARIABLE_BOX_NUMBER_POSY			(19)
#define						VARIABLE_BOX_TEXT_POSY				(38)
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT    HMI_DemoVariableBox_Initialize(SGUI_SCR_DEV* pstIFObj);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoVariableBox_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT	HMI_DemoVariableBox_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);
static void				    HMI_DemoVariableBox_DrawFrame(SGUI_SCR_DEV* pstIFObj, SGUI_SZSTR szTitle);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_NUM_VARBOX_STRUCT	s_stNumberVariableBox =		{	{VARIABLE_BOX_POSX+2, VARIABLE_BOX_NUMBER_POSY+2, VARIABLE_BOX_WIDTH, VARIABLE_NUMBER_BOX_HEIGHT},
																&SGUI_DEFAULT_FONT_8,
																-50,
																100,
																0
															};
static SGUI_CHAR				s_szTextVariableBuffer[TEXT_VARIABLE_LENGTH+1] = {"ABCDEFG1234567890"};
static SGUI_TEXT_VARBOX_STRUCT	s_stTextVariableBox =		{	{VARIABLE_BOX_POSX+2, VARIABLE_BOX_TEXT_POSY+2, VARIABLE_BOX_WIDTH, VARIABLE_TEXT_BOX_HEIGHT},
																&SGUI_DEFAULT_FONT_12,
																0,
																TEXT_VARIABLE_LENGTH,
																s_szTextVariableBuffer,
															};
static SGUI_CHAR				s_szDefaultFrameTitle[] =	DEMO_VARIABLE_BOX_TITLE;
static SGUI_SZSTR				s_szFrameTitle =			s_szDefaultFrameTitle;
static SGUI_INT					s_uiFocusedFlag;
static SGUI_CSZSTR				s_szHelpNoticeText =		DEMO_VARIABLE_BOX_HELPER;
static SGUI_INT					s_uiAutoConfirmTimer =		5;
HMI_SCREEN_ACTION				s_stDemoVariableBoxActions = {
																HMI_DemoVariableBox_Initialize,
																HMI_DemoVariableBox_Prepare,
																HMI_DemoVariableBox_RefreshScreen,
																HMI_DemoVariableBox_ProcessEvent,
																HMI_DemoVariableBox_PostProcess,
															};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       		g_stHMIDemo_VariableBox =	{	HMI_SCREEN_ID_DEMO_VARIABLE_BOX,
																&s_stDemoVariableBoxActions
															};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
HMI_ENGINE_RESULT HMI_DemoVariableBox_Initialize(SGUI_SCR_DEV* pstIFObj)
{
	s_uiFocusedFlag = 0;
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_NOTICT_BOX           	stNoticeBox;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stNoticeBox.stLayout.iPosX = 5;
	stNoticeBox.stLayout.iPosY = 5;
	stNoticeBox.stLayout.iWidth = pstIFObj->stSize.iWidth-10;
	stNoticeBox.stLayout.iHeight = pstIFObj->stSize.iHeight-10;
	stNoticeBox.pstIcon = &SGUI_RES_ICON_INFORMATION_24;
	stNoticeBox.cszNoticeText = s_szHelpNoticeText;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	s_szFrameTitle = s_szDefaultFrameTitle;
	HMI_DemoVariableBox_DrawFrame(pstIFObj, (SGUI_SZSTR)s_szFrameTitle);
	// Show notice
#ifdef _SIMPLE_GUI_NON_ASCII_
	SGUI_Notice_Repaint(pstIFObj, &stNoticeBox, &SGUI_DEFAULT_FONT_12, 0);
#else
	SGUI_Notice_Repaint(pstIFObj, &stNoticeBox, &SGUI_DEFAULT_FONT_12, 0);
#endif //_SIMPLE_GUI_NON_ASCII_
	// Start RTC
	RTCTimerEnable(true);
	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
    HMI_DemoVariableBox_DrawFrame(pstIFObj, (SGUI_SZSTR)s_szFrameTitle);
    // Draw number box
    SGUI_Basic_DrawRectangle(pstIFObj, VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_NUMBER_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
    SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, (0 == s_uiFocusedFlag)?SGUI_DRAW_REVERSE:SGUI_DRAW_NORMAL);
    // Draw text box
    SGUI_Basic_DrawRectangle(pstIFObj, VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_TEXT_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
    SGUI_TextVariableBox_Paint(pstIFObj, &s_stTextVariableBox, (0 == s_uiFocusedFlag)?SGUI_DRAW_NORMAL:SGUI_DRAW_REVERSE);

	return HMI_RET_NORMAL;
}

HMI_ENGINE_RESULT HMI_DemoVariableBox_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	SGUI_UINT16					uiKeyValue;
	KEY_PRESS_EVENT*			pstKeyEvent;
	SGUI_INT					iProcessAction;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	iProcessAction =			HMI_DEMO_PROC_NO_ACT;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(s_uiAutoConfirmTimer > 0)
    {
		if(EVENT_TYPE_ACTION == pstEvent->iType)
		{
			if(EVENT_ID_KEY_PRESS == pstEvent->iID)
			{
				pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
				uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);

				if(KEY_VALUE_SPACE == uiKeyValue)
				{
					// Stop count down when press space.
					s_uiAutoConfirmTimer = 0;
				}
			}
		}
		else if(EVENT_TYPE_DATA == pstEvent->iType)
		{
			if(EVENT_ID_RTC == pstEvent->iID)
			{
				//Count down five seconds
				s_uiAutoConfirmTimer--;
			}
		}

        // Redraw screen if time out.
        if(0 == s_uiAutoConfirmTimer)
        {
            eProcessResult = HMI_DemoVariableBox_RefreshScreen(pstIFObj, NULL);
            RTCTimerEnable(false);
        }
    }
    else
    {
        if(EVENT_ID_KEY_PRESS == pstEvent->iID)
        {
        	pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
			uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);

			switch(uiKeyValue)
			{
				case KEY_VALUE_TAB:
				{
					s_uiFocusedFlag = ((s_uiFocusedFlag+1)%2);
					if(0 == s_uiFocusedFlag)
					{
						SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, SGUI_DRAW_REVERSE);
						SGUI_TextVariableBox_Paint(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_NORMAL);
					}
					else
					{
						SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, SGUI_DRAW_NORMAL);
						SGUI_TextVariableBox_Paint(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE);
					}
					break;
				}
				case KEY_VALUE_ESC:
				{
					iProcessAction = HMI_DEMO_PROC_CANCEL;
					break;
				}
				case KEY_VALUE_LEFT:
				{
					if(1 == s_uiFocusedFlag)
					{
						if(s_stTextVariableBox.sFocusIndex > 0)
						{
							s_stTextVariableBox.sFocusIndex--;
							SGUI_TextVariableBox_ChangeCharacter(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE, SGUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NONE);
						}
					}
					break;
				}
				case KEY_VALUE_UP:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_ChangeCharacter(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE, SGUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_PREV);
					}
					else
					{
						s_stNumberVariableBox.Value++;
						SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, SGUI_DRAW_REVERSE);
					}
					break;
				}
				case KEY_VALUE_RIGHT:
				{
					if(1 == s_uiFocusedFlag)
					{
						if(s_stTextVariableBox.sFocusIndex < (s_stTextVariableBox.sMaxTextLength-1))
						{
							s_stTextVariableBox.sFocusIndex++;
							SGUI_TextVariableBox_ChangeCharacter(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE, SGUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NONE);
						}
					}
					break;
				}
				case KEY_VALUE_DOWN:
				{
					if(1 == s_uiFocusedFlag)
					{
						SGUI_TextVariableBox_ChangeCharacter(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE, SGUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NEXT);
					}
					else
					{
						s_stNumberVariableBox.Value--;
						SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, SGUI_DRAW_REVERSE);
					}
					break;
				}
				case KEY_VALUE_ENTER:
				{
					if(1 == s_uiFocusedFlag)
					{
						s_szFrameTitle = s_stTextVariableBox.szValue;
						HMI_DemoVariableBox_DrawFrame(pstIFObj, (SGUI_SZSTR)s_szFrameTitle);
						// Draw number box
						SGUI_Basic_DrawRectangle(pstIFObj, VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_NUMBER_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
						SGUI_NumberVariableBox_Paint(pstIFObj, &s_stNumberVariableBox, SGUI_CENTER, SGUI_DRAW_NORMAL);
						// Draw text box
						SGUI_Basic_DrawRectangle(pstIFObj, VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_TEXT_BOX_HEIGHT+4, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
						SGUI_TextVariableBox_Paint(pstIFObj, &s_stTextVariableBox, SGUI_DRAW_REVERSE);
					}
					break;
				}
				default:
				{
					/* No process. */
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

HMI_ENGINE_RESULT HMI_DemoVariableBox_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CANCEL == iActionID)
		{
			s_uiAutoConfirmTimer = 5;
			HMI_GoBack(NULL);
		}
	}

	return HMI_RET_NORMAL;
}

void HMI_DemoVariableBox_DrawFrame(SGUI_SCR_DEV* pstIFObj, SGUI_SZSTR szTitle)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT_AREA				stTextDisplayArea;
	SGUI_POINT					stInnerPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stTextDisplayArea.iPosX =	4;
	stTextDisplayArea.iPosY =	4;
	stTextDisplayArea.iHeight = 12;
	stInnerPos.iPosX =			0;
	stInnerPos.iPosY =			0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstIFObj)
	{
		stTextDisplayArea.iWidth = pstIFObj->stSize.iWidth-8;
		SGUI_Basic_DrawRectangle(pstIFObj, 0, 0, RECT_WIDTH(pstIFObj->stSize), RECT_HEIGHT(pstIFObj->stSize), SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
		SGUI_Basic_DrawRectangle(pstIFObj, 2, 2, RECT_WIDTH(pstIFObj->stSize)-4, RECT_HEIGHT(pstIFObj->stSize)-4, SGUI_COLOR_FRGCLR, SGUI_COLOR_TRANS);
		SGUI_Basic_DrawLine(pstIFObj, 3, 17, 124, 17, SGUI_COLOR_FRGCLR);
		SGUI_Text_DrawText(pstIFObj, szTitle, &SGUI_DEFAULT_FONT_12, &stTextDisplayArea, &stInnerPos, SGUI_DRAW_NORMAL);
	}
}
