#include <stdio.h>

void sortAlgo(int arr[], int arrLen);
void printArr(int arr[], int arrLen);

int main(){
int arr[]={1,3,2,6};
printArr(arr, 4);
sortAlgo(arr, 4);
printArr(arr,4);

return 0;
}

void printArr(int arr[], int arrLen){
	for(int i=0; i<arrLen;i++){
		printf("%d ", arr[i]);
	}	
	putchar('\n');
}

/* The idea of sorting
 * take each element and compare it with rest of the array.
 * After finishing the first round (through the array) the fist element 
 * of it is the smallest
 */
void sortAlgo(int arr[], int arrLen){

	for (int i=0; i< arrLen-1;i++){
		for(int j=i+1; j < arrLen; j++){
			if(arr[i] >  arr[j]) { //ascending order
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;
			}
		}

	}

}
