/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo01_Text.c											**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "DemoProc.h"
#include "SGUI_Text.h"
#include "SGUI_Frame.h"
#include "HMI_Engine.h"
#include <stdio.h>

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
#define		HMI_TEXT_DEMO_FRAME_TEXT_WIDTH				(LCD_SIZE_WIDTH-(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)*2)
#define		HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT				(LCD_SIZE_HEIGHT-(HMI_TEXT_DEMO_FRAMR_EDGE_WIDTH+1)*2)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Initialize(void);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Prepare(const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_RefreshScreen(const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_ProcessEvent(HMI_EVENT_TYPE eEvent, const HMI_EVENT* pstEvent);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
// Demo text.
static char					szDemoText[] =
{
"  欢迎来到SimpleGUI演示工程，本工程用于演示SimpleGUI各API的显示效果、\
使用方法以及运作机理，在演示过程中，您可以通过键盘输入与SimpleGUI演示工\
程进行交互。\n\
  按“空格”键开始演示。"
};

static int32_t				m_iTextOffset;
static SGUI_INT				m_iTextHeight;
static SGUI_RECT_AREA		m_stTextDisplayArea;

static SGUI_BOX_FRAME_STRUCT stTextFrame =				{{HMI_TEXT_DEMO_FRAME_EDGE_LAYERS, SGUI_FONT_SIZE_H12}, {NULL}};
HMI_SCREEN_ACTION		m_stHMIDemo_ScrollingTextActions = {
														HMI_DemoScrollingText_Initialize,
														HMI_DemoScrollingText_Prepare,
														HMI_DemoScrollingText_RefreshScreen,
														HMI_DemoScrollingText_ProcessEvent,
														HMI_DemoScrollingText_PostProcess,};

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_OBJECT       g_stHMIDemo_ScrollingText =		{
														HMI_SCREEN_ID_DEMO_SCROLLING_TEXT,
														&m_stHMIDemo_ScrollingTextActions};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	HMI_DemoScrollingText_Initialize                        **/
/** Purpose:		Initialize screen data.									**/
/** Resources:		Current screen display or control data.					**/
/** Parameters:		None.													**/
/** Return:			Initialize process result.								**/
/** Limitation:		None.													**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_Initialize(void)
{
	m_iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
	m_iTextHeight = SGUI_Text_GetMultiLineTextLines(szDemoText, (HMI_TEXT_DEMO_FRAME_TEXT_WIDTH/g_stFontSize[SGUI_FONT_SIZE_H12].Width))*g_stFontSize[SGUI_FONT_SIZE_H12].Height;
	m_stTextDisplayArea.PosX = HMI_TEXT_DEMO_FRAME_TEXT_POSX;
	m_stTextDisplayArea.PosY = HMI_TEXT_DEMO_FRAME_TEXT_POSY;
	m_stTextDisplayArea.Width = HMI_TEXT_DEMO_FRAME_TEXT_WIDTH;
	m_stTextDisplayArea.Height = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
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
HMI_ENGINE_RESULT HMI_DemoScrollingText_Prepare(const void* pstParameters)
{
	SGUI_Frame_DrawFullScreenFrame(&stTextFrame);
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
HMI_ENGINE_RESULT HMI_DemoScrollingText_RefreshScreen(const void* pstParameters)
{
	SGUI_Frame_DrawFullScreenFrame(&stTextFrame);
	SGUI_Text_DrawMultipleLinesText(szDemoText, SGUI_FONT_SIZE_H12, &m_stTextDisplayArea, m_iTextOffset, GUI_DRAW_NORMAL);
	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoText_OnExternalEvent							**/
/** Purpose:		Process with user actions.								**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @uiScreenID[in]: 	Matched screen ID.									**/
/** @pstEvent[in]:		User event data pointer.							**/
/** Return:			User event process result.								**/
/** Limitation:		Parameter pointer is a void type, convert to the 		**/
/**					appropriate type before use.							**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_ProcessEvent(HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	static SGUI_UINT            uiTimer = 3;
	SGUI_UINT16*				parrKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(HMI_ENGINE_EVENT_ACTION == eEventType)
	{
		if(NULL != pstEvent)
		{
			switch(pstEvent->Action)
			{
				case HMI_ENGINE_ACTION_KEY_PRESS:
				{
					parrKeyValue = (SGUI_UINT16*)pstEvent->Data;
                    if(KEY_VALUE_SPACE == *(parrKeyValue+1))
                    {
                        eProcessResult = HMI_RET_FOLLOWUP;
                    }
                    else
                    {
                        eProcessResult = HMI_RET_NOACTION;
                    }
                    break;
				}
				case HMI_ENGINE_ACTION_ON_TIMER:
				{
					if(uiTimer > 0)
                    {
                        uiTimer--;
                    }
                    else
                    {
                        SGUI_Text_DrawMultipleLinesText(szDemoText, SGUI_FONT_SIZE_H12, &m_stTextDisplayArea, m_iTextOffset, GUI_DRAW_NORMAL);
                        if(m_iTextOffset + m_iTextHeight == 0)
                        {
                            m_iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
                        }
                        else
                        {
                            m_iTextOffset--;
                        }
                        uiTimer = 3;
                    }
                    eProcessResult = HMI_RET_NOACTION;
                    break;
				}
				default:
                {
                    eProcessResult = HMI_RET_NOACTION;
                    break;
                }
			}
		}
	}
	return eProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_PostProcess								**/
/** Purpose:		Do something after user action or update screen.		**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @iActionResult[in]: User action or system action process result.		**/
/** Return:			Post process result.									**/
/** Limitation:		None.													**/
/*****************************************************************************/
SGUI_INT HMI_DemoScrollingText_PostProcess(SGUI_INT iActionResult)
{
	if(HMI_RET_FOLLOWUP == iActionResult)
	{
		// Go to main list.
		HMI_Goto(HMI_SCREEN_ID_DEMO_LIST, NULL);
	}
	return HMI_RET_NORMAL;
}
