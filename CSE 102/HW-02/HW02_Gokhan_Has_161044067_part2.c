// Gokhan Has - 161044067
// Part 2

#include <stdio.h>

void printfResults(int digit_count, int num);

int main()
{
	int num,digit_count=0,num_again;
	int control=0;
	

	while(control >= 0)  // This is the control if the number between 23 and 98760
	{
		printf("Enter the number > ");
		scanf("%d",&num);

		if(num >= 23 && num <= 98760)
		{
			control--;
		}
		else
		{
			printf("\nNot in range !! (between 23 and 98760)\n");
		}
	}

	num_again = num; 
	/* This assignment is necessary.Because it will be used another function */
	
	while(num > 0)
	{
		digit_count++;
		num = num / 10;
		/* This loop find the number of digits of the number */
	}

	printfResults(digit_count,num_again);
	
	return 0;
}


void printfResults(int digit_count, int num) // This function print the results
{
	
	int digit1,digit2,digit3,digit4,digit5;

	if(digit_count == 2)
	{
		digit2 = num / 10;
		digit1 = num - digit2 * 10;
		/* If the number is 2 digits, the operations which are mentioned up done  */
		/* Number divided by 10 and find the second digit */
		/* The second digit is multiplied by 10 and subtracted from the number to find the first digit. */
		/* For more digits, the operations is done in increments as in the following */

		printf("\nThe second digit is %d\n",digit2);
		printf("The first digit is %d\n",digit1);
	}

	else if(digit_count == 3)
	{
		digit3 = num / 100;
		num -= digit3 * 100;
		
		digit2 = num / 10;
		num -= digit2 * 10;
		
		digit1 = num;
		/* If the number is 3 digits, the operations which are mentioned up done  */

		printf("\nThe third digit is %d\n",digit3);
		printf("The second digit is %d\n",digit2);
		printf("The first digit is %d\n",digit1);
	}

	else if(digit_count == 4)
	{
		digit4 = num / 1000;
		num -= digit4 * 1000;

		digit3 = num / 100;
		num -= digit3 * 100;
		
		digit2 = num / 10;
		num -= digit2 * 10;
		
		digit1 = num;
		/* If the number is 4 digits, the operations which are mentioned up done  */

		printf("\nThe fourth digit is %d\n",digit4);
		printf("The third digit is %d\n",digit3);
		printf("The second digit is %d\n",digit2);
		printf("The first digit is %d\n",digit1);
	}

	else
	{
		
		digit5 = num / 10000;
		num -= digit5 * 10000;
		
		digit4 = num / 1000;
		num -= digit4*1000;

		digit3 = num / 100;
		num -= digit3 * 100;
		
		digit2 = num / 10;
		num -= digit2*10;
		
		digit1 = num;
		/* If the number is 5 digits, the operations which are mentioned up done  */

		printf("\nThe fifth digit is %d\n",digit5);
		printf("The fourth digit is %d\n",digit4);
		printf("The third digit is %d\n",digit3);
		printf("The second digit is %d\n",digit2);
		printf("The first digit is %d\n",digit1);
	}
}