#ifndef __INCLUDE_GUI_COMMON_H__
#define __INCLUDE_GUI_COMMON_H__
#include <stddef.h>
#include <stdint.h>
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
#include "LCD_OperationIF.h"
#else
// Insert platform driver head file here.
#endif //_SIMPLE_GUI_ENABLE_SIMULATOR_

#define		GUI_NUMBER_STR_LENGTH_MAX		(12)
//#define		GUI_PLACEHOLDER_CHARACTER		('*')

#if defined(_SIMPLE_GUI_ENABLE_SIMULATOR_)&&defined(_SIMPLE_GUI_ENABLE_ICONV_GB2312_)
// Only used when running in simulated environment
char*					GUI_EncodeConvert(char *szSourceEncode, char *szDestinationEncode, char *szSource);
#define		ENCODE_BUFFER_SIZE				(512)
#define		ENCODE(S)						(GUI_EncodeConvert("UTF-8", "GB2312", (char *)S))
#else
#define ENCODE(S)							(S)
#endif //defined(_SIMPLE_GUI_ENABLE_SIMULATOR_)&&defined(_SIMPLE_GUI_ENABLE_ICONV_GB2312_)

#define		GUI_ISDIGIT(C)					(((C>='0')&&(C<='9'))?true:false)
#define		GUI_ISALPHA(C)					((((C>='A')&&(C<='Z'))||((C>='a')&&(C<='z')))?true:false)
#define		GUI_ISHEXDIGIT(C)				((((C>='A')&&(C<='F'))||((C>='a')&&(C<='f'))||((C>='0')&&(C<='9')))?true:false)
#define		GUI_ISUPPER(C)					(((C>='A')&&(C<='Z'))?true:false)
#define		GUI_TOUPPER(C)					(GUI_ISUPPER(C)?(C):(C-32))

#ifndef BOOL
	#define BOOL							int
#endif // BOOL

#ifndef FALSE
	#define FALSE							(0)
#endif // TRUE

#ifndef TRUE
	#define TRUE							(!(FALSE))
#endif // TRUE

typedef struct
{
	uint16_t			Year;
	uint16_t			Month;
	uint16_t			Day;
	uint16_t			Hour;
	uint16_t			Minute;
	uint16_t			Second;
}GUI_TIME;

extern const uint8_t FONT_H8[];
extern const uint8_t FONT_H12[];
extern const uint8_t FONT_H16[];
extern const uint8_t FONT_H32[];

uint16_t				GUI_Common_IntegerToStringWithDecimalPoint(int32_t iInteger, uint16_t uiDecimalPlaces, char* szStringBuffer, int16_t iAlignment, char cFillCharacter);
uint16_t				GUI_Common_IntegerToString(int32_t iInteger, char* szStringBuffer, uint16_t uiBase, int16_t iAlignment, char cFillCharacter);
uint32_t				GUI_Common_ConvertStringToUnsignedInteger(char* szString, char** pcEndPointer, uint16_t uiBase);
int32_t					GUI_Common_ConvertStringToInteger(char* szString, char** pcEndPointer, uint16_t uiBase);
uint32_t				GUI_Common_StringLength(const char* szString);
void					GUI_Common_RefreshScreen(void);
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
void*					GUI_Common_Allocate(uint32_t uiSize);
void					GUI_Common_Free(void* pFreePointer);
#endif //_SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
void*					GUI_Common_MemoryCopy(void* pDest, const void* pSrc, uint32_t uiSize);
void					GUI_Common_GetNowTime(GUI_TIME* pstTime);


#endif // __INCLUDE_GUI_COMMON_H__
