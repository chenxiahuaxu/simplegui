#include <wx/clipbrd.h>
#include "wxPixelPanel.h"

BEGIN_EVENT_TABLE(wxPixelPanel,wxPanel)
	EVT_PAINT		(wxPixelPanel::wxEvent_OnPaint)
END_EVENT_TABLE()
wxPixelPanel::wxPixelPanel(wxWindow *parent, wxWindowID winid, const wxPoint& pos,  const wxSize& size, long style, const wxString& name):
wxPanel(parent, winid, pos, size, style, name),
m_CDC(this)
{
	m_pclsParent = parent;
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

wxPixelPanel::~wxPixelPanel()
{
	if(NULL != m_parrDisplayBuffer)
	{
		free(m_parrDisplayBuffer);
	}

	delete m_pclsEdgeColor;
	delete m_pclsBaseColor;
	delete m_pclsGridColor;
}

void wxPixelPanel::SetDisplaySizes(uint32_t uiEdgeWidth, uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber, uint32_t uiPixelSize, bool bGridVisible)
{
	// Set grid visible status.
	m_uiEdgeWidth =		uiEdgeWidth;
	m_bGridVisible =	bGridVisible;
	m_uiPixelSize =		uiPixelSize;

	if(m_uiPixelSize == 0)
	{
		m_pfDrawPoint = NULL;
	}
	else if(m_uiPixelSize == 1)
	{
		m_pfDrawPoint = &DrawPointSinglePixel;
	}
	else
	{
		if((true == bGridVisible) && (m_uiPixelSize > 2))
		{
			m_pfDrawPoint = &DrawPointMultiplePixelWithGrid;
		}
		else
		{
			m_pfDrawPoint = &DrawPointMultiplePixel;
		}
	}

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

void wxPixelPanel::GetDisplaySize(uint32_t* puiEdgeWidth, uint32_t* puiHorizontalPixelNumber, uint32_t* puiVerticalPixelNumber, uint32_t* puiPixelSize, bool* pbGridVisible)
{
	if(NULL != puiEdgeWidth)
	{
		*puiEdgeWidth = m_uiEdgeWidth;
	}

	if(NULL != puiHorizontalPixelNumber)
	{
		*puiHorizontalPixelNumber = m_uiHorizontalPixelNumber;
	}

	if(NULL != puiVerticalPixelNumber)
	{
		*puiVerticalPixelNumber = m_uiVerticalPixelNumber;
	}

	if(NULL != puiPixelSize)
	{
		*puiPixelSize = m_uiPixelSize;
	}

	if(NULL != pbGridVisible)
	{
		*pbGridVisible = m_bGridVisible;
	}
}

void wxPixelPanel::SetDisplayColors(const wxColor& clsEdgeColor, const wxColor& clsBaseColor, const wxColor& clsGridColor)
{
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

void wxPixelPanel::SetDisplayAreaSize( uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber)
{
    m_uiHorizontalPixelNumber = uiHorizontalPixelNumber;
    m_uiVerticalPixelNumber = uiVerticalPixelNumber;
}

void wxPixelPanel::SetEdgeWidth(uint32_t uiEdgeWidth)
{
	m_uiEdgeWidth = uiEdgeWidth;
}

void wxPixelPanel::SetPixelSize(uint32_t uiPixelSize)
{
    m_uiPixelSize = uiPixelSize;
}

void wxPixelPanel::SetGridVisibled(bool bGridVisible)
{
    m_bGridVisible = bGridVisible;
}

void wxPixelPanel::CleanPanel(void)
{
	uint32_t		uiDisplayBufferSize;
	uiDisplayBufferSize = m_uiHorizontalPixelNumber*m_uiVerticalPixelNumber;
	memset(m_parrDisplayBuffer, 0x00, sizeof(uint32_t)*uiDisplayBufferSize);
	RefreshDisplay();
}

void wxPixelPanel::SetEdgeColor(const wxColor& clsColor)
{
    if(NULL != m_pclsEdgeColor)
	{
		m_pclsEdgeColor->SetRGB(clsColor.GetRGB());
	}
}

void wxPixelPanel::SetBaseColor(const wxColor& clsColor)
{
	if(NULL != m_pclsBaseColor)
	{
		m_pclsBaseColor->SetRGB(clsColor.GetRGB());
	}
}

void wxPixelPanel::SetGridColor(const wxColor& clsColor)
{
	if(NULL != m_pclsGridColor)
	{
		m_pclsGridColor->SetRGB(clsColor.GetRGB());
	}
}

void wxPixelPanel::OnPaint(void)
{
	RefreshDisplay();
}


void wxPixelPanel::DrawPointSinglePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
	clsCDCObject.DrawPoint(wxPoint(m_uiEdgeWidth+uiPosX, m_uiEdgeWidth+uiPosY));
}

void wxPixelPanel::DrawPointMultiplePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
	clsCDCObject.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*uiPixelSize, m_uiEdgeWidth+uiPosY*uiPixelSize), wxSize(uiPixelSize, uiPixelSize));
}

void wxPixelPanel::DrawPointMultiplePixelWithGrid(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize)
{
	clsCDCObject.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*uiPixelSize+1, m_uiEdgeWidth+uiPosY*uiPixelSize+1), wxSize(uiPixelSize-1, uiPixelSize-1));
}

void wxPixelPanel::SetPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor, bool bRefreshNow)
{
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

uint32_t wxPixelPanel::GetPixel(uint32_t uiPosX, uint32_t uiPosY)
{
	uint32_t		uiReturnValue = 0x00;

	if((uiPosX < m_uiHorizontalPixelNumber) && (uiPosY < m_uiVerticalPixelNumber))
	{
		if(NULL != m_parrDisplayBuffer)
		{
			uiReturnValue = *(m_parrDisplayBuffer+uiPosX+(uiPosY*m_uiHorizontalPixelNumber));
		}
	}

	return uiReturnValue;
}

void wxPixelPanel::DrawPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(m_uiPixelSize != 0)
	{
		SetDCColor(clsColor);
		PrepareDC(m_CDC);
		if(m_uiPixelSize == 1)
		{
			m_CDC.DrawPoint(wxPoint(m_uiEdgeWidth+uiPosX, m_uiEdgeWidth+uiPosY));
		}
		else
		{
			if((true == m_bGridVisible) && (m_uiPixelSize > 2))
			{
				m_CDC.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*m_uiPixelSize+1, m_uiEdgeWidth+uiPosY*m_uiPixelSize+1), wxSize(m_uiPixelSize-1, m_uiPixelSize-1));
			}
			else
			{
				m_CDC.DrawRectangle(wxPoint(m_uiEdgeWidth+uiPosX*m_uiPixelSize, m_uiEdgeWidth+uiPosY*m_uiPixelSize), wxSize(m_uiPixelSize, m_uiPixelSize));
			}
		}
		SetPixel(uiPosX, uiPosY, clsColor);
		ReleaseDC(m_CDC);
	}
}


void wxPixelPanel::RefreshDisplay(void)
{
	uint32_t				uiPaintSizeWidth, uiPaintSizeHeight;

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
	wxBufferedDC		clsBufferedDC(&m_CDC, clsBufferImage);

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

void wxPixelPanel::ResizeParent(void)
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
		m_pclsParent->SetClientSize(uiPaintSizeWidth+1, uiPaintSizeHeight+1);
	}
	else
	{
		m_pclsParent->SetClientSize(uiPaintSizeWidth, uiPaintSizeHeight);
	}
}

bool wxPixelPanel::SaveToFile(const wxString& CStrFilePath)
{
	// Create and initialize bitmap.
	uint32_t			uiPictureWidth, uiPictureHeight;

	// Get panel size
	uiPictureWidth = GetSize().GetX();
	uiPictureHeight = GetSize().GetY();

	wxBitmap		CBitMap(uiPictureWidth, uiPictureHeight, wxBITMAP_SCREEN_DEPTH);
	wxMemoryDC		CMemoryDC(CBitMap);
	CMemoryDC.Blit(wxPoint(0, 0), wxSize(uiPictureWidth, uiPictureHeight), &m_CDC, wxPoint(0, 0));
	return CBitMap.SaveFile(CStrFilePath, wxBITMAP_TYPE_JPEG);
}

bool wxPixelPanel::CopyToClipBoard(void)
{
	uint32_t			uiPictureWidth, uiPictureHeight;
	// Get panel size
	uiPictureWidth = GetSize().GetX();
	uiPictureHeight = GetSize().GetY();

	wxBitmap		CBitMap(uiPictureWidth, uiPictureHeight, wxBITMAP_SCREEN_DEPTH);
	wxMemoryDC		CMemoryDC(CBitMap);
	CMemoryDC.Blit(wxPoint(0, 0), wxSize(uiPictureWidth, uiPictureHeight), &m_CDC, wxPoint(0, 0));

	if(wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxBitmapDataObject(CBitMap));
		wxTheClipboard->Close();
		return true;
	}
	else
	{
		return false;
	}
}

wxWindow* wxPixelPanel::GetParentWindow(void)
{
	return m_pclsParent;
}
