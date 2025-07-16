/**
 ******************************************************************************
 * @file    main.c
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
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
#define DBNC_BTN(BTN_CHK) do {delay_ms(DBNC_DELAY_MS); while (BTN_CHK);} while (0)
#define ISUB(A, B) ((A) + (int16_t)~(B) + 1) // Avoid -INT_MIN integer promotion
#define NORM_INT(A, MIN, MAX) (2.0 * MAX_DELTA / ISUB(MAX, MIN) * ISUB(A, MIN) - MAX_DELTA)

/* Public functions' prototypes -----------------------------------------------*/
void delay_ms(uint16_t ms_cnt);

/* Private functions' prototypes ----------------------------------------------*/
static void state_init(void);
static void state_idle(void);
static void state_jstk(void);
static void state_xlda(void);
static void state_auto(void);

/* Private variables ----------------------------------------------------------*/
static void (*current_state)(void) = state_init;
static struct point current_pos = INITIAL_POSITION;

/**
 * @brief  The application entry point
 * @retval None
 */
void main(void)
{
    PLLCON = PLLCON_INIT_VAL; // Configure core clock
    while (1)
        current_state();
}

/**
 * @brief Initialization of the SCARA arm's drivers and peripherals
 * @retval None
 */
static void state_init(void)
{
    lcd_init();
    sv_init();
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
        sv_move(&current_pos); // Init/revert current_pos
        lcd_setcolor(LCD_GREEN);
        lcd_puts_at("IDLE Mode", LCD_CLEAR);
        lcd_puts_at("BUT.A:JSTK", LCD_ROWTWO);
        lcd_puts_at("BUT.B:XLDA", LCD_ROWTHREE);
        lcd_puts_at("BUT.C:Auto", LCD_ROWFOUR);
        return;
    }

    if (BTNA_CHK) {
        state_jstk();
        return;
    }

    if (BTNB_CHK) {
        state_xlda();
        return;
    }

    if (BTNC_CHK) {
        DBNC_BTN(BTNC_CHK);
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
    uint8_t readout[ADC_REGS];
    if (current_state != state_jstk) {
        current_state = state_jstk;
        lcd_setcolor(LCD_CYAN);
        lcd_puts_at("JSTK Mode", LCD_CLEAR);
        lcd_puts_at("BUT.C:Exit", LCD_ROWFOUR);
        jstk_init();
        return;
    }

    if (BTNC_CHK) {
        jstk_disable();
        state_idle();
        DBNC_BTN(BTNC_CHK);
        return;
    }

    if (jstk_read(readout) != ADC_OK) {
        lcd_setcolor(LCD_RED);
        lcd_puts_at("ADC_ERR", LCD_ROWTWO);
        return;
    }

    dx = NORM_INT(readout[X_AXIS], JSTK_X_MIN, JSTK_X_MAX);
    if (fabsf(dx) < JSTK_THRSH * MAX_DELTA)
        dx = 0;
    else
        current_pos.x += dx;

    dy = NORM_INT(readout[Y_AXIS], JSTK_Y_MIN, JSTK_Y_MAX);
    if (fabsf(dy) < JSTK_THRSH * MAX_DELTA)
        dy = 0;
    else
        current_pos.y += dy;

    if (JSTK_TIP_BTN_CHK) {
        DBNC_BTN(JSTK_TIP_BTN_CHK);
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
    xlda_out_t readout;
    static i2c_status_t init_nack;
    if (current_state != state_xlda) {
        current_state = state_xlda;
        lcd_setcolor(LCD_CYAN);
        lcd_puts_at("XLDA Mode", LCD_CLEAR);
        lcd_puts_at("BUT.C:Exit", LCD_ROWFOUR);
        init_nack = xlda_init(CTRL1_ON_VAL);
        return;
    }

    if (BTNC_CHK) {
        xlda_init(CTRL1_OFF_VAL);
        state_idle();
        DBNC_BTN(BTNC_CHK);
        return;
    }

    if (init_nack || xlda_read(&readout)) {
        lcd_setcolor(LCD_RED);
        lcd_puts_at("I2C_ERR", LCD_ROWTWO);
        return;
    }

    dx = NORM_INT(readout.x, XLDA_X_MIN, XLDA_X_MAX);
    if (fabsf(dx) < XLDA_THRSH * MAX_DELTA)
        dx = 0;
    else
        current_pos.x += dx;

    dy = NORM_INT(readout.y, XLDA_Y_MIN, XLDA_Y_MAX);
    if (fabsf(dy) < XLDA_THRSH * MAX_DELTA)
        dy = 0;
    else
        current_pos.y += dy;

    current_pos.z = readout.z >= 0; // Tip down with non-negative g

    if (!sv_move(&current_pos)) {
        current_pos.x -= dx;
        current_pos.y -= dy;
    }
}

/**
 * @brief Control the SCARA arm using AUTO_MODE_POINTS
 * @retval None
 */
static void state_auto(void)
{
    static uint8_t p_cnt;
    static const struct point auto_arr[] = AUTO_MODE_POINTS;
    if (current_state != state_auto) {
        current_state = state_auto;
        lcd_setcolor(LCD_MAGENTA);
        lcd_puts_at("Auto Mode", LCD_CLEAR);
        lcd_puts_at("BUT.C:Exit", LCD_ROWFOUR);
        lcd_puts_at("In Progress", LCD_ROWTHREE);
        lcd_cmd(LCD_DCBON);
        return;
    }

    if (BTNC_CHK || p_cnt == ARR_SIZE(auto_arr)) {
        p_cnt = 0;
        lcd_cmd(LCD_DONCBOFF);
        state_idle();
        DBNC_BTN(BTNC_CHK);
        return;
    }

    if (!sv_move(&auto_arr[p_cnt++])) {
        lcd_setcolor(LCD_RED);
        lcd_puts_at("BAD_COORD.", LCD_ROWTWO);
    }

    delay_ms(AUTO_MODE_DELAY_MS);
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