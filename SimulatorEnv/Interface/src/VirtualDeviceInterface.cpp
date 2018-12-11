/*************************************************************************/
/** Copyright.															**/
/** FileName: VirtualDeviceInterface.c                                  **/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: Virtual device operation interface.                    **/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "VirtualDeviceInterface.h"
#include "LCDFrame.h"

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	VDIF_SetPixel                                       **/
/** Purpose:		Set virtual device pixel register data.             **/
/** Params:																**/
/**	@ iPosX[in]:		Pixel x-coordinate on display panel.			**/
/**	@ iPosY[in]:		Pixel y-coordinate on display panel.			**/
/**	@ iPixelValue[out]:	Pixel value, 0 for clear, 1 for set.			**/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void VDIF_SetPixel(int iPosX, int iPosY, int iPixelValue)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    LCDFrame*           pclsMainFrameObjectPtr;

    /*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
    pclsMainFrameObjectPtr = LCDFrame::GetInstance();

    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    if(NULL != pclsMainFrameObjectPtr)
    {
        pclsMainFrameObjectPtr->SetLCDPixel(iPosX, iPosY, iPixelValue);
    }
}

/*************************************************************************/
/** Function Name:	VDIF_GetPixel                                       **/
/** Purpose:		Get a pixel value form virtual device register.     **/
/** Params:																**/
/**	@ iPosX[in]:		Pixel x-coordinate on display panel.			**/
/**	@ iPosY[in]:		Pixel y-coordinate on display panel.		    **/
/** Return:			Pixel state, 0 for cleared, 1 for set.              **/
/** Notice:			None.                                               **/
/*************************************************************************/
int VDIF_GetPixel(int iPosX, int iPosY)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    LCDFrame*           pclsMainFrameObjectPtr;
    int					iPixelValue;

    /*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
    pclsMainFrameObjectPtr = LCDFrame::GetInstance();

    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    if(NULL != pclsMainFrameObjectPtr)
    {
        iPixelValue = pclsMainFrameObjectPtr->GetLCDPixel(iPosX, iPosY);
    }
    else
    {
        iPixelValue = 0;
    }

    return iPixelValue;
}

/*************************************************************************/
/** Function Name:	VDIF_RefreshDisplay.                                **/
/** Purpose:		Refresh virtual device display.                     **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void VDIF_RefreshDisplay(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    LCDFrame*           pclsMainFrameObjectPtr;

    /*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
    pclsMainFrameObjectPtr = LCDFrame::GetInstance();

    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    if(NULL != pclsMainFrameObjectPtr)
    {
        pclsMainFrameObjectPtr->RefreshLCD();
    }
}

/*************************************************************************/
/** Function Name:	VDIF_ClearDisplay.                                  **/
/** Purpose:		Clear screen display.                               **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			None.                                               **/
/*************************************************************************/
void VDIF_ClearDisplay(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    LCDFrame*           pclsMainFrameObjectPtr;

    /*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
    pclsMainFrameObjectPtr = LCDFrame::GetInstance();

    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    if(NULL != pclsMainFrameObjectPtr)
    {
        pclsMainFrameObjectPtr->ClearLCD();
        pclsMainFrameObjectPtr->RefreshLCD();
    }
}

