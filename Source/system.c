//------------------------------------------------------------------------------
// Description:
//    Reset and Clock Control (RCC)
//    Direct Memory Access (DMA)
//    Nested vectored interrupt controller (NVIC)
//    Independent Watchdog (IWDG)
//    Window Watchdog (WWDG)
//    System Timer (Systick)
//
//   Subroutines:
//     system_init
//     SystemClock_Config
//     _Error_Handler
//     assert_failed
//
//   Functions:
//     None
//
//   Interrupts:
//     None
//
//
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
//  Includes Files
//------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "system.h"








//------------------------------------------------------------------------------
// Function Name  : system_init
// Description    : Initialize
//                  Configures system peripherals
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void system_init(void)
{

	HAL_Init();



	SystemClock_Config();

}


//------------------------------------------------------------------------------
// Function Name  : SystemClock_Config
// Description    : Initialize Clocks
//                  Configures the different system clocks.
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void SystemClock_Config(void)
{
	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

	    // Configure the main internal regulator output voltage
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	  // Initializes the CPU, AHB and APB busses clocks
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 8;
	  RCC_OscInitStruct.PLL.PLLN = 336;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  // Initializes the CPU, AHB and APB busses clocks
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
	  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
	  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  // Configure Systick
	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


//------------------------------------------------------------------------------
// Function Name  : HAL_TIM_PeriodElapsedCallback
// Description    : Timer callback
//                  Configures for systick
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }

}


//------------------------------------------------------------------------------
// Task Name      : Error_Handler
// Description    : report the HAL error return state
// Input          : char *file,  Source file pointer
//                  int line,    Line number
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void _Error_Handler(char *file, int line)
{

	while(1)
	{
	}

}


//------------------------------------------------------------------------------
// Function Name  : assert_failed
// Description    : Initialize Clocks
//                  Reports the name of the source file and the source line number
//                  where the assert_param error has occurred.
// Input          : char *file,  Source file pointer
//                  int line,    Line number
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
#ifdef  USE_FULL_ASSERT
// @brief  Reports the name of the source file and the source line number
//         where the assert_param error has occurred.
// @param  file: pointer to the source file name
// @param  line: assert_param error line source number
// @retval None
void assert_failed(uint8_t* file, uint32_t line)
{
	// User can add his own implementation to report the file name and line number,
	//   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
}
#endif /* USE_FULL_ASSERT */
