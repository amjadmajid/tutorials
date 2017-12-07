#include <stdlib.h>
#include <stdio.h>

int arrSum(int[] , int);
void printMe(int);

int main(int argc, char const *argv[])
{
	int arr[] =  {1,2,3};
	int len = 3;
	int aSum = arrSum(arr, len);
	printMe(aSum);
	return 0;
}


int arrSum( int arr[], const int len)
{
	int res=0, * arrBegin, *arrEnd;
	arrEnd = arr + len; 
	arrBegin = arr;

	while (arrBegin < arrEnd)
	{
		res += *arrBegin;
		arrBegin++;
	}
	return(res);
}

void printMe(int s)
{
	printf("%s%d\n","The sum of the array is ", s );
}