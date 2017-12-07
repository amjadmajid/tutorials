/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
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
//  MSP430FR59xx Demo - DMA0, Repeated Block to-from RAM, Software Trigger
//
//  Description: A 16 word block from 1C20-1C2Fh is transfered to 1C40h-1C4fh
//  using DMA0 in a burst block using software DMAREQ trigger.
//  After each transfer, source, destination and DMA size are
//  reset to initial software setting because DMA transfer mode 5 is used.
//  P1.0 is toggled during DMA transfer only for demonstration purposes.
//  ** RAM location 0x1C00 - 0x1C3F used - make sure no compiler conflict **
//   MCLK = SMCLK = default DCO
//
//
//                 MSP430FR5969
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Priya Thanigai
//   Texas Instruments Inc.
//   August 2012
//   Built with IAR Embedded Workbench V5.40 & Code Composer Studio V5.5
//******************************************************************************
#include "msp430fr5969.h"

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;

//#define SW

//  __bis_SR_register(LPM4_bits | GIE );
//
//
//  __no_operation();
//  while(1)
//  {
//	  __no_operation();
//
//  }
//}

#ifdef SW
  unsigned int * src_pt = (unsigned int *) 0x1C20;
  unsigned int * des_pt = (unsigned int *) 0x5000;

  unsigned int arr[16] = {1,2,3,4,5,6,7,4,5,6,7,0,9,14,5,8};

  unsigned int i;

  while(100){
			for (i = 1000; i > 0; i--)
				{
				* des_pt = * src_pt ;
					src_pt++;
				*des_pt = arr[i];
					des_pt++;
				}
			src_pt = (unsigned int *) 0x1C20;
			des_pt = (unsigned int *) 0x5000;
		}
//			__bis_SR_register(LPM4_bits | GIE);

  while(1)
  {
	  __no_operation();
  }

}

#else
  // Configure DMA channel 0
  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long) 0x1C20);
                                            // Source block address
  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long) 0x5000);
                                            // Destination single address
  DMA0SZ = 2048;                              // Block size
  DMA0CTL = DMADT_5 ;       				   //Repeated block transfer
  DMA0CTL|= DMASRCINCR_3 | DMADSTINCR_3;    //increment the destination/source addresses
  DMA0CTL |= DMAIE;
  DMA0CTL |= DMAEN;                         // Enable DMA0
  DMA0CTL |= DMAREQ;                        // Trigger block transfer
  __bis_SR_register(LPM3_bits | GIE);
  while(1){

	  __no_operation();                         // For debugger
  }
}

volatile unsigned x = 0;
void __attribute__((interrupt(DMA_VECTOR))) DMA_ISR(void)
		{
	  	  	  DMA0CTL &=~DMAIFG;

	  	    unsigned int * src_pt = (unsigned int *) 0x1C30;
	  	    unsigned int * des_pt = (unsigned int *) 0x5000;

	  	    unsigned int i;
	  	  			for (i = 2048; i > 0; i--)
	  	  				{
	  	  				* des_pt = * src_pt ;
	  	  					src_pt++;
	  	  					des_pt++;
	  	  				}
	  	  			src_pt = (unsigned int *) 0x1C20;
	  	  			des_pt = (unsigned int *) 0x5000;

//	  	  		  DMA0CTL |= DMAREQ;                        // Trigger block transfer
//	  	  		  __bic_SR_register_on_exit(LPM3_bits);
		}
#endif
