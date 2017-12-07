/*
Newton-Raphson Method to Compute the Square Root of x
Step 1: Set the value of guess to 1.
Step 2: If |guess2 - x| < ε, proceed to step 4.
Step 3: Set the value of guess to (x / guess + guess) / 2 and return to step 2.
Step 4: The guess is the approximation of the square root.
*/

#include <stdio.h>
float absoluteValue (float x) {
	if ( x < 0 ) x = -x; return (x);
}
// Function to compute the square root of a number
float squareRoot (float x) {
	const float epsilon = .00001; 
	float guess = 1.0;
	while ( absoluteValue (guess * guess - x) >= epsilon ) 
		{
			guess = ( x / guess + guess ) / 2.0;
		}
	return guess; 
}
int main (void) {
	printf ("squareRoot (2.0) = %f\n", squareRoot (2.0)); 
	printf ("squareRoot (144.0) = %f\n", squareRoot (144.0)); 
	printf ("squareRoot (17.5) = %f\n", squareRoot (17.5));
return 0; 
}