/**
 ******************************************************************************
 * @file    joystick.h
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Header for joystick.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef JOYSTICK_H
#define JOYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"
#include "i2c.h"

/* Public defines ------------------------------------------------------------*/
#define ADC_REGS (Y_AXIS + 1)

/* Public typedefs/enums -----------------------------------------------------*/
typedef bool jstk_input_t;
enum {X_AXIS, Y_AXIS};

/* Public functions' prototypes ----------------------------------------------*/
void jstk_init(void);
i2c_status_t jstk_read(uint8_t pdata[static ADC_REGS]);

#endif // JOYSTICK_H