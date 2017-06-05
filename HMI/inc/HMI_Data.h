#ifndef __INCLUDE_HMI_DATA_H__
#define __INCLUDE_HMI_DATA_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
// HMI process result
#define 	HMI_RESULT_NORMAL								(0)
#define 	HMI_RESULT_INITIALIZE							(1)
#define		HMI_RESULT_CONFIRM								(2)
#define		HMI_RESULT_CANCEL								(3)
#define 	HMI_RESULT_FOLLOWUP								(4)
#define		HMI_RESULT_NOACTION								(5)
#define		HMI_RESULT_INPROCESS							(6)
#define		HMI_RESULT_ERROR								(-1)
#define 	HMI_RESULT_INVALID_DATA							(-2)
#define		HMI_RESULT_INVALID_PARAMETER					(-3)
#define		HMI_RESULT_UNDEFINED_ACTION						(-4)

#define		HMI_PROCESS_SUCCESSFUL(RESULT)					((RESULT >= 0))

// GoBack history size
#define		HMI_GOBACK_HISTORY_SIZE_MAX						(20)

// Parameter post label.
#define		HMI_SCREEN_ID_ANY								(0xFFFFFFFF)	// This label means parameter will posted to every screen.
// Add screen parameter label definition here,
// it's defined between 0 and the maximum value of the label defined type.
#define		HMI_REFRESH_DATA_LABEL_RTC						(1)


// Start screen definition
#define		HMI_SCREEN_START								(0)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
// Data type define.
typedef struct
{
	int32_t							(*Initialize)(void);
	int32_t							(*PreProcess)(void* pstParameters);
	int32_t							(*InternalEventProcess)(uint32_t uiScreenID, void* pstParameters);
	int32_t							(*ExternalEventProcess)(uint32_t uiScreenID, void* pstParameters);
	int32_t							(*PostProcess)(int32_t iProcessResult);
}HMI_SCREEN_ACTION;

typedef struct _t_hmi_element_
{
	uint32_t						ScreenID;
	HMI_SCREEN_ACTION*				Actions;
}HMI_SCREEN;


typedef struct
{
	uint16_t						Year;
	uint16_t						Month;
	uint16_t						Day;
	uint16_t						Hour;
	uint16_t						Minute;
	uint16_t						Second;
}HMI_RTC_TIME;

void			HMI_ScreenData_Initialize(void);
void			HMI_ScreenData_SetCurrentScreen(uint32_t uiScreenIndex);
HMI_SCREEN*		HMI_ScreenData_GetCurrentScreen(void);
bool			HMI_ScreenData_PushHistory(void);
size_t			HMI_ScreenData_PopHistory(void);

#endif // __INCLUDE_HMI_DATA_H__
