#include <stdio.h>

int convertedNumber[64]; 
long int numberToConvert; 
int base;
int digit = 0;

void getNumberAndBase (void) {
	
	printf ("Number to be converted? "); 
	scanf ("%li", &numberToConvert);
	printf ("Base? "); 
	scanf ("%i", &base);
	
	if (base<2 || base>16)	// validate the base 
		{
			printf ("Bad base - must be between 2 and 16\n");
			base = 10;		// set the base to a default value 
		} 	
}

void convertNumber (void) {
do {
		convertedNumber[digit] = numberToConvert % base; 	// get the reminder 
		++digit;											// move to a new location in the array
		numberToConvert /= base;							// integer division to remove the reminder
	}while ( numberToConvert != 0 ); 
}
void displayConvertedNumber (void) {
	const char baseDigits[16] = 
	{ '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; 

	int nextDigit;
	printf ("Converted number = ");
	for (--digit; digit >= 0; --digit ) 	// the initial value of digit is reduced by 1 because 
											// it was increased in the last conversion operation be 1 
		{ 
			nextDigit = convertedNumber[digit]; 
			printf ("%c", baseDigits[nextDigit]);
		}
	printf ("\n"); 
}

int main (void) {
	void getNumberAndBase (void), 	// get user input
	convertNumber (void), 
	displayConvertedNumber (void);
	getNumberAndBase (); 
	convertNumber (); 
	displayConvertedNumber ();
return 0;
}
