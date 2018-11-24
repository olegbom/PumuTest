/*
 * lis3.h
 *
 *  Created on: 23 нояб. 2018 г.
 *      Author: Oleg
 */

#ifndef LIS3_H_
#define LIS3_H_

#include "main.h"


#define LIS3_ADDR_OUT_T    0x0C
#define LIS3_ADDR_INFO1    0x0D
#define LIS3_ADDR_INFO2    0x0E
#define LIS3_ADDR_WHO_AM_I    0x0F
#define LIS3_ADDR_OFF_X    0x10
#define LIS3_ADDR_OFF_Y    0x11
#define LIS3_ADDR_OFF_Z    0x12
#define LIS3_ADDR_CS_X    0x13
#define LIS3_ADDR_CS_Y    0x14
#define LIS3_ADDR_CS_Z    0x15
#define LIS3_ADDR_LC_L    0x16
#define LIS3_ADDR_LC_H    0x17
#define LIS3_ADDR_STAT    0x18
#define LIS3_ADDR_PEAK1    0x19
#define LIS3_ADDR_PEAK2    0x1A
#define LIS3_ADDR_VFC_1    0x1B
#define LIS3_ADDR_VFC_2    0x1C
#define LIS3_ADDR_VFC_3    0x1D
#define LIS3_ADDR_VFC_4    0x1E
#define LIS3_ADDR_THRS3    0x1F
#define LIS3_ADDR_CTRL_REG4    0x20
#define LIS3_ADDR_CTRL_REG1    0x21
#define LIS3_ADDR_CTRL_REG2    0x22
#define LIS3_ADDR_CTRL_REG3    0x23
#define LIS3_ADDR_CTRL_REG5    0x24
#define LIS3_ADDR_CTRL_REG6    0x25
#define LIS3_ADDR_STATUS    0x27
#define LIS3_ADDR_OUT_X_L    0x28
#define LIS3_ADDR_OUT_X_H    0x29
#define LIS3_ADDR_OUT_Y_L    0x2A
#define LIS3_ADDR_OUT_Y_H    0x2B
#define LIS3_ADDR_OUT_Z_L    0x2C
#define LIS3_ADDR_OUT_Z_H    0x2D
#define LIS3_ADDR_FIFO_CTRL    0x2E
#define LIS3_ADDR_FIFO_SRC    0x2F
#define LIS3_ADDR_ST1_1    0x40
#define LIS3_ADDR_ST1_2    0x41
#define LIS3_ADDR_ST1_3    0x42
#define LIS3_ADDR_ST1_4    0x43
#define LIS3_ADDR_ST1_5    0x44
#define LIS3_ADDR_ST1_6    0x45
#define LIS3_ADDR_ST1_7    0x46
#define LIS3_ADDR_ST1_8    0x47
#define LIS3_ADDR_ST1_9    0x48
#define LIS3_ADDR_ST1_10    0x49
#define LIS3_ADDR_ST1_11    0x4A
#define LIS3_ADDR_ST1_12    0x4B
#define LIS3_ADDR_ST1_13    0x4C
#define LIS3_ADDR_ST1_14    0x4D
#define LIS3_ADDR_ST1_15    0x4E
#define LIS3_ADDR_ST1_16    0x4F
#define LIS3_ADDR_TIM4_1    0x50
#define LIS3_ADDR_TIM3_1    0x51
#define LIS3_ADDR_TIM2_1_L    0x52
#define LIS3_ADDR_TIM2_1_H    0x53
#define LIS3_ADDR_TIM1_1_L    0x54
#define LIS3_ADDR_TIM1_1_H    0x55
#define LIS3_ADDR_THRS2_1    0x56
#define LIS3_ADDR_THRS1_1    0x57
#define LIS3_ADDR_MASK1_B    0x59
#define LIS3_ADDR_MASK1_A    0x5A
#define LIS3_ADDR_SETT1    0x5B
#define LIS3_ADDR_PR1    0x5C
#define LIS3_ADDR_TC1_L    0x5D
#define LIS3_ADDR_TC1_H    0x5E
#define LIS3_ADDR_OUTS1    0x5F
#define LIS3_ADDR_ST2_1    0x60
#define LIS3_ADDR_ST2_2    0x61
#define LIS3_ADDR_ST2_3    0x62
#define LIS3_ADDR_ST2_4    0x63
#define LIS3_ADDR_ST2_5    0x64
#define LIS3_ADDR_ST2_6    0x65
#define LIS3_ADDR_ST2_7    0x66
#define LIS3_ADDR_ST2_8    0x67
#define LIS3_ADDR_ST2_9    0x68
#define LIS3_ADDR_ST2_10    0x69
#define LIS3_ADDR_ST2_11    0x6A
#define LIS3_ADDR_ST2_12    0x6B
#define LIS3_ADDR_ST2_13    0x6C
#define LIS3_ADDR_ST2_14    0x6D
#define LIS3_ADDR_ST2_15    0x6E
#define LIS3_ADDR_ST2_16    0x6F
#define LIS3_ADDR_TIM4_2    0x70
#define LIS3_ADDR_TIM3_2    0x71
#define LIS3_ADDR_TIM2_2_L    0x72
#define LIS3_ADDR_TIM2_2_H    0x73
#define LIS3_ADDR_TIM1_2_L    0x74
#define LIS3_ADDR_TIM1_2_H    0x75
#define LIS3_ADDR_THRS2_2    0x76
#define LIS3_ADDR_THRS1_2    0x77
#define LIS3_ADDR_DES2    0x78
#define LIS3_ADDR_MASK2_B    0x79
#define LIS3_ADDR_MASK2_A    0x7A
#define LIS3_ADDR_SETT2    0x7B
#define LIS3_ADDR_PR2    0x7C
#define LIS3_ADDR_TC2_L    0x7D
#define LIS3_ADDR_TC2_H    0x7E
#define LIS3_ADDR_OUTS2    0x7F


typedef enum
{
    ORD_PowerDown = 0,
    ORD_3_125_Hz = 1,
    ORD_6_25_Hz = 2,
    ORD_12_5_Hz = 3,
    ORD_25_Hz = 4,
    ORD_50_Hz = 5,
    ORD_100_Hz = 6,
    ORD_400_Hz = 7,
    ORD_800_Hz = 8,
    ORD_1600_Hz = 9
}LIS3_CTRL_REG4_ORD_Enum;

/**
 * @brief Control register 4
 */
typedef struct
{
    LIS3_CTRL_REG4_ORD_Enum ORD: 4;  /*!< Output data rate and power mode selection  */
    unsigned int BDU: 1;  /*!< Block data update  */
    unsigned int Zen: 1;  /*!< Z-axis enable */
    unsigned int Yen: 1;  /*!< Z-axis enable */
    unsigned int Xen: 1;  /*!< Z-axis enable */
} LIS3_CTRL_REG4_TypeDef;



/**
 * @brief Control register 1
 */
typedef struct
{
    unsigned int HYSTx_1: 3;  /*!< Hysteresis unsigned value to be added or subtracted from threshold value in SM1  */
    unsigned int reserved_1: 1;
    unsigned int SM1_PIN: 1;  /*!< 0: SM1 interrupt routed to INT1; 1: SM1 interrupt routed to INT2  */
    unsigned int reserved_2: 2;
    unsigned int SM1_EN: 1;  /*!< 0: SM1 disabled; 1: SM1 enabled */
} LIS3_CTRL_REG1_TypeDef;

/**
 * @brief Control register 2
 */
typedef struct
{
    unsigned int HYSTx_2: 3;  /*!< Hysteresis unsigned value to be added or subtracted from threshold value in SM2  */
    unsigned int reserved_1: 1;
    unsigned int SM2_PIN: 1;  /*!< 0: SM2 interrupt routed to INT1; 1: SM2 interrupt routed to INT2  */
    unsigned int reserved_2: 2;
    unsigned int SM2_EN: 1;  /*!< 0: SM2 disabled; 1: SM2 enabled */
} LIS3_CTRL_REG2_TypeDef;

/**
 * @brief Control register 3
 */
typedef struct
{
    unsigned int DR_EN: 1; /*!< DRDY signal enable to INT1 */
    unsigned int IEA: 1; /*!< Interrupt signal polarity */
    unsigned int IEL: 1; /*!< Interrupt signal latching */
    unsigned int INT2_EN: 1; /*!< Interrupt 2 enable/disable */
    unsigned int INT1_EN: 1; /*!< Interrupt 2 enable/disable */
    unsigned int VFILT: 1; /*!< Vector filter enable/disable */
    unsigned int reserved_1: 1;
    unsigned int STRT: 1; /*!< Soft reset bit */
} LIS3_CTRL_REG3_TypeDef;


/**
 * @brief Control register 5
 */
typedef struct
{
    unsigned int BW: 2; /*!<  Anti-aliasing filter bandwidth
                 (0: 800 Hz; 1: 200 Hz; 2: 400 Hz; 3: 50 Hz)*/
    unsigned int FSCALE: 3; /*!< Full-scale selection
         (0: ±2 g; 1: ±4 g; 2: ±6 g; 3: ±8 g; 4: ±16 g)*/
    unsigned int ST: 2; /*!< Self-test enable
        0: Normal mode; 1: Positive sign self-test;
        2: Negative sign self-test;*/
    unsigned int SIM: 1; /*!< SPI serial interface mode selection
        0: 4-wire interface; 1: 3-wire interface */
} LIS3_CTRL_REG5_TypeDef;




/**
 * @brief Control register 6
 */
typedef struct
{
    unsigned int BOOT: 1; /*!< Force reboot, cleared as soon as the reboot
                            is finished. Active high. */
    unsigned int FIFO_EN: 1; /*!< FIFO enable */
    unsigned int WTM_EN: 1; /*!< Enable FIFO watermark level use */
    unsigned int ADD_INC: 1; /*!< Register address automatically incremented
                         during a multiple byte access with a
                         serial interface (I2C or SPI) */
    unsigned int P1_EMPTY: 1; /*!< Enable FIFO empty indication on Int1 */
    unsigned int P1_WTM: 1; /*!<  FIFO watermark interrupt on Int1 */
    unsigned int P1_OVERRUN: 1; /*!<  FIFO overrun interrupt on Int1 */
    unsigned int P2_BOOT: 1; /*!< BOOT interrupt on Int2 */
} LIS3_CTRL_REG6_TypeDef;

/**
 * @brief Status register
 */
typedef struct
{
    unsigned int ZYXOR: 1; /*!< X, Y, and Z-axis data overrun */
    unsigned int ZOR: 1; /*!< Z-axis data overrun */
    unsigned int YOR: 1; /*!< Y-axis data overrun */
    unsigned int XOR: 1; /*!< X-axis data overrun */
    unsigned int ZYXDA: 1; /*!< X, Y, and Z-axis new data available */
    unsigned int ZDA: 1; /*!<  Z-axis new data available */
    unsigned int YDA: 1; /*!<  Y-axis new data available */
    unsigned int XDA: 1; /*!< X-axis new data available */
} LIS3_CTRL_STATUS_TypeDef;


/**
 * @brief FIFO control register
 */
typedef struct
{
    unsigned int FMODE: 3; /*!< FIFO mode selection. See datasheet*/
    unsigned int WTMP: 5; /*!< FIFO watermark pointer. See datasheet */
} LIS3_CTRL_FIFO_CTRL_TypeDef;

void LIS3_WriteReg(uint8_t reg, uint8_t data);
uint8_t LIS3_ReadReg(uint8_t reg);
void LIS3_Init();
int16_t LIS3_ReadX();
int16_t LIS3_ReadY();
int16_t LIS3_ReadZ();


#endif /* LIS3_H_ */
