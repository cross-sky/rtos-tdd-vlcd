#include <stdio.h>
#include <stdarg.h>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "hal_button.h"
}

//create button queue
static hal_queue_handle_t queue;

TEST_GROUP(HAL_BUTTON)
{
void setup()
{
	//hal_button_init();
}

void teardown()
{

}
};

TEST(HAL_BUTTON, printBuff)
{

}
