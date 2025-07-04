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
    return i2c_memwrite(LSM6DS_I2CADDR, CTRL1_XL, &val, 1); 
}

/**
 * @brief Read the value of one of the three axes of the accelerometer
 * @note Undefined value returned if I2C connection is lost
 * @param in Axis to be read via xlda_input enum
 * @retval Readout from the accelerometer
 */
int8_t xlda_read(xlda_input_t in)
{
    int8_t readout;
    while (!i2c_memread(LSM6DS_I2CADDR, STATUS_REG, &readout, 1) && !(readout & SR_XLDA));
    i2c_memread(LSM6DS_I2CADDR, in, &readout, 1);
    return readout;
}