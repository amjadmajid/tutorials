#include <stdio.h>
#include <stdint.h>
int main(int argc, char const *argv[])
{
	//Bit fields are used to pack information together, using bit level operations,
	// for a better use of memory 

	// Scenario: | 0 0 0 | 0 | 0 | 0 | 0 0 0 0 0 0 0 0 | 000000000000000000
	//             unused  f1  f2  f3     type               index
	// we want to pack the information as illustrated above
	// three unused bits
	// three bits for thee flags
	// one byte for type 
	// 18 bits for index

// 1- ASSIGNING VALUE TO BIT FIELDS

	uint32_t packedData = 0 ; // packedData = 00000000000000000000000000000000
	// -1- Assign 7 to type 
	packedData |= 7 << 18; 

	// -2- Assign 3 to type
	int n = 3;
	packedData &= ~(0xff << 18) ;  // First make sure that the type's bits are all zeros
	packedData |= (n & 0xff) << 18; //  (n & 0xff) to make sure that the n vlaue does not 
									// exceeds 255

	// -3- Assign 8 to type
	n=8;
	// combine the steps above in one statement
				// clear the old bits                assign the new value
	packedData = (packedData & ~( 0xff << 18 ) ) | ( (n & 0xff) << 18 ) ;


// 2- EXTRACTING VALUES FROM BIT FIELDS
	n= 0 ; 
	// assign the value in the field `type` to n
		// -1- shift packedata to put the `type` in the lowest bits
		// -2- mask everything else to make it zero
	n = (packedData >> 18 ) & 0xff;

	printf("The value of `type` is %d\n", n );
	return 0;
}