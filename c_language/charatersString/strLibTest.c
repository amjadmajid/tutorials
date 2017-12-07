#include <stdlib.h>
#include <stdio.h>
#include "include/strLib.h"


int main(int argc, char const *argv[])
{
	// test the strLen function
	const char testString[] = "This is test string!";
	int sLen = strLen(testString);
	printf("%s%d\n","The length of the string is: ", sLen );

	// Testing the strConcat function
	const char testConcatStr1[] = "I'm concatinated ";
	const char testConcatStr2[] = "string";
	char resStr[ strLen(testConcatStr1)+strLen(testConcatStr1)+1 ];
	strConcat(resStr, testConcatStr1, testConcatStr2);
	printf("%s\n", resStr);

	//Testing the strEqual function
	const char testStrEqual1[] = "string";
	const char testStrEqual2[] = "string";
	const char testStrEqual3[] = "different string";
	const char testStrEqual4[] = "String";

	if(strEqual(testStrEqual1, testStrEqual2)){
		printf("%s%s%s%s%s\n", "the strings '", testStrEqual1, "' and '", testStrEqual2, "' are equal." );
	}else{
		printf("%s%d\n", "The two strings are not the same!!", strEqual(testStrEqual1, testStrEqual2) );
	}
	if(!strEqual(testStrEqual1, testStrEqual3)){
		printf("%s%s%s%s%s\n", "the strings '", testStrEqual1, "' and '", testStrEqual3, "' are not equal." );
	}
	if(!strEqual(testStrEqual1, testStrEqual4)){
		printf("%s%s%s%s%s\n", "the strings '", testStrEqual1, "' and '", testStrEqual4, "' are not equal." );
	}

	// Testing stringCopy function
	char *str1 = "String to be copied";
	char *str2 = (char *) malloc( sizeof(char) * strLen( str1)+1 ) ;
	if( str2 != NULL ){
		copyString(str1, str2);
		printf("%s\n", str2);
	}else{
		printf("%s\n", "unable to copy the string!!" );
	}
	return 0;
}