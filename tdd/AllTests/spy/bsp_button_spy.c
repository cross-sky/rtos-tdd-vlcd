#include "bsp_button_spy.h"

static uint16_t mock_key;

void bsp_button_spy_set_key(uint16_t key)
{
	mock_key = key;
}

uint16_t bsp_button_getInput(void)
{
	return mock_key;
}

