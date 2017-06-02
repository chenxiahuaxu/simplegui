#ifndef HMI_PROCESS_H_INCLUDED
#define HMI_PROCESS_H_INCLUDED
#include "HMI_Data.h"
#include <stdio.h>

void		HMI_Action_Initialize(void);
int32_t		HMI_Action_UserActions(uint16_t uiOptions, uint16_t* uiActions);
int32_t		HMI_Action_RefreshScreen(uint32_t uiScreenID, void* pstData);
void		HMI_Action_GotoScreen(uint32_t uiCurrentScreenID, uint32_t uiDestScreenID, void* pstPreProcessData);
void		HMI_Action_GoBack(void);
#endif // HMI_PROCESS_H_INCLUDED
