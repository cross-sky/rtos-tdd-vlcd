#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "bsp_hw.h"

typedef enum
{
	LED1 = 0,
	LED_ANZ 
}LED_NAME_t;

typedef enum {
	LED_OFF = 1,     // LED EIN
	LED_ON = 0			// LED AUS
}LED_STATUS_t;

typedef struct  
{
	LED_NAME_t		LED_NAME;
	GPIO_TypeDef*	LED_PORT;
	const uint16_t	LED_PIN;
	const uint32_t	LED_CLK;
	LED_STATUS_t	LED_INIT;
}LED_t;

void BSP_init_led(void);
void BSP_led_on(LED_NAME_t led_name);
void BSP_led_off(LED_NAME_t led_name);
void BSP_led_toggle(LED_NAME_t led_name);

#endif
