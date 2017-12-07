#include <stdio.h>

void variablesType(){
	int autoNum = 1 ;	// will be initialized with every function call
	const int constNum = 2; // same as above
	static int staticNum = 3; // will be initialized only one
	static int static2Num;
	static2Num = 4; // this explicit initialization will be executed every time the function is called 
	
	printf(" Auto-%d Const-%d static-%d static(with explicit initialization)-%d\n", autoNum, constNum, staticNum, static2Num);
autoNum++; 
//constNum++;  constant number can not be changed 
 staticNum++;
 static2Num++;
}

int main(){
	variablesType();
	variablesType();
	variablesType();
return 0;
}
