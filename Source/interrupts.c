
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "systick-remap.h"
#include "cmsis_os.h"


extern PCD_HandleTypeDef hpcd_USB_OTG_FS;



// This function handles Non maskable interrupt.
void NMI_Handler(void)
{
}


// This function handles Hard fault interrupt.
void HardFault_Handler(void)
{
	while (1){}
}


// This function handles Memory management fault.
void MemManage_Handler(void)
{
	while (1){}
}


// This function handles Pre-fetch fault, memory access fault.
void BusFault_Handler(void)
{
	while (1){}
}


// This function handles Undefined instruction or illegal state.
void UsageFault_Handler(void)
{
	while (1){}
}


// This function handles System service call via SWI instruction.
void SVC_Handler(void)
{
}


// This function handles Debug monitor.
void DebugMon_Handler(void)
{
}


// This function handles Pendable request for system service.
void PendSV_Handler(void)
{
}


// This function handles System tick timer.
void SysTick_Handler(void)
{
	//HAL_IncTick();
	//HAL_SYSTICK_IRQHandler();
	//osSystickHandler();
}


// This function handles TIM7 global interrupt.
void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(get_tick_tim());
}


// This function handles USB On The Go FS global interrupt.
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}


