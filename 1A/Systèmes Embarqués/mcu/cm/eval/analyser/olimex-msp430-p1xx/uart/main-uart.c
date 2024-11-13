#include "io430.h"
#ifdef  MSP430_1XX
#include "uart0.h"
#else //MSP430_2XX
#include "usart.h"
#endif

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  InitUART0 ();

  UART0SendTxt("\r\nhttps://www.olimex.com/");
  UART0SendTxt("\r\nPress any key to return echo (next ASCII symbol)\r\n");
  while (1);
}
