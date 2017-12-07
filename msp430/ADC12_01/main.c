#include <msp430fr5969.h>

// Functions prototyping
void ADC_init();

void ADC_init()
{
	ADC12CTL0 = ADC12SHT0_2 | ADC12ON;		//  Sample and hold 16 ADC clock cycle and Turn on the ADC
	/*
	 * ADC12CTL0 = [15-12 ADC12SHT1x | 11-8 ADC12SHT0x | 7 ADC12MSC | 6-5 Res. | 4 ADC12ON | 3-2 Res. | 1 ADCENC | 0 ADC12SC ]
	 *
	 * ADC12SHT1x : These bits define the number of ADC12CLK cycles in the sampling period for registers ADC12MEM8 to ADC12MEM23.
	 * ADC12SHT0x : These bits define the number of ADC12CLK cycles in the sampling period for registers ADC12MEM0 to ADC12MEM7.
	 * ADC12MSC 	 : multiple sample and conversion.
	 * ADC12ON   : Enable the ADC
	 * ADCENC	 : Enable conversion
	 * ADC12SC	 : Start conversion
	 */

	ADC12CTL1 = ADC12SHP;			// ADC12_B sample-and-hold pulse-mode select. Source clock is sample timer
	/*
	 * [15 Res. | 14-13 ADC12PDIV | 12-10 ADC12SHSx | 9 ADC12SHP | 8 ADC12ISSH | 7-5 ADC12DIVx | 4-3 ADC12SSELx | 2-1 ADC12CONSEQx | 0 ADC12BUSY]
	 * ADC12PDIV : This bit predivides the selected ADC12_B clock source.
	 *
	 */

	ADC12CTL2 |= ADC12RES_2;			// Select the ADC resolution
	/*
	 * 00b = 8 bit (10 clock cycle conversion time)
	 * 01b = 10 bit (12 clock cycle conversion time)
	 * 10b = 12 bit (14 clock cycle conversion time)
	 */

	ADC12IER0 |= ADC12IE0;			// Enable interrupts for specific channels
	/*
	 * Enables or disables the interrupt request for ADC12IFG0 bit.
	 * 0b = Interrupt disabled
	 * 1b = Interrupt enabled
	 *
	 * ADC12IE0               (0x0001)     ADC12 Memory 0 Interrupt Enable.
	 * ADC12IE1               (0x0002)     ADC12 Memory 1 Interrupt Enable.
	 * ...
	 * ADC12IE15              (0x8000)     ADC12 Memory 15 Interrupt Enable
	 */

	ADC12MCTL0 |= ADC12INCH_3 | ADC12VRSEL_2;		// Select the channel to sample from and the references
	/*
	 * Select        A1 (P1.1)      Vref = 1.2V
	 *
	 * ADC12INCH_4: Input channel select.
	 * If ADC12DIF = 0: A4;
	 * If ADC12DIF = 1: Ain+ = A4, Ain- = A5
	 *
	 * ADC12VRSEL_x : Selects combinations of VR+ and VR- sources as well as the buffer selection.
	 * 0000b = VR+ = AVCC, VR- = AVSS
	 * 0001b = VR+ = VREF buffered, VR- = AVSS 0010b = VR+ = VeREF-, VR- = AVSS
	 * 0011b = VR+ = VeREF+ buffered, VR- = AVSS
	 * ...
	 */
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // Configure P1.1 for the ADC
    // The Temp Sensor pin from the BoosterPack
    P1SEL1 |= BIT3;
    P1SEL0 |= BIT3;

    P1DIR |= 0x01;


    ADC_init();

    while(1){
		ADC12CTL0 |= ADC12ENC | ADC12SC; // Enabling and start conversion
	
		__bis_SR_register(LPM0_bits +GIE);
		// The__bis_SR_register() command enables the low power mode in the status register after returning
		// from the ADC interrupt routine, and enables the general interrupt to wake up the MSP430 upon another
		// ADC sampling.
		__no_operation();
    }
	return 0;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	  switch (__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG))
	  {
		case ADC12IV_ADC12IFG0:                 // Vector 12:  ADC12MEM0 Interrupt
		  if (ADC12MEM0 > 0x323)               // ADC12MEM = A1 > 0.5V?
			P1OUT |= BIT0;                      // P1.0 = 1
		  else
			P1OUT &= ~BIT0;                     // P1.0 = 0
		  __bic_SR_register_on_exit(LPM0_bits); // Exit active CPU
		  break;
		 default: break;
	  }
}
