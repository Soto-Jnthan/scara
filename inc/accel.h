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

/* Public typedefs/enums ------------------------------------------------------*/
typedef struct {int16_t x; int16_t y; int16_t z;} xlda_out_t; // SDCC's endianness same as lsm6ds33

/* Public functions' prototypes -----------------------------------------------*/
i2c_status_t xlda_init(uint8_t ctrl1);
i2c_status_t xlda_read(xlda_out_t *pdata);

#endif // ACCEL_H