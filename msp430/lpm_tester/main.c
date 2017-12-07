
/*******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//   MSP430FR59xx Demo - Enters LPM4
//
//   Description: Device enters LPM4
//
//          MSP430FR5969
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |               |
//
//   T. Witt/ P. Thanigai
//   Texas Instruments Inc.
//   December 2011
//   Built with IAR Embedded Workbench V5.30 & Code Composer Studio V5.1
//******************************************************************************
#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

#ifdef nan
  // Configure GPIO
  P1OUT = 0;
  P1DIR = 0xFF;

  P2OUT = 0;
  P2DIR = 0xFF;

  P3OUT = 0;
  P3DIR = 0xFF;

  P4OUT = 0;
  P4DIR = 0xFF;

  PJOUT = 0;
  PJDIR = 0xFFFF;
#endif

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
#ifdef nan
  // Clock System Setup
  CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
  CSCTL1 = DCOFSEL_6;                       // Set DCO to 8MHz
  CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;  // Set SMCLK = MCLK = DCO
                                            // ACLK = VLOCLK
  CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // set all dividers
  CSCTL0_H = 0;                             // Lock CS registers
#endif

  // Configure DMA channel 0
//  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) 0x1C20);
//                                            // Source block address
//  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) 0x5000);
//                                            // Destination single address
//  DMA0SZ = 10;                              // Block size
//  DMA0CTL = DMADT_5 ;       //Repeated block transfer
//  DMA0CTL|= DMASRCINCR_3 | DMADSTINCR_3; //  increment the destination/source addresses
//  DMA0CTL |= DMAIE;
//  DMA0CTL |= DMAEN;                         // Enable DMA0

  __bis_SR_register(LPM4_bits);
  __no_operation();                         // For debugger
}
