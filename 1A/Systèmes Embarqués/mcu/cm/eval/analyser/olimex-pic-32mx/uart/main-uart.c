/*********************************************************************
 *
 *                  OLIMEX PIC-32MX UART Basic Example
 *
 *********************************************************************
 *
 * The purpose of this example code is to demonstrate the use of
 * peripheral library macros and functions supporting the PIC32MX
 * UART.
 *
 * Platform: 	Olimex PIC-32MX
 *
 * Features demonstrated:
 *		- UART configuration
 *		- I/O ports configuration
 *
 * Description:
 *		- After reset a 'Hello' message is sent through the UART (RS232) to PC
 *		- When a character is received through RS232 an echo is returned of the character+1 
 *
 * Oscillator Configuration Bit Settings:
 * 		- Oscillator Selection Bits = 	Primary Osc w/PLL (XT+HS+EC+PLL)
 *		- Primary Oscillator Config = 	HS osc mode
 *		- PLL Input Divider			=	2x Divider
 *		- PLL Multiplier			=	18x Multiplier
 *
 **********************************************************************/
#include <plib.h>

// Configuration Bit settings
// SYSCLK = 72 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 36 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
//
#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2

#define SYSCLK			(72000000)

#define DESIRED_BAUDRATE    	(9600)      // The desired BaudRate



int main(void)
{
	int	pbClk;
   unsigned char data;
	int i;

	// STEP1. Configure the device for maximum performance.
	// This macro sets flash wait states, PBCLK divider and DRM wait states based on the specified
	// clock frequency. It also turns on the cache mode if avaialble.
	// We're using the PB clock frequency that was set automatically by this call.
	// Another option is to set the PB divider explicitely and then use a #define for the pbClk value.
	pbClk=SYSTEMConfigPerformance(SYSCLK);


	// STEP2. Open UART2 with Receive and Transmitter enable.
   OpenUART2(UART_EN, UART_RX_ENABLE | UART_TX_ENABLE, pbClk/16/DESIRED_BAUDRATE-1);	
	//UART is On   Enable Rx      Enable Tx         Calculate Baud Rate

	mPORTFClearBits(BIT_1); 		// Turn off RF1 on startup.
	mPORTFSetPinsDigitalOut(BIT_1);	// Make PORTF.RF1 as output.

	i = 512*512;
	while(i) { i--;}	//Time delay

   putsUART2("*** OLIMEX PIC32MX BASIC UART Example ***\r\n");
   putsUART2("*** Type some characters and observe echo ***\r\n");

   while(1)
   {
      while(!DataRdyUART2()); // Wait for data in the UARTRx. 

      data = (char)ReadUART2(); // Read data from Rx. 

      mPORTFToggleBits(BIT_1);	//Toggle the LED

      while(BusyUART2()); // Wait till the UART transmitter is free. 
      putcUART2(data+1); // Write data into Tx. 

   };

   return 0;
}

