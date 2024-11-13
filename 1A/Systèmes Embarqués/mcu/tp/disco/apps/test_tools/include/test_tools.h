/**
* @brief header file for test tools project
* @author hugo
*/

#ifndef _TEST_TOOLS_H
#define _TEST_TOOLS_H

#include <common/include/pic18fx7k40_config.h>
#include <common/include/delay.h>
#include <timer0/include/timer0.h>
#include <uart1/include/uart1.h>
#include <uart2/include/uart2.h>
#include <gpio/include/gpio.h>
#include <i2c1/include/i2c1.h>
#include <rn52/include/rn52.h>
#include <adc/include/adc.h>
#include <lcd/include/lcd.h>

#define led2_on() LATAbits.LATA4 = 1
#define led3_on() LATAbits.LATA5 = 1
#define led4_on() LATAbits.LATA6 = 1
#define led5_on() LATAbits.LATA7 = 1
#define led2_off() LATAbits.LATA4 = 0
#define led3_off() LATAbits.LATA5 = 0
#define led4_off() LATAbits.LATA6 = 0
#define led5_off() LATAbits.LATA7 = 0
#define switch1_read() !PORTBbits.RB4
#define switch2_read() !PORTCbits.RC5
#define sys_interrupt_enable()  INTCONbits.IPEN = 1;    \
                                INTCONbits.GIEH = 1;    \
                                INTCONbits.GIEL = 1

#endif /* _TEST_TOOLS_H */


















