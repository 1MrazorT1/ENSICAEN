//system.c
#include "system.h"
#include <AnalogDevices/ioaduc7026.h>

// Init Frequency
void InitFreq(void) {
  POWKEY1 = 0x01;
  POWCON = 0x02;         //11.272MHz
  POWKEY2 = 0xF4;
}

// Init Led
void InitLeds(void) {

  // P4.0 and P4.1 as output
  GP4DAT = 0x03000000;

}
