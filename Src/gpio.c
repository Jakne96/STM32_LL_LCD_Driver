/*
 * gpio.c
 *
 *  Created on: Apr 9, 2026
 *      Author: janec
 */


//#include "main.h"
#include "gpio.h"

//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif

void gpio_init(void)
{
	LL_SetSystemCoreClock(16000000);
	LL_Init1msTick(16000000);

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinOutputType(LCD_DC_GPIO_Port, LCD_DC_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_DC_GPIO_Port, LCD_DC_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(LCD_DC_GPIO_Port, LCD_DC_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(LCD_DC_GPIO_Port, LCD_DC_Pin, LL_GPIO_MODE_OUTPUT);

	LL_GPIO_SetPinOutputType(LCD_RST_GPIO_Port, LCD_RST_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_RST_GPIO_Port, LCD_RST_Pin, LL_GPIO_PULL_NO);
	LL_GPIO_SetPinSpeed(LCD_RST_GPIO_Port, LCD_RST_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinMode(LCD_RST_GPIO_Port, LCD_RST_Pin, LL_GPIO_MODE_OUTPUT);

}
