/*************************************************************************/
/** Copyright.															**/
/** FileName: HMI_Demo04_Graph.c										**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: HMI demo for graph interface.							**/
/** History:															**/
/**	Polarix	2017/6/5	1.0.0.0		New create.							**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Demo05_VariableBox.h"
#include "GUI_Frame.h"
#include "GUI_Notice.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define						VARIABLE_DEMO_FONT_SIZE				(GUI_FONT_SIZE_H12)
#define						FRAME_TITLE_HEIGHT					(g_stFontSize[GUI_FONT_SIZE_H12].Height+2)
#define						TEXT_VARIABLE_LENGTH				(20)

#define						VARIABLE_BOX_WIDTH					(100)
#define						VARIABLE_BOX_HEIGHT					(18)
#define						VARIABLE_BOX_POSX					(10)
#define						VARIABLE_BOX_NUMBER_POSY			(20)
#define						VARIABLE_BOX_TEXT_POSY				(40)
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static int32_t			HMI_DemoVariableBox_Initialize(void);
static int32_t			HMI_DemoVariableBox_PreProcess(const void* pstParameters);
static int32_t			HMI_DemoVariableBox_RefrershScreen(void);
static int32_t			HMI_DemoVariableBox_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoVariableBox_OnExternalEvent(uint32_t uiScreenID, const void* pstParameters);
static int32_t			HMI_DemoVariableBox_PostProcess(int32_t iActionResult);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static GUI_INT_VARBOX_STRUCT	stNumberVariableBox =	{VARIABLE_BOX_POSX+2, VARIABLE_BOX_NUMBER_POSY+2, VARIABLE_BOX_WIDTH, -50, 100, 0};
static char						arrTextVariable[TEXT_VARIABLE_LENGTH] = {"ABCDEFG"};
static GUI_TXT_VARBOX_STRUCT	stTextVariableBox =		{VARIABLE_BOX_POSX+2, VARIABLE_BOX_TEXT_POSY+2, VARIABLE_BOX_WIDTH, 0, TEXT_VARIABLE_LENGTH, arrTextVariable};
static const char				stFrameTitle[] =		{"数值/文本编辑演示"};
static uint16_t					uiFocusedFlag;
static const char				szHelpNoticeText[] =	{"按下TAB键切换焦点编辑框。\n按下上下箭头调整焦点编辑框中的值。\n按下左右箭头调整焦点字符"};
static uint16_t					uiNeedHelp =			5;

//=======================================================================//
//= Global variable declaration.									    =//
//=======================================================================//
HMI_SCREEN_ACTION		stHMI_DemoVariableBoxActions = {HMI_DemoVariableBox_Initialize,
														HMI_DemoVariableBox_PreProcess,
														HMI_DemoVariableBox_RefrershScreen,
														HMI_DemoVariableBox_OnInternalEvent,
														HMI_DemoVariableBox_OnExternalEvent,
														HMI_DemoVariableBox_PostProcess,
														};
HMI_SCREEN				g_stHMI_DemoVariableBox =	{	HMI_SCREEN_ID_ANY,
														&stHMI_DemoVariableBoxActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
int32_t HMI_DemoVariableBox_Initialize(void)
{
	uiFocusedFlag = 0;
	GUI_Notice_RefreshNotice(szHelpNoticeText, 0, GUI_ICON_INFORMATION);
	return HMI_RESULT_NORMAL;
}

static int32_t HMI_DemoVariableBox_PreProcess(const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_BOX_FRAME_STRUCT	stFrameData;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stFrameData.Parameter.EdgeLayers = 2;
	stFrameData.Parameter.FontSize = GUI_FONT_SIZE_H12;
	stFrameData.Data.Title = (char*)stFrameTitle;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	GUI_Frame_DrawFullScreenFrame(&stFrameData);
	// Draw number box
	GUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_BOX_HEIGHT, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
	GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_REVERSE);
    // Draw text box
	GUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_BOX_HEIGHT, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
	GUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_NORMAL);
	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoVariableBox_RefrershScreen(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_BOX_FRAME_STRUCT	stFrameData;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stFrameData.Parameter.EdgeLayers = 2;
	stFrameData.Parameter.FontSize = GUI_FONT_SIZE_H12;
	stFrameData.Data.Title = (char*)stFrameTitle;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	GUI_Frame_DrawFullScreenFrame(&stFrameData);
	// Draw number box
	GUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_BOX_HEIGHT, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
	GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_REVERSE);
    // Draw text box
	GUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, VARIABLE_BOX_HEIGHT, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
	GUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_NORMAL);

	return HMI_RESULT_NORMAL;
}

int32_t HMI_DemoVariableBox_OnInternalEvent(uint32_t uiScreenID, const void* pstParameters)
{
	/*----------------------------------*/
	/* Process	 						*/
	/*----------------------------------*/
	if(uiNeedHelp > 0)
	{
		uiNeedHelp--;
		HMI_Action_Goto(3, szHelpNoticeText);
	}
	else
	{
		HMI_DemoVariableBox_PreProcess(NULL);
	}
	return HMI_RESULT_NOACTION;
}

int32_t HMI_DemoVariableBox_OnExternalEvent(uint32_t uiScreenID,const void* pstParameters)
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
	pstUserEvent =				(USER_ACT_KEYPRESS*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	switch(pstUserEvent->KeyValue[0])
	{
		case KEY_VALUE_TAB:
		{
			uiFocusedFlag = ((uiFocusedFlag+1)%2);
			if(0 == uiFocusedFlag)
			{
				GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_REVERSE);
				GUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_NORMAL);
			}
			else
			{
				GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_NORMAL);
				GUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_REVERSE);
			}
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
		case KEY_VALUE_ESC:
		{
			iProcessResult = HMI_RESULT_CANCEL;
			break;
		}
		case KEY_VALUE_LEFT:
		{
			if(1 == uiFocusedFlag)
			{
				if(stTextVariableBox.FocusIndex > 0)
				{
					stTextVariableBox.FocusIndex--;
					GUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, GUI_TXT_VARBOX_OPT_NONE);
				}
			}
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
		case KEY_VALUE_UP:
		{
			if(1 == uiFocusedFlag)
			{
				GUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, GUI_TXT_VARBOX_OPT_PREV);
			}
			else
			{
				stNumberVariableBox.Value++;
				GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_REVERSE);
			}
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
		case KEY_VALUE_RIGHT:
		{
			if(1 == uiFocusedFlag)
			{
				if(stTextVariableBox.FocusIndex != (TEXT_VARIABLE_LENGTH-1))
				{
					stTextVariableBox.FocusIndex++;
					GUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, GUI_TXT_VARBOX_OPT_NONE);
				}
			}
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
		case KEY_VALUE_DOWN:
		{
			if(1 == uiFocusedFlag)
			{
				GUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, GUI_TXT_VARBOX_OPT_NEXT);
			}
			else
			{
				stNumberVariableBox.Value--;
				GUI_IntegerVariableBox_Refresh(&stNumberVariableBox, GUI_CENTER, GUI_DRAW_REVERSE);
			}
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
		break;
		{
			iProcessResult = HMI_RESULT_NOACTION;
			break;
		}
	}
	return iProcessResult;
}

int32_t HMI_DemoVariableBox_PostProcess(int32_t iActionResult)
{
	if(HMI_RESULT_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return HMI_RESULT_NORMAL;
}
