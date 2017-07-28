#include "bsp.h"



const LED_t LED[]={
	// Name    ,PORT , PIN       , CLOCK              , Init
	{LED1 ,GPIOB,GPIO_Pin_12,RCC_APB2Periph_GPIOB,LED_OFF},   // 
};

void BSP_init_led(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t led_name;

	for (led_name=0; led_name < LED_ANZ; led_name++)
	{
		RCC_APB2PeriphClockCmd(LED[led_name].LED_CLK , ENABLE); 

		GPIO_InitStructure.GPIO_Pin = LED[led_name].LED_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(LED[led_name].LED_PORT, &GPIO_InitStructure);

		// Default Wert einstellen
		if(LED[led_name].LED_INIT==LED_ON) {
			BSP_led_off((LED_NAME_t)led_name);
		}
		else {
			BSP_led_on((LED_NAME_t)led_name);
		}
	}
}

void BSP_led_on(LED_NAME_t led_name)
{
	LED[led_name].LED_PORT->BRR = LED[led_name].LED_PIN;
}

void BSP_led_off(LED_NAME_t led_name)
{
	LED[led_name].LED_PORT->BSRR = LED[led_name].LED_PIN;
} 

void BSP_led_toggle(LED_NAME_t led_name)
{
	LED[led_name].LED_PORT->ODR ^= LED[led_name].LED_PIN;
}




