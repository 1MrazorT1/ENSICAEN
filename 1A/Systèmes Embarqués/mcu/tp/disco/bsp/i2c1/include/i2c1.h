/**
 * @file i2c1/include/i2c1.h
 * @brief header file for I2C1 library 
 * @author hugo descoubes - copyleft
 */

/** @ingroup I2C */
/* @{ */
/** @defgroup  I2C1 */
/** @ingroup I2C1 */
/* @{ */
#ifndef _I2C1_H
#define _I2C1_H

#include <common/include/common.h>

/* API parameters */
#define I2C1_ADD        0x42
#define I2C1_BAUDRATE   100000

/* API reference */

/**
 * @brief i2c1 configuration
 * @li mode : I2C master, no collision
 * @li pins : SDA input/output connected to RC4
 * SCL input/output connected to RC3
 * @li protocol : 7 bits address, write only, 8 bits data payload
 * @li misc : slew rate disable, SMBus disable 
 * @li enable : enable module
 * @warning connect two 4,7K pull-up resistors to RC3 and RC4 pins on J8 and
 * J11 curiosity HPC expansion connectors 
 */
void i2c1_init(uInt32_t bdrate);

/**
 * @brief send 8 bits command and 8 bits data to an I2C slave device
 * @param add 7 bits device address
 * @param cmd 8bits command to send
 * @param payload 8bits payload to send
 * @return return TRUE if sequence has been transmitted else return FALSE 
 */
uInt8_t i2c1_write(uInt8_t add, uInt8_t cmd, uInt8_t payload);

/**
 * @brief wait for the end of I2C idle state
 */
#define i2c1_idle()

/**
 * @brief send start bit and wait the end of start bit transmission
 */
#define i2c1_start()

/**
 * @brief send 8 bits data and wait the end of transmission
 */
#define i2c1_send(value)

/**
  * @brief check for slave acknowledgment
  */
#define i2c1_ack()

/**
  * @brief send stop bit and wait the end of stop bit transmission
  */
#define i2c1_stop()

#endif /*_I2C1_H*/


















