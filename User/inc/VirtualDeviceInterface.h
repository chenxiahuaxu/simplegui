#ifndef __INCLUDE_VIRTUAL_DEVICE_INTERFACE_H__
#define __INCLUDE_VIRTUAL_DEVICE_INTERFACE_H__
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//=======================================================================//
//= User definition.												    =//
//=======================================================================//
// Key value definition.
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
#define		KEY_OPTION_NONE									(0x0000)
#define		KEY_OPTION_CTRL									(0x0001)
#define		KEY_OPTION_ALT									(0x0002)
#define		KEY_OPTION_SHIFT								(0x0004)

#define		KEY_PRESS_EVENT_VALUE_MAX						(4)

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void USR_ACT_OnInitialize(void);
void USR_ACT_OnKeyPress(bool bShift, bool bCtrl, bool bAlt, uint16_t uiKeyCode);
void USR_ACT_OnTimerEventProcess(void);
void USR_ACT_OnRTCUpdateEventProcess(uint16_t uiYear, uint16_t uiMonth, uint16_t uiDay, uint16_t uiHour, uint16_t uiMinute, uint16_t uiSecond);

#endif // __INCLUDE_VIRTUAL_DEVICE_INTERFACE_H__
