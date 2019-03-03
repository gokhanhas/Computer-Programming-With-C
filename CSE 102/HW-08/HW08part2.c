// Gokhan Has - 161044067
// CSE 102 - HW08 - part2

#include <stdio.h>

/******************* Defining Functions *******************************/

char * find_operations(int arr[], int expected_val, char operations[],
	size_t arr_len, int cursor, int current);
int find_result(int arr[], char operations[], int arr_len);

/**********************************************************************/

int main(){

	int expected_val = 44;
	int arr_len = 6;
	int array[6] = {25,12,6,10,32,8};
	char operations[arr_len-1];
	char *op;

	op = find_operations(array, expected_val, operations, arr_len, 0, 0);
	printf("Operations String : %s\n",op);

	return 0;
}


int find_result(int arr[], char operations[], int arr_len){
	
	int result=0;
	int i=0,j=0;
	
	while(i<arr_len){
		
		if(operations[j]=='+'){
			
			if(i==0){
				result=result+arr[i]+arr[i+1];
				i=i+2;
				/* The first operation is applied to the zeroth and first indices of the array. */
				/* Therefore, transactions are executed starting from the second index. */
			}
			else{
				result=result+arr[i];
				i++;
				/* Otherwise, the transactions are executed starting from the next index. */
			}
		}
		
		else if(operations[j]=='-'){
			
			if(i==0){
				result=result+arr[i]-arr[i+1];
				i=i+2;
				/* The first operation is applied to the zeroth and first indices of the array. */
				/* Therefore, transactions are executed starting from the second index. */
			}
			
			else{
				result=result-arr[i];
				i++;
				/* Otherwise, the transactions are executed starting from the next index. */
			}
		}
		
		else if(operations[j]=='*'){
			
			if(i==0){
				result=result+(arr[i]*arr[i+1]);
				i=i+2;
				/* The first operation is applied to the zeroth and first indices of the array. */
				/* Therefore, transactions are executed starting from the second index. */
			}
			else{
				result=result*arr[i];
				i++;
				/* Otherwise, the transactions are executed starting from the next index. */
			}
		}
		
		else{
			return result; /* return result. */
		}
		j++; /* index increment. */
	}
	return result;
	/* return result */
}

char * find_operations(int arr[], int expected_val, char operations[], 
	size_t arr_len, int cursor, int current){
	
	int tempLocation=0;
	char *array;
	
	if(cursor>=arr_len){ /* Function termination condition */
		
		current = find_result(arr,operations,arr_len); /* current is assigned a result. */
		
		if(current==expected_val){
			/* If the result is equal to expected_val, it is returned. */
			operations[arr_len-1]='\0';
			return operations;
		}
		else
			return NULL; /* Otherwise the result is not retrieved and NULL is returned. */
	}
	
	if(cursor==0){
		
		operations[cursor]='+';
		cursor=cursor+2;
		/* the initial situation is checked for '+'. */
	}
	
	else{
		tempLocation=cursor;
		operations[cursor-1]='+';
		cursor++;
		/* otherwise the next index will be processed. */
	}
	array = find_operations(arr, expected_val, operations, arr_len, cursor, current);
	/* The function is called again and assigned to array. */
	
	if(array!=NULL){
		return operations;
		/* If condition is satisfied, operations are returned. */
	}
		
	cursor=tempLocation; 
	/* The current location (cursor) is saved (tempLocation).
		It will be used again when going back. */
	
	if(cursor==0){
		
		operations[cursor]='-';
		cursor=cursor+2;
		/* the initial situation is checked for '-'. */
	}
	
	else{
		
		tempLocation=cursor;
		operations[cursor-1]='-';
		cursor++;
		/* otherwise the next index will be processed. */
	}
	array = find_operations(arr, expected_val, operations, arr_len, cursor, current);
	/* The function is called again and assigned to array. */
	
	if(array!=NULL){
		return operations;
		/* If condition is satisfied, operations are returned. */
	}
	
	cursor=tempLocation;
	/* The current location (cursor) is saved (tempLocation).
		It will be used again when going back. */
	
	if(cursor==0){
		
		operations[cursor]='*';
		cursor=cursor+2;
		/* the initial situation is checked for '*'. */
	}
	
	else{
		tempLocation=cursor;
		operations[cursor-1]='*';
		cursor++;
		/* otherwise the next index will be processed. */
	}
	
	array = find_operations(arr, expected_val, operations, arr_len, cursor, current);
	/* The function is called again and assigned to array. */
	
	if(array!=NULL){
		return operations;
		/* If condition is satisfied, operations are returned. */
	}
}