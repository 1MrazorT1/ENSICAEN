/*
 * gpio/src/led_init.c
 * led's pins initializations 
 * author 
 */

#include <gpio/include/gpio.h>
#include <xc.h>

void led2_init(void)
{
    TRISAbits.TRISA4 = 0;
}  

void led3_init(void)
{
    TRISAbits.TRISA5 = 0;
} 

void led4_init(void)
{
    TRISAbits.TRISA6 = 0;
} 

void led5_init(void)
{
    TRISAbits.TRISA7 = 0;
}

int switch1_read(void){
    if(PORTBbits.RB4 == 1){
        return 0;
    }else{
        return 1;
    }
}

int switch2_read(void){
    if(PORTCbits.RC5 == 1){
        return 0;
    }else{
        return 1;
    }
}