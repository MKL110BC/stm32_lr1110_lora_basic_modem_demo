#include "main.h"
#include "led.h"
#include "key.h"
#include "driver_flash.h"
#include "system_time.h"
#include "system_port.h"
#include "lbm_app.h"


static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	/* Enable HSE Oscillator and Activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType	  = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState			  = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState		  = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource 	  = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL		  = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PLLDIV		  = RCC_PLL_DIV3;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Set Voltage scale1 as MCU will run at 32MHz */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
	while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

}



int main(void)
{
	APP_INFO("\n\n");
	APP_INFO("--------------------------------------\n");
	APP_INFO("Last Modify Time: 2022/6/01 14:30 \n");
	APP_INFO("Current FirmWare Version: %s \n",FIRMWARE_VERSION);
	APP_INFO("--------------------------------------\n");
	
	HAL_Init();
	SystemClock_Config();
	led_init();
	key_init();
	
	lbm_init();
	APP_INFO("lbm_init ok\n");

	while (1)
	{		
		lbm_cycle_test();
		key_scan();
		led_process();
	}
}


#ifdef	USE_FULL_ASSERT

/**
  * @brief	Reports the name of the source file and the source line number
  * 		where the assert_param error has occurred.
  * @param	file: pointer to the source file name
  * @param	line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
