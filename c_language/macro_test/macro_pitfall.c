/*
The example illustate the pitfal of using macros and
the way to use them safely 
*/

#include <stdio.h>
#include "t.h"


int main(int argc, char const *argv[])
{

	p1("function!");

	FUNC( p1(char[]); )
	return 0;
}

void p1(char[] x){
	printf("%s\n", x);
}