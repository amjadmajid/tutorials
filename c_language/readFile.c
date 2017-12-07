/*
 ============================================================================
 Name        : readFile.c
 Author      : Amjed Yousef
 ============================================================================
 */

/*
 * Reading a file in c
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	//ch is used to get one character at a time from the file
	// fineName is an array of char to get the file name from the user
	char ch , fileName[25];

	//File pointer, works as a file handler or give you access to the file
	FILE *fp;
	// prompt the user
	puts("Please enter the file name: ");
	// receive user input
	scanf("%s",fileName);
	// open the file for reading
	fp = fopen(fileName, "r");
	// check if the file point is null
	if(fp  == NULL){
		perror("Error while opening the file\n");
		exit(EXIT_FAILURE);
	}
	// read the file char char
	while( (ch = getc(fp)) != EOF ){
		printf("%c" , ch);
	}
	// close the filed
	fclose(fp);
	return 0;
}
