/**
 * @file timer0/include/timer0.h
 * @brief header file for TIMER0 library 
 * @author hugo descoubes - copyleft
 */

/** @ingroup TIMER */
/* @{ */
/** @defgroup  TIMER0 */
/** @ingroup TIMER0 */
/* @{ */
#ifndef _TIMER0_H
#define _TIMER0_H

#include <common/include/common.h>

/* API parameters */
#define TIMER0_PERIOD   20000     /* 20ms period example */
      
/* API reference */

 /**
  * @brief timer0 configuration
  * @li source : Fosc/4 (16MHz)
  * @li mode : 16 bits asynchronous
  * @li prescaler : prescale 1:16 and postcale 1:1
  * @li sleep : active on sleep mode
  * @li interrupt : interrupt enable with high priority ISR 
  * @li enable : timer enable by default
  * @warning reference counting period 1us (only for Fosc = HFINTOSC 64MHz) 
  * @param count number of reference cycles to count. range [0-65535]
  */
void timer0_init(uInt16_t count);

 /**
  * @brief timer 0 reload value
  * @warning reference counting period 1us (only for HFINTOSC 64MHz CPU clock) 
  * @param count number of reference cycles to count. range [0-65535]
  */
void timer0_reload(uInt16_t count);

 /**
  * @brief enable timer 0 module
  */
#define timer0_start() T0CON0bits.T0EN = 1

 /**
  * @brief disable timer 0 module
  */
#define timer0_stop() T0CON0bits.T0EN = 0

#endif /* _TIMER0_H */


















