/*
 * test program for all needed tools
 * author hugo
 */

#include "../include/test_tools.h"

void __interrupt(low_priority) isr_low (void)
{
    uart1_isr_process ();  
    uart2_isr_process ();    				
}

void main(void)
{
    uInt8_t conv_data;
    
    /* system init */
    switch1_init();
    switch2_init();
    led2_init();
    led3_init();
    led4_init();
    led5_init();    
    uart1_init(UART1_BAUD_RATE);
    uart2_init(UART2_BAUD_RATE);
    adc_init();     
    sys_interrupt_enable();    

    /* application init */    
    led2_off();
    led3_off();
    led4_off();
    led5_off();  
    
    /* test UART1 and UART2 outputs */
    uart1_puts("\r\nWelcome to UART1 output TEST\n\r");
    uart2_puts("\r\nWelcome to UART2 output TEST\n\r");    
    
     /* test delays and LEDs */
    for (char i=0; i<3; i++) {
        led5_off();
        led2_on();
        delay_200ms();
        led2_off();
        led3_on();
        delay_200ms();
        led3_off();
        led4_on();
        delay_200ms();  
        led4_off();
        led5_on();
        delay_200ms();    
    }

    /* test switch 1 and 2, LEDs and ADC */
    while (1) {

        if (switch1_read()) {
            led2_on();
            led3_on();
            led4_on();
            led5_on();           
            
        } else if (switch2_read()){
            led2_off();
            led3_off();
            led4_off();
            led5_off();  
            
        } else {  
            conv_data = adc_read();
            LATA = (uInt8_t) (conv_data & 0xF0);          
            
        }
    }       
}
