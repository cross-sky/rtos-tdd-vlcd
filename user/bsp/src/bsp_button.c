#include "bsp.h"

#define BTN_MASK 0x1f
#define BTN_RCC RCC_APB2Periph_GPIOB
#define BTN_PORT GPIOB
#define BTN_PIN  GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8

static uint16_t s_longKey = 0;
static uint16_t trg=0, cont=0, cnt_last=0, cnt_plus = 0;

const BSP_BUTTON_HW_t _tabBtn[BTN_MAX]={
	{BTN1_SHUT,	1},
	{BTN2_DOWN, 3},
	{BTN3_UP,	4},
	{BTN4_MODE,	5},
	{BTN5_MENU,	8},
};

void bsp_button_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = BTN_PIN;
	GPIO_Init(BTN_PORT, &GPIO_InitStructure);
}

static uint16_t inputConvert(uint16_t hwValue)
{
	uint8_t i;
	uint16_t sfValue=0;
	for (i = 0; i < BTN_MAX; i++)
	{
		sfValue |= ((hwValue >> _tabBtn[i].hwPin) & 0x01) << _tabBtn[i].sfPin;
	}
	return sfValue;
}

static uint16_t bsp_button_check(uint16_t hwValue)
{
	uint16_t tvalue;
	uint16_t sfValue= inputConvert(hwValue);
	
	/**
	unsigned char ReadData = PINB^0xff;   // 1
	Trg = ReadData & (ReadData ^ Cont);   // 2
	Cont = ReadData;                      // 3
	***/
	//0µ¼Í¨£¬ 1¶Ï¿ª
	cnt_last = cont;
	tvalue = sfValue ^ BTN_MASK;
	trg = tvalue & (tvalue ^ cont);
	cont = tvalue;

	if (cnt_plus > 20 )
	{
		//run 21 + 1 times
		//setLongKey((cnt_last & BTN_MASK) | 0x1000);
		cnt_plus = 0;
		//return long key
		return (cnt_last & BTN_MASK) | 0x1000;
	}
	//check long key 
	if (cnt_last == cont && cont!= 0)
		cnt_plus++;
	else
		cnt_plus = 0;

	//return short key
	return trg & BTN_MASK;
}

uint16_t bsp_button_getInput(void)
{
	return GPIO_ReadInputData(BTN_PORT) & BTN_PIN;
}

HAL_BUTTON_ENUM bsp_button_get(void)
{
	
	return (HAL_BUTTON_ENUM)bsp_button_check(bsp_button_getInput());
}

//uint8_t bsp_button_send(p_HAL_BUTTON pButton, hal_queue_handle_t queue)
//{
//	uint16_t key = bsp_button_getInput();
//	//send to queue
//}
//
//uint8_t bsp_button_recv(p_HAL_BUTTON pButton, hal_queue_handle_t queue)
//{
//
//}

