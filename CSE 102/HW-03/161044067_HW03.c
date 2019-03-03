// Gokhan Has - 161044067
// CSE102 - HW03

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void menu();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
void horseRacingGame();
void countOccurrence();
void triangleOfSequences();
int power(int a,int b);
/* Defining functions which are going to use in code */

int main()
{
	srand(time(NULL));
	/* This is necessary to random values */
	menu();
	/* In main, only used menu function */
	return 0;
}


void menu()
{
	int selection;

	do{
		printf("\n**************************");
		printf("\n1. Horse Racing Game\n");
		printf("2. Occurrence Counter\n");
		printf("3. Triangle of Sequences\n");
		printf("0. Exit\n");
		printf("**************************");
		printf("\nMake a selection > ");
		scanf("%d",&selection);
		printf("\n");
		/* Printing Menu and its selections */
		
		switch(selection)
		{

			case 1:		
				horseRacingGame();
				break;
			
			case 2:
				countOccurrence();
				break;

			case 3:
				triangleOfSequences();
				break;

			case 0:
				printf("Exiting...\n");
				break;
		}
	
	} while(selection != 0);
	/* If the user selection's is 0, the loop ends and exits */ 
}

int getInt(int mini, int maxi)
{
	int number;
	int flag=1;

	do{	
		scanf("%d",&number);

		if(number >= mini && number <= maxi)
		{
			flag--;
			return number;
			/* If the number entered is within the specified range,
				it returns the number */		
		}
		else
		{
			printf("Enter a wrong number !! \n");
			/* If not, it prompts you enter the another number again */ 
		}
		

	} while(flag != 0);

}

int numberGeneratorBetweenRange(int min, int max)
{
	int number;
	int flag=1;

	do{
		number = rand() % 100;

		if(number >= min && number <= max)
		{
			flag--;
			return number;
			/* This function generates a number using the rand()
				function in the specified range */
		}
	
	}	while(flag != 0);


} 

void horseRacingGame()
{
	int horsesNumber,i,j,timeHorse,winNumber=0;
	int usersHorse,usersHorseTime,min=20;

	horsesNumber = numberGeneratorBetweenRange(3,5);
	/* Assignment of random number to horsesNumber between 3 and 5 */
	printf("\nNumber of Horse : %d",horsesNumber);
	printf("\nHorse Number: ");
	

	usersHorse = getInt(1,horsesNumber);
	/* If the user enters a number other than horsesNumber, 
		It asks the user to enter the number again. */
		
	printf("Racing Stars...\n");
	for(i=1; i<= horsesNumber; i++){
		
		timeHorse = numberGeneratorBetweenRange(10,20);
		
		printf("Horse %d : ",i);
		for(j=1; j <= timeHorse; j++){
			printf("-");
		}
		/* Priting the screen according to time intervals */
		printf("\n");

		if(i == usersHorse){
			usersHorseTime = timeHorse;
			/* Determine which user chooses which horse */
		}

		if(timeHorse < min ){
			winNumber = i;
			min = timeHorse;
			/* 	If timeHorse less than min, timeHorse is assigned to min.
				The horse number is assigned to winNumber to find out 
				which horse will win.  */
		}


		else if(timeHorse == min){
			//  winNumber=0;
			/* 	If there is another horse that finishes at the same time, 
				there will be no winner. */
		} 
		
		// ****************** !! NOTE !! ************************
		// * According to HW03v3, the state of the draw is gone,*
		// * So, we don't need the above "else if" code block.  *
		// ******************************************************
	}

	if(usersHorseTime == min){ 
		printf("You Win! Winner is Horse %d. \n",usersHorse);
	}
	else{
		printf("You Lose! Winner is Horse %d.\n",winNumber);
	}
	
	/* Print results according to the situation. */


	/* 

	else if(usersHorseTime > min && winNumber != 0){
		printf("You Lose! Winner is Horse %d.\n",winNumber);
	}
	else{
		printf("No Winner !\n");
	}

	****************** !! NOTE !! ************************
	* According to HW03v3, the state of the draw is gone,*
	* So, we don't need the above "else if" code block.  *
	******************************************************

	*/
}
	


void countOccurrence()
{
	int bigNumber, searchNumber, occurrence=0;
	int i,j,k,temp,temp2,count=0;
	
	printf("Big Number:");
	scanf("%d",&bigNumber);
	printf("Search Number:");
	scanf("%d",&searchNumber);
	
	temp=searchNumber;
	if(temp==0){ 
		count=1;
		/* If it is zero, it is one digit. */
	} 
	
	
	while(temp!=0)
	{
		i=temp%10; 
		temp=(temp-i)/10;
		count++;
		/* Finds out how many digits the searchNumber is. */
	}
	
	temp2=bigNumber;
	while(temp2!=0)
	{
		k = power(10,count);
		j= (temp2 % k);
		/* The bigNumber is set to the number of digits of the searcNumber. */
		if(j == searchNumber) 
		{
			/* Comparison is made.If is equal, occurrence increases. */
			occurrence++;
		}
		temp2=(temp2-(temp2%10))/10;
		/* Then, one digit is deleted from bigNumber */
	}
	printf("Occurrence: %d\n",occurrence);
}

void triangleOfSequences()
{
	int value,i,j;
	value = numberGeneratorBetweenRange(2,10);
	printf("Random Value > %d\n\n",value);
	
	for(i=1;i<=value;i++)
	{
		for(j=1;j<=i;j++)
		{
			printf("%d ",i*j);
			/* The desired shape is formed by multiplying the number of rows and columns. */
		}
		printf("\n");
	}
}

int power(int a,int b)
{
	int result=1,i;

	for(i=1;i <= b;i++){
		result *= a ;
		/* This function will be used in the occurence function. */
	}
	return result;
}
