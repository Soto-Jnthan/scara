/**
 ******************************************************************************
 * @file    joystick.c
 * @author  J.Soto
 * @version V1.3.0
 * @date    July 11th, 2025
 * @brief   Joystick Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "joystick.h"
#include "ads1015.h"

/* Public defines ------------------------------------------------------------*/
#define ADC_X_CONFIG_REG ((uint8_t)(OS | MUX2 | MUX0 | MODE))
#define ADC_Y_CONFIG_REG ((uint8_t)(OS | MUX2 | MODE))

/* Private functions' prototypes ---------------------------------------------*/
static i2c_status_t read_adc(uint8_t *pdata);

/**
 * @brief Initialization of the I2C interface of the joystick
 * @retval None
 */
void jstk_init(void)
{
    i2c_init();
}

/**
 * @brief Read the values of the two axes of the joystick
 * @param pdata Pointer to data buffer (size of at least ADC_REGS bytes)
 * @retval I2C_OK if both ADC readings were successfuly, I2C_NACK otherwise
 */
i2c_status_t jstk_read(uint8_t pdata[static ADC_REGS])
{
    pdata[X_AXIS] = ADC_X_CONFIG_REG;
    pdata[Y_AXIS] = ADC_Y_CONFIG_REG;
    return read_adc(&pdata[X_AXIS]) || read_adc(&pdata[Y_AXIS]);
}

/**
 * @brief Read one of the ADCs of the ADS1015 module
 * @param pdata Pointer to data buffer that contains at entry CONFIG_REG's value and CONVERSION_REG at exit
 * @retval I2C_OK if CONVERSION_REG reading is successfuly, I2C_NACK otherwise
 */
static i2c_status_t read_adc(uint8_t *pdata)
{
    i2c_memwrite(ADS1015_I2CADDR, CONFIG_REG, pdata, sizeof(*pdata));
    while (!i2c_memread(ADS1015_I2CADDR, CONFIG_REG, pdata, sizeof(*pdata)) && !(*pdata & OS));
    return i2c_memread(ADS1015_I2CADDR, CONVERSION_REG, pdata, sizeof(*pdata));
}