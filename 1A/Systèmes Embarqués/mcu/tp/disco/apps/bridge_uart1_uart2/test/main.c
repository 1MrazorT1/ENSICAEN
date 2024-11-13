/*
 * test program for uart1 library
 * author hugo
 */

#include <bsplib.h>

void __interrupt(high_priority) isr_high (void)
{ 
    /* high ISR processing */					
}


void __interrupt(low_priority) isr_low (void)
{
    uart1_isr_process ();  
    uart2_isr_process ();    				
}


void main(void)
{
    uInt8_t payload;
    
    /* system init*/
    uart1_init(UART1_BAUD_RATE);
    uart2_init(UART2_BAUD_RATE);
    sys_interrupt_enable();
   
    /* bridge uart1 to uart2 */ 
    uart1_puts("\r\nWelcome to UART1\n\r");
    uart2_puts("\r\nWelcome to UART2\n\r");
    
    while (1) {
        
        if(uart1_getc(&payload, UART1_ECHO)){
          
            if (payload == '\r') {
                uart1_putc('\n');
                uart2_putc('\n');
                uart2_putc(payload);
            } else {
                uart2_putc(payload);
            }    
          
        } else if(uart2_getc(&payload, UART2_ECHO)){

            if (payload == '\r') {
                uart2_putc('\n');                
                uart1_putc('\n');
                uart1_putc(payload);
            } else {
                uart1_putc(payload);
            }              
            
        } 
    }       
}
