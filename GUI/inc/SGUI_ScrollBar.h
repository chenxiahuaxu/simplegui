#ifndef __INCLUDE_GUI_SCROLLBAR__
#define __INCLUDE_GUI_SCROLLBAR__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Basic.h"
#include "SGUI_Common.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef enum
{
	SGUI_SCROLLBAR_VERTICAL = 0,						//Vertical scroll bar.
	SGUI_SCROLLBAR_HORIZONTAL,						//Horizontal scroll bar.
}SGUI_SCROLLBAR_DIRECTION;

typedef struct
{
	SGUI_INT					iPosX;
	SGUI_INT					iPosY;
	SGUI_INT					iWidth;
	SGUI_INT					iHeight;
	SGUI_SIZE					sMaxIndex;
	SGUI_SIZE					sIndex;
	SGUI_SCROLLBAR_DIRECTION	eDirection;
}SGUI_SCROLLBAR_STRUCT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//												--
void	SGUI_ScrollBar_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_SCROLLBAR_STRUCT* pstScrollBar);

#endif // __INCLUDE_GUI_SCROLLBAR_STRUCT__
