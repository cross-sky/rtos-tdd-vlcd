#include "hal_hw.h"
#include "bsp.h"

void hal_button_init(void)
{
	bsp_button_init();
}

HAL_BUTTON_ENUM hal_button_get(void)
{
	return bsp_button_get();
}


