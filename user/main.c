#include "includes.h"

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static void vTaskLED(void *pvParameters);
static void AppTaskCreate (void);
static void BSP_lcd_task(void *pvParameters);

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskLED = NULL;

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
	xTaskCreate(BSP_lcd_task, "task_lcd", 200, NULL, 2, NULL);
}

static void vTaskLED(void *pvParameters)
{
	while(1)
	{
		BSP_led_toggle(LED1);
		vTaskDelay( 2000 / portTICK_PERIOD_MS);
	}
}

static void BSP_lcd_task(void *pvParameters)
{
	uint8_t i = 0;
	while(1)
	{
		if ((i++) & 0x01)
		{
			BSP_lcd_test();
			BSP_lcd_refresh();
		}
		else
			BSP_lcd_blank();

		vTaskDelay( 2000 / portTICK_PERIOD_MS);
	}
}
