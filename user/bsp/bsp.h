#ifndef __BSP_H
#define __BSP_H

#define STM32_VLCD

#define __STM32F1_BSP_VERSION "1.1"

#define BSP_Printf printf

#include "os_task.h"

//hal
#include "hal_hw.h"

//bsp
#include "bsp_led.h"
#include "bsp_st7587.h"
#include "bsp_button.h"
#include "BSP_gui.h"

void BSP_init(void);


#endif

