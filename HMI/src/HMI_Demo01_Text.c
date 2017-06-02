/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo01_Text.c											**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for list control interface.					**/
/** History:															**/
/**	Polarix	2017/6/1	1.0.0.0		New create.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo01_Text.h"
#include "GUI_Text.h"
#include "GUI_Frame.h"
#include "HMI_Process.h"
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

GUI_BOX_FRAME_STRUCT		stTextFrame = 		{	{HMI_TEXT_DEMO_FRAME_EDGE_LAYERS, GUI_FONT_SIZE_H12},
													{NULL}};
static int32_t				iTextOffset;
static int32_t				iTextHeight;
static RECTANGLE			stTextDisplayArea;
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t				HMI_DemoText_Initialize(void);
static int32_t				HMI_DemoText_PreProcess(void* pstParameters);
static int32_t				HMI_DemoText_UserActions(uint16_t uiOptions, uint16_t* puiActions);
static int32_t				HMI_DemoText_UpdateScreen(uint32_t uiScreenID, void* pstParameters);
static int32_t				HMI_DemoText_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoTextActions =			{	HMI_DemoText_Initialize,
															HMI_DemoText_PreProcess,
															HMI_DemoText_UserActions,
															HMI_DemoText_UpdateScreen,
															HMI_DemoText_PostProcess,
														};
HMI_SCREEN				g_stHMI_DemoText =				{	HMI_REFRESH_DATA_LABEL_ANY,
															&stHMI_DemoTextActions
														};
//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
int32_t	HMI_DemoText_Initialize(void)
{
	iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
	iTextHeight = 120;//GUI_Notice_GetNoticeLines(szDemoText, (HMI_TEXT_DEMO_FRAME_TEXT_WIDTH/g_stFontSize[GUI_FONT_SIZE_H12].Width));
	stTextDisplayArea.PosX = HMI_TEXT_DEMO_FRAME_TEXT_POSX;
	stTextDisplayArea.PosY = HMI_TEXT_DEMO_FRAME_TEXT_POSY;
	stTextDisplayArea.Width = HMI_TEXT_DEMO_FRAME_TEXT_WIDTH;
	stTextDisplayArea.Height = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoText_PreProcess(void* pstParameters)
{
	GUI_Frame_DrawFullScreenFrame(&stTextFrame);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoText_UserActions(uint16_t uiOptions, uint16_t* puiActions)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	uint16_t					uiKeyValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RESULT_NORMAL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	uiKeyValue = *(puiActions+0);
	if(KEY_VALUE_SPACE == uiKeyValue)
	{
		iProcessResult = HMI_RESULT_CONFIRM;
	}
	else
	{
		iProcessResult = HMI_RESULT_NOACTION;
	}
	return iProcessResult;
}

int32_t	HMI_DemoText_UpdateScreen(uint32_t uiScreenID, void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	int32_t						iProcessResult;
	static uint32_t				uiTimer = 5;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(g_stHMI_DemoText.ScreenID == uiScreenID)
	{
		if(uiTimer > 0)
		{
			uiTimer--;
		}
		else
		{
			GUI_Text_DrawMultipleLinesText(ENCODE(szDemoText), GUI_FONT_SIZE_H12, &stTextDisplayArea, iTextOffset, GUI_DRAW_NORMAL);
			if(iTextOffset + iTextHeight == 0)
			{
				iTextOffset = HMI_TEXT_DEMO_FRAME_TEXT_HEIGHT;
			}
			else
			{
				iTextOffset--;
			}
			uiTimer = 5;
		}


		iProcessResult = HMI_RESULT_NORMAL;
	}
	else
	{
		iProcessResult = HMI_RESULT_NOACTION;
	}

	return iProcessResult;
}

int32_t HMI_DemoText_PostProcess(int32_t iActionResult)
{
	if(HMI_RESULT_CONFIRM == iActionResult)
	{
		// Go to main list.
		HMI_Action_GotoScreen(g_stHMI_DemoText.ScreenID, 1, NULL);
	}
	return HMI_RESULT_NORMAL;
}
