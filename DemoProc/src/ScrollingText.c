/*************************************************************************/
/** Copyright.															**/
/** FileName: ScrollingText.c											**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for text draw interface.						**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Text.h"
#include "HMI_Engine.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		HMI_TEXT_DEMO_FRAME_EDGE_LAYERS				(2)
		#if(HMI_TEXT_DEMO_FRAME_EDGE_LAYERS == 0)
#define 	HMI_FRAMR_EDGE_WIDTH						(0)
		#else
#define		HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH				(HMI_TEXT_DEMO_FRAME_EDGE_LAYERS*2-1)
		#endif
#define		HMI_TEXT_DEMO_FRAME_TEXT_POSX				(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)
#define		HMI_TEXT_DEMO_FRAME_TEXT_POSY				(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)
#define		HMI_TEXT_DEMO_FRAME_TEXT_WIDTH(SCR_SIZE)	(((SCR_SIZE).Width)-(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)*2)
#define		HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT(SCR_SIZE)	(((SCR_SIZE).Height)-(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)*2)

#ifdef _SIMPLE_GUI_NON_ASCII_
#define SCROLL_TEXT_FONT_SIZE							(SGUI_FONT_SIZE_H12)
#else
#define SCROLL_TEXT_FONT_SIZE							(SGUI_FONT_SIZE_H8)
#endif // _SIMPLE_GUI_NON_ASCII_

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Initialize(SGUI_SCR_DEV* Interface);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Prepare(SGUI_SCR_DEV* Interface, const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_RefreshScreen(SGUI_SCR_DEV* Interface, const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_ProcessEvent(SGUI_SCR_DEV* Interface, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_PostProcess(SGUI_SCR_DEV* Interface, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID);
static void					HMI_DemoScrollingText_DrawFrame(SGUI_SCR_DEV* Interface);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
// Demo text.
static SGUI_CCHAR           s_szDemoText[] =            {DEMO_START_NOTICE};

static int32_t				s_iTextOffset;
static SGUI_INT				s_iTextHeight;
static SGUI_RECT_AREA		s_stTextDisplayArea;

static HMI_SCREEN_ACTION	s_stDemoScrollingTextActions =	{
															HMI_DemoScrollingText_Initialize,
															HMI_DemoScrollingText_Prepare,
															HMI_DemoScrollingText_RefreshScreen,
															HMI_DemoScrollingText_ProcessEvent,
															HMI_DemoScrollingText_PostProcess
														};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_ScrollingText =		{
														HMI_SCREEN_ID_DEMO_SCROLLING_TEXT,
														&s_stDemoScrollingTextActions};

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	HMI_DemoScrollingText_Initialize                        **/
/** Purpose:		Initialize screen data.									**/
/** Resources:		Current screen display or control data.					**/
/** Parameters:		None.													**/
/** Return:			Initialize process result.								**/
/** Limitation:		None.													**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_Initialize(SGUI_SCR_DEV* Interface)
{
	s_iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT(Interface->stSize);
	s_iTextHeight = SGUI_Text_GetMultiLineTextLines(s_szDemoText, (HMI_TEXT_DEMO_FRAME_TEXT_WIDTH(Interface->stSize)/g_stFontSize[SCROLL_TEXT_FONT_SIZE].Width))*g_stFontSize[SCROLL_TEXT_FONT_SIZE].Height;
	s_stTextDisplayArea.PosX = HMI_TEXT_DEMO_FRAME_TEXT_POSX;
	s_stTextDisplayArea.PosY = HMI_TEXT_DEMO_FRAME_TEXT_POSY;
	s_stTextDisplayArea.Width = HMI_TEXT_DEMO_FRAME_TEXT_WIDTH(Interface->stSize);
	s_stTextDisplayArea.Height = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT(Interface->stSize);
	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoScrollingText_Prepare                           **/
/** Purpose:		Preprocess after initialize.							**/
/** Resources:		None.													**/
/** Parameters:		None.													**/
/** Return:			Preprocess result.										**/
/** Limitation:		None.													**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_Prepare(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	// Paint frame edge.
	HMI_DemoScrollingText_DrawFrame(pstIFObj);
	// Start dummy heart-beat timer.
	SysTickTimerEnable(true);
	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoText_RefreshScreen								**/
/** Purpose:		Refresh current screen.									**/
/** Resources:		None.													**/
/** Parameters:		None.													**/
/** Return:			Refresh process result.									**/
/** Limitation:		None.													**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_RefreshScreen(SGUI_SCR_DEV* pstIFObj, const void* pstParameters)
{
	HMI_DemoScrollingText_DrawFrame(pstIFObj);
	SGUI_Text_DrawMultipleLinesText(pstIFObj, s_szDemoText, SCROLL_TEXT_FONT_SIZE, &s_stTextDisplayArea, s_iTextOffset, SGUI_DRAW_NORMAL);
	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoText_OnExternalEvent							**/
/** Purpose:		Process with user actions.								**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @ pstIFObj [in]: 	Screen device operation interface structure.		**/
/** @ pstEvent[in]:		User event data pointer.							**/
/** Return:			User event process result.								**/
/** Limitation:		Parameter pointer is a void type, convert to the 		**/
/**					appropriate type before use.							**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_ProcessEvent(SGUI_SCR_DEV* pstIFObj, const HMI_EVENT_BASE* pstEvent, SGUI_INT* piActionID)
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
	switch(pstEvent->iID)
	{
		case EVENT_ID_KEY_PRESS:
		{
			pstKeyEvent = (KEY_PRESS_EVENT*)pstEvent;
			uiKeyValue = KEY_CODE_VALUE(pstKeyEvent->Data.uiKeyValue);

			if(KEY_VALUE_SPACE == uiKeyValue)
			{
				iProcessAction = HMI_DEMO_PROC_CONFIRM;
			}
			break;
		}
		case EVENT_ID_TIMER:
		{
			SGUI_Text_DrawMultipleLinesText(pstIFObj, s_szDemoText, SCROLL_TEXT_FONT_SIZE, &s_stTextDisplayArea, s_iTextOffset, SGUI_DRAW_NORMAL);
			if(s_iTextOffset + s_iTextHeight == 0)
			{
				s_iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT(pstIFObj->stSize);
			}
			else
			{
				s_iTextOffset--;
			}
			break;
		}
		default:
		{
			/* No process. */
			break;
		}
	}
	if(NULL != piActionID)
	{
		*piActionID = iProcessAction;
	}

	return eProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_PostProcess								**/
/** Purpose:		Do something after user action or update screen.		**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @ iActionResult[in]: User action or system action process result.		**/
/** Return:			Post process result.									**/
/** Limitation:		None.													**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_PostProcess(SGUI_SCR_DEV* pstIFObj, HMI_ENGINE_RESULT eProcResult, SGUI_INT iActionID)
{
	if(HMI_PROCESS_SUCCESSFUL(eProcResult))
	{
		if(HMI_DEMO_PROC_CONFIRM == iActionID)
		{
			// Stop heart-beat timer.
			SysTickTimerEnable(false);
			// Go to main list.
			HMI_SwitchScreen(HMI_SCREEN_ID_DEMO_LIST, NULL);
		}
	}

	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoScrollingText_DrawFrame							**/
/** Purpose:		Draw frame edge for scroll text screen.					**/
/** Parameters:																**/
/** @ Interface[in]:	Device driver object.								**/
/** Return:			None.													**/
/** Limitation:		None.													**/
/*****************************************************************************/
void HMI_DemoScrollingText_DrawFrame(SGUI_SCR_DEV* Interface)
{
	if(NULL != Interface)
	{
        SGUI_Basic_DrawRectangle(Interface, 0, 0, RECT_WIDTH(Interface->stSize), RECT_HEIGHT(Interface->stSize), SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
		SGUI_Basic_DrawRectangle(Interface, 2, 2, RECT_WIDTH(Interface->stSize)-4, RECT_HEIGHT(Interface->stSize)-4, SGUI_COLOR_FRGCLR, SGUI_COLOR_TRANS);
	}
}
