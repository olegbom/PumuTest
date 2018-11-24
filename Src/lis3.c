/*
 * lis3.c
 *
 *  Created on: 23 нояб. 2018 г.
 *      Author: Oleg
 */

#include "lis3.h"
#include "spi.h"
#include "gpio.h"

void LIS3_CTRL_REG5_Write(LIS3_CTRL_REG5_TypeDef *str)
{
    uint8_t data = (str->BW << 6)
         | (str->FSCALE << 3)
         | (str->ST << 2)
         | str->SIM;
    LIS3_WriteReg(LIS3_ADDR_CTRL_REG5, data);
}

void LIS3_CTRL_REG4_Write(LIS3_CTRL_REG4_TypeDef *str)
{
    uint8_t data =  (str->ORD << 4)
         | (str->BDU << 3)
         | (str->Zen << 2)
         | (str->Yen << 1)
         | (str->Xen << 0);
    LIS3_WriteReg(LIS3_ADDR_CTRL_REG4, data);
}


#define LIS3_CS_ENABLE()  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET)
#define LIS3_CS_DISABLE()  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_SET)

static uint8_t tx_buffer[2];

void LIS3_WriteReg(uint8_t reg, uint8_t data)
{
    tx_buffer[0] = reg & 0x7F;
    tx_buffer[1] = data;

    LIS3_CS_ENABLE();

    HAL_SPI_Transmit(&hspi1, tx_buffer, 2, 10);

    LIS3_CS_DISABLE();
}

uint8_t LIS3_ReadReg(uint8_t reg)
{
    uint8_t rx_buffer[2] = {0,0};
    tx_buffer[0] = reg | 0x80;
    tx_buffer[1] = 0;
    LIS3_CS_ENABLE();

    HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, 2, 10);

    LIS3_CS_DISABLE();
    return rx_buffer[1];
}


void LIS3_Init()
{
    LIS3_CTRL_REG4_TypeDef reg4;
    reg4.BDU = 0;
    reg4.ORD = ORD_100_Hz;
    reg4.Xen = 1;
    reg4.Yen = 1;
    reg4.Zen = 1;
    LIS3_CTRL_REG4_Write(&reg4);


    LIS3_CTRL_REG5_TypeDef reg5;
    reg5.BW = 0;
    reg5.FSCALE = 0;
    reg5.SIM = 0;
    reg5.ST = 0;
    LIS3_CTRL_REG5_Write(&reg5);
}

int16_t LIS3_ReadX()
{
    int8_t buf_l = LIS3_ReadReg(LIS3_ADDR_OUT_X_L);
    int8_t buf_h = LIS3_ReadReg(LIS3_ADDR_OUT_X_H);
    return (int16_t)((buf_h << 8) + buf_l);
}

int16_t LIS3_ReadY()
{
    int8_t buf_l = LIS3_ReadReg(LIS3_ADDR_OUT_Y_L);
    int8_t buf_h = LIS3_ReadReg(LIS3_ADDR_OUT_Y_H);
    return (int16_t)((buf_h << 8) + buf_l);
}

int16_t LIS3_ReadZ()
{
    int8_t buf_l = LIS3_ReadReg(LIS3_ADDR_OUT_Z_L);
    int8_t buf_h = LIS3_ReadReg(LIS3_ADDR_OUT_Z_H);
    return (int16_t)((buf_h << 8) + buf_l);
}
