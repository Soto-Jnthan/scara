/**
 ******************************************************************************
 * @file    lcd.c
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   Liquid Crystal Display (LCD) Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Private defines -----------------------------------------------------------*/
#define HIGH_NIB_MASK 0xF0U

#define LCD_POWER_ON_DELAY_MS 40 // 5V:15mS 3.3V:40mS
#define LCD_FUNC_SET_DELAY_MS 5  // 4.1mS
#define LCD_MAX_BUSY_DELAY_MS 2  // 1.52mS
#define LCD_REWRITE_DELAY_MS  1  // 100uS

/* Private macros -------------------------------------------------------------*/
#define SWAP_NIBS(A) ((A) >> 4 | (A) << 4) // Compiler uses SWAP opcode
#define LCD_SET_E()  PORT_LCD_CTRL |= LCD_E_PIN_MASK
#define LCD_CLR_E()  PORT_LCD_CTRL &= ~LCD_E_PIN_MASK
#define LCD_SET_RS() PORT_LCD_CTRL |= LCD_RS_PIN_MASK
#define LCD_CLR_RS() PORT_LCD_CTRL &= ~LCD_RS_PIN_MASK

/* Imported functions' prototypes ---------------------------------------------*/
extern void delay_ms(uint16_t ms_cnt);

/* Private functions' prototypes ----------------------------------------------*/
static void lcd_4b_wrt(uint8_t byte);

/**
 * @brief Initialize the LCD
 * @retval None
 */
void lcd_init(void)
{
    delay_ms(LCD_POWER_ON_DELAY_MS);

    LCD_CLR_RS();
    lcd_4b_wrt(LCD_8BIT1LX8);
    delay_ms(LCD_FUNC_SET_DELAY_MS);

    LCD_SET_E();
    LCD_CLR_E();
    delay_ms(LCD_REWRITE_DELAY_MS);

    LCD_SET_E();
    LCD_CLR_E();
    delay_ms(LCD_REWRITE_DELAY_MS);

    /* 4-bit interface */
    lcd_4b_wrt(LCD_4BIT1LX8);
    delay_ms(LCD_REWRITE_DELAY_MS);
    
    lcd_cmd(LCD_4BIT2LX8);
    lcd_cmd(LCD_DCBOFF);
    lcd_cmd(LCD_CLEAR);
    lcd_cmd(LCD_CINC);
    lcd_cmd(LCD_DONCBOFF);
}

/**
 * @brief  Write to the four most significant bits of the LCD's data port
 * @param  byte Byte containing the four most significant bits to be written
 * @retval None
 */
static void lcd_4b_wrt(uint8_t byte)
{
    LCD_SET_E();
    PORT_LCD_D &= ~HIGH_NIB_MASK;
    PORT_LCD_D |= byte & HIGH_NIB_MASK;
    LCD_CLR_E();
}

/**
 * @brief  Send byte as a command to the LCD
 * @param  cmd Command to be executed
 * @retval None
 */
void lcd_cmd(uint8_t cmd)
{
    LCD_CLR_RS();
    lcd_4b_wrt(cmd);
    lcd_4b_wrt(SWAP_NIBS(cmd));
    delay_ms(LCD_MAX_BUSY_DELAY_MS);
}

/**
 * @brief  Send byte as a character to the LCD
 * @param  c Character to be printed on the LCD
 * @retval None
 */
void lcd_putchar(char c)
{
    LCD_SET_RS();
    lcd_4b_wrt(c);
    lcd_4b_wrt(SWAP_NIBS(c));
    delay_ms(LCD_REWRITE_DELAY_MS);
}

/**
 * @brief  Send a null-terminated string to the LCD
 * @param  str Pointer to null-terminated array of characters
 * @retval None
 */
void lcd_puts(const char *str)
{
    while (*str != '\0')
        lcd_putchar(*str++);
}