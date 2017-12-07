/*
An enumeration is a user-defined data type that consists of 
integral constants. To define an enumeration, keyword enum is used.
enum flag { const1, const2, ..., constN };
*/
#include <stdio.h>


enum 
{
	zero, // per default the first int constant has the value 0
	one = 1 ,
	two,
	thee,
	four,
	five,
	ten = 10, 
	eleven, // this will have the value 11 
	twelve
} numbers; //declaring a data type 

enum {RANDOM, IMMEDIATE, SEARCH} strategy;


int main(void)
{
//	enum numbers nums; // a variable of enum numbers is created
	numbers = zero;

	strategy = IMMEDIATE;

	if(! numbers )
		printf("%s %d\n", "x is less than 6", strategy);


	return 0;
}