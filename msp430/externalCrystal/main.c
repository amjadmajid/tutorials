/*
 * Blink the LED every 4 seconds
 */

#include <msp430fr5969.h>


void blinkLed()
{
    P1OUT |= BIT0;
    __delay_cycles(37268/2);
    P1OUT &=~BIT0;
    __delay_cycles(37268/2);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P1OUT &=~BIT0;
    P1DIR |=BIT0;

    // Configure PJ.4 and PJ.5 to be used by the low frequency oscillator
    PJSEL0 |= BIT4 | BIT5;                    // For XT1

    // XT1 Setup
    CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
    CSCTL2 = SELA__LFXTCLK | SELS__LFXTCLK  | SELM__LFXTCLK ; // Source all the clocks from the Low Frequency oscillator
    CSCTL3 = DIVA__4 | DIVS__4 | DIVM__4;     // divide all the clocks by 4
    CSCTL4 &= ~LFXTOFF;  // Clear the LFXTOFF bits to enable LFXT.
    do
    {
      CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
      SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
    CSCTL0_H = 0;                             // Lock CS registers

    while(1)
    {
        blinkLed();
    }
	
}
