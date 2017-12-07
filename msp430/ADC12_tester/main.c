/*
The program uses Timer1_A. It uses two compare/capture channels (CCR1/CCR2)
to alternate two LEDs.

 @ Authar: Amjad Yousef Majid
 @  26/March/2017

 */

#include <msp430fr5969.h>

void init()
{
	  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

	  // Configure GPIO
	//  P1DIR |= BIT0;
	//  P1OUT |= BIT0;

	  PM5CTL0 &= ~LOCKLPM5;
}

void initCLK(){
	//Set the oscillator and the clock
	CSCTL0_H = CSKEY >>8; // Unlock the clock system registers
	CSCTL1 = DCOFSEL_6; 	  // Set the DCO to 1 MHz

	// Feed the ACLK form VLO oscillator, SMCLK from the DCO oscillator
	// and  MCLK from the DCO oscillator
	CSCTL2 =  SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 =  DIVS__8 | DIVM__1;
}

void timerInit()
{
	  TA1CCTL1 = CCIE;
	  TA1CCR1 = 1000;
}


void ADC_init()
{
	ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
	ADC12CTL1 = ADC12SHP;
	ADC12CTL2 |= ADC12RES_2;
	ADC12IER0 |= ADC12IE0;
	ADC12MCTL0 |= ADC12INCH_1 | ADC12VRSEL_1;
}

int main(void)
{
 	init();
 	initCLK();
 	ADC_init();
	timerInit();
	TA1CTL = TASSEL__SMCLK | ID__1| MC__CONTINUOUS;

  __bis_SR_register(GIE);
  while(1)
  {
	  ;
  }
  __no_operation();
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR (void)
{
	switch(__even_in_range(TA1IV, TA1IV_TAIFG))
		{
			case TA1IV_TACCR1:
				  ADC12CTL0 |= ADC12ENC | ADC12SC;                   // Start conversion-software trigger
				  while (!(ADC12IFGR0 & BIT0));
				  *(unsigned int *)0x1900 = ADC12MEM0;                     // Read conversion result

				  TA1CCR1 +=1000; //set the offset for the next interrupt
			//	  P1OUT ^=BIT0;
			break;

			default:   break;
		}

}
