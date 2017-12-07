/*
 * This App is attempting to light up an LED when a switch is pressed
 * and dim it when the switch is released.
 *
 * Required
 *	A switch is connected to Port 1 pin 1 (P1.1)
 *	An LED is connected to Port 1 pin 0 (P1.0)
 *
 *	@ Author   : Amjad Yousef Majid
 *	@ Date     : 15/April/2017
 *	@ Gmail ID : amjad.y.majid
 */

#include <msp430.h> 


void init()
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;

	P1REN |= BIT1;		// Enable Resistor on  P1.1
	P1OUT = BIT1;		// Make it a pull up resistor
	P1DIR = BIT0;		// Make P1.0 and output
	P1DIR &=~BIT1;		// Make P1.1 an input (this is the default state)
}

int main(void) {
	 init();

    while(1)
    {
    		if( (P1IN & BIT1) )   // the button is negative logic (when it is pressed the pin (P1.1) is low )
    		{
    			P1OUT |= BIT0;	  // set the LED pin
    			__delay_cycles(50000);
    		}else{
    			P1OUT &=~BIT0;    // CLear the LED pin
    			__delay_cycles(5000);
    		}
    }

	return 0;
}
