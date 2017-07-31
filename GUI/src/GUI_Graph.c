/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_Graph.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: Graph adjustment interface.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Graph.h"
#include "GUI_Frame.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define	GUI_GRAPH_SCROLLBAR_WIDTH					(3)
#define GUI_GRAPH_GRAPH_AREA_WIDTH					(LCD_SIZE_WIDTH-GUI_GRAPH_SCROLLBAR_WIDTH-1)
#define GUI_GRAPH_GRAPH_AREA_HEIGHT					(LCD_SIZE_HEIGHT- GUI_GRAPH_SCROLLBAR_WIDTH-1)

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static void GUI_Graph_DrawLine(GUI_GRAPH* pstGraph, uint32_t uiStartPointIndex, uint32_t uiEndPointIndex);
static void GUI_Praph_GetPointDrawingCoordinate(GUI_GRAPH_POINT* pstDataPoint, GUI_GRAPH_CONTROL* pstControlData, GUI_GRAPH_POINT* pstDrawingPoint);

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	GUI_Graph_InitializeGraphData							**/
/** Purpose:		Initialize a graph control data.						**/
/** Resources:		List item data.											**/
/** Params:																	**/
/**	@pstList[in]:		Pointer of list data will be initialized.			**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_Graph_InitializeGraphData(GUI_GRAPH* pstGraph, GUI_GRAPH_INIT_DATA* pstInitializeData)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstGraph) && (NULL != pstInitializeData))
	{
		// Point data
		if(0 == pstInitializeData->Count)
		{
			pstGraph->Data->Points = NULL;
			pstGraph->Data->Count = 0;
		}
		else
		{
			pstGraph->Data->Points = pstInitializeData->Points;
			pstGraph->Data->Count = pstInitializeData->Count;
		}
		// Point range
		pstGraph->Control->PointRangeX = pstGraph->Control->xAxis.Max-pstGraph->Control->xAxis.Min + 1;
		pstGraph->Control->PointRangeY = pstGraph->Control->yAxis.Max-pstGraph->Control->yAxis.Min + 1;
		// Focused point index.
		if(pstInitializeData->FocusIndex >= pstGraph->Data->Count)
		{
			pstGraph->Control->FocusIndex = pstGraph->Data->Count-1;
		}
		else
		{
			pstGraph->Control->FocusIndex = pstInitializeData->FocusIndex;
		}
		// Axis scrollbar
		pstGraph->SubElement.xScrollBar.Parameter.eDirection = GUI_SCROLLBAR_HORIZONTAL;
 		pstGraph->SubElement.xScrollBar.Parameter.MaxIndex = pstGraph->Control->PointRangeX;
		pstGraph->SubElement.xScrollBar.Parameter.PosX = GUI_GRAPH_SCROLLBAR_WIDTH;
		pstGraph->SubElement.xScrollBar.Parameter.PosY = 0;
		pstGraph->SubElement.xScrollBar.Parameter.Width = LCD_SIZE_WIDTH - GUI_GRAPH_SCROLLBAR_WIDTH;
		pstGraph->SubElement.xScrollBar.Parameter.Height = GUI_GRAPH_SCROLLBAR_WIDTH;

		pstGraph->SubElement.yScrollBar.Parameter.eDirection = GUI_SCROLLBAR_VERTICAL;
		pstGraph->SubElement.yScrollBar.Parameter.MaxIndex = pstGraph->Control->PointRangeY;
		pstGraph->SubElement.yScrollBar.Parameter.PosX = 0;
		pstGraph->SubElement.yScrollBar.Parameter.PosY = GUI_GRAPH_SCROLLBAR_WIDTH;
		pstGraph->SubElement.yScrollBar.Parameter.Width = GUI_GRAPH_SCROLLBAR_WIDTH;
		pstGraph->SubElement.yScrollBar.Parameter.Height = LCD_SIZE_HEIGHT - GUI_GRAPH_SCROLLBAR_WIDTH;

		pstGraph->Control->FocusIndex = pstInitializeData->FocusIndex;
	}
}

void GUI_Graph_Refresh(GUI_GRAPH* pstGraph)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_BOX_FRAME_STRUCT				stFrameData;
	uint32_t							uiPointIndex;
	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stFrameData.Data.Title	=			NULL;
	stFrameData.Parameter.EdgeLayers =	1;
	stFrameData.Parameter.FontSize = 	GUI_FONT_SIZE_H6;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	GUI_Frame_DrawFullScreenFrame(&stFrameData);
	//GUI_Basic_DrawRectangle(0, 0, LCD_SIZE_WIDTH, LCD_SIZE_HEIGHT, GUI_COLOR_BKGCLR, GUI_COLOR_BKGCLR);
	GUI_ScrollBar_RefreshScrollBar(&(pstGraph->SubElement.xScrollBar));
	GUI_ScrollBar_RefreshScrollBar(&(pstGraph->SubElement.yScrollBar));

	if(pstGraph->Data->Count > 1)
	{
		for(uiPointIndex=0; uiPointIndex<(pstGraph->Data->Count-1); uiPointIndex++)
		{
			GUI_Graph_DrawLine(pstGraph, uiPointIndex, uiPointIndex+1);
		}
	}
}

void GUI_Graph_DrawLine(GUI_GRAPH* pstGraph, uint32_t uiStartPointIndex, uint32_t uiEndPointIndex)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	GUI_GRAPH_POINT*					pstStartPoint;
	GUI_GRAPH_POINT*					pstEndPoint;
	GUI_GRAPH_POINT						stGStartPoint;
	GUI_GRAPH_POINT						stGEndPoint;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstGraph)
	{
		// Start point.
		pstStartPoint = pstGraph->Data->Points+uiStartPointIndex;
		GUI_Praph_GetPointDrawingCoordinate(pstStartPoint, pstGraph->Control, &stGStartPoint);

		// End point.
		pstEndPoint = pstGraph->Data->Points+uiEndPointIndex;
		GUI_Praph_GetPointDrawingCoordinate(pstEndPoint, pstGraph->Control, &stGEndPoint);

		// End point.

		GUI_Basic_DrawLine(stGStartPoint.x, stGStartPoint.y, stGEndPoint.x, stGEndPoint.y, GUI_COLOR_FRGCLR);
	}
}

/*****************************************************************************/
/** Function Name:	GUI_Praph_GetPointDrawingCoordinate						**/
/** Purpose:		Convert data point to a drawing point in visible graph	**/
/**					area.													**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@pstDataPoint[in]:	Data point structure pointer.						**/
/**	@pstDrawingPoint[out]: Drawing point structure pointer.					**/
/** Return:			None.													**/
/** Notice:			None.													**/
/*****************************************************************************/
void GUI_Praph_GetPointDrawingCoordinate(GUI_GRAPH_POINT* pstDataPoint, GUI_GRAPH_CONTROL* pstControlData, GUI_GRAPH_POINT* pstDrawingPoint)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstDataPoint) && (NULL != pstDrawingPoint))
	{
		// Offset data;
		pstDrawingPoint->x = (pstDataPoint->x-pstControlData->xAxis.Min);
		pstDrawingPoint->y = (pstControlData->PointRangeY-(pstDataPoint->y-pstControlData->yAxis.Min)-1);

		pstDrawingPoint->x = GUI_GRAPH_SCROLLBAR_WIDTH+pstDrawingPoint->x*GUI_GRAPH_GRAPH_AREA_WIDTH/pstControlData->PointRangeX;
		pstDrawingPoint->y = GUI_GRAPH_SCROLLBAR_WIDTH+pstDrawingPoint->y*GUI_GRAPH_GRAPH_AREA_HEIGHT/pstControlData->PointRangeY;
	}
}
