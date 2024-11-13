//untested

/*	Sample program for Olimex AVR-P20 with AT90S2313 processor
 *	Press Button to start Led blinking
 *	Compile with AVRStudio+WinAVR (gcc version 3.4.6)
 *	make sure LED-J is not closed while programming
 */

#define	__AVR_AT90S2313__	1

#include "avr/io.h"

void PORT_Init()
{
	PORTB = 0b10000000;
	DDRB  = 0b10000000;		//set Led as output (Bit7 = 1)

	PORTB = 0b00000000;
	DDRD  = 0b00000000;
}

int main()
{
	int i;
	PORT_Init();
	while (1)
	{
		if (PIND & 0b00000100)
			{
				PORTB = PORTB & 0b01111111;
				for (i=30000; i; i--);
				PORTB = PORTB | 0b10000000;
				for (i=30000; i; i--);
			}
		else
			PORTB = PORTB & 0b01111111;
	}
}
