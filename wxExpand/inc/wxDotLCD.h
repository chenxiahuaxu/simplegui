#ifndef _INCLUDE_CLASS_WXEX_PIXEL_PANEL_H__
#define _INCLUDE_CLASS_WXEX_PIXEL_PANEL_H__

#include <wx/panel.h>
#include <wx/dcbuffer.h>
#include <wx/colour.h>

///////////////////////////////////////////////////////////////////////////////
/// Class LCD_DisplayPanel
///////////////////////////////////////////////////////////////////////////////

class wxDotLCD : public wxPanel
{
private:	//Appearance parameters.
	// Colors
	wxColor*			m_pclsEdgeColor;
	wxColor*			m_pclsBaseColor;
	wxColor*			m_pclsGridColor;
	// Display area
	uint32_t			m_uiHorizontalPixelNumber;
	uint32_t			m_uiVerticalPixelNumber;
	// Appearance size
    uint32_t			m_uiPixelSize;
    uint32_t			m_uiEdgeWidth;
    bool				m_bGridVisible;
	// Private data declare.
private:	// Private data.
	uint32_t*			m_parrDisplayBuffer;
	void				(wxDotLCD::*m_pfDrawPoint)(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);

private:	// Private object;
	wxClientDC			m_clsCDC;
	wxPen				m_clsPen;
	wxBrush				m_clsBrush;

private:	// Event callback function.
	void				_wxEvent_OnPaint(wxPaintEvent &event)		{OnPaint();event.Skip();}


public:		// Constructor/Destructor
						wxDotLCD(wxWindow *pclsParent, wxWindowID iWinID = wxID_ANY, const wxPoint& clsPosition = wxDefaultPosition);
						~wxDotLCD();

public:		// Public interface
	void				SetDisplaySizes(uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber);
	void				GetDisplaySize(uint32_t* puiHorizontalPixelNumber, uint32_t* puiVerticalPixelNumber);
	void				SetDisplayColors(const wxColor& clsEdgeColor, const wxColor& clsBaseColor, const wxColor& clsGridColor);
	void				SetEdgeWidth(uint32_t uiEdgeWidth);
	uint32_t			GetEdgeWidth(void)							{return m_uiEdgeWidth;}
	void				SetPixelSize(uint32_t uiPixelSize);
	uint32_t			GetPixelSize(void)							{return m_uiPixelSize;}
	void				SetGridVisibled(bool bGridVisible);
	bool                GetGridVisibled(void)          {return m_bGridVisible;}
	void				SetDisplayAreaSize( uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber);
	void				SetEdgeColor(const wxColor& clsColor);
	void				SetBaseColor(const wxColor& clsColor);
	void				SetDrawColor(const wxColor& clsColor);
	void				SetGridColor(const wxColor& clsColor);
	void				OnPaint(void);
	void				SetPixelUnitColor(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor, bool bRefreshNow = false);
	void                DrawPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor);
	uint32_t			GetPixelUnitColor(uint32_t uiPosX, uint32_t uiPosY);
	void				RefreshDisplay(void);
	void				CleanPanel(void);
	bool				SaveScreenImageToFile(const wxString& strFilePath);
	bool				CopyScreenImageToClipBoard(void);
	void				ResizeParent(void);

private:	// Private process function.
	inline void			DrawPointSinglePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			DrawPointMultiplePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			DrawPointMultiplePixelWithGrid(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			ReleaseDC(wxMemoryDC& clsCDCObject)			{clsCDCObject.SetBrush(wxNullBrush); clsCDCObject.SetPen(wxNullPen);}
	inline void			PrepareDC(wxMemoryDC& clsCDCObject)			{clsCDCObject.SetBrush(m_clsBrush); clsCDCObject.SetPen(m_clsPen);}
	inline void			ReleaseDC(wxClientDC& clsCDCObject)			{clsCDCObject.SetBrush(wxNullBrush); clsCDCObject.SetPen(wxNullPen);}
	inline void			PrepareDC(wxClientDC& clsCDCObject)			{clsCDCObject.SetBrush(m_clsBrush); clsCDCObject.SetPen(m_clsPen);}
	inline void			SetDCColor(const wxColor& clsColour)		{m_clsPen.SetColour(clsColour);m_clsBrush.SetColour(clsColour);}

	DECLARE_EVENT_TABLE();
};

#endif // _INCLUDE_CLASS_WXEX_PIXEL_PANEL_H__
