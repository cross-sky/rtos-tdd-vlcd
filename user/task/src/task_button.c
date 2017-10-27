#include "bsp.h"

#define DELAY_BUTTON	(100 / portTICK_PERIOD_MS)
#define MSG_BUTTON_LEN	10
//queue
static hal_queue_handle_t button_queue = NULL;

//typedef struct {
//	HAL_BUTTON_ENUM button;
//}MSG_BUTTON_t;

void task_button_init(void)
{
	hal_button_init();
	button_queue = xQueueCreate(MSG_BUTTON_LEN, sizeof(HAL_BUTTON_ENUM));
}
void task_button_run(void* pvParameter)
{
	//(void*)pvParameter;
	uint16_t key;
	//portBASE_TYPE xReturn = errQUEUE_FULL;
	while(1)
	{
		key = hal_button_get();
		if (key != HAL_BUTTON_NULL)
		{
			xQueueSend(button_queue, &key, DELAY_BUTTON);
		}
		vTaskDelay(DELAY_BUTTON);
	}
}

