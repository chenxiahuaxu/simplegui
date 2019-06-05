#include "SSD1306_SPI.h"
#include "GPIO.h"


#define     SSD1306_SPI_PIN_IDX_CLK         (0)
#define     SSD1306_SPI_PIN_IDX_DIO         (1)
#define     SSD1306_SPI_PIN_IDX_CS          (2)
#define     SSD1306_SPI_PIN_IDX_DC          (3)
#define     SSD1306_SPI_PIN_IDX_RST         (4)

#define     SSD1306_PIN_HIGH(IDX)           GPIO_SetPinHigh(arrstSSD1306_GPIO, IDX)
#define     SSD1306_PIN_LOW(IDX)            GPIO_SetPinLow(arrstSSD1306_GPIO, IDX)

#define     SSD1306_DATA_MODE_CMD()         SSD1306_PIN_LOW(SSD1306_SPI_PIN_IDX_DC)
#define     SSD1306_DATA_MODE_DAT()         SSD1306_PIN_HIGH(SSD1306_SPI_PIN_IDX_DC)

#define     SSD1306_CS_ENABLE()             SSD1306_PIN_LOW(SSD1306_SPI_PIN_IDX_CS)
#define     SSD1306_CS_DISABLE()            SSD1306_PIN_HIGH(SSD1306_SPI_PIN_IDX_CS)

#define     SSD1306_RST_LOW()				SSD1306_PIN_LOW(SSD1306_SPI_PIN_IDX_RST)
#define     SSD1306_RST_HIGH()				SSD1306_PIN_HIGH(SSD1306_SPI_PIN_IDX_RST)

static GPIO_OBJECT_STRUCT	arrstSSD1306_GPIO[] =
{
	{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_13, GPIO_Mode_Out_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_15, GPIO_Mode_Out_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_12, GPIO_Mode_Out_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_11, GPIO_Mode_Out_PP, GPIO_Speed_2MHz, GPIO_STATE_HIGH},
	{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_10, GPIO_Mode_Out_PP, GPIO_Speed_2MHz, GPIO_STATE_LOW},
};

static void SSD1306_SPI_WriteByte(uint8_t uiData);

/*****************************************************************************/
/** Function Name:	SSD1306_SPI_WriteByte.                                  **/
/** Purpose:		Simulate SPI communication timing to write a byte		**/
/**					to OLED controler.										**/
/** Resources:		Simulate SPI GPIO.										**/
/** Params:																	**/
/**	@uiData:		Byte will be write.										**/
/** Return:			None.													**/
/** Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_WriteByte(uint8_t uiData)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint16_t                i;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	for(i=0;i<8;i++)
	{
		if((uiData << i) & 0x80)
		{
			SSD1306_PIN_HIGH(SSD1306_SPI_PIN_IDX_DIO);
		}
		else
		{
			SSD1306_PIN_LOW(SSD1306_SPI_PIN_IDX_DIO);
		}
		SSD1306_PIN_LOW(SSD1306_SPI_PIN_IDX_CLK);
		SSD1306_PIN_HIGH(SSD1306_SPI_PIN_IDX_CLK);
	}
}

/*****************************************************************************/
/* Function Name:	SSD1306_WriteData.										**/
/* Purpose:			Write a data byte to OLED coltroler.					**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiData:			One byte data will be write.						**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_WriteData(uint8_t uiData)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_DATA_MODE_DAT();
	SSD1306_SPI_WriteByte(uiData);
}

/*****************************************************************************/
/* Function Name:	SSD1306_WriteCommand.									**/
/* Purpose:			Write a command byte to OLED coltroler.					**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiData:			One byte command will be write.						**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_WriteCommand(uint8_t uiCommand)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_DATA_MODE_CMD();
	SSD1306_SPI_WriteByte(uiCommand);
}

/*****************************************************************************/
/* Function Name:	OLED_SetPosition.										**/
/* Purpose:			Set current position of page and colomn.				**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiColumn:			Position of column.									**/
/*	@uiPage:			Position of page.									**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_SetPosition(uint8_t uiColumn, uint8_t uiPage)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	SSD1306_SPI_WriteCommand(0xB0 | uiPage);
	SSD1306_SPI_WriteCommand(((uiColumn & 0xF0)>>4)|0x10);
	SSD1306_SPI_WriteCommand((uiColumn & 0x0F));
}

/*****************************************************************************/
/* Function Name:	SSD1306_SPI_Fill.												**/
/* Purpose:			Fill screen.											**/
/* Resources:		None.													**/
/* Params:																	**/
/*	@uiColumn:			Position of column.									**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_Fill(uint8_t uiByte)//全屏填充
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint8_t uiPage, uiColumn;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	for(uiPage=0; uiPage<8; uiPage++)
	{
		SSD1306_SPI_WriteCommand(0xb0 | uiPage);
		SSD1306_SPI_WriteCommand(0x00);
		SSD1306_SPI_WriteCommand(0x10);
		for(uiColumn=0; uiColumn<128; uiColumn++)
		{
			SSD1306_SPI_WriteData(uiByte);
		}
	}
}

/*****************************************************************************/
/* Function Name:	SSD1306_SPI_Clear.												**/
/* Purpose:			Clear screen display.									**/
/* Resources:		None.													**/
/* Params:			None.													**/
/* Return:			None.													**/
/* Limitation:		None.													**/
/*****************************************************************************/
void SSD1306_SPI_Clear(void)//清屏
{
	SSD1306_SPI_Fill(0x00);
}

/*****************************************************************************/
/** Function Name:	SSD1306_Initialize										**/
/** Purpose:		Run the device initialize sequence.						**/
/** Resources:		None.													**/
/** Params:			None.													**/
/** Return:			None.													**/
/** Limitation:		Initialize sequence must executed after power on 500ms.	**/
/*****************************************************************************/
void SSD1306_SPI_Initialize(void)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Initialize GPIO
	GPIO_Initialize(arrstSSD1306_GPIO, 5);
	
	SSD1306_RST_HIGH();

	SSD1306_CS_ENABLE();

	SSD1306_SPI_WriteCommand(0xae);
	SSD1306_SPI_WriteCommand(0xae);//--turn off oled panel
	SSD1306_SPI_WriteCommand(0x00);//---set low column address
	SSD1306_SPI_WriteCommand(0x10);//---set high column address
	SSD1306_SPI_WriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	SSD1306_SPI_WriteCommand(0x81);//--set contrast control register
	SSD1306_SPI_WriteCommand(0xcf); // Set SEG Output Current Brightness
	SSD1306_SPI_WriteCommand(0xa1);//--Set SEG/Column Mapping     0xa0,0xa1
	SSD1306_SPI_WriteCommand(0xc8);//Set COM/Row Scan Direction   0xc0,0xc8
	SSD1306_SPI_WriteCommand(0xa6);//--set normal display
	SSD1306_SPI_WriteCommand(0xa8);//--set multiplex ratio(1 to 64)
	SSD1306_SPI_WriteCommand(0x3f);//--1/64 duty
	SSD1306_SPI_WriteCommand(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	SSD1306_SPI_WriteCommand(0x00);//-not offset
	SSD1306_SPI_WriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
	SSD1306_SPI_WriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	SSD1306_SPI_WriteCommand(0xd9);//--set pre-charge period
	SSD1306_SPI_WriteCommand(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	SSD1306_SPI_WriteCommand(0xda);//--set com pins hardware configuration
	SSD1306_SPI_WriteCommand(0x12);
	SSD1306_SPI_WriteCommand(0xdb);//--set vcomh
	SSD1306_SPI_WriteCommand(0x40);//Set VCOM Deselect Level
	SSD1306_SPI_WriteCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	SSD1306_SPI_WriteCommand(0x02);//
	SSD1306_SPI_WriteCommand(0x8d);//--set Charge Pump enable/disable
	SSD1306_SPI_WriteCommand(0x14);//--set(0x10) disable
	SSD1306_SPI_WriteCommand(0xa4);// Disable Entire Display On (0xa4/0xa5)
	SSD1306_SPI_WriteCommand(0xa6);// Disable Inverse Display On (0xa6/a7)
	SSD1306_SPI_WriteCommand(0xaf);//--turn on oled panel
	SSD1306_SPI_Fill(0x00);
	SSD1306_SPI_SetPosition(0,0);
}

void OLED_BMP(uint32_t uiPosX, uint32_t uiPosY, uint32_t uiWidth, uint32_t uiHeight, uint8_t *pData)
{
	uint16_t	uiColumnIndex, uiPageIndex;
	uint16_t	uiColumnCount, uiPageCount;
	uint32_t	uiDataIndex;

	uiColumnCount = (uint16_t)uiWidth;
	if(uiHeight%8==0)
	{
		uiPageCount=uiHeight/8;
	}
	else
	{
		uiPageCount=uiHeight/8+1;
	}
	uiDataIndex = 0;

	for(uiPageIndex=uiPosY; uiPageIndex<uiPageCount; uiPageIndex++)
	{
		SSD1306_SPI_SetPosition(uiPosX, uiPageIndex);
		for(uiColumnIndex=uiPosX; uiColumnIndex<uiColumnCount; uiColumnIndex++)
		{
			SSD1306_SPI_WriteData(*(pData+uiDataIndex));
			uiDataIndex++;
		}
	}
}
