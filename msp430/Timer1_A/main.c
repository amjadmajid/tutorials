/*
The program uses Timer1_A. It uses two compare/capture channels (CCR1/CCR2)
to alternate two LEDs.

 @ Authar: Amjad Yousef Majid
 @  26/March/2017

 */


#include <msp430fr5969.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

  // Configure GPIO
  P1DIR |= BIT0;
  P4DIR |= BIT6;
  P1OUT |= BIT0;
  P4OUT &= BIT6;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

// Enable interrupts for TA1CCR1 and TA1CCR2
  TA1CCTL1 = CCIE;
  TA1CCTL2 = CCIE;
  TA1CCR1 = 0xffff/2;
  TA1CCR2 = 0xffff;

  // Timer1_A control register
  TA1CTL = TASSEL__SMCLK | ID__8| MC__CONTINUOUS;   // SMCLK, continuous mode
  	  	  	  	  	  	  	  	  	  	  	  	  	  // ID__8 divide the input clock by 8

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
  __no_operation();                         // For debugger
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR (void)
{
	switch(__even_in_range(TA1IV, TA1IV_TAIFG))
		{
			case TA1IV_TACCR1:
				P1OUT &= ~BIT0;
				P4OUT |= BIT6;
			break;

			case TA1IV_TACCR2:
				P1OUT |= BIT0;
				P4OUT &= ~BIT6;
			break;

			default:   break;
		}

}
