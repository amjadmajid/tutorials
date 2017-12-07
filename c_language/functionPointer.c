#include <stdio.h>
// A function to be pointed to 
 int addNums(int n1, int n2){
	return n1+n2;
}

// Define a pointer to a function that takes two arguments and returns an int
int (*funcPointer)(int,int);

int main(){
	// Link the function pointer to a function
	funcPointer = &addNums;
	// Use the function pointer
	int res = (*funcPointer)(2,3);
	printf("The result is %d\n", res);
}
