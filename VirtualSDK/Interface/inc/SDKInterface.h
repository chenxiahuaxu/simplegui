#ifndef __INCLUDE_SDK_INTERFACE__
#define __INCLUDE_SDK_INTERFACE__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <stdint.h>
#include <stdbool.h>

//=======================================================================//
//= User definition.												    =//
//=======================================================================//
// Key value definition.
#define		KEY_VALUE_NONE									(0x0000)
#define		KEY_VALUE_TAB									(0x0009)
#define		KEY_VALUE_ENTER									(0x000D)
#define		KEY_VALUE_ESC									(0x001B)
#define		KEY_VALUE_SPACE									(0x0020)
#define		KEY_VALUE_LEFT									(0x013A)
#define		KEY_VALUE_UP									(0x013B)
#define		KEY_VALUE_RIGHT									(0x013C)
#define		KEY_VALUE_DOWN									(0x013D)
#define		KEY_VALUE_F1									(0x0154)
#define		KEY_VALUE_F2									(0x0155)
#define		KEY_VALUE_F3									(0x0156)
#define		KEY_VALUE_F4									(0x0157)
#define		KEY_VALUE_F5									(0x0158)
#define		KEY_VALUE_F6									(0x0159)
#define		KEY_VALUE_F7									(0x015A)
#define		KEY_VALUE_F8									(0x015B)
#define		KEY_VALUE_F9									(0x015C)
#define		KEY_VALUE_F10									(0x015D)
#define		KEY_VALUE_F11									(0x015E)
#define		KEY_VALUE_F12									(0x015F)
#define		KEY_VALUE_ENTER_PAD								(0x0172)
// User option flag value define
#define		KEY_OPTION_CTRL									(0x1000)
#define		KEY_OPTION_ALT									(0x2000)
#define		KEY_OPTION_SHIFT								(0x4000)

#define		KEY_CODE_VALUE(CODE)							(CODE & 0x0FFF)
#define		KEY_CODE_OPT(CODE)								(CODE & 0xF000)

#define 	SDK_DEFAULT_HEART_BEAT_INTERVAL_MS				(20)
#define 	SDK_DEFAULT_EVENT_SYNC_TIMEOUT_MS				(500)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
    ENV_FLAG_IDX_SDK_INIT		= 0,
    ENV_FLAG_IDX_SDK_RTC_EN,
    ENV_FLAG_IDX_SDK_RTC_EVENT,
    ENV_FLAG_IDX_SDK_TIM_SET,
    ENV_FLAG_IDX_SDK_TIM_EVENT,
    ENV_FLAG_IDX_SDK_KEY_EVENT,
    ENV_FLAG_IDX_MAX,
} ENV_FLAG_INDEX;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
void			SGUI_SDK_SetEvnetSyncFlag(ENV_FLAG_INDEX eIndex, bool bValue);
void			SGUI_SDK_SyncKeyEventData(unsigned int uiKeyCode);
unsigned int	SGUI_SDK_GetKeyEventData(void);
bool			SGUI_SDK_GetEventSyncFlag(ENV_FLAG_INDEX eIndex);
bool			SGUI_SDK_Initialize(void);
bool			SGUI_SDK_ConfigHearBeatTimer(unsigned int uiIntervalMs);
bool			SGUI_SDK_EnableRTCInterrupt(bool bEnabled);
int				SGUI_SDK_DummyMainProc(void);
void			SGUI_SDK_KeyPressInterruptEvent(unsigned int uiKeyCode);
void			SGUI_SDK_HeartBeatTimerTagEvent(void);
void			SGUI_SDK_RTCInterruptTagEvent(void);
void			SGUI_SDK_SetPixel(int uiPosX, int uiPosY, int uiPixelValue);
int				SGUI_SDK_GetPixel(int uiPosX, int uiPosY);
void			SGUI_SDK_RefreshDisplay(void);
void			SGUI_SDK_ClearDisplay(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __INCLUDE_USER_ACTION_INTERFACE__
