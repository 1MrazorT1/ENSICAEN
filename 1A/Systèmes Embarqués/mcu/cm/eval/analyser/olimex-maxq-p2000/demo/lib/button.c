//button.c
#include "button.h"

#define   BIT0        0x00000001
#define   BIT1        0x00000002
#define   BIT2        0x00000004
#define   BIT3        0x00000008
#define   BIT4        0x00000010
#define   BIT5        0x00000020
#define   BIT6        0x00000040
#define   BIT7        0x00000080


void InitButton(void)
{
  //LCFG -> PCF3 -> 0 -> IO port
  //LCFG -> PCF3 -> 1 -> LCD segment output 
  //PCGF3 is 7 bit in register LCFG
  
  //Set Port3 to I/O port 
  LCFG  |= 0x80;

  //Set button1(P3.6) and button2 (P3.7) to input 
  PD3   |= ~BIT6;
  PD3   |= ~BIT7;
} 

