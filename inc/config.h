/**
 ******************************************************************************
 * @file    config.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   This file contains the config definitions for the SCARA project
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONFIG_H
#define CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "lab_board.h"

/* Public defines ------------------------------------------------------------*/

/* main config definitions: */
#define PLLCON_INIT_VAL    0x00     // Must be assigned to PLLCON at application entry
#define INITIAL_POSITION   {10, 10}
#define MAX_DELTA          0.5      // SCARA arm max movement step in centimeters (absolute value)
#define AUTO_MODE_DELAY_MS 1000     // Delay between each auto mode step in milliseconds
#define DBNC_DELAY_MS      5        // Button debounce delay in milliseconds
#define BTNA_CHK           BTN1_CHK
#define BTNB_CHK           BTN2_CHK
#define BTNC_CHK           BTN4_CHK
#define AUTO_MODE_POINTS   {\
	{-5.0, 15.0}, {-5.0, 15.0, 1}, {-8.91, 13.12, 1}, {-9.87, 8.89, 1},\
	{-7.17, 5.5, 1}, {-2.83, 5.5, 1}, {-0.13, 8.89, 1}, {-1.09, 13.12, 1},\
	{-5.0, 15.0, 1}, {-5.0, 15.0}} // Equidistant points on (x+5)^2+(y-10)^2=25
/* These may be transformed at compile time to their timer value equivalents, but
runtime transformations still needed for JSTK/XLDA modes */

/* joystick config definitions: */
#define JSTK_FRONT_BTN_CHK BTN2_CHK
#define JSTK_BACK_BTN_CHK  BTN3_CHK
#define JSTK_RIGHT_BTN_CHK BTN5_CHK
#define JSTK_LEFT_BTN_CHK  BTN4_CHK
#define JSTK_TIP_BTN_CHK   JSTK_BACK_BTN_CHK
#define JSTK_ADC0CON_VAL   0x4F // ADC0 set to full scale unipolar mode from AIN1 to AIN2 with XREF
#define JSTK_ADC1CON_VAL   0x58 // ADC0 set to unipolar mode from AIN4 to GND with XREF
#define JSTK_SF_VAL        0x0D // Max ADC Output Update Rate
#define JSTK_ADCMODE_VAL   0x33 // ADC0 and ADC1 powered on in continuous conversion mode
#define JSTK_ADCOFF_VAL    0x00 
#define JSTK_X_MAX         200  // [0 ≤ JSTK_X_MIN ≤ JSTK_X_MAX ≤ 255]
#define JSTK_X_MIN         55
#define JSTK_Y_MAX         200  // [0 ≤ JSTK_Y_MIN ≤ JSTK_Y_MAX ≤ 255]
#define JSTK_Y_MIN         55
#define JSTK_THRSH         0.1  // Joystick input threshold (between 0 and 1.0)

/* accel config definitions: */
#define LSM6DS_A0_VAL 1
#define CTRL_ON_VALS  {0x50, 0x00, 0x06} // {CTRL1_XL, CTRL2_G, CTRL3_C}
#define CTRL_OFF_VALS {0x00, 0x00, 0x05}
#define XLDA_X_MAX    32767              // [-32768 ≤ XLDA_X_MIN ≤ XLDA_X_MAX ≤ 32767] 
#define XLDA_X_MIN    -32768
#define XLDA_Y_MAX    32767              // [-32768 ≤ XLDA_Y_MIN ≤ XLDA_Y_MAX ≤ 32767]
#define XLDA_Y_MIN    -32768 
#define XLDA_THRSH    0.1                // Accelerometer input threshold (between 0 and 1.0)

/* lcd config definitions: */
#define LCD_COLUMNS_PER_ROW 12

/* servo config definitions: */
#define SV_L1            8.0    // Arm length of 'base' servo (in centimeters)
#define SV_L2            9.0    // Arm length of 'mid' servo (in centimeters)
#define SV_MAX_US_PULSE  2000.0 // HIGH pulse time for maximum angle in microseconds
#define SV_MIN_US_PULSE  1000.0 // HIGH pulse time for minimum angle in microseconds
#define SV_FREQUENCY     50.0   // Hz

#endif // CONFIG_H