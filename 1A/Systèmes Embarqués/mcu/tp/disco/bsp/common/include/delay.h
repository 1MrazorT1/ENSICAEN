/**
* @file common/include/delay.h
* @brief header file for pic18 ASM software delay library 
* @author hugo descoubes - copyleft
*/

/** @ingroup DELAY */
/* @{ */
/** @defgroup SOFTWARE_DELAY_64MHz_CPU */
/** @ingroup SOFTWARE_DELAY_64MHz_CPU */
/* @{ */
#ifndef _DELAY_H
#define _DELAY_H

/* API reference */

 /**
  * @brief 10us software delay
  * @warning 10us duration only for 64MHz cpu clock  
  */
void delay_10us(void);

 /**
  * @brief 1ms software delay
  * @warning 1ms duration only for 64MHz cpu clock  
  */
void delay_1ms(void);

 /**
  * @brief 40ms software delay
  * @warning 40ms duration only for 64MHz cpu clock  
  */
void delay_40ms(void);

 /**
  * @brief 200ms software delay
  * @warning 200ms duration only for 64MHz cpu clock  
  */
void delay_200ms(void);

#endif /* _DELAY_H */


















