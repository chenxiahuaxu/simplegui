#ifndef __INCLUDE_LCD_COMMON_H__
#define __INCLUDE_LCD_COMMON_H__
#include <stdint.h>

#define LCD_COLOR_OBJ_PIX						    	(0xFF168363)
#define LCD_COLOR_OBJ_BKG						    	(0xFF00F0D7)
#define LCD_COLOR_OBJ_EDGE						    	(0xFF383834)
#define LCD_COLOR_OBJ_GRID						    	(0xFF383834)

#define PARAM_DEFAULT_COLUMNS						    (192)
#define PARAM_DEFAULT_PAGES					    		(8)
#define PARAM_DEFAULT_PIXEL					    		(3)
#define PARAM_DEFAULT_EDGE					    		(5)
#define PARAM_DEFAULT_GRID					    		(false)

#define _TRANS_TEXT(STR)								_(STR)

typedef union
{
	uint8_t					Channel[4];
	uint32_t				RGBA;
}LCDRGBAColor;

typedef struct
{
	size_t					HorizontalPixelNumber;
    size_t					VerticalPixelNumber;
    size_t					PixelSize;
    size_t					EdgeWidth;
    bool					EnableGrid;
	LCDRGBAColor			EdgeColor;
	LCDRGBAColor			PanelColor;
	LCDRGBAColor			PixelColor;
	LCDRGBAColor			GridColor;

}PixelPanelParameter;

#endif // __INCLUDE_LCD_COMMON_H__
