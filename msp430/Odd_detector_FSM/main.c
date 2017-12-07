/*
 * @ Author	  : Amjad Yousef Majid
 * @ Date 	  : 14/April/2017
 * @ Gmail ID : amjad.y.maid
 */

/*
 Setup:
 An input binary signal that may toggle between logic 1 and 0 (+3.3V and 0V)
 This signal is received on pin P1.4 (port 1 pin 4).
 On an odd number of the received ones (the input signal at +3.3V) and LED (connected to P1.0) must blink

 This solution is realized using the following Finite State Machine (FSM) abstraction

  ************ Odd number of 1's detector Finite State Machine (FSM) ******************
                 --------                       --------
                 |      |                       |      |
                 |   0  v                       |   0  v
                ------------        1         ------------
    init --->  |    Even    |  ----------->   |    Odd     |     <---- The name of the states
               |------------|      1          |------------|
               |     0      |  <----------    |     1      |     <--- This output of the states
               --------------                 --------------

*/

#include <msp430.h> 

// Functions prototypes
void init();
void wait(unsigned int w);


// Declaring a data type to hold a state of the FSM
struct _state{
	unsigned char out;   	// The Output of a state
	unsigned int wait;		// The time to stay in a state
	unsigned char next[2]; 	// The possible next states
};
typedef struct _state state;

// defining the possible outputs in text for better readability
#define EVEN 	0
#define ODD 		1


// Declaring an array of states to be the FSM
state fsm[2] = {

		{0, 3, {EVEN, ODD} },   // This is the Even State
		{1, 3, {ODD, EVEN} }    // This is the Odd State
};


int main(void) {
    init();

    unsigned char currentState = EVEN ; // initial state
    unsigned char input;
    // traverse the Finite State Machine (FSM)
    while(1)
    {
    		P1OUT = fsm[currentState].out;                 // Output
    		wait(fsm[currentState].wait);
    		input = (P1IN & BIT4)>>4;                      // Get the input and shift it to the fist digit
    		currentState = fsm[currentState].next[input];  // Transition
    }

	
	return 0;
}


void init()
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= BIT0; 				// Make P1.0 and P1.5 are outputs
	P1DIR &=~BIT4; // input
}

void wait(unsigned int w)
{
	volatile unsigned int cnt =  100; // wait for
	while(w --)
		while(cnt--);
}
