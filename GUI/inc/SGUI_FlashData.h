#ifndef _INCLUDED_SGUI_FLASHDATA_H_
#define _INCLUDED_SGUI_FLASHDATA_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE				SGUI_FlashData_GetFilash(SGUI_IF_OBJ* pstIFObj, SGUI_FLASH_DATA_SOURCE eDataSource, SGUI_ROM_ADDRESS adStartAddr, SGUI_SIZE sReadSize, SGUI_BYTE* pOutputBuffer);

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
//#if (_SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_ > 0)
extern SGUI_CBYTE		SGUI_FONT_H8[];
extern SGUI_CBYTE		SGUI_FONT_H12[];
extern SGUI_CBYTE		SGUI_FONT_H16[];
extern SGUI_CBYTE		SGUI_FONT_H32[];
//#endif

#endif // _INCLUDED_SGUI_FLASHDATA_H_
