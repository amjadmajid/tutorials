#include <msp430.h>
#include <stdint.h>
#include "virtual_chain.h"

//delay
volatile unsigned work_x;
static void burn( uint32_t iters)
{
	while(iters--)
		work_x++;
	while(work_x--)
		iters++;
	while(iters--)
		work_x++;
	while(work_x--)
		iters++;
}

//blink an led once
static void blinkLed(uint32_t wait )
{
	P1OUT |= 0x01; // lit the LED
	burn(wait); // wait
	P1OUT &= ~0x01; // dim the LED
	burn(wait); // wait
}


void task0()
{
	blinkLed( 150000 );
	blinkLed( 10000 );
}


void task1()
{
	blinkLed( 150000 );
	blinkLed( 10000 );
	blinkLed( 10000 );


}

void task2()
{
	blinkLed( 150000 );
	blinkLed( 10000 );
	blinkLed( 10000 );
	blinkLed( 10000 );

	blinkLed( 500000 );

}


int main(int argc, char const *argv[])
{

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	// Disable the GPIO power-on default high-impedance mode to activate previously configured port settings.
	PM5CTL0 &= ~LOCKLPM5;		// Lock LPM5.
	__enable_interrupt();
	P1DIR |= 0x01; // make Port 4 pin 0 an output

	task* current = addTasks(task0,task1 ,task2);
	scheduler(current);
	return 0;
}
