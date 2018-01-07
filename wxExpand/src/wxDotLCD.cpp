//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include <wx/clipbrd.h>
#include "wxDotLCD.h"

//=======================================================================//
//= Event table.													    =//
//=======================================================================//
BEGIN_EVENT_TABLE(wxDotLCD,wxPanel)
	EVT_PAINT		(wxDotLCD::_wxEvent_OnPaint)
END_EVENT_TABLE()

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
wxDotLCD::wxDotLCD(wxWindow *pclsParent, wxWindowID iWinID, const wxPoint& clsPosition):
wxPanel(pclsParent, iWinID, clsPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxPanelNameStr),
m_clsCDC(this)
{
	m_parrDisplayBuffer =			NULL;
	m_pfDrawPoint =					NULL;

	m_uiHorizontalPixelNumber =		0;
	m_uiVerticalPixelNumber =		0;
	m_uiPixelSize =					0;
	m_uiEdgeWidth =					0;
	m_bGridVisible =				false;

	m_pclsEdgeColor =				new wxColor(0x80, 0x80, 0x80, 0x00);
	m_pclsBaseColor =				new wxColor(0xFF, 0xFF, 0xFF, 0x00);
	m_pclsGridColor =				new wxColor(0x80, 0x80, 0x80, 0x00);
}

wxDotLCD::~wxDotLCD()
{
	if(NULL != m_parrDisplayBuffer)
	{
		free(m_parrDisplayBuffer);
	}

	delete m_pclsEdgeColor;
	delete m_pclsBaseColor;
	delete m_pclsGridColor;
}

void wxDotLCD::SetDisplaySizes(uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
		// Free current buffer.
	if(NULL != m_parrDisplayBuffer)
	{
		free(m_parrDisplayBuffer);
	}
	if((uiHorizontalPixelNumber > 0) && (uiVerticalPixelNumber > 0))
	{
		uint32_t		uiDisplayBufferSize;
		// Recalculate buffer size.
		m_uiHorizontalPixelNumber = uiHorizontalPixelNumber;
		m_uiVerticalPixelNumber = uiVerticalPixelNumber;
		uiDisplayBufferSize = m_uiHorizontalPixelNumber*m_uiVerticalPixelNumber;
		// Reallocate display buffer;
		m_parrDisplayBuffer = (uint32_t*)malloc(uiDisplayBufferSize*sizeof(uint32_t));
		if(NULL != m_parrDisplayBuffer)
		{
			// Clear memory.
			memset(m_parrDisplayBuffer, 0x00, uiDisplayBufferSize);
		}
	}
	else
	{
		m_uiHorizontalPixelNumber = 0;
		m_uiVerticalPixelNumber = 0;
	}
}

void wxDotLCD::GetDisplaySize(uint32_t* puiHorizontalPixelNumber, uint32_t* puiVerticalPixelNumber)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != puiHorizontalPixelNumber)
	{
		*puiHorizontalPixelNumber = m_uiHorizontalPixelNumber;
	}

	if(NULL != puiVerticalPixelNumber)
	{
		*puiVerticalPixelNumber = m_uiVerticalPixelNumber;
	}
}

void wxDotLCD::SetDisplayColors(const wxColor& clsEdgeColor, const wxColor& clsBaseColor, const wxColor& clsGridColor)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != m_pclsEdgeColor)
	{
		m_pclsEdgeColor->SetRGB(clsEdgeColor.GetRGB());
	}
	if(NULL != m_pclsBaseColor)
	{
		m_pclsBaseColor->SetRGB(clsBaseColor.GetRGB());
	}
	if(NULL != m_pclsGridColor)
	{
		m_pclsGridColor->SetRGB(clsGridColor.GetRGB());
	}
}

void wxDotLCD::SetDisplayAreaSize( uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    m_uiHorizontalPixelNumber = uiHorizontalPixelNumber;
    m_uiVerticalPixelNumber = uiVerticalPixelNumber;
}

void wxDotLCD::SetEdgeWidth(uint32_t uiEdgeWidth)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	m_uiEdgeWidth = uiEdgeWidth;
}

void wxDotLCD::SetPixelSize(uint32_t uiPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Save the pixel size value.
    m_uiPixelSize = uiPixelSize;

	if(3 > m_uiPixelSize)
    // If pixel size is less then 3, grid is fixed to NOT visible.
	{
        if(0 == m_uiPixelSize)
        // If pixel size is 0, the pixel drawing function will set to invalid.
        {
            m_pfDrawPoint = NULL;
        }
        else if(1 == m_uiPixelSize)
        // If pixel size is 1, the pixel drawing function will set to draw pixel unit by point.
        {
            m_pfDrawPoint = &DrawPointSinglePixel;
        }
        else
        {
            m_pfDrawPoint = &DrawPointMultiplePixel;
        }
	}
	else
	{
		if(true == m_bGridVisible)
		{
			m_pfDrawPoint = &DrawPointMultiplePixelWithGrid;
		}
		else
		{
			m_pfDrawPoint = &DrawPointMultiplePixel;
		}
	}
}

void wxDotLCD::SetGridVisibled(bool bGridVisible)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Save the grid visible value set.
    m_bGridVisible = bGridVisible;

    if(3 <= m_uiPixelSize)
	{
		if(true == m_bGridVisible)
		{
			m_pfDrawPoint = &DrawPointMultiplePixelWithGrid;
		}
		else
		{
			m_pfDrawPoint = &DrawPointMultiplePixel;
		}
	}
}

void wxDotLCD::CleanPanel(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t                    uiDisplayBufferSize;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiDisplayBufferSize =       m_uiHorizontalPixelNumber*m_uiVerticalPixelNumber;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	memset(m_parrDisplayBuffer, 0x00, sizeof(uint32_t)*uiDisplayBufferSize);
	RefreshDisplay();
}

void wxDotLCD::SetEdgeColor(const wxColor& clsColor)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
    if(NULL != m_pclsEdgeColor)
	{
		m_pclsEdgeColor->SetRGB(clsColor.GetRGB());
	}
}

void wxDotLCD::SetBaseColor(const wxColor& clsColor)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != m_pclsBaseColor)
	{
		m_pclsBaseColor->SetRGB(clsColor.GetRGB());
	}
}

void wxDotLCD::SetGridColor(const wxColor& clsColor)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != m_pclsGridColor)
	{
		m_pclsGridColor->SetRGB(clsColor.GetRGB());
	}
}

void wxDotLCD::OnPaint(void)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	RefreshDisplay();
}


void wxDotLCD::DrawPointSinglePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsCDCObject.DrawPoint(wxPoint(m_uiEdgeWidth+uiPosX, m_uiEdgeWidth+uiPosY));
}

void wxDotLCD::DrawPointMultiplePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsCDCObject.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*uiPixelSize, m_uiEdgeWidth+uiPosY*uiPixelSize), wxSize(uiPixelSize, uiPixelSize));
}

void wxDotLCD::DrawPointMultiplePixelWithGrid(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	clsCDCObject.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*uiPixelSize+1, m_uiEdgeWidth+uiPosY*uiPixelSize+1), wxSize(uiPixelSize-1, uiPixelSize-1));
}

/*************************************************************************/
/** Function Name:	SetPixelUnitColor                                   **/
/** Purpose:		Set a pixel RGBA color value.                       **/
/** Params:																**/
/**	@ uiPosX[in]:       X-Coordinate of pixel.                          **/
/**	@ uiPosY[in]:       Y-Coordinate of pixel.                          **/
/**	@ clsColor[in]:     Color data object.                              **/
/**	@ bRefreshNow[in]:  Refresh display at once, default to false.      **/
/** Return:			None.                                               **/
/** Notice:			This function only change the pixel color register  **/
/**                 if bRefreshNow is false(default), and when the      **/
/**                 parameter bRefreshNow is true, all pixel blocks of  **/
/**                 LCD screen panel will be repaint. if need to draw   **/
/**                 only one pixel, please use the DrawPixel function   **/
/**                 directly.                                           **/
/*************************************************************************/
void wxDotLCD::SetPixelUnitColor(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor, bool bRefreshNow)
{
    /*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((uiPosX < m_uiHorizontalPixelNumber) && (uiPosY < m_uiVerticalPixelNumber))
	{
		if(NULL != m_parrDisplayBuffer)
		{
			*(m_parrDisplayBuffer+uiPosX+(uiPosY*m_uiHorizontalPixelNumber)) = clsColor.GetRGBA();
		}
		if(true == bRefreshNow)
		{
			RefreshDisplay();
		}
	}
}

/*************************************************************************/
/** Function Name:	GetPixelUnitColor                                   **/
/** Purpose:		Get color of a pixel unit.                          **/
/** Params:																**/
/**	@ uiPosX[in]:       X-Coordinate of pixel.                          **/
/**	@ uiPosY[in]:       Y-Coordinate of pixel.                          **/
/** Return:			RGBA color value of the pixel unit.                 **/
/** Notice:			None.                                               **/
/*************************************************************************/
uint32_t wxDotLCD::GetPixelUnitColor(uint32_t uiPosX, uint32_t uiPosY)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t		uiReturnValue = 0x00;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((uiPosX < m_uiHorizontalPixelNumber) && (uiPosY < m_uiVerticalPixelNumber))
	{
		if(NULL != m_parrDisplayBuffer)
		{
			uiReturnValue = *(m_parrDisplayBuffer+uiPosX+(uiPosY*m_uiHorizontalPixelNumber));
		}
	}

	return uiReturnValue;
}

/*************************************************************************/
/** Function Name:	DrawPixel                                           **/
/** Purpose:		Draw a pixel.                                       **/
/** Params:																**/
/**	@ uiPosX[in]:       X-Coordinate of pixel.                          **/
/**	@ uiPosY[in]:       Y-Coordinate of pixel.                          **/
/**	@ clsColor[in]:     Color data object.                              **/
/** Return:			None.                                               **/
/** Notice:			Draw only one pixel directly.                       **/
/*************************************************************************/
void wxDotLCD::DrawPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(m_uiPixelSize != 0)
	{
		SetDCColor(clsColor);
		PrepareDC(m_clsCDC);
		if(m_uiPixelSize == 1)
		{
			m_clsCDC.DrawPoint(wxPoint(m_uiEdgeWidth+uiPosX, m_uiEdgeWidth+uiPosY));
		}
		else
		{
			if((true == m_bGridVisible) && (m_uiPixelSize > 2))
			{
				m_clsCDC.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*m_uiPixelSize+1, m_uiEdgeWidth+uiPosY*m_uiPixelSize+1), wxSize(m_uiPixelSize-1, m_uiPixelSize-1));
			}
			else
			{
				m_clsCDC.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*m_uiPixelSize, m_uiEdgeWidth+uiPosY*m_uiPixelSize), wxSize(m_uiPixelSize, m_uiPixelSize));
			}
		}
		SetPixelUnitColor(uiPosX, uiPosY, clsColor);
		ReleaseDC(m_clsCDC);
	}

	if(NULL != m_parrDisplayBuffer)
    {
        *(m_parrDisplayBuffer+uiPosX+(uiPosY*m_uiHorizontalPixelNumber)) = clsColor.GetRGBA();
    }

}

/*************************************************************************/
/** Function Name:	RefreshDisplay                                      **/
/** Purpose:		Repaint LCD screen panel.                           **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			Call this function after the SetPixelColor called,  **/
/**                 all pixels of the LCD panel will be repaint by the  **/
/**                 pixels's RGBA value register array.                 **/
/*************************************************************************/
void wxDotLCD::RefreshDisplay(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t				uiPaintSizeWidth, uiPaintSizeHeight;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiPaintSizeWidth =	m_uiHorizontalPixelNumber*m_uiPixelSize+m_uiEdgeWidth*2;
	uiPaintSizeHeight =	m_uiVerticalPixelNumber*m_uiPixelSize+m_uiEdgeWidth*2;

	// Set buffer size.
	if((true == m_bGridVisible) && (2 < m_uiPixelSize))
	{
		uiPaintSizeWidth++;
		uiPaintSizeHeight++;
	}
	// Create buffer image and DC object.
	wxBitmap			clsBufferImage(uiPaintSizeWidth, uiPaintSizeHeight);
	wxBufferedDC		clsBufferedDC(&m_clsCDC, clsBufferImage);

	// Draw background.
	SetDCColor(*m_pclsEdgeColor);
	PrepareDC(clsBufferedDC);
	clsBufferedDC.DrawRectangle(wxPoint(0, 0),wxSize(uiPaintSizeWidth, uiPaintSizeHeight));

	// Draw grid line.
	if((true == m_bGridVisible) && (2 < m_uiPixelSize))
	{
		SetDCColor(*m_pclsGridColor);
		PrepareDC(clsBufferedDC);
		clsBufferedDC.DrawRectangle(wxPoint(m_uiEdgeWidth, m_uiEdgeWidth),
							wxSize(	m_uiHorizontalPixelNumber*m_uiPixelSize+1,
									m_uiVerticalPixelNumber*m_uiPixelSize+1));
	}

	if(NULL != m_pfDrawPoint)
	{
		// Refresh each pixel on screen.
		for(uint32_t i_H=0; i_H<m_uiVerticalPixelNumber; i_H++)
		{
			for(uint32_t i_W=0; i_W<m_uiHorizontalPixelNumber; i_W++)
			{
				SetDCColor(wxColor(*(m_parrDisplayBuffer+(i_W+i_H*m_uiHorizontalPixelNumber))));
				PrepareDC(clsBufferedDC);
				(this->*m_pfDrawPoint)(clsBufferedDC, i_W, i_H, m_uiPixelSize);
			}
		}
	}
}

/*************************************************************************/
/** Function Name:	ResizeParent                                        **/
/** Purpose:		Resize parent window to adapt current object size.  **/
/** Params:			None.                                               **/
/** Return:			None.                                               **/
/** Notice:			Call this function after the SetPixelColor called,  **/
/**                 all pixels of the LCD panel will be repaint by the  **/
/**                 pixels's RGBA value register array.                 **/
/*************************************************************************/
void wxDotLCD::ResizeParent(void)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t						uiPaintSizeWidth, uiPaintSizeHeight;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Get drawing area size.
	uiPaintSizeWidth =	m_uiHorizontalPixelNumber*m_uiPixelSize+m_uiEdgeWidth*2;
	uiPaintSizeHeight =	m_uiVerticalPixelNumber*m_uiPixelSize+m_uiEdgeWidth*2;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((true == m_bGridVisible) && (2 <m_uiPixelSize))
	{
		GetParent()->SetClientSize(uiPaintSizeWidth+1, uiPaintSizeHeight+1);
	}
	else
	{
		GetParent()->SetClientSize(uiPaintSizeWidth, uiPaintSizeHeight);
	}
}

/*************************************************************************/
/** Function Name:	SaveScreenImageToFile                               **/
/** Purpose:		Save current panel image to a jpeg file.            **/
/** Params:			                                                    **/
/**	@ strFilePath[in]:  Save file path.                                 **/
/** Return:                                                             **/
/** @ true:             Save successfully.                              **/
/** @ false:            Save failed.                                    **/
/** Notice:			To support jpeg format, need add wxWidgets jpeg     **/
/**                 format handler in initialize(OnInit) function of    **/
/**                 the wxApp Object.                                   **/
/**                 wxImage::AddHandler(new wxJPEGHandler)              **/
/*************************************************************************/
bool wxDotLCD::SaveScreenImageToFile(const wxString& strFilePath)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	wxBitmap*               pclsBitMap;
	wxMemoryDC*             pclsMemoryDC;
	bool                    bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	bReturn =               false;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Create bitmap buffer.
	pclsBitMap = new wxBitmap(GetSize(), wxBITMAP_SCREEN_DEPTH);
	if(NULL != pclsBitMap)
    {
        pclsMemoryDC = new wxMemoryDC(*pclsBitMap);
        if(NULL != pclsMemoryDC)
        {
            bReturn = pclsMemoryDC->Blit(wxPoint(0, 0), GetSize(), &m_clsCDC, wxPoint(0, 0));
            if(true == bReturn)
            {
                bReturn = pclsBitMap->SaveFile(strFilePath, wxBITMAP_TYPE_JPEG);
            }
        }
    }
    //
    delete pclsBitMap;
    delete pclsMemoryDC;

	return bReturn;
}

/*************************************************************************/
/** Function Name:	CopyScreenImageToClipBoard                          **/
/** Purpose:		Copy current screen image to clip board.            **/
/** Params:			None.                                               **/
/** Return:                                                             **/
/** @ true:             Copy successfully.                              **/
/** @ false:            Copy failed.                                    **/
/** Notice:			None.                                               **/
/*************************************************************************/
bool wxDotLCD::CopyScreenImageToClipBoard(void)
{
    /*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t                uiPictureWidth, uiPictureHeight;
	wxBitmap*               pclsDCBufferBitmap;
	wxMemoryDC*             pclsDCBuffer;
	bool                    bReturn;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiPictureWidth =        GetSize().GetX();
	uiPictureHeight =       GetSize().GetY();
	pclsDCBufferBitmap =    new wxBitmap(uiPictureWidth, uiPictureHeight, wxBITMAP_SCREEN_DEPTH);
	pclsDCBuffer =          new wxMemoryDC(*pclsDCBufferBitmap);
	bReturn =               true;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pclsDCBufferBitmap) && (NULL != pclsDCBuffer))
    {
        if(true == wxTheClipboard->Open())
        {
            pclsDCBuffer->Blit(0, 0, uiPictureWidth, uiPictureHeight, &m_clsCDC, 0, 0);
            wxTheClipboard->SetData(new wxBitmapDataObject(*pclsDCBufferBitmap));
            wxTheClipboard->Close();
        }
        else
        {
            bReturn = false;
        }
    }

    delete pclsDCBufferBitmap;
    delete pclsDCBuffer;

	return bReturn;
}

