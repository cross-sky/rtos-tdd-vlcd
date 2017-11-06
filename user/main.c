#include "includes.h"

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static void vTaskLED(void *pvParameters);
static void AppTaskCreate (void);
static void BSP_lcd_task(void *pvParameters);
static void vTaskButton(void* pvParameters);

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskLED = NULL;

static QueueHandle_t button_que_handler = NULL;

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{
	/* Ӳ����ʼ����ʼ�� */
	BSP_init(); 
	
	/* ��ʼ��һ����ʱ���жϣ����ȸ��ڵδ�ʱ���жϣ������ſ��Ի��׼ȷ��ϵͳ��Ϣ */
	//vSetupSysInfoTest();
	
	/* �������� */
	AppTaskCreate();
	
    /* �������ȣ���ʼִ������ */
    vTaskStartScheduler();

	/* ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п����ǿ�������heap�ռ䲻����ɴ���ʧ�� */
	while(1);
}

static void AppTaskCreate (void)
{
	xTaskCreate(vTaskLED, "task_led", 150, NULL, 1, &xHandleTaskLED);
	xTaskCreate(BSP_lcd_task, "task_lcd", 200, NULL, 1, NULL);
	xTaskCreate(vTaskButton, "task_button", 150, NULL, 2, NULL);
}

static void vTaskLED(void *pvParameters)
{
	while(1)
	{
		BSP_led_toggle(LED1);
		vTaskDelay( 2000 / portTICK_PERIOD_MS);
	}
}

static void vTaskButton(void* pvParameters)
{
	//queue
	uint16_t key=0;
	button_que_handler = xQueueCreate(10, sizeof(uint16_t));
	if (button_que_handler == NULL)
	{
		//
		
	}
	while(1)
	{
		key = hal_button_get();
		if (key != BSP_BUTTON_NULL)
			xQueueSend(button_que_handler, &key, 0);

		vTaskDelay( 100 / portTICK_PERIOD_MS);
	}
}

static void app_menu(uint16_t key)
{
	char str_key = key + '0';
	
	BSP_gui_char(50, 5, str_key);
}

static void BSP_lcd_task(void *pvParameters)
{
	//uint8_t i = 0;
	uint16_t key = 0;
	BSP_gui_str(10, 5, "key");
	BSP_lcd_refresh();
	while(1)
	{
		xQueueReceive(button_que_handler, &key, 0);
		if (key != BSP_BUTTON_NULL)
		{
			app_menu(key);
			BSP_lcd_refresh();
			key = 0;

		}
		//if ((i++) & 0x01)
		//{
		//	BSP_lcd_test();
		//	BSP_lcd_refresh();
		//}
		//else
		//	BSP_lcd_blank();

		vTaskDelay( 300 / portTICK_PERIOD_MS);
	}
}
