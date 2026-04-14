/*
 * gpio.h
 *
 *  Created on: Apr 9, 2026
 *      Author: janec
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_utils.h"

#define LCD_DC_Pin LL_GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RST_Pin LL_GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOA


void gpio_init(void);

#endif /* GPIO_H_ */
