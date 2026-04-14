/*
 * spi.c
 *
 *  Created on: Apr 9, 2026
 *      Author: janec
 */

#include "spi.h"


void spi_gpio_init(void)
{
    /* Enable clock for GPIOA */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    /* PA5 -> SCK */

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_5, LL_GPIO_AF_5);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_DOWN);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_LOW);

    /* PA6 -> MISO */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_6, LL_GPIO_AF_5);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_LOW);
    /* PA7 -> MOSI */

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_7, LL_GPIO_AF_5);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_7, LL_GPIO_PULL_DOWN);
    /* PA9 -> manual CS (GPIO output) */
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
}

void spi1_config(void)
{
	LL_SPI_Disable(SPI1);
    /* Enable clock for SPI1 */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

    /* Set baud rate = fPCLK / 4 */
    LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV32);

    /* CPOL = 0, CPHA = 0 */
    LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);
    LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);

    /* Full duplex */
    LL_SPI_SetTransferDirection(SPI1, LL_SPI_HALF_DUPLEX_TX);

    /* MSB first */
    LL_SPI_SetTransferBitOrder(SPI1, LL_SPI_MSB_FIRST);

    /* Master mode */
    LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

    /* 8-bit data */
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);

    LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
    /* Software NSS (SSM=1, SSI=1) */
    LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
    SET_BIT(SPI1->CR1, SPI_CR1_SSI);

    /* Enable SPI */
    LL_SPI_Enable(SPI1);
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
    uint32_t i = 0;
    volatile uint8_t temp;

    while (i < size)
    {
        /* Wait TXE */
        while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {}

        /* Send data */
        LL_SPI_TransmitData8(SPI1, data[i]);
        i++;
    }

    /* Wait TXE */
    while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {}
    /* Wait BSY = 0 */
    while (LL_SPI_IsActiveFlag_BSY(SPI1)) {}


    /* Clear OVR */
    LL_SPI_ClearFlag_OVR(SPI1);
    temp = SPI1->SR;
}

void spi1_receive(uint8_t *data, uint32_t size)
{
    while (size)
    {
        /* Send dummy */
        while (!LL_SPI_IsActiveFlag_TXE(SPI1)) {}
        LL_SPI_TransmitData8(SPI1, 0x00);

        /* Wait RXNE */
        while (!LL_SPI_IsActiveFlag_RXNE(SPI1)) {}

        /* Read data */
        *data++ = LL_SPI_ReceiveData8(SPI1);

        size--;
    }
}

void cs_enable(void)
{
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_9);
}

void cs_disable(void)
{
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_9);
}
