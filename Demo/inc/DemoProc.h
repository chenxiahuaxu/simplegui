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
//= Public variable declaration.									    =//
//=======================================================================//
extern HMI_SCREEN_OBJECT        g_stHMI_DemoText;
extern HMI_ENGINE_OBJECT        g_stDemoEngine;
//=======================================================================//
//= Function declare.   											    =//
//=======================================================================//
void                SimpleGUI_DemoProcess(void);
HMI_ENGINE_RESULT   InitializeEngine(HMI_ENGINE_OBJECT* pstHMIEngineObject);


#endif // __INCLUDE_DEMO_PROC_H__
