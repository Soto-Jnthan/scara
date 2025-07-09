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

/* Public defines ------------------------------------------------------------*/
#define ADC_REGS (Y_AXIS + 1)

/* Public typedefs/enums -----------------------------------------------------*/
typedef bool jstk_input_t;
enum {X_AXIS, Y_AXIS};

typedef bool adc_status_t;
enum {ADC_OK, ADC_ERR};

/* Public functions' prototypes ----------------------------------------------*/
void jstk_init(void);
adc_status_t jstk_read(uint8_t pdata[static ADC_REGS]);

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