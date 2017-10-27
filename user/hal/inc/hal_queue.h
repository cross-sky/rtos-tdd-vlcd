#ifndef __HAL_QUEUE_H
#define __HAL_QUEUE_H

#include <stdint.h>

typedef void * hal_queue_handle_t;

//typedef struct {
//	HAL_BUTTON_ENUM button;
//}HAL_BUTTON_QUEUE_T;

hal_queue_handle_t hal_queue_create(uint16_t length, uint16_t sizeOfElement);


#endif
