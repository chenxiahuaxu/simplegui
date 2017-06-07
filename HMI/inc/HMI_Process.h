#ifndef HMI_PROCESS_H_INCLUDED
#define HMI_PROCESS_H_INCLUDED
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "HMI_Data.h"
#include "UserAction.h"
#include <stdio.h>

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void		HMI_Action_Initialize(void);
int32_t		HMI_Action_ExternalEventProcess(uint32_t uiScreenID, void* pstData);
int32_t		HMI_Action_InternalEventProcess(uint32_t uiScreenID, void* pstData);
void		HMI_Action_Goto(uint32_t uiDestScreenID, const void* pstPreProcessData);
void		HMI_Action_GoBack(void);
#endif // HMI_PROCESS_H_INCLUDED
