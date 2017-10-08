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
#include "SGUI_Frame.h"
#include "SGUI_Notice.h"
#include "SGUI_VariableBox.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define						VARIABLE_DEMO_FONT_SIZE				(SGUI_FONT_SIZE_H12)
#define						FRAME_TITLE_HEIGHT					(g_stFontSize[SGUI_FONT_SIZE_H12].Height+2)
#define						TEXT_VARIABLE_LENGTH				(20)

#define						VARIABLE_BOX_WIDTH					(100)
#define						VARIABLE_BOX_POSX					(10)
#define						VARIABLE_BOX_NUMBER_POSY			(19)
#define						VARIABLE_BOX_TEXT_POSY				(38)
//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static SGUI_INT			HMI_DemoVariableBox_Initialize(void);
static SGUI_INT			HMI_DemoVariableBox_PreProcess(const void* pstParameters);
static SGUI_INT			HMI_DemoVariableBox_RefrershScreen(void);
static SGUI_INT			HMI_DemoVariableBox_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoVariableBox_OnExternalEvent(SGUI_INT uiScreenID, const void* pstParameters);
static SGUI_INT			HMI_DemoVariableBox_PostProcess(SGUI_INT iActionResult);
static void				HMI_DemoVariableBox_DrawFrame(SGUI_PSZSTR szTitle);

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
static SGUI_INT_VARBOX_STRUCT	stNumberVariableBox =	{VARIABLE_BOX_POSX+2, VARIABLE_BOX_NUMBER_POSY+2, VARIABLE_BOX_WIDTH, SGUI_FONT_SIZE_H12, -50, 100, 0};
static char						arrTextVariable[TEXT_VARIABLE_LENGTH+1] = {"ABCDEFG"};
static SGUI_TEXT_VARBOX_STRUCT	stTextVariableBox =		{VARIABLE_BOX_POSX+2, VARIABLE_BOX_TEXT_POSY+2, VARIABLE_BOX_WIDTH, SGUI_FONT_SIZE_H16, 0, TEXT_VARIABLE_LENGTH, arrTextVariable};
static const char				stFrameTitleDefault[] =	{"数值/文本编辑演示"};
static const char*				szFrameTitle =			stFrameTitleDefault;
static uint16_t					uiFocusedFlag;
static const char				szHelpNoticeText[] =	{"TAB键切换焦点编辑框。\n上下箭头调整数值。\n左右箭头调整焦点字符。\n按空格键继续。"};
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
HMI_SCREEN_OBJECT       g_stHMI_DemoVariableBox =	{	HMI_SCREEN_ID_ANY,
														&stHMI_DemoVariableBoxActions
														};

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
SGUI_INT HMI_DemoVariableBox_Initialize(void)
{
	uiFocusedFlag = 0;
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoVariableBox_PreProcess(const void* pstParameters)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	HMI_DemoVariableBox_DrawFrame((SGUI_PSZSTR)szFrameTitle);
	// Show notice
	SGUI_Notice_RefreshNotice(szHelpNoticeText, 0, SGUI_ICON_INFORMATION);
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoVariableBox_RefrershScreen(void)
{
	return HMI_RET_NORMAL;
}

SGUI_INT HMI_DemoVariableBox_OnInternalEvent(SGUI_INT uiScreenID, const void* pstParameters)
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
	return HMI_RET_NOACTION;
}

SGUI_INT HMI_DemoVariableBox_OnExternalEvent(SGUI_INT uiScreenID,const void* pstParameters)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iProcessResult;
	USER_ACT_KEYPRESS*			pstUserEvent;
	static	uint32_t			iInitialized = 0;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iProcessResult =			HMI_RET_NORMAL;
	pstUserEvent =				(USER_ACT_KEYPRESS*)pstParameters;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(0 == iInitialized)
	{
		switch(pstUserEvent->KeyValue[0])
		{
			case KEY_VALUE_SPACE:
			{
				if(0 == iInitialized)
				{
					// Draw frame
					HMI_DemoVariableBox_DrawFrame((SGUI_PSZSTR)szFrameTitle);
					// Draw number box
					SGUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, g_stFontSize[stNumberVariableBox.FontSize].Height+6, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_REVERSE);
					// Draw text box
					SGUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4,  g_stFontSize[stTextVariableBox.FontSize].Height+6, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
					SGUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_NORMAL);
					iInitialized = 1;
				}
				break;
			}
			break;
			{
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
		}
	}
	else
	{
		switch(pstUserEvent->KeyValue[0])
		{
			case KEY_VALUE_TAB:
			{
				uiFocusedFlag = ((uiFocusedFlag+1)%2);
				if(0 == uiFocusedFlag)
				{
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_REVERSE);
					SGUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_NORMAL);
				}
				else
				{
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_NORMAL);
					SGUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_REVERSE);
				}
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
			case KEY_VALUE_ESC:
			{
				iProcessResult = HMI_RET_CANCEL;
				break;
			}
			case KEY_VALUE_LEFT:
			{
				if(1 == uiFocusedFlag)
				{
					if(stTextVariableBox.FocusIndex > 0)
					{
						stTextVariableBox.FocusIndex--;
						SGUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NONE);
					}
				}
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
			case KEY_VALUE_UP:
			{
				if(1 == uiFocusedFlag)
				{
					SGUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_PREV);
				}
				else
				{
					stNumberVariableBox.Value++;
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_REVERSE);
				}
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
			case KEY_VALUE_RIGHT:
			{
				if(1 == uiFocusedFlag)
				{
					if(stTextVariableBox.FocusIndex < (stTextVariableBox.MaxTextLength-1))
					{
						stTextVariableBox.FocusIndex++;
						SGUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NONE);
					}
				}
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
			case KEY_VALUE_DOWN:
			{
				if(1 == uiFocusedFlag)
				{
					SGUI_TextVariableBox_ChangeCharacter(&stTextVariableBox, GUI_DRAW_REVERSE, GUI_TEXT_ASCII, SGUI_TXT_VARBOX_OPT_NEXT);
				}
				else
				{
					stNumberVariableBox.Value--;
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_REVERSE);
				}
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
			case KEY_VALUE_ENTER:
			{
				if(1 == uiFocusedFlag)
				{
					szFrameTitle = stTextVariableBox.Value;
					HMI_DemoVariableBox_DrawFrame((SGUI_PSZSTR)szFrameTitle);
					// Draw number box
					SGUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_NUMBER_POSY, VARIABLE_BOX_WIDTH+4, g_stFontSize[stNumberVariableBox.FontSize].Height+6, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
					SGUI_IntegerVariableBox_Refresh(&stNumberVariableBox, SGUI_CENTER, GUI_DRAW_NORMAL);
					// Draw text box
					SGUI_Basic_DrawRectangle(VARIABLE_BOX_POSX, VARIABLE_BOX_TEXT_POSY, VARIABLE_BOX_WIDTH+4, g_stFontSize[stTextVariableBox.FontSize].Height+6, GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
					SGUI_TextVariableBox_Refresh(&stTextVariableBox, GUI_DRAW_REVERSE);
				}
				break;
			}
			break;
			{
				iProcessResult = HMI_RET_NOACTION;
				break;
			}
		}
	}
	return iProcessResult;
}

SGUI_INT HMI_DemoVariableBox_PostProcess(SGUI_INT iActionResult)
{
	if(HMI_RET_CANCEL == iActionResult)
	{
		HMI_Action_GoBack();
	}
	return HMI_RET_NORMAL;
}

void HMI_DemoVariableBox_DrawFrame(SGUI_PSZSTR szTitle)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_BOX_FRAME_STRUCT	stFrameData;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stFrameData.Parameter.EdgeLayers = 2;
	stFrameData.Parameter.FontSize = SGUI_FONT_SIZE_H12;
	stFrameData.Data.Title = szTitle;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Draw frame
	SGUI_Frame_DrawFullScreenFrame(&stFrameData);
}
