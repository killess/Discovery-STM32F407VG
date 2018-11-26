//------------------------------------------------------------------------------
// Program Name:    STM32F4 DISCOVERY
// Program Number:
// Program Date:    11/19/18
// Project:
// Board:           STM32F4DISCOVERY
// Author:          Greg Hughes
// IDE:             TrueStudio v9.1
// Microcontroller: STMicroelectronics
//                  STM32F407VG
//
// Description:     Starting project template
//
//
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
//  Include Files
//------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "system.h"
#include "gpio.h"
//#include "stm32f4_discovery.h"

#include "usb_device.h"



int main(void)
{
	system_init();
	gpio_init();

	MX_USB_DEVICE_Init();
	HAL_Delay(500);


  while (1)
  {

	  HAL_GPIO_TogglePin(LD3);
	  HAL_GPIO_TogglePin(LD4);
	  HAL_GPIO_TogglePin(LD5);
	  HAL_GPIO_TogglePin(LD6);
	  HAL_Delay(250);
	  CDC_Transmit_FS("hello\r\n",7);


  }
}
