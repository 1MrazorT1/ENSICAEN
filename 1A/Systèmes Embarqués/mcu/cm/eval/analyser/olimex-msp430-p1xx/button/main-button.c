#include "io430.h"

#define LED_ON                  P6OUT &= ~0x01
#define LED_OFF                 P6OUT |= 0x01

#define But_Check               (P6IN & 0x02)

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P6OUT = 0x01;               // All outputs are low, except P6.0 -> LED
  P6SEL = 0x00;               // Peripheral module function: I/O function is selected.
  P6DIR = 0x01;               // 1 -> Output; 0 -> Input; All inputs, except P6.0 -> LED
  while (1)
  {
     if (But_Check)
        LED_ON;
     else
        LED_OFF;
  }
}
