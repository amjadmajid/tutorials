#include "include/strLib.h"

int strLen(const char str[])
{
	/* strLen returns the length of a string
	 It assumes that the string is terminated by a  
	 null character   */ 

	const char *cptr = str; // The value that this pointer points to will not change
	while(*cptr)
		++cptr;

	// The result of subtracting two pointers is the nummber of elements 
	// between their locations 
	return cptr - str; //This is pointer arithmetic 
}


void strConcat( char resStr[], const char str1[], const char str2[] )
{
	/* strConcat concatinate strings str1 and str2. 
		it returns the concatinated string in resStr 
	*/
	int idx1=0;
	while(str1[idx1] != '\0'){
		resStr[idx1] = str1[idx1];		// adding the first string 
		++idx1;
		}

	int idx2=0;
	while(str2[idx2] != '\0'){
		resStr[idx1+idx2] = str2[idx2];  // adding the second sting
		++idx2;
	}

	resStr[idx1+idx2+1] = '\0'; 		 // adding the terminator char

}

int strEqual( const char str1[], const char str2[])
{
	if (strLen(str1) != strLen(str2))
		return False;

	int idx=0;
	while(str1[idx] == str2[idx] && (str1[idx]) !='\0' && str2[idx] !='\0' )
		++idx;

	if( (str1[idx]) =='\0' && str2[idx] =='\0')
		return True;
	else
		return False;
}

void copyString( char *from, char *to)
{
	do{
		*to++ = *from++;
	}while(*from != '\0');
}