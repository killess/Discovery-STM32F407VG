//------------------------------------------------------------------------------
// Description:
//   Remap system timer (Systick) to a different timer
//
//
//   Subrountines:
//     gpio_init
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "systick-remap.h"

//------------------------------------------------------------------------------
//  Public
//------------------------------------------------------------------------------
uint32_t uwIncrementState = 0;


//------------------------------------------------------------------------------
//  Private
//------------------------------------------------------------------------------
static TIM_HandleTypeDef  htim;




//------------------------------------------------------------------------------
// Function Name  : get_tick_tim
// Description    : Get the timer structure
// Input          : None
// Output         : None
// Return         : timer pointer
//------------------------------------------------------------------------------
TIM_HandleTypeDef* get_tick_tim(void)
{
	return &htim;
}


//------------------------------------------------------------------------------
// Function Name  : HAL_InitTick
// Description    : This function configures the TIM as a time base source
//                  1ms time base with a dedicated tick interrupt priority
// Input          : uint32_t TickPriority: Tick interrupt priorty
// Output         : None
// Return         : HAL_StatusTypeDef: HAL status
//------------------------------------------------------------------------------
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock = 0;
	uint32_t              uwPrescalerValue = 0;
	uint32_t              pFLatency;

	// Configure the TIM IRQ priority
	HAL_NVIC_SetPriority(TIM7_IRQn, TickPriority ,0);

	// Enable the TIM global Interrupt
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

	// Enable TIM clock
	__HAL_RCC_TIM7_CLK_ENABLE();

	// Get clock configuration
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	// Compute TIM clock
	uwTimclock = 2*HAL_RCC_GetPCLK1Freq();

	// Compute the prescaler value to have TIM counter clock equal to 1MHz
	uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);

	// Initialize TIM
	htim.Instance = TIM7;

	// Initialize TIMx peripheral as follow:
	// + Period = [(TIMCLK/1000) - 1]. to have a (1/1000) s time base.
	// + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
	// + ClockDivision = 0
	// + Counter direction = Up
	htim.Init.Period = (1000000 / 1000) - 1;
	htim.Init.Prescaler = uwPrescalerValue;
	htim.Init.ClockDivision = 0;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&htim) == HAL_OK)
	{
		// Start the TIM time Base generation in interrupt mode
		return HAL_TIM_Base_Start_IT(&htim);
	}

	// Return function status
	return HAL_ERROR;
}


//------------------------------------------------------------------------------
// Function Name  : HAL_SuspendTick
// Description    : Suspend Tick increment
//                  Disable the tick increment by disabling TIM update interrupt.
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void HAL_SuspendTick(void)
{
	// Disable TIM update Interrupt
	__HAL_TIM_DISABLE_IT(&htim, TIM_IT_UPDATE);
}


//------------------------------------------------------------------------------
// Function Name  : HAL_ResumeTick
// Description    : Resume Tick increment.
//                  Enable the tick increment by Enabling TIM update interrupt
// Input          : None
// Output         : None
// Return         : None
//------------------------------------------------------------------------------
void HAL_ResumeTick(void)
{
	// Enable TIM Update interrupt
	__HAL_TIM_ENABLE_IT(&htim, TIM_IT_UPDATE);
}


