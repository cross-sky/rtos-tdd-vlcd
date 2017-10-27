#include "includes.h"

/*
**********************************************************************************************************
											函数声明
**********************************************************************************************************
*/
static void vTaskLED(void *pvParameters);
static void AppTaskCreate (void);
static void BSP_lcd_task(void *pvParameters);

/*
**********************************************************************************************************
											变量声明
**********************************************************************************************************
*/
static TaskHandle_t xHandleTaskLED = NULL;

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: 标准c程序入口。
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
int main(void)
{
	/* 硬件初始化初始化 */
	BSP_init(); 
	
	/* 初始化一个定时器中断，精度高于滴答定时器中断，这样才可以获得准确的系统信息 */
	//vSetupSysInfoTest();
	
	/* 创建任务 */
	AppTaskCreate();
	
    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();

	/* 如果系统正常启动是不会运行到这里的，运行到这里极有可能是空闲任务heap空间不足造成创建失败 */
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
