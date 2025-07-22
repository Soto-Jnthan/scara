/**
 ******************************************************************************
 * @file    lcd.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Liquid Crystal Display (LCD) Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Private defines -----------------------------------------------------------*/
#define HIGH_NIB_MASK 0xF0U
#define LOG10_256     2.40823996531

#define LCD_POWER_ON_DELAY_MS 40 // 5V:15mS 3.3V:40mS
#define LCD_FUNC_SET_DELAY_MS 5  // 4.1mS
#define LCD_MAX_BUSY_DELAY_MS 2  // 1.52mS
#define LCD_REWRITE_DELAY_MS  1  // 100uS

/* Private macros -------------------------------------------------------------*/
#define LOW_NIB_SHIFT(A) ((A) << 4)

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

    lcd_rs_sbit = 0;
    lcd_4b_wrt(LCD_8BIT1LX8);
    delay_ms(LCD_FUNC_SET_DELAY_MS);

    lcd_e_sbit = 1;
    lcd_e_sbit = 0;
    delay_ms(LCD_REWRITE_DELAY_MS);

    lcd_e_sbit = 1;
    lcd_e_sbit = 0;
    delay_ms(LCD_REWRITE_DELAY_MS);

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
    lcd_e_sbit = 1;
    PORT_LCD_D &= ~HIGH_NIB_MASK;
    PORT_LCD_D |= byte & HIGH_NIB_MASK;
    lcd_e_sbit = 0;
}

/**
 * @brief  Send byte as a command to the LCD
 * @param  cmd Command to be executed
 * @retval None
 */
void lcd_cmd(uint8_t cmd)
{
    lcd_rs_sbit = 0;
    lcd_4b_wrt(cmd);
    lcd_4b_wrt(LOW_NIB_SHIFT(cmd));
    delay_ms(LCD_MAX_BUSY_DELAY_MS);
}

/**
 * @brief  Send byte as a character to the LCD
 * @param  c Character to be printed on the LCD
 * @retval None
 */
void lcd_putchar(char c)
{
    lcd_rs_sbit = 1;
    lcd_4b_wrt(c);
    lcd_4b_wrt(LOW_NIB_SHIFT(c));
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

#if !defined(ENABLE_PUTU) && (defined(ENABLE_PUTI) || defined(ENABLE_PUTF))
#define ENABLE_PUTU
static
#endif

#ifdef ENABLE_PUTU
/**
 * @brief  Send an unsigned integer as an array of characters to the LCD
 * @param  val Unsigned integer to be sent to the LCD
 * @note   Assumed that the LCD has enough columns for all characters
 * @retval None
 */
void lcd_putu(uint16_t val)
{
    uint8_t i = 0;
    char s[(int)(LOG10_256 * sizeof(val)) + 1]; // max_digits
    do {
        s[i++] = (char)(val % 10) + '0';
    } while (val /= 10);
    do {
        lcd_putchar(s[--i]);
    } while (i);
}
#endif

#ifdef ENABLE_PUTI
/**
 * @brief  Send a signed integer as an array of characters to the LCD
 * @param  val Signed integer to be sent to the LCD
 * @note   Assumed that the LCD has enough columns for all characters
 * @retval None
 */
void lcd_puti(int16_t val)
{
    if (val < 0) {
        lcd_putchar('-');
        lcd_putu(-val); // INT_MIN handled properly
    } else {
        lcd_putu(val);
    }
}
#endif

#ifdef ENABLE_PUTF
/**
 * @brief  Send a float as an array of characters to the LCD
 * @param  val Float to be sent to the LCD
 * @note   Value must be within ± lcd_putu's range plus 2 decimal places.
 *         Assumed that the LCD has enough columns for all characters
 * @retval None
 */
void lcd_putf(float val)
{
    uint16_t temp;
    if (val < 0.0f) {
        lcd_putchar('-');
        val = -val;
    }
    lcd_putu(temp = val);
    lcd_putchar('.');
    temp = 100.0f * (val - temp) + 0.5f;
    lcd_putchar(((char)temp / 10) % 10 + '0');
    lcd_putchar((char)temp % 10 + '0');
}
#endif