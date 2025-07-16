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

/* Public typedefs/enums -----------------------------------------------------*/
typedef struct {uint8_t x; uint8_t y;} jstk_out_t;

typedef bool adc_status_t;
enum {ADC_OK, ADC_ERR};

/* Public functions' prototypes ----------------------------------------------*/
void jstk_init(void);
adc_status_t jstk_read(jstk_out_t *pdata);

/* Public inline functions' definitions --------------------------------------*/

/**
 * @brief Turn off the ADCs connected to the joystick
 * @retval None
 */
inline void jstk_disable(void)
{
    ADCMODE &= ~(ADC0EN | ADC1EN);
}

#endif // JOYSTICK_H