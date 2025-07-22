/**
 ******************************************************************************
 * @file    utils.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   This file contains the common definitions of the application
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UTILS_H
#define UTILS_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "config.h"

/* Public defines ------------------------------------------------------------*/
#define bool  bit
#define true  ((bool)1)
#define false ((bool)0)

#define PLLCON_CD_MASK 0x07U
#define MAX_CORE_CLK   12.582912 // MHz
#define CORE_CLK_FREQ  (MAX_CORE_CLK / (1U << (PLLCON_INIT_VAL & PLLCON_CD_MASK)))
#define OVHEAD_CONST   8.0204 // Loop overhead constant for volatile uint16_t (measured debugging)

/* Public macros -------------------------------------------------------------*/
#define LOWBYTE(A)  ((uint8_t)(A))                    // Only for r-values
#define HIGHBYTE(A) ((uint8_t)(((uint16_t)(A)) >> 8)) // Only for r-values
#define ARR_SIZE(A) (sizeof(A) / sizeof(*(A)))        // Size of array (only within scope of initialization)

#define US_TO_MC(A) ((uint16_t)((A) * CORE_CLK_FREQ / 12 + 0.5)) // uS to machine cycles
#define DELAY_US(A) do {volatile uint16_t i = US_TO_MC((A) / OVHEAD_CONST); for (; i; i--);} while (0)

#define LERP(A,B,C,D,E) (((E)-(D))*((A)-(B))/((C)-(B))+(D)) // Linear interpolation of A from interval [B-C] to [D-E]

#endif // UTILS_H