#ifndef __BSP_BUTTON_H
#define __BSP_BUTTON_H

#include "bsp_hw.h"
#include "hal_hw.h"


typedef enum{
	BTN1_SHUT=0,	//k1
	BTN2_DOWN,		//k2
	BTN3_UP,		//k3
	BTN4_MODE,			//k4
	BTN5_MENU,			//k5
	BTN_MAX
}BSP_BUTTON_SF_ENUM;

typedef enum{
	BSP_BUTTON_NULL =	0,
	BSP_BUTTON_EXIT =	0x0001,
	BSP_BUTTON_DOWN =	0x0002,
	BSP_BUTTON_UP =		0x0004,
	BSP_BUTTON_SWITCH = 0x0008,
	BSP_BUTTON_MENU =	0x0010,
	BSP_BUTTON_SHUT =	0x0011
}BSP_BUTTON_ENUM;

typedef struct{
	BSP_BUTTON_SF_ENUM sfPin;
	uint16_t hwPin;
}BSP_BUTTON_HW_t;

typedef struct{
	HAL_BUTTON_ENUM hal_button;
	BSP_BUTTON_ENUM bsp_button;
}BSP_TO_HAL_t;


void bsp_button_init(void);
HAL_BUTTON_ENUM bsp_button_get(void);
//uint8_t bsp_button_send(p_HAL_BUTTON, hal_queue_handle_t);
//uint8_t bsp_button_recv(p_HAL_BUTTON, hal_queue_handle_t);

#endif

