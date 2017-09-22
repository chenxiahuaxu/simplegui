#ifndef __INCLUDE_GUI_COMMON_H__
#define __INCLUDE_GUI_COMMON_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Config.h"
#include "SGUI_Typedef.h"
#if (_SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_ > 0)
#include "LCD_OperationIF.h"
#else
// Insert platform driver head file here.
#endif //_SIMPLE_GUI_ENABLE_SIMULATOR_

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		GUI_NUMBER_STR_LENGTH_MAX		(12)
#define		GUI_ISDIGIT(C)					(((C>='0')&&(C<='9'))?true:false)
#define		GUI_ISALPHA(C)					((((C>='A')&&(C<='Z'))||((C>='a')&&(C<='z')))?true:false)
#define		GUI_ISHEXDIGIT(C)				((((C>='A')&&(C<='F'))||((C>='a')&&(C<='f'))||((C>='0')&&(C<='9')))?true:false)
#define		GUI_ISUPPER(C)					(((C>='A')&&(C<='Z'))?true:false)
#define		GUI_TOUPPER(C)					(GUI_ISUPPER(C)?(C):(C-32))

//=======================================================================//
//= Public variable declaration.									    =//
//=======================================================================//
#if (_SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_ > 0)
extern SGUI_CBYTE		SGUI_FONT_H8[];
extern SGUI_CBYTE		SGUI_FONT_H12[];
extern SGUI_CBYTE		SGUI_FONT_H16[];
extern SGUI_CBYTE		SGUI_FONT_H32[];
#endif

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
#if (_SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_ > 0) && (_SIMPLE_GUI_ENABLE_ICONV_GB2312_ > 0)
// Only used when running in simulated environment and text encode need convert to GB2312.
SGUI_PSZSTR				SGUI_Common_EncodeConvert(SGUI_PCSZSTR szSourceEncode, SGUI_PSZSTR szDestinationEncode, SGUI_PSZSTR szSource);
#define		_SIMPLE_GUI_ENCODE_BUFFER_SIZE	(512)
#define		ENCODE(S)						(SGUI_Common_EncodeConvert("UTF-8", "GB2312", (char *)S))
#else
#define		ENCODE(S)						(S)
#endif

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE				SGUI_Common_IntegerToStringWithDecimalPoint(SGUI_INT iInteger, SGUI_UINT uiDecimalPlaces, SGUI_PSZSTR szStringBuffer, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_SIZE				SGUI_Common_IntegerToString(SGUI_INT iInteger, SGUI_PSZSTR szStringBuffer, SGUI_UINT uiBase, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_UINT32				SGUI_Common_ConvertStringToUnsignedInteger(SGUI_PSZSTR szString, SGUI_PSZSTR* pcEndPointer, SGUI_UINT uiBase);
SGUI_INT32				SGUI_Common_ConvertStringToInteger(SGUI_PSZSTR szString, SGUI_PSZSTR* pcEndPointer, SGUI_UINT uiBase);
inline SGUI_SIZE		SGUI_Common_StringLength(SGUI_PCSZSTR szString);
void					SGUI_Common_RefreshScreen(void);
#if (_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_ > 0)
inline void*			SGUI_Common_Allocate(SGUI_SIZE uiSize);
inline void				SGUI_Common_Free(void* pFreePointer);
#endif
inline SGUI_PSZSTR		SGUI_Common_StringCopy(SGUI_PSZSTR szDest, SGUI_PCSZSTR szSrc);
inline SGUI_PSZSTR		SGUI_Common_StringLengthCopy(SGUI_PSZSTR szDest, SGUI_PCSZSTR szSrc, SGUI_SIZE uiSize);
inline void*			SGUI_Common_MemoryCopy(void* pDest, const void* pSrc, SGUI_SIZE uiSize);
inline void				SGUI_Common_GetNowTime(SGUI_TIME* pstTime);
void					SGUI_Common_ReadFlashROM(SGUI_ROM_ADDRESS uiAddressHead, SGUI_SIZE uiDataLength, SGUI_BYTE* pBuffer);

#endif // __INCLUDE_GUI_COMMON_H__
