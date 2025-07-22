/**
 ******************************************************************************
 * @file    ads1015.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   This file contains the definitions to interface the ADS1015
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ADS1015_H
#define ADS1015_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Public defines ------------------------------------------------------------*/

// ADS1015 I2C address modified by ADDR pin
#define ADS1015_I2CADDR  (0x48 | ADS1015_ADDR_VAL)

// ADS1015 I2C General Call Reset (must be sent as device address)
#define ADS1015_GC_RESET (0x06)

// ADS1015's conversion register (16-bits)
#define CONVERSION_REG 0x00

// ADS1015's config register (16-bits)
#define CONFIG_REG 0x01

// ADS1015's config register high 8-bits
#define OS   (1 << 7)
#define MUX2 (1 << 6)
#define MUX1 (1 << 5)
#define MUX0 (1 << 4)
#define PGA2 (1 << 3)
#define PGA1 (1 << 2)
#define PGA0 (1 << 1)
#define MODE (1 << 0)

// ADS1015's config register low 8-bits
#define DR2       (1 << 7)
#define DR1       (1 << 6)
#define DR0       (1 << 5)
#define COMP_MODE (1 << 4)
#define COMP_POL  (1 << 3)
#define COMP_LAT  (1 << 2)
#define COMP_QUE1 (1 << 1)
#define COMP_QUE0 (1 << 0)

// ADS1015's Lo_Thresh register (16-bits)
#define LO_THRESH_REG 0x02

// ADS1015's Hi_Thresh register (16-bits)
#define HI_THRESH_REG 0x03

#endif // ADS1015_H