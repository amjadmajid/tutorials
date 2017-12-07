
#include <stdio.h>

#define True 1
#define False 0

// function declation 
int _chkUserInput(int fact);
int userInput();
long unsigned factorial(int fact );

// validate user input 
int _chkUserInput(int fact)
{
	if (fact < 0 )
	{
		printf("%s\n", "ERROR: invalid input \n");
		return False;
	}
	return True;
}

// get user input 
int userInput()
{
	int fact;
	do{
		printf("%s", "Please enter an integer number to compute the factorial: ");
		scanf("%d", &fact);
	}while( !_chkUserInput(fact));
	return fact;
}

//	compute the factorial 
long unsigned factorial(int fact ){
	if(fact ==0)
		return 1;
	else
		return fact * factorial(fact-1);
}

// display the result
void dispRes(int num , long unsigned fact){
	printf("%s%.5d%s%lu\n", "The factorial of ",num, " is ", fact );
}

// main
int main(int argc, char const *argv[])
{
	int num  = userInput();
	long unsigned fact = factorial(num);
	dispRes(num, fact);
	return 0;
}