/*
 * test program for gpio library (switch and led)
 * author 
 */
#include <bsplib.h>
#include <pic18f27k40.h>

void main(void)
{   
    led2_init();
    while(1){
        LATAbits.LATA4 = 1;
        delay_40ms();
        LATAbits.LATA4 = 0;
        delay_40ms();
    }
}
