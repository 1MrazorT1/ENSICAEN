/**
 * @file uart1/include/uart1.h
 * @brief header file for UART1 library 
 * @author hugo descoubes - copyleft
 */

/** @ingroup UART */
/* @{ */
/** @defgroup  UART1 */
/** @ingroup UART1 */
/* @{ */
#ifndef _UART1_H
#define _UART1_H

#include <common/include/common.h>

/* API parameters */
#define UART1_BAUD_RATE         9600
#define UART1_CIRC_BUFF_SIZE    20   // warning - 6 elements minimum
#define UART1_ECHO              1
#define UART1_ECHO_OFF          0

/**
 * @brief circular buffer object 
 */
typedef struct {
    uInt8_t buffer[UART1_CIRC_BUFF_SIZE]; /**< circular buffer */
    uInt8_t idx_read;       /**< writer index modulo the size of buffer */
    uInt8_t idx_write;      /**< reader index modulo the size of buffer */
    uInt8_t nb_elt;         /**< current number of elements inside the buffer */
} circ_buffer_t;

/* API reference */

 /**
  * @brief uart1 ISR processing
  * @warning always call this function in application inside low priority ISR
  */
extern void uart1_isr_process (void); 

 /**
  * @brief uart1 configuration
  * @li mode : asynchronous
  * @li pins : RX1 input connected to RC7, TX1 output connected to RC6
  * @li protocol : 8 bits payload, 1 stop bit, no error detection (no parity)
  * @li baud rate : 16 bits mode, hight speed mode   
  * @li interrupt : enable only for receiving with low priority ISR 
  * @li enable : enable receiver, transmitter and module
  * @warning connect USB UART click board on J28 curiosity HPC connector 
  * @param bdrate communication baud rate in decimal value
  */
void uart1_init(uInt32_t bdrate);

 /**
  * @brief one byte payload sending
  * @warning sending by polling 
  * @param payload 8 bits payload to send
  */
void uart1_putc(uInt8_t payload);

 /**
  * @brief send caracters string 
  * @warning sending by polling 
  * @param str pointer to a caracters string 
  */
void uart1_puts(const uInt8_t *str);

 /**
  * @brief one byte payload receiving
  * @warning receiving by low level priority interrupt 
  * with circular buffer and software flow control XON/XOFF 
  * @param payload pointer to receiving data buffer
  * @param echo enable (1) or disable (0) application data echo
  * @return TRUE (1) if payload has been received, else return FALSE (0)
  */
uInt8_t uart1_getc(uInt8_t *payload, uInt8_t echo);

 /**
  * @brief caracters string receiving
  * @warning receiving by low level priority interrupt 
  * with circular buffer and software flow control XON/XOFF 
  * @param rx_buf pointer to receiving buffer
  * @param buf_limit application buffer size to avoid overflowing
  * @param echo enable (1) or disable (0) application data echo
  * @return TRUE (1) if caracter string was successfully built, 
  * else return FALSE (0)
  */
uInt8_t uart1_gets(uInt8_t *rx_buf, uInt8_t buf_limit, uInt8_t echo);

 /**
  * @brief waiting the end of current payload sending
  * @return return TRUE (1) if module is busy, else return FALSE (0) 
  */
#define uart1_tx_busy()

 /**
  * @brief wait for data receiving
  * @return return TRUE (!=0) if data has arrived, else return FALSE (0)
  */
#define uart1_rx_ready()

#endif /*_UART1_H*/


















