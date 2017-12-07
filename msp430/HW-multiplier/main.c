#include <msp430.h> 


unsigned res, res2;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    *((unsigned int *)&MPY) = 4;   // First operand
    *((unsigned int *)&OP2) = 6;   // Second operand


    res = RESLO;                   // result
//    res2 = RESHI;                   // second part of the result

    __no_operation();

    while(1);

    return 0;
}
