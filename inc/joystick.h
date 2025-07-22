/**
 ******************************************************************************
 * @file    joystick.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Header for joystick.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef JOYSTICK_H
#define JOYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Public typedefs/enums -----------------------------------------------------*/
typedef struct {int8_t x, y;} jstk_out_t;

/* Public functions' prototypes ----------------------------------------------*/
void jstk_init(void);
i2c_status_t jstk_read(__idata jstk_out_t *pdata);

#endif // JOYSTICK_H