/**
 ******************************************************************************
 * @file    main.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
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
#define ISUB(N, A, B) ((uint##N##_t)((A) - (B))) // Ensure correct casting. A ≥ B required
#define NORM_INT(N, A, MIN, MAX) (2.0 * MAX_DELTA / ISUB(N, MAX, MIN) * ISUB(N, A, MIN) - MAX_DELTA)

/* Public functions' prototypes -----------------------------------------------*/
void delay_ms(uint16_t ms_cnt);

/* Private functions' prototypes ----------------------------------------------*/
static void state_init(void);
static void state_idle(void);
static void state_jstk(void);
static void state_xlda(void);
static void state_auto(void);

/* Private variables ----------------------------------------------------------*/
static point_t current_pos = INITIAL_POSITION;
static enum {ST_INIT, ST_IDLE, ST_JSTK, ST_XLDA, ST_AUTO} current_state;
static void (*const code state_arr[])(void) = {state_init, state_idle, state_jstk, state_xlda, state_auto};

/**
 * @brief  The application entry point
 * @retval None
 */
void main(void)
{
    PLLCON = PLLCON_INIT_VAL; // Configure core clock
    while (1)
        state_arr[current_state]();
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
    if (current_state != ST_IDLE) {
        current_state = ST_IDLE;
        sv_move(&current_pos); // Init/revert current_pos
        LCD_SETCOLOR(LCD_GREEN);
        LCD_PUTS_AT("IDLE Mode", LCD_CLEAR);
        LCD_PUTS_AT("BUT.A:JSTK", LCD_ROWTWO);
        LCD_PUTS_AT("BUT.B:XLDA", LCD_ROWTHREE);
        LCD_PUTS_AT("BUT.C:Auto", LCD_ROWFOUR);
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
    float delta;
    point_t old_pos;
    jstk_out_t readout;
    if (current_state != ST_JSTK) {
        current_state = ST_JSTK;
        LCD_SETCOLOR(LCD_CYAN);
        LCD_PUTS_AT("JSTK Mode", LCD_CLEAR);
        LCD_PUTS_AT("BUT.C:Exit", LCD_ROWFOUR);
        jstk_init();
        return;
    }

    if (BTNC_CHK) {
        JSTK_DISABLE();
        state_idle();
        DBNC_BTN(BTNC_CHK);
        return;
    }

    if (jstk_read(&readout) != ADC_OK) {
        LCD_SETCOLOR(LCD_RED);
        LCD_PUTS_AT("ADC_ERR", LCD_ROWTWO);
        return;
    }

    old_pos = current_pos;

    delta = NORM_INT(8, readout.x, JSTK_X_MIN, JSTK_X_MAX);
    if (fabs(delta) >= JSTK_THRSH * MAX_DELTA)
        current_pos.x += delta;

    delta = NORM_INT(8, readout.y, JSTK_Y_MIN, JSTK_Y_MAX);
    if (fabs(delta) >= JSTK_THRSH * MAX_DELTA)
        current_pos.y += delta;

    if (JSTK_TIP_BTN_CHK) {
        DBNC_BTN(JSTK_TIP_BTN_CHK);
        current_pos.z = !current_pos.z;
    }

    if (!sv_move(&current_pos))
        current_pos = old_pos;
}

/**
 * @brief Control the SCARA arm using the accelerometer module
 * @retval None
 */
static void state_xlda(void)
{
    float delta;
    point_t old_pos;
    xlda_out_t readout;
    static i2c_status_t init_nack;
    static code const xlda_ctrl_t xl_on = CTRL_ON_VALS;
    static code const xlda_ctrl_t xl_off = CTRL_OFF_VALS;
    if (current_state != ST_XLDA) {
        current_state = ST_XLDA;
        LCD_SETCOLOR(LCD_CYAN);
        LCD_PUTS_AT("XLDA Mode", LCD_CLEAR);
        LCD_PUTS_AT("BUT.C:Exit", LCD_ROWFOUR);
        init_nack = xlda_init(&xl_on);
        return;
    }

    if (BTNC_CHK) {
        xlda_init(&xl_off);
        state_idle();
        DBNC_BTN(BTNC_CHK);
        return;
    }

    if (init_nack | xlda_read(&readout)) {
        LCD_SETCOLOR(LCD_RED);
        LCD_PUTS_AT("I2C_ERR", LCD_ROWTWO);
        return;
    }

    old_pos = current_pos;

    delta = NORM_INT(16, readout.x, XLDA_X_MIN, XLDA_X_MAX);
    if (fabs(delta) >= XLDA_THRSH * MAX_DELTA)
        current_pos.x += delta;

    delta = NORM_INT(16, readout.y, XLDA_Y_MIN, XLDA_Y_MAX);
    if (fabs(delta) >= XLDA_THRSH * MAX_DELTA)
        current_pos.y += delta;

    current_pos.z = readout.z >= 0; // Tip down with non-negative g

    if (!sv_move(&current_pos))
        current_pos = old_pos;
}

/**
 * @brief Control the SCARA arm using AUTO_MODE_POINTS
 * @retval None
 */
static void state_auto(void)
{
    static uint8_t p_cnt;
    static code const point_t auto_arr[] = AUTO_MODE_POINTS;
    if (current_state != ST_AUTO) {
        current_state = ST_AUTO;
        LCD_SETCOLOR(LCD_MAGENTA);
        LCD_PUTS_AT("Auto Mode", LCD_CLEAR);
        LCD_PUTS_AT("BUT.C:Exit", LCD_ROWFOUR);
        LCD_PUTS_AT("In Progress", LCD_ROWTHREE);
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
        LCD_SETCOLOR(LCD_RED);
        LCD_PUTS_AT("BAD_COORD.", LCD_ROWTWO);
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