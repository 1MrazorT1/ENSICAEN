/*********************************************************************
 *
 *********************************************************************
 *		 OLIMEX PIC-32MX TIMER1 EXAMPLE
 *********************************************************************
 *
 *
 * The purpose of this example code is to demonstrate the use of
 * peripheral library macros and functions supporting the PIC32MX
 * General Purpose Timer1.
 *
 * Platform: 	Olimex PIC-32MX
 *
 * Features demonstrated:
 *      - Timer configuration
 *      - Interrupt configuration
 *      - ISR syntax
 *
 * Description:
 * 		- This example toggles PORTF.RD1 once every two second
 *
 * Oscillator Configuration Bit Settings:
 * 		- Oscillator Selection Bits = 	Primary Osc w/PLL (XT+HS+EC+PLL)
 *		- Primary Oscillator Config = 	HS osc mode
 *		- PLL Input Divider			=	2x Divider
 *		- PLL Multiplier			=	18x Multiplier
 *
 * Notes:
 *		- Timer1 clock 		= SOSC/PRESCALE
 *							= 32768/1 = 32.768KHz
 *		- To toggle led once every two seconds, PR1 is loaded with 65535 = 0xFFFF
 *
 ********************************************************************/
#include <plib.h>

// Configuration Bit settings
// SYSCLK = 72 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 36 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// FSOSCEN ON - this enables the SOSC to work independantly
// Other options are don't care
//
#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF, FSOSCEN = ON
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2

#define FOSC           		72E6

int main(void)
{
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
    // STEP 2. Configure Timer1 using external asynchronous clock, 1:1 prescale, 0xFFFF period

    OpenTimer1(T1_ON | T1_SOURCE_EXT | T1_SYNC_EXT_OFF | T1_PS_1_1, 0xFFFF);
			//Timer1 On, External Source, No synchronization, 1:1 Prescale, 65535 Period

    // STEP 3. Set up the timer interrupt with a priority of 2
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_2);

    // STEP 4. Enable multi-vector interrupts
    INTEnableSystemMultiVectoredInt();

	//Configure PORTF.RF1 = output
    mPORTFSetPinsDigitalOut(BIT_1);

    while(1);
}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 5. Configure the Timer1 interrupt handler

void __ISR(_TIMER_1_VECTOR, ipl2) Timer1Handler(void)
{
    // Toggle the LED
    mPORTFToggleBits(BIT_1);

    // Clear the interrupt flag
	mT1ClearIntFlag();
}


