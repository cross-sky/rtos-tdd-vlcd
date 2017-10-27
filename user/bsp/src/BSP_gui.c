#include "BSP_gui.h"
//#include "font8_B.h"

void BSP_gui_char(uint8_t x, uint8_t y, char c)
{
	uint8_t i, j;
	uint8_t t = (c - 0x20) & 0XFF;
	uint8_t char_pos;
	uint8_t* font = BSP_lcd_getFont();
	for (i = 0; i < 8; i++)
	{
		char_pos = *(font + t * 8 + i);
		for (j=0; j < 8; j++)
		{
			if ( char_pos & 0x01 )
				BSP_lcd_pixel_b(x + i, y + j, 1);
			else
				BSP_lcd_pixel_b(x + i, y + j, 0);
			char_pos >>= 1;
		}
	}
}

void BSP_gui_str(uint8_t x, uint8_t y, char* str)
{
	uint8_t i = 0;
	while(*str != '\0'){
		BSP_gui_char(x + i, y, *str++);
		i += 8;
	}
}



