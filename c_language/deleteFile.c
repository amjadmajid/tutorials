#include <stdio.h>

int main(int argc, char const *argv[])
{
	char fileName[30];
	int status;

	printf("Please enter the name of the file you wish to delete: " );
	scanf("%s",fileName);

	status = remove(fileName);

	if(status == 0){
		printf("%s is deleted successfully\n", fileName);
	}else{
		printf("Unable to delete %s\n", fileName);
	}

	return 0;
}