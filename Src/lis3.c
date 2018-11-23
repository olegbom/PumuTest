/*
 * lis3.c
 *
 *  Created on: 23 нояб. 2018 г.
 *      Author: Oleg
 */

#include "lis3.c"
#include "spi.h"
#include "main.h"
#include "gpio.h"




#define LIS3_CS_ENABLE()  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET)
#define LIS3_CS_DISABLE()  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET)

static uint8_t tx_buffer[2];

void LIS3_WriteReg(uint8_t reg, uint8_t data)
{
    tx_buffer[0] = reg | 0x80;
    tx_buffer[1] = data;

    LIS3_CS_ENABLE();

    HAL_SPI_Transmit(&hspi2, tx_buffer, 2, 10);

    LIS3_CS_DISABLE();
}

uint8_t LIS3_ReadReg(uint8_t reg)
{
    uint8_t rx_buffer[2] = {0,0};
    tx_buffer[0] = reg & 0x7F;
    tx_buffer[1] = 0;
    LIS3_CS_ENABLE();

    HAL_SPI_TransmitReceive(&hspi2, tx_buffer, rx_buffer, 2, 10);

    LIS3_CS_DISABLE();
    return rx_buffer[1];
}

