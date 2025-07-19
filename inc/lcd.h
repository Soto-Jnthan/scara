/**
 ******************************************************************************
 * @file    lcd.h
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Header for lcd.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LCD_H
#define LCD_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Public defines ------------------------------------------------------------*/
//#define ENABLE_PUTU
//#define ENABLE_PUTI
//#define ENABLE_PUTF

/* Public typedefs/enums -----------------------------------------------------*/
enum lcd_command {
//                                      D7  D6  D5  D4  D3   D2  D1   D0
    LCD_CLEAR   = 0x01,   //             0   0   0   0   0    0   0    1
    LCD_RETHOME = 0x02,   //             0   0   0   0   0    0   1    *
// Entry Set                             0   0   0   0   0    1  I/D   S
    LCD_CDEC   = 0x04,    //             0   0   0   0   0    1   0    0
    LCD_CWDDEC = 0x05,    //             0   0   0   0   0    1   0    1
    LCD_CINC   = 0x06,    //             0   0   0   0   0    1   1    0
    LCD_CWDINC = 0x07,    //             0   0   0   0   0    1   1    1
// Display-Cursor-Blink On/Off Control   0   0   0   0   1    D   C    B
    LCD_DCBOFF   = 0x08,  //             0   0   0   0   1    0   0    0
    LCD_DONCBOFF = 0x0C,  //             0   0   0   0   1    1   0    0
    LCD_DBONCOFF = 0x0D,  //             0   0   0   0   1    1   0    1
    LCD_DCONBOFF = 0x0E,  //             0   0   0   0   1    1   1    0
    LCD_DCBON    = 0x0F,  //             0   0   0   0   1    1   1    1
// Cursor-Dispay Shift                   0   0   0   1  S/C  R/L  *    *
    LCD_LCSHIFT = 0x10,   //             0   0   0   1   0    0   *    *
    LCD_RCSHIFT = 0x14,   //             0   0   0   1   0    1   *    *
    LCD_LDSHIFT = 0x18,   //             0   0   0   1   1    0   *    *
    LCD_RDSHIFT = 0x1C,   //             0   0   0   1   1    1   *    *
// Function Set                          0   0   1   DL  N    F   *    *
    LCD_4BIT1LX8  = 0x20, //             0   0   1   0   0    0   *    *
    LCD_4BIT1LX10 = 0x24, //             0   0   1   0   0    1   *    *
    LCD_4BIT2LX8  = 0x28, //             0   0   1   0   1    *   *    *
    LCD_8BIT1LX8  = 0x30, //             0   0   1   1   0    0   *    *
    LCD_8BIT1LX10 = 0x34, //             0   0   1   1   0    1   *    *
    LCD_8BIT2LX8  = 0x38, //             0   0   1   1   1    *   *    *
// Set CGRAM address                     0   1  Acg Acg Acg  Acg Acg  Acg
// Set DDRAM address                     1  Add Add Add Add  Add Add  Add
    LCD_ROWONE   = 0x80,  //             1   0   0   0   0    0   0    0
    LCD_ROWTWO   = 0xC0,  //             1   1   0   0   0    0   0    0
    LCD_ROWTHREE = LCD_ROWONE + LCD_COLUMNS_PER_ROW,
    LCD_ROWFOUR  = LCD_ROWTWO + LCD_COLUMNS_PER_ROW
// I/D: 0 = Decrement cursor position,  1 = Increment cursor position
// S:   0 = No display shift,           1 = Display shift
// D:   0 = Display off,                1 = Display on
// C:   0 = Cursor off,                 1 = Cursor on
// B:   0 = Cursor blink off,           1 = Cursor blink on
// S/C: 0 = Move cursor,                1 = Shift display
// R/L: 0 = Shift left,                 1 = Shift right
// F:   0 = 5x8 dots fonts,             1 = 5x10 dots fonts
// N:   0 = 1 line,                     1 = 2 lines (Only 5x8 fonts)
// DL:  0 = 4-bit interface,            1 = 8-bit interface
// Acg: Character Generator RAM,        Add: Display Data RAM
// *:   Don't Care
};

typedef enum {
    LCD_NOLEDS,
    LCD_RED = LCD_RED_LED_MASK, // RGB
    LCD_GREEN = LCD_GREEN_LED_MASK,
    LCD_BLUE = LCD_BLUE_LED_MASK,
    LCD_CYAN = LCD_GREEN | LCD_BLUE, // CMY
    LCD_MAGENTA = LCD_RED | LCD_BLUE,
    LCD_YELLOW = LCD_RED | LCD_GREEN,
    LCD_WHITE = LCD_RED | LCD_GREEN | LCD_BLUE
} lcd_color_t;

/* Public functions' prototypes ----------------------------------------------*/
void lcd_init(void);
void lcd_cmd(uint8_t cmd); // No enum type to avoid CG/DDRAM address warnings
void lcd_putchar(char c);
void lcd_puts(const char *str);

#ifdef ENABLE_PUTU
void lcd_putu(uint16_t val);
#endif

#ifdef ENABLE_PUTI
void lcd_puti(int16_t val);
#endif

#ifdef ENABLE_PUTF
void lcd_putf(float val);
#endif

/* Public inline functions' definitions --------------------------------------*/

/**
 * @brief  Turn on/off the LEDs of the LCD
 * @param  c Specify LEDs to be turned on via lcd_color_t enum
 * @retval None
 */
inline void lcd_setcolor(lcd_color_t c)
{
    PORT_LCD_LED &= ~c;
    PORT_LCD_LED |= c ^ LCD_WHITE;
}

/**
 * @brief  Send a command and a null-terminated string to the LCD
 * @param  str Pointer to null-terminated array of characters
 * @param  cmd Command to be executed before sending the array
 * @retval None
 */
inline void lcd_puts_at(const char *str, uint8_t cmd)
{
    lcd_cmd(cmd);
    lcd_puts(str);
}

#endif // LCD_H