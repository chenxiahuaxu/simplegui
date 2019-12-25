/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Curve.c												**/
/** Author: Polarix														**/
/** Description: Draw frames on screen.									**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Curve.h"

//=======================================================================//
//= Static function declaration.									    =//
//=======================================================================//
static void SGUI_Curve_CalculatePointPosY(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstPoint);

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Curve_Initialize								**/
/** Purpose:		Draw a frame on screen, just like a window frame.	**/
/** Params:																**/
/**	@ pstObj[in]:	Curve object pointer.								**/
/**	@ arrstValueArray[in]: Points data array.							**/
/**	@ iArraySize[in]: Array size.										**/
/** Return:			None.												**/
/** Notice:			none.												**/
/*************************************************************************/
void SGUI_Curve_Initialize(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstStartPoint, SGUI_CURVE_POINT* pstEndPoint)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstStartPoint) && (NULL != pstEndPoint))
	{
		pstObj->pstStartPoint = pstStartPoint;
		pstObj->pstEndPoint = pstEndPoint;
		pstObj->pstStartPoint->pstNext = pstObj->pstEndPoint;
		pstObj->pstStartPoint->pstPrev = NULL;
		pstObj->pstEndPoint->pstPrev = pstObj->pstStartPoint;
		pstObj->pstEndPoint->pstNext = NULL;
		pstObj->iCount = 2;
        // Draw frame edge
		pstObj->stXRange.iMin = 0;
		pstObj->stXRange.iMax = 0;
		pstObj->stYRange.iMin = 0;
		pstObj->stYRange.iMax = 0;
	}
}

void SGUI_Curve_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_CURVE_STRUCT* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_POINT					stLineStartPoint;
	SGUI_POINT					stLineEndPoint;
	SGUI_CURVE_POINT*			pstLineStartValue;
	SGUI_CURVE_POINT*			pstLineEndValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstDeviceIF) && (NULL != pstObj))
	{
		/* Clean up background. */
		SGUI_Basic_DrawRectangle(pstDeviceIF, pstObj->stLayout.iPosX, pstObj->stLayout.iPosY, pstObj->stLayout.iWidth, pstObj->stLayout.iHeight, SGUI_COLOR_BKGCLR, SGUI_COLOR_BKGCLR);
		if(pstObj->iCount > 1)
		{
			pstLineStartValue = pstObj->pstStartPoint;
			pstLineEndValue = pstLineStartValue->pstNext;
			while(NULL != pstLineEndValue->pstNext)
			{
				/* Line point X coordinate. */
				stLineStartPoint.iPosX = RECT_X_END(pstObj->stLayout);
				stLineEndPoint.iPosX = 5;
				/* Line point Y coordinate. */
				stLineStartPoint.iPosY = pstLineStartValue->iPosY;
				stLineEndPoint.iPosY = pstLineEndValue->iPosY;
				/* Paint visible line. */
				if(SGUI_Basic_PointIsInArea(&(pstObj->stLayout), &stLineStartPoint) || SGUI_Basic_PointIsInArea(&(pstObj->stLayout), &stLineEndPoint))
				{
					SGUI_Basic_DrawLineInArea(pstDeviceIF, &stLineStartPoint, &stLineEndPoint, &(pstObj->stLayout), SGUI_COLOR_FRGCLR);
				}
				if(stLineEndPoint.iPosX > RECT_X_START(pstObj->stLayout))
				{
					stLineStartPoint.iPosX -= 5;
					stLineEndPoint.iPosX -= 5;
				}
				else
				{
					break;
				}
			}
		}
	}
}

void SGUI_Curve_AppendValue(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstNewPoint)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstNewPoint))
	{
		pstNewPoint->pstPrev = NULL;
		pstNewPoint->pstNext = pstObj->pstStartPoint;
		pstObj->pstStartPoint = pstNewPoint;
		SGUI_Curve_CalculatePointPosY(pstObj, pstNewPoint);
		pstObj->iCount++;
	}
}

void SGUI_Curve_RemoveValue(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstPoint)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstPoint) && (pstObj->iCount > 2))
	{
		if(pstObj->pstStartPoint == pstPoint)
		{
			pstObj->pstStartPoint = pstPoint->pstNext;
			pstObj->pstStartPoint->pstPrev = NULL;
		}
		else if(pstObj->pstEndPoint == pstPoint)
		{
			pstObj->pstEndPoint = pstPoint->pstPrev;
			pstObj->pstEndPoint->pstNext = NULL;
		}
		else
		{
			pstPoint->pstPrev->pstNext = pstPoint->pstNext;
			pstPoint->pstNext->pstPrev = pstPoint->pstPrev;
			pstPoint->pstNext = NULL;
			pstPoint->pstPrev = NULL;
		}
		pstObj->iCount--;
	}
}

void SGUI_Curve_CalculatePointPosY(SGUI_CURVE_STRUCT* pstObj, SGUI_CURVE_POINT* pstPoint)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_INT					iValueArea;
	SGUI_INT					iAbsoluteValue;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstPoint))
	{
		iValueArea = pstObj->stYRange.iMax - pstObj->stYRange.iMin + 1;
		iAbsoluteValue = pstPoint->iValue - pstObj->stYRange.iMin;
		pstPoint->iPosY = iAbsoluteValue*RECT_HEIGHT(pstObj->stLayout)/iValueArea;
		pstPoint->iPosY = RECT_HEIGHT(pstObj->stLayout)-pstPoint->iPosY;
		pstPoint->iPosY = pstPoint->iPosY + RECT_Y_START(pstObj->stLayout)-1;
	}
}
