#ifndef _INCLUDE_CLASS_PANELLCD_H__
#define _INCLUDE_CLASS_PANELLCD_H__

#include <wx/panel.h>
#include <wx/dcbuffer.h>
#include <wx/colour.h>

///////////////////////////////////////////////////////////////////////////////
/// Class LCD_DisplayPanel
///////////////////////////////////////////////////////////////////////////////

class wxPixelPanel : public wxPanel
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
	wxWindow*			m_pclsParent;
	void				(wxPixelPanel::*m_pfDrawPoint)(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);

private:	// Private object;
	wxClientDC			m_CDC;
	wxPen				m_CPen;
	wxBrush				m_CBrush;

private:	// Event callback function.
	void				wxEvent_OnPaint(wxPaintEvent &event)		{OnPaint();event.Skip();}


public:		// Constructor/Destructor
						wxPixelPanel(wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition,  const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER,const wxString& name = wxPanelNameStr);
						~wxPixelPanel();

public:		// Public interface
	void				SetDisplaySizes(uint32_t uiEdgeWidth, uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber, uint32_t uiPixelSize, bool bGridVisible);
	void				GetDisplaySize(uint32_t* puiEdgeWidth, uint32_t* puiHorizontalPixelNumber, uint32_t* puiVerticalPixelNumber, uint32_t* puiPixelSize, bool* pbGridVisible);
	void				SetDisplayColors(const wxColor& clsEdgeColor, const wxColor& clsBaseColor, const wxColor& clsGridColor);
	void				SetEdgeWidth(uint32_t uiEdgeWidth);
	uint32_t			GetEdgeWidth(void)							{return m_uiEdgeWidth;}
	void				SetPixelSize(uint32_t uiPixelSize);
	uint32_t			GetPixelSize(void)							{return m_uiPixelSize;}
	void				SetGridVisibled(bool bGridVisible);
	void				SetDisplayAreaSize( uint32_t uiHorizontalPixelNumber, uint32_t uiVerticalPixelNumber);
	void				SetEdgeColor(const wxColor& clsColor);
	void				SetBaseColor(const wxColor& clsColor);
	void				SetDrawColor(const wxColor& clsColor);
	void				SetGridColor(const wxColor& clsColor);
	wxWindow*			GetParentWindow(void);
	void				OnPaint(void);
	void				SetPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor, bool bRefreshNow = false);
	void                DrawPixel(uint32_t uiPosX, uint32_t uiPosY, wxColor& clsColor);
	uint32_t			GetPixel(uint32_t uiPosX, uint32_t uiPosY);
	void				RefreshDisplay(void);
	void				CleanPanel(void);
	bool				SaveToFile(const wxString& CStrFilePath);
	bool				CopyToClipBoard(void);
	void				ResizeParent(void);

private:	// Private process function.

	inline void			DrawPointSinglePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			DrawPointMultiplePixel(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			DrawPointMultiplePixelWithGrid(wxMemoryDC& clsCDCObject, uint32_t uiPosX, uint32_t uiPosY, uint32_t uiPixelSize);
	inline void			ReleaseDC(wxMemoryDC& clsCDCObject)			{clsCDCObject.SetBrush(wxNullBrush); clsCDCObject.SetPen(wxNullPen);}
	inline void			PrepareDC(wxMemoryDC& clsCDCObject)			{clsCDCObject.SetBrush(m_CBrush); clsCDCObject.SetPen(m_CPen);}
	inline void			ReleaseDC(wxClientDC& clsCDCObject)			{clsCDCObject.SetBrush(wxNullBrush); clsCDCObject.SetPen(wxNullPen);}
	inline void			PrepareDC(wxClientDC& clsCDCObject)			{clsCDCObject.SetBrush(m_CBrush); clsCDCObject.SetPen(m_CPen);}
	inline void			SetDCColor(const wxColor& clsColour)		{m_CPen.SetColour(clsColour);m_CBrush.SetColour(clsColour);}

	DECLARE_EVENT_TABLE();
};

#endif // _INCLUDE_CLASS_PANELLCD_H__
