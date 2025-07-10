/**
 ******************************************************************************
 * @file    config.h
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   This file contains the config defines for the SCARA project
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONFIG_H
#define CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "lab_board.h"

/* Public defines ------------------------------------------------------------*/

/* main config definitions: */
#define PLLCON_INIT_VAL    0x00 // Must be assigned to PLLCON at application entry
#define INITIAL_POSITION   {10, 10}
#define MAX_DELTA_POS      0.5  // SCARA arm max movement step in centimeters (absolute value)
#define AUTO_MODE_DELAY_MS 1000 // Delay between each auto mode step in milliseconds
#define DBNC_DELAY_MS      5    // Button debounce delay in milliseconds
#define BTNA_CHK           BTN1_CHK
#define BTNB_CHK           BTN2_CHK
#define BTNC_CHK           BTN4_CHK
#define AUTO_MODE_POINTS   {{-5.0, 15.0}, {-5.0, 15.0, 1}, {-6.62, 14.73, 1}, {-8.07, 13.95, 1},\
    {-9.19, 12.73, 1},{-9.85, 11.23, 1}, {-9.98, 9.59, 1}, {-9.58, 7.99, 1}, {-8.68, 6.61, 1},\
    {-7.38, 5.6, 1}, {-5.82, 5.07, 1}, {-4.18, 5.07, 1}, {-2.62, 5.6, 1}, {-1.32, 6.61, 1},\
    {-0.42, 7.99, 1},{-0.02, 9.59, 1}, {-0.15, 11.23, 1}, {-0.81, 12.73, 1}, {-1.93, 13.95, 1},\
    {-3.38, 14.73, 1},{-5.0, 15.0, 1}, {-5.0, 15.0}, {-7.5, 12.5}, {-7.5, 12.5, 1}, {-6.5, 12.5, 1},\
    {-5.5, 12.5, 1},{-4.5, 12.5, 1}, {-3.5, 12.5, 1}, {-2.5, 12.5, 1}, {-2.5, 11.5, 1}, {-2.5, 10.5, 1},\
    {-2.5, 9.5, 1},{-2.5, 8.5, 1}, {-2.5, 7.5, 1}, {-3.5, 7.5, 1}, {-4.5, 7.5, 1}, {-5.5, 7.5, 1},\
    {-6.5, 7.5, 1}, {-7.5, 7.5, 1}, {-7.5, 8.5, 1}, {-7.5, 9.5, 1}, {-7.5, 10.5, 1}, {-7.5, 11.5, 1},\
    {-7.5, 12.5, 1}, {-7.5, 12.5}} // (x+5)^2 + (y-10)^2 = 25 with square of lenght 5
/* These may be transformed at compile time to their timer value equivalents, but
runtime transformations still needed for JSTK/XLDA modes */

/* joystick config definitions: */
#define JSTK_FRONT_BTN_CHK BTN2_CHK
#define JSTK_BACK_BTN_CHK  BTN3_CHK
#define JSTK_RIGHT_BTN_CHK BTN5_CHK
#define JSTK_LEFT_BTN_CHK  BTN4_CHK
#define JSTK_TIP_BTN_CHK   JSTK_BACK_BTN_CHK
#define JSTK_X_MAX         200 // [0 <= JSTK_X_MIN <= JSTK_X_MAX <= 255]
#define JSTK_X_MIN         55
#define JSTK_Y_MAX         200 // [0 <= JSTK_Y_MIN <= JSTK_Y_MAX <= 255]
#define JSTK_Y_MIN         55
#define JSTK_THRSH         0.1 // Joystick input threshold (between 0 and 1.0)

/* accel config definitions: */
#define LSM6DS_A0_VAL 1
#define CTRL1_ON_VAL  0x50 // 208 Hz (normal mode) 
#define CTRL1_OFF_VAL 0
#define XLDA_X_MAX    127 // [-128 <= XLDA_X_MIN <= XLDA_X_MAX <= 127]
#define XLDA_X_MIN    -128
#define XLDA_Y_MAX    127 // [-128 <= XLDA_Y_MIN <= XLDA_Y_MAX <= 127]
#define XLDA_Y_MIN    -128
#define XLDA_THRSH    0.1 // Accelerometer input threshold (between 0 and 1.0)

/* lcd config definitions: */
#define LCD_COLUMNS_PER_ROW 12

/* servo config definitions: */
#define SV_L1           8.0    // Arm length of 'base' servo (in centimeters)
#define SV_L2           9.0    // Arm length of 'mid' servo (in centimeters)
#define SV_MAX_US_PULSE 2000.0 // HIGH pulse time for maximum angle in microseconds
#define SV_MIN_US_PULSE 1000.0 // HIGH pulse time for minimum angle in microseconds
#define SV_FREQUENCY    50.0   // Hz

#endif // CONFIG_H