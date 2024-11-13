/**
 * @file rn52/include/rn52.h
 * @brief header file for RN52 bluetooth module library 
 * @author hugo descoubes - copyleft
 */

/** @ingroup BLUETOOTH */
/* @{ */
/** @defgroup  RN52 */
/** @ingroup RN52 */
/* @{ */
#ifndef _RN52_H
#define _RN52_H

#include <uart1/include/uart1.h>
#include <uart2/include/uart2.h>
#include <common/include/delay.h>
#include <string.h>

/* uncomment to activate UART1 console */
#define CONFIG_UART1_CONSOLE

/* RN52 default command reference */
#define RN52_DEV_NAME           "SN,BlueWave"
#define RN52_NO_CODE            "SA,0"
#define RN52_A2DP_PROFILE       "SK,04"
#define RN52_DISCONNECT         "K,04"
#define RN52_RECONNECT          "B"
#define RN52_PLAY_PAUSE         "AP"
#define RN52_NEXT_TRACK         "AT+"
#define RN52_VOLUME_INC         "AV+"
#define RN52_VOLUME_DEC         "AV-"

/* API reference */

/**
  * @brief RN52 bluetooth module default configuration
  * @li mode : UART interface with GPIO9 pin forced to low
  * @li pins (PIC18-UART2/RN52) : RB1/RST, RB2/PWR_EN, RC0-RX2/TX, RC1-TX2/RX
  * @li uart2 : 9600bps, 8 bits payload, 1 stop bit, no parity
  * @li protocol : A2DP audio profile, no authentification
  * @li init : reconnect last connected device, choose module name
  * @warning connect BT audio click board on J29 curiosity HPC connector and
  * connect RD2 to RB1 and RD3 to RB2 on J27 curiosity HPC connector  
  * @return return TRUE if initialization was performed else return FALSE 
  */
uInt8_t rn52_init(void);

 /**
  * @brief send command to RN52 bluetooth module
  * @param cmd command to send
  * @return return TRUE if command was performed else return FALSE 
  */
uInt8_t rn52_cmd(const uInt8_t *cmd);

#endif /*_RN52_H*/


















