// This program is designed for ADUC_P7026 board
#include <AnalogDevices/ioaduc7026.h>
#include "system.h"
#include "uart.h"

unsigned char ch = 0;

int main()
{
  // Init frequency
  InitFreq();

  // Init UART
  InitUart();

  // loop forever
  while(1) {

    // echo for uart
    ch = ReadChar_nonstop();
    if(ch) {
      WriteChar(ch);
      WriteChar('*');
    }

  }

}
