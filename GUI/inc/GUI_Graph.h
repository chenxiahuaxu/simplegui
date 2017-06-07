#ifndef __INCLUDE_GUI_GRAPH_H__
#define __INCLUDE_GUI_GRAPH_H__
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Basic.h"
#include "GUI_ScrollBar.h"
#include "LCD_VirtualDeviceParameter.h"

//=======================================================================//
//= Data type definition.											    =//
//=======================================================================//
typedef struct
{
	int32_t					x;
	int32_t					y;
}GUI_GRAPH_POINT;

typedef struct
{
	int32_t					Min;
	int32_t					Max;
}GUI_GRAPH_AXIS;

typedef struct
{
	GUI_GRAPH_POINT*		Points;
	uint32_t				Count;
}GUI_GRAPH_DATA;

typedef struct
{
	GUI_GRAPH_AXIS			xAxis;
	GUI_GRAPH_AXIS			yAxis;
	uint32_t				FocusIndex;
	uint32_t				PointRangeX;
	uint32_t				PointRangeY;
	GUI_GRAPH_POINT			LastDrawingPoint;
}GUI_GRAPH_CONTROL;

typedef struct
{
	GUI_SCROLLBAR_STRUCT	xScrollBar;
	GUI_SCROLLBAR_STRUCT	yScrollBar;
}GUI_GRAPH_SUBELEMENT;

typedef struct
{
	GUI_GRAPH_DATA*			Data;
	GUI_GRAPH_CONTROL*		Control;
	GUI_GRAPH_SUBELEMENT	SubElement;
}GUI_GRAPH;

typedef struct
{
	uint32_t				Count;
	uint32_t				FocusIndex;
	GUI_GRAPH_POINT*		Points;
}GUI_GRAPH_INIT_DATA;

void GUI_Graph_InitializeGraphData(GUI_GRAPH* pstGraph, GUI_GRAPH_INIT_DATA* pstInitializeData);
void GUI_Graph_Refresh(GUI_GRAPH* pstGraph);
#endif // __INCLUDE_GUI_GRAPH_H__
