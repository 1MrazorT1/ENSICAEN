#include "uart.h" 

void InitUART(unsigned int boud)
{

  SCON0_bit.SM1   = 1;        //Set to mode 1 (10-bit asynchronous)
  SCON0_bit.REN   = 1;        //Enable receiver
  SMD0_bit.SMOD   = 1;        //Baud rate = 16 x baud clock
  PR0             = 0x3ef;    //PR0 = 2^21 * 115200 / 20 MHz (crystal)

  SCON0_bit.RI    = 0;        //Clear received character flag
  SCON0_bit.TI    = 0;        //Clear transmit character flag

}
void WriteChar(unsigned char ch)
{
  SBUF0 = ch;
  while (!SCON0_bit.TI);
  SCON0_bit.TI = 0;
}

unsigned char ReadChar(void)
{
  while (!SCON0_bit.RI);
  SCON0_bit.RI = 0;
  return SBUF0;
}

