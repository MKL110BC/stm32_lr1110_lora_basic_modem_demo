#include "led.h"
#include "system_time.h"


void led_init()
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	LED1_GPIO_CLK_ENABLE();
	LED2_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
	GPIO_InitStruct.Pin = LED1_PIN;
	HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LED2_PIN;
	HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(LED1_GPIO_PORT,LED1_PIN,GPIO_PIN_RESET);	//Net Led Off	
	HAL_GPIO_WritePin(LED2_GPIO_PORT,LED2_PIN,GPIO_PIN_SET);	//Power Led On
	
}



void led_process()
{

}

