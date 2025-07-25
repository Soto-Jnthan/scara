/**
 ******************************************************************************
 * @file    i2c.h
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Header for i2c.c file
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef I2C_H
#define I2C_H

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Public defines ------------------------------------------------------------*/
#define BYTE_MSB_MASK 0x80U

/* Public typedefs/enums -----------------------------------------------------*/
typedef bool i2c_status_t;
enum {I2C_ACK, I2C_NACK};

/* Public functions' prototypes ----------------------------------------------*/
void i2c_init(void);
i2c_status_t i2c_memwrite(uint8_t devaddr, uint8_t memaddr, const uint8_t *pdata, uint8_t datalen);
i2c_status_t i2c_memread(uint8_t devaddr, uint8_t memaddr, uint8_t *pdata, uint8_t datalen);

/* Public inline functions' definitions --------------------------------------*/

inline i2c_status_t i2c_write(uint8_t devaddr, const uint8_t *pdata, uint8_t datalen)
{
    return i2c_memwrite(devaddr | BYTE_MSB_MASK, 0, pdata, datalen);
}

inline i2c_status_t i2c_read(uint8_t devaddr, uint8_t *pdata, uint8_t datalen)
{
    return i2c_memread(devaddr | BYTE_MSB_MASK, 0, pdata, datalen);
}

#endif // I2C_H