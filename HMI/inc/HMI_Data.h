#ifndef __INCLUDE_HMI_DATA_H__
#define __INCLUDE_HMI_DATA_H__
#include <stdint.h>
#include <stddef.h>

// HMI process result
#define 	HMI_RESULT_NORMAL								(0)
#define 	HMI_RESULT_INITIALIZE							(1)
#define		HMI_RESULT_CONFIRM								(2)
#define		HMI_RESULT_CANCEL								(3)
#define 	HMI_RESULT_FOLLOWUP								(4)
#define		HMI_RESULT_UNDEFINED_ACTION						(5)
#define		HMI_RESULT_ERROR								(-1)
#define 	HMI_RESULT_INVALID_DATA							(-2)
#define		HMI_RESULT_INVALID_PARAMETER					(-3)

#define		HMI_PROCESS_SUCCESSFUL(RESULT)					((RESULT >= 0))

// Global HMI action process judgment flags.
#define 	STATE_CONTROL_FLAG_NONE							(0x0000)
#define		STATE_CONTROL_FLAG_ENABLE_DATA_UPDATE			(0x0001)
#define		STATE_CONTROL_FLAG_ENABLE_UI_UPDATE				(0x0002)
#define		STATE_CONTROL_FLAG_SKIP_USER_ACTION				(0x0004)

// GoBack history size
#define		HMI_GOBACK_HISTORY_SIZE_MAX						(20)

// Data type define.
typedef struct _t_hmi_element_
{
	int32_t							(*Initialize)(void);
	int32_t							(*PreProcess)(void* pstParameters);
	int32_t							(*UserActionCallBack)(uint16_t uiOptions, uint16_t* uiActions);
	int32_t							(*UpdateScreen)(void* pstParameters);
	int32_t							(*PostProcess)(int32_t iProcessResult);
}HMI_SCREEN;

void			HMI_ScreenData_Initialize(void);
void			HMI_ScreenData_SetCurrentScreen(size_t uiScreenIndex);
HMI_SCREEN*		HMI_ScreenData_GetCurrentScreen(void);

#endif // __INCLUDE_HMI_DATA_H__
