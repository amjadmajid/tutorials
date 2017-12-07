#include <msp430.h> 
#include <stdint.h>
#include "dataProtec.h"

__nv unsigned int __persis_CrntPagHeader = BIGEN_ROM;

__p uint16_t rVar_p2 = 0x2222;
__p uint8_t fillPage_2[999] ={0};

__p uint16_t rVar_p1 = 0x1111;
__p uint8_t fillPage_1[999] ={0};




uint16_t res1 =0 ;
volatile uint16_t res2 =0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;       // Lock LPM5.

    P3OUT &= ~BIT5;
    P3DIR |=BIT5;

    //******// Check the correctness of the address translation
    __bringPagROM(__persis_CrntPagHeader);            // bring the default page

    P3OUT |= BIT5;
    WP(rVar_p1) = res1;          // write a value into the RAM page
    P3OUT &= ~BIT5;

    __delay_cycles(500);

    res1 = RP(rVar_p1) + 1;           // read the variable
//    res1++;
    P3OUT |= BIT5;

    res1 = RP(rVar_p1);           // read the variable
    P3OUT &= ~BIT5;

    __delay_cycles(500);

    //******// Check the page swapping, Check the memory to see if the page1 went to its temporary location (0xDF70)
    P3OUT |= BIT5;
    res2 = RP(rVar_p2);           // read the variable
    P3OUT &= ~BIT5;

    __delay_cycles(500);

    P3OUT |= BIT5;
    WP(res2) = rVar_p2;           // read the variable
    P3OUT &= ~BIT5;

    __delay_cycles(500);
    res2++;
    WP(rVar_p2) = res2;          // write a value into the RAM page

    //******// Check page swapping caused by writing to a variable
    P3OUT |= BIT5;
    WP(rVar_p1) = res2;          // write a value into a page that is not in RAM
    P3OUT &= ~BIT5;

    WP(rVar_p2) = res1;          // write a value into a page that is not in RAM


    //******// Check the commit process
    P3OUT |= BIT5;
    __pagsCommit();
    P3OUT &= ~BIT5;

    __no_operation();
     while(1)
     {
         ;
     }

	return 0;
}
