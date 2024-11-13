// uart.c

#include "uart.h"
#include <AnalogDevices/ioaduc7026.h>

#define TEMT  0x40
#define THRE  0x20
#define	DR    0x01

// init uart interface
void InitUart(void) {

  // Setup tx & rx pins on P1.0 and P1.1
  GP1CON = 0x011;

  // Start setting up UART at 9600bps
  COMCON0 = 0x080;				// Setting DLAB
  COMDIV0 = 0x023;				// Setting DIV0 and DIV1 to DL calculated (9600/11.2MHz)
  COMDIV1 = 0x000;
  COMCON0 = 0x003;				// Clearing DLAB
}

// Send char via uart
void WriteChar(unsigned char ch) {
  while ((COMSTA0 & TEMT) == 0);
  COMTX=ch;	
}

// Receive char from uart
unsigned char ReadChar(void) {
  while ((COMSTA0 & DR) == 0);
  return COMRX;
}

// Receive char from uart non stop
unsigned char ReadChar_nonstop(void) {
  if(COMSTA0 & DR)
    return COMRX;
  else
    return 0;
}

// Send text via uart
void WriteText(unsigned char *txt) {
  for(; *txt; txt++)
      WriteChar(*txt);
}

