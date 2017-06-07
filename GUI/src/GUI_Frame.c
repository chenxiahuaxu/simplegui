/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_Frame.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: Draw frames on screen.									**/
/** History:															**/
/**	Polarix	2017/5/24	1.0.0.0		New create.							**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Frame.h"

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
void GUI_Frame_DrawFullScreenFrame(GUI_BOX_FRAME_STRUCT* pstFrameData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t				uiEdgeLayerIndex;
	uint16_t				uiEdgeRectanglePosX, uiEdgeRectanglePosY;
	uint16_t				uiEdgeRectangleWidth, uiEdgeRectangleHeight;
	uint16_t				uiTitleLineWidth;
	RECTANGLE				stTitleTextDisplayArea;
	RECTANGLE				stTitleTextDataArea = {0, 0, 0, 0};

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	if(NULL != pstFrameData)
	{
		uiEdgeRectanglePosX		= 0;
		uiEdgeRectanglePosY		= 0;
		uiEdgeRectangleWidth	= LCD_SIZE_WIDTH;
		uiEdgeRectangleHeight	= LCD_SIZE_HEIGHT;
		uiTitleLineWidth		= g_stFontSize[pstFrameData->Parameter.FontSize].Height+2;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstFrameData)
	{
        // Draw frame edge
		for(uiEdgeLayerIndex = 0; uiEdgeLayerIndex<pstFrameData->Parameter.EdgeLayers; uiEdgeLayerIndex++)
		{
			GUI_Basic_DrawRectangle(	uiEdgeRectanglePosX, uiEdgeRectanglePosY,
										uiEdgeRectangleWidth, uiEdgeRectangleHeight,
										GUI_COLOR_FRGCLR, GUI_COLOR_BKGCLR);
			uiEdgeRectanglePosX += 2;
			uiEdgeRectanglePosY += 2;
			uiEdgeRectangleWidth -= 4;
			uiEdgeRectangleHeight -= 4;
		}

		// Draw Title if exist.
		if(NULL != pstFrameData->Data.Title)
		{
			if(pstFrameData->Parameter.EdgeLayers > 0)
			{
				GUI_Basic_DrawLine((pstFrameData->Parameter.EdgeLayers*2-1), (pstFrameData->Parameter.EdgeLayers*2-1+uiTitleLineWidth),
									LCD_SIZE_WIDTH-pstFrameData->Parameter.EdgeLayers*2, (pstFrameData->Parameter.EdgeLayers*2-1+uiTitleLineWidth),
									GUI_COLOR_FRGCLR);
				stTitleTextDisplayArea.PosX		= pstFrameData->Parameter.EdgeLayers*2;
				stTitleTextDisplayArea.PosY		= pstFrameData->Parameter.EdgeLayers*2;
				stTitleTextDisplayArea.Width	= LCD_SIZE_WIDTH-pstFrameData->Parameter.EdgeLayers*4;
				stTitleTextDisplayArea.Height	= g_stFontSize[pstFrameData->Parameter.FontSize].Height;
			}
			else
			{
				GUI_Basic_DrawLine(	0, (pstFrameData->Parameter.EdgeLayers*2+uiTitleLineWidth),
									LCD_SIZE_WIDTH-1, (pstFrameData->Parameter.EdgeLayers*2+uiTitleLineWidth),
									GUI_COLOR_FRGCLR);
				stTitleTextDisplayArea.PosX		= 1;
				stTitleTextDisplayArea.PosY		= 1;
				stTitleTextDisplayArea.Width	= LCD_SIZE_WIDTH-2;
				stTitleTextDisplayArea.Height	= g_stFontSize[pstFrameData->Parameter.FontSize].Height;
			}
			GUI_Text_DrawSingleLineText(	ENCODE(pstFrameData->Data.Title), pstFrameData->Parameter.FontSize,
											&stTitleTextDisplayArea, &stTitleTextDataArea, GUI_DRAW_NORMAL);
		}
	}
}
