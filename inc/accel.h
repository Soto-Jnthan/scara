/**
 ******************************************************************************
 * @file    accel.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Header for accel.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ACCEL_H
#define ACCEL_H

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Public typedefs/enums ------------------------------------------------------*/
typedef struct {int16_t x, y, z;} xlda_out_t; 
/* KEIL's int16_t endianess not equal to lsm6ds33's default. Set CTRL3_C's BLE flag */
typedef struct {int8_t xl, g, c;} xlda_ctrl_t; // Add contiguous CTRL registers as needed

/* Public functions' prototypes -----------------------------------------------*/
i2c_status_t xlda_init(const xlda_ctrl_t *ctrl);
i2c_status_t xlda_read(xlda_out_t *p_data);

#endif // ACCEL_H