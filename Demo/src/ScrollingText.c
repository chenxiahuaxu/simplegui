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

SGUI_BOX_FRAME_STRUCT		stTextFrame = 		{	{HMI_TEXT_DEMO_FRAME_EDGE_LAYERS, SGUI_FONT_SIZE_H12},
													{NULL}};
static int32_t				iTextOffset;
static SGUI_INT				iTextHeight;
static SGUI_RECT_AREA		stTextDisplayArea;
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Initialize(void);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_Prepare(const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_RefreshScreen(const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_ProcessEvent(HMI_EVENT_TYPE eEvent, const void* pstParameters);
static HMI_ENGINE_RESULT    HMI_DemoScrollingText_PostProcess(SGUI_INT iActionResult);

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoTextActions =			{	HMI_DemoScrollingText_Initialize,
															HMI_DemoScrollingText_Prepare,
															HMI_DemoScrollingText_RefreshScreen,
															HMI_DemoScrollingText_ProcessEvent,
															HMI_DemoScrollingText_PostProcess,
														};

HMI_SCREEN_OBJECT       g_stHMI_DemoText =				{	HMI_SCREEN_ID_ANY,
															&stHMI_DemoTextActions
														};
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
	iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
	iTextHeight = SGUI_Text_GetMultiLineTextLines(szDemoText, (HMI_TEXT_DEMO_FRAME_TEXT_WIDTH/g_stFontSize[SGUI_FONT_SIZE_H12].Width))*g_stFontSize[SGUI_FONT_SIZE_H12].Height;
	stTextDisplayArea.PosX = HMI_TEXT_DEMO_FRAME_TEXT_POSX;
	stTextDisplayArea.PosY = HMI_TEXT_DEMO_FRAME_TEXT_POSY;
	stTextDisplayArea.Width = HMI_TEXT_DEMO_FRAME_TEXT_WIDTH;
	stTextDisplayArea.Height = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
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
	SGUI_Text_DrawMultipleLinesText(szDemoText, SGUI_FONT_SIZE_H12, &stTextDisplayArea, iTextOffset, GUI_DRAW_NORMAL);
	return HMI_RET_NORMAL;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoText_OnExternalEvent							**/
/** Purpose:		Process with user actions.								**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @[in]uiScreenID: 	Matched screen ID.									**/
/** @[in]pstParameters: User event data pointer.							**/
/** Return:			User event process result.								**/
/** Limitation:		Parameter pointer is a void type, convert to the 		**/
/**					appropriate type before use.							**/
/*****************************************************************************/
HMI_ENGINE_RESULT HMI_DemoScrollingText_ProcessEvent(HMI_EVENT_TYPE eEvent, const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	HMI_ENGINE_RESULT           eProcessResult;
	HMI_INTERRUPT_PARAMETER*    pstEventData;
	static SGUI_UINT            uiTimer = 3;
	SGUI_UINT16					uiKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	eProcessResult =			HMI_RET_NORMAL;
	pstEventData =				(HMI_INTERRUPT_PARAMETER*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(eEvent)
	{
        case HMI_ENGINE_EVENT_INTERRUPT:
        {
            switch(pstEventData->Source)
            {
                case HMI_INT_TIMER:
                {
                    if(uiTimer > 0)
                    {
                        uiTimer--;
                    }
                    else
                    {
                        SGUI_Text_DrawMultipleLinesText(szDemoText, SGUI_FONT_SIZE_H12, &stTextDisplayArea, iTextOffset, GUI_DRAW_NORMAL);
                        if(iTextOffset + iTextHeight == 0)
                        {
                            iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
                        }
                        else
                        {
                            iTextOffset--;
                        }
                        uiTimer = 3;
                    }

                    eProcessResult = HMI_RET_NORMAL;
                    break;
                }
                case HMI_INT_KEY:
                {
                    uiKeyValue = *(SGUI_UINT16*)pstEventData->Data;
                    if(KEY_VALUE_SPACE == uiKeyValue)
                    {
                        eProcessResult = HMI_RET_CONFIRM;
                    }
                    else
                    {
                        eProcessResult = HMI_RET_NOACTION;
                    }
                    break;
                }
                default:
                {
                    eProcessResult = HMI_RET_NOACTION;
                    break;
                }
            }
            break;
        }
        default:
        {
            break;
        }

	}
	return eProcessResult;
}

/*****************************************************************************/
/** Function Name:	HMI_DemoList_PostProcess								**/
/** Purpose:		Do something after user action or update screen.		**/
/** Resources:		List data structure and bind data if existed.			**/
/** Parameters:																**/
/** @[in]iActionResult: User action or system action process result.		**/
/** Return:			Post process result.									**/
/** Limitation:		None.													**/
/*****************************************************************************/
SGUI_INT HMI_DemoScrollingText_PostProcess(SGUI_INT iActionResult)
{
	if(HMI_RET_CONFIRM == iActionResult)
	{
		// Go to main list.
		//HMI_Action_Goto(1, NULL);
	}
	return HMI_RET_NORMAL;
}
