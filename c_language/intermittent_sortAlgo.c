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

unsigned arr[]={3,1,4,6};
unsigned arr_len = 4;  
unsigned i =  0 ;
unsigned j = 1;

// This task must be blocked at the very first call
void task_outer_loop()
{
	i++;
	j=i+1;
}

void task_inner_loop()
{
	if(arr[i] > arr[j])
	{
		int temp = arr[j];
		arr[j] = arr[i];
		arr[i] = temp;
	}
	if( j >= arr_len)
	{
		os_unblock(task_outer_loop)
	}else{
		os_same();
	}
	j++;
}

