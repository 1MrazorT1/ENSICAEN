/*********************************************************************
 *
 *********************************************************************
 *     		    OLIMEX PIC-32MX PORT API EXAMPLE
 *********************************************************************
 *
 *
 * The purpose of this example code is to demonstrate the PIC32MX
 * peripheral library macros and functions supporting IOPORT
 * module and its various features.
 *
 * Platform: 	Olimex PIC-32MX
 *
 * Features demonstrated:
 *      - Port pin configurations
 *      - Output pin toggle
 *
 * Description:
 *		- This example blinks LED (PORTF.RF1) when button on PORTD.RD8
 *  	is pressed
 *
 * Oscillator Configuration Bit Settings:
 * 		- Oscillator Selection Bits = 	Primary Osc w/PLL (XT+HS+EC+PLL)
 *		- Primary Oscillator Config = 	HS osc mode
 *		- PLL Input Divider			=	2x Divider
 *		- PLL Multiplier			=	18x Multiplier
 *
 ********************************************************************/
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


#define FOSC			72E6


int main(void)
{
    unsigned int temp;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //STEP 1. Configure cache, wait states and peripheral bus clock
	// Configure the device for maximum performance.
	// This macro sets flash wait states, PBCLK divider and DRM wait states based on the specified
	// clock frequency. It also turns on the cache mode if avaialble.
	// Based on the current frequency, the PBCLK divider will be set at 1:2. This knoweldge
	// is required to correctly set UART baud rate, timer reload value and other time sensitive
	// setting.

	SYSTEMConfigPerformance(FOSC);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 2. Configure the port registers
    PORTSetPinsDigitalOut(IOPORT_F, BIT_1);
    PORTSetPinsDigitalIn(IOPORT_D, BIT_8);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 3. Initialize the port pin states 
    mPORTFClearBits(BIT_1);



   while(1)
   {
 	  	while(mPORTDRead() & 0x0100);		// Wait until button pushed

		while(!(mPORTDRead() & 0x0100));	// Wait until button released

		mPORTFToggleBits(BIT_1);			// Toggle port
   };

}

