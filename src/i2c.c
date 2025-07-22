/**
 ******************************************************************************
 * @file    i2c.c
 * @author  J.Soto
 * @version V1.3.1
 * @date    July 19th, 2025
 * @brief   Inter-Integrated Circuit (I2C) Driver Software
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* Private defines -----------------------------------------------------------*/
#define BYTE_BIT 8

/* Private macros -------------------------------------------------------------*/
#define I2C_WR(ADDR) ((ADDR) << 1)
#define I2C_RD(ADDR) (((ADDR) << 1) | 1U)

/* Private inline functions' definitions ---------------------------------------*/
inline void i2c_delay(void) {NOP(); NOP(); NOP(); NOP();} // Depends on I2C mode and core frequency

/* Private functions' prototypes -----------------------------------------------*/
static void i2c_start(void);
static void i2c_stop(void);
static i2c_status_t i2c_sendbyte(uint8_t byte);
static uint8_t i2c_receivebyte(i2c_status_t reply_bit);

/**
 * @brief Initialization of the I2C interface
 * @note The I2C and SPI modules may only be used one at a time
 * @retval None
 */
void i2c_init(void)
{
    SDA = 1; // Set to IDLE state
    SCL = 1;
}

/**
 * @brief  Write an amount of data starting from a memory address of the slave device
 * @param  devaddr Target 7-bit I2C device address
 * @param  memaddr Internal memory address
 * @param  pdata Pointer to data buffer
 * @param  datalen Amount of data in bytes to be sent
 * @note   Set devaddr's MSB to ignore memaddr and write data directly to device
 * @retval I2C_ACK if successful, I2C_NACK otherwise
 */
i2c_status_t i2c_memwrite(uint8_t devaddr, uint8_t memaddr, const uint8_t *pdata, uint8_t datalen)
{
    i2c_start();
    if (!i2c_sendbyte(I2C_WR(devaddr)) && (devaddr & BYTE_MSB_MASK || !i2c_sendbyte(memaddr)))
        for (; datalen && !i2c_sendbyte(*pdata++); datalen--);
    i2c_stop();
    return datalen;
}

/**
 * @brief  Read an amount of data starting from a memory address of the slave device
 * @param  devaddr Target 7-bit I2C device address
 * @param  memaddr Internal memory address
 * @param  pdata Pointer to data buffer
 * @param  datalen Amount of data in bytes to be read
 * @note   Set devaddr's MSB to ignore memaddr and read data directly from device
 * @retval I2C_ACK if successful, I2C_NACK otherwise
 */
i2c_status_t i2c_memread(uint8_t devaddr, uint8_t memaddr, uint8_t *pdata, uint8_t datalen)
{
    i2c_start();
    if (!(devaddr & BYTE_MSB_MASK)) {
        if (i2c_sendbyte(I2C_WR(devaddr)) || i2c_sendbyte(memaddr))
            goto clean_up;
        i2c_start(); // Repeated start
    }
    if (!i2c_sendbyte(I2C_RD(devaddr)))
        for (; datalen; datalen--)
            *pdata++ = i2c_receivebyte(datalen == 1); // End w/NACK
  clean_up:
    i2c_stop();
    return datalen;
}

/**
 * @brief Execute the "Start" sequence of the I2C protocol
 * @retval None
 */
static void i2c_start(void)
{
    SCL = 0;
    SDA = 1;
    i2c_delay();
    SCL = 1;
    i2c_delay();
    SDA = 0;
    i2c_delay();
}

/**
 * @brief Execute the "Stop" sequence of the I2C protocol
 * @retval None
 */
static void i2c_stop(void)
{
    SCL = 0;
    SDA = 0;
    SCL = 1;
    i2c_delay();
    SDA = 1;
}

/**
 * @brief  Send a byte bit-by-bit over the I2C interface
 * @param  byte Payload to be sent
 * @retval ACK/NACK read from the I2C interface after last data bit
 */
static i2c_status_t i2c_sendbyte(uint8_t byte)
{
    uint8_t bit_mask = BYTE_MSB_MASK;
    do {
        SCL = 0;
        SDA = byte & bit_mask;
        i2c_delay();
        SCL = 1;
    } while (bit_mask >>= 1);
    SCL = 0;
    SDA = 1;
    SCL = 1;
    return SDA;
}

/**
 * @brief  Read a byte bit-by-bit over the I2C interface
 * @param  reply_bit Reply bit to be sent after last data bit
 * @retval Byte read from the I2C interface
 */
static uint8_t i2c_receivebyte(i2c_status_t reply_bit)
{
    uint8_t byte = 0x00;
    uint8_t bit_cnt = BYTE_BIT;
    SCL = 0;
    SDA = 1;
    do {
        i2c_delay();
        SCL = 1;
        byte = (byte << 1) | SDA;
        SCL = 0;
    } while (--bit_cnt);
    SDA = reply_bit;
    SCL = 1;
    return byte;
}