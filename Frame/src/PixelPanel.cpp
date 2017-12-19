#include "PixelPanel.h"

BEGIN_EVENT_TABLE(LCD_ScreenPanel,wxPixelPanel)
	EVT_MOUSE_EVENTS	(LCD_ScreenPanel::wxEvent_OnMouseClick)
END_EVENT_TABLE()
LCD_ScreenPanel::LCD_ScreenPanel(wxWindow *parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name):
wxPixelPanel(parent, winid, pos, size, style, name)
{
	m_pclsPanelColor = new wxColor(0x00, 0x00, 0x00, 0x00);
	m_pclsPixelColor = new wxColor(0x00, 0x00, 0x00, 0x00);
}

LCD_ScreenPanel::~LCD_ScreenPanel(void)
{
	delete m_pclsPanelColor;
	delete m_pclsPixelColor;
}

void LCD_ScreenPanel::CleanPanel(void)
{
	uint32_t uiHorizontalPixelNumber, uiVerticalPixelNumber;

	GetDisplaySize(NULL, &uiHorizontalPixelNumber, &uiVerticalPixelNumber, NULL, NULL);
	for(uint32_t i_V=0; i_V<uiVerticalPixelNumber; i_V++)
	{
		for(uint32_t i_H=0; i_H<uiHorizontalPixelNumber; i_H++)
		{
			SetPixel(i_H, i_V, *m_pclsPanelColor);
		}
	}
}

void LCD_ScreenPanel::SetParameter(PixelPanelParameter* pstPanelParameter)
{
	if(NULL != pstPanelParameter)
	{
		wxPixelPanel::SetDisplaySizes(	pstPanelParameter->EdgeWidth,
										pstPanelParameter->HorizontalPixelNumber,
										pstPanelParameter->VerticalPixelNumber,
										pstPanelParameter->PixelSize,
										pstPanelParameter->EnableGrid);
		m_uiColumnCount = pstPanelParameter->HorizontalPixelNumber;
		m_uiPageCount = pstPanelParameter->VerticalPixelNumber/8;

		m_pclsPanelColor->SetRGBA(pstPanelParameter->PanelColor.RGBA);
		m_pclsPixelColor->SetRGBA(pstPanelParameter->PixelColor.RGBA);
		wxPixelPanel::SetDisplayColors(	wxColor(pstPanelParameter->EdgeColor.RGBA),
										wxColor(pstPanelParameter->PanelColor.RGBA),
										wxColor(pstPanelParameter->GridColor.RGBA));
	}
	CleanPanel();
}


void LCD_ScreenPanel::SetPosition(uint32_t uiColumn, uint32_t uiPage)
{
	SetColumn(uiColumn);
	SetPage(uiPage);
}

void LCD_ScreenPanel::SetData(uint8_t uiData)
{
    for(uint32_t i=0; i<8; i++)
	{
		wxPixelPanel::SetPixel(m_uiPosColumn, m_uiPosPage*8+i, (0<(uiData & 0x01)?(*m_pclsPixelColor):(*m_pclsPanelColor)));
		uiData = uiData >> 1;
	}
	m_uiPosColumn++;
	m_uiPosColumn = m_uiPosColumn%m_uiColumnCount;
}

uint8_t LCD_ScreenPanel::GetData(void)
{
	uint8_t			uiReadByte = 0x00;

    for(uint32_t i=0; i<8; i++)
	{
		uiReadByte = uiReadByte >> 1;
		if(m_pclsPixelColor->GetRGBA() == wxPixelPanel::GetPixel(m_uiPosColumn, m_uiPosPage*8+i))
		{
			uiReadByte = uiReadByte | 0x80;
		}
	}
	m_uiPosColumn++;
	m_uiPosColumn = m_uiPosColumn%m_uiColumnCount;
	return uiReadByte;
}

void LCD_ScreenPanel::SetColumn(uint32_t uiColumn)
{
	m_uiPosColumn = uiColumn;
	m_uiPosColumn = m_uiPosColumn%m_uiColumnCount;
}

void LCD_ScreenPanel::SetPage(uint32_t uiPage)
{
	m_uiPosPage = uiPage;
	m_uiPosPage = m_uiPosPage%m_uiPageCount;
}


void LCD_ScreenPanel::OnMouseClick(wxMouseEvent& event)
{
	uint32_t    uiEdgeWidth, uiHorizontalPixelNumber, uiVerticalPixelNumber, uiPixelSize;
	bool		bGridVisible;
	long		uiPixelPosX, uiPixelPosY;
	wxPoint		clsMousePositoin = event.GetPosition();
	if(true == event.LeftDown())
	{
		GetDisplaySize(&uiEdgeWidth, &uiHorizontalPixelNumber, &uiVerticalPixelNumber, &uiPixelSize,&bGridVisible);

		uiPixelPosX = (clsMousePositoin.x - uiEdgeWidth)/GetPixelSize();
		uiPixelPosY = (clsMousePositoin.y - uiEdgeWidth)/GetPixelSize();


		if(	(uiPixelPosX >= 0) && (uiPixelPosY >= 0) &&
			(uiPixelPosX < (long)uiHorizontalPixelNumber) && (uiPixelPosY < (long)uiVerticalPixelNumber))
		{
			if(m_pclsPanelColor->GetRGBA() == GetPixel(uiPixelPosX, uiPixelPosY))
			{
				DrawPixel(uiPixelPosX, uiPixelPosY, *m_pclsPixelColor);
			}
			else
			{
				DrawPixel(uiPixelPosX, uiPixelPosY, *m_pclsPanelColor);
			}
		}
	}
}
