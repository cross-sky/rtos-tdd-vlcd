
#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "bsp_st7587.h"
#include "BSP_gui.h"
}

TEST_GROUP(BSP_lcd)
{
void setup()
{

}

void teardown()
{

}
};

TEST(BSP_lcd, printBuff)
{
	BSP_lcd_test();
	//BSP_lcd_char(0, 0, 'a');
	//BSP_gui_char(8, 1, 'a');
	//BSP_gui_str(1, 8, "abcd");
	BSP_lcd_print();
}
