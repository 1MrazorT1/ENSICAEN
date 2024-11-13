//led.c
#include "led.h"

#define   BIT0        0x00000001
#define   BIT1        0x00000002
#define   BIT2        0x00000004
#define   BIT3        0x00000008
#define   BIT4        0x00000010
#define   BIT5        0x00000020
#define   BIT6        0x00000040
#define   BIT7        0x00000080

//simple delay
void Delay_l(unsigned long a) { while (--a!=0); }

void InitLed(void)
{
  //LCFG -> PCF3 -> 0 -> IO port
  //LCFG -> PCF3 -> 1 -> LCD segment output 
  //PCGF3 is 7 bit in register LCFG
  
  //Set Port3 to I/O port 
  LCFG  |= 0x80;
  
  //Set P3.5 to output
  PD3   |= BIT5;
}

//turn on led
void LedOn(void)
{
  //ON when port is set to 0 
  PO3 &= ~BIT5;
}

//turn off led
void LedOff(void)
{
  //ON when port is set to 1 
  PO3 |= BIT5;
}



