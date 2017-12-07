#include "msp430fr5969.h"


void blinkLed();

unsigned data=0;
unsigned prevData=0;

void blinkLed()
{
    P1OUT |= BIT0;
    __delay_cycles(500000);
    P1OUT &=~BIT0;
    __delay_cycles(500000);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;

 // * // Look up the " Signal Descriptions" table in the data sheet
      // Configure GPIO: Configure P2.5 and P2.6 to be the USCI_A1 UART
      P2SEL1 |= BIT5 | BIT6;
      P2SEL0 &= ~(BIT5 | BIT6);

      P1OUT &=~BIT0;
      P1DIR |=BIT0;


// * // Enhanced Universal Serial Communication Interface (eUSCI)
     // Configure USCI_A1 for UART mode
     UCA1CTLW0 = UCSWRST;                      // Put eUSCI in reset
     UCA1CTLW0 |= UCSSEL__SMCLK;               // CLK = SMCLK


// * // UCA1CTLW0: eUSCI_A1 Control Word Register 0
     //  [15 UCPEN | 14 UCPAR | 13 UCMSB |12 UC7BIT | 11 UCS PB | 10-9 UCMODEx | 8 UCSYNC
     //  7-6 UCSSELx | 5 UCRXEIE | 4 UCBRKIE | 3 UCDORM | 2 UCTXADDR | 1 UCTXBRK | 0 UCSWRST ]

// 15-6 can only be modified when UCSWRST = 1

/*
 *   UCPEN   : Parity enable
 *   UCPAR   : Parity select
 *   UCMSB   : MSB first
 *   UC7BIT  : Select 8-bit/7-bit data length
 *   UCSPB   : Select the number of stop bits (One or Two)
 *   UCMODEx : USCI_A mode select (00 UART)
 *   UCSYNC  : Synchronous mode enable
 *   UCSSELx :  Clock source select
 *   UCRXEIE : Receive erroneous-character interrupt enable
 *   UCBRKIE : Receive break character interrupt enable
 *   UCDORM  : Dormant
 *   UCTXADDR: Transmit address
 *   UCTXBRK : Transmit break
 *   UCSWRST : Software reset enable
 */

// *  // Baud Rate calculation
      // if (F/BR > 16)  use oversampling mode
      // 1M/(16 * 9600) = 6.51
      // Fractional portion = 0.51
      // User's Guide Table 24-5: UCBRSx = 0x20
      // UCBRFx = int ( (0.51)*16) = 8

      // UCA0BR0 : eUSCI_A0 Baud Rate Control Word Register 0
      UCA1BR0 = 6;                             // int(1e6/16/9600)
      // UCA0BR0 : eUSCI_A0 Baud Rate Control Word Register 1
      UCA1BR1 = 0;

      UCA1MCTLW |= UCBRS5 | UCOS16 | UCBRF_8 ;
      // UCA0MCTLW : eUSCI_Ax Modulation Control Word Register
      // [ 15-8 UCBRSx | 7-4 UCBRFx | 3-1 Res. | 0 UCOS16]
      /*
       * UCBRSx : Second modulation stage select
       * UCBRFx : First modulation stage select
       * UCOS16 : oversampling  mode enabled
       *
       */
      UCA1CTLW0 &= ~UCSWRST;                    // Initialize eUSCI and release it for operation
      UCA1IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
      // UCA0IE : eUSCI_Ax Interrupt Enable Register
      // [ 15-4 Res. | 3 UCTXCPTIE | 2 UCSTTIE | 1 UCTXIE |  0 UCRXIE ]
      /*
       * UCTXCPTIE: Transmit complete interrupt enable
       * UCSTTIE  : Start bit interrupt enable
       * UCTXIE   : Transmit interrupt enable
       * UCRXIE   : Receive itnerrupt enable
       */

/********************************************************************
 // *********** Add only to Communication initiator  ***************
*********************************************************************/
  data =1;
  while(!(UCA1IFG&UCTXIFG));  // wait for the transmission flag to be set
  UCA1TXBUF = data;


  while(1){

      __bis_SR_register(LPM3_bits | GIE);       // Enter LPM3, interrupts enabled

      if(data > prevData)
      {
          blinkLed();
      }

      prevData = data;
      data++;   // When data overflow this system may break.
      while(!(UCA1IFG&UCTXIFG));
      UCA1TXBUF =  data;

      __no_operation();                         // For debugger
  }


}


#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG))
  {
    case USCI_UART_UCRXIFG:
      // UCA0IFG : eUSCI_Ax Interrupt Flag Register
      // [ 15-4 Res. | 3 UCTXCPTIFG | 2 UCSTTIFG | 1 UCTXIFG |  0 UCRXIFG ]
      /*
       * UCTXCPTIFG: Transmit complete interrupt flag
       * UCSTTIFG : Start bit interrupt flag
       * UCTXIFG   : Transmit interrupt flag
       * UCRXIFG   : Receive interrupt flag
       */

       data = UCA1RXBUF;  // Echo back the received character

      // UCA0TXBUF :  eUSCI_Ax Transmit Buffer Register
      // UCA0RXBUF :  eUSCI_Ax Receive Buffer Register
       __bic_SR_register_on_exit(LPM3_bits);
      break;
  }
}
