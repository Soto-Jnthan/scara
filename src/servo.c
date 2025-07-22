/**
 ******************************************************************************
 * @file    servo.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Servomotor Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <intrins.h>
#include "servo.h"

/* Private macros ------------------------------------------------------------*/
#define SQR(A) ((A) * (A))
#define GET_SV_MASK(A) (1U << (A == BASE ? SV1_PIN : A == MID ? SV2_PIN : SV3_PIN))
#define BRANCH_DELAY() do {_nop_(); _nop_();} while (0) // JNB delay

/* Private variables ----------------------------------------------------------*/
sbit base_sbit = PORT_SV ^ SV1_PIN;
sbit mid_sbit = PORT_SV ^ SV2_PIN;
sbit tip_sbit = PORT_SV ^ SV3_PIN;
static uint16_t sv_rcap[] = {-SV_MID_CNT, -SV_MID_CNT, -SV_MIN_CNT}; // Timer values of servos

/**
 * @brief Initialization of the driver's peripherals
 * @note TMR2 to be reserved for sending the control pulses
 * @retval None
 */
void sv_init(void)
{
    RCAP2H = HIGHBYTE(sv_rcap[BASE]);
    RCAP2L = LOWBYTE(sv_rcap[BASE]);
    EA = 1;
    ET2 = 1;
    TR2 = 1;
}

/**
 * @brief Adjust the pulse width for a specific servomotor
 * @param sv Target servomotor via servo_t enum
 * @param cnt Pulse width given as a number of machine cycles
 * @note No changes occur if value is not between SV_MIN_CNT and SV_MAX_CNT
 * @retval True if executed, false otherwise
 */
bool sv_setcnt(servo_t sv, uint16_t cnt)
{
    if (sv > TIP || cnt > SV_MAX_CNT || cnt < SV_MIN_CNT)
        return false;
    sv_rcap[sv] = -cnt;
    return true;
}

/**
 * @brief Position the arm tip over a point on the cartesian plane
 * @param p Pointer to point_t containing the x,y,z coordinates
 * @note The point must be in the range of the two-links inverse kinematics equations
 *       of the arm configuration illustrated in the servo.h file
 * @retval True if all links were moved, false otherwise
 */
bool sv_move(const point_t *p)
{
    float c, s, a; // cos, sin, alpha
    c = (SQR(p->x) + SQR(p->y) - SQR(SV_L1) - SQR(SV_L2)) / (2 * SV_L1 * SV_L2);
    if (fabs(c) > 1.0)
        return false;
    a = atan2(p->y, p->x) - atan2(SV_L2 * (s = sqrt(1 - SQR(c))), SV_L1 + SV_L2 * c);
    if (a <= -PI)
        a += 2 * PI;
    if (!sv_setcnt(BASE, SV_RTOC(a)))
        return false;
    sv_setcnt(TIP, p->z ? SV_MAX_CNT : SV_MIN_CNT);
    return sv_setcnt(MID, SV_RTOC(atan2(s, c)));
}

/**
 * @brief Transmit the control pulses of the servomotors at a ~SV_FREQUENCY rate
 * @note TMR2 Interrupt Subroutine (TF2 not cleared by hardware)
 * @retval None
 */
void sv_isr(void) interrupt TF2_VECTOR
{
    TF2 = 0;
    if (!base_sbit) {
        BRANCH_DELAY(); // Ensure same ON/OFF timing
        BRANCH_DELAY();
        PORT_SV ^= GET_SV_MASK(BASE) | GET_SV_MASK(MID);
        RCAP2H = HIGHBYTE(sv_rcap[TIP]);
        RCAP2L = LOWBYTE(sv_rcap[TIP]);
    }
    else if (!mid_sbit) {
        BRANCH_DELAY();
        PORT_SV ^= GET_SV_MASK(MID) | GET_SV_MASK(TIP);
        RCAP2H = HIGHBYTE(-SV_PERIOD_CNT);
        RCAP2L = LOWBYTE(-SV_PERIOD_CNT);
    }
    else if (!tip_sbit) {
        /* Reset all to fix duty cycle inversion if pins were altered */
        PORT_SV |= GET_SV_MASK(BASE) | GET_SV_MASK(MID) | GET_SV_MASK(TIP);
        RCAP2H = HIGHBYTE(sv_rcap[BASE]);
        RCAP2L = LOWBYTE(sv_rcap[BASE]);
    }
    else {
        PORT_SV ^= GET_SV_MASK(BASE);
        RCAP2H = HIGHBYTE(sv_rcap[MID]);
        RCAP2L = LOWBYTE(sv_rcap[MID]);
    }
}