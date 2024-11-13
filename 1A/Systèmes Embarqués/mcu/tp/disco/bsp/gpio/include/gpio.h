/**
* @file gpio/include/gpio.h
* @brief header file for gpio library (switch and led)
* @author 
*/

/** @ingroup GPIO */
/* @{ */
/** @defgroup  SWITCH_AND_LED */
/** @ingroup SWITCH_AND_LED */
/* @{ */
#ifndef _GPIO_H
#define _GPIO_H

#include <common/include/common.h>

/* API reference */
 
 /**
  * @brief LED D2 pin initialization 
  */
void led2_init(void);
 
 /**
  * @brief LED D3 pin initialization 
  */
void led3_init(void);
 
 /**
  * @brief LED D4 pin initialization 
  */
void led4_init(void);
 
 /**
  * @brief LED D5 pin initialization 
  */
void led5_init(void);

 /**
  * @brief turn on LED D2
  */
#define led2_on() 

 /**
  * @brief turn on LED D3
  */
#define led3_on() 

 /**
  * @brief turn on LED D4
  */
#define led4_on() 

 /**
  * @brief turn on LED D5 
  */
#define led5_on() 

 /**
  * @brief turn off LED D2
  */
#define led2_off() 

 /**
  * @brief turn off LED D3
  */
#define led3_off() 

 /**
  * @brief turn off LED D4
  */
#define led4_off() 

 /**
  * @brief turn off LED D5 
  */
#define led5_off() 


 /**
  * @brief push button switch S1 pin initialization 
  */
void switch1_init(void);

 /**
  * @brief push button switch S2 pin initialization 
  */
void switch2_init(void);

 /**
  * @brief push button switch S1 read state 
  */
int switch1_read(void);

 /**
  * @brief push button switch S2 read state  
  */
int switch2_read(void);

#endif /* _GPIO_H */
