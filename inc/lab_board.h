/**
 ******************************************************************************
 * @file    lab_board.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   This file contains the definitions of the MCU development board at use
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LAB_BOARD_H
#define LAB_BOARD_H

/* Includes ------------------------------------------------------------------*/
#include <ADuC834.h>

/* Public defines ------------------------------------------------------------*/
sbit btn1_sbit =           P1 ^ 1;
sbit btn2_sbit =           P2 ^ 0;
sbit btn3_sbit =           P3 ^ 5;
sbit btn4_sbit =           P3 ^ 2;
sbit btn5_sbit =           P3 ^ 3;

#define BTN1_CHK           (!btn1_sbit)
#define BTN2_CHK           (!btn2_sbit)
#define BTN3_CHK           (!btn3_sbit)
#define BTN4_CHK           (!btn4_sbit)
#define BTN5_CHK           (!btn5_sbit)

/* SV lines are inverted */
#define PORT_SV            P0
#define SV1_PIN            4
#define SV2_PIN            5
#define SV3_PIN            6
#define SV4_PIN            7

#define PORT_LED           P0
#define LED2_PIN_MASK      (1u << 7)
#define LED3_PIN_MASK      (1u << 6)
#define LED4_PIN_MASK      (1u << 5)
#define LED5_PIN_MASK      (1u << 4)

#define PORT_LCD_D         P2
sbit lcd_rs_sbit =         P3 ^ 6;
sbit lcd_e_sbit  =         P3 ^ 7;

#define PORT_LCD_LED       P2
#define LCD_RED_LED_MASK   (1u << 1)
#define LCD_GREEN_LED_MASK (1u << 2)
#define LCD_BLUE_LED_MASK  (1u << 3)

#endif // LAB_BOARD_H