/**
 ******************************************************************************
 * @file    accel.c
 * @author  J.Soto
 * @version V1.2.0
 * @date    Nov 11th, 2023
 * @brief   Accelerometer Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "accel.h"

/**
 * @brief Initialize the accelerometer of the LSM6DS33
 * @retval I2C_ACK if connection established, I2C_NACK otherwise
 */
i2c_status_t xlda_init(void)
{
    static const uint8_t val = ODR_XL2; // Power-on accelerometer
    i2c_init();
    return i2c_memwrite(LSM6DS_I2CADDR, CTRL1_XL, &val, sizeof(val)); 
}

/**
 * @brief Read the value of the three axes of the accelerometer
 * @param pdata Pointer to data buffer (size of at least ACCEL_REGS bytes)
 * @retval I2C_ACK if connection established, I2C_NACK otherwise
 */
i2c_status_t xlda_read(int8_t pdata[static ACCEL_REGS])
{
    while (!i2c_memread(LSM6DS_I2CADDR, STATUS_REG, pdata, 1) && !(*pdata & SR_XLDA));
    return i2c_memread(LSM6DS_I2CADDR, OUTX_L_XL, pdata, sizeof(*pdata) * ACCEL_REGS);
}