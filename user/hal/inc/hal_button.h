#ifndef __HAL_BUTTON_H
#define __HAL_BUTTON_H

#include "hal_queue.h"

typedef enum{
	HAL_BUTTON_NULL  =	0,
	HAL_BUTTON_EXIT = 0x0001,
	HAL_BUTTON_DOWN =	0x0002,
	HAL_BUTTON_UP =		0x0004,
	HAL_BUTTON_SWITCH = 0x0008,
	HAL_BUTTON_MENU =	0x0010,
	HAL_BUTTON_SHUT =	0x1001
}HAL_BUTTON_ENUM;		

typedef struct{
	HAL_BUTTON_ENUM key;
}HAL_BUTTON_t, *p_HAL_BUTTON;

void hal_button_init(void);
HAL_BUTTON_ENUM hal_button_get(void);

//uint8_t hal_button_send(p_HAL_BUTTON);
//uint8_t hal_button_recv(p_HAL_BUTTON);

#endif

