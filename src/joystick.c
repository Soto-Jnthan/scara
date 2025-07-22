/**
 ******************************************************************************
 * @file    joystick.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Joystick Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "joystick.h"
#include "ads1015.h"

/* Private defines -----------------------------------------------------------*/
#define ADC_X_CONFIG_REG (OS | MUX0 | MODE | PGA1) // ±2.048V AIN0-AIN3
#define ADC_Y_CONFIG_REG (OS | MUX1 | MODE | PGA1) // ±2.048V AIN1-AIN3

/* Private functions' prototypes ---------------------------------------------*/
static i2c_status_t read_adc(uint8_t *pdata);

/**
 * @brief Initialization of the joystick's I2C interface
 * @retval None
 */
void jstk_init(void)
{
    i2c_init();
}

/**
 * @brief Read the values of the two axes of the joystick
 * @param pdata Pointer to jstk_out_t used for data reception
 * @note AIN0-AIN3 and AIN1-AIN3 channels assumed to be connected to the x-axis and y-axis respectively
 * @retval I2C_OK if both ADC readings were successful, I2C_NACK otherwise
 */
i2c_status_t jstk_read(jstk_out_t *pdata)
{
    pdata->x = ADC_X_CONFIG_REG;
    pdata->y = ADC_Y_CONFIG_REG;
    return read_adc(&pdata->x) | read_adc(&pdata->y);
}

/**
 * @brief Read one of the ADCs of the ADS1015 module
 * @param[in] pdata Pointer to data buffer containing CONFIG_REG's value
 * @param[out] pdata Pointer to data buffer containing CONVERSION_REG's value
 * @retval I2C_OK if CONVERSION_REG reading is successful, I2C_NACK otherwise
 */
 static i2c_status_t read_adc(uint8_t *pdata)
{
    i2c_memwrite(ADS1015_I2CADDR, CONFIG_REG, pdata, sizeof(*pdata));
    while (!i2c_memread(ADS1015_I2CADDR, CONFIG_REG, pdata, sizeof(*pdata)) && !(*pdata & OS));
    return i2c_memread(ADS1015_I2CADDR, CONVERSION_REG, pdata, sizeof(*pdata));
}