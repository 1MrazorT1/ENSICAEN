// This program is designed for ADUC_P7026 board
#include <AnalogDevices/ioaduc7026.h>
#include "system.h"


int main()
{
  // Init frequency
  InitFreq();

  // Init Leds
  InitLeds();

  // loop forever
  while(1) {

    // check buttons
    if(!(GP0DAT&0x10))
      LED1_ON;
    else
      LED1_OFF;

    if(!(GP0DAT&0x20))
      LED2_ON;
    else
      LED2_OFF;

  }

}
