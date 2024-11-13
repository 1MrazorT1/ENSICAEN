/**
* @file apps/bluewave/include/bluewave.h
* @brief header file for bluetooth speaker application
* @author 
*/
#ifndef _BLUEWAVE_H
#define _BLUEWAVE_H

#include <stdio.h>
#include <bsplib.h>

/* API parameters */
#define SYSTEM_TICK_PERIOD      20000
#define UART_CONSOLE            1
#define TMP_BUFFER_SIZE         77

#define RADIO                   2
#define BLUETOOTH               1
#define AUX                     0
#define MUTE_ON                 1
#define MUTE_OFF                0

/**
 * @brief bluewave environment variables for embedded software application
 */
typedef struct {
    
    enum {
        TASK_INPUTS, 
        TASK_DISPLAY, 
        TASK_BLUETOOTH, 
    } state;            /**< current application state for task scheduling  */
    
    uInt8_t volume;         /**< volume value between 0 and 255 */
    uInt8_t volume_flag;    /**<  boolean flag for outputs processing */

    uInt8_t source;         /**< source selection : 0=AUX 1=BT 2=Radio */
    uInt8_t source_flag;    /**<  boolean flag for outputs processing */

    uInt8_t mute;           /**< mute selection : 0=OFF 1=ON */
    uInt8_t mute_flag;      /**<  boolean flag for outputs processing */
    
    uInt8_t bluetooth_flag; /**<  boolean flag for outputs processing */
    
} bluewave_env;

/* API reference */

 /**
  * @brief hardware system initialization for bluewave application
  */
void system_init(void);

 /**
  * @brief environment variables initialization for bluewave application 
  */
void app_init(bluewave_env *speaker);

 /**
  * @brief application offline scheduler 
  * @warning scheduler called all ticks (20ms) during application life
  */
void app_scheduler(bluewave_env *speaker);

/**
 * @brief TASK - check digital and analog inputs interfaces
 * @warning check for switchs inputs, adc and update analog mux
 */
void task_inputs(bluewave_env *speaker);

/**
 * @brief TASK - update led and display interfaces
 */
void task_display(bluewave_env *speaker);

/**
 * @brief TASK - update bluetooth interface
 */
void task_bluetooth(bluewave_env *speaker);

#endif /* _BLUEWAVE_H */


















