#ifndef _INCLUDE_GUI_CURVE_H__
#define _INCLUDE_GUI_CURVE_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Common.h"
#include "SGUI_Basic.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//


//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct _sgui_st_curve_point_
{
	struct _sgui_st_curve_point_* pstPrev;
	SGUI_INT				iValue;
	SGUI_INT				iPosY;
	struct _sgui_st_curve_point_* pstNext;
}SGUI_CURVE_POINT;

typedef struct
{
	SGUI_RECT				stLayout;
	SGUI_CURVE_POINT*		pstStartPoint;
	SGUI_CURVE_POINT*		pstEndPoint;
	SGUI_INT				iCount;
	SGUI_RANGE				stXRange;
	SGUI_RANGE				stYRange;
}SGUI_CURVE_STRUCT;

//=======================================================================//
//= Public function declaration.									    =//
//=======================================================================//
void SGUI_Curve_Initialize(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstStartPoint, SGUI_CURVE_POINT* pstEndPoint);
void SGUI_Curve_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_CURVE_STRUCT* pstObj);
void SGUI_Curve_AppendValue(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstNewPoint);
void SGUI_Curve_RemoveValue(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstNewPoint);

#endif // __INCLUDE_GUI_REAL_GRAPH_H__
