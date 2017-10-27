#include "bsp.h"

void BSP_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	BSP_init_led();

	BSP_lcd_init();
}

