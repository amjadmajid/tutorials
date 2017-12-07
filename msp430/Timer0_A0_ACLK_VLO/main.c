/*
	 This example sets Timer0_A counter (TA0R) in continuous mode (counts up to 0xffff)
	 When TA0R overflows (back to zero) it generates an interrupts and set the TAIFG
	 @ Author: Amjad Yousef Majid
	 @ Data : 26/March/2017
*/

#include <msp430fr5969.h>
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watch dog timer

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= BIT0; 		// Make port 1 pin 0 an output (BIT0 = 0x0001)
	P1OUT |= BIT0; 		// Set port 1 pin 0 high

	//Set the oscillator and the clock
	CSCTL0_H = CSKEY >>8; // Unlock the clock system registers
	CSCTL1 = DCOFSEL_0; 	  // Set the DCO to 1 MHz

	// Feed the ACLK form VLO oscillator, SMCLK from the DCO oscillator
	// and  MCLK from the DCO oscillator
	CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;


	// This control register controls Timer_A counter (TA0R)
	TA0CTL = TASSEL__ACLK | ID__1 | MC__CONTINUOUS | TACLR | TAIE;
/*
	Timer0_A control register
	[15-10 Res. | 9-8 TASSEL | 7-8 ID | 5-4 MC | 3 Res. | 2 TACLR | 1 TAIE | 0 TAIFG]

	TASSEL: Timer_A source select
	ID	  : Input Divider
	MC	  : Mode Control
	TACLR : Timer_A clear
	TAIE  : Timer_A interrupt enable
	TAIFG : Timer_A interrupt flag
 */

	__bis_SR_register(LPM3_bits | GIE);
/*
 	 LPM3: Low power mode 3
 	 GIE: General interrupts enable
 */

}

/*
	TIMER0_A1_VECTOR is the .int44 interrupt vector.
	It handles interrupts from:
	TA0CCR1
	TA0CCR2
	TA0R (TAIFG)
 */

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
	switch(__even_in_range(TA0IV, TA0IV_TAIFG) )
	{
	case TA0IV_TAIFG:			// when TA0R overflows
		P1OUT ^= BIT0;
	break;
	default: break;
	}
}
