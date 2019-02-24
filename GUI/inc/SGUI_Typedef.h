#ifndef _INCLUDE_GUI_TYPEDEF_H_
#define _INCLUDE_GUI_TYPEDEF_H_
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "stdint.h"
#include "stddef.h"
#include <stdbool.h>

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define 	RECT_X_START(ST)			((ST).PosX)
#define 	RECT_X_END(ST)				(((ST).PosX + (ST).Width - 1))
#define 	RECT_Y_START(ST)			((ST).PosY)
#define 	RECT_Y_END(ST)				(((ST).PosY + (ST).Height - 1))
#define 	RECT_WIDTH(ST)				((ST).Width)
#define 	RECT_HEIGHT(ST)				((ST).Height)
#define 	RECT_VALID_WIDTH(ST)		((RECT_X_START(ST)>0)?RECT_WIDTH(ST):(RECT_WIDTH(ST)+RECT_X_START(ST)))
#define		RECT_VALID_HEIGHT(ST)		((RECT_Y_START(ST)>0)?RECT_HEIGHT(ST):(RECT_HEIGHT(ST)+RECT_Y_START(ST)))

#define		SGUI_DEVPF_IF_DEFINE(R, FN, PARAM) typedef R(*FN)PARAM
#define		SGUI_BMP_DATA_BUFFER_SIZE	(512)

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef char							SGUI_INT8;
typedef	unsigned char					SGUI_UINT8;
typedef int16_t							SGUI_INT16;
typedef uint16_t						SGUI_UINT16;
typedef int32_t							SGUI_INT32;
typedef	uint32_t						SGUI_UINT32;

typedef	int								SGUI_INT;
typedef unsigned int					SGUI_UINT;
typedef unsigned char					SGUI_BYTE;
typedef const unsigned char				SGUI_CBYTE;
typedef size_t							SGUI_SIZE;

typedef char*							SGUI_SZSTR;
typedef const char*						SGUI_CSZSTR;
typedef char							SGUI_CHAR;
typedef const char						SGUI_CCHAR;

typedef void*							SGUI_PTR;

typedef SGUI_SIZE						SGUI_INDEX;
#define	SGUI_INVALID_INDEX				(-1)
typedef	SGUI_UINT32						SGUI_ROM_ADDRESS;

#define	SGUI_BOOL						SGUI_INT
#define SGUI_FALSE						(0)
#define SGUI_TRUE						(!SGUI_FALSE)

typedef struct
{
	SGUI_INT							PosX;
	SGUI_INT							PosY;
	SGUI_INT							Width;
	SGUI_INT							Height;
}SGUI_RECT_AREA;

typedef struct
{
	SGUI_INT							Width;
	SGUI_INT							Height;
}SGUI_AREA_SIZE;

typedef struct
{
	SGUI_INT							PosX;
	SGUI_INT							PosY;
}SGUI_POINT;

typedef struct
{
	SGUI_UINT16							Year;
	SGUI_UINT16							Month;
	SGUI_UINT16							Day;
	SGUI_UINT16							Hour;
	SGUI_UINT16							Minute;
	SGUI_UINT16							Second;
}SGUI_TIME;

typedef enum
{
	SGUI_COLOR_BKGCLR   = 0,
	SGUI_COLOR_FRGCLR   = 1,
	SGUI_COLOR_TRANS    = 2,
}SGUI_COLOR;

typedef enum
{
	SGUI_DRAW_NORMAL    = 0,
	SGUI_DRAW_REVERSE   = 1,
}SGUI_DRAW_MODE;

// Declare data source flag here.
typedef enum
{
	SGUI_FONT_SRC_NONE	= 0,
	SGUI_FONT_SRC_H6,
	SGUI_FONT_SRC_H8,
	SGUI_FONT_SRC_H12,
	SGUI_FONT_SRC_H16,
	SGUI_NOTICE_ICON,
	SGUI_FONT_SRC_UNKNOWN,
}SGUI_FLASH_DATA_SOURCE;

typedef struct
{
	SGUI_FLASH_DATA_SOURCE				Source;
	SGUI_ROM_ADDRESS					StartAddr;
	SGUI_SIZE							Length;
}SGUI_BMP_DATA;

// Screen device operation interface type declare.
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_INITIALIZE,				(void));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_CLEAR,					(void));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_SET_POINT,				(SGUI_INT iX, SGUI_INT iY, SGUI_INT iColor));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_GET_POINT,				(SGUI_INT iX, SGUI_INT iY));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_SET_BYTE,				(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_GET_BYTE,				(SGUI_INT iPage, SGUI_INT iColumn));
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_REFRESH,					(void));

// System function interface type declare.
SGUI_DEVPF_IF_DEFINE(void,				SGUI_FN_IF_GET_RTC,					(SGUI_INT iYear, SGUI_INT iMounth, SGUI_INT iDay, SGUI_INT iWeekDay, SGUI_INT iHour, SGUI_INT iMinute, SGUI_INT iSecond));
SGUI_DEVPF_IF_DEFINE(SGUI_SIZE,			SGUI_FN_IF_READ_FLASH,				(SGUI_INT iSourceID, SGUI_ROM_ADDRESS adStartAddr, SGUI_SIZE sReadSize, SGUI_BYTE* pOutputBuffer));
SGUI_DEVPF_IF_DEFINE(SGUI_INT,			SGUI_FN_IF_GET_CHAR_INDEX,			(SGUI_CSZSTR cszSrc));

typedef struct
{
	//Screen display area size in pixel.
	SGUI_AREA_SIZE						stSize;
	//Bitmap data buffer.
	SGUI_BYTE							arrBmpDataBuffer[SGUI_BMP_DATA_BUFFER_SIZE];
    //Engine & device initialize function.
    SGUI_FN_IF_INITIALIZE				fnInitialize;
    //Clear screen function.
    SGUI_FN_IF_CLEAR					fnClearScreen;
    //Set pixel value function.
    SGUI_FN_IF_SET_POINT				fnSetPixel;
    //Get pixel value function.
    SGUI_FN_IF_GET_POINT				fnGetPixel;
    // Refresh screen display.
    SGUI_FN_IF_REFRESH					fnRefreshScreen;
}SGUI_SCR_DEV;

#endif // _INCLUDE_GUI_TYPEDEF_H_
