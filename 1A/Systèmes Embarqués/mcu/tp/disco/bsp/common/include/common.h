/**
* @file common/include/common.h
* @brief generic header file for BSP and application
* @author hugo descoubes - copyleft
*/
#ifndef _COMMON_H
#define _COMMON_H

#include <pic18.h>

typedef char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef unsigned char uInt8_t;
typedef unsigned short uInt16_t;
typedef unsigned long uInt32_t;

/* misc parameters */
#define CPU_FREQ_HZ     64000000
#define CPU_CYCLE_HZ    CPU_FREQ_HZ / 4
#define TRUE            1
#define FALSE           0
#define ON              1
#define OFF             0
#define HIGH            1
#define LOW             0
#define SET             1
#define CLEAR           0
#define DONT_CARE       0

/* system API reference */

 /**
  * @brief global interrupt enable
  * @warning global interrupt enable for low and high priority in priority mode  
  */
#define sys_interrupt_enable()  INTCONbits.IPEN = 1;    \
                                INTCONbits.GIEH = 1;    \
                                INTCONbits.GIEL = 1

 /**
  * @brief global interrupt disable
  * @warning global interrupt disable for high interrupt priority only  
  */
#define sys_interrupt_disable()  INTCONbits.GIEH = 0 

 /**
  * @brief application software reset  
  */
#define reset() asm(" reset")

 /**
  * @brief processor sleep mode 
  */
#define sleep() asm("sleep")

 /**
  * @brief watchdog management
  * @warning watchdog is active during sleep mode 
  */
#define watchdog_enable()    WDTCON0bits.SEN = 1
#define watchdog_disable()   WDTCON0bits.SEN = 0
#define watchdog_clear()     asm("clrwdt")

#endif /*_COMMON_H*/


















