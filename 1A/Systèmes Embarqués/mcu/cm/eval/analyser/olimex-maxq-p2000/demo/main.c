//main.c
// This program test board MAXQ-P2000
//
//  Button test: 
//  button1 -> beep buzzer
//  button2 -> beep buzzer
//
//  RS232 Test:
//  '1' -> Led ON
//  '2' -> Led OFF
//  '3' -> Beep 1
//  '4' -> Beep 2


#include <intrinsics.h>
#include <iomaxq200x.h>

#include "led.h"
#include "buzzer.h"
#include "uart.h"
#include "button.h"


/****** Interupts Functions *******/
void InitUartInterr(void);              //init interupt
void UartInterrupt(unsigned char ch);    //function processing interupt


// serial port/timer 0 module vector
#pragma vector=2   

// define the interrupt handler         
__interrupt void uartReceiveHandler( void )
{
  //temp variable
  unsigned char ch;
  // Clear the Recieve Interrupt Flag
  SCON0_bit.RI = 0;
  // read data value from Serial Data Buffer
  ch = SBUF0;
  //function that processing interupts
  UartInterrupt(ch);
}


int main()
{

  /**** Initialization ****/
  InitLed();        
  InitBuzzer();
  InitButton();
  InitUART(0);
  InitUartInterr();

  //loop forever 
  while(1)
  {
    if((PI3 & 0x40) == 0) Beep_1();  //beep if button1 is pressed
    if((PI3 & 0x80) == 0) Beep_2();  //beep if button2 is pressed 
  }
}



/**** FUNCTIONS ****/
//function, that processing interupt
void UartInterrupt(unsigned char ch)
{
    if(ch == '1') LedOn();    //led on
    if(ch == '2') LedOff();   //led off
    if(ch == '3') Beep_1();   //beep
    if(ch == '4') Beep_2();   //beep
}

//init interrupt
void InitUartInterr(void)
{
  //disable interrupts
  __disable_interrupt();
  // Enable serial port interrupt
  SMD0_bit.ESI = 1;           
  // Serial port 0 reciver enabled
  SCON0_bit.REN = 1;          
  // Activate the interrupt request from module 2 where SMD0 is located
  IMR_bit.IM2 = 1;           
  //enable interupts
  __enable_interrupt();
}
