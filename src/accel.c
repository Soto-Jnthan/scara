/**
 ******************************************************************************
 * @file    accel.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Accelerometer Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "accel.h"
#include "lsm6ds33.h"

/**
 * @brief Initialize the accelerometer of the LSM6DS33
 * @param ctrl Pointer to xlda_ctrl_t containing CTRL_X values
 * @retval I2C_ACK if connection established, I2C_NACK otherwise
 */
i2c_status_t xlda_init(const xlda_ctrl_t *ctrl)
{
    i2c_init();
    return i2c_memwrite(LSM6DS_I2CADDR, CTRL1_XL, (uint8_t *)ctrl, sizeof(*ctrl));
}

/**
 * @brief Read the value of the three axes of the accelerometer
 * @param pdata Pointer to xlda_out_t used for data reception
 * @retval I2C_ACK if connection established, I2C_NACK otherwise
 */
i2c_status_t xlda_read(xlda_out_t *pdata)
{
    while (!i2c_memread(LSM6DS_I2CADDR, STATUS_REG, (uint8_t *)pdata, sizeof(uint8_t)) &&
           !(*(uint8_t *)pdata & SR_XLDA));
    return i2c_memread(LSM6DS_I2CADDR, OUTX_L_XL, (uint8_t *)pdata, sizeof(*pdata));
}