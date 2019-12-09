#ifndef _INCLUDE_SGUI_RESOURCE_H_
#define _INCLUDE_SGUI_RESOURCE_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define	SGUI_BMP_RESOURCE_DECLARE(NAME)				extern const SGUI_BMP_RES NAME

#define	SGUI_BMP_RESOURCE_DEFINE(NAME, W, H, ...)	const SGUI_BYTE NAME##DATA[] = {__VA_ARGS__};\
													const SGUI_BMP_RES NAME = {W, H, NAME##DATA}

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_ERROR_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_INFORMATION_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_QUESTION_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_WARNING_16);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_ERROR_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_INFORMATION_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_QUESTION_24);
SGUI_BMP_RESOURCE_DECLARE(SGUI_RES_ICON_WARNING_24);

#endif // _INCLUDE_SGUI_RESOURCE_H_
