#ifndef __INCLUDE_CLS_LCD_SCREENPANEL_H__
#define __INCLUDE_CLS_LCD_SCREENPANEL_H__

#include <wx/colour.h>

#include "wxPixelPanel.h"
#include "Common.h"

class LCD_ScreenPanel : public wxPixelPanel
{
private:
	uint32_t			m_uiPageCount;
	uint32_t			m_uiColumnCount;
	uint32_t			m_uiPosColumn;
	uint32_t			m_uiPosPage;

	wxColor*			m_pclsPanelColor;
	wxColor*			m_pclsPixelColor;

	void				wxEvent_OnMouseClick(wxMouseEvent& event)		{OnMouseClick(event);}

protected:
	void				OnMouseClick(wxMouseEvent& event);

public:
						LCD_ScreenPanel(	wxWindow *parent,
											wxWindowID winid = wxID_ANY,
											const wxPoint& pos = wxDefaultPosition,
											const wxSize& size = wxDefaultSize,
											long style = wxTAB_TRAVERSAL | wxNO_BORDER,
											const wxString& name = wxPanelNameStr);
						~LCD_ScreenPanel(void);

	void				SetParameter(PixelPanelParameter* pstPanelParameter);
	void				SetColumn(uint32_t uiColumn);
	void				SetPage(uint32_t uiPage);
	void				SetPosition(uint32_t uiColumn, uint32_t uiPage);
	void				SetData(uint8_t uiData);
	uint8_t				GetData(void);
	void				CleanPanel(void);

						DECLARE_EVENT_TABLE();
};


#endif // __INCLUDE_CLS_LCD_SCREENPANEL_H__
