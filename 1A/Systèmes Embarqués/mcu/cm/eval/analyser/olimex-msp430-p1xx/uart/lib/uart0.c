
#include  <msp430x16x.h>
#include  "uart0.h"

void InitUART0 (void)                           //UART0 init
{
  UCTL0 = CHAR;                                 //Sart bit, 8 data bits, no parity, 1 stop
  UTCTL0 = SSEL0;                               //ACLK(32768) is UART clock

  U0BR0 = 0x03;                                 //9600
  U0BR1 = 0x00;
  UMCTL0 = 0x4A;                                //modulation

  ME1 |= UTXE0 | URXE0;                         //enable UART modul
  P3SEL |= 0x30;                                // P3.4,5 = USART0 TXD/RXD
  P3DIR |= BIT4;                                //enable TXD0 as output
  P3DIR &= ~BIT5;                               //enable RXD0 as input
  IE1 |= URXIE0;                                // Enable USART0 RX interrupt
  
  // SPP +
  // PWR_RS enable - 1 (p3.0)
  P3DIR = P3DIR | 0x01;
  P3OUT = P3OUT | 0x01;
  // SPP -    
  
  _EINT();
  for (int i=100; i; i--);  // short delay
}

void UART_transmit (unsigned char Transmit_Data)              //UART0 Transmit Subroutine
{
  while ((IFG1 & UTXIFG0) == 0);                              //Wait for ready U0TXBUF
  U0TXBUF = Transmit_Data;                                    //send data
}

void UART0SendTxt(char* a)
{
   for(;*a;++a) UART_transmit(*a);
}

#pragma vector=UART0RX_VECTOR
__interrupt void usart0_rx (void)
{
  UART_transmit (RXBUF0+1);                  //transmit Echo + 1
}
