/**
 ******************************************************************************
 * @file    accel.h
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Header for accel.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ACCEL_H
#define ACCEL_H

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Public defines ------------------------------------------------------------*/
#define ACCEL_REGS (Z_ACCEL_H + 1)

/* Public typedefs/enums ------------------------------------------------------*/
enum {X_ACCEL_L, X_ACCEL_H, Y_ACCEL_L, Y_ACCEL_H, Z_ACCEL_L, Z_ACCEL_H};

/* Public functions' prototypes -----------------------------------------------*/
i2c_status_t xlda_init(uint8_t ctrl1);
i2c_status_t xlda_read(int8_t pdata[static ACCEL_REGS]);

#endif // ACCEL_H