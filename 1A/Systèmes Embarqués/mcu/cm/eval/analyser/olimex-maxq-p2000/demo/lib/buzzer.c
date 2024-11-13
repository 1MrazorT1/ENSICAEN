//buzzer.c
#include "buzzer.h"

#define   BIT0        0x00000001
#define   BIT1        0x00000002
#define   BIT2        0x00000004
#define   BIT3        0x00000008
#define   BIT4        0x00000010
#define   BIT5        0x00000020
#define   BIT6        0x00000040
#define   BIT7        0x00000080

//delay ~ simple
void Delay_b(unsigned long a) { while (--a!=0); }

void InitBuzzer(void)
{
   //set port P6.0 to output  
  PD6 |= BIT0;
  PD6 |= BIT1;
}

//beep with tonality 1 
void Beep_1(void)
{
  int i;
  for(i=0; i<50; i++)
  {
    //to beep buzzer, must shake port P6.0

    P06 |= BIT0;        //buzzer port P6.0 to 1
    P06 &= ~BIT1;       //buzzer port P6.1 to 0
    Delay_b(5000);
    P06 &= ~BIT0;       //buzzer port P6.0 to 0
    P06 |= BIT1;        //buzzer port P6.1 to 1
    Delay_b(5000);
  }
}

//beep with tonality 2
void Beep_2(void)
{
  int i;
  for(i=0; i<50; i++)
  {
    //to beep buzzer, must shake port P6.0

    P06 |= BIT0;        //buzzer port P6.0 to 1
    P06 &= ~BIT1;       //buzzer port P6.1 to 0
    Delay_b(2500);
    P06 &= ~BIT0;       //buzzer port P6.0 to 0
    P06 |= BIT1;        //buzzer port P6.1 to 1
    Delay_b(2500);
  }
}



