#ifndef STRLEN_H_

#include <stdlib.h>
#include <stdio.h>

// define constants 
#define True 1
#define False 0

// functions prototypes 
int strLen(const char str[]);
void strConcat( char resStr[], const char str1[], const char str2[] );
int strEqual(const char str1[], const char str2[]);
void copyString( char *from, char *to);
#endif 