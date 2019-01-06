
#include "wxLCD.h"

wxLCD::wxLCD(wxWindow *pclsParent, wxWindowID iWinID, const wxPoint& clsPosition, const wxSize& clsSizeInPixel):
wxLCDBase(pclsParent, iWinID, clsPosition, clsSizeInPixel)
{
	m_clsPixelLColour.Set(0x00FFFFFF);
	m_clsPixelHColour.Set(0x00000000);
}

wxLCD::~wxLCD(void)
{

}

void wxLCD::SetPanelColour(const wxColour& clsPanelColour, bool bRefreshNow)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Replace old panel color.
	ReplaceColour(m_clsPixelLColour, clsPanelColour);
	// Set new panel color.
	m_clsPixelLColour = clsPanelColour;
	// Refresh display.
	if(true == bRefreshNow)
	{
		RefreshDisplay();
	}
}

void wxLCD::SetPixelColour(const wxColour& clsPixelColour, bool bRefreshNow)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Replace old pixel color.
	ReplaceColour(m_clsPixelHColour, clsPixelColour);
	// Set new pixel color.
	m_clsPixelHColour = clsPixelColour;
	// Refresh display.
	if(true == bRefreshNow)
	{
		RefreshDisplay();
	}
}

int wxLCD::GetPixel(const int iPosX, const int iPosY)
{
	int				iReturn;

	if(WX_LCD_PIX_RGB(GetPixelUnitColor(iPosX, iPosY)) == WX_LCD_PIX_RGB(m_clsPixelHColour.GetRGBA()))
	{
		iReturn = 1;
	}
	else
	{
		iReturn = 0;
	}

	return iReturn;
}

void wxLCD::SetPixel(const int iPosX, const int iPosY, const int iValue)
{
	if(1 == iValue)
	{
		SetPixelUnitColor(iPosX, iPosY, m_clsPixelHColour);
	}
	else
	{
		SetPixelUnitColor(iPosX, iPosY, m_clsPixelLColour);
	}
}

void wxLCD::CleanScreen(void)
{
	SetDisplayBuffer(m_clsPixelLColour);
}

void wxLCD::SetParameter(PixelPanelParameter* pstPanelParameter)
{
	if(NULL != pstPanelParameter)
	{
		SetPixelSize(pstPanelParameter->PixelSize);
	    SetGridVisibled(pstPanelParameter->EnableGrid);
		SetPixelNumber(pstPanelParameter->HorizontalPixelNumber, pstPanelParameter->VerticalPixelNumber);

		SetPixelColour(wxColor(pstPanelParameter->PixelColor.RGBA), false);
		SetPanelColour(wxColor(pstPanelParameter->PanelColor.RGBA), false);
		SetGridColor(wxColor(pstPanelParameter->GridColor.RGBA));
	}
	CleanScreen();
}
