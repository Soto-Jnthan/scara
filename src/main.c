/**
 ******************************************************************************
 * @file    main.c
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   SCARA Robot Controller Application
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "utils.h"
#include "lcd.h"
#include "joystick.h"
#include "accel.h"
#include "servo.h"

/* Private macros -------------------------------------------------------------*/
#define DBNC_BTN(BTN) do {delay_ms(DBNC_DELAY_MS); while (BTN);} while (0)
#define NORM_INPUT(A, AMIN, AMAX) LERP(A, AMIN, AMAX, -MAX_DELTA_POS, (float)MAX_DELTA_POS)

/* Public functions' prototypes -----------------------------------------------*/
void delay_ms(uint16_t ms_cnt);

/* Private functions' prototypes ----------------------------------------------*/
static void state_init(void);
static void state_idle(void);
static void state_jstk(void);
static void state_xlda(void);
static void state_auto(void);

/* Private variables ----------------------------------------------------------*/
static bool xlda_on;
static void (*current_state)(void);
static struct point current_pos = INITIAL_POSITION;
static const struct point figure[] = AUTO_MODE_POINTS;

/**
 * @brief  The application entry point
 * @retval None
 */
void main(void)
{
    current_state = state_init;
    while (1)
        current_state();
}

/**
 * @brief Initialization of the SCARA arm's drivers and peripherals
 * @retval None
 */
static void state_init(void)
{
    PLLCON = PLLCON_INIT_VAL; // Configure core clock
    lcd_init();
    sv_init();
    jstk_init();
    xlda_on = xlda_init() == I2C_ACK;
    sv_move(&current_pos); // Move arm to initial position
    state_idle();
}

/**
 * @brief Idle the SCARA arm until user input is received
 * @retval None
 */
static void state_idle(void)
{
    if (current_state != state_idle) {
        current_state = state_idle;
        lcd_setcolor(LCD_GREEN);
        lcd_cmd(LCD_CLEAR);
        lcd_puts("IDLE Mode");
        lcd_cmd(LCD_ROWTWO);
        lcd_puts("BUT.A:JSTK");
        lcd_cmd(LCD_ROWTHREE);
        lcd_puts("BUT.B:XLDA");
        lcd_cmd(LCD_ROWFOUR);
        lcd_puts("BUT.C:Auto");
        return;
    }

    if (BTNA_CHK) {
        state_jstk();
        return;
    }

    if (xlda_on && BTNB_CHK) {
        state_xlda();
        return;
    }
        
    if (BTNC_CHK) {
        state_auto();
        return;
    }  
}

/**
 * @brief Control the SCARA arm using the joystick module
 * @retval None
 */
static void state_jstk(void)
{
    float dx, dy;
    if (current_state != state_jstk) {
        current_state = state_jstk;
        lcd_setcolor(LCD_CYAN);
        lcd_cmd(LCD_CLEAR);
        lcd_puts("JSTK Mode");
        lcd_cmd(LCD_ROWFOUR);
        lcd_puts("BUT.C:Exit");
        return;
    }

    if (BTNC_CHK) {
        DBNC_BTN(BTNC_CHK);
        state_idle();
        return;
    }

    dx = NORM_INPUT(jstk_read(X_AXIS), JSTK_X_MIN, JSTK_X_MAX);
    if (fabsf(dx) < JSTK_THRSH * MAX_DELTA_POS)
        dx = 0;
    else
        current_pos.x += dx;

    dy = NORM_INPUT(jstk_read(Y_AXIS), JSTK_Y_MIN, JSTK_Y_MAX);
    if (fabsf(dy) < JSTK_THRSH * MAX_DELTA_POS)
        dy = 0;
    else
        current_pos.y += dy;

    /* Press button to toggle tip */ 
    if (JSTK_RIGHT_BTN_CHK) {
        DBNC_BTN(JSTK_RIGHT_BTN_CHK);
        current_pos.z = !current_pos.z;
    }

    if (!sv_move(&current_pos)) {
        current_pos.x -= dx;
        current_pos.y -= dy;
    }
}

/**
 * @brief Control the SCARA arm using the accelerometer module
 * @retval None
 */
static void state_xlda(void)
{
    float dx, dy;
    if (current_state != state_xlda) {
        current_state = state_xlda;
        lcd_setcolor(LCD_CYAN);
        lcd_cmd(LCD_CLEAR);
        lcd_puts("XLDA Mode");
        lcd_cmd(LCD_ROWFOUR);
        lcd_puts("BUT.C:Exit");
        return;
    }

    if (BTNC_CHK) {
        DBNC_BTN(BTNC_CHK);
        state_idle();
        return;
    }

    dx = NORM_INPUT(xlda_read(X_ACC), XLDA_X_MIN, XLDA_X_MAX);
    if (fabsf(dx) < XLDA_THRSH * MAX_DELTA_POS)
        dx = 0;
    else
        current_pos.x += dx;

    dy = NORM_INPUT(xlda_read(Y_ACC), XLDA_Y_MIN, XLDA_Y_MAX);
    if (fabsf(dy) < XLDA_THRSH * MAX_DELTA_POS)
        dy = 0;
    else
        current_pos.y += dy;

    current_pos.z = xlda_read(Z_ACC) >= 0; // Tip down with non-negative g

    if (!sv_move(&current_pos)) {
        current_pos.x -= dx;
        current_pos.y -= dy;
    }
}

/**
 * @brief Control the SCARA arm using the points in "figure" array
 * @retval None
 */
static void state_auto(void)
{
    uint8_t p_cnt;
    if (current_state != state_auto) {
        current_state = state_auto;
        lcd_setcolor(LCD_MAGENTA);
        lcd_cmd(LCD_CLEAR);
        lcd_puts("Auto Mode");
        lcd_cmd(LCD_ROWFOUR);
        lcd_puts("In Progress");
        lcd_cmd(LCD_DCBON);
        return;
    }

    for (p_cnt = 0; p_cnt != ARR_SIZE(figure); p_cnt++) {
        if(!sv_move(&figure[p_cnt])) {
            lcd_cmd(LCD_ROWTWO);
            lcd_puts("Bad Coord.");
            delay_ms(ERR_DELAY_MS);
            break;
        }
        delay_ms(AUTO_MODE_DELAY_MS);
    }

    lcd_cmd(LCD_DONCBOFF);
    sv_move(&current_pos);
    state_idle();
}

/**
 * @brief Blocking delay of a given number of milliseconds
 * @param ms_cnt Time of the delay in milliseconds
 * @retval None
 */
void delay_ms(uint16_t ms_cnt)
{
    for (; ms_cnt; ms_cnt--)
        DELAY_US(1000);
}