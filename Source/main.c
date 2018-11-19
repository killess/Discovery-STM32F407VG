
#include "stm32f4xx.h"
#include "system.h"
#include "gpio.h"
//#include "stm32f4_discovery.h"





int main(void)
{
	system_init();
	gpio_init();



  while (1)
  {

	  HAL_GPIO_TogglePin(LD3);
	  HAL_GPIO_TogglePin(LD4);
	  HAL_GPIO_TogglePin(LD5);
	  HAL_GPIO_TogglePin(LD6);
	  HAL_Delay(250);



  }
}
