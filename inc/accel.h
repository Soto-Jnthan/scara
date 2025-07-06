/**
 ******************************************************************************
 * @file    accel.h
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   Header for accel.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ACCEL_H
#define ACCEL_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"
#include "lsm6ds33.h"
#include "i2c.h"

/* Public typedefs/enums ------------------------------------------------------*/
typedef enum {
    X_ACC = OUTX_H_XL,
    Y_ACC = OUTY_H_XL,
    Z_ACC = OUTZ_H_XL
} xlda_input_t; 

/* Public functions' prototypes -----------------------------------------------*/
i2c_status_t xlda_init(void);
int8_t xlda_read(xlda_input_t in);

#endif // ACCEL_H