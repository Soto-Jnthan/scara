/**
 ******************************************************************************
 * @file    servo.h
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Header for servo.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SERVO_H
#define SERVO_H

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "utils.h"

/* Public defines ------------------------------------------------------------*/
#define MAX_ANGLE     PI  // Rad
#define MIN_ANGLE     0.0 // Rad

#define SV_MIN_CNT    US_TO_MC(SV_MIN_US_PULSE)
#define SV_MAX_CNT    US_TO_MC(SV_MAX_US_PULSE)
#define SV_MID_CNT    US_TO_MC((SV_MAX_US_PULSE + SV_MIN_US_PULSE) / 2.0)
#define SV_PERIOD_CNT (US_TO_MC(1e6 / SV_FREQUENCY) - 2 * SV_MID_CNT)

#define SV_MIN_EXCT   (SV_MIN_US_PULSE * CORE_CLK_FREQ / 12)
#define SV_MAX_EXCT   (SV_MAX_US_PULSE * CORE_CLK_FREQ / 12)

/* Public macros --------------------------------------------------------------*/
#define SV_RTOC(A) ((uint16_t)(LERP(A, MIN_ANGLE, MAX_ANGLE, SV_MIN_EXCT, SV_MAX_EXCT) + 0.5))

/* Public typedefs/enums ------------------------------------------------------*/
typedef enum {BASE, MID, TIP} servo_t;
struct point {float x; float y; _Bool z;};

/* Public functions' prototypes -----------------------------------------------*/
void sv_init(void);
bool sv_setcnt(servo_t sv, uint16_t cnt);
bool sv_move(const struct point *p);
void sv_isr(void) __interrupt(TF2_VECTOR) __naked;

/** ASSUMED ARM CONFIGURATION FOR ANGLE CALCULATIONS **/
/** WHERE SV_MIN_US_PULSE EQUALS 0 AS MEASURED BELOW **/
/**                                                  **/
/**                                 2                **/
/**                                2   SV2's angle   **/
/**                               2 \\     *         **/
/**                              2   \\*             **/
/**                             2  *                 **/
/**                            1                     **/
/**                        1                         **/
/**                    1                             **/
/**                1                                 **/
/**            1                                     **/
/**        1 \\                                      **/
/**    1       \\ SV1's angle                        **/
/**1__________\\_____________________________________**/
/**   https://www.desmos.com/calculator/3ebmf7hpk8   **/

#endif // SERVO_H