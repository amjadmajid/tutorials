/*
 * dataProtec.h
 *
 *  Created on: 16 May 2017
 *      Author: Amjad
 */

#include <msp430fr5969.h>
#include <stdint.h>
#include "global.h"

#ifndef INCLUDE_DATAPROTEC_H_
#define INCLUDE_DATAPROTEC_H_

/*
 * Max available memory is 48/2 = 24
 * Maximum number of supported pages are 8
 * This code requires linker script modification to put the variables
 * in a known location (the pages locations 0xBF70)
 */


uint8_t* __return_addr_no_check(unsigned int* var) ;
uint8_t* __return_addr_wr_no_check(unsigned int* var) ;

void __bringPagROM(unsigned int pagTag);
void __sendPagROM(unsigned int pagTag);

void __sendPagTemp(unsigned int pagTag);
void __bringPagTemp(unsigned int pagTag);

unsigned int __pageSwap(unsigned int * varAddr);
void __pagesSwap(unsigned int * CurnPag, unsigned int * varAddr);

void __bringPersisCrntPag(unsigned int curntPag);
void __pagsCommit();

// Memory access interface

#define DIRTY_PAGE  0      // make it 0 to commit only the dirty pages [This macro does not work with P() ]

#define __VAR_ADDR(var)                 ((unsigned int) (&(var)) )

#define __IS_VAR_IN_CRNT_PAG(var)       ( ( __VAR_ADDR(var)  >= CrntPagHeader ) && \
                                        ( __VAR_ADDR(var)  <  (CrntPagHeader+PAG_SIZE) ))

#define __VAR_PT_IN_RAM(var)            (  (__typeof__(var)*) (  (__VAR_ADDR(var) - CrntPagHeader) + RAM_PAG )  )

#define __PP(wvar, rvar)  __temp_temp = RP(rvar) ; \
                              WP(var) =  __temp_temp

/******************************************
 *        User Memory Interface
 ******************************************/
#define __RP__(var) (__typeof__(var)*) __return_addr_no_check(&var)
#define __WP__(var) (__typeof__(var)*) __return_addr_wr_no_check(&var)

#define WP(var)         ( *__WP__(var) )
#define RP(var)         ( *__RP__(var) )

#define PP(wvar, rvar)  ( __PP(wvar, rvar) )

#endif /* INCLUDE_DATAPROTEC_H_ */
















