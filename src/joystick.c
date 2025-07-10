/**
 ******************************************************************************
 * @file    joystick.c
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
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
 * @param pdata Pointer to data buffer (size of at least ADC_REGS bytes)
 * @retval ADC_OK if both ADC readings were successfuly, ADC_ERR otherwise
 */
adc_status_t jstk_read(uint8_t pdata[static ADC_REGS])
{
    RDY0 = 0;
    RDY1 = 0;
    while (!RDY0);
    pdata[X_AXIS] = ADC0H;
    while (!RDY1);
    pdata[Y_AXIS] = ADC1H;
    return ERR0 | ERR1;
}