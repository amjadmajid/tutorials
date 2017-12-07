#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

  __delay_cycles(100000);

//  // Configure GPIO
  P1OUT &= ~BIT0;
  P1DIR |= BIT0;
  P1OUT |= BIT0;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

  TA0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
  TA0CCR0 = 50000;
  TA0CTL = TASSEL__SMCLK | MC__CONTINOUS;   // SMCLK, continuous mode



  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
  __no_operation();                         // For debugger
}

// Timer0_A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	__delay_cycles(1000);
  P1OUT ^= BIT0;
//  TA0CCR0 += 500000;                         // Add Offset to TA0CCR0
  PMMCTL0 = PMMPW|PMMSWBOR;
}
