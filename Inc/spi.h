/*
 * spi.h
 *
 *  Created on: Apr 9, 2026
 *      Author: janec
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_spi.h"

void spi_gpio_init(void);
void spi1_config(void);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive(uint8_t *data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
