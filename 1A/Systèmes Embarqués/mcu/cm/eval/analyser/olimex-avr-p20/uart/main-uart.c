/*	Sample program for Olimex AVR-P20 with AT90S2313 processor
 *	Echoes back the received characters on the uart. In order to work,
 *	connect the RX pad with PD1(pin 3) and TX pad with PD0(pin 2)
 *	Compile with AVRStudio+WinAVR (gcc version 3.4.6)
 */

#define	__AVR_AT90S2313__	1
#define OSCSPEED	10000000		/* in Hz */


#define UBRR	_SFR_IO8(0x09)
#define UCR	_SFR_IO8(0x0A)
#define USR	_SFR_IO8(0x0B)
#define UDR	_SFR_IO8(0x0C)

#include "avr/io.h"


int main()
{
	//long BaudRate;
	unsigned char Ch=0;
	//uint32_t Baud = 9600;
	//unsigned int BaudRate;
	//unsigned int i;
	//+ + +		Initialize PORT		+ + +
		PORTB = 0b10000000;
		PORTD = 0b00000000;

		DDRB = 0b10000000;
		DDRD = 0b00000000;
	//- - -		Initialize PORT		- - -

	//+ + +		Initialize UART		+ + +
		//BaudRate = OSCSPEED / (16 * Baud) - 1;
		//UBRR = (unsigned char) BaudRate;
		UBRR = 64;

		UCR = UCR | 0b00011000;
		//RXEN, TXEN (Bit 3, 4) = 1
	//- - -		Initialize UART		- - -


	while (1)
	{
		//Ch = UARTReceive();

		//+ + +		UARTReceive		+ + +
		if (USR & 0b10000000)
			Ch = UDR;
		else
			Ch = 0;
		//- - -		UARTReceive		- - -


		if (Ch)
		{
			//UARTTransmit(Ch+1);

			//+ + +		UARTTransmit	+ + +
			while (!(USR & 0b00100000));
			UDR = Ch + 1;
			//- - -		UARTTransmit	- - -
		}
	}	
	return 0;
}
