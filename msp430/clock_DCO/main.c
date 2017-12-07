//******************** DCO *******************
// Setting the DCO to a specific frequency
// Feeding the MCLK from the DCO
// Developed using CCS 6
// @Author Amjad Yuosef Majid
// Date 12-Feb-2017
//*********************************************
#include <msp430fr5969.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop Watchdog timer

  // Configure GPIO
  P1OUT &= ~BIT0;                           // Clear P1.0 output latch for a defined power-on state
  P1DIR |= BIT0;                            // Set P1.0 to output direction

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;




  CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers

 //********************* CSCTL1 Register ***********************
  // CSCTL1 is used to select a frequencys range for the DCO
  // CSCTL1: [15-7 Res. | 6 DCORSEL | 5-4 Res. | 3-1 DCOFSEL | 0 Res.]

  //  CSCTL1 = DCOFSEL_0;                   // Set DCO to 1MHz
  CSCTL1 = DCOFSEL_1;                       // Set DCO to 2.67 MHz
  //  CSCTL1 = DCOFSEL_2;                   // Set DCO to 3.5 MHz
  //  CSCTL1 = DCOFSEL_3;                   // Set DCO to 4 MHz
  //  CSCTL1 = DCOFSEL_4;                   // Set DCO to 5.33 MHz
  //  CSCTL1 = DCOFSEL_5;                   // Set DCO to 7 MHz
  //  CSCTL1 = DCOFSEL_6;                   // Set DCO to 8MHz

  // To operate beyond the 8MHz set the DCORSEL and 
  // Configure one FRAM waitstate as required by the device datasheet for MCLK
  // operation beyond 8MHz _before_ configuring the clock system.
  // FRCTL0 = FRCTLPW | NWAITS_1;

  //********************* CSCTL2 Register ***********************
  // CSCTL2 is used to set the clocks sources
  // CSCTL2 : [ 15-11 Res.| 10-8 SELA | 7 Res. | 6-4 SELS | 3 Res.| 2-0 SELM ]
  /*
  Selects the MCLK source
  	000b = LFXTCLK when LFXT available, otherwise VLOCLK
  	001b = VLOCLK
  	010b = LFMODCLK
  	011b = DCOCLK
  	100b = MODCLK
  	101b = HFXTCLK when HFXT available, otherwise DCOCLK
  */
  CSCTL2 =  SELM__DCOCLK;  					// MCLK = DCO

  //********************* CSCTL3 Register ***********************
  // CSCTL3 is used to select a frequency divider
  // CSCTL3 : [15-11 Res. | 10-8 DIVA | 7 Res. | 6-4 DIVS | 3 Res. | 2-0 DIVM]
	/*
	the dividers values
	000b = /1
	001b = /2
	010b = /4
	011b = /8
	100b = /16
	101b = /32
	 */
  CSCTL3 = DIVM__1;     						// divide the DCO frequency by 1

  CSCTL0_H = 0;                             	// Lock CS registers


  while (1) {
    P1OUT ^= 0x01;                          // Toggle LED
    __delay_cycles(2670000*10);                // Wait 2670000*10 CPU Cycles (10 seconds)
  }
}
