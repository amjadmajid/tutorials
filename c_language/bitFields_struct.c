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

	struct packed_struct
	{
		unsigned int 	:3;  // unnamed field because it is not used
		unsigned int 	f1:1;
		unsigned int 	f2:1;
		unsigned int    f3:1;
		unsigned int    type:8;
		unsigned int    index:18;
	} packed_struct;

	// we do not need to test the size of the
	// assigned value. Only the lower eight bits will be assigned
	packed_struct.type = 7; 
	// The bits fo the type field will be automatically shifted
	// to the lowest eight bits
	printf("%d\n", packed_struct.type * 2 );

	packed_struct.f1 = 1 ; // ... 0000 0001
	packed_struct.f2 = 2 ; // ... 0000 0010 THIS WILL RESULT IN A WARRNING 
						   // this will not set the flag f2 

	if( packed_struct.f1)
		printf("%s\n", "The flag f1 is set");

	if(!packed_struct.f2)
		printf("%s\n", "The flag f2 is CLEARED");
	return 0;
}