#include "bsp_st7587.h"
#include "font8_B.h"
#include "BSP_gui.h"

#define SCREEN_WIDTH	(128)
#define SCREEN_HEIGHT	(64 / 8)

#define SCREEN_WIDTH_PIXEL	(128)
#define SCREEN_HEIGHT_PIXEL	(64)

const static uint8_t _line_table[SCREEN_HEIGHT]={
	3, 2, 1, 0, 7, 6, 5, 4
//	5, 4, 7, 6, 1, 0, 3, 2
};

static uint8_t _lcd_buff[SCREEN_HEIGHT][SCREEN_WIDTH];

uint8_t* BSP_lcd_getFont(void)
{
	return (uint8_t*)&font8_B;
}

static void bsp_lcd_init_pins(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	//lcd rst scl sd cs --- pa
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(LCD_GPIOA, &GPIO_InitStructure);

	//init lcd_a0 -- pb0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(LCD_GPIOB, &GPIO_InitStructure);
}

//x 0-127, y 0-63
void BSP_lcd_pixel_b(uint8_t x, uint8_t y, uint8_t color)
{
	uint8_t y_pos;
	//if (x > SCREEN_WIDTH_PIXEL || y > SCREEN_WIDTH_PIXEL)
	//	return ;
	x -= 1;
	y -= 1;

	y_pos = (y / 8) & 0x07 ;

	if (color)
		_lcd_buff[_line_table[y_pos]][x] |= 1 << (y % 8);
	else
		_lcd_buff[_line_table[y_pos]][x] &= 0xff ^ (1 << (y % 8));
}

//x 0-128, y 0-7
void BSP_lcd_pixel(uint8_t x, uint8_t y, uint8_t c) 
{
	if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT) return;

	//x = _line_table[x];
	//y = _line_table[y];
	//array_pos = x + ((y >> 3) << 7); //x + ((y / 8) * 128);
	_lcd_buff[y][x] = c;
}

void BSP_lcd_char(uint8_t x, uint8_t y, char c)
{
	uint8_t t, i;
	t = (c - 0x20) & 0XFF;
	for (i = 0; i < 8; i++)
	{
		BSP_lcd_pixel(x + i, y, font8_B[t][i]);
	}
}

void BSP_lcd_str(uint8_t x, uint8_t y, const char* str)
{
	while(*str != '\0')
	{
		if (x > SCREEN_WIDTH)
		{
			x = 0;
			y += 1;
		}
		BSP_lcd_char(x, y, *str++);
		x += 8;
	}
}

void bsp_lcd_command(uint8_t command) {
	uint8_t n;
	// A0 is low for command data.
	LCD_A0_L;

	// Select the chip
	LCD_CS_L;
	for (n = 0; n < 8; n++) {
		LCD_SCLK_L;
		if (command & 0x80) {
			LCD_SDA_H;
		} else {
			LCD_SDA_L;
		}

		// Pulse SCL
		__nop();
		LCD_SCLK_H;
		command <<= 1;
	}

	// Unselect the chip
	LCD_CS_H;
}

void bsp_lcd_data(unsigned char data) {
	uint8_t n;
	// A0 is high for display data
	LCD_A0_H;

	// Select the chip
	LCD_CS_L;

	for (n = 0; n < 8; n++) {
		LCD_SCLK_L;
		if (data & 0x01) {
			LCD_SDA_H;
		} else {
			LCD_SDA_L;
		}

		// Pulse SCL
		__nop();
		LCD_SCLK_H;
		data >>= 1;
	}

	//for (n = 0; n < 8; n++) {
	//	LCD_SCLK_L;
	//	if (data & 0x80) {
	//		LCD_SDA_H;
	//	} else {
	//		LCD_SDA_L;
	//	}

	//	// Pulse SCL
	//	LCD_SCLK_H;
	//	__nop();
	//	data <<= 1;
	//}
	// Unselect the chip
	LCD_CS_H;
}

void BSP_lcd_blank(void) {
	uint8_t y, x;
	uint8_t i, j;
	// Reset the internal buffer
	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_WIDTH; j ++)
		{
			_lcd_buff[i][j] = 0;
		}
	}

	// Clear the actual screen
	for (y = 0; y < 8; y++) {
		bsp_lcd_command(GLCD_CMD_SET_PAGE | y);

		// Reset column to 0 (the left side)
		bsp_lcd_command(GLCD_CMD_COLUMN_LOWER);
		bsp_lcd_command(GLCD_CMD_COLUMN_UPPER);

		// We iterate to 132 as the internal buffer is 65*132, not
		// 64*124.
		for (x = 0; x < 128; x++) {
			bsp_lcd_data(0x00);
		}
	}
}

void BSP_lcd_refresh(void) {
	uint16_t x, y;
	for (y = 0; y < 8; y++) {
		bsp_lcd_command(GLCD_CMD_SET_PAGE | y);

		bsp_lcd_command(GLCD_CMD_COLUMN_LOWER);
		bsp_lcd_command(GLCD_CMD_COLUMN_UPPER);

		for (x = 0; x < 128; x++) {
			bsp_lcd_data(_lcd_buff[y][x]); 
		}
	}
}

static void delay_ms(uint16_t ms)
{
	uint8_t i;
	uint16_t j;
	for (i = 0; i < 200; i++)
	{
		for (j = 0; j < ms; j++)
		{
			__nop();
		}
	}
}

static void delay_us(uint16_t us)
{
	uint16_t i;
	for (i = 0; i < us; i++)
	{
		__nop();
	}
}

void BSP_lcd_init(void) {
	bsp_lcd_init_pins();
	LCD_RESET_L;
	delay_ms(20);
	LCD_RESET_H;
	delay_ms(20);

	////-----------------------------
	bsp_lcd_command(0xae);// disp off
	delay_us(20);
	bsp_lcd_command(0xa2);// 1 / 9 bias
	delay_us(20);
	bsp_lcd_command(0xa0);// adc s0- s128
	bsp_lcd_command(0xc0);
	delay_us(20);
	//bsp_lcd_command(0xc8);// com1- com64
	bsp_lcd_command(0x25);// ---
	bsp_lcd_command(0x81);// sets v0
	bsp_lcd_command(0x05);  // 
	bsp_lcd_command(0x2f);// voltage follower ON regulator ON booster ON
	bsp_lcd_command(0xa6);// Normal Display (not reverse dispplay)
	bsp_lcd_command(0xa4);// Entire Display Disable
	bsp_lcd_command(0xa3);	   //起到了关键性作用         ********
	//bsp_lcd_command(0x60);// Set Display Start Line = com0  ************
	bsp_lcd_command(0x40);// Set Display Start Line = com0  ************
	bsp_lcd_command(0xb0);// Set Page Address = 0
	bsp_lcd_command(0x10);// Set Column Address 4 higher bits = 0
	bsp_lcd_command(0x01);// Set Column Address 4 lower bits = 1 , from IC SEG1 -> SEG128
	bsp_lcd_command(0xaf);
	BSP_lcd_blank();
	//GRA_drawStr(LcdOffStr, 0, 0);
}

void BSP_lcd_test(void)
{
	static uint8_t y = 0;
	
	BSP_gui_str(3, (y + 1) , "00abcde");
	BSP_gui_str(3, (y + 9) , "01fghij");
	BSP_gui_str(3, (y + 17) , "22klmno");
	BSP_gui_str(3, (y + 25) , "33pqrst");
	BSP_gui_str(3, (y + 33) , "44uvwxy");
	BSP_gui_str(3, (y + 41) , "55zABCD");
	BSP_gui_str(1, (y + 49) , "66EFGHILKLMNO");
	BSP_gui_str(1, (y + 57) , "7PQRSTUVWXYZ");

	y = (y + 1) & 0x07;
	//BSP_lcd_char(0, 0, 'a');

	/*BSP_gui_str(3, 4, "00abcde");
	BSP_gui_str(3, 9, "01fghij");
	BSP_gui_str(3, 17, "22klmno");
	BSP_gui_str(3, 25, "33pqrst");
	BSP_gui_str(3, 33, "44uvwxy");
	BSP_gui_str(3, 41, "55zABCD");
	BSP_gui_str(1, 53, "66EFGHI");*/
	//BSP_gui_str(1, 57, "77PQRST");
	//BSP_gui_str(1, 49, "66EFGHILKLMNO");
	//BSP_gui_str(1, 57, "77PQRSTUVWXYZ");

	//BSP_lcd_str(0, 0, "0abcde");
	//BSP_lcd_str(0, 1, "1fghij");
	//BSP_lcd_str(0, 2, "2klmno");
	//BSP_lcd_str(0, 3, "3pqrst");
	//BSP_lcd_str(0, 4, "4uvwxy");
	//BSP_lcd_str(0, 5, "5zABCD");
	//BSP_lcd_str(0, 6, "6EFGHILKLMNO");
	//BSP_lcd_str(0, 7, "7PQRSTUVWXYZ");
}

void BSP_lcd_print(void)
{
	uint8_t i, j, m;
	uint8_t data;
	for (i=0; i < 8; i++)
	{
		for (m = 0; m < 8; m++)
		{
			for (j = 0; j < 128; j++)
			{
				data = _lcd_buff[i][j];
				data = data << m;
				if (data & 0x80)
					printf("* ");
				else
					printf("  ");
			}
			printf("\r\n");
		}
		printf("\r\n");
	}
	
}


