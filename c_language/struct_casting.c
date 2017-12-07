#include <stdio.h>
#include <stdint.h>
int main(int argc, char const *argv[])
{
	typedef struct type
	{
		int age;
		char * name ;
	}types;

	types p = {100, "Amjad"};

	int age1 =  p.age;
	printf("The age is %d\n", age1 );
	
	char * name1 = p.name;
	printf("The name is %s\n", name1);
return 0;
}