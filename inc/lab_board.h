/**
 ******************************************************************************
 * @file    lab_board.h
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   This file contains the defines of the MCU development board at use
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LAB_BOARD_H
#define LAB_BOARD_H

/* Includes ------------------------------------------------------------------*/
#include <ADuC834.h>

/* Public defines ------------------------------------------------------------*/
#define BTN1_CHK           (!P1_1)
#define BTN2_CHK           (!P2_0)
#define BTN3_CHK           (!P3_5)
#define BTN4_CHK           (!P3_2)
#define BTN5_CHK           (!P3_3)

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
#define LCD_RS_SBIT        P3_6
#define LCD_E_SBIT         P3_7

#define PORT_LCD_LED       P2
#define LCD_RED_LED_MASK   (1u << 1)
#define LCD_GREEN_LED_MASK (1u << 2)
#define LCD_BLUE_LED_MASK  (1u << 3)

#endif // LAB_BOARD_H