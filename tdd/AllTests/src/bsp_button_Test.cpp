#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "bsp_button.h"
#include "bsp_button_spy.h"
#include "bsp_hw.h"
}




TEST_GROUP(BSP_BUTTON)
{
void setup()
{
	//hal_button_init();
}

void teardown()
{

}
};

TEST(BSP_BUTTON, shortKey)
{
	//0µ¼Í¨£¬ 1¶Ï¿ª
	bsp_button_spy_set_key(0xffff);
	LONGS_EQUAL(0, bsp_button_get());

	bsp_button_spy_set_key(~GPIO_Pin_1);
	LONGS_EQUAL(HAL_BUTTON_EXIT, bsp_button_get());
}
