#include "ssd1306_softspi.h"
#include "oled.h"

static struct
{
	struct
	{
		uint16_t		uiStartPageIndex;
		uint16_t		uiStartColumnIndex;
		uint16_t		uiEndPageIndex;
		uint16_t		uiEndColumnIndex;
	}stUpdateArea;
	uint16_t		auiDisplayCache[LCD_SIZE_WIDTH][LCD_SIZE_PAGES];
}s_stLCDBuffer;

static void OLED_UpdateChangedBufferAreaRecord(uint8_t uiPageIndex, uint8_t uiColumnIndex);
static void OLED_ClearDisplayBuffer(void);

/*************************************************************************/
/** Function Name:	OLED_UpdateChangedBufferAreaRecord                  **/
/** Purpose:        Check changed area recodr and update.				**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ uiPageIndex:		Operated page index.							**/
/**	@ uiColumnIndex:    Operated column index.							**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_UpdateChangedBufferAreaRecord(uint8_t uiPageIndex, uint8_t uiColumnIndex)
{
	// Check and set page and column index.
	if(uiPageIndex < s_stLCDBuffer.stUpdateArea.uiStartPageIndex)
	{
		s_stLCDBuffer.stUpdateArea.uiStartPageIndex = uiPageIndex;
	}
	if(uiPageIndex > s_stLCDBuffer.stUpdateArea.uiEndPageIndex)
	{
		s_stLCDBuffer.stUpdateArea.uiEndPageIndex = uiPageIndex;
	}
	if(uiColumnIndex < s_stLCDBuffer.stUpdateArea.uiStartColumnIndex)
	{
		s_stLCDBuffer.stUpdateArea.uiStartColumnIndex = uiColumnIndex;
	}
	if(uiColumnIndex > s_stLCDBuffer.stUpdateArea.uiEndColumnIndex)
	{
		s_stLCDBuffer.stUpdateArea.uiEndColumnIndex = uiColumnIndex;
	}
}

/*************************************************************************/
/** Function Name:	LCD_ClearDisplayBuffer								**/
/** Purpose:			Clean display buffer.							**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_ClearDisplayBuffer(void)
{
	uint16_t uiCurrentPageIndex, uiCurrentColumnIndex;

	for(uiCurrentPageIndex = 0; uiCurrentPageIndex < LCD_SIZE_PAGES; uiCurrentPageIndex++)
	{
		for(uiCurrentColumnIndex = 0; uiCurrentColumnIndex < LCD_SIZE_WIDTH; uiCurrentColumnIndex++)
		{
			s_stLCDBuffer.auiDisplayCache[uiCurrentColumnIndex][uiCurrentPageIndex] = 0x00;
		}
	}
	s_stLCDBuffer.stUpdateArea.uiStartPageIndex		= (LCD_SIZE_HEIGHT/8) - 1;
	s_stLCDBuffer.stUpdateArea.uiEndPageIndex		= 0;
	s_stLCDBuffer.stUpdateArea.uiStartColumnIndex	= LCD_SIZE_WIDTH - 1;
	s_stLCDBuffer.stUpdateArea.uiEndColumnIndex		= 0;
}

/*************************************************************************/
/** Function Name:	OLED_SetPixel										**/
/** Purpose:		Set a pixel color or draw a point.              	**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ iPosX:		X location of point by pixels.						**/
/**	@ iPosY:		Y location of point by pixels.						**/
/**	@ iColor:		Point color, 0 is white, Nonzero is Black.			**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_SetPixel(int iPosX, int iPosY, int iColor)
{
	// Operating position check.
	if((iPosX < LCD_SIZE_WIDTH) && (iPosY < LCD_SIZE_HEIGHT))
	{
		// Check and set page and column index.
		OLED_UpdateChangedBufferAreaRecord(iPosY/8, iPosX);
		// Set point data.
		if(OLED_COLOR_FRG == iColor)
		{
			SET_PAGE_BIT(s_stLCDBuffer.auiDisplayCache[iPosX][iPosY/8], iPosY%8);
		}
		else
		{
			CLR_PAGE_BIT(s_stLCDBuffer.auiDisplayCache[iPosX][iPosY/8], iPosY%8);
		}
	}
}

/*************************************************************************/
/** Function Name:	OLED_GetPixel										**/
/** Purpose:		Get a pixel from buffer.							**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ iPosX:			X location of point by pixels.					**/
/**	@ iPosY:			Y location of point by pixels.					**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
int OLED_GetPixel(int iPosX, int iPosY)
{
	// Operating position check.
	if((iPosX < LCD_SIZE_WIDTH) && (iPosY < LCD_SIZE_HEIGHT))
	{
		return GET_PAGE_BIT(s_stLCDBuffer.auiDisplayCache[iPosX][iPosY/8], iPosY%8);
	}
	else
	{
		return 0;
	}
}

/*************************************************************************/
/** Function Name:	OLED_Initialize										**/
/** Purpose:			Simple delay function for KS0108 controler.     **/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_Initialize(void)
{
	SSD1306_Initialize();
	OLED_ClearDisplayBuffer();
}

/*************************************************************************/
/** Function Name:	LCD_RefreshScreen									**/
/** Purpose:			Update Screen with cache data.					**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_RefreshScreen(void)
{
	uint8_t uiChangedPageIndex, uiChangedColumnIndex;

	if(s_stLCDBuffer.stUpdateArea.uiEndColumnIndex > LCD_SIZE_WIDTH-1)
	{
		s_stLCDBuffer.stUpdateArea.uiEndColumnIndex = LCD_SIZE_WIDTH-1;
	}
	if(s_stLCDBuffer.stUpdateArea.uiEndPageIndex > (LCD_SIZE_HEIGHT/8)-1)
	{
		s_stLCDBuffer.stUpdateArea.uiEndPageIndex = (LCD_SIZE_HEIGHT/8)-1;
	}
	uiChangedPageIndex = s_stLCDBuffer.stUpdateArea.uiStartPageIndex;
	// Loop for each changed page.
	while(uiChangedPageIndex <= s_stLCDBuffer.stUpdateArea.uiEndPageIndex)
	{
		uiChangedColumnIndex = s_stLCDBuffer.stUpdateArea.uiStartColumnIndex;
		SSD1306_SetPosition(s_stLCDBuffer.stUpdateArea.uiStartColumnIndex, uiChangedPageIndex);
		// Loop for each changed column data in current page.
		while(uiChangedColumnIndex <= s_stLCDBuffer.stUpdateArea.uiEndColumnIndex)
		{
			// Write data to screen controler.
			SSD1306_WriteData(s_stLCDBuffer.auiDisplayCache[uiChangedColumnIndex][uiChangedPageIndex]);
			uiChangedColumnIndex++;
		}
		uiChangedPageIndex++;
	}

	// Reset global variable.
	s_stLCDBuffer.stUpdateArea.uiStartPageIndex		= (LCD_SIZE_HEIGHT/8) - 1;
	s_stLCDBuffer.stUpdateArea.uiEndPageIndex		= 0;
	s_stLCDBuffer.stUpdateArea.uiStartColumnIndex	= LCD_SIZE_WIDTH - 1;
	s_stLCDBuffer.stUpdateArea.uiEndColumnIndex		= 0;
}

/*************************************************************************/
/** Function Name:	OLED_ClearDisplay			    					**/
/** Purpose:		Clean display buffer.					    		**/
/** Resources:		None.												**/
/** Params:			None.												**/
/** Return:			None.												**/
/** Limitation:		None.												**/
/*************************************************************************/
void OLED_ClearDisplay(void)
{
	OLED_ClearDisplayBuffer();
	SSD1306_Fill(0x00);
}

