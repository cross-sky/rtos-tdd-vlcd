
#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "bsp_st7587.h"
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
	BSP_lcd_print();
}
