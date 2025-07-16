/**
 ******************************************************************************
 * @file    joystick.c
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Joystick Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "joystick.h"

/**
 * @brief Initialization of the ADCs connected to the joystick
 * @retval None
 */
void jstk_init(void)
{
    ADC0CON = JSTK_ADC0CON_VAL;
    ADC1CON = JSTK_ADC1CON_VAL;
    SF = JSTK_SF_VAL;
    ADCMODE = JSTK_ADCMODE_VAL;
}

/**
 * @brief Read the values of the two axes of the joystick
 * @note ADC0 and ADC1 assumed to be connected to x-axis and y-axis respectively
 * @param pdata Pointer to jstk_out_t used for data reception
 * @retval ADC_OK if both ADC readings were successfuly, ADC_ERR otherwise
 */
adc_status_t jstk_read(jstk_out_t *pdata)
{
    RDY0 = 0;
    RDY1 = 0;
    while (!RDY0);
    pdata->x = ADC0H;
    while (!RDY1);
    pdata->y = ADC1H;
    return ERR0 | ERR1;
}