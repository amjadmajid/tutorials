/*
This example sets Timer0_A0 in compare mode.
Timer_A counter (TA0R) counts up to the value of TA0CCR0.
Once TA0R = TA0CCR0 an interrupt generated and TA0R rolls back to zero
Note:
The TA0CCR0 CCIFG flag has the highest Timer_A interrupt priority and has a dedicated interrupt vector

 @ Authar: Amjad Yousef Majid
 @  26/March/2017
 Based on a TI example
 */


#include <msp430fr5969.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

  // Configure GPIO
  P1DIR |= BIT0;
  P1OUT |= BIT0;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

  // TACCR0 interrupt enabled
  // CAP=0: Timer0_A0 is used in the compare mode
  TA0CCTL0 = CCIE;
/*
	 TA0CCTL0 : Timer0_A Capture/Compare Control n Register
	 [15-14 CM | 13-12 CCIS | 11 SCS | 10 SCCI | 9 Res. | 8 CAP | 7-5 OUTMOD | 4 CCIE | 3 CCI | 2 OUT | 1 COV | 0 CCIFG ]

	 M: Capture mode
	 CCIS: Capture/compare input select.
	 SCS: Synchronize capture source. This bit is used to synchronize the capture input signal with the timer clock.
	 SCCI: Synchronized capture/compare input.
	 CAP: Capture mode
	 OUTMOD: Output Mode
	 CCIE: Capture/compare interrupt enable.
	 CCI: Capture/compare input. The selected input signal can be read by this bit.
	 OUT: Output
	 COV: Capture overflow.
	 CCIFG: Capture/compare interrupt flag.
 */

  // Timer_A Capture/Compare 0 Register
  // The value to compare Timer0_A (TA0R) against
  TA0CCR0 = 50000;

  // Timer0_A control register
  TA0CTL = TASSEL__SMCLK | MC__UP;   // SMCLK, continuous mode
  	  	  	  	  	  	  	  	  	  	  	// Interrupts for the timer0_A (TA0R) is not enabled

  //  All CCIFG flags request an interrupt when their corresponding CCIE bit and the GIE bit are set.
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
  __no_operation();                         // For debugger
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
  P1OUT ^= BIT0;
}
