#ifndef __INCLUDE_DEMO_PROC_H__
#define __INCLUDE_DEMO_PROC_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"
#include "SGUI_Common.h"
#include "HMI_Engine.h"
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
#include "DemoResource_UTF8.h"
#include "SDKInterface.h"
#else
#include "DemoResource_GB2312.h"
#endif
#include <stdlib.h>
#include <stdio.h>
//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
// HMI action type
typedef enum
{
	EVENT_ID_UNKNOW				= 0,
	// User defined action type.
	EVENT_ID_KEY_PRESS,
	EVENT_ID_TIMER,
	EVENT_ID_RTC,
	// User defined action above.
	EVENT_ID_MAX
}EVENT_ID;

typedef struct
{
	SGUI_UINT16		uiKeyValue;
}KEY_EVENT_DATA;

typedef struct
{
	SGUI_INT		iValue;
}DUMMY_DATA_EVENT_DATA;

HMI_EVENT_TYPE_DECLARE(KEY_PRESS_EVENT, KEY_EVENT_DATA)
HMI_EVENT_TYPE_DECLARE(DATA_EVENT, DUMMY_DATA_EVENT_DATA);

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		HMI_SCREEN_ID_DEMO_SCROLLING_TEXT			(1001)
#define		HMI_SCREEN_ID_DEMO_LIST						(1002)
#define		HMI_SCREEN_ID_DEMO_TEXT_NOTICE				(1003)
#define		HMI_SCREEN_ID_DEMO_RTC_NOTICE				(1004)
#define		HMI_SCREEN_ID_DEMO_VARIABLE_BOX				(1005)
#define		HMI_SCREEN_ID_DEMO_REAL_TIME_GRAPH			(1006)

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern HMI_ENGINE_OBJECT        g_stDemoEngine;
extern HMI_SCREEN_OBJECT        g_stHMIDemo_ScrollingText;
extern HMI_SCREEN_OBJECT		g_stHMIDemo_List;
extern HMI_SCREEN_OBJECT		g_stHMIDemo_TextNotice;
extern HMI_SCREEN_OBJECT		g_stHMIDemo_RTCNotice;
extern HMI_SCREEN_OBJECT        g_stHMIDemo_VariableBox;
extern HMI_SCREEN_OBJECT		g_stHMI_DemoRealtimeGraph;
//=======================================================================//
//= Function declare.   											    =//
//=======================================================================//
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
HMI_ENGINE_RESULT	InitializeEngine(void);
HMI_ENGINE_RESULT	EventProcess(const HMI_EVENT_BASE* pstEvent);
int					DemoMainProcess(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __INCLUDE_DEMO_PROC_H__
