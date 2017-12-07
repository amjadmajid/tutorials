

#include "dataProtec.h"
/*####################################
              Paging
#####################################*/

     volatile uint8_t dirtyPag = DIRTY_PAGE;
     uint32_t __temp_temp=0;
     // TODO THIS ARRAY CONSUME TOO MUCH OF THE SRAM
     unsigned int __pagsInTemp[NUM_PAG] = {0};  // This can be pretty big and consume large section of the SRAM, therefore I shift it to FRAM
__nv unsigned int __persis_pagsInTemp[NUM_PAG ] = {0};

     unsigned int CrntPagHeader = BIGEN_ROM;
__nv unsigned int __persis_CrntPagHeader = BIGEN_ROM;

__nv unsigned int __pageFaultCounter = 0;


/*
 * Send a page to its temp buffer
 */
void __sendPagTemp(unsigned int pagHeader)
{
    // Configure DMA channel 1
    __data16_write_addr((unsigned short) &DMA1SA,(unsigned long) RAM_PAG);
                                            // Source block address
    __data16_write_addr((unsigned short) &DMA1DA,(unsigned long) pagHeader + APP_MEM );
                                            // Destination single address
    DMA1SZ = PAG_SIZE_W;                            // Block size
    DMA1CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA1CTL |= DMAEN;                         // Enable DMA0

    DMA1CTL |= DMAREQ;                      // Trigger block transfer


    unsigned char idx=0;
    while(__pagsInTemp[idx] !=0 )
    {
        if(pagHeader == __pagsInTemp[idx] )
        {
            break;
        }
        idx++;
    }
    // Keep track of the buffered pages
    __pagsInTemp[ idx ] = pagHeader;
}


/*
 * Bring a page to its temp buffer
 */
void __bringPagTemp(unsigned int pagHeader)
{
    // Configure DMA channel 1
    __data16_write_addr((unsigned short) &DMA1SA,(unsigned long) (pagHeader + APP_MEM) );
                                            // Source block address
    __data16_write_addr((unsigned short) &DMA1DA,(unsigned long)  RAM_PAG );
                                            // Destination single address
    DMA1SZ = PAG_SIZE_W;                            // Block size
    DMA1CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA1CTL |= DMAEN;                         // Enable DMA0

    DMA1CTL |= DMAREQ;                      // Trigger block transfer

    CrntPagHeader =  pagHeader;
}

/*
 * Bring a page to its ROM buffer
 */
void __bringPagROM(unsigned int pagHeader)
{
    // Configure DMA channel 1
    __data16_write_addr((unsigned short) &DMA1SA,(unsigned long) (pagHeader) );
                                            // Source block address
    __data16_write_addr((unsigned short) &DMA1DA,(unsigned long) RAM_PAG );
                                            // Destination single address
    DMA1SZ = PAG_SIZE_W;                            // Block size
    DMA1CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA1CTL |= DMAEN;                         // Enable DMA0

    DMA1CTL |= DMAREQ;                      // Trigger block transfer

    CrntPagHeader =  pagHeader;
}

/*
 * Send a page to its final locaiton
 */
void __sendPagROM(unsigned int pagHeader)
{
    // Configure DMA channel 1
    __data16_write_addr((unsigned short) &DMA2SA,(unsigned long) pagHeader + APP_MEM);
                                            // Source block address
    __data16_write_addr((unsigned short) &DMA2DA,(unsigned long)  pagHeader );
                                            // Destination single address
    DMA2SZ = PAG_SIZE_W;                            // Block size
    DMA2CTL = DMADT_5 | DMASRCINCR_3 | DMADSTINCR_3; // Rpt, inc
    DMA2CTL |= DMAEN;                         // Enable DMA0

    DMA2CTL |= DMAREQ;                      // Trigger block transfer
}


//TODO this function does not
void __bringPersisCrntPag(unsigned int curntPag)
{
    unsigned int ReqPagTag, idx=0;

    // Search the page in the buffer
    while( (ReqPagTag = __persis_pagsInTemp[idx]) != 0)
    {
        if ( ReqPagTag  == curntPag )
            {
                __bringPagTemp( curntPag );
                goto PAGE_PULLED;
             }
        idx++;
    }

    __bringPagROM( curntPag);

PAGE_PULLED:
	__no_operation();
}

/*
 * pageSwap:
 */
//TODO this function does not
unsigned int __pageSwap(unsigned int * varAddr)
{
#if !DIRTY_PAGE
    __pageFaultCounter++;
#endif

    //2// Find the requested page
    unsigned int ReqPagTag;
    unsigned int ReqPagTag_dirty = (unsigned int) varAddr;
    unsigned int __temp_pagSize = BIGEN_ROM+PAG_SIZE ; // the upper limit of the first page
    // TODO we are not checking if the var is not in any page !
    unsigned char idx=0;

    // Search the page in the buffer
    while( (ReqPagTag = __pagsInTemp[idx]) != 0)
    {
        if ( (ReqPagTag_dirty >= ReqPagTag) && (ReqPagTag_dirty < (ReqPagTag+PAG_SIZE) ) )
                {
                    if(dirtyPag)
                    {
                        __pageFaultCounter++;
                        __sendPagTemp( CrntPagHeader );  // check the buffer before insertting to it
                        dirtyPag=DIRTY_PAGE;
                    }
                    // we found the page
                    __bringPagTemp( ReqPagTag );

                    goto PAG_IN_TEMP;
                }
        idx++;
    }

    //TODO optimize this search (maybe with a switch statement )
    // search the page in the ROM if it is not in the buffer
    while( ! (ReqPagTag_dirty < __temp_pagSize) )  // if the var is not with the page
    {
        __temp_pagSize +=   PAG_SIZE;               // move to next page
    }

    ReqPagTag = __temp_pagSize-PAG_SIZE;

    if(dirtyPag)
    {
        __pageFaultCounter++;
        __sendPagTemp( CrntPagHeader );
        dirtyPag=DIRTY_PAGE;
    }
    __bringPagROM(ReqPagTag);

PAG_IN_TEMP:

    return 0;
}


/*
 * pageSwap:
 */
//TODO this function does not
void __pagesSwap(unsigned int * CurnPag, unsigned int * varAddr)
{
#if !DIRTY_PAGE
    __pageFaultCounter++;
#endif

    //2// Find the requested page
    unsigned int ReqPagTag;
    unsigned int ReqPagTag_dirty = (unsigned int) varAddr;
    unsigned int __temp_pagSize = BIGEN_ROM+PAG_SIZE ; // the upper limit of the first page
    // TODO we are not checking if the var is not in any page !
    unsigned char idx=0;

    // Search the page in the buffer
    while( (ReqPagTag = __pagsInTemp[idx]) != 0)
    {
        if ( (ReqPagTag_dirty >= ReqPagTag) && (ReqPagTag_dirty < (ReqPagTag+PAG_SIZE) ) )
                {
                    if(dirtyPag)
                    {
                        __pageFaultCounter++;
                        __sendPagTemp( *CurnPag );  // check the buffer before insertting to it
                        dirtyPag=DIRTY_PAGE;
                    }
                    // we found the page
                    __bringPagTemp( ReqPagTag );

                    goto PAG_IN_TEMP;
                }
        idx++;
    }

    //TODO optimize this search (maybe with a switch statement )
    // search the page in the ROM if it is not in the buffer
    while( ! (ReqPagTag_dirty < __temp_pagSize) )  // if the var is not with the page
    {
        __temp_pagSize +=   PAG_SIZE;               // move to next page
    }

    ReqPagTag = __temp_pagSize-PAG_SIZE;

    if(dirtyPag)
    {
        __pageFaultCounter++;
        __sendPagTemp( *CurnPag );
        dirtyPag=DIRTY_PAGE;
    }
    __bringPagROM(ReqPagTag);

PAG_IN_TEMP:

        *CurnPag = ReqPagTag;
}


/*####################################
          Paging commit
#####################################*/

void __pagsCommit()
{

    unsigned int cnt=0;
    unsigned int page;
    while (__persis_pagsInTemp[cnt])
    {
        // send the pages to their final locations in ROM
            __sendPagROM(__persis_pagsInTemp[cnt] );
            __pagsInTemp[cnt] = 0; // clear the temp buffer
           cnt++;
    }

    while(cnt--)
    {
        __persis_pagsInTemp[cnt] =0;
    }

}


uint8_t* __return_addr_no_check(unsigned int * var) {
    if( __IS_VAR_IN_CRNT_PAG(*var) )
    {
        return __VAR_PT_IN_RAM(*var);
    }
    else{
        __pageSwap((var));
        return __VAR_PT_IN_RAM(*var);
    }
}

uint8_t* __return_addr_wr_no_check(unsigned int * var) {
    if( __IS_VAR_IN_CRNT_PAG(*var) )
    {
        dirtyPag = 1;
        return __VAR_PT_IN_RAM(*var);
    }
    else{
        __pageSwap((var));
        dirtyPag = 1;
        return __VAR_PT_IN_RAM(*var);
    }
}


/*
 ************************************
 *     Multiple pages interface
 ************************************
 */

uint8_t* __return_addr_no_check(unsigned int * var) {
    if( __IS_VAR_IN_CRNT_PAG(*var) )
    {
        return __VAR_PT_IN_RAM(*var);
    }
    else{
        __pageSwap((var));
        return __VAR_PT_IN_RAM(*var);
    }
}

uint8_t* __return_addr_wr_no_check(unsigned int * var) {
    if( __IS_VAR_IN_CRNT_PAG(*var) )
    {
        dirtyPag = 1;
        return __VAR_PT_IN_RAM(*var);
    }
    else{
        __pageSwap((var));
        dirtyPag = 1;
        return __VAR_PT_IN_RAM(*var);
    }
}

