/**
 ******************************************************************************
 * @file    joystick.h
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   Header for joystick.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef JOYSTICK_H
#define JOYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Public typedefs/enums -----------------------------------------------------*/
typedef bool jstk_input_t;
enum {X_AXIS, Y_AXIS};

/* Public functions' prototypes ----------------------------------------------*/
void jstk_init(void);
uint8_t jstk_read(jstk_input_t in);

#endif // JOYSTICK_H