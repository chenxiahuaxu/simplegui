/*************************************************************************/
/** Copyright.															**/
/** FileName: Common.cpp												**/
/** Author: Polarix														**/
/** Description: Common data and functions define.						**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "Common.h"

PixelPanelParameter			g_stParameters;


void SetDefaultParameterData(PixelPanelParameter* pstParameter)
{
	if(NULL != pstParameter)
	{
		// Appearance
		pstParameter->HorizontalPixelNumber = PARAM_DEFAULT_PIXEL_NUM_H;
		pstParameter->VerticalPixelNumber = PARAM_DEFAULT_PIXEL_NUM_V;
		pstParameter->PixelSize = PARAM_DEFAULT_PIXEL_SIZE;
		pstParameter->EnableGrid = PARAM_DEFAULT_GRID_ENABLE;

		// ScreenColor
		pstParameter->PanelColor = LCD_COLOR_OBJ_BKG;
		pstParameter->PixelColor = LCD_COLOR_OBJ_PIX;
		pstParameter->GridColor = LCD_COLOR_OBJ_GRID;
	}
}
