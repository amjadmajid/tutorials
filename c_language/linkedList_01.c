#include <stdio.h>

int main(int argc, char const *argv[])
{
	
	//defining a struct
	struct entry
	{
		int value;
		struct entry  *next;
	};

	// declaring variables
	struct entry n1, n2, n3; 
	struct entry *list_pointer; // list_pointer is pointer to a variable of `struct entry` type

	// initialize the variables
	n1.value = 100;
	n2.value = 200;
	n3.value = 300;

	//linking the list
	list_pointer = &n1; 			//list_pointer points to the start of the list
	n1.next = &n2;
	n2.next = &n3;
	n3.next = (struct entry *) 0; // null pointer of struct entry data type
								  // This null pointer marks the end of the linked list

	while(list_pointer != (struct entry *) 0 )
	{
		printf("%d\n", list_pointer->value);
		list_pointer = list_pointer->next;

	}

	return 0;
}