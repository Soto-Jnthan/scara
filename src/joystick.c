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
    ADC0CON = 0x4F; // ADC0 set to full scale unipolar mode from AIN1 to AIN2 with XREF
    ADC1CON = 0x58; // ADC0 set to unipolar mode from AIN4 to GND with XREF
    SF = 0x0D;      // Max ADC Output Update Rate
    ADCMODE = 0x33; // ADC0 and ADC1 powered on in continuous conversion mode
}

/**
 * @brief Read the value of one of the two axes of the joystick
 * @note ADC0 and ADC1 assumed to be connected to x-axis and y-axis respectively
 * @param in Axis to be read via JSTK_Input enum
 * @retval Readout from the joystick
 */
uint8_t jstk_read(jstk_input_t in)
{
    if (in == X_AXIS) {
        RDY0 = 0;
        while (!RDY0);
        return ADC0H;
    } else {
        RDY1 = 0;
        while (!RDY1);
        return ADC1H;
    }
}