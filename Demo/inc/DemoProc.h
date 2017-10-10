#ifndef __INCLUDE_DEMO_PROC_H__
#define __INCLUDE_DEMO_PROC_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"
#include "HMI_Engine.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
    HMI_INT_UNKNOW,
    HMI_INT_EXINT,
    HMI_INT_KEY,
    HMI_INT_DATA,
    HMI_INT_TIMER,
    HMI_INT_RTC,
}HMI_INTERRUPT_SOURCE;

typedef struct
{
    HMI_INTERRUPT_SOURCE    Source;
    void*                   Data;
}HMI_INTERRUPT_PARAMETER;

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		HMI_SCREEN_ID_DEMO_SCROLLING_TEXT			(1001)
#define		HMI_SCREEN_ID_DEMO_LIST						(1002)
#define		HMI_SCREEN_ID_DEMO_TEXT_NOTICE				(1003)
#define		HMI_SCREEN_ID_DEMO_VARIABLE_BOX				(1004)

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
extern HMI_ENGINE_OBJECT        g_stDemoEngine;
extern HMI_SCREEN_OBJECT        g_stHMIDemo_ScrollingText;
extern HMI_SCREEN_OBJECT		g_stHMIDemo_List;
extern HMI_SCREEN_OBJECT		g_stHMIDemo_TextNotice;
extern HMI_SCREEN_OBJECT        g_stHMIDemo_VariableBox ;
//=======================================================================//
//= Function declare.   											    =//
//=======================================================================//
void                SimpleGUI_DemoProcess(void);
HMI_ENGINE_RESULT   InitializeEngine(HMI_ENGINE_OBJECT* pstHMIEngineObject);
HMI_ENGINE_RESULT	EventProcess(HMI_EVENT_TYPE eEventType, const HMI_EVENT* pstEvent);


#endif // __INCLUDE_DEMO_PROC_H__
