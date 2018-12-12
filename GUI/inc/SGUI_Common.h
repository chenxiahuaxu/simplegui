#ifndef __INCLUDE_GUI_COMMON_H__
#define __INCLUDE_GUI_COMMON_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Typedef.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define		NOTICE_ICON_SIZE				(16)
#define		SGUI_NUMBER_STR_LENGTH_MAX		(12)
#define		SGUI_ISDIGIT(C)					(((C>='0')&&(C<='9'))?true:false)
#define		SGUI_ISALPHA(C)					((((C>='A')&&(C<='Z'))||((C>='a')&&(C<='z')))?true:false)
#define		SGUI_ISHEXDIGIT(C)				((((C>='A')&&(C<='F'))||((C>='a')&&(C<='f'))||((C>='0')&&(C<='9')))?true:false)
#define		SGUI_ISUPPER(C)					(((C>='A')&&(C<='Z'))?true:false)
#define		SGUI_TOUPPER(C)					(SGUI_ISUPPER(C)?(C):(C-32))
#define		SGUI_SWAP(A, B)					{A=A^B; B=A^B; A=A^B;}

#if   defined ( __CC_ARM )
	#define SGUI_ASM			__asm						// asm keyword for ARM Compiler(Keil MDK).
	#define SGUI_INLINE			__inline					// inline keyword for ARM Compiler.
	#pragma	diag_suppress		870							// Disabled "multibyte character sequence" warning.

#elif defined ( __ICCARM__ )
  #define SGUI_ASM				__asm						// < asm keyword for IAR Compiler.
  #define SGUI_INLINE			inline						// inline keyword for IAR Compiler. Only available in High optimization mode!

#elif defined ( __GNUC__ )
  #define SGUI_ASM				__asm						// asm keyword for GNU Compiler.
  #define SGUI_INLINE			inline 						// inline keyword for GNU Compiler.

#elif defined ( __TASKING__ )
  #define SGUI_ASM				__asm 						// asm keyword for TASKING Compiler.
  #define SGUI_INLINE			inline						// inline keyword for TASKING Compiler.
#endif

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
 #ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
// Only used when running in simulated environment and text encode need convert to GB2312.
SGUI_SZSTR				SGUI_Common_EncodeConvert(SGUI_CSZSTR szSourceEncode, SGUI_SZSTR szDestinationEncode, SGUI_SZSTR szSource);
  #define		_SIMPLE_GUI_ENCODE_BUFFER_SIZE	(512)
  #define		ENCODE(S)						(SGUI_Common_EncodeConvert("UTF-8", "GB2312", (char *)S))
 #else

 #endif
#else
#define		ENCODE(S)						(S)
#endif

#define     LCD_SIZE_WIDTH					                (128)
#define     LCD_SIZE_HEIGHT					                (64)

#if LCD_SIZE_WIDTH < 16
#error Define width of LCD size must greater then 16.
#endif
#if LCD_SIZE_HEIGHT < 16
#error Define height of LCD size must greater then 16.
#endif

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
SGUI_SIZE               SGUI_Common_IntegerToStringWithDecimalPoint(SGUI_INT iInteger, SGUI_UINT uiDecimalPlaces, SGUI_SZSTR pszStringBuffer, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_SIZE               SGUI_Common_IntegerToString(SGUI_INT iInteger, SGUI_SZSTR pszStringBuffer, SGUI_UINT uiBase, SGUI_INT iAlignment, SGUI_CHAR cFillCharacter);
SGUI_UINT               SGUI_Common_ConvertStringToUnsignedInteger(SGUI_SZSTR szString, SGUI_CHAR** ppcEndPointer, SGUI_UINT uiBase);
SGUI_INT                SGUI_Common_ConvertStringToInteger(SGUI_SZSTR szString, SGUI_CHAR** ppcEndPointer, SGUI_UINT uiBase);
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
void*					SGUI_Common_Allocate(SGUI_SIZE uiSize);
void					SGUI_Common_Free(void* pFreePointer);
#endif
void*                   SGUI_Common_MemoryCopy(void* pDest, const void* pSrc, SGUI_UINT uiSize);
void                    SGUI_Common_MemorySet(void* pMemoryPtr, SGUI_BYTE iSetValue, SGUI_UINT uiSize);
SGUI_SIZE               SGUI_Common_StringLength(SGUI_CSZSTR szString);
SGUI_SZSTR				SGUI_Common_StringCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc);
SGUI_SZSTR				SGUI_Common_StringLengthCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc, SGUI_SIZE uiSize);
void                    SGUI_Common_GetNowTime(SGUI_TIME* pstTime);

#endif // __INCLUDE_GUI_COMMON_H__
